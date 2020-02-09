function pb1(n)
  clf; hold on;
  x = ivtdiscret([-1 2 3], [4/6 1/6 1/6], n); %media teoretica -1 * 4/6 + 2 * 4/6 +...
  count=histc(x,[-1 2 3]); 
  bar([-1 2 3],count/n,0.9,'FaceColor','b');
  bar([-1 2 3], [4/6 1/6 1/6], 'FaceColor', 'y');
  media_simulari = mean(x);
  media_teoretica = (3+2-4)/6;
endfunction

