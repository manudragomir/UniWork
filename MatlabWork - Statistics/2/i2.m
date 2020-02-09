#lala


function out=i2()
    cntI = 0;
    cntII = 0;
    cntIII = 0;
    
    for i = 1:2000
      x = randsample('RRRRRAAAVV', 3, false);
      ok1 = 0;
      ok2 = 0;
      
      if x(1) == x(2) && x(2) == x(3)
        ok2 = 1;%cand au toate aceeasi culoare
      endif
      
      if x(1) == 'R' || x(2) == 'R' || x(3) == 'R'
        cntI = cntI + 1;%cand cel putin una e rosie
        ok1 = 1;
      endif
      
      if ok1 == 1 && ok2 == 1
        cntII = cntII + 1;
      endif
      
    endfor
    outI = cntI / 2000;
    outII = (cntII) / 2000;
    out = outII % Raspuns la B
  %  out = outII / outI;% Raspuns la C
  %  out = cntII / cntI; % raspuns la D
endfunction