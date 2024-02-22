pkg load statistics

% Given data
standard = [46, 37, 39, 48, 47, 44, 35, 31, 44, 37];
new = [35, 33, 31, 35, 34, 30, 27, 32, 31, 31];

% Significance level
alpha = 0.05;

% a. Test for Population Variances
% Null hypothesis (H0): Variances are equal
% Alternative hypothesis (Ha): Variances are not equal
[H, PVAL, CI, STATS] = vartest2(standard, new, 'alpha', alpha);

% Display results for population variances
fprintf('a. Test for Population Variances:\n');
fprintf('The value of H is: %d. \n', H);
if H == 0
    fprintf('H0 is not rejected; variances do not seem to differ at the %.2f significance level.\n', alpha);
else
    fprintf('H0 is rejected; population variances differ at the %.2f significance level.\n', alpha);
end

alpha_over_2 = alpha / 2;
q1 = finv(alpha_over_2, STATS.df1, STATS.df2);
q2 = finv(1 - alpha_over_2, STATS.df1, STATS.df2);

fprintf('Rejection Region: (-∞, %.4f) U (%.4f, +∞)\n', q1, q2);
fprintf('The 95%% confidence interval for the ratio of population variances is [%.4f, %.4f].\n', CI(1), CI(2));
fprintf('The p-value for the test is %4.3f.\n\n', PVAL);

% b. Confidence interval for the difference of the average assembling time
% Assume unequal variances (use 'unequal' option)
% Hypotheses:
% Null Hypothesis (H0): The average assembling time for the standard method is not significantly different
# from the average assembling time for the new method (μ1 = μ2).
% Alternative Hypothesis (Ha): The average assembling time for the standard method is significantly different
# from the average assembling time for the new method (μ1 ≠ μ2).
[H, PVAL, CI, STATS] = ttest2(standard, new, 'alpha', alpha, 'vartype', 'unequal');

% Display results for the confidence interval
fprintf('b. 95%% Confidence Interval for the Difference of Average Assembling Time:\n');
fprintf('The 95%% confidence interval for the difference of average assembling time is [%4.3f, %4.3f].\n', CI(1), CI(2));
fprintf('\nRejection Region:\n');
fprintf('(-∞, %.4f) U (%.4f, +∞)\n', -STATS.tstat, STATS.tstat)
