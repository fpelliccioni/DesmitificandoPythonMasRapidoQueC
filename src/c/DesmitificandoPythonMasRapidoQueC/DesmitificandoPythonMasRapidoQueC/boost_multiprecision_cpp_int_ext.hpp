#pragma once

#include <boost/multiprecision/cpp_int.hpp>

namespace boost {
namespace multiprecision {


		template <typename I>
		inline
			bool is_valid_dec(I f) {
			return *f >= '0' && *f <= '9';
		}

		template <typename I>
		inline
			bool try_parse_radix(I f, unsigned radix, limb_type& val) {
			if (*f >= '0' && *f <= '9')
				val = *f - '0';
			else if (*f >= 'a' && *f <= 'f')
				val = 10 + *f - 'a';
			else if (*f >= 'A' && *f <= 'F')
				val = 10 + *f - 'A';
			else
				return false;

			return val < radix;
		}

		template <typename Int, typename I>
		// requires: I models Random Access Iterator TODO: revisar si se puede con Bidirectional o Forward
		// Note: End of range:
		//               f == l or invalid char

		std::tuple<Int, I> make_from_bounded_range(I f, I l) {
			//precondition: [f, l) is a valid range...
			using default_ops::eval_multiply;
			using default_ops::eval_add;
			using base_type = Int::backend_type::base_type;

			Int res = static_cast<limb_type>(0u);
			unsigned radix = 10;
			bool isneg = false;

			if (f != l && *f == '-') {
				++f;
				isneg = true;
			}

			if (f != l && *f == '0') {
				I sf = f;
				++sf;

				if (sf != l && (*sf == 'x' || *sf == 'X')) {
					radix = 16;
					f += 2;
					//n -= 2;
				}
				else {
					radix = 8;
					++f;
					//n -= 1;
				}
			}

			//if (n) {
			if (f != l) {
				if (radix == 8 || radix == 16) {
					unsigned shift = radix == 8 ? 3 : 4;
					unsigned block_count = base_type::limb_bits / shift;

					unsigned block_shift = shift * block_count;
					limb_type val, block;

					while (f != l) {
						block = 0;

						unsigned i = 0;
						while (f != l && try_parse_radix(f, radix, val) && i < block_count) {
							block <<= shift;
							block |= val;
							++f;
							++i;
						}

						if (f == l || !try_parse_radix(f, radix, val)) {
							block_shift = (i + 1) * shift;
							eval_left_shift(res.backend(), block_shift);
							res.backend().limbs()[0] |= block;
							break;
						}


						eval_left_shift(res.backend(), block_shift);
						res.backend().limbs()[0] |= block;
					}
				}
				else {
					// Base 10, we extract blocks of size 10^9 at a time, that way
					// the number of multiplications is kept to a minimum:
					limb_type block_mult = max_block_10;

					while (f != l) {
						limb_type block = 0;

						unsigned i = 0;
						while (f != l && is_valid_dec(f) && i < digits_per_block_10) {
							limb_type val = *f - '0';
							block *= 10;
							block += val;
							++f;
							++i;
						}

						if (f == l || !is_valid_dec(f)) {
							block_mult = block_multiplier(i - 1);
							eval_multiply(res.backend(), block_mult);
							eval_add(res.backend(), block);
							break;
						}

						eval_multiply(res.backend(), block_mult);
						eval_add(res.backend(), block);
					}
				}
			}

			if (isneg) {
				res.backend().negate();
			}

			return std::make_tuple(res, f);
		}


		template <typename Int, typename I>
		// requires: I models Random Access Iterator
		std::tuple<Int, I, std::size_t> make_from_counted_range(I f, std::size_t n) {
			//std::tuple<Int, I, DistanceType(I)> make_from_counted_range(I f, DistanceType(I) n) {

			//precondition: [f, n) is a valid range...

			using default_ops::eval_multiply;
			using default_ops::eval_add;
			using base_type = Int::backend_type::base_type;

			Int res = static_cast<limb_type>(0u);
			unsigned radix = 10;
			bool isneg = false;

			if (n && (*f == '-')) {
				--n;
				++f;
				isneg = true;
			}

			if (n && (*f == '0')) {
				if ((n > 1) && ((f[1] == 'x') || (f[1] == 'X'))) {
					radix = 16;
					f += 2;
					n -= 2;
				}
				else {
					radix = 8;
					++f;
					--n;
					//n -= 1;
				}
			}

			if (n) {
				if (radix == 8 || radix == 16) {
					unsigned shift = radix == 8 ? 3 : 4;
					unsigned block_count = base_type::limb_bits / shift;

					unsigned block_shift = shift * block_count;
					limb_type val, block;

					while (n != 0) {
						block = 0;
						//for (unsigned i = 0; (i < block_count); ++i) {
						//	if (*f >= '0' && *f <= '9')
						//		val = *f - '0';
						//	else if (*f >= 'a' && *f <= 'f')
						//		val = 10 + *f - 'a';
						//	else if (*f >= 'A' && *f <= 'F')
						//		val = 10 + *f - 'A';
						//	else
						//		val = base_type::max_limb_value;
						//	if (val >= radix) {
						//		BOOST_THROW_EXCEPTION(std::runtime_error("Unexpected content found while parsing character string."));
						//	}
						//	block <<= shift;
						//	block |= val;

						//	++f;
						//	if (--n == 0) {
						//		// final shift is different:
						//		block_shift = (i + 1) * shift;
						//		break;
						//	}
						//}


						unsigned i = 0;
						while (n != 0 && try_parse_radix(f, radix, val) && i < block_count) {
							block <<= shift;
							block |= val;
							++f;
							++i;
						}

						if (n == 0 || !try_parse_radix(f, radix, val)) {
							block_shift = (i + 1) * shift;
							eval_left_shift(res.backend(), block_shift);
							res.backend().limbs()[0] |= block;
							break;
						}

						eval_left_shift(res.backend(), block_shift);
						res.backend().limbs()[0] |= block;
					}
				}
				else
				{
					// Base 10, we extract blocks of size 10^9 at a time, that way
					// the number of multiplications is kept to a minimum:
					limb_type block_mult = max_block_10;

					while (n != 0) {
						limb_type block = 0;

						unsigned i = 0;
						while (n != 0 && is_valid_dec(f) && i < digits_per_block_10) {
							limb_type val = *f - '0';
							block *= 10;
							block += val;
							++f;
							++i;
						}

						if (n == 0 || !is_valid_dec(f)) {
							//if (i - 1 >= 9) {
							//	break;
							//}

							block_mult = block_multiplier(i - 1);
							eval_multiply(res.backend(), block_mult);
							eval_add(res.backend(), block);
							break;
						}

						eval_multiply(res.backend(), block_mult);
						eval_add(res.backend(), block);
					}
				}
			}

			if (isneg) {
				res.backend().negate();
			}

			//return res;
			return std::make_tuple(res, f, n);
		}


		template <typename Int, typename I>
		// requires: I models Random Access Iterator
		std::tuple<Int, I, std::size_t> make_from_counted_range_dec(I f, std::size_t n) {
			//std::tuple<Int, I, DistanceType(I)> make_from_counted_range_dec(I f, DistanceType(I) n) {

			//precondition: [f, n) is a valid range...

			using default_ops::eval_multiply;
			using default_ops::eval_add;
			using base_type = Int::backend_type::base_type;

			Int res = static_cast<limb_type>(0u);
			bool isneg = false;

			if (n && *f == '-') {
				--n;
				++f;
				isneg = true;
			}

			// Base 10, we extract blocks of size 10^9 at a time, that way
			// the number of multiplications is kept to a minimum:
			limb_type block_mult = max_block_10;

			while (n != 0) {
				limb_type block = 0;

				unsigned i = 0;
				while (n != 0 && is_valid_dec(f) && i < digits_per_block_10) {
					limb_type val = *f - '0';
					block *= 10;
					block += val;
					++f;
					++i;
				}

				if (n == 0 || !is_valid_dec(f)) {
					block_mult = block_multiplier(i - 1);
					eval_multiply(res.backend(), block_mult);
					eval_add(res.backend(), block);
					break;
				}

				eval_multiply(res.backend(), block_mult);
				eval_add(res.backend(), block);
			}

			if (isneg) {
				res.backend().negate();
			}

			return std::make_tuple(res, f, n);
		}


} //namespace multiprecision
} //namespace boost


