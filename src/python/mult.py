import hrc
import random
import timeit  # http://stackoverflow.com/questions/85451/python-time-clock-vs-time-time-accuracy
import math
# import copy



# ----------------------------------------------------------------------------
# Algorithms
# ----------------------------------------------------------------------------


def mult1():
	a = 5
	b = 10
	c = a * b
	return c


def mult_big_vector_no_out_hot(data):


	# print("mult_big_vector_no_out_hot: ", len(data))

	f = 0
	l = len(data);
	m = f + int(l * 0.2);

	# print("f: ", f)
	# print("m: ", m)
	# print("l: ", l)


	# print("****************************************************************************************")


	while f != m:
		uno = data[f][0]
		dos = data[f][1]
		
		# data[f][0] = uno * dos
		data[f] = [uno * dos, dos]

		f += 1
		# print("++f: ", f)
	

	t1 = hrc.nanoseconds_since_epoch()

	while m != l: 
		uno = data[m][0]
		dos = data[m][1]
		# data[m][0] = uno * dos
		data[m] = [uno * dos, dos]


		# print("uno:        ", uno)
		# print("uno:        ", dos)
		# print("uno * dos:  ", (uno * dos))
		# print("data[m][0]: ", data[m][0])


		# ++m;
		m += 1;

	t2 = hrc.nanoseconds_since_epoch()

	# print("start: ", t1)
	# print("end:   ", t2)
	# print("diff:  ", t2 - t1)

	return t2 - t1



# ----------------------------------------------------------------------------
# Measurement tools
# ----------------------------------------------------------------------------

def createRandomIntList(max_data):
    res = []

    # for i in xrange(0, max_data):
    for i in range(0, max_data):
        n = random.randint(0, max_data)
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


def createRandomPairIntList_Bits_Signed(bits, max_data):

	int_from = -(2**bits//2)
	int_to = 2**bits//2-1

	# print(int_from)
	# print(int_to)

	return createRandomPairIntList(int_from, int_to, max_data)


def createRandomPairIntList_Bits_Unsigned(bits, max_data):

	int_from = 0
	int_to = 2**bits

	print(int_from)
	print(int_to)

	return createRandomPairIntList(int_from, int_to, max_data)


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


def measure_v2(data, numTrials, setUp, test): 

	numConcreteTrials = int(numTrials * 0.8)
	trials = []
	data_copy = list(data)

	for i in range(0, int(numTrials * 0.2)):
		setUp()
		data = list(data_copy)
		test(data)

	for i in range(0, numConcreteTrials):
		setUp()
		data = list(data_copy)
		ns = test(data)
		trials.append(ns)
		# print("ns: ", ns)

	

	ssd = sample_std_dev(trials)

	# //cout << "sample standard deviation " << ssd << endl;
	# //cout << "trials.size() " << trials.size() << endl;
	# //cout << "numConcreteTrials " << numConcreteTrials << endl;

	# mean = accumulate(trials, 0.0) / numConcreteTrials
	m = mean(trials)


	 # mean-median test
	trials.sort()
	median = trials[numConcreteTrials // 2];
	# mmtest = abs(m - median) / max(m, median);
	# print("mean: ", m, " - median: ", median, " - mean-median test: ", mmtest)

	return [m, ssd, median];




def measure_and_print_mult_big_vector_no_out_hot(data):

	p = measure_v2( data,
					1000,
					lambda: None,
					lambda x: mult_big_vector_no_out_hot(x)
					)

	print("mult_big_vector_no_out_hot             ;", len(data), ";", p[0], ";", p[1], ";", p[2])


def run_mearurements(bits, min_size, max_size):

	array_size = min_size

	while array_size <= max_size:

		data = createRandomPairIntList_Bits_Signed(bits, array_size)
		# data2 = copy_convert_vector(data1);

		# //measure_and_print_mult_big_vector_do_nothing_hot(data2);
		# measure_and_print_mult_big_vector_hot<IntMax>(data2);
		# measure_and_print_mult_big_vector_no_out_hot(data1);

		measure_and_print_mult_big_vector_no_out_hot(data)

		print("-------------------------")

		array_size *= 2
	



def test_random_creator():

	signed_32_bit = createRandomPairIntList_Bits_Signed(32, 255)

	for x in signed_32_bit:
		print(x[0], x[1])


# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------


def main():

	# x = int(1000 * 0.8)
	# print(x)

	# test_random_creator()


	# min_size = 8;
	min_size = 16 * 1024
	max_size = 8 * 1024 * 1024;
	# max_size = 16 * 1024 * 1024;
	bits = 32	


	run_mearurements(bits, min_size, max_size)


	# ----------------------------------------
	# a = hrc.nanoseconds_since_epoch()
	# b = hrc.nanoseconds_since_epoch()
	# print(a)
	# print(b)
	# print(b - a)




# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------

if __name__ == "__main__":
  main()





