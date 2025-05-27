import sys
import os

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'src')))

import streamlit as st
import numpy as np
import pandas as pd
from embeddings_loader import load_embedding_model, get_word_vector
from similarity_metrics import cosine_sim, jaccard_sim, dice_coef, levenshtein_similarity
from rowordnet_utils import get_rowordnet_path_similarity
from visualizations import plot_embedding_space
from evaluation import compute_correlation

import torch
from transformers import AutoTokenizer, AutoModel

# Load Static-word Embedding Models
@st.cache_resource
def load_models():
    fasttext_model = load_embedding_model("D:\\_DOCUMENTE_RARES\\Desktop\\ro_word_similarity\\embeddings\\cc.ro.300.vec")
    conll_model = load_embedding_model("D:\\_DOCUMENTE_RARES\\Desktop\\ro_word_similarity\\embeddings\\CoNLL17.bin")
    return fasttext_model, conll_model

# Load Contextual Embedding Model (BERT)
@st.cache_resource
def load_bert():
    model_name = "dumitrescustefan/bert-base-romanian-cased-v1"
    tokenizer = AutoTokenizer.from_pretrained(model_name)
    model = AutoModel.from_pretrained(model_name)
    return tokenizer, model

def get_bert_sentence_embedding(sentence, tokenizer, model):
    tokens = tokenizer(sentence, return_tensors="pt")
    with torch.no_grad():
        outputs = model(**tokens)
    # Use the [CLS] token as sentence embedding
    return outputs.last_hidden_state[0,0,:].numpy()



# Streamlit App

st.title("Romanian Word Similarity Explorer")

tabs = st.tabs(["Static Embeddings", "Contextual Embeddings (BERT)"])

with tabs[0]:
    st.header("Static Embedding Similarity")
    fasttext_model, conll_model = load_models()

    word1 = st.text_input("First word (Romanian):", key="static1")
    word2 = st.text_input("Second word (Romanian):", key="static2")

    def compute_metrics(w1, w2, model):
        v1 = get_word_vector(w1, model)
        v2 = get_word_vector(w2, model)
        return {
            "Cosine": cosine_sim(v1, v2),
            "Jaccard": jaccard_sim(v1, v2),
            "Dice": dice_coef(v1, v2),
            "Levenshtein": levenshtein_similarity(w1, w2),
            "ROWordNet Path (noun)": get_rowordnet_path_similarity(w1, w2, pos="n")
        }

    if word1 and word2:
        scores_fast = compute_metrics(word1, word2, fasttext_model)
        scores_conll = compute_metrics(word1, word2, conll_model)

        st.subheader("Similarity Table")
        st.table({
            "Metric": list(scores_fast.keys()),
            "FastText": [f"{v:.3f}" if isinstance(v, float) else v for v in scores_fast.values()],
            "CoNLL17": [f"{v:.3f}" if isinstance(v, float) else v for v in scores_conll.values()],
        })
        
    st.markdown("---")
    with st.expander("Show Correlation with Human Judgments (entire dataset)"):
        st.write("**Pearson and Spearman correlation between each metric/model and human similarity scores.**")
        df = pd.read_csv("data/RoSimLex-999.csv") 
        # Helper: Compute all metrics for a model
        def batch_metrics(model):
            scores = {
                "Cosine": [],
                "Jaccard": [],
                "Dice": [],
                "Levenshtein": [],
                "ROWordNet Path": []
            }
            for _, row in df.iterrows():
                w1, w2 = row["word1"], row["word2"]
                v1 = get_word_vector(w1, model)
                v2 = get_word_vector(w2, model)
                scores["Cosine"].append(cosine_sim(v1, v2))
                scores["Jaccard"].append(jaccard_sim(v1, v2))
                scores["Dice"].append(dice_coef(v1, v2))
                scores["Levenshtein"].append(levenshtein_similarity(w1, w2))
                scores["ROWordNet Path"].append(get_rowordnet_path_similarity(w1, w2, pos="n"))
            return scores

        fasttext_scores = batch_metrics(fasttext_model)
        conll_scores = batch_metrics(conll_model)
        human = df["human_score"].values

        # Prepare correlation table
        table_data = []
        for metric in fasttext_scores.keys():
            for label, scores in [("FastText", fasttext_scores), ("CoNLL17", conll_scores)]:
                arr = np.array(scores[metric])
                corr = compute_correlation(human, arr)
                pearson = f"{corr['pearson']:.3f}" if not np.isnan(corr['pearson']) else "n/a"
                spearman = f"{corr['spearman']:.3f}" if not np.isnan(corr['spearman']) else "n/a"
                table_data.append({
                    "Metric": metric,
                    "Model": label,
                    "Pearson": pearson,
                    "Spearman": spearman
                })

        table_df = pd.DataFrame(table_data)
        st.table(table_df)



with tabs[1]:
    st.header("Contextual Embedding Similarity (BERT)")
    tokenizer, bert_model = load_bert()
    col1, col2 = st.columns(2)

    with col1:
        word1 = st.text_input("Word 1 (Romanian):", key="bert1")
        context1 = st.text_area("Sentence/context for Word 1:", key="ctx1")
    with col2:
        word2 = st.text_input("Word 2 (Romanian):", key="bert2")
        context2 = st.text_area("Sentence/context for Word 2:", key="ctx2")

    if word1 and context1 and word2 and context2:
        # Insert the word into its context (replace a token [MASK] if you want, or just use the sentence)
        emb1 = get_bert_sentence_embedding(context1, tokenizer, bert_model)
        emb2 = get_bert_sentence_embedding(context2, tokenizer, bert_model)
        sim = cosine_sim(emb1, emb2)
        st.write(f"**Contextual Cosine Similarity (BERT):** {sim:.3f}")
        st.write("_(Similarity is highest when words have similar meaning in these contexts)_")
