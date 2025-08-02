#pragma once

#include <string>

enum ITEM_TYPE {
	ITEM_BACKPACK,
	ITEM_BAG,
	ITEM_WALLET,
	ITEM_LUGGAGE,
	ITEM_BOX,
	ITEM_BIKE,
	ITEM_KEY,
	ITEM_PHONE,
	ITEM_CHARGER,
	ITEM_BATTERY,
	ITEM_UMBRELLA,
	ITEM_FIRE,
	ITEM_PEN,
	ITEM_WATCH,
	ITEM_FLASH,
	ITEM_GLOVES,
	ITEM_HAT,
	ITEM_MASK,
	ITEM_BOTTLE,
	ITEM_MIRROR,
	ITEM_COMB,
	ITEM_HAMMER,
	ITEM_SCREW,
	ITEM_SCISSOR,
	ITEM_SAW,
	ITEM_SHOVEL,
	ITEM_LADDER,
	ITEM_ROLL,
	ITEM_TAPE,
	ITEM_LOCK,
	ITEM_COMPASS,
	ITEM_RULLER,
	ITEM_DRILL,
	ITEM_TELESCOPE,
	ITEM_LAPTOP,
	ITEM_EARPHONE,
	ITEM_DRONE,
	ITEM_UPAN,
	ITEM_HELMET,
	ITEM_ID,
	ITEM_LICENSE,
	ITEM_CARD,
	ITEM_WEAPON,
	ITEM_BANDAGE,
	ITEM_PAINKILLER,
	ITEM_FOOD,
	ITEM_DRINK,
	ITEM_POISON,
	ITEM_CONDOM,
	ITEM_FILE,
	ITEM_INSTRUMENT,
	ITEM_BALL,
	ITEM_SPECIAL
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
