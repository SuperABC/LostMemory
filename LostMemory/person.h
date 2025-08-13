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
	~Person();

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
	void AddRelative(RELATIVE_TYPE type, std::shared_ptr<Person> person);
	std::shared_ptr<Person> GetFather();
	std::shared_ptr<Person> GetMother();
	std::shared_ptr<Person> GetSpouse();
	std::vector<std::shared_ptr<Person>> GetChilds();

	// 管理属性信息
	void AddPhone(std::string phone);
	void AddAsset(std::shared_ptr<Asset> asset);
	std::vector<std::shared_ptr<Asset>>& GetAssets();
	void AddAddress(std::shared_ptr<Room> room);
	std::vector<std::shared_ptr<Room>>& GetAddresses();

	// 管理经验信息
	void AddEducationExperience(EducationExperience exp);
	void AddEmotionExperience(EmotionExperience exp);
	void AddJobExperience(JobExperience exp);
	std::vector<EducationExperience>& GetEducationExperiences();
	std::vector<EmotionExperience>& GetEmotionExperiences();
	std::vector<JobExperience>& GetJobExperiences();
	void AddAcquaintance(std::shared_ptr<Person> person, Relation relation);
	std::vector<std::pair<std::shared_ptr<Person>, Relation>>& GetAcquaintances();

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

	std::vector<std::pair<RELATIVE_TYPE, std::shared_ptr<Person>>> relatives;
	std::vector<std::string> phones;
	std::vector<std::shared_ptr<Asset>> assets;
	std::vector<std::shared_ptr<Room>> addresses;
	std::vector<EducationExperience> educationExperiences;
	std::vector<EmotionExperience> emotionExperiences;
	std::vector<JobExperience> jobExperiences;
	std::vector<std::pair<std::shared_ptr<Person>, Relation>> acquaintances;
};