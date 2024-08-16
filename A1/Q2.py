from sys import stdin
from time import time_ns
datatype_size = stdin.read()
datatype_size = datatype_size.split()
datatype,n = datatype_size
n = int(n)
N = 2**n

if datatype == "int":
    M1 = [list(range(N)) for i in range(N)]
    M2 = [list(range(N)) for i in range(N)]
    M3 = [list(range(N)) for i in range(N)]
elif datatype == "float":
    M1 = [[j + 0.5 for j in range(N)] for i in range(N)]
    M2 = [[j + 0.5 for j in range(N)] for i in range(N)]
    M3 = [[j + 0.5 for j in range(N)] for i in range(N)]
else: raise ValueError("datatype (first argument) can only be 'int' or 'float'")

t0 = time_ns()
for i in range(N):
    for j in range(N):
        M3[i][j] = 0
        for k in range(N):
            M3[i][j] += M1[i][k] * M2[i][j]
t1 = time_ns()

print(f"\nN = {N}")
print(f"cpu_time = {t1-t0} ns",end="")