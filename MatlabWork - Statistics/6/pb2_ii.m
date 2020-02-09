function pb2_ii(n)
g=@(x) abs(sin(exp(x)));
int_g_1=MC1(g,-1,3,n)
int_g_2=MC2(g,-1,3,n)
int_g_3=integral(g,-1,3)
