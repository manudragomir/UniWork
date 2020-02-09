#lala
function out=ex2subi(n)
    countIn = 0;
    countTotal = n;
    for j = 1:n
      Xa = rand;
      Ya = rand;
      pair = [0.5, 0.5; Xa, Ya];
      dist = pdist(pair, 'euclidean');
      if dist <= 0.5 
        countIn++;
      endif
    endfor
    out = countIn / countTotal;
endfunction

