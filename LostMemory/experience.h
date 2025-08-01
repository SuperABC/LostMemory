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
    Time operator+(const Time& other) const;
    Time operator-(const Time& other) const;
    Time& operator+=(const Time& other);
    Time& operator-=(const Time& other);

    static int DaysInMonth(int year, int month);
    static int DaysInYear(int year);
    static int DaysBetweenYears(int startYear, int endYear);
    static int DaysBetween(const Time& start, const Time& end);
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

Time GetRandom(Time begin, Time end);

class Experience {
public:
    Experience() = default;

    const Time& GetBeginTime() const { return begin; }
    const Time& GetEndTime() const { return end; }
    void SetTime(const Time& b, const Time& e) { begin = b; end = e; }
private:
    Time begin, end;
};

class EducationExperience : public Experience {
public:
    EducationExperience() = default;

    void SetSchool(const std::string& s) { school = s; }
    const std::string& GetSchool() const { return school; }
    void AddClassmate(Person* p) { classmates.push_back(p); }
    void SetTeacher(Person* t) { teacher = t; }
    const std::vector<Person*>& GetClassmates() const { return classmates; }
    Person* GetTeacher() const { return teacher; }
    void SetGraduate(bool g) { graduate = g; }
    bool GetGraduate() const { return graduate; }

private:
    std::string school;
    std::vector<Person*> classmates;
    Person* teacher = nullptr;

    bool graduate = true;
};

class JobExperience : public Experience {
public:
    JobExperience() = default;

    void SetJobType(JOB_TYPE t) { type = t; }
    JOB_TYPE GetJobType() const { return type; }
    void SetOrganization(Organization* org) { organization = org; }
    Organization* GetOrganization() const { return organization; }
    void AddColleague(Person* p) { colleagues.push_back(p); }
    const std::vector<Person*>& GetColleagues() const { return colleagues; }
private:
    JOB_TYPE type;
    Organization* organization;
    std::vector<Person*> colleagues;
};

class EmotionExperience : public Experience {
public:
    EmotionExperience() = default;

    Person* GetPerson() const { return person; }
    void SetPerson(Person* p) { person = p; }
private:
    Person* person;
};

