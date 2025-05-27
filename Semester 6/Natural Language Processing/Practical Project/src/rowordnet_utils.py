import rowordnet
import numpy as np

# Load the model globally, so it’s loaded only once
wn = rowordnet.RoWordNet()

def get_rowordnet_path_similarity(word1, word2, pos="n"):
    """
    Compute the maximum path similarity for all synset pairs between two words.
    If no synsets, returns np.nan.
    """

    synsets1 = [s for s in wn.synsets(word1, strict=True) if s.endswith("-" + pos)]
    synsets2 = [s for s in wn.synsets(word2, strict=True) if s.endswith("-" + pos)]
    if not synsets1 or not synsets2:
        return np.nan

    max_similarity = 0.0
    for s1 in synsets1:
        for s2 in synsets2:
            try:
                similarity = wn.path_similarity(s1, s2)
                if similarity is not None and similarity > max_similarity:
                    max_similarity = similarity
            except Exception:
                continue
    return round(max_similarity, 3) if max_similarity > 0 else np.nan
