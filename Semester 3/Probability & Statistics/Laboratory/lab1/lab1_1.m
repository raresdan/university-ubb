pkg load statistics

%We ask the user to input the
%required values for the binomial
n = input("Give the nb. of trials n= ")
p = input("Give the prob. of success p= ")
%n is a natural nb.
%p is a value between 0 and 1 !!!
%x is the nb. of success x -values fo the pdf
x = 0:1:n
%works like a for
px = binopdf(x,n,p);
hold on
plot(x, px, 'r+')
%if you wish to have multiple graphs
%in the same window, write the com.
%"hold on"
%to give the values for the CDF
%you must always "simulate continuity"
%that is
xx = 0:0.01:n
fx = binocdf(xx,n,p);
legend
plot(xx,fx,"b")
%use hold on & legend to puten
%them together
