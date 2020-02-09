function pb2(n)
  %i
  clf; hold on;
  X = normrnd(165, 10, 1, n); % m si sigma^2
  wbin = (max(X)-min(X))/10; 
  bins = min(X):wbin:max(X);
  count = histc(X,bins); 
  bar(bins,count/(n*wbin),'histc');
  f=@(x)normpdf(x,165,10); fplot(f, [min(X), max(X)], 'r');
  %ii
  media_simulari = mean(X); %media_teoretica = 165
  proportia_simulari = mean(160<=X & X<=170)
  proportia_teoretica = normcdf(170,160,10) - normcdf(160,165,10)
endfunction
