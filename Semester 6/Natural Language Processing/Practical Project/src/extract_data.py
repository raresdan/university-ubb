import pandas as pd

df = pd.read_csv("data/RoSimLex-Common.txt", sep="\t")
df = df[df["ro pair accept"] == 1]  # Only accepted Romanian word pairs

# Keep key columns
df = df[["word_ro_1", "word_ro_2", "ro human scores"]]
df.columns = ["word1", "word2", "human_score"]
print(df.head())

# Save to CSV
df.to_csv("data/RoSimLex-999.csv", index=False)