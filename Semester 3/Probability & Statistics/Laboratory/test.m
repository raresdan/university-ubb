# Problem 7
pkg load statistics

# Input data
X1 = [1021, 980, 1017, 988, 1005, 998, 1014, 985, 995, 1004, 1030, 1015, 995, 1023];
X2 = [1070, 970, 993, 1013, 1006, 1002, 1014, 997, 1002, 1010, 975];

# Ask the user for the signifance level
alpha = input("Significance level: ");

# 7.a.
printf("\na.\n");
# The null hypothesis H0: mu1 = mu2
# The alternative hypothesis H1: mu1 != mu2
# Two tailed test
# We choose vartest2 for comapring variances

[H, PVAL, CI, STATS] = vartest2(X1, X2, 'alpha', alpha);

printf("The value of H is: %d. \n", H);
if H == 0
    printf('H0 is not rejected, variances are equal\n');
else
    printf('H0 is rejected, population variances differ\n');
end

q1 = finv(alpha/2, STATS.df1, STATS.df2);
q2 = finv(1-alpha/2, STATS.df2, STATS.df1);

printf('The rejection region is (-inf, %4.3f) U (%4.3f, inf)\n', q1, q2);
printf('The observed value of the test statistic is %4.3f\n', STATS.fstat);
printf('The pvalue is %4.3f\n', PVAL);

#7.b
printf("\nb.\n");
# The confidence interval for the difference of the average (means)
# The null hypothesis H0: mu1 = mu2
# The alternative hypothesis H1: mu1 != mu2
# To compare the means we have to perform a ttetst2
# Two tailed test


# We set vartype to equal because our variances are equal
[H, PVAL, CI, STATS] = ttest2(X1, X2, 'alpha', alpha, 'vartype', 'equal');

printf("The confidence interval [%4.3f, %4.3f]\n", CI(1), CI(2));
printf('The rejection region is (-inf, %4.3f) U (%4.3f, inf)\n', -STATS.tstat, STATS.tstat);
