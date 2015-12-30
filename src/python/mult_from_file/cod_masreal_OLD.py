result = open("res_masreal.txt", "w")
for lin in file("src_masreal.txt"):
    a,b = map(int, lin.split())
    result.write("%d\n" % (a*b))
result.close()

