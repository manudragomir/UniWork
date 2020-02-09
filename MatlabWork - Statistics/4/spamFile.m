function out = spamFile()
  fileId = fopen('keywords_spam.txt', 'r');
  spamR = textscan(fileId, '%s');
  spam = spamR{1};
  fclose(fileId);
  
  fileId = fopen('keywords_ham.txt', 'r');
  hamR = textscan(fileId, '%s');
  ham = hamR{1};
  fclose(fileId);
  
  fileId = fopen('email.txt', 'r');
  email1R = textscan(fileId, '%s');
  email1 = email1R{1};
  fclose(fileId);
  
  fileId = fopen('email2.txt', 'r');
  email2 = textscan(fileId, '%s');
  fclose(fileId);
  
  words = unique([spam; ham])
  nrWords = numel(words);
  nrSpam = numel(spam);
  nrHam = numel(ham);
  pCspam = nrSpam / (nrSpam + nrHam);
  pCham = nrHam / (nrSpam + nrHam);
  for  i = 1:nrWords
    if ismember(words{i}, email1)
      pCspam = pCspam * sum(strcmp(words{i},spam)) / nrSpam;
      pCham = pCham * sum(strcmp(words{i},ham)) / nrHam;
    else
      pCspam = pCspam * ( 1 - sum(strcmp(words{i},spam)) / nrSpam);
      pCham = pCham * ( 1 - sum(strcmp(words{i},ham)) / nrHam);
    endif
  endfor
  
  if pCspam > pCham
    out = pCspam;
  else
    out = pCham;
  endif
endfunction
