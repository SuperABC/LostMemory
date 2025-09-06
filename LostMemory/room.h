#pragma once

#include "plot.h"

#include <string>


enum ROOM_TYPE {
	ROOM_NONE, //无

	// 居住
	ROOM_HOME, // 住宅
	ROOM_VILLA, //别墅

	// 商业
	ROOM_MARKET, //超市
	ROOM_INGREDIENT, //菜市场
	ROOM_GROCERY, //杂货店
	ROOM_CLOTHES, //服装店
	ROOM_ANTIQUE, //古董行
	ROOM_JEWERY, //珠宝店
	ROOM_SMOKEWINETEA, //烟酒茶专卖店
	ROOM_ELECTRONIC, //电子产品店
	ROOM_STUDIO, //影音棚
	ROOM_HAIRCUT, //理发店
	ROOM_COSMETIC, //美容店
	ROOM_PET, //宠物店
	ROOM_COPY, //文印店
	ROOM_MUSIC, //琴行
	ROOM_BOOK, //书店
	ROOM_CHESSCARD, //棋牌室
	ROOM_NET, //网吧
	ROOM_KTV, //歌厅
	ROOM_ARCADE, //游戏厅
	ROOM_BILLIARD, //台球室
	ROOM_TOY, //玩具店
	ROOM_FURNITURE, //家具城
	ROOM_CARWASH, //洗车店
	ROOM_4S, //售车店
	ROOM_REPAIR, //汽修厂
	ROOM_RESTAURANT, //传统餐厅
	ROOM_FASTFOOD, //快餐店
	ROOM_BUFFET, //自助餐店
	ROOM_DRINK, //饮品店
	ROOM_BAR, //酒吧
	ROOM_CARRENT, //租车店
	ROOM_STAGE, //演出大厅
	ROOM_MOVIE, //电影放映厅
	ROOM_EXHIBITION, //展览室
	ROOM_MASAGE, //按摩室
	ROOM_SAUNA, //桑拿房
	ROOM_BATH, //澡堂

	// 办公
	ROOM_OFFICE, //办公室
	ROOM_LAB, //实验室

	// 工业
	ROOM_MACHINE, //车间
	ROOM_PIPELINE, //流水线
	ROOM_BOILER, //锅炉房
	ROOM_WAREHOUSE, //仓库
	ROOM_MINING, //矿场
	ROOM_OILING, //油井
	ROOM_QUARRY, //采石场
	ROOM_FARM, //农场
	ROOM_PASTURE, //牧场
	ROOM_BREEDING, //养殖场
	ROOM_FISHING, //渔场
	ROOM_ORCHARD, //果园
	ROOM_FOREST, //树林

	// 绿化
	ROOM_PARK, //公园
	ROOM_PLAZA, //广场
	ROOM_STATUE, //雕像
	ROOM_ANIMAL, //动物场地
	ROOM_PLANT, //植物温室
	ROOM_AQUARIUM, //水族馆
	ROOM_AMUSEMENT, //游乐场
	ROOM_GYM, //健身房
	ROOM_FOOTBALL, //足球场
	ROOM_BASKETBALL, //篮球场
	ROOM_VOLLEYBALL, //排球场
	ROOM_BADMINTON, //羽毛球场
	ROOM_TABLETENNIS, //乒乓球场
	ROOM_TENNIS, //网球场
	ROOM_SKATE, //滑冰场
	ROOM_BOWLING, //保龄球场
	ROOM_ARCHERY, //射箭场
	ROOM_RANGE, //靶场
	ROOM_POOL, //游泳池
	ROOM_RESORT, // 度假村
	ROOM_REMAINS, // 遗迹

	// 公共服务
	ROOM_CLASS, //教室
	ROOM_REVIEW, //自习室
	ROOM_EMERGENCY, //急诊室
	ROOM_OUTPATIENT, //门诊室
	ROOM_OPERATION, //手术室
	ROOM_ICU, //重症监护室
	ROOM_DOCTOR, //诊室
	ROOM_ASSAY, //化验室
	ROOM_MOTUARY, //太平间
	ROOM_CELL, //牢房
	ROOM_COURT, //法庭
	ROOM_GOLD, //金库
	ROOM_STOCK, //证券交易所
	ROOM_READING, //阅读室
	ROOM_GASOLINE, //加油站
	ROOM_FUNERAL, //灵堂
	ROOM_CONDOLENCE, //吊唁室
	ROOM_COMPUTER, //机房

	// 组件
	ROOM_PARKING, //停车场
	ROOM_GUARD, //保安室
	ROOM_CLEAN, //清洁室
	ROOM_TOILET, //公厕
	ROOM_CANTEEN, //食堂
	ROOM_DOMITRY, //宿舍
	ROOM_PLAYGROUND, //操场
	ROOM_RECEPTION, //服务大堂
	ROOM_MEETING, //会议室
	ROOM_ACTIVITY, //活动室
	ROOM_BUNK, //客房
	ROOM_CHANGING, //更衣室
	ROOM_DEVICE, //设备

	// 交通
	ROOM_METRO, //地铁站台
	ROOM_TRAIN, //火车站台
	ROOM_PLANE, //候机室
	ROOM_SHIP, //候船室
	ROOM_CHECKIN, //安检
	ROOM_TICKET, //售票处
	ROOM_CUSTOM, //海关

	ROOM_END
};

static std::string roomText[ROOM_END] = {
	"无",
	"住宅",
	"别墅",
	"超市",
	"菜市场",
	"杂货店",
	"服装店",
	"古董行",
	"珠宝店",
	"烟酒茶专卖店",
	"电子产品店",
	"影音棚",
	"理发店",
	"美容店",
	"宠物店",
	"文印店",
	"琴行",
	"书店",
	"棋牌室",
	"网吧",
	"歌厅",
	"游戏厅",
	"台球室",
	"玩具店",
	"家具城",
	"洗车店",
	"售车店",
	"汽修厂",
	"传统餐厅",
	"快餐店",
	"自助餐店",
	"饮品店",
	"酒吧",
	"租车店",
	"演出大厅",
	"电影放映厅",
	"展览室",
	"按摩室",
	"桑拿房",
	"澡堂",
	"办公室",
	"实验室",
	"车间",
	"流水线",
	"锅炉房",
	"仓库",
	"矿场",
	"油井",
	"采石场",
	"农场",
	"牧场",
	"养殖场",
	"渔场",
	"果园",
	"树林",
	"公园",
	"广场",
	"雕像",
	"动物场地",
	"植物温室",
	"水族箱",
	"游乐场",
	"健身房",
	"足球场",
	"篮球场",
	"排球场",
	"羽毛球场",
	"乒乓球场",
	"网球场",
	"滑冰场",
	"保龄球场",
	"射箭场",
	"靶场",
	"游泳池",
	"度假村",
	"遗迹",
	"教室",
	"自习室",
	"急诊室",
	"门诊室",
	"手术室",
	"重症监护室",
	"诊室",
	"化验室",
	"太平间",
	"牢房",
	"法庭",
	"金库",
	"证券交易所",
	"阅读室",
	"加油站",
	"灵堂",
	"吊唁室",
	"机房",
	"停车场",
	"保安室",
	"清洁室",
	"公厕",
	"食堂",
	"宿舍",
	"操场",
	"服务大堂",
	"会议室",
	"活动室",
	"客房",
	"更衣室",
	"设备",
	"地铁站台",
	"火车站台",
	"候机室",
	"候船室",
	"安检",
	"售票处",
	"海关"
};

class Room : public Rect {
public:
	Room(ROOM_TYPE type) : type(type) {}

	// 获取/设置类型
	ROOM_TYPE GetType() const;
	void SetType(ROOM_TYPE type);

	// 获取/设置属性
	int GetOwner() const { return owner; }
	void SetOwner(int owner) { this->owner = owner; }
	int GetLayer() const { return layer; }
	void SetLayer(int layer) { this->layer = layer; }
	int GetAcreage() const { return acreage; }
	void SetAcreage(int acreage) { this->acreage = acreage; }

private:
	ROOM_TYPE type;
	int id;
	int owner;
	int layer;
	int acreage;

	int buildingId;
	int componentId;
};

class HomeRoom : public Room {
public:
	HomeRoom() : Room(ROOM_HOME) {}

private:

};

class VillaRoom : public Room {
public:
	VillaRoom() : Room(ROOM_VILLA) {}

private:

};

class MarketRoom : public Room {
public:
	MarketRoom() : Room(ROOM_MARKET) {}

private:

};

class IngredientRoom : public Room {
public:
	IngredientRoom() : Room(ROOM_INGREDIENT) {}

private:

};

class GroceryRoom : public Room {
public:
	GroceryRoom() : Room(ROOM_GROCERY) {}

private:

};

class ClothesRoom : public Room {
public:
	ClothesRoom() : Room(ROOM_CLOTHES) {}

private:

};

class AntiqueRoom : public Room {
public:
	AntiqueRoom() : Room(ROOM_ANTIQUE) {}

private:

};

class JeweryRoom : public Room {
public:
	JeweryRoom() : Room(ROOM_JEWERY) {}

private:

};

class SmokewineteaRoom : public Room {
public:
	SmokewineteaRoom() : Room(ROOM_SMOKEWINETEA) {}

private:

};

class ElectronicRoom : public Room {
public:
	ElectronicRoom() : Room(ROOM_ELECTRONIC) {}

private:

};

class StudioRoom : public Room {
public:
	StudioRoom() : Room(ROOM_STUDIO) {}

private:

};

class HaircutRoom : public Room {
public:
	HaircutRoom() : Room(ROOM_HAIRCUT) {}

private:

};

class CosmeticRoom : public Room {
public:
	CosmeticRoom() : Room(ROOM_COSMETIC) {}

private:

};

class PetRoom : public Room {
public:
	PetRoom() : Room(ROOM_PET) {}

private:

};

class CopyRoom : public Room {
public:
	CopyRoom() : Room(ROOM_COPY) {}

private:

};

class MusicRoom : public Room {
public:
	MusicRoom() : Room(ROOM_MUSIC) {}

private:

};

class BookRoom : public Room {
public:
	BookRoom() : Room(ROOM_BOOK) {}

private:

};

class ChesscardRoom : public Room {
public:
	ChesscardRoom() : Room(ROOM_CHESSCARD) {}

private:

};

class NetRoom : public Room {
public:
	NetRoom() : Room(ROOM_NET) {}

private:

};

class KtvRoom : public Room {
public:
	KtvRoom() : Room(ROOM_KTV) {}

private:

};

class ArcadeRoom : public Room {
public:
	ArcadeRoom() : Room(ROOM_ARCADE) {}

private:

};

class BilliardRoom : public Room {
public:
	BilliardRoom() : Room(ROOM_BILLIARD) {}

private:

};

class ToyRoom : public Room {
public:
	ToyRoom() : Room(ROOM_TOY) {}

private:

};

class FurnitureRoom : public Room {
public:
	FurnitureRoom() : Room(ROOM_FURNITURE) {}

private:

};

class CarwashRoom : public Room {
public:
	CarwashRoom() : Room(ROOM_CARWASH) {}

private:

};

class FourSRoom : public Room {
public:
	FourSRoom() : Room(ROOM_4S) {}

private:

};

class RepairRoom : public Room {
public:
	RepairRoom() : Room(ROOM_REPAIR) {}

private:

};

class RestaurantRoom : public Room {
public:
	RestaurantRoom() : Room(ROOM_RESTAURANT) {}

private:

};

class FastfoodRoom : public Room {
public:
	FastfoodRoom() : Room(ROOM_FASTFOOD) {}

private:

};

class BuffetRoom : public Room {
public:
	BuffetRoom() : Room(ROOM_BUFFET) {}

private:

};

class DrinkRoom : public Room {
public:
	DrinkRoom() : Room(ROOM_DRINK) {}

private:

};

class BarRoom : public Room {
public:
	BarRoom() : Room(ROOM_BAR) {}

private:

};

class CarrentRoom : public Room {
public:
	CarrentRoom() : Room(ROOM_CARRENT) {}

private:

};

class StageRoom : public Room {
public:
	StageRoom() : Room(ROOM_STAGE) {}

private:

};

class MovieRoom : public Room {
public:
	MovieRoom() : Room(ROOM_MOVIE) {}

private:

};

class ExhibitionRoom : public Room {
public:
	ExhibitionRoom() : Room(ROOM_EXHIBITION) {}

private:

};

class MasageRoom : public Room {
public:
	MasageRoom() : Room(ROOM_MASAGE) {}

private:

};

class SaunaRoom : public Room {
public:
	SaunaRoom() : Room(ROOM_SAUNA) {}

private:

};

class BathRoom : public Room {
public:
	BathRoom() : Room(ROOM_BATH) {}

private:

};

class OfficeRoom : public Room {
public:
	OfficeRoom() : Room(ROOM_OFFICE) {}

private:

};

class LabRoom : public Room {
public:
	LabRoom() : Room(ROOM_LAB) {}

private:

};

class MachineRoom : public Room {
public:
	MachineRoom() : Room(ROOM_MACHINE) {}

private:

};

class PipelineRoom : public Room {
public:
	PipelineRoom() : Room(ROOM_PIPELINE) {}

private:

};

class BoilerRoom : public Room {
public:
	BoilerRoom() : Room(ROOM_BOILER) {}

private:

};

class WarehouseRoom : public Room {
public:
	WarehouseRoom() : Room(ROOM_WAREHOUSE) {}

private:

};

class MiningRoom : public Room {
public:
	MiningRoom() : Room(ROOM_MINING) {}

private:

};

class OilingRoom : public Room {
public:
	OilingRoom() : Room(ROOM_OILING) {}

private:

};

class QuarryRoom : public Room {
public:
	QuarryRoom() : Room(ROOM_QUARRY) {}

private:

};

class FarmRoom : public Room {
public:
	FarmRoom() : Room(ROOM_FARM) {}

private:

};

class PastureRoom : public Room {
public:
	PastureRoom() : Room(ROOM_PASTURE) {}

private:

};

class BreedingRoom : public Room {
public:
	BreedingRoom() : Room(ROOM_BREEDING) {}

private:

};

class FishingRoom : public Room {
public:
	FishingRoom() : Room(ROOM_FISHING) {}

private:

};

class OrchardRoom : public Room {
public:
	OrchardRoom() : Room(ROOM_ORCHARD) {}

private:

};

class ForestRoom : public Room {
public:
	ForestRoom() : Room(ROOM_FOREST) {}

private:

};

class ParkRoom : public Room {
public:
	ParkRoom() : Room(ROOM_PARK) {}

private:

};

class PlazaRoom : public Room {
public:
	PlazaRoom() : Room(ROOM_PLAZA) {}

private:

};

class StatueRoom : public Room {
public:
	StatueRoom() : Room(ROOM_STATUE) {}

private:

};

class AnimalRoom : public Room {
public:
	AnimalRoom() : Room(ROOM_ANIMAL) {}

private:

};

class PlantRoom : public Room {
public:
	PlantRoom() : Room(ROOM_PLANT) {}

private:

};

class AquariumRoom : public Room {
public:
	AquariumRoom() : Room(ROOM_AQUARIUM) {}

private:

};

class AmusementRoom : public Room {
public:
	AmusementRoom() : Room(ROOM_AMUSEMENT) {}

private:

};

class GymRoom : public Room {
public:
	GymRoom() : Room(ROOM_GYM) {}

private:

};

class FootballRoom : public Room {
public:
	FootballRoom() : Room(ROOM_FOOTBALL) {}

private:

};

class BasketballRoom : public Room {
public:
	BasketballRoom() : Room(ROOM_BASKETBALL) {}

private:

};

class VolleyballRoom : public Room {
public:
	VolleyballRoom() : Room(ROOM_VOLLEYBALL) {}

private:

};

class BadmintonRoom : public Room {
public:
	BadmintonRoom() : Room(ROOM_BADMINTON) {}

private:

};

class TabletennisRoom : public Room {
public:
	TabletennisRoom() : Room(ROOM_TABLETENNIS) {}

private:

};

class TennisRoom : public Room {
public:
	TennisRoom() : Room(ROOM_TENNIS) {}

private:

};

class SkateRoom : public Room {
public:
	SkateRoom() : Room(ROOM_SKATE) {}

private:

};

class BowlingRoom : public Room {
public:
	BowlingRoom() : Room(ROOM_BOWLING) {}

private:

};

class ArcheryRoom : public Room {
public:
	ArcheryRoom() : Room(ROOM_ARCHERY) {}

private:

};

class RangeRoom : public Room {
public:
	RangeRoom() : Room(ROOM_RANGE) {}

private:

};

class PoolRoom : public Room {
public:
	PoolRoom() : Room(ROOM_POOL) {}

private:

};

class ResortRoom : public Room {
public:
	ResortRoom() : Room(ROOM_RESORT) {}

private:

};

class RemainsRoom : public Room {
public:
	RemainsRoom() : Room(ROOM_REMAINS) {}

private:

};

class ClassRoom : public Room {
public:
	ClassRoom() : Room(ROOM_CLASS) {}

private:

};

class ReviewRoom : public Room {
public:
	ReviewRoom() : Room(ROOM_REVIEW) {}

private:

};

class EmergencyRoom : public Room {
public:
	EmergencyRoom() : Room(ROOM_EMERGENCY) {}

private:

};

class OutpatientRoom : public Room {
public:
	OutpatientRoom() : Room(ROOM_OUTPATIENT) {}

private:

};

class OperationRoom : public Room {
public:
	OperationRoom() : Room(ROOM_OPERATION) {}

private:

};

class IcuRoom : public Room {
public:
	IcuRoom() : Room(ROOM_ICU) {}

private:

};

class DoctorRoom : public Room {
public:
	DoctorRoom() : Room(ROOM_DOCTOR) {}

private:

};

class AssayRoom : public Room {
public:
	AssayRoom() : Room(ROOM_ASSAY) {}

private:

};

class MotuaryRoom : public Room {
public:
	MotuaryRoom() : Room(ROOM_MOTUARY) {}

private:

};

class CellRoom : public Room {
public:
	CellRoom() : Room(ROOM_CELL) {}

private:

};

class CourtRoom : public Room {
public:
	CourtRoom() : Room(ROOM_COURT) {}

private:

};

class GoldRoom : public Room {
public:
	GoldRoom() : Room(ROOM_GOLD) {}

private:

};

class StockRoom : public Room {
public:
	StockRoom() : Room(ROOM_STOCK) {}

private:

};

class ReadingRoom : public Room {
public:
	ReadingRoom() : Room(ROOM_READING) {}

private:

};

class GasolineRoom : public Room {
public:
	GasolineRoom() : Room(ROOM_GASOLINE) {}

private:

};

class FuneralRoom : public Room {
public:
	FuneralRoom() : Room(ROOM_FUNERAL) {}

private:

};

class CondolenceRoom : public Room {
public:
	CondolenceRoom() : Room(ROOM_CONDOLENCE) {}

private:

};

class ComputerRoom : public Room {
public:
	ComputerRoom() : Room(ROOM_COMPUTER) {}

private:

};

class ParkingRoom : public Room {
public:
	ParkingRoom() : Room(ROOM_PARKING) {}

private:

};

class GuardRoom : public Room {
public:
	GuardRoom() : Room(ROOM_GUARD) {}

private:

};

class CleanRoom : public Room {
public:
	CleanRoom() : Room(ROOM_CLEAN) {}

private:

};

class ToiletRoom : public Room {
public:
	ToiletRoom() : Room(ROOM_TOILET) {}

private:

};

class CanteenRoom : public Room {
public:
	CanteenRoom() : Room(ROOM_CANTEEN) {}

private:

};

class DomitryRoom : public Room {
public:
	DomitryRoom() : Room(ROOM_DOMITRY) {}

private:

};

class PlaygroundRoom : public Room {
public:
	PlaygroundRoom() : Room(ROOM_PLAYGROUND) {}

private:

};

class ReceptionRoom : public Room {
public:
	ReceptionRoom() : Room(ROOM_RECEPTION) {}

private:

};

class MeetingRoom : public Room {
public:
	MeetingRoom() : Room(ROOM_MEETING) {}

private:

};

class ActivityRoom : public Room {
public:
	ActivityRoom() : Room(ROOM_ACTIVITY) {}

private:

};

class BunkRoom : public Room {
public:
	BunkRoom() : Room(ROOM_BUNK) {}

private:

};

class ChangingRoom : public Room {
public:
	ChangingRoom() : Room(ROOM_CHANGING) {}

private:

};

class DeviceRoom : public Room {
public:
	DeviceRoom() : Room(ROOM_DEVICE) {}

private:

};

class MetroRoom : public Room {
public:
	MetroRoom() : Room(ROOM_METRO) {}

private:

};

class TrainRoom : public Room {
public:
	TrainRoom() : Room(ROOM_TRAIN) {}

private:

};

class PlaneRoom : public Room {
public:
	PlaneRoom() : Room(ROOM_PLANE) {}

private:

};

class ShipRoom : public Room {
public:
	ShipRoom() : Room(ROOM_SHIP) {}

private:

};

class CheckinRoom : public Room {
public:
	CheckinRoom() : Room(ROOM_CHECKIN) {}

private:

};

class TicketRoom : public Room {
public:
	TicketRoom() : Room(ROOM_TICKET) {}

private:

};

class CustomRoom : public Room {
public:
	CustomRoom() : Room(ROOM_CUSTOM) {}

private:

};

std::shared_ptr<Room> CreateRoom(ROOM_TYPE type);

