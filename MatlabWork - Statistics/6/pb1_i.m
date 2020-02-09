function pb1_i(n)
X=normrnd(1,1,1,n);
Y=normrnd(3,1,1,n);
fprintf('V(X) estimat: %3.2f.\n',var(X,1));
fprintf('V(X) teoretic: 1.\n');
fprintf('V(Y) estimat: %3.2f.\n',var(Y,1));
fprintf('V(Y) teoretic: 1.\n');
fprintf('E(X*Y) estimat: %3.2f.\n',mean(X.*Y));
%E(XY)=E(X)E(Y)=3*1=3
fprintf('E(X*Y) teoretic: 3.\n');
R=corrcoef(X,Y); rho=R(1,2);
fprintf('rho(X,Y) estimat: %3.2f\n',abs(rho));
fprintf('rho(X,Y) teoretic: 0.\n');
fprintf('P(X<2,Y>1) estimat: %3.2f\n',mean(X<2&Y>1));
%P(X<2,Y>1)=P(X<=2)*(1-P(Y<=1))
fprintf('P(X<2,Y>1) teoretic: %3.2f\n',normcdf(2,1,1)*(1-normcdf(1,3,1)));