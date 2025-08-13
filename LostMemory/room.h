#pragma once

#include "plot.h"

#include <string>


enum ROOM_TYPE {
	ROOM_NONE, //无
	ROOM_DEVICE, //设备
	ROOM_PARKING, //停车区
	ROOM_GUARD, //保安室
	ROOM_CLEAN, //清洁室
	ROOM_HIGHWAY, //高速收费站
	ROOM_GASOLINE, //加油区
	ROOM_HOME, //住宅
	ROOM_VILLA, //别墅
	ROOM_WAREHOUSE, //仓库
	ROOM_PROPERTY, //售楼处
	ROOM_OFFICE, //办公室
	ROOM_DOMITRY, //宿舍
	ROOM_CANTEEN, //餐厅
	ROOM_ACTIVITY, //活动室
	ROOM_STAGE, //演出大厅
	ROOM_GROCERY, //杂货店
	ROOM_MUSIC, //琴行
	ROOM_TOILET, //公厕
	ROOM_MARKET, //超市
	ROOM_BUNK, //客房
	ROOM_RECEPTION, //服务大堂
	ROOM_INGREDIENT, //菜市场
	ROOM_SALE, //商店
	ROOM_BRAND, //品牌店
	ROOM_CLOTHES, //服装店
	ROOM_RESTAURANT, //饭店
	ROOM_FASTFOOD, //快餐店
	ROOM_BUFFET, //自助餐店
	ROOM_COFFEE, //咖啡厅
	ROOM_DRINK, //饮品店
	ROOM_CINEMA, //电影院
	ROOM_CARRENT, //租车店
	ROOM_HAIRCUT, //理发店
	ROOM_SMOKEWINETEA, //烟酒茶专卖店
	ROOM_ELECTRONIC, //电子产品店
	ROOM_BOOK, //书店
	ROOM_MOVIE, //电影放映厅
	ROOM_PUB, //酒吧
	ROOM_MASAGE, //按摩室
	ROOM_SAUNA, //桑拿房
	ROOM_BATH, //洗浴堂
	ROOM_CHANGING, //更衣室
	ROOM_PUBLICEAT, //卡座区
	ROOM_PRIVATEEAT, //包间
	ROOM_KITCHEN, //厨房
	ROOM_MEETING, //会议室
	ROOM_COMPUTER, //机房
	ROOM_STOCK, //证券交易所
	ROOM_STUDIO, //影音棚
	ROOM_MAKEUP, //化妆室
	ROOM_ANIMAL, //动物房间
	ROOM_PLANT, //植物温室
	ROOM_EXHIBITION, //展览室
	ROOM_READING, //阅读室
	ROOM_COURT, //法庭
	ROOM_LAB, //实验室
	ROOM_MACHINE, //车间
	ROOM_PIPELINE, //流水线
	ROOM_CONSTRUCTION, //建筑工地
	ROOM_CHICKEN, //鸡舍
	ROOM_COW, //牛棚
	ROOM_PIG, //猪圈
	ROOM_SHEEP, //羊圈
	ROOM_FOOTBALL, //足球室
	ROOM_BASKETBALL, //篮球室
	ROOM_VOLLEYBALL, //排球室
	ROOM_BADMINTON, //羽毛球室
	ROOM_TABLETENNIS, //乒乓球室
	ROOM_TENNIS, //网球室
	ROOM_SKATE, //滑冰室
	ROOM_BOWLING, //保龄球室
	ROOM_ARCHERY, //射箭室
	ROOM_RANGE, //靶场
	ROOM_POOL, //游泳池
	ROOM_HAIR, //理发店
	ROOM_COSMETIC, //美容店
	ROOM_GYM, //健身房
	ROOM_CHESSCARD, //棋牌室
	ROOM_PET, //宠物店
	ROOM_COPY, //文印店
	ROOM_CARWASH, //洗车店
	ROOM_BICYCLE, //自行车棚
	ROOM_NET, //网吧
	ROOM_ARCADE, //游戏厅
	ROOM_KTV, //歌厅
	ROOM_BILLIARD, //台球室
	ROOM_FURNITURE, //家具城
	ROOM_REVIEW, //自习室
	ROOM_EMERGENCY, //急诊室
	ROOM_OUTPATIENT, //门诊室
	ROOM_OPERATION, //手术室
	ROOM_ICU, //重症监护室
	ROOM_DOCTOR, //诊室
	ROOM_ASSAY, //化验室
	ROOM_CLASS, //教室
	ROOM_PLAYGROUND, //操场
	ROOM_CELL, //牢房
	ROOM_METRO, //地铁站台
	ROOM_TRAIN, //火车站台
	ROOM_PLANE, //候机室
	ROOM_SHIP, //候船室
	ROOM_CHECKIN, //安检
	ROOM_TICKET, //售票处
	ROOM_CUSTOM, //海关
	ROOM_MOTUARY, //太平间
	ROOM_FUNERAL, //灵堂
	ROOM_CONDOLENCE, //吊唁室
	ROOM_BOILER, //锅炉房
	ROOM_GOLD, //金库
	ROOM_END
};

static std::string roomText[ROOM_END] = {
	"无",
	"设备",
	"停车区",
	"保安室",
	"清洁室",
	"高速收费站",
	"加油区",
	"住宅",
	"别墅",
	"仓库",
	"售楼处",
	"办公室",
	"宿舍",
	"餐厅",
	"活动室",
	"演出大厅",
	"杂货店",
	"琴行",
	"公厕",
	"超市",
	"客房",
	"服务大堂",
	"菜市场",
	"商店",
	"品牌店",
	"服装店",
	"饭店",
	"快餐店",
	"自助餐店",
	"咖啡厅",
	"饮品店",
	"电影院",
	"租车店",
	"理发店",
	"烟酒茶专卖店",
	"电子产品店",
	"书店",
	"电影放映厅",
	"酒吧",
	"按摩室",
	"桑拿房",
	"洗浴堂",
	"更衣室",
	"卡座区",
	"包间",
	"厨房",
	"会议室",
	"机房",
	"证券交易所",
	"影音棚",
	"化妆室",
	"动物房间",
	"植物温室",
	"展览室",
	"阅读室",
	"法庭",
	"实验室",
	"车间",
	"流水线",
	"建筑工地",
	"鸡舍",
	"牛棚",
	"猪圈",
	"羊圈",
	"足球室",
	"篮球室",
	"排球室",
	"羽毛球室",
	"乒乓球室",
	"网球室",
	"滑冰室",
	"保龄球室",
	"射箭室",
	"靶场",
	"游泳池",
	"理发店",
	"美容店",
	"健身房",
	"棋牌室",
	"宠物店",
	"文印店",
	"洗车店",
	"自行车棚",
	"网吧",
	"游戏厅",
	"歌厅",
	"台球室",
	"家具城",
	"自习室",
	"急诊室",
	"门诊室",
	"手术室",
	"重症监护室",
	"诊室",
	"化验室",
	"教室",
	"操场",
	"牢房",
	"地铁站台",
	"火车站台",
	"候机室",
	"候船室",
	"安检",
	"售票处",
	"海关",
	"太平间",
	"灵堂",
	"吊唁室",
	"锅炉房",
	"金库"
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
	int organizationId;
};

class DeviceRoom : public Room {
public:
	DeviceRoom() : Room(ROOM_DEVICE) {}

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

class HighwayRoom : public Room {
public:
	HighwayRoom() : Room(ROOM_HIGHWAY) {}

private:

};

class GasolineRoom : public Room {
public:
	GasolineRoom() : Room(ROOM_GASOLINE) {}

private:

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

class WarehouseRoom : public Room {
public:
	WarehouseRoom() : Room(ROOM_WAREHOUSE) {}

private:

};

class PropertyRoom : public Room {
public:
	PropertyRoom() : Room(ROOM_PROPERTY) {}

private:

};

class OfficeRoom : public Room {
public:
	OfficeRoom() : Room(ROOM_OFFICE) {}

private:

};

class DormitoryRoom : public Room {
public:
	DormitoryRoom() : Room(ROOM_DOMITRY) {}

private:

};

class CanteenRoom : public Room {
public:
	CanteenRoom() : Room(ROOM_CANTEEN) {}

private:

};

class ActivityRoom : public Room {
public:
	ActivityRoom() : Room(ROOM_ACTIVITY) {}

private:

};

class StageRoom : public Room {
public:
	StageRoom() : Room(ROOM_STAGE) {}

private:

};

class GroceryRoom : public Room {
public:
	GroceryRoom() : Room(ROOM_GROCERY) {}

private:

};

class MusicRoom : public Room {
public:
	MusicRoom() : Room(ROOM_MUSIC) {}

private:

};

class ToiletRoom : public Room {
public:
	ToiletRoom() : Room(ROOM_TOILET) {}

private:

};

class MarketRoom : public Room {
public:
	MarketRoom() : Room(ROOM_MARKET) {}

private:

};

class BunkRoom : public Room {
public:
	BunkRoom() : Room(ROOM_BUNK) {}

private:

};

class ReceptionRoom : public Room {
public:
	ReceptionRoom() : Room(ROOM_RECEPTION) {}

private:

};

class IngredientRoom : public Room {
public:
	IngredientRoom() : Room(ROOM_INGREDIENT) {}

private:

};

class SaleRoom : public Room {
public:
	SaleRoom() : Room(ROOM_SALE) {}

private:

};

class BrandRoom : public Room {
public:
	BrandRoom() : Room(ROOM_BRAND) {}

private:

};

class ClothesRoom : public Room {
public:
	ClothesRoom() : Room(ROOM_CLOTHES) {}

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

class CoffeeRoom : public Room {
public:
	CoffeeRoom() : Room(ROOM_COFFEE) {}

private:

};

class DrinkRoom : public Room {
public:
	DrinkRoom() : Room(ROOM_DRINK) {}

private:

};

class CinemaRoom : public Room {
public:
	CinemaRoom() : Room(ROOM_CINEMA) {}

private:

};

class CarrentRoom : public Room {
public:
	CarrentRoom() : Room(ROOM_CARRENT) {}

private:

};

class HaircutRoom : public Room {
public:
	HaircutRoom() : Room(ROOM_HAIRCUT) {}

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

class BookRoom : public Room {
public:
	BookRoom() : Room(ROOM_BOOK) {}

private:

};

class MovieRoom : public Room {
public:
	MovieRoom() : Room(ROOM_MOVIE) {}

private:

};

class PubRoom : public Room {
public:
	PubRoom() : Room(ROOM_PUB) {}

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

class ChangingRoom : public Room {
public:
	ChangingRoom() : Room(ROOM_CHANGING) {}

private:

};

class PublicEatRoom : public Room {
public:
	PublicEatRoom() : Room(ROOM_PUBLICEAT) {}

private:

};

class PrivateEatRoom : public Room {
public:
	PrivateEatRoom() : Room(ROOM_PRIVATEEAT) {}

private:

};

class KitchenRoom : public Room {
public:
	KitchenRoom() : Room(ROOM_KITCHEN) {}

private:

};

class MeetingRoom : public Room {
public:
	MeetingRoom() : Room(ROOM_MEETING) {}

private:

};

class ComputerRoom : public Room {
public:
	ComputerRoom() : Room(ROOM_COMPUTER) {}

private:

};

class StockRoom : public Room {
public:
	StockRoom() : Room(ROOM_STOCK) {}

private:

};

class StudioRoom : public Room {
public:
	StudioRoom() : Room(ROOM_STUDIO) {}

private:

};

class MakeupRoom : public Room {
public:
	MakeupRoom() : Room(ROOM_MAKEUP) {}

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

class ExhibitionRoom : public Room {
public:
	ExhibitionRoom() : Room(ROOM_EXHIBITION) {}

private:

};

class ReadingRoom : public Room {
public:
	ReadingRoom() : Room(ROOM_READING) {}

private:

};

class CourtRoom : public Room {
public:
	CourtRoom() : Room(ROOM_COURT) {}

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

class ConstructionRoom : public Room {
public:
	ConstructionRoom() : Room(ROOM_CONSTRUCTION) {}

private:

};

class ChickenRoom : public Room {
public:
	ChickenRoom() : Room(ROOM_CHICKEN) {}

private:

};

class CowRoom : public Room {
public:
	CowRoom() : Room(ROOM_COW) {}

private:

};

class PigRoom : public Room {
public:
	PigRoom() : Room(ROOM_PIG) {}

private:

};

class SheepRoom : public Room {
public:
	SheepRoom() : Room(ROOM_SHEEP) {}

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

class TableTennisRoom : public Room {
public:
	TableTennisRoom() : Room(ROOM_TABLETENNIS) {}

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

class HairRoom : public Room {
public:
	HairRoom() : Room(ROOM_HAIR) {}

private:

};

class CosmeticRoom : public Room {
public:
	CosmeticRoom() : Room(ROOM_COSMETIC) {}

private:

};

class GymRoom : public Room {
public:
	GymRoom() : Room(ROOM_GYM) {}

private:

};

class ChessCardRoom : public Room {
public:
	ChessCardRoom() : Room(ROOM_CHESSCARD) {}

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

class CarWashRoom : public Room {
public:
	CarWashRoom() : Room(ROOM_CARWASH) {}

private:

};

class BicycleRoom : public Room {
public:
	BicycleRoom() : Room(ROOM_BICYCLE) {}

private:

};

class NetRoom : public Room {
public:
	NetRoom() : Room(ROOM_NET) {}

private:

};

class ArcadeRoom : public Room {
public:
	ArcadeRoom() : Room(ROOM_ARCADE) {}

private:

};

class KTVRoom : public Room {
public:
	KTVRoom() : Room(ROOM_KTV) {}

private:

};

class BilliardRoom : public Room {
public:
	BilliardRoom() : Room(ROOM_BILLIARD) {}

private:

};

class FurnitureRoom : public Room {
public:
	FurnitureRoom() : Room(ROOM_FURNITURE) {}

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

class ICURoom : public Room {
public:
	ICURoom() : Room(ROOM_ICU) {}

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

class ClassRoom : public Room {
public:
	ClassRoom() : Room(ROOM_CLASS) {}

private:

};

class PlaygroundRoom : public Room {
public:
	PlaygroundRoom() : Room(ROOM_PLAYGROUND) {}

private:

};

class CellRoom : public Room {
public:
	CellRoom() : Room(ROOM_CELL) {}

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

class MotuaryRoom : public Room {
public:
	MotuaryRoom() : Room(ROOM_MOTUARY) {}

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

class BoilerRoom : public Room {
public:
	BoilerRoom() : Room(ROOM_BOILER) {}

private:

};

class GoldRoom : public Room {
public:
	GoldRoom() : Room(ROOM_GOLD) {}

private:

};

std::shared_ptr<Room> CreateRoom(ROOM_TYPE type);

