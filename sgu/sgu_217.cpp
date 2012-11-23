#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

const double H = 5e-5;

struct F {
	double rr1, rr2;
	F(double r1, long double r2) : rr1(r1 * r1), rr2(r2 * r2) {
	}
	double operator()(long double x) const {
		x = x * x;
		return sqrt((rr2 - x) * (rr1 - x));
	}
};

int main() {
	double r1, r2;
	scanf("%lf%lf", &r1, &r2);
	if (r1 > r2) {
		swap(r1, r2);
	}
	int n = int(r1 / H);
	// int n = 1000000;
	double h = r1 / n / 2;
	F f(r1, r2);
	double s = 0;
	s += f(0) + f(r1);
	for (int i = 1; i < 2 * n; ++i) {
		if (i & 1) {
			s += 4 * f(i * h);
		} else {
			s += 2 * f(i * h);
		}
	}
	s /= 6 * n;
	s *= 8 * r1;
	printf("%.4lf\n", s);

	return 0;
}

