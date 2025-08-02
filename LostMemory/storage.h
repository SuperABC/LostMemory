#pragma once

#include "item.h"

enum STORAGE_TYPE {
	STORAGE_BACKPACK,
	STORAGE_BAG,
	STORAGE_WALLET,
	STORAGE_PACKAGE,
	STORAGE_LUGGAGE,
	STORAGE_BOX,
	STORAGE_WAREHOUSE,
	STORAGE_CAR,
	STORAGE_TRUCK
};

class Storage {
public:
	Storage(STORAGE_TYPE type) : type(type) {};

private:
	STORAGE_TYPE type;
	std::string name;
	int capacity;
};

class BackpackStorage : public Storage {
public:
	BackpackStorage() : Storage(STORAGE_BACKPACK) {}

private:

};

class BagStorage : public Storage {
public:
	BagStorage() : Storage(STORAGE_BAG) {}

private:

};

class WalletStorage : public Storage {
public:
	WalletStorage() : Storage(STORAGE_WALLET) {}

private:

};

class PackageStorage : public Storage {
public:
	PackageStorage() : Storage(STORAGE_PACKAGE) {}

private:

};

class LuggageStorage : public Storage {
public:
	LuggageStorage() : Storage(STORAGE_LUGGAGE) {}

private:

};

class BoxStorage : public Storage {
public:
	BoxStorage() : Storage(STORAGE_BOX) {}

private:

};

class WarehouseStorage : public Storage {
public:
	WarehouseStorage() : Storage(STORAGE_WAREHOUSE) {}

private:

};

class CarStorage : public Storage {
public:
	CarStorage() : Storage(STORAGE_CAR) {}

private:

};

class TruckStorage : public Storage {
public:
	TruckStorage() : Storage(STORAGE_TRUCK) {}

private:

};
