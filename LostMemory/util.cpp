#include "util.h"

#include <random>


using namespace std;

int GetRandom(int range, int (*cdf)(int)) {
	if (range <= 0)return 0;

	mt19937 rng(std::random_device{}());
	uniform_int_distribution<int> dist(0, range - 1);
	int ret = dist(rng);

	if (cdf == nullptr)
		return ret;
	else {
		return clamp(cdf(ret), 0, range - 1);
	}
}

bool InBox(int x, int y, int left, int right, int top, int bottom) {
	return (x - left) * (x - right) <= 0 &&
		(y - top) * (y - bottom) <= 0;
}

void debugf(LPCSTR format, ...) {
	va_list args;
	va_start(args, format);
	CHAR buf[1024] = { 0 };
	StringCchVPrintfA(buf, 1023, format, args);
	OutputDebugStringA(buf);
}

Counter::Counter(int count) : num(count) {

}

bool Counter::count() {
	return --num <= 0;
}
