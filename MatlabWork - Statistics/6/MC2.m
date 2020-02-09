function int=MC2(g,a,b,n)
X=unifrnd(a,b,1,n);
M=max(g(X));
Y=unifrnd(0,M,1,n);
int=(b-a)*M*mean(Y<=g(X));
clf; axis equal; hold on;
plot(X(Y<=g(X)),Y(Y<=g(X)),'.k','markersize',15);
fplot(g,[a,b],'r','linewidth',2);
axis([a,b,-0.1 M+0.1]);