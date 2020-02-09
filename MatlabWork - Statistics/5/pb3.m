function pb3(n)
  x = zeros(n,2);
  for i = 1:n
    k = unidrnd(8); % discreta
    if k <= 2
      x(i, :) = [-1 -1];
    elseif k == 3
      x(i, :) = [-1 1];
    elseif k == 4
      x(i, :) = [-1 2];
    elseif k == 5
      x(i, :) = [1 -1];
    elseif k <= 7
      x(i, :) = [1 1];
    else
      x(i, :) = [1 2];
    endif
  endfor
  pr_sim = mean((x(:, 1) .* x(:, 2)) >= 1);
  %pr_teor = 2/8 + 2/8 + 1/8;
  medi_sim = mean(x(:, 1) .* x(:, 2));
  %medi_teor = -2*1/8 - 1*2/8 + 1*4/8 + 2*1/8
  
endfunction
