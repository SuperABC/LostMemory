#pragma once
#pragma warning(disable:4244)
#pragma warning(disable:4267)

#include <windows.h>
#include <strsafe.h>

// 获取[0, range - 1]的随机整数
int GetRandom(int range, float (*cdf)(float) = nullptr);

// 判断(x, y)是否在矩形中
bool InBox(int x, int y, int left, int right, int top, int bottom);

// 调试控制台输出
void debugf(LPCSTR format, ...);

// 计数器
class Counter {
public:
	Counter(int count);

	bool count();

private:
	int num;
};
