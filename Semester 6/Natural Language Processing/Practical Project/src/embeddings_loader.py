from gensim.models import KeyedVectors, FastText
from gensim.models.fasttext import load_facebook_model
import os
import torch


def load_embedding_model(embedding_path):
    """
    Try to load as FastText, fallback to KeyedVectors for .vec/.bin
    """
    try:
        # Try FastText first
        return FastText.load_fasttext_format(embedding_path)
    except Exception:
        try:
            # Try KeyedVectors (Word2Vec format)
            return KeyedVectors.load_word2vec_format(embedding_path, binary=embedding_path.endswith('.bin'))
        except Exception as e:
            print(f"ERROR loading {embedding_path}: {e}")
            return None


def get_word_vector(word, model):
    """
    Returns the word vector for a word, using model's get_vector or __getitem__.
    """
    try:
        return model[word]
    except KeyError:
        return None