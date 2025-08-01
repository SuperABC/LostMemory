#pragma once
#include <vector>

enum COMMODITY_CATEGORY {
	COMMODITY_CLOTHES, //衣服
	COMMODITY_INGREDIENT, //食材
	COMMODITY_BUILDING, //建材
	COMMODITY_FURNITURE, //家具
	COMMODITY_ELECTRICAL, //电器
	COMMODITY_TRASPORT, //交通
	COMMODITY_RESOURCE, //资源
	COMMODITY_DAILY, //日用品
	COMMODITY_STATIONARY, //文具
	COMMODITY_MACHINE, //机械
	COMMODITY_ELECTRON, //电子
	COMMODITY_COMPONENT, //配件
	COMMODITY_MAKEUP, //化妆品
	COMMODITY_JEWELRY, //珠宝
	COMMODITY_WEAPON, //武器
	COMMODITY_ART, //艺术品
	COMMODITY_MEDICINE, //药品
};

enum COMMODITY_TYPE {
	//衣服
	COMMODITY_SHORTSHIRT,
	COMMODITY_LONGSHIRT,
	COMMODITY_SWEATER,
	COMMODITY_HOODIE,
	COMMODITY_VEST,
	COMMODITY_PANTS,
	COMMODITY_CHINOS,
	COMMODITY_JOGGERS,
	COMMODITY_JEANS,
	COMMODITY_SKIRT,
	COMMODITY_UPPERSUIT,
	COMMODITY_UPPERUNIFORM,
	COMMODITY_UPPERTHERMAL,
	COMMODITY_LOWERSUIT,
	COMMODITY_LOWERUNIFORM,
	COMMODITY_LOWERTHERMAL,
	COMMODITY_JACKET,
	COMMODITY_OVERCOAT,
	COMMODITY_RAINCOAT,
	COMMODITY_LEATHERCOAT,
	COMMODITY_FURCOAT,
	COMMODITY_VELVET,
	COMMODITY_DRESS,
	COMMODITY_QIPAO,
	COMMODITY_SWIMMALE,
	COMMODITY_SWIMFEMALE,
	COMMODITY_BRA,
	COMMODITY_UNDERWEAR,
	COMMODITY_GLOVES,
	COMMODITY_SCARF,
	COMMODITY_CAP,
	COMMODITY_HAT,
	COMMODITY_SNEAKERS,
	COMMODITY_BOOTS,
	COMMODITY_LEATHERSHOES,
	COMMODITY_HIGHSHOES,
	COMMODITY_SLIPPERS,
	COMMODITY_TIE,
	COMMODITY_MASK,

	//食材
	COMMODITY_APPLE,
	COMMODITY_BANANA,
	COMMODITY_ORANGE,
	COMMODITY_STRAWBERRY,
	COMMODITY_GRAPE,
	COMMODITY_WATERMELON,
	COMMODITY_PEACH,
	COMMODITY_PEAR,
	COMMODITY_LEMON,
	COMMODITY_MANGO,
	COMMODITY_PINEAPPLE,
	COMMODITY_CHERRY,
	COMMODITY_BLUBERRY,
	COMMODITY_KIWI,
	COMMODITY_COCONUT,
	COMMODITY_LITCHI,
	COMMODITY_DURIAN,
	COMMODITY_CABBAGE,
	COMMODITY_CARROT,
	COMMODITY_RADISH,
	COMMODITY_POTATO,
	COMMODITY_TOMATO,
	COMMODITY_ONION,
	COMMODITY_LETTUCE,
	COMMODITY_CUCUMBER,
	COMMODITY_SPINACH,
	COMMODITY_BROCCOLI,
	COMMODITY_CAULIFLOWER,
	COMMODITY_EGGPLANT,
	COMMODITY_PEPPER,
	COMMODITY_MUSHROOM,
	COMMODITY_CORN,
	COMMODITY_BEAN,
	COMMODITY_PUMPKIN,
	COMMODITY_SEAWEED,
	COMMODITY_PORK,
	COMMODITY_BEEF,
	COMMODITY_CHICKEN,
	COMMODITY_EGG,
	COMMODITY_LAMB,
	COMMODITY_DUCK,
	COMMODITY_HONEY,
	COMMODITY_SAUSAGE,
	COMMODITY_HAM,
	COMMODITY_FISH,
	COMMODITY_SHRIMP,
	COMMODITY_CRAB,
	COMMODITY_LOBSTER,
	COMMODITY_OYSTER,
	COMMODITY_SHELL,
	COMMODITY_SQUID,
	COMMODITY_RICE,
	COMMODITY_FLOUR,
	COMMODITY_COCO,
	COMMODITY_WATER,
	COMMODITY_MILK,
	COMMODITY_TEA,
	COMMODITY_COFFEE,
	COMMODITY_JUICE,
	COMMODITY_SODA,
	COMMODITY_BEAR,
	COMMODITY_WINE,
	COMMODITY_BAIJIU,
	COMMODITY_SALT,
	COMMODITY_SUGAR,
	COMMODITY_SOYSAUCE,
	COMMODITY_VINEGAR,
	COMMODITY_OIL,
	COMMODITY_CHILI,
	COMMODITY_MSG,
	COMMODITY_CURRY,
	COMMODITY_ICE,

	//建材
	COMMODITY_BRICK,
	COMMODITY_CONCRETE,
	COMMODITY_STONE,
	COMMODITY_TIMBER,
	COMMODITY_STEEL,
	COMMODITY_CEMENT,
	COMMODITY_PLASTER,
	COMMODITY_PLANK,
	COMMODITY_PAINT,
	COMMODITY_TILE,
	COMMODITY_MARBLE,
	COMMODITY_GLASS,
	COMMODITY_FLOOR,
	COMMODITY_ASPHALT,
	COMMODITY_RUBBER,
	COMMODITY_CLAY,
	COMMODITY_DOOR,
	COMMODITY_WINDOW,
	COMMODITY_PIPE,
	COMMODITY_CARBON,

	//家具
	COMMODITY_CARPET,
	COMMODITY_SOFA,
	COMMODITY_SHELF,
	COMMODITY_CHAIR,
	COMMODITY_TABLE,
	COMMODITY_DESK,
	COMMODITY_BED,
	COMMODITY_CABINET,
	COMMODITY_MIRROR,
	COMMODITY_WARDROBE,
	COMMODITY_COOKTOP,
	COMMODITY_BASIN,
	COMMODITY_TOILET,
	COMMODITY_BATHTUB,
	COMMODITY_SHOWER,
	COMMODITY_CLOCK,
	COMMODITY_LAMP,
	COMMODITY_CHANDELIER,
	COMMODITY_CURTAIN,

	//电器
	COMMODITY_VENTILATOR,
	COMMODITY_FRIDGE,
	COMMODITY_MICROWAVE,
	COMMODITY_OVEN,
	COMMODITY_INDUCTION,
	COMMODITY_DISHWASHER,
	COMMODITY_JUCIER,
	COMMODITY_BREADMAKER,
	COMMODITY_LOUNDRY,
	COMMODITY_CLOTHDRYER,
	COMMODITY_VACUMMER,
	COMMODITY_STEAMER,
	COMMODITY_FLOORROBOT,
	COMMODITY_HIARDRYER,
	COMMODITY_SHAVER,
	COMMODITY_AC,
	COMMODITY_EFAN,
	COMMODITY_HUMIDIFIER,
	COMMODITY_DEHUMIDIFIER,
	COMMODITY_HEATER,
	COMMODITY_IRON,
	COMMODITY_SEWING,
	COMMODITY_SCALAR,
	COMMODITY_GEYSER,
	COMMODITY_KETTLE,

	//交通
	COMMODITY_BIKE,
	COMMODITY_SCOOTER,
	COMMODITY_MOTOR,
	COMMODITY_SEDAN,
	COMMODITY_BUS,
	COMMODITY_TRUCK,
	COMMODITY_VAN,
	COMMODITY_BUSINESSCAR,
	COMMODITY_RV,
	COMMODITY_METRO,
	COMMODITY_TRAIN,
	COMMODITY_TRAM,
	COMMODITY_BOAT,
	COMMODITY_YACHT,
	COMMODITY_FERRY,
	COMMODITY_SHIP,
	COMMODITY_SUBMARINE,
	COMMODITY_PLANE,
	COMMODITY_HELICOPTER,
	COMMODITY_GLIDER,
	COMMODITY_SHUTTLE,

	//资源
	COMMODITY_COAL,
	COMMODITY_ORE,
	COMMODITY_QUARTZ,
	COMMODITY_SULFUR,
	COMMODITY_CRYSTAL,
	COMMODITY_LOG,
	COMMODITY_BAMBOO,
	COMMODITY_RESIN,
	COMMODITY_HERBS,
	COMMODITY_COTTON,
	COMMODITY_CURDE,
	COMMODITY_NATURALGAS,
	COMMODITY_URANIUM,
	COMMODITY_ROCK,
	COMMODITY_SAND,
	COMMODITY_PELT,
	COMMODITY_CLOTH,
	COMMODITY_LEATHER,
	COMMODITY_WOOL,
	COMMODITY_BONE,
	COMMODITY_FEATHER,

	//日用品
	COMMODITY_BOWL,
	COMMODITY_PLATE,
	COMMODITY_CHOPSTICKS,
	COMMODITY_SPOON,
	COMMODITY_KNIFE,
	COMMODITY_FORK,
	COMMODITY_CUP,
	COMMODITY_POT,
	COMMODITY_SPATULA,
	COMMODITY_BOARD,
	COMMODITY_OPENER,
	COMMODITY_CONTAINER,
	COMMODITY_COMB,
	COMMODITY_TOOTHBRUSH,
	COMMODITY_TOOTHPASTE,
	COMMODITY_TOWEL,
	COMMODITY_SOAP,
	COMMODITY_SHAMPOO,
	COMMODITY_SHOWERGEM,
	COMMODITY_TISSUE,
	COMMODITY_RAZOR,
	COMMODITY_BROOM,
	COMMODITY_MOP,
	COMMODITY_TRASHCAN,
	COMMODITY_RAG,
	COMMODITY_DETERGENT,
	COMMODITY_LOUNDRYPOWDER,
	COMMODITY_LOUNDRYGEM,
	COMMODITY_PILLOW,
	COMMODITY_QUILT,
	COMMODITY_BEDSHEET,
	COMMODITY_MATRESS,
	COMMODITY_ALARM,
	COMMODITY_HANGER,
	COMMODITY_NAIL,
	COMMODITY_SCREW,
	COMMODITY_BOLT,
	COMMODITY_HAMMER,
	COMMODITY_UMBRELLA,
	COMMODITY_KEY,
	COMMODITY_CANDLE,
	COMMODITY_LIGHTER,
	COMMODITY_MAGNIFYING,
	COMMODITY_FLASHLIGHT,
	COMMODITY_BELT,
	COMMODITY_HELMET,
	COMMODITY_GLASSES,
	COMMODITY_FILE,

	//文具
	COMMODITY_PEN,
	COMMODITY_PENCIL,
	COMMODITY_CHALK,
	COMMODITY_CRAYON,
	COMMODITY_BRUSH,
	COMMODITY_NOTEBOOK,
	COMMODITY_PAPER,
	COMMODITY_ERASER,
	COMMODITY_STAPLER,
	COMMODITY_SCISSORS,
	COMMODITY_FOLDER,
	COMMODITY_STICKY,
	COMMODITY_TAPE,
	COMMODITY_GLUE,
	COMMODITY_RULER,
	COMMODITY_BOOKMARK,
	COMMODITY_STAMP,
	COMMODITY_WATERCOLOR,
	COMMODITY_PALETTE,

	//机械
	COMMODITY_DRILL,
	COMMODITY_CHAINSAW,
	COMMODITY_GRINDER,
	COMMODITY_WELDING,
	COMMODITY_LATHE,
	COMMODITY_3DPRINTER,
	COMMODITY_EXCAVATOR,
	COMMODITY_BULLDOZER,
	COMMODITY_FORKLIFT,
	COMMODITY_CRANE,
	COMMODITY_ROLLER,
	COMMODITY_TOWER,
	COMMODITY_TRACTOR,
	COMMODITY_HARVESTER,
	COMMODITY_SEEDER,
	COMMODITY_IRRIGATOR,
	COMMODITY_CONVEYOR,
	COMMODITY_BLADE,

	//电子
	COMMODITY_TV,
	COMMODITY_PROJECTOR,
	COMMODITY_SPEAKER,
	COMMODITY_MICROPHONE,
	COMMODITY_PLAYSTATION,
	COMMODITY_EARBUDS,
	COMMODITY_DESKTOP,
	COMMODITY_LAPTOP,
	COMMODITY_TABLET,
	COMMODITY_TELEPHONE,
	COMMODITY_PRINTER,
	COMMODITY_SCANNER,
	COMMODITY_ROUTER,
	COMMODITY_MONITOR,
	COMMODITY_SCREEN,
	COMMODITY_CAMERA,
	COMMODITY_CHARGER,
	COMMODITY_MOBILE,
	COMMODITY_WATCH,
	COMMODITY_CALCULATOR,
	COMMODITY_POWERBANK,
	COMMODITY_USB,
	COMMODITY_EXTENSION,
	COMMODITY_DRONE,

	//配件
	COMMODITY_CPU,
	COMMODITY_GPU,
	COMMODITY_RAM,
	COMMODITY_DISK,
	COMMODITY_PSU,
	COMMODITY_COOLING,
	COMMODITY_BATTERY,
	COMMODITY_CAPACITOR,
	COMMODITY_RESISTOR,
	COMMODITY_TRANSISTOR,
	COMMODITY_DIODE,
	COMMODITY_IC,
	COMMODITY_SENSOR,
	COMMODITY_GENERATOR,
	COMMODITY_EMOTOR,
	COMMODITY_GEAR,
	COMMODITY_BEARING,
	COMMODITY_PISTON,
	COMMODITY_PUMP,
	COMMODITY_TURBINE,
	COMMODITY_SPRING,
	COMMODITY_WIRE,
	COMMODITY_NETCABLE,
	COMMODITY_OPTICCABLE,
	COMMODITY_PLUG,
	COMMODITY_RELAY,
	COMMODITY_TRANSFORMER,
	COMMODITY_INVERTER,
	COMMODITY_TIRE,
	COMMODITY_BRAKE,

	//化妆品
	COMMODITY_CLEANSER,
	COMMODITY_TONER,
	COMMODITY_SERUM,
	COMMODITY_MOISTURIZER,
	COMMODITY_SUNSCREEN,
	COMMODITY_FOUNDATION,
	COMMODITY_EYESLINER,
	COMMODITY_MASCARA,
	COMMODITY_LIPSTICK,
	COMMODITY_BLUSH,
	COMMODITY_REMOVER,
	COMMODITY_PERFUME,

	//珠宝
	COMMODITY_DIAMOND,
	COMMODITY_RUBY,
	COMMODITY_SUPPHIRE,
	COMMODITY_JADE,
	COMMODITY_PEARL,
	COMMODITY_GOLD,
	COMMODITY_PLATINUM,
	COMMODITY_SILVER,
	COMMODITY_RING,
	COMMODITY_NECKLACE,
	COMMODITY_EARRINGS,
	COMMODITY_BRACELET,
	COMMODITY_PENDANT,

	//武器
	COMMODITY_SWORD,
	COMMODITY_DAGGER,
	COMMODITY_AXE,
	COMMODITY_SPEAR,
	COMMODITY_DART,
	COMMODITY_PISTOL,
	COMMODITY_RIFLE,
	COMMODITY_SNIPER,
	COMMODITY_SMG,
	COMMODITY_SHOTGUN,
	COMMODITY_MACHINEGUN,
	COMMODITY_GRENADE,
	COMMODITY_BOW,
	COMMODITY_CROSSBOW,
	COMMODITY_MOLOTOV,
	COMMODITY_ROCKET,
	COMMODITY_MORTAR,
	COMMODITY_ARTILLERY,
	COMMODITY_LANDMINE,
	COMMODITY_C4,
	COMMODITY_MISSILE,
	COMMODITY_TANK,
	COMMODITY_NAVAL,
	COMMODITY_TASER,
	COMMODITY_SPRAY,
	COMMODITY_FLASHBANG,
	COMMODITY_LAZERGUN,

	//艺术品
	COMMODITY_PAINTING,
	COMMODITY_SCULPTURE,
	COMMODITY_CALLIGRAPHY,
	COMMODITY_SKETCH,
	COMMODITY_COMIC,
	COMMODITY_EMBROIDERY,
	COMMODITY_BOOK,
	COMMODITY_COSTUME,
	COMMODITY_PHOTO,

	//药品
	COMMODITY_PAINKILLER,
	COMMODITY_COLDPILL,
	COMMODITY_ANTIPYRETIC,
	COMMODITY_ANTIBIOTIC,
	COMMODITY_ANTIIFLAMMATORY,
	COMMODITY_ANTIDIARRHEAL,
	COMMODITY_BANDAGE,
	COMMODITY_GAUZE,
	COMMODITY_ANTISEPTIC,
	COMMODITY_SWAB,
	COMMODITY_INSULIN,
	COMMODITY_SEDATIVE,
	COMMODITY_SLEEPINGPILL,
	COMMODITY_EYEDROP,
	COMMODITY_VITAMIN,
	COMMODITY_PROTEIN,
	COMMODITY_MORPHINE,
	COMMODITY_POISON,
	COMMODITY_STIMULANT,
	COMMODITY_EPIPEN,
	COMMODITY_DRUG,
};

class Commodity {
public:
	Commodity(COMMODITY_TYPE type) : type(type) {};

	COMMODITY_TYPE GetType();
	void SetType(COMMODITY_TYPE type);

private:
	COMMODITY_TYPE type;

	std::vector<std::pair<COMMODITY_TYPE, float>> materials;
};

class ShortshirtCommodity : public Commodity {
public:
	ShortshirtCommodity() : Commodity(COMMODITY_SHORTSHIRT) {}

private:

};

class LongshirtCommodity : public Commodity {
public:
	LongshirtCommodity() : Commodity(COMMODITY_LONGSHIRT) {}

private:

};

class SweaterCommodity : public Commodity {
public:
	SweaterCommodity() : Commodity(COMMODITY_SWEATER) {}

private:

};

class HoodieCommodity : public Commodity {
public:
	HoodieCommodity() : Commodity(COMMODITY_HOODIE) {}

private:

};

class VestCommodity : public Commodity {
public:
	VestCommodity() : Commodity(COMMODITY_VEST) {}

private:

};

class PantsCommodity : public Commodity {
public:
	PantsCommodity() : Commodity(COMMODITY_PANTS) {}

private:

};

class ChinosCommodity : public Commodity {
public:
	ChinosCommodity() : Commodity(COMMODITY_CHINOS) {}

private:

};

class JoggersCommodity : public Commodity {
public:
	JoggersCommodity() : Commodity(COMMODITY_JOGGERS) {}

private:

};

class JeansCommodity : public Commodity {
public:
	JeansCommodity() : Commodity(COMMODITY_JEANS) {}

private:

};

class SkirtCommodity : public Commodity {
public:
	SkirtCommodity() : Commodity(COMMODITY_SKIRT) {}

private:

};

class UppersuitCommodity : public Commodity {
public:
	UppersuitCommodity() : Commodity(COMMODITY_UPPERSUIT) {}

private:

};

class UpperuniformCommodity : public Commodity {
public:
	UpperuniformCommodity() : Commodity(COMMODITY_UPPERUNIFORM) {}

private:

};

class UpperthermalCommodity : public Commodity {
public:
	UpperthermalCommodity() : Commodity(COMMODITY_UPPERTHERMAL) {}

private:

};

class LowersuitCommodity : public Commodity {
public:
	LowersuitCommodity() : Commodity(COMMODITY_LOWERSUIT) {}

private:

};

class LoweruniformCommodity : public Commodity {
public:
	LoweruniformCommodity() : Commodity(COMMODITY_LOWERUNIFORM) {}

private:

};

class LowerthermalCommodity : public Commodity {
public:
	LowerthermalCommodity() : Commodity(COMMODITY_LOWERTHERMAL) {}

private:

};

class JacketCommodity : public Commodity {
public:
	JacketCommodity() : Commodity(COMMODITY_JACKET) {}

private:

};

class OvercoatCommodity : public Commodity {
public:
	OvercoatCommodity() : Commodity(COMMODITY_OVERCOAT) {}

private:

};

class RaincoatCommodity : public Commodity {
public:
	RaincoatCommodity() : Commodity(COMMODITY_RAINCOAT) {}

private:

};

class LeathercoatCommodity : public Commodity {
public:
	LeathercoatCommodity() : Commodity(COMMODITY_LEATHERCOAT) {}

private:

};

class FurcoatCommodity : public Commodity {
public:
	FurcoatCommodity() : Commodity(COMMODITY_FURCOAT) {}

private:

};

class VelvetCommodity : public Commodity {
public:
	VelvetCommodity() : Commodity(COMMODITY_VELVET) {}

private:

};

class DressCommodity : public Commodity {
public:
	DressCommodity() : Commodity(COMMODITY_DRESS) {}

private:

};

class QipaoCommodity : public Commodity {
public:
	QipaoCommodity() : Commodity(COMMODITY_QIPAO) {}

private:

};

class SwimaleCommodity : public Commodity {
public:
	SwimaleCommodity() : Commodity(COMMODITY_SWIMMALE) {}

private:

};

class SwimfemaleCommodity : public Commodity {
public:
	SwimfemaleCommodity() : Commodity(COMMODITY_SWIMFEMALE) {}

private:

};

class BraCommodity : public Commodity {
public:
	BraCommodity() : Commodity(COMMODITY_BRA) {}

private:

};

class UnderwearCommodity : public Commodity {
public:
	UnderwearCommodity() : Commodity(COMMODITY_UNDERWEAR) {}

private:

};

class GlovesCommodity : public Commodity {
public:
	GlovesCommodity() : Commodity(COMMODITY_GLOVES) {}

private:

};

class ScarfCommodity : public Commodity {
public:
	ScarfCommodity() : Commodity(COMMODITY_SCARF) {}

private:

};

class CapCommodity : public Commodity {
public:
	CapCommodity() : Commodity(COMMODITY_CAP) {}

private:

};

class HatCommodity : public Commodity {
public:
	HatCommodity() : Commodity(COMMODITY_HAT) {}

private:

};

class SneakersCommodity : public Commodity {
public:
	SneakersCommodity() : Commodity(COMMODITY_SNEAKERS) {}

private:

};

class BootsCommodity : public Commodity {
public:
	BootsCommodity() : Commodity(COMMODITY_BOOTS) {}

private:

};

class LeathershoesCommodity : public Commodity {
public:
	LeathershoesCommodity() : Commodity(COMMODITY_LEATHERSHOES) {}

private:

};

class HighshoesCommodity : public Commodity {
public:
	HighshoesCommodity() : Commodity(COMMODITY_HIGHSHOES) {}

private:

};

class SlippersCommodity : public Commodity {
public:
	SlippersCommodity() : Commodity(COMMODITY_SLIPPERS) {}

private:

};

class TieCommodity : public Commodity {
public:
	TieCommodity() : Commodity(COMMODITY_TIE) {}

private:

};

class MaskCommodity : public Commodity {
public:
	MaskCommodity() : Commodity(COMMODITY_MASK) {}

private:

};

class AppleCommodity : public Commodity {
public:
	AppleCommodity() : Commodity(COMMODITY_APPLE) {}

private:

};

class BananaCommodity : public Commodity {
public:
	BananaCommodity() : Commodity(COMMODITY_BANANA) {}

private:

};

class OrangeCommodity : public Commodity {
public:
	OrangeCommodity() : Commodity(COMMODITY_ORANGE) {}

private:

};

class StrawberryCommodity : public Commodity {
public:
	StrawberryCommodity() : Commodity(COMMODITY_STRAWBERRY) {}

private:

};

class GrapeCommodity : public Commodity {
public:
	GrapeCommodity() : Commodity(COMMODITY_GRAPE) {}

private:

};

class WatermelonCommodity : public Commodity {
public:
	WatermelonCommodity() : Commodity(COMMODITY_WATERMELON) {}

private:

};

class PeachCommodity : public Commodity {
public:
	PeachCommodity() : Commodity(COMMODITY_PEACH) {}

private:

};

class PearCommodity : public Commodity {
public:
	PearCommodity() : Commodity(COMMODITY_PEAR) {}

private:

};

class LemonCommodity : public Commodity {
public:
	LemonCommodity() : Commodity(COMMODITY_LEMON) {}

private:

};

class MangoCommodity : public Commodity {
public:
	MangoCommodity() : Commodity(COMMODITY_MANGO) {}

private:

};

class PineappleCommodity : public Commodity {
public:
	PineappleCommodity() : Commodity(COMMODITY_PINEAPPLE) {}

private:

};

class CherryCommodity : public Commodity {
public:
	CherryCommodity() : Commodity(COMMODITY_CHERRY) {}

private:

};

class BlueberryCommodity : public Commodity {
public:
	BlueberryCommodity() : Commodity(COMMODITY_BLUBERRY) {}

private:

};

class KiwiCommodity : public Commodity {
public:
	KiwiCommodity() : Commodity(COMMODITY_KIWI) {}

private:

};

class CoconutCommodity : public Commodity {
public:
	CoconutCommodity() : Commodity(COMMODITY_COCONUT) {}

private:

};

class LitchiCommodity : public Commodity {
public:
	LitchiCommodity() : Commodity(COMMODITY_LITCHI) {}

private:

};

class DurianCommodity : public Commodity {
public:
	DurianCommodity() : Commodity(COMMODITY_DURIAN) {}

private:

};

class CabbageCommodity : public Commodity {
public:
	CabbageCommodity() : Commodity(COMMODITY_CABBAGE) {}

private:

};

class CarrotCommodity : public Commodity {
public:
	CarrotCommodity() : Commodity(COMMODITY_CARROT) {}

private:

};

class RadishCommodity : public Commodity {
public:
	RadishCommodity() : Commodity(COMMODITY_RADISH) {}

private:

};

class PotatoCommodity : public Commodity {
public:
	PotatoCommodity() : Commodity(COMMODITY_POTATO) {}

private:

};

class TomatoCommodity : public Commodity {
public:
	TomatoCommodity() : Commodity(COMMODITY_TOMATO) {}

private:

};

class OnionCommodity : public Commodity {
public:
	OnionCommodity() : Commodity(COMMODITY_ONION) {}

private:

};

class LettuceCommodity : public Commodity {
public:
	LettuceCommodity() : Commodity(COMMODITY_LETTUCE) {}

private:

};

class CucumberCommodity : public Commodity {
public:
	CucumberCommodity() : Commodity(COMMODITY_CUCUMBER) {}

private:

};

class SpinachCommodity : public Commodity {
public:
	SpinachCommodity() : Commodity(COMMODITY_SPINACH) {}

private:

};

class BroccoliCommodity : public Commodity {
public:
	BroccoliCommodity() : Commodity(COMMODITY_BROCCOLI) {}

private:

};

class CauliflowerCommodity : public Commodity {
public:
	CauliflowerCommodity() : Commodity(COMMODITY_CAULIFLOWER) {}

private:

};

class EggplantCommodity : public Commodity {
public:
	EggplantCommodity() : Commodity(COMMODITY_EGGPLANT) {}

private:

};

class PepperCommodity : public Commodity {
public:
	PepperCommodity() : Commodity(COMMODITY_PEPPER) {}

private:

};

class MushroomCommodity : public Commodity {
public:
	MushroomCommodity() : Commodity(COMMODITY_MUSHROOM) {}

private:

};

class CornCommodity : public Commodity {
public:
	CornCommodity() : Commodity(COMMODITY_CORN) {}

private:

};

class BeanCommodity : public Commodity {
public:
	BeanCommodity() : Commodity(COMMODITY_BEAN) {}

private:

};

class PumpkinCommodity : public Commodity {
public:
	PumpkinCommodity() : Commodity(COMMODITY_PUMPKIN) {}

private:

};

class SeaweedCommodity : public Commodity {
public:
	SeaweedCommodity() : Commodity(COMMODITY_SEAWEED) {}

private:

};

class PorkCommodity : public Commodity {
public:
	PorkCommodity() : Commodity(COMMODITY_PORK) {}

private:

};

class BeefCommodity : public Commodity {
public:
	BeefCommodity() : Commodity(COMMODITY_BEEF) {}

private:

};

class ChickenCommodity : public Commodity {
public:
	ChickenCommodity() : Commodity(COMMODITY_CHICKEN) {}

private:

};

class EggCommodity : public Commodity {
public:
	EggCommodity() : Commodity(COMMODITY_EGG) {}

private:

};

class LambCommodity : public Commodity {
public:
	LambCommodity() : Commodity(COMMODITY_LAMB) {}

private:

};

class DuckCommodity : public Commodity {
public:
	DuckCommodity() : Commodity(COMMODITY_DUCK) {}

private:

};

class HoneyCommodity : public Commodity {
public:
	HoneyCommodity() : Commodity(COMMODITY_HONEY) {}

private:

};

class SausageCommodity : public Commodity {
public:
	SausageCommodity() : Commodity(COMMODITY_SAUSAGE) {}

private:

};

class HamCommodity : public Commodity {
public:
	HamCommodity() : Commodity(COMMODITY_HAM) {}

private:

};

class FishCommodity : public Commodity {
public:
	FishCommodity() : Commodity(COMMODITY_FISH) {}

private:

};

class ShrimpCommodity : public Commodity {
public:
	ShrimpCommodity() : Commodity(COMMODITY_SHRIMP) {}

private:

};

class CrabCommodity : public Commodity {
public:
	CrabCommodity() : Commodity(COMMODITY_CRAB) {}

private:

};

class LobsterCommodity : public Commodity {
public:
	LobsterCommodity() : Commodity(COMMODITY_LOBSTER) {}

private:

};

class OysterCommodity : public Commodity {
public:
	OysterCommodity() : Commodity(COMMODITY_OYSTER) {}

private:

};

class ShellCommodity : public Commodity {
public:
	ShellCommodity() : Commodity(COMMODITY_SHELL) {}

private:

};

class SquidCommodity : public Commodity {
public:
	SquidCommodity() : Commodity(COMMODITY_SQUID) {}

private:

};

class RiceCommodity : public Commodity {
public:
	RiceCommodity() : Commodity(COMMODITY_RICE) {}

private:

};

class FlourCommodity : public Commodity {
public:
	FlourCommodity() : Commodity(COMMODITY_FLOUR) {}

private:

};

class CocoCommodity : public Commodity {
public:
	CocoCommodity() : Commodity(COMMODITY_COCO) {}

private:

};

class WaterCommodity : public Commodity {
public:
	WaterCommodity() : Commodity(COMMODITY_WATER) {}

private:

};

class MilkCommodity : public Commodity {
public:
	MilkCommodity() : Commodity(COMMODITY_MILK) {}

private:

};

class TeaCommodity : public Commodity {
public:
	TeaCommodity() : Commodity(COMMODITY_TEA) {}

private:

};

class CoffeeCommodity : public Commodity {
public:
	CoffeeCommodity() : Commodity(COMMODITY_COFFEE) {}

private:

};

class JuiceCommodity : public Commodity {
public:
	JuiceCommodity() : Commodity(COMMODITY_JUICE) {}

private:

};

class SodaCommodity : public Commodity {
public:
	SodaCommodity() : Commodity(COMMODITY_SODA) {}

private:

};

class BearCommodity : public Commodity {
public:
	BearCommodity() : Commodity(COMMODITY_BEAR) {}

private:

};

class WineCommodity : public Commodity {
public:
	WineCommodity() : Commodity(COMMODITY_WINE) {}

private:

};

class BaijiuCommodity : public Commodity {
public:
	BaijiuCommodity() : Commodity(COMMODITY_BAIJIU) {}

private:

};

class SaltCommodity : public Commodity {
public:
	SaltCommodity() : Commodity(COMMODITY_SALT) {}

private:

};

class SugarCommodity : public Commodity {
public:
	SugarCommodity() : Commodity(COMMODITY_SUGAR) {}

private:

};

class SoySauceCommodity : public Commodity {
public:
	SoySauceCommodity() : Commodity(COMMODITY_SOYSAUCE) {}

private:

};

class VinegarCommodity : public Commodity {
public:
	VinegarCommodity() : Commodity(COMMODITY_VINEGAR) {}

private:

};

class OilCommodity : public Commodity {
public:
	OilCommodity() : Commodity(COMMODITY_OIL) {}

private:

};

class ChiliCommodity : public Commodity {
public:
	ChiliCommodity() : Commodity(COMMODITY_CHILI) {}

private:

};

class MsgCommodity : public Commodity {
public:
	MsgCommodity() : Commodity(COMMODITY_MSG) {}

private:

};

class CurryCommodity : public Commodity {
public:
	CurryCommodity() : Commodity(COMMODITY_CURRY) {}

private:

};

class IceCommodity : public Commodity {
public:
	IceCommodity() : Commodity(COMMODITY_ICE) {}

private:

};

class BrickCommodity : public Commodity {
public:
	BrickCommodity() : Commodity(COMMODITY_BRICK) {}

private:

};

class ConcreteCommodity : public Commodity {
public:
	ConcreteCommodity() : Commodity(COMMODITY_CONCRETE) {}

private:

};

class StoneCommodity : public Commodity {
public:
	StoneCommodity() : Commodity(COMMODITY_STONE) {}

private:

};

class TimberCommodity : public Commodity {
public:
	TimberCommodity() : Commodity(COMMODITY_TIMBER) {}

private:

};

class SteelCommodity : public Commodity {
public:
	SteelCommodity() : Commodity(COMMODITY_STEEL) {}

private:

};

class CementCommodity : public Commodity {
public:
	CementCommodity() : Commodity(COMMODITY_CEMENT) {}

private:

};

class PlasterCommodity : public Commodity {
public:
	PlasterCommodity() : Commodity(COMMODITY_PLASTER) {}

private:

};

class PlankCommodity : public Commodity {
public:
	PlankCommodity() : Commodity(COMMODITY_PLANK) {}

private:

};

class PaintCommodity : public Commodity {
public:
	PaintCommodity() : Commodity(COMMODITY_PAINT) {}

private:

};

class TileCommodity : public Commodity {
public:
	TileCommodity() : Commodity(COMMODITY_TILE) {}

private:

};

class MarbleCommodity : public Commodity {
public:
	MarbleCommodity() : Commodity(COMMODITY_MARBLE) {}

private:

};

class GlassCommodity : public Commodity {
public:
	GlassCommodity() : Commodity(COMMODITY_GLASS) {}

private:

};

class FloorCommodity : public Commodity {
public:
	FloorCommodity() : Commodity(COMMODITY_FLOOR) {}

private:

};

class AsphaltCommodity : public Commodity {
public:
	AsphaltCommodity() : Commodity(COMMODITY_ASPHALT) {}

private:

};

class RubberCommodity : public Commodity {
public:
	RubberCommodity() : Commodity(COMMODITY_RUBBER) {}

private:

};

class ClayCommodity : public Commodity {
public:
	ClayCommodity() : Commodity(COMMODITY_CLAY) {}

private:

};

class DoorCommodity : public Commodity {
public:
	DoorCommodity() : Commodity(COMMODITY_DOOR) {}

private:

};

class WindowCommodity : public Commodity {
public:
	WindowCommodity() : Commodity(COMMODITY_WINDOW) {}

private:

};

class PipeCommodity : public Commodity {
public:
	PipeCommodity() : Commodity(COMMODITY_PIPE) {}

private:

};

class CarbonCommodity : public Commodity {
public:
	CarbonCommodity() : Commodity(COMMODITY_CARBON) {}

private:

};

class CarpetCommodity : public Commodity {
public:
	CarpetCommodity() : Commodity(COMMODITY_CARPET) {}

private:

};

class SofaCommodity : public Commodity {
public:
	SofaCommodity() : Commodity(COMMODITY_SOFA) {}

private:

};

class ShelfCommodity : public Commodity {
public:
	ShelfCommodity() : Commodity(COMMODITY_SHELF) {}

private:

};

class ChairCommodity : public Commodity {
public:
	ChairCommodity() : Commodity(COMMODITY_CHAIR) {}

private:

};

class TableCommodity : public Commodity {
public:
	TableCommodity() : Commodity(COMMODITY_TABLE) {}

private:

};

class DeskCommodity : public Commodity {
public:
	DeskCommodity() : Commodity(COMMODITY_DESK) {}

private:

};

class BedCommodity : public Commodity {
public:
	BedCommodity() : Commodity(COMMODITY_BED) {}

private:

};

class CabinetCommodity : public Commodity {
public:
	CabinetCommodity() : Commodity(COMMODITY_CABINET) {}

private:

};

class MirrorCommodity : public Commodity {
public:
	MirrorCommodity() : Commodity(COMMODITY_MIRROR) {}

private:

};

class WardrobeCommodity : public Commodity {
public:
	WardrobeCommodity() : Commodity(COMMODITY_WARDROBE) {}

private:

};

class CooktopCommodity : public Commodity {
public:
	CooktopCommodity() : Commodity(COMMODITY_COOKTOP) {}

private:

};

class BasinCommodity : public Commodity {
public:
	BasinCommodity() : Commodity(COMMODITY_BASIN) {}

private:

};

class ToiletCommodity : public Commodity {
public:
	ToiletCommodity() : Commodity(COMMODITY_TOILET) {}

private:

};

class BathtubCommodity : public Commodity {
public:
	BathtubCommodity() : Commodity(COMMODITY_BATHTUB) {}

private:

};

class ShowerCommodity : public Commodity {
public:
	ShowerCommodity() : Commodity(COMMODITY_SHOWER) {}

private:

};

class ClockCommodity : public Commodity {
public:
	ClockCommodity() : Commodity(COMMODITY_CLOCK) {}

private:

};

class LampCommodity : public Commodity {
public:
	LampCommodity() : Commodity(COMMODITY_LAMP) {}

private:

};

class ChandelierCommodity : public Commodity {
public:
	ChandelierCommodity() : Commodity(COMMODITY_CHANDELIER) {}

private:

};

class CurtainCommodity : public Commodity {
public:
	CurtainCommodity() : Commodity(COMMODITY_CURTAIN) {}

private:

};

class VentilatorCommodity : public Commodity {
public:
	VentilatorCommodity() : Commodity(COMMODITY_VENTILATOR) {}

private:

};

class FridgeCommodity : public Commodity {
public:
	FridgeCommodity() : Commodity(COMMODITY_FRIDGE) {}

private:

};

class MicrowaveCommodity : public Commodity {
public:
	MicrowaveCommodity() : Commodity(COMMODITY_MICROWAVE) {}

private:

};

class OvenCommodity : public Commodity {
public:
	OvenCommodity() : Commodity(COMMODITY_OVEN) {}

private:

};

class InductionCommodity : public Commodity {
public:
	InductionCommodity() : Commodity(COMMODITY_INDUCTION) {}

private:

};

class DishwasherCommodity : public Commodity {
public:
	DishwasherCommodity() : Commodity(COMMODITY_DISHWASHER) {}

private:

};

class JucierCommodity : public Commodity {
public:
	JucierCommodity() : Commodity(COMMODITY_JUCIER) {}

private:

};

class BreadmakerCommodity : public Commodity {
public:
	BreadmakerCommodity() : Commodity(COMMODITY_BREADMAKER) {}

private:

};

class LoundryCommodity : public Commodity {
public:
	LoundryCommodity() : Commodity(COMMODITY_LOUNDRY) {}

private:

};

class ClothdryerCommodity : public Commodity {
public:
	ClothdryerCommodity() : Commodity(COMMODITY_CLOTHDRYER) {}

private:

};

class VacummerCommodity : public Commodity {
public:
	VacummerCommodity() : Commodity(COMMODITY_VACUMMER) {}

private:

};

class SteamerCommodity : public Commodity {
public:
	SteamerCommodity() : Commodity(COMMODITY_STEAMER) {}

private:

};

class FloorrobotCommodity : public Commodity {
public:
	FloorrobotCommodity() : Commodity(COMMODITY_FLOORROBOT) {}

private:

};

class HairdryerCommodity : public Commodity {
public:
	HairdryerCommodity() : Commodity(COMMODITY_HIARDRYER) {}

private:

};

class ShaverCommodity : public Commodity {
public:
	ShaverCommodity() : Commodity(COMMODITY_SHAVER) {}

private:

};

class AcCommodity : public Commodity {
public:
	AcCommodity() : Commodity(COMMODITY_AC) {}

private:

};

class EfanCommodity : public Commodity {
public:
	EfanCommodity() : Commodity(COMMODITY_EFAN) {}

private:

};

class HumidifierCommodity : public Commodity {
public:
	HumidifierCommodity() : Commodity(COMMODITY_HUMIDIFIER) {}

private:

};

class DehumidifierCommodity : public Commodity {
public:
	DehumidifierCommodity() : Commodity(COMMODITY_DEHUMIDIFIER) {}

private:

};

class HeaterCommodity : public Commodity {
public:
	HeaterCommodity() : Commodity(COMMODITY_HEATER) {}

private:

};

class IronCommodity : public Commodity {
public:
	IronCommodity() : Commodity(COMMODITY_IRON) {}

private:

};

class SewingCommodity : public Commodity {
public:
	SewingCommodity() : Commodity(COMMODITY_SEWING) {}

private:

};

class ScalarCommodity : public Commodity {
public:
	ScalarCommodity() : Commodity(COMMODITY_SCALAR) {}

private:

};

class GeyserCommodity : public Commodity {
public:
	GeyserCommodity() : Commodity(COMMODITY_GEYSER) {}

private:

};

class KettleCommodity : public Commodity {
public:
	KettleCommodity() : Commodity(COMMODITY_KETTLE) {}

private:

};

class BikeCommodity : public Commodity {
public:
	BikeCommodity() : Commodity(COMMODITY_BIKE) {}

private:

};

class ScooterCommodity : public Commodity {
public:
	ScooterCommodity() : Commodity(COMMODITY_SCOOTER) {}

private:

};

class MotorCommodity : public Commodity {
public:
	MotorCommodity() : Commodity(COMMODITY_MOTOR) {}

private:

};

class SedanCommodity : public Commodity {
public:
	SedanCommodity() : Commodity(COMMODITY_SEDAN) {}

private:

};

class BusCommodity : public Commodity {
public:
	BusCommodity() : Commodity(COMMODITY_BUS) {}

private:

};

class TruckCommodity : public Commodity {
public:
	TruckCommodity() : Commodity(COMMODITY_TRUCK) {}

private:

};

class VanCommodity : public Commodity {
public:
	VanCommodity() : Commodity(COMMODITY_VAN) {}

private:

};

class BusinesscarCommodity : public Commodity {
public:
	BusinesscarCommodity() : Commodity(COMMODITY_BUSINESSCAR) {}

private:

};

class RvCommodity : public Commodity {
public:
	RvCommodity() : Commodity(COMMODITY_RV) {}

private:

};

class MetroCommodity : public Commodity {
public:
	MetroCommodity() : Commodity(COMMODITY_METRO) {}

private:

};

class TrainCommodity : public Commodity {
public:
	TrainCommodity() : Commodity(COMMODITY_TRAIN) {}

private:

};

class TramCommodity : public Commodity {
public:
	TramCommodity() : Commodity(COMMODITY_TRAM) {}

private:

};

class BoatCommodity : public Commodity {
public:
	BoatCommodity() : Commodity(COMMODITY_BOAT) {}

private:

};

class YachtCommodity : public Commodity {
public:
	YachtCommodity() : Commodity(COMMODITY_YACHT) {}

private:

};

class FerryCommodity : public Commodity {
public:
	FerryCommodity() : Commodity(COMMODITY_FERRY) {}

private:

};

class ShipCommodity : public Commodity {
public:
	ShipCommodity() : Commodity(COMMODITY_SHIP) {}

private:

};

class SubmarineCommodity : public Commodity {
public:
	SubmarineCommodity() : Commodity(COMMODITY_SUBMARINE) {}

private:

};

class PlaneCommodity : public Commodity {
public:
	PlaneCommodity() : Commodity(COMMODITY_PLANE) {}

private:

};

class HelicopterCommodity : public Commodity {
public:
	HelicopterCommodity() : Commodity(COMMODITY_HELICOPTER) {}

private:

};

class GliderCommodity : public Commodity {
public:
	GliderCommodity() : Commodity(COMMODITY_GLIDER) {}

private:

};

class ShuttleCommodity : public Commodity {
public:
	ShuttleCommodity() : Commodity(COMMODITY_SHUTTLE) {}

private:

};

class CoalCommodity : public Commodity {
public:
	CoalCommodity() : Commodity(COMMODITY_COAL) {}

private:

};

class OreCommodity : public Commodity {
public:
	OreCommodity() : Commodity(COMMODITY_ORE) {}

private:

};

class QuartzCommodity : public Commodity {
public:
	QuartzCommodity() : Commodity(COMMODITY_QUARTZ) {}

private:

};

class SulfurCommodity : public Commodity {
public:
	SulfurCommodity() : Commodity(COMMODITY_SULFUR) {}

private:

};

class CrystalCommodity : public Commodity {
public:
	CrystalCommodity() : Commodity(COMMODITY_CRYSTAL) {}

private:

};

class LogCommodity : public Commodity {
public:
	LogCommodity() : Commodity(COMMODITY_LOG) {}

private:

};

class BambooCommodity : public Commodity {
public:
	BambooCommodity() : Commodity(COMMODITY_BAMBOO) {}

private:

};

class ResinCommodity : public Commodity {
public:
	ResinCommodity() : Commodity(COMMODITY_RESIN) {}

private:

};

class HerbsCommodity : public Commodity {
public:
	HerbsCommodity() : Commodity(COMMODITY_HERBS) {}

private:

};

class CottonCommodity : public Commodity {
public:
	CottonCommodity() : Commodity(COMMODITY_COTTON) {}

private:

};

class CurdeCommodity : public Commodity {
public:
	CurdeCommodity() : Commodity(COMMODITY_CURDE) {}

private:

};

class NaturalgasCommodity : public Commodity {
public:
	NaturalgasCommodity() : Commodity(COMMODITY_NATURALGAS) {}

private:

};

class UraniumCommodity : public Commodity {
public:
	UraniumCommodity() : Commodity(COMMODITY_URANIUM) {}

private:

};

class RockCommodity : public Commodity {
public:
	RockCommodity() : Commodity(COMMODITY_ROCK) {}

private:

};

class SandCommodity : public Commodity {
public:
	SandCommodity() : Commodity(COMMODITY_SAND) {}

private:

};

class PeltCommodity : public Commodity {
public:
	PeltCommodity() : Commodity(COMMODITY_PELT) {}

private:

};

class ClothCommodity : public Commodity {
public:
	ClothCommodity() : Commodity(COMMODITY_CLOTH) {}

private:

};

class LeatherCommodity : public Commodity {
public:
	LeatherCommodity() : Commodity(COMMODITY_LEATHER) {}

private:

};

class WoolCommodity : public Commodity {
public:
	WoolCommodity() : Commodity(COMMODITY_WOOL) {}

private:

};

class BoneCommodity : public Commodity {
public:
	BoneCommodity() : Commodity(COMMODITY_BONE) {}

private:

};

class FeatherCommodity : public Commodity {
public:
	FeatherCommodity() : Commodity(COMMODITY_FEATHER) {}

private:

};

class BowlCommodity : public Commodity {
public:
	BowlCommodity() : Commodity(COMMODITY_BOWL) {}

private:

};

class PlateCommodity : public Commodity {
public:
	PlateCommodity() : Commodity(COMMODITY_PLATE) {}

private:

};

class ChopsticksCommodity : public Commodity {
public:
	ChopsticksCommodity() : Commodity(COMMODITY_CHOPSTICKS) {}

private:

};

class SpoonCommodity : public Commodity {
public:
	SpoonCommodity() : Commodity(COMMODITY_SPOON) {}

private:

};

class KnifeCommodity : public Commodity {
public:
	KnifeCommodity() : Commodity(COMMODITY_KNIFE) {}

private:

};

class ForkCommodity : public Commodity {
public:
	ForkCommodity() : Commodity(COMMODITY_FORK) {}

private:

};

class CupCommodity : public Commodity {
public:
	CupCommodity() : Commodity(COMMODITY_CUP) {}

private:

};

class PotCommodity : public Commodity {
public:
	PotCommodity() : Commodity(COMMODITY_POT) {}

private:

};

class SpatulaCommodity : public Commodity {
public:
	SpatulaCommodity() : Commodity(COMMODITY_SPATULA) {}

private:

};

class BoardCommodity : public Commodity {
public:
	BoardCommodity() : Commodity(COMMODITY_BOARD) {}

private:

};

class OpenerCommodity : public Commodity {
public:
	OpenerCommodity() : Commodity(COMMODITY_OPENER) {}

private:

};

class ContainerCommodity : public Commodity {
public:
	ContainerCommodity() : Commodity(COMMODITY_CONTAINER) {}

private:

};

class CombCommodity : public Commodity {
public:
	CombCommodity() : Commodity(COMMODITY_COMB) {}

private:

};

class ToothbrushCommodity : public Commodity {
public:
	ToothbrushCommodity() : Commodity(COMMODITY_TOOTHBRUSH) {}

private:

};

class ToothpasteCommodity : public Commodity {
public:
	ToothpasteCommodity() : Commodity(COMMODITY_TOOTHPASTE) {}

private:

};

class TowelCommodity : public Commodity {
public:
	TowelCommodity() : Commodity(COMMODITY_TOWEL) {}

private:

};

class SoapCommodity : public Commodity {
public:
	SoapCommodity() : Commodity(COMMODITY_SOAP) {}

private:

};

class ShampooCommodity : public Commodity {
public:
	ShampooCommodity() : Commodity(COMMODITY_SHAMPOO) {}

private:

};

class ShowergemCommodity : public Commodity {
public:
	ShowergemCommodity() : Commodity(COMMODITY_SHOWERGEM) {}

private:

};

class TissueCommodity : public Commodity {
public:
	TissueCommodity() : Commodity(COMMODITY_TISSUE) {}

private:

};

class RazorCommodity : public Commodity {
public:
	RazorCommodity() : Commodity(COMMODITY_RAZOR) {}

private:

};

class BroomCommodity : public Commodity {
public:
	BroomCommodity() : Commodity(COMMODITY_BROOM) {}

private:

};

class MopCommodity : public Commodity {
public:
	MopCommodity() : Commodity(COMMODITY_MOP) {}

private:

};

class TrashcanCommodity : public Commodity {
public:
	TrashcanCommodity() : Commodity(COMMODITY_TRASHCAN) {}

private:

};

class RagCommodity : public Commodity {
public:
	RagCommodity() : Commodity(COMMODITY_RAG) {}

private:

};

class DetergentCommodity : public Commodity {
public:
	DetergentCommodity() : Commodity(COMMODITY_DETERGENT) {}

private:

};
class LoundrypowderCommodity : public Commodity {
public:
	LoundrypowderCommodity() : Commodity(COMMODITY_LOUNDRYPOWDER) {}

private:

};

class LoundrygemCommodity : public Commodity {
public:
	LoundrygemCommodity() : Commodity(COMMODITY_LOUNDRYGEM) {}

private:

};

class PillowCommodity : public Commodity {
public:
	PillowCommodity() : Commodity(COMMODITY_PILLOW) {}

private:

};

class QuiltCommodity : public Commodity {
public:
	QuiltCommodity() : Commodity(COMMODITY_QUILT) {}

private:

};

class BedsheetCommodity : public Commodity {
public:
	BedsheetCommodity() : Commodity(COMMODITY_BEDSHEET) {}

private:

};

class MatressCommodity : public Commodity {
public:
	MatressCommodity() : Commodity(COMMODITY_MATRESS) {}

private:

};

class AlarmCommodity : public Commodity {
public:
	AlarmCommodity() : Commodity(COMMODITY_ALARM) {}

private:

};

class HangerCommodity : public Commodity {
public:
	HangerCommodity() : Commodity(COMMODITY_HANGER) {}

private:

};

class NailCommodity : public Commodity {
public:
	NailCommodity() : Commodity(COMMODITY_NAIL) {}

private:

};

class ScrewCommodity : public Commodity {
public:
	ScrewCommodity() : Commodity(COMMODITY_SCREW) {}

private:

};

class BoltCommodity : public Commodity {
public:
	BoltCommodity() : Commodity(COMMODITY_BOLT) {}

private:

};

class HammerCommodity : public Commodity {
public:
	HammerCommodity() : Commodity(COMMODITY_HAMMER) {}

private:

};

class UmbrellaCommodity : public Commodity {
public:
	UmbrellaCommodity() : Commodity(COMMODITY_UMBRELLA) {}

private:

};

class KeyCommodity : public Commodity {
public:
	KeyCommodity() : Commodity(COMMODITY_KEY) {}

private:

};

class CandleCommodity : public Commodity {
public:
	CandleCommodity() : Commodity(COMMODITY_CANDLE) {}

private:

};

class LighterCommodity : public Commodity {
public:
	LighterCommodity() : Commodity(COMMODITY_LIGHTER) {}

private:

};

class MagnifyingCommodity : public Commodity {
public:
	MagnifyingCommodity() : Commodity(COMMODITY_MAGNIFYING) {}

private:

};

class FlashlightCommodity : public Commodity {
public:
	FlashlightCommodity() : Commodity(COMMODITY_FLASHLIGHT) {}

private:

};

class BeltCommodity : public Commodity {
public:
	BeltCommodity() : Commodity(COMMODITY_BELT) {}

private:

};

class HelmetCommodity : public Commodity {
public:
	HelmetCommodity() : Commodity(COMMODITY_HELMET) {}

private:

};

class GlassesCommodity : public Commodity {
public:
	GlassesCommodity() : Commodity(COMMODITY_GLASSES) {}

private:

};

class FileCommodity : public Commodity {
public:
	FileCommodity() : Commodity(COMMODITY_FILE) {}

private:

};

class PenCommodity : public Commodity {
public:
	PenCommodity() : Commodity(COMMODITY_PEN) {}

private:

};

class PencilCommodity : public Commodity {
public:
	PencilCommodity() : Commodity(COMMODITY_PENCIL) {}

private:

};

class ChalkCommodity : public Commodity {
public:
	ChalkCommodity() : Commodity(COMMODITY_CHALK) {}

private:

};

class CrayonCommodity : public Commodity {
public:
	CrayonCommodity() : Commodity(COMMODITY_CRAYON) {}

private:

};

class BrushCommodity : public Commodity {
public:
	BrushCommodity() : Commodity(COMMODITY_BRUSH) {}

private:

};

class NotebookCommodity : public Commodity {
public:
	NotebookCommodity() : Commodity(COMMODITY_NOTEBOOK) {}

private:

};

class PaperCommodity : public Commodity {
public:
	PaperCommodity() : Commodity(COMMODITY_PAPER) {}

private:

};

class EraserCommodity : public Commodity {
public:
	EraserCommodity() : Commodity(COMMODITY_ERASER) {}

private:

};

class StaplerCommodity : public Commodity {
public:
	StaplerCommodity() : Commodity(COMMODITY_STAPLER) {}

private:

};

class ScissorsCommodity : public Commodity {
public:
	ScissorsCommodity() : Commodity(COMMODITY_SCISSORS) {}

private:

};

class FolderCommodity : public Commodity {
public:
	FolderCommodity() : Commodity(COMMODITY_FOLDER) {}

private:

};

class StickyCommodity : public Commodity {
public:
	StickyCommodity() : Commodity(COMMODITY_STICKY) {}

private:

};

class TapeCommodity : public Commodity {
public:
	TapeCommodity() : Commodity(COMMODITY_TAPE) {}

private:

};

class GlueCommodity : public Commodity {
public:
	GlueCommodity() : Commodity(COMMODITY_GLUE) {}

private:

};

class RulerCommodity : public Commodity {
public:
	RulerCommodity() : Commodity(COMMODITY_RULER) {}

private:

};

class BookmarkCommodity : public Commodity {
public:
	BookmarkCommodity() : Commodity(COMMODITY_BOOKMARK) {}

private:

};

class StampCommodity : public Commodity {
public:
	StampCommodity() : Commodity(COMMODITY_STAMP) {}

private:

};

class WatercolorCommodity : public Commodity {
public:
	WatercolorCommodity() : Commodity(COMMODITY_WATERCOLOR) {}

private:

};

class PaletteCommodity : public Commodity {
public:
	PaletteCommodity() : Commodity(COMMODITY_PALETTE) {}

private:

};

class DrillCommodity : public Commodity {
public:
	DrillCommodity() : Commodity(COMMODITY_DRILL) {}

private:

};

class ChainsawCommodity : public Commodity {
public:
	ChainsawCommodity() : Commodity(COMMODITY_CHAINSAW) {}

private:

};

class GrinderCommodity : public Commodity {
public:
	GrinderCommodity() : Commodity(COMMODITY_GRINDER) {}

private:

};

class WeldingCommodity : public Commodity {
public:
	WeldingCommodity() : Commodity(COMMODITY_WELDING) {}

private:

};

class LatheCommodity : public Commodity {
public:
	LatheCommodity() : Commodity(COMMODITY_LATHE) {}

private:

};

class D3printerCommodity : public Commodity {
public:
	D3printerCommodity() : Commodity(COMMODITY_3DPRINTER) {}

private:

};

class ExcavatorCommodity : public Commodity {
public:
	ExcavatorCommodity() : Commodity(COMMODITY_EXCAVATOR) {}

private:

};

class BulldozerCommodity : public Commodity {
public:
	BulldozerCommodity() : Commodity(COMMODITY_BULLDOZER) {}

private:

};

class ForkliftCommodity : public Commodity {
public:
	ForkliftCommodity() : Commodity(COMMODITY_FORKLIFT) {}

private:

};

class CraneCommodity : public Commodity {
public:
	CraneCommodity() : Commodity(COMMODITY_CRANE) {}

private:

};

class RollerCommodity : public Commodity {
public:
	RollerCommodity() : Commodity(COMMODITY_ROLLER) {}

private:

};

class TowerCommodity : public Commodity {
public:
	TowerCommodity() : Commodity(COMMODITY_TOWER) {}

private:

};

class TractorCommodity : public Commodity {
public:
	TractorCommodity() : Commodity(COMMODITY_TRACTOR) {}

private:

};

class HarvesterCommodity : public Commodity {
public:
	HarvesterCommodity() : Commodity(COMMODITY_HARVESTER) {}

private:

};

class SeederCommodity : public Commodity {
public:
	SeederCommodity() : Commodity(COMMODITY_SEEDER) {}

private:

};

class IrrigatorCommodity : public Commodity {
public:
	IrrigatorCommodity() : Commodity(COMMODITY_IRRIGATOR) {}

private:

};

class ConveyorCommodity : public Commodity {
public:
	ConveyorCommodity() : Commodity(COMMODITY_CONVEYOR) {}

private:

};

class BladeCommodity : public Commodity {
public:
	BladeCommodity() : Commodity(COMMODITY_BLADE) {}

private:

};

class TvCommodity : public Commodity {
public:
	TvCommodity() : Commodity(COMMODITY_TV) {}

private:

};

class ProjectorCommodity : public Commodity {
public:
	ProjectorCommodity() : Commodity(COMMODITY_PROJECTOR) {}

private:

};

class SpeakerCommodity : public Commodity {
public:
	SpeakerCommodity() : Commodity(COMMODITY_SPEAKER) {}

private:

};

class MicrophoneCommodity : public Commodity {
public:
	MicrophoneCommodity() : Commodity(COMMODITY_MICROPHONE) {}

private:

};

class PlaystationCommodity : public Commodity {
public:
	PlaystationCommodity() : Commodity(COMMODITY_PLAYSTATION) {}

private:

};

class EarbudsCommodity : public Commodity {
public:
	EarbudsCommodity() : Commodity(COMMODITY_EARBUDS) {}

private:

};

class DesktopCommodity : public Commodity {
public:
	DesktopCommodity() : Commodity(COMMODITY_DESKTOP) {}

private:

};

class LaptopCommodity : public Commodity {
public:
	LaptopCommodity() : Commodity(COMMODITY_LAPTOP) {}

private:

};

class TabletCommodity : public Commodity {
public:
	TabletCommodity() : Commodity(COMMODITY_TABLET) {}

private:

};

class TelephoneCommodity : public Commodity {
public:
	TelephoneCommodity() : Commodity(COMMODITY_TELEPHONE) {}

private:

};

class PrinterCommodity : public Commodity {
public:
	PrinterCommodity() : Commodity(COMMODITY_PRINTER) {}

private:

};

class ScannerCommodity : public Commodity {
public:
	ScannerCommodity() : Commodity(COMMODITY_SCANNER) {}

private:

};

class RouterCommodity : public Commodity {
public:
	RouterCommodity() : Commodity(COMMODITY_ROUTER) {}

private:

};

class MonitorCommodity : public Commodity {
public:
	MonitorCommodity() : Commodity(COMMODITY_MONITOR) {}

private:

};

class ScreenCommodity : public Commodity {
public:
	ScreenCommodity() : Commodity(COMMODITY_SCREEN) {}

private:

};

class CameraCommodity : public Commodity {
public:
	CameraCommodity() : Commodity(COMMODITY_CAMERA) {}

private:

};

class ChargerCommodity : public Commodity {
public:
	ChargerCommodity() : Commodity(COMMODITY_CHARGER) {}

private:

};

class MobileCommodity : public Commodity {
public:
	MobileCommodity() : Commodity(COMMODITY_MOBILE) {}

private:

};

class WatchCommodity : public Commodity {
public:
	WatchCommodity() : Commodity(COMMODITY_WATCH) {}

private:

};

class CalculatorCommodity : public Commodity {
public:
	CalculatorCommodity() : Commodity(COMMODITY_CALCULATOR) {}

private:

};

class PowerbankCommodity : public Commodity {
public:
	PowerbankCommodity() : Commodity(COMMODITY_POWERBANK) {}

private:

};

class UsbCommodity : public Commodity {
public:
	UsbCommodity() : Commodity(COMMODITY_USB) {}

private:

};

class ExtensionCommodity : public Commodity {
public:
	ExtensionCommodity() : Commodity(COMMODITY_EXTENSION) {}

private:

};

class DroneCommodity : public Commodity {
public:
	DroneCommodity() : Commodity(COMMODITY_DRONE) {}

private:

};

class CpuCommodity : public Commodity {
public:
	CpuCommodity() : Commodity(COMMODITY_CPU) {}

private:

};

class GpuCommodity : public Commodity {
public:
	GpuCommodity() : Commodity(COMMODITY_GPU) {}

private:

};

class RamCommodity : public Commodity {
public:
	RamCommodity() : Commodity(COMMODITY_RAM) {}

private:

};

class DiskCommodity : public Commodity {
public:
	DiskCommodity() : Commodity(COMMODITY_DISK) {}

private:

};

class PsuCommodity : public Commodity {
public:
	PsuCommodity() : Commodity(COMMODITY_PSU) {}

private:

};

class CoolingCommodity : public Commodity {
public:
	CoolingCommodity() : Commodity(COMMODITY_COOLING) {}

private:

};

class BatteryCommodity : public Commodity {
public:
	BatteryCommodity() : Commodity(COMMODITY_BATTERY) {}

private:

};

class CapacitorCommodity : public Commodity {
public:
	CapacitorCommodity() : Commodity(COMMODITY_CAPACITOR) {}

private:

};

class ResistorCommodity : public Commodity {
public:
	ResistorCommodity() : Commodity(COMMODITY_RESISTOR) {}

private:

};

class TransistorCommodity : public Commodity {
public:
	TransistorCommodity() : Commodity(COMMODITY_TRANSISTOR) {}

private:

};

class DiodeCommodity : public Commodity {
public:
	DiodeCommodity() : Commodity(COMMODITY_DIODE) {}

private:

};

class IcCommodity : public Commodity {
public:
	IcCommodity() : Commodity(COMMODITY_IC) {}

private:

};

class SensorCommodity : public Commodity {
public:
	SensorCommodity() : Commodity(COMMODITY_SENSOR) {}

private:

};

class GeneratorCommodity : public Commodity {
public:
	GeneratorCommodity() : Commodity(COMMODITY_GENERATOR) {}

private:

};

class EmotorCommodity : public Commodity {
public:
	EmotorCommodity() : Commodity(COMMODITY_EMOTOR) {}

private:

};

class GearCommodity : public Commodity {
public:
	GearCommodity() : Commodity(COMMODITY_GEAR) {}

private:

};

class BearingCommodity : public Commodity {
public:
	BearingCommodity() : Commodity(COMMODITY_BEARING) {}

private:

};

class PistonCommodity : public Commodity {
public:
	PistonCommodity() : Commodity(COMMODITY_PISTON) {}

private:

};

class PumpCommodity : public Commodity {
public:
	PumpCommodity() : Commodity(COMMODITY_PUMP) {}

private:

};

class TurbineCommodity : public Commodity {
public:
	TurbineCommodity() : Commodity(COMMODITY_TURBINE) {}

private:

};

class SpringCommodity : public Commodity {
public:
	SpringCommodity() : Commodity(COMMODITY_SPRING) {}

private:

};

class WireCommodity : public Commodity {
public:
	WireCommodity() : Commodity(COMMODITY_WIRE) {}

private:

};

class NetcableCommodity : public Commodity {
public:
	NetcableCommodity() : Commodity(COMMODITY_NETCABLE) {}

private:

};

class OpticcableCommodity : public Commodity {
public:
	OpticcableCommodity() : Commodity(COMMODITY_OPTICCABLE) {}

private:

};

class PlugCommodity : public Commodity {
public:
	PlugCommodity() : Commodity(COMMODITY_PLUG) {}

private:

};

class RelayCommodity : public Commodity {
public:
	RelayCommodity() : Commodity(COMMODITY_RELAY) {}

private:

};

class TransformerCommodity : public Commodity {
public:
	TransformerCommodity() : Commodity(COMMODITY_TRANSFORMER) {}

private:

};

class InverterCommodity : public Commodity {
public:
	InverterCommodity() : Commodity(COMMODITY_INVERTER) {}

private:

};

class TireCommodity : public Commodity {
public:
	TireCommodity() : Commodity(COMMODITY_TIRE) {}

private:

};

class BrakeCommodity : public Commodity {
public:
	BrakeCommodity() : Commodity(COMMODITY_BRAKE) {}

private:

};

class CleanserCommodity : public Commodity {
public:
	CleanserCommodity() : Commodity(COMMODITY_CLEANSER) {}

private:

};

class TonerCommodity : public Commodity {
public:
	TonerCommodity() : Commodity(COMMODITY_TONER) {}

private:

};

class SerumCommodity : public Commodity {
public:
	SerumCommodity() : Commodity(COMMODITY_SERUM) {}

private:

};

class MoisturizerCommodity : public Commodity {
public:
	MoisturizerCommodity() : Commodity(COMMODITY_MOISTURIZER) {}

private:

};

class SunscreenCommodity : public Commodity {
public:
	SunscreenCommodity() : Commodity(COMMODITY_SUNSCREEN) {}

private:

};

class FoundationCommodity : public Commodity {
public:
	FoundationCommodity() : Commodity(COMMODITY_FOUNDATION) {}

private:

};

class EyeslinerCommodity : public Commodity {
public:
	EyeslinerCommodity() : Commodity(COMMODITY_EYESLINER) {}

private:

};

class MascaraCommodity : public Commodity {
public:
	MascaraCommodity() : Commodity(COMMODITY_MASCARA) {}

private:

};

class LipstickCommodity : public Commodity {
public:
	LipstickCommodity() : Commodity(COMMODITY_LIPSTICK) {}

private:

};

class BlushCommodity : public Commodity {
public:
	BlushCommodity() : Commodity(COMMODITY_BLUSH) {}

private:

};

class RemoverCommodity : public Commodity {
public:
	RemoverCommodity() : Commodity(COMMODITY_REMOVER) {}

private:

};

class PerfumeCommodity : public Commodity {
public:
	PerfumeCommodity() : Commodity(COMMODITY_PERFUME) {}

private:

};

class DiamondCommodity : public Commodity {
public:
	DiamondCommodity() : Commodity(COMMODITY_DIAMOND) {}

private:

};

class RubyCommodity : public Commodity {
public:
	RubyCommodity() : Commodity(COMMODITY_RUBY) {}

private:

};

class SupphireCommodity : public Commodity {
public:
	SupphireCommodity() : Commodity(COMMODITY_SUPPHIRE) {}

private:

};

class JadeCommodity : public Commodity {
public:
	JadeCommodity() : Commodity(COMMODITY_JADE) {}

private:

};

class PearlCommodity : public Commodity {
public:
	PearlCommodity() : Commodity(COMMODITY_PEARL) {}

private:

};

class GoldCommodity : public Commodity {
public:
	GoldCommodity() : Commodity(COMMODITY_GOLD) {}

private:

};

class PlatinumCommodity : public Commodity {
public:
	PlatinumCommodity() : Commodity(COMMODITY_PLATINUM) {}

private:

};

class SilverCommodity : public Commodity {
public:
	SilverCommodity() : Commodity(COMMODITY_SILVER) {}

private:

};

class RingCommodity : public Commodity {
public:
	RingCommodity() : Commodity(COMMODITY_RING) {}

private:

};

class NecklaceCommodity : public Commodity {
public:
	NecklaceCommodity() : Commodity(COMMODITY_NECKLACE) {}

private:

};

class EarringsCommodity : public Commodity {
public:
	EarringsCommodity() : Commodity(COMMODITY_EARRINGS) {}

private:

};

class BraceletCommodity : public Commodity {
public:
	BraceletCommodity() : Commodity(COMMODITY_BRACELET) {}

private:

};

class PendantCommodity : public Commodity {
public:
	PendantCommodity() : Commodity(COMMODITY_PENDANT) {}

private:

};

class SwordCommodity : public Commodity {
public:
	SwordCommodity() : Commodity(COMMODITY_SWORD) {}

private:

};

class DaggerCommodity : public Commodity {
public:
	DaggerCommodity() : Commodity(COMMODITY_DAGGER) {}

private:

};

class AxeCommodity : public Commodity {
public:
	AxeCommodity() : Commodity(COMMODITY_AXE) {}

private:

};

class SpearCommodity : public Commodity {
public:
	SpearCommodity() : Commodity(COMMODITY_SPEAR) {}

private:

};

class DartCommodity : public Commodity {
public:
	DartCommodity() : Commodity(COMMODITY_DART) {}

private:

};

class PistolCommodity : public Commodity {
public:
	PistolCommodity() : Commodity(COMMODITY_PISTOL) {}

private:

};

class RifleCommodity : public Commodity {
public:
	RifleCommodity() : Commodity(COMMODITY_RIFLE) {}

private:

};

class SniperCommodity : public Commodity {
public:
	SniperCommodity() : Commodity(COMMODITY_SNIPER) {}

private:

};

class SmgCommodity : public Commodity {
public:
	SmgCommodity() : Commodity(COMMODITY_SMG) {}

private:

};

class ShotgunCommodity : public Commodity {
public:
	ShotgunCommodity() : Commodity(COMMODITY_SHOTGUN) {}

private:

};

class MachinegunCommodity : public Commodity {
public:
	MachinegunCommodity() : Commodity(COMMODITY_MACHINEGUN) {}

private:

};

class GrenadeCommodity : public Commodity {
public:
	GrenadeCommodity() : Commodity(COMMODITY_GRENADE) {}

private:

};

class BowCommodity : public Commodity {
public:
	BowCommodity() : Commodity(COMMODITY_BOW) {}

private:

};

class CrossbowCommodity : public Commodity {
public:
	CrossbowCommodity() : Commodity(COMMODITY_CROSSBOW) {}

private:

};

class MolotovCommodity : public Commodity {
public:
	MolotovCommodity() : Commodity(COMMODITY_MOLOTOV) {}

private:

};

class RocketCommodity : public Commodity {
public:
	RocketCommodity() : Commodity(COMMODITY_ROCKET) {}

private:

};

class MortarCommodity : public Commodity {
public:
	MortarCommodity() : Commodity(COMMODITY_MORTAR) {}

private:

};

class ArtilleryCommodity : public Commodity {
public:
	ArtilleryCommodity() : Commodity(COMMODITY_ARTILLERY) {}

private:

};

class LandmineCommodity : public Commodity {
public:
	LandmineCommodity() : Commodity(COMMODITY_LANDMINE) {}

private:

};

class C4Commodity : public Commodity {
public:
	C4Commodity() : Commodity(COMMODITY_C4) {}

private:

};

class MissileCommodity : public Commodity {
public:
	MissileCommodity() : Commodity(COMMODITY_MISSILE) {}

private:

};

class TankCommodity : public Commodity {
public:
	TankCommodity() : Commodity(COMMODITY_TANK) {}

private:

};

class NavalCommodity : public Commodity {
public:
	NavalCommodity() : Commodity(COMMODITY_NAVAL) {}

private:

};

class TaserCommodity : public Commodity {
public:
	TaserCommodity() : Commodity(COMMODITY_TASER) {}

private:

};

class SprayCommodity : public Commodity {
public:
	SprayCommodity() : Commodity(COMMODITY_SPRAY) {}

private:

};

class FlashbangCommodity : public Commodity {
public:
	FlashbangCommodity() : Commodity(COMMODITY_FLASHBANG) {}

private:

};

class LazergunCommodity : public Commodity {
public:
	LazergunCommodity() : Commodity(COMMODITY_LAZERGUN) {}

private:

};

class PaintingCommodity : public Commodity {
public:
	PaintingCommodity() : Commodity(COMMODITY_PAINTING) {}

private:

};

class SculptureCommodity : public Commodity {
public:
	SculptureCommodity() : Commodity(COMMODITY_SCULPTURE) {}

private:

};

class CalligraphyCommodity : public Commodity {
public:
	CalligraphyCommodity() : Commodity(COMMODITY_CALLIGRAPHY) {}

private:

};

class SketchCommodity : public Commodity {
public:
	SketchCommodity() : Commodity(COMMODITY_SKETCH) {}

private:

};

class ComicCommodity : public Commodity {
public:
	ComicCommodity() : Commodity(COMMODITY_COMIC) {}

private:

};

class EmbroideryCommodity : public Commodity {
public:
	EmbroideryCommodity() : Commodity(COMMODITY_EMBROIDERY) {}

private:

};

class BookCommodity : public Commodity {
public:
	BookCommodity() : Commodity(COMMODITY_BOOK) {}

private:

};

class CostumeCommodity : public Commodity {
public:
	CostumeCommodity() : Commodity(COMMODITY_COSTUME) {}

private:

};

class PhotoCommodity : public Commodity {
public:
	PhotoCommodity() : Commodity(COMMODITY_PHOTO) {}

private:

};

class PainkillerCommodity : public Commodity {
public:
	PainkillerCommodity() : Commodity(COMMODITY_PAINKILLER) {}

private:

};

class ColdpillCommodity : public Commodity {
public:
	ColdpillCommodity() : Commodity(COMMODITY_COLDPILL) {}

private:

};

class AntipyreticCommodity : public Commodity {
public:
	AntipyreticCommodity() : Commodity(COMMODITY_ANTIPYRETIC) {}

private:

};

class AntibioticCommodity : public Commodity {
public:
	AntibioticCommodity() : Commodity(COMMODITY_ANTIBIOTIC) {}

private:

};

class AntiinflammatoryCommodity : public Commodity {
public:
	AntiinflammatoryCommodity() : Commodity(COMMODITY_ANTIIFLAMMATORY) {}

private:

};

class AntidiarrhealCommodity : public Commodity {
public:
	AntidiarrhealCommodity() : Commodity(COMMODITY_ANTIDIARRHEAL) {}

private:

};

class BandageCommodity : public Commodity {
public:
	BandageCommodity() : Commodity(COMMODITY_BANDAGE) {}

private:

};

class GauzeCommodity : public Commodity {
public:
	GauzeCommodity() : Commodity(COMMODITY_GAUZE) {}

private:

};

class AntisepticCommodity : public Commodity {
public:
	AntisepticCommodity() : Commodity(COMMODITY_ANTISEPTIC) {}

private:

};

class SwabCommodity : public Commodity {
public:
	SwabCommodity() : Commodity(COMMODITY_SWAB) {}

private:

};

class InsulinCommodity : public Commodity {
public:
	InsulinCommodity() : Commodity(COMMODITY_INSULIN) {}

private:

};

class SedativeCommodity : public Commodity {
public:
	SedativeCommodity() : Commodity(COMMODITY_SEDATIVE) {}

private:

};

class SleepingpillCommodity : public Commodity {
public:
	SleepingpillCommodity() : Commodity(COMMODITY_SLEEPINGPILL) {}

private:

};

class EyedropCommodity : public Commodity {
public:
	EyedropCommodity() : Commodity(COMMODITY_EYEDROP) {}

private:

};

class VitaminCommodity : public Commodity {
public:
	VitaminCommodity() : Commodity(COMMODITY_VITAMIN) {}

private:

};

class ProteinCommodity : public Commodity {
public:
	ProteinCommodity() : Commodity(COMMODITY_PROTEIN) {}

private:

};

class MorphineCommodity : public Commodity {
public:
	MorphineCommodity() : Commodity(COMMODITY_MORPHINE) {}

private:

};

class PoisonCommodity : public Commodity {
public:
	PoisonCommodity() : Commodity(COMMODITY_POISON) {}

private:

};

class StimulantCommodity : public Commodity {
public:
	StimulantCommodity() : Commodity(COMMODITY_STIMULANT) {}

private:

};

class EpipenCommodity : public Commodity {
public:
	EpipenCommodity() : Commodity(COMMODITY_EPIPEN) {}

private:

};

class DrugCommodity : public Commodity {
public:
	DrugCommodity() : Commodity(COMMODITY_DRUG) {}

private:

};
