pkg load statistics
#Example 3

# Given data
sizes = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96];

# Calculate sample mean and standard deviation
sample_mean = mean(sizes); #mu0
sample_std = std(sizes);  #mu1

# Calculate the margin of error
alpha = 0.05;  # 95% confidence level

# Perform one-sample t-test to get the confidence interval directly
# For subpoint (a), where you're constructing a confidence interval for
# the mean, it's a two-tailed test because you're interested in whether
# the true mean is different from the sample mean.
[H, PVAL, CI, STATS]= ttest(sizes, sample_mean, 'alpha', alpha);
# Display the results for subpoint a
fprintf('a. The %d%% confidence interval for the average size of nickel particles is (%4.3f, %4.3f)\n', (1-alpha)*100, CI(1), CI(2));

# Calculate the rejection region for subpoint a
t_critical_a = tinv(alpha/2, length(sizes) - 1);
rejection_region_a = [-inf, t_critical_a];
fprintf('Rejection Region for subpoint a: (-∞, %4.3f) U (%4.3f, ∞)\n', -t_critical_a, t_critical_a);

# Given null hypothesis: H0: mu = 3
mu0 = 3;

# Perform one-sample t-test
[H, PVAL, CI, STATS] = ttest(sizes, mu0, 'alpha', 0.01, 'tail', 'left');

# Display results for the one-sample t-test
if H == 0
    printf('b. At the 1%% significance level, there is no evidence that nickel particles are smaller than 3.\n');
else
    printf('b. At the 1%% significance level, there is evidence that nickel particles are smaller than 3.\n');
end

# Calculate the rejection region for subpoint b
t_critical_b = tinv(0.01, length(sizes) - 1);
rejection_region_b = [-inf, t_critical_b];

printf('   The p-value of the test statistic is %4.3f.\n', PVAL);
printf('   The observed value of the test statistic is %4.3f.\n', STATS.tstat);
fprintf('Rejection Region for subpoint b: (-∞, %4.3f)\n', t_critical_b);
