#lala
function out=ex2subii(n)
    countIn = 0;
    countTotal = n;
    for j = 1:n
      Xa = rand;
      Ya = rand;
      pair1 = [0.5, 0.5; Xa, Ya];
      dist1 = pdist(pair1, 'euclidean');
      
      pair2 = [0, 0; Xa, Ya];
      dist2 = pdist(pair2, 'euclidean');
      
      pair3 = [0, 1; Xa, Ya];
      dist3 = pdist(pair3, 'euclidean');
      
      pair4 = [1, 0; Xa, Ya];
      dist4 = pdist(pair4, 'euclidean');
      
      pair5 = [1, 1; Xa, Ya];
      dist5 = pdist(pair5, 'euclidean');
      
      if dist1 < dist2 && dist1 < dist3 && dist1 < dist4 && dist1 < dist5
           countIn = countIn + 1;  
      endif
    endfor
    out = countIn / countTotal;
endfunction