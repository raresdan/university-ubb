import numpy as np
from sklearn.metrics.pairwise import cosine_similarity
import Levenshtein


def cosine_sim(vec1, vec2):
    """
    Calculate the cosine similarity between two vectors
    """
    if vec1 is None or vec2 is None:
        return np.nan
    v1 = np.array(vec1).reshape(1, -1)
    v2 = np.array(vec2).reshape(1, -1)
    return float(cosine_similarity(v1, v2)[0][0])


def jaccard_sim(vec1, vec2, k=20):
    """
    Calculate the Jaccard similarity between two vectors.
    The Jaccard similarity is defined as the size of the intersection divided by the size of the union. 
    This function considers the top k elements of each vector.
    """
    if vec1 is None or vec2 is None:
        return np.nan
    idx1 = set(np.argsort(np.abs(vec1))[-k:])
    idx2 = set(np.argsort(np.abs(vec2))[-k:])
    intersection = len(idx1 & idx2)
    union = len(idx1 | idx2)
    if union == 0:
        return 0.0
    return intersection / union


def dice_coef(vec1, vec2, k=20):
    """
    Calculate the Dice coefficient between two vectors.
    The Dice coefficient is defined as twice the size of the intersection divided by the sum of the sizes of the two sets.
    This function considers the top k elements of each vector.
    """
    if vec1 is None or vec2 is None:
        return np.nan
    idx1 = set(np.argsort(np.abs(vec1))[-k:])
    idx2 = set(np.argsort(np.abs(vec2))[-k:])
    intersection = len(idx1 & idx2)
    if (len(idx1) + len(idx2)) == 0:
        return 0.0
    return (2 * intersection) / (len(idx1) + len(idx2))



def levenshtein_similarity(w1, w2):
    """
    Calculate the Levenshtein similarity between two words.
    The Levenshtein similarity is defined as 1 - (Levenshtein distance / max(len(w1), len(w2))).
    """
    dist = Levenshtein.distance(w1, w2)
    max_len = max(len(w1), len(w2))
    if max_len == 0:
        return 1.0
    return 1 - dist / max_len
