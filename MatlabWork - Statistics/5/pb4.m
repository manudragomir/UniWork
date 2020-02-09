function pb4(n)
  x = exprnd(15, 1, n);
  y = unifrnd(5,15,1,n);
  I = (15 <= x) & (x <= 10 + y);
  pr_sim = mean(I)
  pr_teor = (3 * exp(-5/3) - exp(-1))/2;
  x = exprnd(15, 10, n);
  y = unifrnd(5,15,10,n);
  I = (15 <= x) & (x <= 10 + y);
  media_sim = mean(sum(I,1));
  media_teor = 5 * (3 * exp(-5/3) - exp(-1));
endfunction
