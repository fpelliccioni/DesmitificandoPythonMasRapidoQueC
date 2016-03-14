import hrc
import random
# import timeit  # http://stackoverflow.com/questions/85451/python-time-clock-vs-time-time-accuracy
import math
# import copy
import datetime
import sys


# class triangle:
#     def __init__(self, a, b):
#         self.a = a
#         self.b = b

#     def __lt__(self, other):
#         h1 = math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2))
#         h2 = math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2))
#         return h1 < h2

#     def __del__(self):
#         print("triangle __del__: " + a)


class singleton:
    def __init__(self, a):
        self.a = a

    def __lt__(self, other):
        return self.a < other.a

    def __del__(self):
        print("destructing " + repr(self))
        # print("singleton __del__: " + a)

    def __repr__(self):
        return "singleton(%d)" % (self.a,)

    # def __str__(self):
    #     return "singleton(%d)" % (self.a,)

    def __neg__(self):
        return singleton(-self.a)

def min_signed_int(bits):
    return -(2**bits//2)

def max_signed_int(bits):
    return 2**bits//2-1

def min_unsigned_int(bits):
    return 0

def max_unsigned_int(bits):
    return 2**bits

def createList(int_from, int_to, max_data):
    res = [None] * max_data

    for i in range(max_data):
        a = random.randint(int_from, int_to)
        c = singleton(a)
        res[i] = c
    return res


def return_null(x):
    # raise Exception('...')
    # return x
    # return -x
    # if x == 8:
    #     return -1
    # else:
    #     return x
    if x.a == 7:
        raise Exception('...')
    else:
        return x

def main():
        bits = 32
        int_from = min_signed_int(bits)
        int_to   = max_signed_int(bits)

        sswo = hrc.size_of_sortwrapperobject()
        print("size_of_sortwrapperobject: " + str(sswo))

        # # print("NULL...:")
        # x = hrc.return_null()
        # print(x)
        # # print(hrc.return_null())

        # l = createList(int_from, int_to, 8)
        l = [singleton(1), singleton(2), singleton(3), singleton(4), singleton(5), singleton(6), singleton(7), singleton(8)]
        print(l)

        # s1 = sorted(l, key=lambda x: (x,)) 
        # print(s1)

        # s2 = sorted(l, key=lambda x: None) 
        # print(s2)

        s3 = sorted(l, key=lambda x: return_null(x)) 
        print(s3)
  
# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------

if __name__ == "__main__":
  main()
