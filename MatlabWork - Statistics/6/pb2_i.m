function pb2_i(n)
g=@(x) exp(-x.^2);
int_g_1=MC1(g,-2,2,n)
int_g_2=MC2(g,-2,2,n)
int_g_3=integral(g,-2,2)
