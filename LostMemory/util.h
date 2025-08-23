#pragma once
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4150)

#include <string>
#include <memory>
#include <set>
#include <mutex>
#include <codecvt>
#include <locale>

#include <windows.h>
#include <strsafe.h>

#define GLOBAL_EPS 1e-4


// 获取[0, range - 1]的随机整数
int GetRandom(int range, int (*cdf)(int, int) = nullptr);

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

class Time {
public:
    Time() = default;
    Time(bool online);
    Time(int y, int mon, int d, int h = 0, int min = 0, int s = 0, int ms = 0);

	// 获取/设置时间
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    int GetHour() const;
    int GetMinute() const;
    int GetSecond() const;
    int GetMillisecond() const;
    void SetYear(int y);
    void SetMonth(int m);
    void SetDay(int d);
    void SetHour(int h);
    void SetMinute(int m);
    void SetSecond(int s);
    void SetMillisecond(int ms);
    void SetDate(int y, int m, int d);
    void SetTime(int h, int m, int s, int ms = 0);

	// 使用在线时间
    void SetToCurrentTime();

	// 时间偏移
    void AddYears(int years);
    void AddMonths(int months);
    void AddDays(int days);
    void AddHours(int hours);
    void AddMinutes(int minutes);
    void AddSeconds(int seconds);
    void AddMilliseconds(int ms);

	// 输出时间
    std::string ToString() const;
    std::string Format(const std::string& fmt) const;

	// 时间比较与计算
    bool operator==(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>=(const Time& other) const;
    bool operator!=(const Time& other) const;
    Time operator+(const Time& other) const;
    Time operator-(const Time& other) const;
    Time& operator+=(const Time& other);
    Time& operator-=(const Time& other);	
    double DifferenceInSeconds(const Time& other) const;

	// 日期属性
    bool IsLeapYear() const;
    int DayOfWeek() const;
    std::string DayOfWeekName() const;

	// 天数计算
    static int DaysInMonth(int year, int month);
    static int DaysInYear(int year);
    static int DaysBetweenYears(int startYear, int endYear);
    static int DaysBetween(const Time& start, const Time& end);

private:
    int year = 2000;
    int month = 1;
    int day = 1;
    int hour = 0;
    int minute = 0;
    int second = 0;
    int millisecond = 0;

	// 检查各项数值范围
    void Validate() const;

	// 时间进位
    void NormalizeTime();

	// 当前为当年第几天
    int OrdinalDate() const;
};

// 时间范围内随机采样
Time GetRandom(Time begin, Time end, int (*cdf)(int, int) = nullptr);

class MemoryManager {
private:
    struct WeakPtrCompare {
        bool operator()(const std::weak_ptr<void>& lhs,
            const std::weak_ptr<void>& rhs) const {
            return lhs.owner_before(rhs);
        }
    };

    static std::set<std::weak_ptr<void>, WeakPtrCompare> objects_;
    static std::mutex mutex_;

    // 数组删除器
    template <typename T>
    struct ArrayDeleter {
        void operator()(T* ptr) {
            delete[] ptr;
        }
    };

public:
    // 创建对象
    template <typename T, typename... Args>
    static std::shared_ptr<T> create(Args&&... args) {
        std::shared_ptr<T> ptr = std::make_shared<T>(std::forward<Args>(args)...);
        track(ptr);
        return ptr;
    }

    // 创建数组
    template <typename T>
    static std::shared_ptr<T> create_array(size_t size) {
        std::shared_ptr<T> ptr(new T[size], ArrayDeleter<T>());
        track(ptr);
        return ptr;
    }

    // 清理失效引用
    static void cleanup() {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto it = objects_.begin(); it != objects_.end(); ) {
            it->expired() ? it = objects_.erase(it) : ++it;
        }
    }

private:
    // 追踪对象
    template <typename T>
    static void track(const std::shared_ptr<T>& ptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        objects_.emplace(ptr);
    }
};

// 宏定义封装
#define LM_NEW(T, ...) MemoryManager::create<T>(__VA_ARGS__)
#define LM_NEW_ARRAY(T, size) MemoryManager::create_array<T>(size)
#define LM_DELETE(ptr) (ptr).reset()

