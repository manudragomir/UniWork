function out = BayesNet(n)
  N = zeros(1,n);
  for i = 1:n
    B1 = bernoulli(0.8);
    if B1 == 1
      B2 = bernoulli(0.9);
    else
      B2 = bernoulli(0.6);
    endif
    
    if B1 == 1 && B2 == 1
      B3 = bernoulli(0.6);
    elseif B1 == 0 && B2 == 1
      B3 = bernoulli(0.2);
    elseif B1 == 1 && B2 == 0
      B3 = bernoulli(0.9);
    else
      B3 = bernoulli(0.4);
    endif
    
    if B3 == 1
      B4 = bernoulli(0.3);
      B5 = bernoulli(0.5);
    else
      B4 = bernoulli(0.5);
      B5 = bernoulli(0.8);
    endif
      
    if B5 == 1 && B4 == 1
      B6 = bernoulli(0.5);
    elseif B5 == 1 && B4 == 0
      B6 = bernoulli(0.3);
    elseif B5 == 0 && B4 == 1
      B6 = bernoulli(0.8);
    else
      B6 = bernoulli(0.5);
    endif
    N(i) = bin2dec(num2str([B6, B5, B4, B3, B2, B1]));
 endfor
  
  bar(0:64, histc(N, 0:64) / n);
  grid on; set(gca, 'XLim', [0 64], 'XTick', 0:2:64);
endfunction
