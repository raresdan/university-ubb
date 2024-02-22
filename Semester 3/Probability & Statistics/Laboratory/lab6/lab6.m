pkg load statistics

x = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7, 12, 5, 6, 2, 1, 13,  14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7];
n = length(x);
alpha = input("Significance level: ")

# the null hypothesis is H0: u = 8.5 (it goes together with u > 8.5, the standard is met)
# the alternative hypothesis H1: u < 8.5 (the standard is not met)
# this is a left tailed test for u)

printf("Left tailed test for the mean when sigma is known")
sigma = 5;
M0 = 8.5;

[H, PVAL, CI, ZVALUE] = ztest(x, M0, sigma, 'alpha', alpha, 'tail', 'left');

zalpha = norminv(alpha, 0, 1);
RR = [-inf, zalpha];

printf("The value of H is: %d. \n", H);
if (H == 1)
  printf("The null hypothesis is rejected.\n");
  printf("The data suggests that the standard is not met.\n");
else
  printf("The null hypothesis is not rejected.\n");
  printf("The data suggests that the standard is met.\n");
endif

printf("The rejection region is (%4.3f, %4.3f)\n", RR);
printf("The observed value of the test statistic is %4.3f\n", ZVALUE);
printf("The pvalue of the test is %4.3f\n", PVAL);

# find the role of pval
# It represents the probability of obtaining results as extreme as or
# more extreme than the observed results, assuming that the null
# hypothesis is true.

# Hint for 1. b) ttest
# right tailed test for the mean

% Hypotheses
null_mean = 5.5; # mu1
alpha = 0.05; % Significance level (you can change this to 0.01 for 1% significance)

% One-sample t-test
% Null hypothesis (H0): Average number of files <= 5.5
% Alternative hypothesis (H1): Average number of files > 5.5
[H, PVAL, CI, STATS] = ttest(x, null_mean, 'tail', 'right');

% Display results
printf('Hypothesis Test Results:\n');
printf('Null hypothesis (H0): Average number of files <= %4.3f\n', null_mean);
printf('Alternative hypothesis (H1): Average number of files > %4.3f\n', null_mean);

critical_value = tinv(1 - alpha, n - 1);
printf('t-statistic: %4.3f\n', STATS.tstat);
printf('p-value: %4.3f\n', PVAL);
printf('\nRejection Region:\n');
printf('(%4.3f, +inf)\n', critical_value);

% Decision based on significance level
printf('\nDecision:\n');
if H == 1
    printf('Reject the null hypothesis at the %.2f significance level.\n', alpha);
else
    printf('Fail to reject the null hypothesis at the %.2f significance level.\n', alpha);
end

# Hint for 2. a) vartest2
# 2 tailed test for comparing variances

# Hint for 2. b) ttest2
# right tailed test for the difference of means

# ztest + norminv -> when you know the population standard deviation and have a large sample size + you need mu
# ttest + tinv -> when the population standard deviation is unknown and you have a relatively small sample size + you need mu
# vartest2 + finv -> when comparing the variances of two independent samples
# ttest2 + tinv -> when comparing the means of two independent samples
