import hrc
import random
# import timeit  # http://stackoverflow.com/questions/85451/python-time-clock-vs-time-time-accuracy
import math
# import copy
import datetime


# ----------------------------------------------------------------------------
# Algorithms
# ----------------------------------------------------------------------------


def mult_original_1():
	a = 5
	b = 10
	c = a * b
	# return c

def mult_original_100():

	# print("mult_original_100")
	a = 5
	b = 10

	# for i in xrange(100000):
	for i in range(100000):
	    c = a * b




def mult_a(data):

	# print(data[0]);


	f = 0
	l = len(data);
	m = f + int(l * 0.2);

	while f != m:
		a = data[f][0]
		b = data[f][1]
		
		# data[f][0] = a * b
		data[f] = [a * b, b]

		f += 1

	t1 = hrc.nanoseconds_since_epoch()

	while m != l: 
		a = data[m][0]
		b = data[m][1]

		# data[m][0] = a * b
		data[m] = [a * b, b]

		m += 1;

	t2 = hrc.nanoseconds_since_epoch()
	return t2 - t1


def mult_b(input, output):

	f = 0
	l = len(input);
	m = f + int(l * 0.2);

	while f != m:
		a = input[f][0]
		b = input[f][1]
		
		# print(output[f]);

		output[f] = a * b

		f += 1

	t1 = hrc.nanoseconds_since_epoch()

	while m != l: 
		a = input[m][0]
		b = input[m][1]

		output[m] = a * b
		m += 1;

	t2 = hrc.nanoseconds_since_epoch()
	return t2 - t1

def mult_c(input_a, input_b, output):

	f = 0
	l = len(input_a);
	m = f + int(l * 0.2);

	while f != m:
		a = input_a[f]
		b = input_b[f]
		
		output[f] = a * b

		f += 1

	t1 = hrc.nanoseconds_since_epoch()

	while m != l: 
		a = input_a[m]
		b = input_b[m]

		output[m] = a * b
		m += 1;

	t2 = hrc.nanoseconds_since_epoch()
	return t2 - t1



def mult_d(data):

	f = 0
	l = len(data);
	m = f + int(l * 0.2);

	while f != m:
		a = data[f][0]
		b = data[f][1]
		
		# data[f][2] = a * b		# tuples are immutables in Python
		data[f] = [a, b, a * b]		# workaround

		f += 1

	# print("------------------------------------")

	t1 = hrc.nanoseconds_since_epoch()

	while m != l: 
		a = data[m][0]
		b = data[m][1]

		# data[m][2] = a * b			# tuples are immutables in Python
		data[m] = [a, b, a * b]		# workaround

		m += 1;

	t2 = hrc.nanoseconds_since_epoch()
	return t2 - t1


def mult_e(input_output, input):

	# print(input_output[0]);

	f = 0
	l = len(input);
	m = f + int(l * 0.2);

	while f != m:
		a = input_output[f]
		b = input[f]
		
		input_output[f] = a * b

		f += 1
	

	t1 = hrc.nanoseconds_since_epoch()

	while m != l: 
		a = input_output[m]
		b = input[m]

		input_output[m] = a * b
		m += 1;

	t2 = hrc.nanoseconds_since_epoch()
	return t2 - t1


def mult_f(input_a, input_b):

	f = 0
	l = len(input_a);
	m = f + int(l * 0.2);

	while f != m:
		a = input_a[f]
		b = input_b[f]
		prod = a * b

		# print("a:    ", a)
		# print("b:    ", b)
		# print("prod: ", prod)

		f += 1

	t1 = hrc.nanoseconds_since_epoch()

	while m != l: 
		a = input_a[m]
		b = input_b[m]
		prod = a * b
		m += 1;

	t2 = hrc.nanoseconds_since_epoch()
	return t2 - t1



# ----------------------------------------------------------------------------
# Measurement tools
# ----------------------------------------------------------------------------

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
	sum = accumulate(data, 0.0);
	return sum / len(data);


def variance_helper(data):
	m = mean(data)
	s = 0

	for x in data:
		s += (x - m) * (x - m);

	return s;


def sample_variance(data):
	s = variance_helper(data)
	return s / (len(data) - 1);


def sample_std_dev(data):
	s2 = sample_variance(data)
	return math.sqrt(s2)


def get_statistics(samples_list): 
	ssd = sample_std_dev(samples_list)

	# //cout << "sample standard deviation " << ssd << endl;
	# //cout << "samples_list.size() " << samples_list.size() << endl;
	# //cout << "concrete_samples " << concrete_samples << endl;

	# mean = accumulate(samples_list, 0.0) / concrete_samples
	m = mean(samples_list)


	 # mean-median test
	samples_list.sort()
	median = samples_list[len(samples_list) // 2];
	# mmtest = abs(m - median) / max(m, median);
	# print("mean: ", m, " - median: ", median, " - mean-median test: ", mmtest)

	return [m, ssd, median];

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




def measure_unary(data, samples, setUp, test): 

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
	l = len(list);

	while f != l:
		list[f] = None
		f += 1

def clear_list_max(list, bits): 

	f = 0
	l = len(list);

	while f != l:
		list[f] = max_signed_int(bits)
		f += 1

		

def clear_list_third(list): 

	f = 0
	l = len(list);

	while f != l:
		list[f] = (list[f][0], list[f][1], None)
		f += 1

def copy_list(source, target): 
	# precondition: len(source) = len(target)

	f = 0
	l = len(source);

	while f != l:
		target[f] = source[f]
		f += 1

# --------------------
	
def measure_and_print_mult_a(data):

	p = measure_unary( data,
					1000,
					lambda: None,
					lambda x: mult_a(x)
					)

	print("mult_a             ;", len(data), ";", p[0], ";", p[1], ";", p[2])


def measure_and_print_mult_a_with_copy(data):

	data_copy = data[:]

	p = measure_nullary(
					1000,
					lambda: copy_list(data_copy, data),
					lambda: mult_a(data)
					)

	print("mult_a_with_copy   ;", len(data), ";", p[0], ";", p[1], ";", p[2])



def measure_and_print_mult_b(data):

	output = len(data) * [None]

	p = measure_nullary(
					1000,
					lambda: clear_list(output),  #output[:] = [],
					lambda: mult_b(data, output)
					)

	print("mult_b             ;", len(data), ";", p[0], ";", p[1], ";", p[2])


# No hay mucha ganancia pre-seteando el array con elementos del tamaño en bits final.
# Se ve que CPython no aprovecha la memoria ya asignada (allocated)
# def measure_and_print_mult_b_variant(data, bits_min):

# 	MAX = max_signed_int(bits_min)

# 	# print("MAX: ", MAX)

# 	# output = len(data) * [None]
# 	output = len(data) * [MAX]


# 	# for x in output:
# 	#     print("x: ", x)



# 	p = measure_nullary(
# 					1000,
# 					lambda: clear_list_max(output, bits_min),  #output[:] = [],
# 					lambda: mult_b(data, output)
# 					)

# 	print("mult_bV            ;", len(data), ";", p[0], ";", p[1], ";", p[2])



def measure_and_print_mult_c(input_a, input_b):

	output = len(input_a) * [None]

	p = measure_nullary(
					1000,
					lambda: clear_list(output),
					lambda: mult_c(input_a, input_b, output)
					)

	print("mult_c             ;", len(input_a), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_mult_d(dataP):

	dataT = pairs_to_triples(dataP)

	p = measure_nullary(1000,
					lambda: clear_list_third(dataT),
					lambda: mult_d(dataT)
					)

	print("mult_d             ;", len(dataT), ";", p[0], ";", p[1], ";", p[2])

def measure_and_print_mult_e(input_output, input):

	input_output_copy = input_output[:]

	p = measure_nullary(1000,
					lambda: copy_list(input_output_copy, input_output),
					lambda: mult_e(input_output, input)
					)

	print("mult_e             ;", len(input_output), ";", p[0], ";", p[1], ";", p[2])


def measure_and_print_mult_f(input_a, input_b):

	p = measure_nullary(
					1000,
					lambda: None,
					lambda: mult_f(input_a, input_b)
					)

	print("mult_f             ;", len(input_a), ";", p[0], ";", p[1], ";", p[2])


def measure_and_print_mult_original_1():

	p = measure_nullary_amortized(
					10000,
					1000,
					lambda: mult_original_1()
					)

	print("mult_original_1            ;1000;1000;", p[0], ";", p[1], ";", p[2])

def measure_and_print_mult_original_100():

	p = measure_nullary_amortized(
					1000,
					1,
					lambda: mult_original_100()
					)

	print("mult_original_100          ;1000;1000;", p[0], ";", p[1], ";", p[2])



def run_mearurements_a(bits_min, bits_max, min_size, max_size):

	array_size = min_size

	while array_size <= max_size:

		data = createRandomPairIntList_Bits_Signed(bits_min, array_size)
		print("data generated: ", array_size, " - time: ", datetime.datetime.now())

		# data2 = copy_convert_vector(data1);

		# //measure_and_print_mult_big_vector_do_nothing_hot(data2);
		# measure_and_print_mult_big_vector_hot<IntMax>(data2);
		# measure_and_print_mult_a(data1);



		# measure_and_print_mult_a(data)              	# falta medir 32: osx,         101: win32, osx
		# measure_and_print_mult_a_with_copy(data)    	# falta medir 32: win32, osx   101: win32, osx


		# measure_and_print_mult_b(data)   # falta medir, osx
		# measure_and_print_mult_b_variant(data, bits_min)   # falta medir, osx

		measure_and_print_mult_d(data)   # falta medir , osx

		print("-------------------------")

		array_size *= 2
	


def run_mearurements_b(bits_min, bits_max, min_size, max_size):

	array_size = min_size

	while array_size <= max_size:

		input_a = createRandomIntList_Bits_Signed(bits_min, array_size)
		input_b = createRandomIntList_Bits_Signed(bits_min, array_size)

		measure_and_print_mult_c(input_a, input_b)     # falta medir 32: osx,         101: win32, osx
		# measure_and_print_mult_e(input_a, input_b)   # falta medir 32: osx,         101: win32, osx
		# measure_and_print_mult_f(input_a, input_b)     # falta medir 32: osx,         101: win32, osx


		print("-------------------------")

		array_size *= 2



def run_mearurements_c(bits):
	measure_and_print_mult_original_1()        # falta medir osx
	# measure_and_print_mult_original_100()        # falta medir osx




# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------


def main():
	# min_size = 8;
	min_size = 16 * 1024
	max_size = 8 * 1024 * 1024;
	# max_size = 16 * 1024 * 1024;

	# bits_min = 32
	# bits_max = 64?
	bits_min = 101
	bits_max = 201


	# (2^x/2)-1>10^digits-1			=
	# 	ceil(((d+1) log(2) + d log(5))/(log(2)))
	# (2^x/2)-1>10^30-1				= 		
	# 	ceil((31 log(2)+30 log(5))/(log(2)))



	run_mearurements_a(bits_min, bits_max, min_size, max_size)
	# run_mearurements_b(bits_min, bits_max, min_size, max_size)
	# run_mearurements_c(bits_min, bits_max)

# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------

if __name__ == "__main__":
  main()
