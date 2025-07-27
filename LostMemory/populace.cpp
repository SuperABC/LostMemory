#include "populace.h"

#include <iostream>
#include <algorithm>


using namespace std;

Populace::~Populace() {
	for (auto citizen : citizens) {
		if (citizen)delete citizen;
	}
}

void Populace::Init(int accomodation) {
	enum LIFE_TYPE {
		LIFE_SINGLE,
		LIFE_MARRY,
		LIFE_BIRTH,
		LIFE_DEAD
	};

	struct Human {
		int idx;
		int birth;
		LIFE_TYPE life;
		GENDER_TYPE gender;
		int father;
		int mother;
		int spouse;
		std::vector<std::pair<GENDER_TYPE, int>> childs;
	};

	int num = accomodation * 0.5 * exp(GetRandom(1000) / 1000.0f - 0.5f);

	std::vector<Human> females(1, { -1, 0, LIFE_DEAD });
	std::vector<Human> males(1, { -1, 0, LIFE_DEAD });
	std::vector<int> maleBirths(4096, -1);
	int currentBirth = 0;
	std::vector<std::vector<std::pair<int, LIFE_TYPE>>> chronology(4096);

	int year = 1;
	for (int i = 1; i <= 100; i++) {
		females.push_back({ -1, GetRandom(20), LIFE_SINGLE, GENDER_FEMALE, -1, -1, -1, {} });
		chronology[females.back().birth + 20 + GetRandom(15)].push_back(std::make_pair(females.size() - 1, LIFE_MARRY));
		chronology[females.back().birth + 60 + GetRandom(40)].push_back(std::make_pair(females.size() - 1, LIFE_DEAD));
	}
	for (int i = 1; i <= 100; i++) {
		males.push_back({ -1, GetRandom(20), LIFE_SINGLE, GENDER_MALE, -1, -1, -1, {} });
	}
	std::sort(males.begin(), males.end(), [](Human x, Human y) {return x.birth < y.birth; });
	maleBirths[0] = 0;
	for (int i = 1; i <= 100; i++) {
		if (males[i].birth > currentBirth) {
			for (int j = currentBirth + 1; j <= males[i].birth; j++) {
				maleBirths[j] = i;
			}
			currentBirth = males[i].birth;
		}
		chronology[males[i].birth + 60 + GetRandom(40)].push_back(std::make_pair(-i, LIFE_DEAD));
	}

	while (year < 4096 && females.size() + males.size() < num) {
		for (auto event : chronology[year]) {
			if (event.first >= 0) {
				switch (event.second)
				{
				case LIFE_MARRY: {
					int lowId = max(0, females[event.first].birth - 10);
					int highId = max(0, females[event.first].birth + 5);
					if (maleBirths[lowId] == maleBirths[highId])break;
					if (maleBirths[highId] == -1)break;
					int selectId = -1;
					for (int i = 0; i < 10; i++) {
						selectId = maleBirths[lowId] + GetRandom(maleBirths[highId] - maleBirths[lowId]);
						if (males[selectId].spouse >= 0) {
							selectId = -1;
							continue;
						}
						else {
							break;
						}
					}
					if (selectId < 0)break;
					females[event.first].spouse = selectId;
					females[event.first].life = LIFE_MARRY;
					males[selectId].spouse = event.first;
					males[selectId].life = LIFE_MARRY;
					int childs = ((GetRandom(8) == 0) ? 0 : (1 + GetRandom(6)));
					int interval = 1 + GetRandom(3);
					for (int i = 0; i < childs; i++) {
						if (year + interval - females[event.first].birth > 45)break;
						chronology[year + interval].push_back(std::make_pair(event.first, LIFE_BIRTH));
						interval += 1 + GetRandom(3);
					}
					break;
				}
				case LIFE_BIRTH: {
					int gender = GetRandom(2);
					if (gender == GENDER_FEMALE) {
						females[event.first].childs.push_back(std::make_pair(GENDER_FEMALE, females.size()));
						males[females[event.first].spouse].childs.push_back(std::make_pair(GENDER_FEMALE, females.size()));
						females.push_back({ -1, year, LIFE_SINGLE, GENDER_FEMALE, females[event.first].spouse, event.first, -1, {} });
						chronology[females.back().birth + 20 + GetRandom(15)].push_back(std::make_pair(females.size() - 1, LIFE_MARRY));
						chronology[females.back().birth + 60 + GetRandom(40)].push_back(std::make_pair(females.size() - 1, LIFE_DEAD));
					}
					else {
						females[event.first].childs.push_back(std::make_pair(GENDER_MALE, males.size()));
						males[females[event.first].spouse].childs.push_back(std::make_pair(GENDER_MALE, males.size()));
						males.push_back({ -1, year, LIFE_SINGLE, GENDER_MALE, females[event.first].spouse, event.first, -1, {} });
						if (males.back().birth > currentBirth) {
							for (int j = currentBirth + 1; j <= males.back().birth; j++) {
								maleBirths[j] = males.size() - 1;
							}
							currentBirth = males.back().birth;
						}
						chronology[males.back().birth + 60 + GetRandom(40)].push_back(std::make_pair(-((int)males.size() - 1), LIFE_DEAD));
					}
					break;
				}
				case LIFE_DEAD:
					females[event.first].life = LIFE_DEAD;
					break;
				default:
					break;
				}
			}
			else {
				switch (event.second)
				{
				case LIFE_DEAD:
					males[-event.first].life = LIFE_DEAD;
					break;
				default:
					break;
				}
			}
		}
		year++;
	}
	time.SetYear(year);

	for (int i = 0; i < females.size(); i++) {
		if (females[i].life != LIFE_DEAD && GetRandom(20) > 0) {
			Person* person = new Person();
			person->SetId(citizens.size());
			females[i].idx = citizens.size();
			person->SetGender(GENDER_FEMALE);
			int month = 1 + GetRandom(12);
			person->SetBirthday({ 2000 + females[i].birth, month, 1 + GetRandom(Time::DaysInMonth(2000 + females[i].birth, month)) });
			citizens.push_back(person);
		}
	}
	for (int i = 0; i < males.size(); i++) {
		if (males[i].life != LIFE_DEAD && GetRandom(20) > 0) {
			Person* person = new Person();
			person->SetId(citizens.size());
			males[i].idx = citizens.size();
			person->SetGender(GENDER_MALE);
			int month = 1 + GetRandom(12);
			person->SetBirthday({ 2000 + males[i].birth, month, 1 + GetRandom(Time::DaysInMonth(2000 + males[i].birth, month)) });
			citizens.push_back(person);
		}
	}

	for (auto female : females) {
		if (female.idx >= 0) {
			Person* person = citizens[female.idx];
			if (female.mother >= 0 && females[female.mother].idx >= 0)
				person->AddRelative(RELATIVE_MOTHER, citizens[females[female.mother].idx]);
			if (female.father >= 0 && males[female.father].idx >= 0)
				person->AddRelative(RELATIVE_FATHER, citizens[males[female.father].idx]);
			if (female.spouse >= 0 && males[female.spouse].idx >= 0) {
				person->AddRelative(RELATIVE_HUSBAND, citizens[males[female.spouse].idx]);
			}
			for (auto child : female.childs) {
				if (child.first == GENDER_FEMALE && females[child.second].idx >= 0)
					person->AddRelative(RELATIVE_DAUGHTER, citizens[females[child.second].idx]);
				else if (child.first == GENDER_MALE && males[child.second].idx >= 0)
					person->AddRelative(RELATIVE_SON, citizens[males[child.second].idx]);
			}
		}
	}

	for (auto male : males) {
		if (male.idx >= 0) {
			Person* person = citizens[male.idx];
			if (male.mother >= 0 && females[male.mother].idx >= 0)
				person->AddRelative(RELATIVE_MOTHER, citizens[females[male.mother].idx]);
			if (male.father >= 0 && males[male.father].idx >= 0)
				person->AddRelative(RELATIVE_FATHER, citizens[males[male.father].idx]);
			if (male.spouse >= 0 && females[male.spouse].idx >= 0) {
				person->AddRelative(RELATIVE_WIFE, citizens[females[male.spouse].idx]);
			}
			for (auto child : male.childs) {
				if (child.first == GENDER_FEMALE && females[child.second].idx >= 0)
					person->AddRelative(RELATIVE_DAUGHTER, citizens[females[child.second].idx]);
				else if (child.first == GENDER_MALE && males[child.second].idx >= 0)
					person->AddRelative(RELATIVE_SON, citizens[males[child.second].idx]);
			}
		}
	}

	for (auto citizen : citizens) {
		int number;
		do {
			number = pow(10, 9);
			for (int i = 0; i < 9; i++) {
				number += GetRandom(10) * pow(10, i);
			}
		} while (phoneRoll.find(number) != phoneRoll.end() && phoneRoll[number] != citizen);

		phoneRoll[number] = citizen;
		citizen->AddPhone(to_string(number));
	}
}

void Populace::Destroy() {
	for (auto citizen : citizens) {
		if (citizen)delete citizen;
	}
	citizens.clear();
}

void Populace::Tick() {

}

void Populace::Print() {
	if (citizens.size() == 0)return;

	cout << "总人口 " << citizens.size() << endl;

	int female = 0;
	int male = 0;
	vector<int> ageList(120, 0);
	for (auto citizen : citizens) {
		if (citizen->GetGender() == GENDER_FEMALE)female++;
		else male++;

		ageList[(time - citizen->GetBirthday()).GetYear()]++;
	}
	for (int age = 0; age < ageList.size(); age++) {
		cout << age << "岁人数 " << ageList[age] << endl;
	}
}

void Populace::Load(std::string path) {

}

void Populace::Save(std::string path) {

}

Time Populace::GetTime() {
	return time;
}

std::vector<Person*>& Populace::GetCitizens() {
	return citizens;
}
