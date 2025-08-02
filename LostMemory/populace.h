#pragma once

#include "person.h"

#include <vector>
#include <unordered_map>


class Populace {
public:
	Populace() = default;
	~Populace();

	// 初始化市民
	void Init(int num);

	// 释放空间
	void Destroy();

	// 时钟前进
	void Tick();

	// 输出当前市民统计信息
	void Print();

	// 保存/加载地图
	void Load(std::string path);
	void Save(std::string path);

	// 获取当前时间
	Time GetTime();

	// 获取全部市民
	std::vector<Person*>& GetCitizens();

private:
	Time time;

	std::vector<Person*> citizens;
	std::unordered_map<int, Person*> phoneRoll;

	// 生成市民和经历
	void GenerateCitizens(int num);
	void GeneratePhones();
	void GenerateEducations();
	void GenerateEmotions();
	void GenerateJobs();
	void GenerateAcquaintances();
};