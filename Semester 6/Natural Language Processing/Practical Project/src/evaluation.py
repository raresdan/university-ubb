import numpy as np
from scipy.stats import pearsonr, spearmanr

def compute_correlation(human_scores, model_scores):
    """
    Compute Pearson and Spearman correlation. Ignores pairs with nan.
    """
    mask = ~np.isnan(model_scores)
    human = np.array(human_scores)[mask]
    model = np.array(model_scores)[mask]
    pearson = pearsonr(human, model)[0]
    spearman = spearmanr(human, model)[0]
    return {"pearson": pearson, "spearman": spearman}
