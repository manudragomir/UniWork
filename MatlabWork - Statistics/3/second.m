#lala

function out = second(n,p,m)
  x1=binornd(n,p,1,m);
  N1=histc(x1,0:n);
  subplot(1,2,1); 
  hold on; title('Binornd');
  bar(0:n,N1/m,'hist','FaceColor','b');
  bar(0:n,binopdf(0:n,n,p),'FaceColor','y');
  legend('estimated probabilities','theoretical probabilities');
  
  x2=my_binord(p,n,m);
  N2=histc(x2,0:n);
  subplot(1,2,2);
  hold on; title('My binornd');
  bar(0:n,N2/m,'hist','FaceColor','b');
  bar(0:n,binopdf(0:n,n,p),'FaceColor','y');
  legend('estimated probabilities','theoretical probabilities');

endfunction



