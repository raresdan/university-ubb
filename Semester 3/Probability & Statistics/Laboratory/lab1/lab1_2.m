pkg load statistics

%Application 2
%subpoint A
%use binomial distribution
%n = 3 p = 0.5
x = 0:1:3
px = binopdf(x,3,0.5);
% the probability distribution of x is
% 0       1      2       3
%0.125  0.375  0.375   0.125
xx = 0:0.5:3
fx = binocdf(xx, 3. 0.5);
