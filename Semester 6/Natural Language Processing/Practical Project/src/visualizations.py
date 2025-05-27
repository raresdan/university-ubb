import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.manifold import TSNE
import numpy as np

def plot_scatter(human, model, title):
    plt.figure(figsize=(6,6))
    sns.scatterplot(x=human, y=model)
    plt.xlabel("Human Similarity")
    plt.ylabel("Model Similarity")
    plt.title(title)
    plt.show()

def plot_embedding_space(words, vectors, method="tsne"):

    valid = [(w, v) for w, v in zip(words, vectors) if v is not None]
    if len(valid) < 2:
        plt.figure(figsize=(6,2))
        plt.text(0.5, 0.5, "Need at least two words with vectors!", ha='center', va='center', fontsize=16)
        plt.axis('off')
        return plt

    words, vectors = zip(*valid)
    arr = np.vstack(vectors)
    tsne = TSNE(n_components=2, random_state=42)
    reduced = tsne.fit_transform(arr)

    plt.figure(figsize=(8,8))
    plt.scatter(reduced[:,0], reduced[:,1])
    for i, word in enumerate(words):
        plt.annotate(word, (reduced[i,0], reduced[i,1]))
    plt.title("Word Embedding Space")
    return plt  

