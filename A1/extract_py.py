s = open("Q2O_py.txt",'r').read()
S = (s.split("\n\n"))[1:]
I,D = [],[]
for i,s in enumerate(S):
    if s != "Floats":I.append(s)
    else:
        D = S[i+1:]
        break
def pad(s):
    if len(s) > 13: return s
    else: return s + " "*(13-len(s))
def extract(s):
    lines = s.split("\n")
    N = lines[0][4:]
    cpu_time = lines[1].split(" ")[2]
    def simplify(time_measure):
        minutes,seconds = time_measure.split("m")
        minutes = int(minutes)
        seconds = float(seconds[:-1])
        return str(60*minutes + seconds)
    exec_time = simplify(lines[2].split("\t")[1])
    user_time = simplify(lines[3].split("\t")[1])
    sys_time = simplify(lines[4].split("\t")[1])
    data = [N,cpu_time,exec_time,user_time,sys_time]
    data = [pad(x) for x in data]
    return data
I = [extract(s) for s in I]
D = [extract(s) for s in D]
to_print = ""
to_print+= "\n" + ("int data-type")
to_print+= "\n" + ("|N            \t|cpu_time     \t|exec_time     \t|user_time     \t|sys_time     |")
to_print+= "\n" + ("|-------------\t|-------------\t|--------------\t|--------------\t|-------------|")
for s in I:to_print+= "\n" + ("|"+"\t|".join(s)+"|")
to_print+= "\n" + ("\ndouble data-type")
to_print+= "\n" + ("|N            \t|cpu_time     \t|exec_time     \t|user_time     \t|sys_time     |")
to_print+= "\n" + ("|-------------\t|-------------\t|--------------\t|--------------\t|-------------|")
for s in D:to_print+= "\n" + ("|"+"\t|".join(s)+"|")
file = open("extracted_py.md",'w')
file.write(to_print)
file.close()