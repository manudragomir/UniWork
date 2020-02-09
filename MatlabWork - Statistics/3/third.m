#lala

function out = third(n,p,m)
  clf;
  x1=geornd(p,1,m);
  n= max(x1);
N1=histc(x1,0:n);
subplot(1,2,1); hold on; title('Geornd');
bar(0:n,N1/m,'hist','FaceColor','b');
bar(0:n,geopdf(0:n,p),'FaceColor','y');
legend('estimated probabilities','theoretical probabilities');
x2=my_geornd(p,m);
n = max(x2);
N2=histc(x2,0:n);
subplot(1,2,2); hold on; title('My geornd');
bar(0:n,N2/m,'hist','FaceColor','b');
bar(0:n,geopdf(0:n,p),'FaceColor','y');
legend('estimated probabilities','theoretical probabilities');

endfunction



