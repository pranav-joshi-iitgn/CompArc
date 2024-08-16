s = open("Q2O.txt",'r').read()
S = s.split("\n\n")
S = S[1:]
I = []
D = []
for i,s in enumerate(S):
    if s != "Doubles":
        I.append(s)
    else:
        D = S[i+1:]
        break

"""
N = 64
cpu	1621021e-9 s
real	0m0.003s
user	0m0.003s
sys	0m0.001s
"""

def pad(s):
    if len(s) > 8: return s
    else: return s + " "*(8-len(s))


def extract(s):
    lines = s.split("\n")

    N = lines[0][4:]
    #N = int(N)

    cpu_time = lines[1].split("\t")[1].split(" ")[0]
    #if len(cpu_time.split("e")) > 1:
    #    cpu_time,order = cpu_time.split("e")
    #    cpu_time = int(cpu_time)
    #    order = int(order)
    #    cpu_time = cpu_time * 10**order #s

    exec_time = lines[2].split("\t")[1]
    exec_time = exec_time[2:-1]

    #exec_time = float(exec_time) #s 

    user_time = lines[3].split("\t")[1]
    user_time = user_time[2:-1] 
    #user_time = float(user_time) #s

    sys_time = lines[4].split("\t")[1]
    sys_time = sys_time[2:-1] 
    #sys_time = float(sys_time) #s

    data = [N,cpu_time,exec_time,user_time,sys_time]
    data = [pad(x) for x in data]
    return data

#for s in I:
#    print(s,"\n")

I = [extract(s) for s in I]
D = [extract(s) for s in D]

to_print = ""
to_print+= "\n" + ("int data-type")
to_print+= "\n" + ("|N       \t|cpu_time\t|exec_time\t|user_time\t|sys_time|")
to_print+= "\n" + ("|--------\t|--------\t|---------\t|---------\t|--------|")
for s in I:
    to_print+= "\n" + ("|"+"\t|".join(s)+"|")

to_print+= "\n" + ("\ndouble data-type")
to_print+= "\n" + ("|N       \t|cpu_time\t|exec_time\t|user_time\t|sys_time|")
to_print+= "\n" + ("|--------\t|--------\t|---------\t|---------\t|--------|")
for s in D:
    to_print+= "\n" + ("|"+"\t|".join(s)+"|")
    
file = open("extracted.md",'w')
file.write(to_print)
file.close()
