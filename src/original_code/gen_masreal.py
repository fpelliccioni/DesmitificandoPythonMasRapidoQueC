import random

arch = open("src_masreal.txt", "w")
for i in range(1000000):
    a = random.randint(-1000,1000)
    b = random.randint(-1000,1000)
    arch.write("%5d %5d\n" % (a,b))
arch.close()
