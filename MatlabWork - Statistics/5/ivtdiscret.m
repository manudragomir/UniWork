function Y=ivtdiscret(x,p,N) %inverse transform method
  Y = zeros(1,N);
  q = cumsum(p);
  for i=1:N
    U = unifrnd(0,1);
    Y(i) = x(find(U <= q,1));
  endfor
endfunction