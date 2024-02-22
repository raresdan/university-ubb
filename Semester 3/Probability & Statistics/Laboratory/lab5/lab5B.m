pkg load statistics

% Solving B 1 a)

X = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7, 12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7];
n = length(X);
oneMinusAplha = input("Confidence level: ");
alpha = 1 - oneMinusAplha;
sigma = 5;
% quantile => norminv
m1 = mean(X) - sigma/sqrt(n) * norminv(1 - alpha / 2, 0, 1);
m2 = mean(X) - sigma/sqrt(n) * norminv(alpha / 2, 0, 1);

printf("The confidence interval for the mean when you know sigma is (m1, m2) = (%4.3f, %4.3f)\n", m1, m2);


% Solving B 1 b)
% s = standard deviation of the given data
% quantile => tinv

m1b = mean(X) - std(X)/sqrt(n) * tinv(1 - alpha/2, n-1);
m2b = mean(X) - std(X)/sqrt(n) * tinv(alpha/2, n-1);

printf("The confidence interval for the mean when sigma unknown is (m1, m2) = (%4.3f, %4.3f)\n", m1b, m2b);


% Solving B 1 c)
% s^2 is computed with var() and s is computed with std()
% quantile => chi2

v1 = ((n-1) * var(X))/chi2inv(1 - alpha/2, n-1);
v2 = ((n-1) * var(X))/chi2inv(alpha/2, n-1);

printf("The confidence interval for the variance (v1, v2) = (%4.3f, %4.3f)\n", v1, v2);

s1 = sqrt(v1);
s2 = sqrt(v2);

printf("The confidence interval for the standard deviation (s1, s2) = (%4.3f, %4.3f)\n", s1, s2);
