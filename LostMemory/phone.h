#pragma once
#include <string>
#include <vector>

class App {
public:
	App() = default;

private:
	std::string name;
};

class Phone {
public:
	Phone() = default;

private:
	std::vector<App*> apps;
};