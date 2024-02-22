%problem 1

pkg load statistics

N = input("N=")
sigma = input("sigma = ")
alpha = input("alpha = ")
beta = input("beta = ")
m = input("m= ")

normcdf(0,m,sigma)

1 - normcdf(0, m, sigma)

1 - normcdf(1,m,sigma) - normcdf(-1,m,sigma)

x_alpha = norminv(alpha, m, sigma)
y_alpha = norminv(1-beta,m,sigma)
