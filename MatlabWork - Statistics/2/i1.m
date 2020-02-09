#lala
function out=i1()
    cnt = 0;
    for i = 1:2000
      x = randsample('RRRRRAAAVV', 3, false);
      if x(1) == 'R' || x(2) == 'R' || x(3) == 'R'
        cnt = cnt + 1;
      endif
    endfor
    out = cnt / 2000;
endfunction