﻿#define _CRT_SECURE_NO_WARNINGS

#include "util.h"

#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <random>


using namespace std;

int GetRandom(int range, int (*cdf)(int)) {
	if (range <= 0)return 0;

	mt19937 rng(random_device{}());
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

Time::Time(bool online) {
    if (online) {
        SetToCurrentTime();
    }
}

Time::Time(int y, int mon, int d, int h, int min, int s, int ms)
    : year(y), month(mon), day(d), hour(h), minute(min), second(s), millisecond(ms) {
    Validate();
}

void Time::SetYear(int y) {
    year = y; Validate();
}
void Time::SetMonth(int m) {
    month = m; Validate();
}
void Time::SetDay(int d) {
    day = d; Validate();
}
void Time::SetHour(int h) {
    hour = h; Validate();
}
void Time::SetMinute(int m) {
    minute = m; Validate();
}
void Time::SetSecond(int s) {
    second = s; Validate();
}
void Time::SetMillisecond(int ms) {
    millisecond = ms; Validate();
}

void Time::SetDate(int y, int m, int d) {
    year = y; month = m; day = d;
    Validate();
}

void Time::SetTime(int h, int m, int s, int ms) {
    hour = h; minute = m; second = s; millisecond = ms;
    Validate();
}

int Time::GetYear() const {
    return year;
}
int Time::GetMonth() const {
    return month;
}
int Time::GetDay() const {
    return day;
}
int Time::GetHour() const {
    return hour;
}
int Time::GetMinute() const {
    return minute;
}
int Time::GetSecond() const {
    return second;
}
int Time::GetMillisecond() const {
    return millisecond;
}

void Time::SetToCurrentTime() {
    auto now = chrono::system_clock::now();
    auto now_time = chrono::system_clock::to_time_t(now);
    auto ms = chrono::duration_cast<chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    tm tm = *localtime(&now_time);
    year = tm.tm_year + 1900;
    month = tm.tm_mon + 1;
    day = tm.tm_mday;
    hour = tm.tm_hour;
    minute = tm.tm_min;
    second = tm.tm_sec;
    millisecond = static_cast<int>(ms.count());
}

void Time::AddYears(int years) {
    year += years;
}

void Time::AddMonths(int months) {
    month += months;
    while (month > 12) {
        month -= 12;
        year++;
    }
    while (month < 1) {
        month += 12;
        year--;
    }
}

void Time::AddDays(int days) {
    day += days;
    while (day > DaysInMonth(year, month)) {
        day -= DaysInMonth(year, month);
        AddMonths(1);
    }
    while (day < 1) {
        AddMonths(-1);
        day += DaysInMonth(year, month);
    }
}

void Time::AddHours(int hours) {
    hour += hours;
    NormalizeTime();
}

void Time::AddMinutes(int minutes) {
    minute += minutes;
    NormalizeTime();
}

void Time::AddSeconds(int seconds) {
    second += seconds;
    NormalizeTime();
}

void Time::AddMilliseconds(int ms) {
    millisecond += ms;
    NormalizeTime();
}

string Time::ToString() const {
    return Format("YYYY-MM-DD HH:mm:ss.zzz");
}

string Time::Format(const string& fmt) const {
    ostringstream oss;
    for (size_t i = 0; i < fmt.size(); ++i) {
        if (fmt[i] == 'Y') {
            if (fmt.substr(i, 4) == "YYYY") {
                oss << setw(4) << setfill('0') << year;
                i += 3;
            }
            else if (fmt.substr(i, 2) == "YY") {
                oss << setw(2) << setfill('0') << (year % 100);
                i += 1;
            }
        }
        else if (fmt[i] == 'M') {
            if (fmt.substr(i, 2) == "MM") {
                oss << setw(2) << setfill('0') << month;
                i += 1;
            }
        }
        else if (fmt[i] == 'D') {
            if (fmt.substr(i, 2) == "DD") {
                oss << setw(2) << setfill('0') << day;
                i += 1;
            }
        }
        else if (fmt[i] == 'H') {
            if (fmt.substr(i, 2) == "HH") {
                oss << setw(2) << setfill('0') << hour;
                i += 1;
            }
        }
        else if (fmt[i] == 'm') {
            if (fmt.substr(i, 2) == "mm") {
                oss << setw(2) << setfill('0') << minute;
                i += 1;
            }
        }
        else if (fmt[i] == 's') {
            if (fmt.substr(i, 2) == "ss") {
                oss << setw(2) << setfill('0') << second;
                i += 1;
            }
        }
        else if (fmt[i] == 'z') {
            if (fmt.substr(i, 3) == "zzz") {
                oss << setw(3) << setfill('0') << millisecond;
                i += 2;
            }
        }
        else {
            oss << fmt[i];
        }
    }
    return oss.str();
}

bool Time::operator==(const Time& other) const {
    return year == other.year &&
        month == other.month &&
        day == other.day &&
        hour == other.hour &&
        minute == other.minute &&
        second == other.second &&
        millisecond == other.millisecond;
}

bool Time::operator<(const Time& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    if (day != other.day) return day < other.day;
    if (hour != other.hour) return hour < other.hour;
    if (minute != other.minute) return minute < other.minute;
    if (second != other.second) return second < other.second;
    return millisecond < other.millisecond;
}

bool Time::operator>(const Time& other) const { return other < *this; }
bool Time::operator<=(const Time& other) const { return !(*this > other); }
bool Time::operator>=(const Time& other) const { return !(*this < other); }
bool Time::operator!=(const Time& other) const { return !(*this == other); }

Time Time::operator+(const Time& other) const {
    Time result = *this;
    result.AddYears(other.year);
    result.AddMonths(other.month);
    result.AddDays(other.day);
    result.AddHours(other.hour);
    result.AddMinutes(other.minute);
    result.AddSeconds(other.second);
    result.AddMilliseconds(other.millisecond);
    return result;
}

Time Time::operator-(const Time& other) const {
    Time result = *this;
    result.AddYears(-other.year);
    result.AddMonths(-(other.month - 1));
    result.AddDays(-(other.day - 1));
    result.AddHours(-other.hour);
    result.AddMinutes(-other.minute);
    result.AddSeconds(-other.second);
    result.AddMilliseconds(-other.millisecond);
    return result;
}

Time& Time::operator+=(const Time& other) {
    *this = *this + other;
    return *this;
}

Time& Time::operator-=(const Time& other) {
    *this = *this - other;
    return *this;
}

double Time::DifferenceInSeconds(const Time& other) const {
    if (*this == other) return 0.0;

    const Time* earlier = this;
    const Time* later = &other;
    bool inverted = false;
    if (*this > other) {
        earlier = &other;
        later = this;
        inverted = true;
    }

    int yearDays = 0;
    if (earlier->year != later->year) {
        yearDays = DaysBetweenYears(earlier->year, later->year);
    }

    int earlierDayOfYear = earlier->OrdinalDate();
    int laterDayOfYear = later->OrdinalDate();

    int dayDifference = laterDayOfYear - earlierDayOfYear + yearDays;

    int secondsEarlier = earlier->hour * 3600 + earlier->minute * 60 + earlier->second;
    int secondsLater = later->hour * 3600 + later->minute * 60 + later->second;

    double totalSeconds = dayDifference * 86400.0 + (secondsLater - secondsEarlier);

    totalSeconds += (later->millisecond - earlier->millisecond) / 1000.0;

    return inverted ? totalSeconds : -totalSeconds;
}

bool Time::IsLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Time::DayOfWeek() const {
    int m = month;
    int y = year;
    if (m < 3) {
        m += 12;
        y--;
    }
    int q = day;
    int k = y % 100;
    int j = y / 100;
    int h = (q + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    return (h + 6) % 7;
}

string Time::DayOfWeekName() const {
    static const string names[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };
    return names[DayOfWeek()];
}

void Time::Validate() const {
    if (month < 1 || month > 12)
        throw out_of_range("Month must be between 1-12.\n");
    if (day < 1 || day > DaysInMonth(year, month))
        throw out_of_range("Invalid day for given month and year.\n");
    if (hour < 0 || hour > 23)
        throw out_of_range("Hour must be between 0-23.\n");
    if (minute < 0 || minute > 59)
        throw out_of_range("Minute must be between 0-59.\n");
    if (second < 0 || second > 59)
        throw out_of_range("Second must be between 0-59.\n");
    if (millisecond < 0 || millisecond > 999)
        throw out_of_range("Millisecond must be between 0-999.\n");
}

int Time::DaysInMonth(int year, int month) {
    static const int days[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        return 29;
    }
    return days[month - 1];
}

int Time::DaysInYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 366 : 365;
}

int Time::DaysBetweenYears(int startYear, int endYear) {
    if (startYear > endYear) return -DaysBetweenYears(endYear, startYear);

    int totalDays = 0;
    for (int year = startYear; year < endYear; year++) {
        totalDays += DaysInYear(year);
    }
    return totalDays;
}

int Time::DaysBetween(const Time& start, const Time& end) {
    // 确保开始日期不晚于结束日期
    if (start > end) {
        return -DaysBetween(end, start);
    }

    // 计算年份差的天数
    int totalDays = 0;
    for (int year = start.GetYear(); year < end.GetYear(); year++) {
        totalDays += Time::DaysInYear(year);
    }

    // 计算开始日期在当年的天数
    Time startYearStart(start.GetYear(), 1, 1);
    int startDays = (start - startYearStart).GetDay();

    // 计算结束日期在当年的天数
    Time endYearStart(end.GetYear(), 1, 1);
    int endDays = (end - endYearStart).GetDay();

    return totalDays + endDays - startDays;
}

void Time::NormalizeTime() {
    while (millisecond >= 1000) {
        millisecond -= 1000;
        second++;
    }
    while (millisecond < 0) {
        millisecond += 1000;
        second--;
    }

    while (second >= 60) {
        second -= 60;
        minute++;
    }
    while (second < 0) {
        second += 60;
        minute--;
    }

    while (minute >= 60) {
        minute -= 60;
        hour++;
    }
    while (minute < 0) {
        minute += 60;
        hour--;
    }

    while (hour >= 24) {
        hour -= 24;
        day++;
    }
    while (hour < 0) {
        hour += 24;
        day--;
    }

    while (day > DaysInMonth(year, month)) {
        day -= DaysInMonth(year, month);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    while (day < 1) {
        month--;
        if (month < 1) {
            month = 12;
            year--;
        }
        day += DaysInMonth(year, month);
    }

    Validate();
}

int Time::OrdinalDate() const {
    int days = day;
    for (int m = 1; m < month; m++) {
        days += DaysInMonth(year, m);
    }
    return days;
}

Time GetRandom(Time begin, Time end, int (*cdf)(int)) {
	// 矫正起始与结束时间
    if (begin > end) {
        swap(begin, end);
    }
    else if (begin == end) {
        return begin;
    }

    // 将时间归一化到当天0点
    begin.SetTime(0, 0, 0, 0);
    end.SetTime(0, 0, 0, 0);

    // 计算总天数
    int totalDays = Time::DaysBetween(begin, end) + 1;

    // 生成随机偏移天数
    int randomDays = GetRandom(totalDays, cdf);

    // 创建结果时间
    Time result = begin;
    result.AddDays(randomDays);

    return result;
}

// 静态成员初始化
std::set<std::weak_ptr<void>, MemoryManager::WeakPtrCompare> MemoryManager::objects_;
std::mutex MemoryManager::mutex_;
