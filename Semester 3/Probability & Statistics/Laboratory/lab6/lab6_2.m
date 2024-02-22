pkg load statistics

# Define the data for premium and regular gasoline
X1 = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];
X2 = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2];

n1 = length(X1);
n2 = length(X2);

# Ask the user for the signifance level
alpha = input("Significance level: ")

#2. a.
# Test for Population Variances
[H, PVAL, CI, STATS] = vartest2(X1, X2, 'alpha', alpha);

# Display results for population variances
printf("The value of H is: %d. \n", H);
if H == 0
    printf('H0 is not rejected, variances are equal\n');
else
    printf('H0 is rejected, population variances differ\n');
end

# Calculate rejection region for population variances
q1 = finv(alpha/2, STATS.df1, STATS.df2);
q2 = finv(1-alpha/2, STATS.df2, STATS.df1);

printf('The rejection region is (-inf, %4.3f) U (%4.3f, inf)\n', q1, q2);
printf('The observed value is %4.3f\n', STATS.fstat);
printf('The pvalue is %4.3f\n', PVAL);

# 2.b.
# Test for Population Means
[H, PVAL, CI, STATS] = ttest2(X1, X2, 'alpha', alpha, 'vartype', 'unequal');
#%vartype - unequal (because in point a. we got different values for population
%variances. If they were equal, we would have used 'equal' parameter.
%PVAL - P value; CI = confidence level

# Hypotheses:
# Null Hypothesis (H0): The average gas mileage with premium gasoline is not significantly higher
# than the average gas mileage with regular gasoline (μ1 <= μ2).
# Alternative Hypothesis (Ha): The average gas mileage with premium gasoline is significantly higher
# than the average gas mileage with regular gasoline (μ1 > μ2).

# Display Results for Means
printf("The value of H is: %d. \n", H);
if H == 0
    printf('H0 is not rejected. Gas mileage does NOT seem higher with premium gasoline.\n');
else
    printf('H0 is rejected. Gas mileage seems higher with premium gasoline.\n');
end

# Display Additional Information for Means
q1 = tinv(alpha, STATS.df);
printf('The rejection region is (%4.3f, +inf)\n', q1);
printf('The pvalue of the test statistic is %4.3f.\n', PVAL);
printf('Observed value of the test statistic is %4.3f.\n', STATS.tstat);


# Smaller, less, lower -> left tailed test
# Bigger, more, greater, exceeds(a value), higher -> right tailed test
# equal, differ -> two tailed test

# Left-tailed test:
# Null hypothesis (H0): μ ≥ μ0
# Alternative hypothesis (Ha): μ < μ0
# Rejection region: (-∞, q)
# Critical value: q such that P(test statistic < q) = α

# Right-tailed test:
# Null hypothesis (H0): μ ≤ μ0
# Alternative hypothesis (Ha): μ > μ0
# Rejection region: (q, ∞)
# Critical value: q such that P(test statistic > q) = α

# Two-tailed test:
# Null hypothesis (H0): μ = μ0
# Alternative hypothesis (Ha): μ ≠ μ0
# Rejection region: (-∞, q1) ∪ (q2, ∞)
# Critical values: q1 and q2 such that P(test statistic < q1 or test statistic > q2) = α
