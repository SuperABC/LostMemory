#include "person.h"


using namespace std;

Person::~Person() {
	for (auto asset : assets) {
		delete asset;
	}
}

void Person::AddRelative(RELATIVE_TYPE type, Person* person) {
	relatives.push_back(make_pair(type, person));
}

Person* Person::GetFather() {
	for (auto relative : relatives) {
		if (relative.first == RELATIVE_FATHER)return relative.second;
	}
	return nullptr;
}

Person* Person::GetMother() {
	for (auto relative : relatives) {
		if (relative.first == RELATIVE_MOTHER)return relative.second;
	}
	return nullptr;
}

Person* Person::GetSpouse() {
	for (auto relative : relatives) {
		if (relative.first == RELATIVE_WIFE || relative.first == RELATIVE_HUSBAND)return relative.second;
	}

	return nullptr;
}

vector<Person*> Person::GetChilds() {
	vector<Person*>childs;
	for (auto relative : relatives) {
		if (relative.first == RELATIVE_SON || relative.first == RELATIVE_DAUGHTER)childs.push_back(relative.second);
	}
	return childs;
}

void Person::AddPhone(string phone) {
	phones.push_back(phone);
}

void Person::AddAddress(Room* room) {
	addresses.push_back(room);
}

vector<Room*>& Person::GetAddresses() {
	return addresses;
}

void Person::AddAsset(Asset* asset) {
	assets.push_back(asset);
}

vector<Asset*>& Person::GetAssets() {
	return assets;
}

void Person::AddEducationExperience(const EducationExperience& exp) {
	educationExperiences.push_back(exp);
}

void Person::AddJobExperience(const JobExperience& exp) {
	jobExperiences.push_back(exp);
}

void Person::AddEmotionExperience(const EmotionExperience& exp) {
	emotionExperiences.push_back(exp);
}

vector<EducationExperience>& Person::GetEducationExperiences() {
	return educationExperiences;
}

vector<JobExperience>& Person::GetJobExperiences() {
	return jobExperiences;
}

vector<EmotionExperience>& Person::GetEmotionExperiences() {
	return emotionExperiences;
}

void Person::AddAcquaintance(Person* person, Relation relation) {
	acquaintances.push_back(make_pair(person, relation));
}

vector<pair<Person*, Relation>>& Person::GetAcquaintances() {
	return acquaintances;
}

void Person::ExpComposition() {
	if (educationExperiences.size() == 0)return;

	int idx = 0;
	EducationExperience education = educationExperiences[0];
	for (int i = 1; i < educationExperiences.size(); i++) {
		if (education.GetSchool() == educationExperiences[i].GetSchool() &&
			education.GetEndTime().GetYear() == educationExperiences[i].GetBeginTime().GetYear()) {
			education.SetTime(education.GetBeginTime(), educationExperiences[i].GetEndTime());
			education.SetGraduate(educationExperiences[i].GetGraduate());
		}
		else {
			educationExperiences[idx++] = education;
			education = educationExperiences[i];
		}
	}
	educationExperiences[idx++] = education;
	educationExperiences.resize(idx);
}
