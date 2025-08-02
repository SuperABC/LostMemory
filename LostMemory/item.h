#pragma once

#include <string>

enum ITEM_TYPE {
	ITEM_BACKPACK, // 背包
	ITEM_BAG, // 袋子
	ITEM_WALLET, // 钱包
	ITEM_LUGGAGE, // 行李箱
	ITEM_BOX, // 盒子
	ITEM_BIKE, // 自行车
	ITEM_KEY, // 钥匙
	ITEM_PHONE, // 手机
	ITEM_CHARGER, // 充电器
	ITEM_BATTERY, // 电池
	ITEM_UMBRELLA, // 雨伞
	ITEM_FIRE, // 打火机
	ITEM_PEN, // 笔
	ITEM_WATCH, // 手表
	ITEM_FLASH, // 手电
	ITEM_GLOVES, // 手套
	ITEM_HAT, // 帽子
	ITEM_MASK, // 口罩
	ITEM_BOTTLE, // 瓶子
	ITEM_MIRROR, // 镜子
	ITEM_COMB, // 梳子
	ITEM_HAMMER, // 锤子
	ITEM_SCREW, // 螺丝刀
	ITEM_SCISSOR, // 剪刀
	ITEM_SAW, // 锯子
	ITEM_SHOVEL, // 铲子
	ITEM_LADDER, // 梯子
	ITEM_ROLL, // 名单
	ITEM_TAPE, // 胶带
	ITEM_LOCK, // 锁
	ITEM_COMPASS, // 指南针
	ITEM_RULLER, // 尺子
	ITEM_DRILL, // 电钻
	ITEM_TELESCOPE, // 望远镜
	ITEM_LAPTOP, // 笔记本
	ITEM_EARPHONE, // 耳机
	ITEM_DRONE, // 无人机
	ITEM_UPAN, // U盘
	ITEM_HELMET, // 头盔
	ITEM_ID, // 身份证
	ITEM_LICENSE, // 证件
	ITEM_CARD, // 银行卡
	ITEM_WEAPON, // 武器
	ITEM_BANDAGE, // 绷带
	ITEM_PAINKILLER, // 止疼药
	ITEM_FOOD, // 食物
	ITEM_DRINK, // 饮品
	ITEM_POISON, // 毒药
	ITEM_CONDOM, // 避孕套
	ITEM_FILE, // 文件
	ITEM_INSTRUMENT, // 乐器
	ITEM_BALL, // 球
	ITEM_SPECIAL, // 特殊
	ITEM_END
};

class Item {
public:
	Item(ITEM_TYPE type) : type(type) {};

private:
	ITEM_TYPE type;
	std::string name;
	float volume;
};

class KeyItem : public Item {
public:
	KeyItem() : Item(ITEM_KEY) {}

private:

};

class WalletItem : public Item {
public:
	WalletItem() : Item(ITEM_WALLET) {}

private:

};

class PhoneItem : public Item {
public:
	PhoneItem() : Item(ITEM_PHONE) {}

private:

};

class ChargerItem : public Item {
public:
	ChargerItem() : Item(ITEM_CHARGER) {}

private:

};

class BatteryItem : public Item {
public:
	BatteryItem() : Item(ITEM_BATTERY) {}

private:

};

class UmbrellaItem : public Item {
public:
	UmbrellaItem() : Item(ITEM_UMBRELLA) {}

private:

};

class FireItem : public Item {
public:
	FireItem() : Item(ITEM_FIRE) {}

private:

};

class PenItem : public Item {
public:
	PenItem() : Item(ITEM_PEN) {}

private:

};

class WatchItem : public Item {
public:
	WatchItem() : Item(ITEM_WATCH) {}

private:

};

class FlashItem : public Item {
public:
	FlashItem() : Item(ITEM_FLASH) {}

private:

};

class GlovesItem : public Item {
public:
	GlovesItem() : Item(ITEM_GLOVES) {}

private:

};

class HatItem : public Item {
public:
	HatItem() : Item(ITEM_HAT) {}

private:

};

class MaskItem : public Item {
public:
	MaskItem() : Item(ITEM_MASK) {}

private:

};

class BottleItem : public Item {
public:
	BottleItem() : Item(ITEM_BOTTLE) {}

private:

};

class MirrorItem : public Item {
public:
	MirrorItem() : Item(ITEM_MIRROR) {}

private:

};

class CombItem : public Item {
public:
	CombItem() : Item(ITEM_COMB) {}

private:

};

class HammerItem : public Item {
public:
	HammerItem() : Item(ITEM_HAMMER) {}

private:

};

class ScrewItem : public Item {
public:
	ScrewItem() : Item(ITEM_SCREW) {}

private:

};

class ScissorItem : public Item {
public:
	ScissorItem() : Item(ITEM_SCISSOR) {}

private:

};

class SawItem : public Item {
public:
	SawItem() : Item(ITEM_SAW) {}

private:

};

class ShovelItem : public Item {
public:
	ShovelItem() : Item(ITEM_SHOVEL) {}

private:

};

class LadderItem : public Item {
public:
	LadderItem() : Item(ITEM_LADDER) {}

private:

};

class RollItem : public Item {
public:
	RollItem() : Item(ITEM_ROLL) {}

private:

};

class TapeItem : public Item {
public:
	TapeItem() : Item(ITEM_TAPE) {}

private:

};

class LockItem : public Item {
public:
	LockItem() : Item(ITEM_LOCK) {}

private:

};

class CompassItem : public Item {
public:
	CompassItem() : Item(ITEM_COMPASS) {}

private:

};

class RullerItem : public Item {
public:
	RullerItem() : Item(ITEM_RULLER) {}

private:

};

class DrillItem : public Item {
public:
	DrillItem() : Item(ITEM_DRILL) {}

private:

};

class TelescopeItem : public Item {
public:
	TelescopeItem() : Item(ITEM_TELESCOPE) {}

private:

};

class LaptopItem : public Item {
public:
	LaptopItem() : Item(ITEM_LAPTOP) {}

private:

};

class EarphoneItem : public Item {
public:
	EarphoneItem() : Item(ITEM_EARPHONE) {}

private:

};

class DroneItem : public Item {
public:
	DroneItem() : Item(ITEM_DRONE) {}

private:

};

class UpanItem : public Item {
public:
	UpanItem() : Item(ITEM_UPAN) {}

private:

};

class HelmetItem : public Item {
public:
	HelmetItem() : Item(ITEM_HELMET) {}

private:

};

class IDItem : public Item {
public:
	IDItem() : Item(ITEM_ID) {}

private:

};

class LicenseItem : public Item {
public:
	LicenseItem() : Item(ITEM_LICENSE) {}

private:

};

class CardItem : public Item {
public:
	CardItem() : Item(ITEM_CARD) {}

private:

};

class WeaponItem : public Item {
public:
	WeaponItem() : Item(ITEM_WEAPON) {}

private:

};

class BandageItem : public Item {
public:
	BandageItem() : Item(ITEM_BANDAGE) {}

private:

};

class PainkillerItem : public Item {
public:
	PainkillerItem() : Item(ITEM_PAINKILLER) {}

private:

};

class FoodItem : public Item {
public:
	FoodItem() : Item(ITEM_FOOD) {}

private:

};

class DrinkItem : public Item {
public:
	DrinkItem() : Item(ITEM_DRINK) {}

private:

};

class PoisonItem : public Item {
public:
	PoisonItem() : Item(ITEM_POISON) {}

private:

};

class CondomItem : public Item {
public:
	CondomItem() : Item(ITEM_CONDOM) {}

private:

};

class FileItem : public Item {
public:
	FileItem() : Item(ITEM_FILE) {}

private:

};

class InstrumentItem : public Item {
public:
	InstrumentItem() : Item(ITEM_INSTRUMENT) {}

private:

};

class SpecialItem : public Item {
public:
	SpecialItem() : Item(ITEM_SPECIAL) {}

private:

};
