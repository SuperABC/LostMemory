#pragma once

#include "relation.h"
#include "character.h"
#include "job.h"
#include "asset.h"
#include "experience.h"

#include <string>
#include <vector>

class Time;
class JobExperience;
class EmotionExperience;

enum GENDER_TYPE {
	GENDER_FEMALE, // 女性
	GENDER_MALE // 男性
};

enum RELATIVE_TYPE {
	RELATIVE_FATHER, // 父亲
	RELATIVE_MOTHER, // 母亲
	RELATIVE_WIFE, // 妻子
	RELATIVE_HUSBAND, // 丈夫
	RELATIVE_SON, // 儿子
	RELATIVE_DAUGHTER // 女儿
};

class Person {
public:
	Person() = default;

	// 获取/设置基础信息
	int GetId() const { return id; }
	void SetId(int newId) { id = newId; }
	const std::string& GetName() const { return name; }
	void SetName(const std::string& newName) { name = newName; }
	GENDER_TYPE GetGender() const { return gender; }
	void SetGender(GENDER_TYPE newGender) { gender = newGender; }
	int GetHeight() const { return height; }
	void SetHeight(int newHeight) { height = newHeight; }
	int GetWeight() const { return weight; }
	void SetWeight(int newWeight) { weight = newWeight; }
	const Time& GetBirthday() const { return birthday; }
	void SetBirthday(const Time& newBirthday) { birthday = newBirthday; }
	const Time& GetMarryday() const { return marryday; }
	void SetMarryday(const Time& newMarryday) { marryday = newMarryday; }
	const Job& GetJob() const { return job; }
	void SetJob(const Job& newJob) { job = newJob; }
	const std::string& GetNick() const { return nick; }
	void SetNick(const std::string& newNick) { nick = newNick; }
	int GetDeposit() const { return deposit; }
	void SetDeposit(int newDeposit) { deposit = newDeposit; }

	// 管理亲属
	void AddRelative(RELATIVE_TYPE type, Person* person);
	Person* GetFather();
	Person* GetMother();
	Person* GetSpouse();
	std::vector<Person*> GetChilds();

	// 管理属性信息
	void AddPhone(std::string phone);
	void AddAsset(Asset* asset);
	std::vector<Asset*>& GetAssets();
	void AddAddress(Room* room);
	std::vector<Room*>& GetAddresses();

	// 管理经验信息
	void AddEducationExperience(const EducationExperience& exp);
	void AddEmotionExperience(const EmotionExperience& exp);
	void AddJobExperience(const JobExperience& exp);
	std::vector<EducationExperience>& GetEducationExperiences();
	std::vector<EmotionExperience>& GetEmotionExperiences();
	std::vector<JobExperience>& GetJobExperiences();
	void AddAcquaintance(Person* person, Relation relation);
	std::vector<std::pair<Person*, Relation>>& GetAcquaintances();

	// 组合相同经历
	void ExpComposition();

private:
	int id;
	std::string name;
	GENDER_TYPE gender;
	Time birthday;
	Time marryday;
	int height, weight;
	Job job;
	std::string nick;
	int deposit;

	std::vector<std::pair<RELATIVE_TYPE, Person*>> relatives;
	std::vector<std::string> phones;
	std::vector<Asset*> assets;
	std::vector<Room*> addresses;
	std::vector<EducationExperience> educationExperiences;
	std::vector<EmotionExperience> emotionExperiences;
	std::vector<JobExperience> jobExperiences;
	std::vector<std::pair<Person*, Relation>> acquaintances;
};