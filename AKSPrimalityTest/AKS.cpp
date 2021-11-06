#include <numeric>
#include "utils.cpp"
#include "AKS.h"

inline bool test1(const uint64_t& n, bool& isPrime)
{
	isPrime = true;
	// Step 1 - If n = a^b for integers a > 1 and b > 1, output composite.
	const double EPSILON = 1E-10;//0.0000000001;
	for (double b = 2; b <= std::log2(n); ++b) {
		const double  a = std::pow(n, 1 / b);

		if (std::abs(std::floor(a) - a) < EPSILON) {
			isPrime = false;
			return false;
		}
	}

	return true;
}

inline uint64_t step2(const uint64_t& n) {
	// Step 2 - Find the smallest r such that Or(n) > (log2 n)^2
	const double maxk = std::floor(std::pow(std::log2(n), 2));
	const double maxr = std::max(3.0, std::ceil(std::pow(std::log2(n), 5)));
	bool nextR = true;
	uint64_t r = 0;

	for (r = 2; nextR && r < maxr; ++r) {
		nextR = false;
		for (uint64_t k = 1; (!nextR) && k < maxk; ++k) {
			const uint64_t mod = fast_pow_mod(n, k, r);
			nextR = mod == 1 || mod == 0;
		}
	}
	--r;

	return r;
}

inline bool test3(const uint64_t& n, const uint64_t& r, bool& isPrime)
{
	isPrime = true;
	//Step 3 - If 1 < gcd(a,n) < n for some a ≤ r, output composite
	for (uint64_t i = r; i > 1; --i) {
		const uint64_t gcd = std::gcd(i, n);

		if (1 < gcd && gcd < n) {
			isPrime = false;
			return false;
		}
	}

	return true;
}

inline bool test4(const uint64_t& n, const uint64_t& r, bool& isPrime)
{
	// Step 4 - If n ≤ r, output prime
	isPrime = (n <= r);
	return !isPrime;
}

inline bool test5(const uint64_t& n, bool& isPrime)
{
	isPrime = true;
	//Step 5 - check that for every coeficient (ai) in (x-1)^n ai%n == 0
	// https://fishi.devtail.io/weblog/2015/06/25/computing-large-binomial-coefficients-modulo-prime-non-prime/

	uint64_t current = 1;

	for (int i = 1; i < n / 2 + 1; ++i)
	{
		current = mul_mod(current, n + 1 - i, n) / i;

		if (current % n != 0) {
			isPrime = false;
			return false;
		}
	}

	return true;
}

bool isPrime(uint64_t n) {

	bool isPrime;
	if (!test1(n, isPrime)) return isPrime;

	uint64_t r = step2(n);

	if (!test3(n, r, isPrime)) return isPrime;

	if (!test4(n, r, isPrime)) return isPrime;

	if (!test5(n, isPrime)) return isPrime;

	// Step 6 -  Output prime
	return true;
}

