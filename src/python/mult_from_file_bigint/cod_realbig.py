result = open("res_realbig.txt", "w")
for lin in open("src_realbig.txt"):
    a,b = map(int, lin.split())
    result.write("%d\n" % (a*b))
result.close()

