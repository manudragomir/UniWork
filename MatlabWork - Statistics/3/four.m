#lala

function out = four(p,m,k)
  rr = randsample([-1 1], m * k, true, [1-p p]);
  rr = reshape(rr, m, k);
  col = [];
  for j=1:m
    last = 0;
    fprintf('%d ', last);
    for i=1:k
      rr(j,i) = last + rr(j,i);
      last = rr(j,i);
      fprintf('%d ', last);
    endfor
  
    col(j) = last;
  fprintf('\n');
endfor
  bar(-k:k, histc(col, -k:k));

  clf;

N=histc(col,-k:2:k);
subplot(1,1,1); hold on; title('Binomial Distribution');
bar(-k:2:k,N/m,'hist','FaceColor','b');
bar(-k:2:k,binopdf(0:k,k,p),'FaceColor','y');
legend('estimated probabilities','theoretical probabilities');

endfunction



