#include "populace.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>


using namespace std;

// TODO: 当前仍在持续的经历截止时间设为-1

Populace::~Populace() {
	citizens.clear();
}

void Populace::Init(int accomodation) {
	// 生成市民
	GenerateCitizens(accomodation * exp(GetRandom(1000) / 1000.0f - 0.5f));

	// 生成手机号
	GeneratePhones();

	// 生成经历
	GenerateEducations();
	GenerateEmotions();
	GenerateJobs();

	// 生成朋友
	GenerateAcquaintances();
}

void Populace::Destroy() {
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

void Populace::Load(string path) {

}

void Populace::Save(string path) {

}

Time Populace::GetTime() {
	return time;
}

vector<shared_ptr<Person>>& Populace::GetCitizens() {
	return citizens;
}

void Populace::GenerateCitizens(int num) {
	enum LIFE_TYPE {
		LIFE_SINGLE,
		LIFE_MARRY,
		LIFE_BIRTH,
		LIFE_DEAD
	};

	struct Human {
		int idx;
		int birth;
		int marry;
		LIFE_TYPE life;
		GENDER_TYPE gender;
		int father;
		int mother;
		int spouse;
		vector<pair<GENDER_TYPE, int>> childs;
	};

	// 临时男女数组及年表
	vector<Human> females(1, { -1, 0, LIFE_DEAD });
	vector<Human> males(1, { -1, 0, LIFE_DEAD });
	vector<int> maleBirths(4096, -1);
	int currentBirth = 0;
	vector<vector<pair<int, LIFE_TYPE>>> chronology(4096);

	// 初始添加100男100女
	int year = 1;
	for (int i = 1; i <= 100; i++) {
		females.push_back({ -1, GetRandom(20), -1, LIFE_SINGLE, GENDER_FEMALE, -1, -1, -1, {} });
		chronology[females.back().birth + 20 + GetRandom(15)].push_back(make_pair(females.size() - 1, LIFE_MARRY));
		chronology[females.back().birth + 60 + GetRandom(40)].push_back(make_pair(females.size() - 1, LIFE_DEAD));
	}
	for (int i = 1; i <= 100; i++) {
		males.push_back({ -1, GetRandom(20), -1, LIFE_SINGLE, GENDER_MALE, -1, -1, -1, {} });
	}
	sort(males.begin(), males.end(), [](Human x, Human y) {return x.birth < y.birth; });
	maleBirths[0] = 0;
	for (int i = 1; i <= 100; i++) {
		if (males[i].birth > currentBirth) {
			for (int j = currentBirth + 1; j <= males[i].birth; j++) {
				maleBirths[j] = i;
			}
			currentBirth = males[i].birth;
		}
		chronology[males[i].birth + 60 + GetRandom(40)].push_back(make_pair(-i, LIFE_DEAD));
	}

	// 自动迭代繁殖最多4096年
	while (year < 4096 && females.size() + males.size() < num) {
		for (auto event : chronology[year]) {
			if (event.first >= 0) {
				switch (event.second) {
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
					females[event.first].marry = year;
					males[selectId].spouse = event.first;
					males[selectId].life = LIFE_MARRY;
					males[selectId].marry = year;
					int childs = ((GetRandom(8) == 0) ? 0 : (1 + GetRandom(6)));
					int interval = 1 + GetRandom(3);
					for (int i = 0; i < childs; i++) {
						if (year + interval - females[event.first].birth > 45)break;
						chronology[year + interval].push_back(make_pair(event.first, LIFE_BIRTH));
						interval += 1 + GetRandom(3);
					}
					break;
				}
				case LIFE_BIRTH: {
					int gender = GetRandom(2);
					if (gender == GENDER_FEMALE) {
						females[event.first].childs.push_back(make_pair(GENDER_FEMALE, females.size()));
						males[females[event.first].spouse].childs.push_back(make_pair(GENDER_FEMALE, females.size()));
						females.push_back({ -1, year, -1, LIFE_SINGLE, GENDER_FEMALE, females[event.first].spouse, event.first, -1, {} });
						if (GetRandom(10) > 0)
							chronology[females.back().birth + 20 + GetRandom(15)].push_back(make_pair(females.size() - 1, LIFE_MARRY));
						chronology[females.back().birth + 60 + GetRandom(40)].push_back(make_pair(females.size() - 1, LIFE_DEAD));
					}
					else {
						females[event.first].childs.push_back(make_pair(GENDER_MALE, males.size()));
						males[females[event.first].spouse].childs.push_back(make_pair(GENDER_MALE, males.size()));
						males.push_back({ -1, year, -1, LIFE_SINGLE, GENDER_MALE, females[event.first].spouse, event.first, -1, {} });
						if (males.back().birth > currentBirth) {
							for (int j = currentBirth + 1; j <= males.back().birth; j++) {
								maleBirths[j] = males.size() - 1;
							}
							currentBirth = males.back().birth;
						}
						chronology[males.back().birth + 60 + GetRandom(40)].push_back(make_pair(-((int)males.size() - 1), LIFE_DEAD));
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
				switch (event.second) {
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
	time.SetYear(year + 2000);

	// 将活着的男女加入市民列表
	for (int i = 1; i < females.size(); i++) {
		if (females[i].life != LIFE_DEAD && GetRandom(20) > 0) {
			shared_ptr<Person> person = LM_NEW(Person);
			person->SetId(citizens.size());
			females[i].idx = citizens.size();
			person->SetGender(GENDER_FEMALE);
			int month = 1 + GetRandom(12);
			person->SetBirthday({ 2000 + females[i].birth, month, 1 + GetRandom(Time::DaysInMonth(2000 + females[i].birth, month)) });
			citizens.push_back(person);
		}
	}
	for (int i = 1; i < males.size(); i++) {
		if (males[i].life != LIFE_DEAD && GetRandom(20) > 0) {
			shared_ptr<Person> person = LM_NEW(Person);
			person->SetId(citizens.size());
			males[i].idx = citizens.size();
			person->SetGender(GENDER_MALE);
			int month = 1 + GetRandom(12);
			person->SetBirthday({ 2000 + males[i].birth, month, 1 + GetRandom(Time::DaysInMonth(2000 + males[i].birth, month)) });
			citizens.push_back(person);
		}
	}

	// 为所有人分配姓名
	for (auto& citizen : citizens) {
		citizen->SetName(nameGenerator.GenerateName(
			citizen->GetGender() == GENDER_MALE, citizen->GetGender() == GENDER_FEMALE));
	}

	// 记录有配偶的市民的结婚日期
	for (int i = 1; i < females.size(); i++) {
		if (females[i].spouse >= 0 && females[i].idx >= 0 && males[females[i].spouse].idx >= 0) {
			int month = GetRandom(12) + 1;
			Time marryday = Time(2000 + females[i].marry, month, 1 + GetRandom(Time::DaysInMonth(2000 + females[i].marry, month)));
			citizens[females[i].idx]->SetMarryday(marryday);
			citizens[males[females[i].spouse].idx]->SetMarryday(marryday);
		}
	}

	// 记录亲属关系
	for (auto female : females) {
		if (female.idx >= 0) {
			shared_ptr<Person> person = citizens[female.idx];
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
			shared_ptr<Person> person = citizens[male.idx];
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

	debugf("generate %d citizens.\n", citizens.size());
}

void Populace::GeneratePhones() {
	// 生成手机号
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

	debugf("generate phones.\n", citizens.size());
}

void Populace::GenerateEducations() {
	enum EducationLevel {
		EDUCATION_PRIMARY,
		EDUCATION_JUNIOR,
		EDUCATION_SENIOR,
		EDUCATION_COLLEGE,
		EDUCATION_POST,
		EDUCATION_END
	};

	struct SchoolClass {
		string schoolName;
		EducationLevel level;
		int startYear;
		int grade;
		vector<int> students;
		int teacher = -1;
	};
	vector<SchoolClass> levelClasses[EDUCATION_END];

	// 从120年前开始模拟
	mt19937 generator(random_device{}());
	vector<int> levelPotentials[EDUCATION_END];
	for (int year = time.GetYear() - 120; year <= time.GetYear(); year++) {
		// 班级变动
		for (int level = EDUCATION_PRIMARY; level <= EDUCATION_POST; level++) {
			for (auto& cls : levelClasses[level]) {
				Time begin(year - 1, 9, 1);
				Time end(year, 6, 30);

				for (auto student : cls.students) {
					EducationExperience eduExp;
					eduExp.SetSchool(cls.schoolName);
					eduExp.SetTime(begin, end);
					citizens[student]->AddEducationExperience(eduExp);
				}
			}

			for (auto& cls : levelClasses[level]) {
				for (int i = 0; i < cls.students.size(); i++) {
					int fate = GetRandom(100);

					if (fate > 95) { // 转学
						vector<SchoolClass*> targetClasses;
						for (auto& target : levelClasses[level]) {
							if (&target != &cls && target.grade == cls.grade &&
								target.startYear == cls.startYear) {
								targetClasses.push_back(&target);
							}
						}
						if (!targetClasses.empty()) {
							SchoolClass* targetClass = targetClasses[GetRandom(targetClasses.size())];
							targetClass->students.push_back(cls.students[i]);
							cls.students[i] = cls.students.back();
							cls.students.pop_back();
						}
					}
					else if (fate > 92) { // 留级
						vector<SchoolClass*> targetClasses;
						for (auto& target : levelClasses[level]) {
							if (&target != &cls && target.grade == cls.grade - 1 &&
								target.schoolName == cls.schoolName) {
								targetClasses.push_back(&target);
							}
						}
						if (!targetClasses.empty()) {
							SchoolClass* targetClass = targetClasses[GetRandom(targetClasses.size())];
							targetClass->students.push_back(cls.students[i]);
							cls.students[i] = cls.students.back();
							cls.students.pop_back();
						}
					}
					else if (fate > 90) { // 跳级
						bool valid = false;
						if (level == EDUCATION_PRIMARY && cls.grade < 6) {
							valid = true;
						}
						if (level == EDUCATION_JUNIOR && cls.grade < 3) {
							valid = true;
						}
						if (level == EDUCATION_SENIOR && cls.grade < 3) {
							valid = true;
						}
						if (level == EDUCATION_COLLEGE && cls.grade < 4) {
							valid = true;
						}

						if (valid) {
							vector<SchoolClass*> targetClasses;
							for (auto& target : levelClasses[level]) {
								if (target.grade == cls.grade + 1 &&
									target.schoolName == cls.schoolName) {
									targetClasses.push_back(&target);
								}
							}
							if (!targetClasses.empty()) {
								SchoolClass* targetClass = targetClasses[GetRandom(targetClasses.size())];
								targetClass->students.push_back(cls.students[i]);
								cls.students[i] = cls.students.back();
								cls.students.pop_back();
							}
						}
					}
				}

				cls.grade++;
				if (level < EDUCATION_POST) {
					int maxGrade;
					float continueRatio;
					float stayRatio;
					if (level == EDUCATION_PRIMARY) {
						maxGrade = 6;
						continueRatio = 0.98f;
						stayRatio = 0.99f;
					}
					if (level == EDUCATION_JUNIOR) {
						maxGrade = 3;
						continueRatio = 0.9f;
						stayRatio = 0.98f;
					}
					if (level == EDUCATION_SENIOR) {
						maxGrade = 3;
						continueRatio = 0.7f;
						stayRatio = 0.96f;
					}
					if (level == EDUCATION_COLLEGE) {
						maxGrade = 4;
						continueRatio = 0.3f;
						stayRatio = 0.92f;
					}

					if (cls.grade > maxGrade) {
						cls.students.resize(cls.students.size() * continueRatio);
						levelPotentials[level + 1].insert(levelPotentials[level + 1].end(), cls.students.begin(), cls.students.end());
						cls.students.clear();
					}
					else {
						float ratio = (100 - GetRandom((1.0f - stayRatio) * 100)) / 100.0f;
						for (int j = cls.students.size() * ratio; j < cls.students.size(); j++) {
							if(citizens[cls.students[j]]->GetEducationExperiences().size() > 0)
								citizens[cls.students[j]]->GetEducationExperiences().back().SetGraduate(false);
						}
						cls.students.resize(cls.students.size() * ratio);
					}
				}
				else {
					for (auto& student : cls.students) {
						if (cls.grade > 2 && GetRandom(7 - cls.grade) == 0) {
							student = cls.students.back();
							cls.students.pop_back();
						}
					}
				}
			}

			auto& classes = levelClasses[level];
			classes.erase(
				remove_if(classes.begin(), classes.end(),
					[](const SchoolClass& c) { return c.students.empty(); }),
				classes.end());
		}

		// 适龄小学生
		for (int i = 0; i < citizens.size(); i++) {
			int birthYear = citizens[i]->GetBirthday().GetYear();
			if (birthYear < year - 5) {
				if (GetRandom(9 + birthYear - year) == 0 && citizens[i]->GetEducationExperiences().size() == 0)
					levelPotentials[EDUCATION_PRIMARY].push_back(i);
			}
		}

		// 小学入学
		if (!levelPotentials[EDUCATION_PRIMARY].empty()) {
			int classCount = max(1, levelPotentials[EDUCATION_PRIMARY].size() / (20 + GetRandom(20)));
			if (classCount == 0)classCount = 1;

			int schoolCount = max(1, classCount / 5);
			vector<string> schoolNames;
			for (int i = 0; i < schoolCount; i++) {
				schoolNames.push_back("第" + to_string(i + 1) + "小学");
			}
			shuffle(levelPotentials[EDUCATION_PRIMARY].begin(), levelPotentials[EDUCATION_PRIMARY].end(), generator);
			int studentsPerClass = levelPotentials[EDUCATION_PRIMARY].size() / classCount;

			for (int i = 0; i < classCount; i++) {
				SchoolClass newClass;
				newClass.schoolName = schoolNames[i % schoolNames.size()];
				newClass.startYear = year;
				newClass.grade = 1;
				newClass.level = EDUCATION_PRIMARY;

				int startIdx = i * studentsPerClass;
				int endIdx = (i == classCount - 1) ? levelPotentials[EDUCATION_PRIMARY].size() : (i + 1) * studentsPerClass;
				for (int j = startIdx; j < endIdx; j++) {
					newClass.students.push_back(levelPotentials[EDUCATION_PRIMARY][j]);
				}

				levelClasses[EDUCATION_PRIMARY].push_back(newClass);
			}
			levelPotentials[EDUCATION_PRIMARY].clear();
		}

		// 初中入学
		if (!levelPotentials[EDUCATION_JUNIOR].empty()) {
			int classCount = max(1, levelPotentials[EDUCATION_JUNIOR].size() / (20 + GetRandom(20)));
			if (classCount == 0)classCount = 1;

			int schoolCount = max(1, classCount / 4);
			vector<string> schoolNames;
			for (int i = 0; i < schoolCount; i++) {
				schoolNames.push_back("第" + to_string(i + 1) + "初中");
			}

			shuffle(levelPotentials[EDUCATION_JUNIOR].begin(), levelPotentials[EDUCATION_JUNIOR].end(), generator);
			int studentsPerClass = levelPotentials[EDUCATION_JUNIOR].size() / classCount;

			for (int i = 0; i < classCount; i++) {
				SchoolClass newClass;
				newClass.schoolName = schoolNames[i % schoolNames.size()];
				newClass.startYear = year;
				newClass.grade = 1;
				newClass.level = EDUCATION_JUNIOR;

				int startIdx = i * studentsPerClass;
				int endIdx = (i == classCount - 1) ? levelPotentials[EDUCATION_JUNIOR].size() : (i + 1) * studentsPerClass;
				for (int j = startIdx; j < endIdx; j++) {
					newClass.students.push_back(levelPotentials[EDUCATION_JUNIOR][j]);
				}

				levelClasses[EDUCATION_JUNIOR].push_back(newClass);
			}
			levelPotentials[EDUCATION_JUNIOR].clear();
		}

		// 高中入学
		if (!levelPotentials[EDUCATION_SENIOR].empty()) {
			int classCount = max(1, levelPotentials[EDUCATION_SENIOR].size() / (30 + GetRandom(20)));
			if (classCount == 0)classCount = 1;

			int schoolCount = max(1, classCount / 4);
			vector<string> schoolNames;
			for (int i = 0; i < schoolCount; i++) {
				schoolNames.push_back("第" + to_string(i + 1) + "高中");
			}

			shuffle(levelPotentials[EDUCATION_SENIOR].begin(), levelPotentials[EDUCATION_SENIOR].end(), generator);
			int studentsPerClass = levelPotentials[EDUCATION_SENIOR].size() / classCount;

			for (int i = 0; i < classCount; i++) {
				SchoolClass newClass;
				newClass.schoolName = schoolNames[i % schoolNames.size()];
				newClass.startYear = year;
				newClass.grade = 1;
				newClass.level = EDUCATION_SENIOR;

				int startIdx = i * studentsPerClass;
				int endIdx = (i == classCount - 1) ? levelPotentials[EDUCATION_SENIOR].size() : (i + 1) * studentsPerClass;
				for (int j = startIdx; j < endIdx; j++) {
					newClass.students.push_back(levelPotentials[EDUCATION_SENIOR][j]);
				}

				levelClasses[EDUCATION_SENIOR].push_back(newClass);
			}
			levelPotentials[EDUCATION_SENIOR].clear();
		}

		// 大学入学
		if (!levelPotentials[EDUCATION_COLLEGE].empty()) {
			int majorCount = 5 + GetRandom(5);
			vector<string> schoolNames;
			for (int i = 0; i < majorCount; i++) {
				schoolNames.push_back("第" + to_string(i + 1) + "大学");
			}

			shuffle(levelPotentials[EDUCATION_COLLEGE].begin(), levelPotentials[EDUCATION_COLLEGE].end(), generator);
			int studentsPerMajor = levelPotentials[EDUCATION_COLLEGE].size() / majorCount;

			for (int i = 0; i < majorCount; i++) {
				SchoolClass newClass;
				newClass.schoolName = schoolNames[i];
				newClass.startYear = year;
				newClass.grade = 1;
				newClass.level = EDUCATION_COLLEGE;

				int startIdx = i * studentsPerMajor;
				int endIdx = (i == majorCount - 1) ? levelPotentials[EDUCATION_COLLEGE].size() : (i + 1) * studentsPerMajor;
				for (int j = startIdx; j < endIdx; j++) {
					newClass.students.push_back(levelPotentials[EDUCATION_COLLEGE][j]);
				}

				levelClasses[EDUCATION_COLLEGE].push_back(newClass);
			}
			levelPotentials[EDUCATION_COLLEGE].clear();
		}

		// 研究生入学
		if (!levelPotentials[EDUCATION_POST].empty()) {
			int majorCount = 3 + GetRandom(3);
			vector<string> schoolNames;
			for (int i = 0; i < majorCount; i++) {
				schoolNames.push_back("第" + to_string(i + 1) + "研究院");
			}

			shuffle(levelPotentials[EDUCATION_POST].begin(), levelPotentials[EDUCATION_POST].end(), generator);
			int studentsPerMajor = levelPotentials[EDUCATION_POST].size() / majorCount;

			for (int i = 0; i < majorCount; i++) {
				SchoolClass newClass;
				newClass.schoolName = schoolNames[i];
				newClass.startYear = year;
				newClass.grade = 1;
				newClass.level = EDUCATION_POST;

				int startIdx = i * studentsPerMajor;
				int endIdx = (i == majorCount - 1) ? levelPotentials[EDUCATION_POST].size() : (i + 1) * studentsPerMajor;
				for (int j = startIdx; j < endIdx; j++) {
					newClass.students.push_back(levelPotentials[EDUCATION_POST][j]);
				}

				levelClasses[EDUCATION_POST].push_back(newClass);
			}
			levelPotentials[EDUCATION_POST].clear();
		}
	}
	for (auto citizen : citizens) {
		citizen->ExpComposition();
	}

	debugf("generate educations.\n");
}

int relationCdf(int x, int max) {
	float y = log(log(x + 3)) / log(log(40000));
	if (y < 0.5f) {
		y = -0.75 / (4 * y + 1) + 0.75;
	}
	else {
		y = -0.75 / (4 * y - 5) + 0.25;
	}
	return exp(exp(log(log(40000)) * y));
}

void Populace::GenerateEmotions() {
	for (auto citizen : citizens) {
		// 计算本人情感经历范围
		int birthYear = citizen->GetBirthday().GetYear();
		int currentAge = time.GetYear() - birthYear;
		if (currentAge < 16) continue;

		Time startBound = citizen->GetBirthday() + Time(16, 1, 1);
		Time endBound;
		shared_ptr<Person> spouse = citizen->GetSpouse();
		if (spouse) {
			endBound = citizen->GetMarryday();
		}
		else {
			endBound = time;
		}
		if (startBound >= endBound) continue;

		int maxRelationships = min(10, (endBound - startBound).GetYear() / 3 + 1);
		int relationshipCount = GetRandom(maxRelationships + 1);
		relationshipCount = max(relationshipCount - citizen->GetEmotionExperiences().size(), 0);

		// 随机生成指定段数的经历
		vector<EmotionExperience> newEmotions;
		vector<pair<Time, Time>> allocatedPeriods;
		for (int i = 0; i < relationshipCount; i++) {
			Time startTime, endTime;
			bool validPeriod = false;
			int attempts = 0;

			// 首先生成一段符合本人时间段的经历
			while (!validPeriod && attempts < 100) {
				attempts++;

				startTime = GetRandom(startBound, endBound);

				int minDuration = 1;
				int maxDuration = Time::DaysBetween(startTime, endBound) + 1;
				int durationDays = minDuration + GetRandom(maxDuration - minDuration + 1, relationCdf);
				endTime = startTime;
				endTime.AddDays(durationDays - 1);
				if (endTime > endBound) endTime = endBound;

				validPeriod = true;
				for (const auto& period : allocatedPeriods) {
					if (!(endTime < period.first || startTime > period.second)) {
						validPeriod = false;
						break;
					}
				}

				if (validPeriod) {
					for (const auto& exp : citizen->GetEmotionExperiences()) {
						if (!(endTime < exp.GetBeginTime() || startTime > exp.GetEndTime())) {
							validPeriod = false;
							break;
						}
					}
				}
			}
			if (!validPeriod) continue;

			// 随机寻找伴侣并判断该经历是否符合其时间段
			shared_ptr<Person> partner = nullptr;
			int candidateAttempts = 0;
			while (!partner && candidateAttempts < 100) {
				candidateAttempts++;

				int idx = GetRandom(citizens.size());
				shared_ptr<Person> candidate = citizens[idx];
				if (candidate->GetGender() == citizen->GetGender())continue;
				if (candidate == citizen) continue;

				bool isCloseRelative = false;
				if (candidate == citizen->GetSpouse())isCloseRelative = true;
				if (citizen->GetFather()) {
					for (auto relative : citizen->GetFather()->GetChilds()) {
						if (candidate == relative) {
							isCloseRelative = true;
							break;
						}
					}
				}
				if (citizen->GetMother()) {
					for (auto relative : citizen->GetMother()->GetChilds()) {
						if (candidate == relative) {
							isCloseRelative = true;
							break;
						}
					}
				}
				if (isCloseRelative) continue;

				int candidateBirthYear = candidate->GetBirthday().GetYear();
				int candidateAge = startTime.GetYear() - candidateBirthYear;
				int ageDiff = abs(birthYear - candidateBirthYear);
				if (candidateAge < 16 || ageDiff > 10) continue;

				bool timeAvailable = true;
				for (const auto& exp : candidate->GetEmotionExperiences()) {
					if (!(endTime < exp.GetBeginTime() || startTime > exp.GetEndTime())) {
						timeAvailable = false;
						break;
					}
				}
				if (!timeAvailable) continue;

				shared_ptr<Person> candidateSpouse = candidate->GetSpouse();
				if (candidateSpouse) {
					Time marryTime = candidate->GetMarryday();
					if (marryTime < endTime) {
						continue;
					}
				}
				partner = candidate;
			}
			if (!partner) continue;
			if (startTime > endTime)continue;

			// 写入经历
			EmotionExperience emotionExp;
			emotionExp.SetPerson(partner);
			emotionExp.SetTime(startTime, endTime);
			newEmotions.push_back(emotionExp);
			allocatedPeriods.emplace_back(startTime, endTime);

			EmotionExperience partnerExp;
			partnerExp.SetPerson(citizen);
			partnerExp.SetTime(startTime, endTime);
			partner->AddEmotionExperience(partnerExp);
		}

		// 将临时经历全部写入本人经历
		for (const auto& exp : newEmotions) {
			citizen->AddEmotionExperience(exp);
		}

		// 四成未婚市民存在正在进行的恋爱
		if (!spouse && GetRandom(100) < 40) {
			shared_ptr<Person> currentPartner = nullptr;
			int candidateAttempts = 0;

			Time marrigeBegin = citizen->GetBirthday() + Time(16, 1, 1);
			for (auto experience : citizen->GetEmotionExperiences()) {
				if (experience.GetEndTime() > marrigeBegin)
					marrigeBegin = experience.GetEndTime();
			}
			Time marrigeTime = GetRandom(marrigeBegin, time);
			while (!currentPartner && candidateAttempts < 100) {
				candidateAttempts++;

				int idx = GetRandom(citizens.size());
				shared_ptr<Person> candidate = citizens[idx];
				if (candidate->GetGender() == citizen->GetGender())continue;
				if (candidate == citizen || candidate->GetSpouse()) continue;

				bool isCloseRelative = false;
				if (candidate == citizen->GetSpouse())isCloseRelative = true;
				if (citizen->GetFather()) {
					for (auto relative : citizen->GetFather()->GetChilds()) {
						if (candidate == relative) {
							isCloseRelative = true;
							break;
						}
					}
				}
				if (citizen->GetMother()) {
					for (auto relative : citizen->GetMother()->GetChilds()) {
						if (candidate == relative) {
							isCloseRelative = true;
							break;
						}
					}
				}
				if (isCloseRelative) continue;

				int candidateBirthYear = candidate->GetBirthday().GetYear();
				int candidateAge = time.GetYear() - candidateBirthYear;
				int ageDiff = abs(currentAge - candidateAge);
				if (ageDiff > 10) continue;

				bool timeAvailable = true;
				for (const auto& exp : candidate->GetEmotionExperiences()) {
					if (exp.GetEndTime() >= marrigeTime) {
						timeAvailable = false;
						break;
					}
				}
				if (!timeAvailable) continue;

				currentPartner = candidate;
			}

			if (currentPartner) {
				EmotionExperience currentExp;
				currentExp.SetPerson(currentPartner);
				currentExp.SetTime(marrigeTime, time);

				citizen->AddEmotionExperience(currentExp);

				EmotionExperience partnerExp;
				partnerExp.SetPerson(citizen);
				partnerExp.SetTime(marrigeTime, time);
				currentPartner->AddEmotionExperience(partnerExp);
			}
		}
	}

	debugf("generate emotions.\n");
}

void Populace::GenerateJobs() {

}

void Populace::GenerateAcquaintances() {

}
