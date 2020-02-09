#lala
function out=ex2subiii(n)
    countIn = 0;
    countTotal = n;
    for j = 1:n
     Xa = rand;
     Ya = rand;
     
     pair2 = [0, 0; Xa, Ya];
     OA = pdist(pair2, 'euclidean');
     
     pair3 = [0, 1; Xa, Ya];
     OB = pdist(pair3, 'euclidean');
     
     pair4 = [1, 1; Xa, Ya];
     OC = pdist(pair4, 'euclidean');
     
     pair5 = [1, 0; Xa, Ya];
     OD = pdist(pair5, 'euclidean');
     
     obtuze = 0;
      
     if(OA*OA + OB*OB < 1)
      obtuze++;
     endif
    
     if(OB*OB + OC*OC < 1)
      obtuze++;
     endif
    
     if(OC*OC + OD*OD < 1)
      obtuze++;
     endif
    
     if(OD*OD + OA*OA < 1)
      obtuze++;
      endif
     
     if obtuze == 2
      countIn++;
     endif 
    endfor
    out = countIn / countTotal;
endfunction