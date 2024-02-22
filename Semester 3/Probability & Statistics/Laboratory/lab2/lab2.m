%pdf: f(x) = P(X=x)
%cdf: F(x) = P(X<=x)
%App. c) P(X=0)
p1=binopdf(0,3,0.5)
p2=1-binopdf(1,3,0.5)

%d) P(X<=2) = F(2)
p3=binopdf(2,3,0.5)
%p4=...
%P(X<2) = P(X<=1)


