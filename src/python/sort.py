# Python 2
#     py -2 sort.py
# Python 3
#    py -3 sort.py



import hrc
import random
# import timeit  # http://stackoverflow.com/questions/85451/python-time-clock-vs-time-time-accuracy
import math
# import copy
import datetime
import sys


# ----------------------------------------------------------------------------
# Algorithms
# ----------------------------------------------------------------------------

# s is a sequence
# r is a Weak Ordering relation on Domain(S)
# in-place sort?
# stable?
# def fer_sort(s, r):



class entity:
  def __init__(self, a, b, c, d, e):
    self.a = a
    self.b = b
    self.c = c
    self.d = d
    self.e = e


class triangle:
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def __lt__(self, other):
        h1 = math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2))
        h2 = math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2))
        # h1 = math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2))
        # h2 = math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2))
        # h1 = math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2))
        # h2 = math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2))
        # h1 = math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2))
        # h2 = math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2))
        # h1 = math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2))
        # h2 = math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2))
        # h1 = math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2)) + math.sqrt(math.pow(self.a, 2)  + math.pow(self.b, 2))
        # h2 = math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2)) + math.sqrt(math.pow(other.a, 2) + math.pow(other.b, 2))
        return h1 < h2

class extra:
    def __init__(self, t):
        self.t = t

    def __lt__(self, other):
        # print("extra less than self: " + str(id(self)) + " - other: " + str(id(other)))
        return self.t < other.t


def extra_fo_comp(a, b):
    if a < b: return -1
    if a > b: return 1
    return 0

def compare(a, b, comp):
    return comp(a, b)

class extra_fo:
    def __init__(self, t, comp):
        self.t = t
        self.comp = comp

    def __lt__(self, other):
        return compare(self.t, other.t, self.comp) < 0



class container:
    def __init__(self, t):
        self.t = t

    # def __repr__(self):
    #     #Hay alguna forma mejor de hacer esto?
    #     return "ClassB(%d, ClassA(%d))" % (self.x, self.y.x)
    # def __str__(self):
    #     return "member of ClassB"        



  # def __repr__(self):
  #   return "Employee { i:%s n:%s s:%s }" % (self.i, self.n, self.s)


# ----------------------------------------------------------------------------
# Test
# ----------------------------------------------------------------------------

def sort_just_sort(data):
    # print(data[0])
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

def sort_with_key_1(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, key=lambda x: (x,)) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

def sort_with_key_2(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, key=lambda x: (x & 0b00000000000000001111111111111111, x & 0b11111111111111110000000000000000)) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

# Cuando no se puede usar un key porque la Relation es muy compleja. La solucion recomendada es:
def sort_with_key_3(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata  = sorted(data,  key=lambda x: (x & 0b00000000000000001111111111111111,)) 
    ssdata = sorted(sdata, key=lambda x: (x & 0b11111111111111110000000000000000,)) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

def sort_with_key_4(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata  = sorted(data,  key=lambda x: (x & 0b00000000000000001111111111111111,)) 
    sdata.sort(key=lambda x: (x & 0b11111111111111110000000000000000,)) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

def sort_with_key_5(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data,  key=lambda x: (x & 0b00000000000000001111111111111111,)) 
    sdata = sorted(sdata, key=lambda x: (x & 0b11111111111111110000000000000000,)) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

#
def sort_with_key_6(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data,  key=lambda x: (x & 0b00000000111111111111111100000000,))
    sdata = sorted(sdata, key=lambda x: (x & 0b00000000000000000000000011111111,))
    sdata = sorted(sdata, key=lambda x: (x & 0b11111111000000000000000000000000,))
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1


# def precedencia(a, b):
#     nombre1, valor1 = a
#     nombre2, valor2 = b

#     if valor1 == valor2:
#         if nombre1 < nombre2:
#             return -1
#         return 1

#     if valor1 > valor2:
#         return -1
#     return 1

def weak_ordering_cmp_1(a, b):
    # nombre1, valor1 = a
    # nombre2, valor2 = b

    if a < b:
        return -1
    else:
        if a > b:
            return 1
        else:
            return 0

def sort_with_cmp_1(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_cmp_1)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1


def weak_ordering_cmp_1_b(a, b):
    return cmp(a, b)

def sort_with_cmp_1_b(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_cmp_1_b)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1


def weak_ordering_cmp_2(a, b):
    a1 = a & 0b00000000000000001111111111111111
    b1 = b & 0b00000000000000001111111111111111

    if a1 < b1:
        return -1
    else:
        if a1 > b1:
            return 1
        else:
            a2 = a & 0b11111111111111110000000000000000
            b2 = b & 0b11111111111111110000000000000000

            if a2 < b2:
                return -1
            else:
                if a2 > b2:
                    return 1
                else:
                    return 0

def sort_with_cmp_2(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_cmp_2)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1


def weak_ordering_cmp_2_b(a, b):
    a1 = a & 0b00000000000000001111111111111111
    b1 = b & 0b00000000000000001111111111111111

    if a1 < b1:
        return -1
    else:
        if a1 > b1:
            return 1
        else:
            a2 = a & 0b11111111111111110000000000000000
            b2 = b & 0b11111111111111110000000000000000
            return cmp(a2, b2)

def sort_with_cmp_2_b(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_cmp_2_b)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1




def weak_ordering_cmp_3(a, b):
    a1 = a & 0b00000000111111111111111100000000
    b1 = b & 0b00000000111111111111111100000000

    if a1 < b1:
        return -1
    else:
        if a1 > b1:
            return 1
        else:
            a2 = a & 0b00000000000000000000000011111111
            b2 = b & 0b00000000000000000000000011111111

            if a2 < b2:
                return -1
            else:
                if a2 > b2:
                    return 1
                else:
                    a3 = a & 0b11111111000000000000000000000000
                    b3 = b & 0b11111111000000000000000000000000

                    if a3 < b3:
                        return -1
                    else:
                        if a3 > b3:
                            return 1
                        else:
                            return 0

def sort_with_cmp_3(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_cmp_3)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1




def weak_ordering_cmp_4(a, b):
    ax = a & 0b00000000111111111111111100000000
    bx = b & 0b00000000111111111111111100000000

    if ax < bx:
        return -1
    else:
        if ax > bx:
            return 1
        else:
            ax = a & 0b00000000000000000000000011111111
            bx = b & 0b00000000000000000000000011111111

            if ax < bx:
                return -1
            else:
                if ax > bx:
                    return 1
                else:
                    ax = a & 0b11111111000000000000000000000000
                    bx = b & 0b11111111000000000000000000000000

                    if ax < bx:
                        return -1
                    else:
                        if ax > bx:
                            return 1
                        else:
                            return 0

def sort_with_cmp_4(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_cmp_4)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1



def sort_entity_key_1(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata  = sorted(data,  key=lambda x: x.a) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

def sort_entity_key_2(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata  = sorted(data,  key=lambda x: x.a) 
    sdata  = sorted(sdata, key=lambda x: x.b) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

def sort_entity_key_3(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata  = sorted(data,  key=lambda x: x.a) 
    sdata  = sorted(sdata, key=lambda x: x.b) 
    sdata  = sorted(sdata, key=lambda x: x.c) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

def sort_entity_key_4(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata  = sorted(data,  key=lambda x: x.a) 
    sdata  = sorted(sdata, key=lambda x: x.b) 
    sdata  = sorted(sdata, key=lambda x: x.c) 
    sdata  = sorted(sdata, key=lambda x: x.d) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

def sort_entity_key_5(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata  = sorted(data,  key=lambda x: x.a) 
    sdata  = sorted(sdata, key=lambda x: x.b) 
    sdata  = sorted(sdata, key=lambda x: x.c) 
    sdata  = sorted(sdata, key=lambda x: x.d) 
    sdata  = sorted(sdata, key=lambda x: x.e) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1


def weak_ordering_entity_cmp_1(a, b):
    if a.a < b.a:
        return -1
    else:
        if a.a > b.a:
            return 1
        else:
            return 0

def weak_ordering_entity_cmp_2(a, b):
    if a.a < b.a:
        return -1
    else:
        if a.a > b.a:
            return 1
        else:
            if a.b < b.b:
                return -1
            else:
                if a.b > b.b:
                    return 1
                else:
                    return 0

def weak_ordering_entity_cmp_3(a, b):
    if a.a < b.a:
        return -1
    else:
        if a.a > b.a:
            return 1
        else:
            if a.b < b.b:
                return -1
            else:
                if a.b > b.b:
                    return 1
                else:
                    if a.c < b.c:
                        return -1
                    else:
                        if a.c > b.c:
                            return 1
                        else:
                            return 0

def weak_ordering_entity_cmp_4(a, b):
    if a.a < b.a:
        return -1
    else:
        if a.a > b.a:
            return 1
        else:
            if a.b < b.b:
                return -1
            else:
                if a.b > b.b:
                    return 1
                else:
                    if a.c < b.c:
                        return -1
                    else:
                        if a.c > b.c:
                            return 1
                        else:
                            if a.d < b.d:
                                return -1
                            else:
                                if a.d > b.d:
                                    return 1
                                else:
                                    return 0

def weak_ordering_entity_cmp_5(a, b):
    if a.a < b.a:
        return -1
    else:
        if a.a > b.a:
            return 1
        else:
            if a.b < b.b:
                return -1
            else:
                if a.b > b.b:
                    return 1
                else:
                    if a.c < b.c:
                        return -1
                    else:
                        if a.c > b.c:
                            return 1
                        else:
                            if a.d < b.d:
                                return -1
                            else:
                                if a.d > b.d:
                                    return 1
                                else:
                                    if a.e < b.e:
                                        return -1
                                    else:
                                        if a.e > b.e:
                                            return 1
                                        else:
                                            return 0

def sort_entity_cmp_1(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_entity_cmp_1)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

def sort_entity_cmp_2(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_entity_cmp_2)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

def sort_entity_cmp_3(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_entity_cmp_3)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

def sort_entity_cmp_4(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_entity_cmp_4)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1

def sort_entity_cmp_5(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_entity_cmp_5)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1



def sort_container_key_1(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata  = sorted(data,  key=lambda x: x.t) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1


def extra_call_1(x):
    return extra_call_2(x)

def extra_call_2(x):
    return extra_call_3(x)

def extra_call_3(x):
    return x.t

def extra_call(x):
    return extra_call_1(x)

def sort_container_key_1_extra(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata  = sorted(data,  key=lambda x: extra_call(x)) 
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1


def weak_ordering_container_cmp_1(a, b):
    if a.t < b.t: return -1
    # if a.t < b.t: return 1
    if a.t > b.t: return 1
    return 0

def sort_container_cmp_1(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_container_cmp_1)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1



def weak_ordering_triangle_cmp_1(a, b):
    if a < b: return -1
    if a > b: return 1
    return 0

def sort_triangle_cmp_1(data):
    t1 = hrc.nanoseconds_since_epoch()
    sdata = sorted(data, cmp=weak_ordering_triangle_cmp_1)
    t2 = hrc.nanoseconds_since_epoch()
    return t2 - t1




# ----------------------------------------------------------------------------
# Measurement tools
# ----------------------------------------------------------------------------

import string
import random

def random_string_detail(size=6, chars=string.ascii_uppercase + string.ascii_lowercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))

def random_string(size_from, size_to):
    size = random.randint(size_from, size_to)
    return random_string_detail(size)



def createRandomEntityList(int_from, int_to, size_from, size_to, max_data):
    res = []

    # for i in xrange(0, max_data):
    for i in range(0, max_data):
        a = random_string(size_from, size_to)
        b = random.randint(int_from, int_to)
        c = random_string(size_from, size_to)
        d = random.randint(int_from, int_to)
        e = random_string(size_from, size_to)

        ent = entity(a, b, c, d, e)
        
        res.append(ent)

    return res

# def createRandomContainerList(int_from, int_to, max_data):
#     res = []

#     # for i in xrange(0, max_data):
#     for i in range(0, max_data):
#         a = random.randint(int_from, int_to)
#         b = random.randint(int_from, int_to)

#         c = container(triangle(a, b))
        
#         res.append(c)

#     return res

def createRandomContainerList(int_from, int_to, max_data):
    res = [None] * max_data

    for i in range(max_data):
        a = random.randint(int_from, int_to)
        b = random.randint(int_from, int_to)
        c = container(triangle(a, b))
        res[i] = c
    return res

def createRandomContainerExtraList(int_from, int_to, max_data):
    res = [None] * max_data

    for i in range(max_data):
        a = random.randint(int_from, int_to)
        b = random.randint(int_from, int_to)
        c = container(extra(triangle(a, b)))
        res[i] = c
    return res

def createRandomContainerExtraFOList(int_from, int_to, max_data):
    res = [None] * max_data

    for i in range(max_data):
        a = random.randint(int_from, int_to)
        b = random.randint(int_from, int_to)
        c = container(extra_fo(triangle(a, b), extra_fo_comp))
        res[i] = c
    return res



def createRandomTriangleList(int_from, int_to, max_data):
    res = [None] * max_data

    for i in range(max_data):
        a = random.randint(int_from, int_to)
        b = random.randint(int_from, int_to)
        c = triangle(a, b)
        res[i] = c
    return res

def createRandomStringList(size_from, size_to, max_data):
    res = []

    # for i in xrange(0, max_data):
    for i in range(0, max_data):
        s = random_string(size_from, size_to)
        res.append(s)

    return res


def createRandomIntList(int_from, int_to, max_data):
    res = []

    # for i in xrange(0, max_data):
    for i in range(0, max_data):
        # n = random.randint(0, max_data)
        n = random.randint(int_from, int_to)
        res.append(n)

    return res

def createRandomPairIntList(int_from, int_to, max_data):
    res = []

    # for i in xrange(0, max_data):
    for i in range(0, max_data):
        a = random.randint(int_from, int_to)
        b = random.randint(int_from, int_to)
        res.append((a, b))

    return res    


def min_signed_int(bits):
    return -(2**bits//2)

def max_signed_int(bits):
    return 2**bits//2-1

def min_unsigned_int(bits):
    return 0

def max_unsigned_int(bits):
    return 2**bits

def createRandomIntList_Bits_Signed(bits, max_data):
    int_from = min_signed_int(bits)
    int_to = max_signed_int(bits)

    return createRandomIntList(int_from, int_to, max_data)


def createRandomIntList_Bits_Unsigned(bits, max_data):
    int_from = min_unsigned_int(bits)
    int_to = max_unsigned_int(bits)

    return createRandomIntList(int_from, int_to, max_data)


def createRandomPairIntList_Bits_Signed(bits, max_data):
    int_from = min_signed_int(bits)
    int_to = max_signed_int(bits)

    # print(int_from)
    # print(int_to)

    return createRandomPairIntList(int_from, int_to, max_data)

def createRandomPairIntList_Bits_Unsigned(bits, max_data):

    int_from = min_unsigned_int(bits)
    int_to = max_unsigned_int(bits)

    # print(int_from)
    # print(int_to)

    return createRandomPairIntList(int_from, int_to, max_data)

def pairs_to_triples(list):
    res = []

    for x in list:
        res.append((x[0], x[1], None))

    return res   


def accumulate(data, init):
    res = init

    for x in data:
        res += x

    return res


def mean(data):
    sum = accumulate(data, 0.0)
    return sum / len(data)


def variance_helper(data):
    m = mean(data)
    s = 0

    for x in data:
        s += (x - m) * (x - m)

    return s


def sample_variance(data):
    s = variance_helper(data)
    return s / (len(data) - 1)


def sample_std_dev(data):
    s2 = sample_variance(data)
    return math.sqrt(s2)


def get_statistics(samples_list): 
    ssd = sample_std_dev(samples_list)

    # mean = accumulate(samples_list, 0.0) / concrete_samples
    m = mean(samples_list)


     # mean-median test
    samples_list.sort()
    median = samples_list[len(samples_list) // 2]
    # mmtest = abs(m - median) / max(m, median)
    # print("mean: ", m, " - median: ", median, " - mean-median test: ", mmtest)

    return [m, ssd, median]

def measure_nullary(samples, setUp, test): 

    concrete_samples = int(samples * 0.8)
    samples_list = []

    for i in range(0, int(samples * 0.2)):
        setUp()
        test()

    for i in range(0, concrete_samples):
        setUp()
        ns = test()
        samples_list.append(ns)
        # print("ns: ", ns)

    return get_statistics(samples_list)


def amortize(test, count):
    t1 = hrc.nanoseconds_since_epoch()
    for i in range(0, count):
        test()

    t2 = hrc.nanoseconds_since_epoch()
    ns = (t2 - t1) #/ count

    # print(ns)

    return ns / count


def measure_nullary_amortized(samples, amortize_count, test): 

    concrete_samples = int(samples * 0.8)
    samples_list = []

    for i in range(0, int(samples * 0.2)):
        amortize(test, amortize_count)

    for i in range(0, concrete_samples):
        ns = amortize(test, amortize_count)
        samples_list.append(ns)

    return get_statistics(samples_list)




# def measure_unary(data, samples, setUp, test): 

#     concrete_samples = int(samples * 0.8)
#     samples_list = []
#     data_copy = list(data)

#     for i in range(0, int(samples * 0.2)):
#         setUp()
#         data = list(data_copy)
#         test(data)

#     for i in range(0, concrete_samples):
#         setUp()
#         data = list(data_copy)
#         ns = test(data)
#         samples_list.append(ns)
#         # print("ns: ", ns)

#     return get_statistics(samples_list)


def measure_unary_immutable(data, samples, setUp, test): 

    concrete_samples = int(samples * 0.8)
    samples_list = []
    data_copy = list(data)

    for i in range(0, int(samples * 0.2)):
        setUp()
        data = list(data_copy)
        test(data)

    for i in range(0, concrete_samples):
        setUp()
        data = list(data_copy)
        ns = test(data)
        samples_list.append(ns)
        # print("ns: ", ns)

    return get_statistics(samples_list)




def clear_list(list): 

    f = 0
    l = len(list)

    while f != l:
        list[f] = None
        f += 1

def clear_list_max(list, bits): 

    f = 0
    l = len(list)

    while f != l:
        list[f] = max_signed_int(bits)
        f += 1

        

def clear_list_third(list): 

    f = 0
    l = len(list)

    while f != l:
        list[f] = (list[f][0], list[f][1], None)
        f += 1

def copy_list(source, target): 
    # precondition: len(source) = len(target)

    f = 0
    l = len(source)

    while f != l:
        target[f] = source[f]
        f += 1

# ------------------------------------------------------------------------

def measure_and_print_sort_just_sort(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_just_sort(x)
                    )
    print("sort_just_sort            ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_with_key_1(data):
    p = measure_unary_immutable( data,
                    10,
                    lambda: None,
                    lambda x: sort_with_key_1(x)
                    )
    print("sort_with_key_1           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_with_key_2(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_with_key_2(x)
                    )
    print("sort_with_key_2           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_with_key_3(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_with_key_3(x)
                    )
    print("sort_with_key_3           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_with_key_4(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_with_key_4(x)
                    )
    print("sort_with_key_4           ;", len(data), ";", p[0], ";", p[1], ";", p[2])


def measure_and_print_sort_with_key_5(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_with_key_5(x)
                    )
    print("sort_with_key_5           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_with_key_6(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_with_key_6(x)
                    )
    print("sort_with_key_6           ;", len(data), ";", p[0], ";", p[1], ";", p[2])





def measure_and_print_sort_with_cmp_1(data):

    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_with_cmp_1(x)
                    )

    print("sort_with_cmp_1           ;", len(data), ";", p[0], ";", p[1], ";", p[2])


def measure_and_print_sort_with_cmp_1_b(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_with_cmp_1_b(x)
                    )
    print("sort_with_cmp_1_b         ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_with_cmp_2(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_with_cmp_2(x)
                    )
    print("sort_with_cmp_2           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_with_cmp_2_b(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_with_cmp_2_b(x)
                    )
    print("sort_with_cmp_2_b         ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_with_cmp_3(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_with_cmp_3(x)
                    )
    print("sort_with_cmp_3           ;", len(data), ";", p[0], ";", p[1], ";", p[2])


def measure_and_print_sort_with_cmp_4(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_with_cmp_4(x)
                    )
    print("sort_with_cmp_4           ;", len(data), ";", p[0], ";", p[1], ";", p[2])


# ------------------------------------------------------------------------

def measure_and_print_sort_entity_key_1(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_entity_key_1(x)
                    )
    print("sort_entity_key_1           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_entity_key_2(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_entity_key_2(x)
                    )
    print("sort_entity_key_2           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_entity_key_3(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_entity_key_3(x)
                    )
    print("sort_entity_key_3           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_entity_key_4(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_entity_key_4(x)
                    )
    print("sort_entity_key_4           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_entity_key_5(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_entity_key_5(x)
                    )
    print("sort_entity_key_5           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_entity_cmp_1(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_entity_cmp_1(x)
                    )
    print("sort_entity_cmp_1           ;", len(data), ";", p[0], ";", p[1], ";", p[2])


def measure_and_print_sort_entity_cmp_2(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_entity_cmp_2(x)
                    )
    print("sort_entity_cmp_2           ;", len(data), ";", p[0], ";", p[1], ";", p[2])


def measure_and_print_sort_entity_cmp_3(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_entity_cmp_3(x)
                    )
    print("sort_entity_cmp_3           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_entity_cmp_4(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_entity_cmp_4(x)
                    )
    print("sort_entity_cmp_4           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_entity_cmp_5(data):
    p = measure_unary_immutable( data,
                    100,
                    lambda: None,
                    lambda x: sort_entity_cmp_5(x)
                    )
    print("sort_entity_cmp_5           ;", len(data), ";", p[0], ";", p[1], ";", p[2])


# ------------------------------------------------------------------------

def measure_and_print_sort_container_key_1(data):
    p = measure_unary_immutable( data,
                    10,
                    lambda: None,
                    lambda x: sort_container_key_1(x)
                    )
    print("sort_container_key_1           ;", len(data), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_sort_container_key_1_extra(data):
    p = measure_unary_immutable( data,
                    10,
                    lambda: None,
                    lambda x: sort_container_key_1_extra(x)
                    )
    print("sort_container_key_1_extra     ;", len(data), ";", p[0], ";", p[1], ";", p[2])





def measure_and_print_sort_container_cmp_1(data):
    p = measure_unary_immutable( data,
                    10,
                    lambda: None,
                    lambda x: sort_container_cmp_1(x)
                    )
    print("sort_container_cmp_1           ;", len(data), ";", p[0], ";", p[1], ";", p[2])


def measure_and_print_sort_triangle_cmp_1(data):
    p = measure_unary_immutable( data,
                    10,
                    lambda: None,
                    lambda x: sort_triangle_cmp_1(x)
                    )
    print("sort_triangle_cmp_1            ;", len(data), ";", p[0], ";", p[1], ";", p[2])



# ------------------------------------------------------------------------


def run_mearurements_0(bits, min_size, max_size):

# Python2
	# ('sort_with_key_1           ;', 2097152, ';', 6388001914.5, ';', 67147091.20603505, ';', 6389842449L)
# Python3
	# sort_with_key_1           ; 2097152 ;         4574730455.375 ; 42059891.491869636 ; 4588065977

    array_size = min_size

    while array_size <= max_size:

        data = createRandomIntList_Bits_Signed(bits, array_size)
        # print(data)
        print("data generated: ", array_size, " - time: ", datetime.datetime.now())

        # measure_and_print_sort_just_sort(data)              # falta medir 32: osx,         101: win32, osx
        measure_and_print_sort_with_key_1(data)                  # falta medir 32: osx,         101: win32, osx
        print("-------------------------")

        array_size *= 2
    
def run_mearurements_a(bits, min_size, max_size):

    array_size = min_size

    while array_size <= max_size:

        # data = createRandomPairIntList_Bits_Signed(bits, array_size)
        data = createRandomIntList_Bits_Signed(bits, array_size)
        # print(data)
        print("data generated: ", array_size, " - time: ", datetime.datetime.now())

        # measure_and_print_sort_just_sort(data)              # falta medir 32: osx,         101: win32, osx

        # measure_and_print_sort_with_key_1(data)                  # falta medir 32: osx,         101: win32, osx
        # measure_and_print_sort_with_key_2(data)                  # falta medir 32: osx,         101: win32, osx
        measure_and_print_sort_with_key_3(data)                  # falta medir 32: osx,         101: win32, osx
        # measure_and_print_sort_with_key_4(data)                  # falta medir 32: osx,         101: win32, osx
        # measure_and_print_sort_with_key_5(data)                  # falta medir 32: osx,         101: win32, osx
        measure_and_print_sort_with_key_6(data)                  # falta medir 32: osx,         101: win32, osx

        if (sys.version_info < (3, 0)):  # Python 2
            # measure_and_print_sort_with_cmp_1(data)                  # falta medir 32: osx,         101: win32, osx
            # measure_and_print_sort_with_cmp_1_b(data)                  # falta medir 32: osx,         101: win32, osx
            measure_and_print_sort_with_cmp_2(data)                  # falta medir 32: osx,         101: win32, osx
            # measure_and_print_sort_with_cmp_2_b(data)
            # measure_and_print_sort_with_cmp_3(data)                  # falta medir 32: osx,         101: win32, osx
            measure_and_print_sort_with_cmp_4(data)                  # falta medir 32: osx,         101: win32, osx
        else:
            print("sorted() with cmp is removed from Python3")

        print("-------------------------")

        array_size *= 2
    

def run_mearurements_b(bits, min_size, max_size):

    array_size = min_size
    str_size_from = 10
    str_size_to = 32
    int_from = min_signed_int(bits)
    int_to   = max_signed_int(bits)


    while array_size <= max_size:

        data = createRandomEntityList(int_from, int_to, str_size_from, str_size_to, array_size)
        # print(data)
        print("data generated: ", array_size, " - time: ", datetime.datetime.now())

        measure_and_print_sort_entity_key_1(data)
        measure_and_print_sort_entity_key_2(data)
        measure_and_print_sort_entity_key_3(data)
        measure_and_print_sort_entity_key_4(data)
        measure_and_print_sort_entity_key_5(data)

        if (sys.version_info < (3, 0)):  # Python 2
            measure_and_print_sort_entity_cmp_1(data)
            measure_and_print_sort_entity_cmp_2(data)
            measure_and_print_sort_entity_cmp_3(data)
            measure_and_print_sort_entity_cmp_4(data)
            measure_and_print_sort_entity_cmp_5(data)
        else:
            print("sorted() with cmp is removed from Python3")

        print("-------------------------")

        array_size *= 2
    


def run_mearurements_c(bits, min_size, max_size):

    array_size = min_size
    str_size_from = 10
    str_size_to = 32
    int_from = min_signed_int(bits)
    int_to   = max_signed_int(bits)


    while array_size <= max_size:

        # data1 = createRandomContainerList(int_from, int_to, array_size)
        data1 = createRandomTriangleList(int_from, int_to, array_size)
        # data2 = createRandomContainerExtraList(int_from, int_to, array_size)
        data2 = createRandomContainerExtraFOList(int_from, int_to, array_size)

        # print(data1)
        # print(data2)
        
        
        print("data generated: ", array_size, " - time: ", datetime.datetime.now())

        measure_and_print_sort_container_key_1(data2)
        # measure_and_print_sort_container_key_1_extra(data2)

        if (sys.version_info < (3, 0)):  # Python 2
            # measure_and_print_sort_container_cmp_1(data1)
            measure_and_print_sort_triangle_cmp_1(data1)
        else:
            print("sorted() with cmp is removed from Python3")

        print("-------------------------")

        array_size *= 2
    





# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------


def main():
    if (sys.version_info < (3, 0)):  # Python 2
	    print(hrc.size_of_pyobject_ptr())

    min_size = 8
    # min_size = 16 * 1024
    # min_size = 1 * 1024 * 1024
    # min_size = 2 * 1024 * 1024
    # min_size = 8 * 1024 * 1024
    max_size = 8
    # max_size = 8 * 1024 * 1024
    # max_size = 16 * 1024 * 1024

    bits = 32
    # bits = 101
    str_size_from = 10
    str_size_to = 32


    run_mearurements_0(bits, min_size, max_size)
    run_mearurements_a(bits, min_size, max_size)
    run_mearurements_b(bits, min_size, max_size)
    run_mearurements_c(bits, min_size, max_size)


    # bits = 32
    # int_from = min_signed_int(bits)
    # int_to = max_signed_int(bits)
    # number = random.randint(int_from, int_to)

    # # number = 14           #1110
    # print(number)
    # print(bin(number))

    # # n1 = number << 2
    # # n2 = number >> 2
    # n1 = number & 0b11111111111111110000000000000000
    # n2 = number & 0b00000000000000001111111111111111

    # print(n1)
    # print(bin(n1))
    # print(n2)
    # print(bin(n2))


# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------

if __name__ == "__main__":
  main()

