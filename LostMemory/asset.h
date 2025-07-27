#pragma once
#include <string>

enum ASSET_TYPE {
	ASSET_ESTATE, // 房产
	ASSET_VEHICLE, // 载具
	ASSET_JEWERY, // 珠宝
	ASSET_ART, // 艺术品
	ASSET_ELECTRONIC, // 电子产品
	ASSET_STOCK, // 股票
	ASSET_ANTIQUE // 古玩
};

class Asset {
public:
	Asset(ASSET_TYPE type, void* object) : type(type), object(object) {};

private:
	ASSET_TYPE type;
	void* object;
	std::string name;
	int value;
};

class EstateAsset : public Asset {
public:
	EstateAsset(void* object) : Asset(ASSET_ESTATE, object) {}

private:

};

class VehicleAsset : public Asset {
public:
	VehicleAsset(void* object) : Asset(ASSET_VEHICLE, object) {}

private:

};

class JeweryAsset : public Asset {
public:
	JeweryAsset(void* object) : Asset(ASSET_JEWERY, object) {}

private:

};

class ArtAsset : public Asset {
public:
	ArtAsset(void* object) : Asset(ASSET_ART, object) {}

private:

};

class ElectronicAsset : public Asset {
public:
	ElectronicAsset(void* object) : Asset(ASSET_ELECTRONIC, object) {}

private:

};

class StockAsset : public Asset {
public:
	StockAsset(void* object) : Asset(ASSET_STOCK, object) {}

private:

};

class AntiqueAsset : public Asset {
public:
	AntiqueAsset(void* object) : Asset(ASSET_ANTIQUE, object) {}

private:

};