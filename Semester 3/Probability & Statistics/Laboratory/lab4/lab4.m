pkg load statistics

N = input("Number of simulation: ");
p = input("Probability of getting 1: ");
U = rand(1, N);
X = (U < p);

U_X = [0,1];
n_X = hist(X, length(U_X));
rel_freq = n_X/N
