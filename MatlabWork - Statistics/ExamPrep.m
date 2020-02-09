function out = test()
    N = 1000;
    x = normrnd(1,2,1,N);
    out = mean(x > 0.5 & x < 1);
endfunction