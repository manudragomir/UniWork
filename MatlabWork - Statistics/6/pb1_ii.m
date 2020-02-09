function pb1_ii(n)
X=normrnd(1,1,1,n);
Y=3*X+1;
fprintf('V(X) estimat: %3.2f.\n',var(X,1));
fprintf('V(X) teoretic: 1.\n');
fprintf('V(Y) estimat: %3.2f.\n',var(Y,1));
%V(Y)=V(3X+1)=9V(X)
fprintf('V(Y) teoretic: 9.\n');
fprintf('E(X*Y) estimat: %3.2f.\n',mean(X.*Y));
%E(XY)=E(3X^2+1)=3E(X^2)+1=3(V(X)+E(X)^2)+1=3(1+1)+1=7
fprintf('E(X*Y) teoretic: 7.\n');
R=corrcoef(X,Y); rho=R(1,2);
fprintf('rho(X,Y) estimat: %3.2f\n',abs(rho));
fprintf('rho(X,Y) teoretic: 1.\n');
fprintf('P(X<2,Y>1) estimat: %3.2f\n',mean(X<2&Y>1));
%P(X<2,Y>1)=P(X<2,3X+1>1)=P(0<X<2)
fprintf('P(X<2,Y>1) teoretic: %3.2f\n',normcdf(2,1,1)-normcdf(0,1,1));