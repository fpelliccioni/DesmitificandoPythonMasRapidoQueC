import random

arch = open("src_realbig.txt", "w")
num30 = int("9"*30)
for i in range(1000000):
    a = random.randint(-num30, num30)
    b = random.randint(-num30, num30)
    arch.write("%32d %32d\n" % (a,b))
arch.close()
