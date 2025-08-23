﻿#pragma once

#include "job.h"
#include "component.h"

class Person;

class Experience {
public:
    Experience() = default;

    // 获取/设置经历时间
    const Time& GetBeginTime() const { return begin; }
    const Time& GetEndTime() const { return end; }
    void SetTime(const Time& b, const Time& e) { begin = b; end = e; }
    
private:
    Time begin, end;
};

class EducationExperience : public Experience {
public:
    EducationExperience() = default;

    // 设置教育经历属性
    void SetSchool(const std::string& s) { school = s; }
    const std::string& GetSchool() const { return school; }
    void AddClassmate(std::shared_ptr<Person> p) { classmates.push_back(p); }
    void SetTeacher(std::shared_ptr<Person> t) { teacher = t; }
    const std::vector<std::shared_ptr<Person>>& GetClassmates() const { return classmates; }
    std::shared_ptr<Person> GetTeacher() const { return teacher; }
    void SetGraduate(bool g) { graduate = g; }
    bool GetGraduate() const { return graduate; }

private:
    std::string school;
    std::vector<std::shared_ptr<Person>> classmates;
    std::shared_ptr<Person> teacher = nullptr;

    bool graduate = true;
};

class EmotionExperience : public Experience {
public:
    EmotionExperience() = default;

    // 获取/设置情感经历属性
    std::shared_ptr<Person> GetPerson() const { return person; }
    void SetPerson(std::shared_ptr<Person> p) { person = p; }

private:
    std::shared_ptr<Person> person;
};


class JobExperience : public Experience {
public:
    JobExperience() = default;

    // 获取/设置工作经历属性
    void SetJobType(JOB_TYPE t) { type = t; }
    JOB_TYPE GetJobType() const { return type; }
    void SetComponent(std::shared_ptr<Component> comp) { component = comp; }
    std::shared_ptr<Component> GetComponent() const { return component; }
    void AddColleague(std::shared_ptr<Person> p) { colleagues.push_back(p); }
    const std::vector<std::shared_ptr<Person>>& GetColleagues() const { return colleagues; }

private:
    JOB_TYPE type;
    std::shared_ptr<Component> component;
    std::vector<std::shared_ptr<Person>> colleagues;
};
