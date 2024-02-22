pkg load statistics

n = input("Number of trials: ");
p = input("Probability of getting 1: ");
N = input("Number of simulation: ");

U = rand(0,1);
X = sum(U < p);
K = [0:n]

p_K = binopdf(K,n,p);
U_X = unique(X);
n_X = hist(X, length(U_X));

rel_freq = n_X/N;

clf;
plot(U_X, rel_freq, '*', K, p_K, 'ro')
