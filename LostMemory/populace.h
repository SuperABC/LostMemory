#pragma once

#include "person.h"

#include <vector>
#include <unordered_map>


class Populace {
public:
	Populace() = default;
	~Populace();

	void Init(int num);
	void Destroy();
	void Tick();
	void Print();

	void Load(std::string path);
	void Save(std::string path);

	Time GetTime();
	std::vector<Person*>& GetCitizens();

private:
	Time time;

	std::vector<Person*> citizens;

	std::unordered_map<std::string, Person*> phoneRoll;
};