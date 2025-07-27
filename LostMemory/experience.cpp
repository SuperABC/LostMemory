#define _CRT_SECURE_NO_WARNINGS

#include "experience.h"

#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cmath>

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
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    std::tm tm = *std::localtime(&now_time);
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
    Validate();
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
    Validate();
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

std::string Time::ToString() const {
    return Format("YYYY-MM-DD HH:mm:ss.zzz");
}

std::string Time::Format(const std::string& fmt) const {
    std::ostringstream oss;
    for (size_t i = 0; i < fmt.size(); ++i) {
        if (fmt[i] == 'Y') {
            if (fmt.substr(i, 4) == "YYYY") {
                oss << std::setw(4) << std::setfill('0') << year;
                i += 3;
            }
            else if (fmt.substr(i, 2) == "YY") {
                oss << std::setw(2) << std::setfill('0') << (year % 100);
                i += 1;
            }
        }
        else if (fmt[i] == 'M') {
            if (fmt.substr(i, 2) == "MM") {
                oss << std::setw(2) << std::setfill('0') << month;
                i += 1;
            }
        }
        else if (fmt[i] == 'D') {
            if (fmt.substr(i, 2) == "DD") {
                oss << std::setw(2) << std::setfill('0') << day;
                i += 1;
            }
        }
        else if (fmt[i] == 'H') {
            if (fmt.substr(i, 2) == "HH") {
                oss << std::setw(2) << std::setfill('0') << hour;
                i += 1;
            }
        }
        else if (fmt[i] == 'm') {
            if (fmt.substr(i, 2) == "mm") {
                oss << std::setw(2) << std::setfill('0') << minute;
                i += 1;
            }
        }
        else if (fmt[i] == 's') {
            if (fmt.substr(i, 2) == "ss") {
                oss << std::setw(2) << std::setfill('0') << second;
                i += 1;
            }
        }
        else if (fmt[i] == 'z') {
            if (fmt.substr(i, 3) == "zzz") {
                oss << std::setw(3) << std::setfill('0') << millisecond;
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

double Time::DifferenceInSeconds(const Time& other) const {
    int daysDiff = OrdinalDate() - other.OrdinalDate();

    int timeDiff = (hour - other.hour) * 3600 +
        (minute - other.minute) * 60 +
        (second - other.second);

    double msDiff = (millisecond - other.millisecond) / 1000.0;

    return daysDiff * 86400.0 + timeDiff + msDiff;
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

std::string Time::DayOfWeekName() const {
    static const std::string names[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };
    return names[DayOfWeek()];
}

int Time::DayOfYear() const {
    int doy = day;
    for (int m = 1; m < month; m++) {
        doy += DaysInMonth(year, m);
    }
    return doy;
}

void Time::Validate() const {
    if (year < 0)
        throw std::out_of_range("Year cannot be negative");
    if (month < 1 || month > 12)
        throw std::out_of_range("Month must be between 1-12");
    if (day < 1 || day > DaysInMonth(year, month))
        throw std::out_of_range("Invalid day for given month and year");
    if (hour < 0 || hour > 23)
        throw std::out_of_range("Hour must be between 0-23");
    if (minute < 0 || minute > 59)
        throw std::out_of_range("Minute must be between 0-59");
    if (second < 0 || second > 59)
        throw std::out_of_range("Second must be between 0-59");
    if (millisecond < 0 || millisecond > 999)
        throw std::out_of_range("Millisecond must be between 0-999");
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
    int o = day;
    for (int m = 1; m < month; m++) {
        o += DaysInMonth(year, m);
    }
    return o;
}