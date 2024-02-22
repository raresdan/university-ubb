pkg load statistics

p = input("Number of success: ");
N = input("Number of simulation: ");
X = zeros(1, N);

for i = 1:N
  X(i) = 0;
  while rand() >= p
    X(i) = X(i) + 1;
  endwhile
 endfor

K = [0:20];
p_K = geopdf(K,p);

U_X = unique(X);
n_X = hist(X, length(U_X));

rel_freq = n_X/N;

clf;
plot(U_X, rel_freq, '*', K, p_K, 'ro')
