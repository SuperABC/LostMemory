#pragma once

#include "job.h"
#include "organization.h"

class Person;
class Time {
public:
    Time() = default;
    Time(bool online);
    Time(int y, int mon, int d, int h = 0, int min = 0, int s = 0, int ms = 0);

    void SetYear(int y);
    void SetMonth(int m);
    void SetDay(int d);
    void SetHour(int h);
    void SetMinute(int m);
    void SetSecond(int s);
    void SetMillisecond(int ms);
    void SetDate(int y, int m, int d);
    void SetTime(int h, int m, int s, int ms = 0);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    int GetHour() const;
    int GetMinute() const;
    int GetSecond() const;
    int GetMillisecond() const;

    void SetToCurrentTime();
    void AddYears(int years);
    void AddMonths(int months);
    void AddDays(int days);
    void AddHours(int hours);
    void AddMinutes(int minutes);
    void AddSeconds(int seconds);
    void AddMilliseconds(int ms);

    std::string ToString() const;
    std::string Format(const std::string& fmt) const;

    bool operator==(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>=(const Time& other) const;
    bool operator!=(const Time& other) const;

    static int DaysInMonth(int year, int month);
    double DifferenceInSeconds(const Time& other) const;
    bool IsLeapYear() const;
    int DayOfWeek() const;
    std::string DayOfWeekName() const;
    int DayOfYear() const;

private:
    int year = 2000;
    int month = 1;
    int day = 1;
    int hour = 0;
    int minute = 0;
    int second = 0;
    int millisecond = 0;

    void Validate() const;
    void NormalizeTime();
    int OrdinalDate() const;
};

class Experience {
public:
    Experience() = default;

private:
    Time begin, end;
};

class EducationExperience : public Experience {
public:
    EducationExperience() = default;

private:
    std::string school;
};

class JobExperience : public Experience {
public:
    JobExperience() = default;

private:
    JOB_TYPE type;
    Organization* organization;
};

class EmotionExperience : public Experience {
public:
    EmotionExperience() = default;

private:
    Person* person;
};

