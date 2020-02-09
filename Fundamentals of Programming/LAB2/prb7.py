n = input("introdu un nr: ")
n = int(n)
f = []
f.append(0)
f.append(1)
k = 0
while f[k] <= n:
    f.insert(k+2, f[k+1] + f[k])
    k = k + 1
m = f[k]
print(m)
