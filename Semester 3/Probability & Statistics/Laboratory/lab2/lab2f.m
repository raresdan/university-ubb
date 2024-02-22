N = input("Enter the number of simulations: ")
%U is a matrix
U = rand(3,N)
%Compare all elements of U with 0.5
Y = (U<0.5)
X = sum(Y)
%Plot a chart
clf
hist(X)
