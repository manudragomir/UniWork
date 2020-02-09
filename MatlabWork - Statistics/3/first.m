#lala
function out = first(p,l,k)
   out = randsample([0 1],l*k,true,[1-p p]);
   out = reshape(out,l,k);
 endfunction
 
