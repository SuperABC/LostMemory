#include "person.h"

void Person::AddRelative(RELATIVE_TYPE type, Person* person) {
	relatives.push_back(std::make_pair(type, person));
}

Person* Person::GetFather() {
	for (auto relative : relatives) {
		if (relative.first == RELATIVE_FATHER)return relative.second;
	}
}

Person* Person::GetMother() {
	for (auto relative : relatives) {
		if (relative.first == RELATIVE_MOTHER)return relative.second;
	}
}

Person* Person::GetSpouse() {
	for (auto relative : relatives) {
		if (relative.first == RELATIVE_WIFE || relative.first == RELATIVE_HUSBAND)return relative.second;
	}

	return nullptr;
}

std::vector<Person*> Person::GetChilds() {
	std::vector<Person*>childs;
	for (auto relative : relatives) {
		if (relative.first == RELATIVE_SON || relative.first == RELATIVE_DAUGHTER)childs.push_back(relative.second);
	}
	return childs;
}

void Person::AddPhone(std::string phone) {
	phones.push_back(phone);
}

void Person::AddAddress(Room* room) {
	addresses.push_back(room);
}

std::vector<Room*>& Person::GetAddresses() {
	return addresses;
}

void Person::AddAsset(Asset* asset) {
	assets.push_back(asset);
}

std::vector<Asset*>& Person::GetAssets() {
	return assets;
}
