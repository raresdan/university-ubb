%exercise 2
pkg load statistics

p = input("Enter a p between (0.05;0.95): ")

for n=1:3:100
  k = 0:n
  y = binopdf(k,n,p);
  plot(k,y)
  pause(0.5)
 endfor

