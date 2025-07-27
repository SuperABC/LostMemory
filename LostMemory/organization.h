#pragma once

#include "building.h"
#include "room.h"

#include <vector>
#include <string>

class Building;

enum ORGANIZATION_TYPE {
	ORGANIZATION_NONE, //无
	ORGANIZATION_ROADFIX, //路政
	ORGANIZATION_PARKING, //停车场
	ORGANIZATION_BANK, //银行
	ORGANIZATION_LIBRARY, //图书馆
	ORGANIZATION_CLINIC, //诊所
	ORGANIZATION_HOSPITAL, //医院
	ORGANIZATION_INPATIENT, //住院部
	ORGANIZATION_SANATORIUM, //疗养院
	ORGANIZATION_POLICE, //警察局
	ORGANIZATION_FIRE, //消防局
	ORGANIZATION_KINDER, //幼儿园
	ORGANIZATION_PRIMARY, //小学
	ORGANIZATION_MIDDLE, //中学
	ORGANIZATION_UNIVERSITY, //大学
	ORGANIZATION_VOCATIONAL, //职业学校
	ORGANIZATION_CREMATORIUM, //火葬场
	ORGANIZATION_CEMETRY, //墓地
	ORGANIZATION_TVSTATION, //电视台
	ORGANIZATION_GASOLINE, //加油站
	ORGANIZATION_TOILET, //公厕
	ORGANIZATION_DEVICE, //设备
	ORGANIZATION_POST, //邮局
	ORGANIZATION_STATION, //交通站
	ORGANIZATION_COMMUNITY, //社区
	ORGANIZATION_ESTATE, //售楼处
	ORGANIZATION_PROPERTY, //物业
	ORGANIZATION_PACKAGE, //快递站
	ORGANIZATION_HOTEL, //酒店
	ORGANIZATION_RESTAURANT, //传统餐馆
	ORGANIZATION_FASTFOOD, //快餐店
	ORGANIZATION_BUFFET, //自助餐店
	ORGANIZATION_COFFEE, //咖啡厅
	ORGANIZATION_DRINK, //饮品店
	ORGANIZATION_MALL, //商场
	ORGANIZATION_MARKET, //超市
	ORGANIZATION_MUSIC, //琴行
	ORGANIZATION_INGREDIENT, //菜市场
	ORGANIZATION_BRAND, //品牌店
	ORGANIZATION_CARRENT, //租车行
	ORGANIZATION_THEATER, //剧院
	ORGANIZATION_MUSEUM, //博物馆
	ORGANIZATION_ZOO, //动物园
	ORGANIZATION_BOTANIC, //植物园
	ORGANIZATION_AQUARIUM, //水族馆
	ORGANIZATION_CINEMA, //电影院
	ORGANIZATION_PUB, //酒吧
	ORGANIZATION_MASSAGE, //会所
	ORGANIZATION_AMUSEMENT, //游乐设施
	ORGANIZATION_FURNISH, //装修公司
	ORGANIZATION_MOVING, //搬家公司
	ORGANIZATION_OPERATOR, //运营商
	ORGANIZATION_GAME, //游戏公司
	ORGANIZATION_LEASE, //外包公司
	ORGANIZATION_FINANCE, //金融公司
	ORGANIZATION_LENDING, //信贷公司
	ORGANIZATION_SALE, //销售公司
	ORGANIZATION_MEDICAL, //医药公司
	ORGANIZATION_RELATION, //公关公司
	ORGANIZATION_ESHOP, //电商
	ORGANIZATION_STAR, //明星经纪公司
	ORGANIZATION_ENGINEER, //工程设计公司
	ORGANIZATION_CONSTRUCT, //建筑公司
	ORGANIZATION_ART, //艺术设计公司
	ORGANIZATION_PUBLISHER, //出版社
	ORGANIZATION_TRAVEL, //旅行社
	ORGANIZATION_MEDIA, //自媒体
	ORGANIZATION_LAWYER, //律所
	ORGANIZATION_CREW, //剧组
	ORGANIZATION_INSURANCE, //保险公司
	ORGANIZATION_SECURITY, //保安公司
	ORGANIZATION_CLEANING, //保洁公司
	ORGANIZATION_GREEN, //绿化公司
	ORGANIZATION_INTERMEDIARY, //房屋中介
	ORGANIZATION_STOCK, //证券交易所
	ORGANIZATION_COURT, //法院
	ORGANIZATION_ADMIN, //行政办公室
	ORGANIZATION_EDUCATIONDEPT, //教育部
	ORGANIZATION_INFODEPT, //工信部
	ORGANIZATION_FINANCEDEPT, //财政部
	ORGANIZATION_TRADEDEPT, //商务部
	ORGANIZATION_PETITIONDEPT, //信访局
	ORGANIZATION_WEATHERDEPT, //气象局
	ORGANIZATION_TAXDEPT, //税务局
	ORGANIZATION_CIVILDEPT, //民政局
	ORGANIZATION_SCIENCEDEPT, //科学院
	ORGANIZATION_ENGINEERDEPT, //工程院
	ORGANIZATION_SOCIALDEPT, //社科院
	ORGANIZATION_CUSTOMHOUSE, //海关
	ORGANIZATION_DOGE, //反贪局
	ORGANIZATION_COMMITTEE, //学术委员会
	ORGANIZATION_LAB, //实验室
	ORGANIZATION_FACTORY, //工厂
	ORGANIZATION_WAREHOUSE, //仓库
	ORGANIZATION_REPAIR, //汽修厂
	ORGANIZATION_RESOURCE, //资源开采
	ORGANIZATION_PARK, //公园
	ORGANIZATION_PLAZA, //广场
	ORGANIZATION_STATUE, //雕像
	ORGANIZATION_GYM, //健身房
	ORGANIZATION_STADIUM, //运动场
	ORGANIZATION_FOOTBALL, //足球场
	ORGANIZATION_BASKETBALL, //篮球场
	ORGANIZATION_VOLLEYBALL, //排球场
	ORGANIZATION_TENNIS, //网球场
	ORGANIZATION_TABLETENNIS, //乒乓球场
	ORGANIZATION_BADMINTON, //羽毛球场
	ORGANIZATION_GOLF, //高尔夫球场
	ORGANIZATION_SKI, //滑冰场
	ORGANIZATION_SKATE, //滑雪场
	ORGANIZATION_SWIM, //游泳池
	ORGANIZATION_RESORT, //度假村
	ORGANIZATION_REMAINS, //遗迹
	ORGANIZATION_ROCKET, //火箭发射塔
	ORGANIZATION_PLAYGROUND, //操场
	ORGANIZATION_PRISON, //监狱
	ORGANIZATION_GUARD, //保安亭
	ORGANIZATION_CANTEEN, //食堂
	ORGANIZATION_DORMITRY, //宿舍
	ORGANIZATION_DATA, //数据中心
	ORGANIZATION_WATER, //抽水站
	ORGANIZATION_SEWAGE, //污水处理厂
	ORGANIZATION_POWER, //火电厂
	ORGANIZATION_WINDMILL, //风电机
	ORGANIZATION_NUCLEAR, //核电厂
	ORGANIZATION_RECYCLE, //废品回收站
	ORGANIZATION_TRASH, //垃圾填埋场
	ORGANIZATION_INCINERATION, //焚烧厂

	ORGANIZATION_BODY, //体检中心
	ORGANIZATION_DENTIST, //牙科医院
	ORGANIZATION_MENTAL, //精神医院
	ORGANIZATION_AFFAIR, //教务处
	ORGANIZATION_GOLD, //金库
	ORGANIZATION_GROCERY, //杂货店
	ORGANIZATION_CLOTHES, //服装店
	ORGANIZATION_COSMETIC, //美容店
	ORGANIZATION_HAIRCUT, //理发店
	ORGANIZATION_DRUG, //药店
	ORGANIZATION_SMOKEWINETEA, //烟酒茶专卖店
	ORGANIZATION_JEWELRY, //珠宝店
	ORGANIZATION_EXTRACURRICULAR, //教培中心
	ORGANIZATION_CHESSCARD, //棋牌室
	ORGANIZATION_PET, //宠物店
	ORGANIZATION_ELECTRONIC, //电子产品店
	ORGANIZATION_COPY, //文印店
	ORGANIZATION_STUDIO, //影音棚
	ORGANIZATION_CARWASH, //洗车店
	ORGANIZATION_BICYCLE, //自行车店
	ORGANIZATION_HARDWARE, //五金店
	ORGANIZATION_BOOK, //书店
	ORGANIZATION_BILLIARD, //台球室
	ORGANIZATION_NET, //网吧
	ORGANIZATION_KTV, //歌厅
	ORGANIZATION_VENDOR, //小摊
	ORGANIZATION_END
};

static std::string organizationText[ORGANIZATION_END] = {
	"无",
	"路政",
	"停车场",
	"银行",
	"图书馆",
	"诊所",
	"医院",
	"住院部",
	"疗养院",
	"警察局",
	"消防局",
	"幼儿园",
	"小学",
	"中学",
	"大学",
	"职业学校",
	"火葬场",
	"墓地",
	"电视台",
	"加油站",
	"公厕",
	"设备",
	"邮局",
	"交通站",
	"社区",
	"售楼处",
	"物业",
	"快递站",
	"酒店",
	"传统餐馆",
	"快餐店",
	"自助餐店",
	"咖啡厅",
	"饮品店",
	"商场",
	"超市",
	"琴行",
	"菜市场",
	"品牌店",
	"租车行",
	"剧院",
	"博物馆",
	"动物园",
	"植物园",
	"水族馆",
	"电影院",
	"酒吧",
	"会所",
	"游乐设施",
	"装修公司",
	"搬家公司",
	"运营商",
	"游戏公司",
	"外包公司",
	"金融公司",
	"信贷公司",
	"销售公司",
	"医药公司",
	"公关公司",
	"电商",
	"明星经纪公司",
	"工程设计公司",
	"建筑公司",
	"艺术设计公司",
	"出版社",
	"旅行社",
	"自媒体",
	"律所",
	"剧组",
	"保险公司",
	"保安公司",
	"保洁公司",
	"绿化公司",
	"房屋中介",
	"证券交易所",
	"法院",
	"行政办公室",
	"教育部",
	"工信部",
	"财政部",
	"商务部",
	"信访局",
	"气象局",
	"税务局",
	"民政局",
	"科学院",
	"工程院",
	"社科院",
	"海关",
	"反贪局",
	"学术委员会",
	"实验室",
	"工厂",
	"仓库",
	"汽修厂",
	"资源开采",
	"公园",
	"广场",
	"雕像",
	"健身房",
	"运动场",
	"足球场",
	"篮球场",
	"排球场",
	"网球场",
	"乒乓球场",
	"羽毛球场",
	"高尔夫球场",
	"滑冰场",
	"滑雪场",
	"游泳池",
	"度假村",
	"遗迹",
	"火箭发射塔",
	"操场",
	"监狱",
	"保安亭",
	"食堂",
	"宿舍",
	"数据中心",
	"抽水站",
	"污水处理厂",
	"火电厂",
	"风电机",
	"核电厂",
	"废品回收站",
	"垃圾填埋场",
	"焚烧厂",
	"体检中心",
	"牙科医院",
	"精神医院",
	"教务处",
	"金库",
	"杂货店",
	"服装店",
	"美容店",
	"理发店",
	"药店",
	"烟酒茶专卖店",
	"珠宝店",
	"教培中心",
	"棋牌室",
	"宠物店",
	"电子产品店",
	"文印店",
	"影音棚",
	"洗车店",
	"自行车店",
	"五金店",
	"书店",
	"台球室",
	"网吧",
	"歌厅",
	"小摊"
};

class Organization {
public:
	Organization(ORGANIZATION_TYPE type) : type(type) {}

	ORGANIZATION_TYPE GetType();
	void SetType(ORGANIZATION_TYPE type);

	void AddRoom(Room* room) { rooms.push_back(room); }
	int AutoRoom(int space) { return 100; }
	std::vector<Room*>& GetRooms() { return rooms; }

	std::string GetName() { return name; }

private:
	ORGANIZATION_TYPE type;
	int id;
	std::string name;

	std::vector<Room*> rooms;
};

class RoadfixOrganization : public Organization {
public:
	RoadfixOrganization() : Organization(ORGANIZATION_ROADFIX) {}

private:

};

class ParkingOrganization : public Organization {
public:
	ParkingOrganization() : Organization(ORGANIZATION_PARKING) {}

private:

};

class BankOrganization : public Organization {
public:
	BankOrganization() : Organization(ORGANIZATION_BANK) {}

private:

};

class LibraryOrganization : public Organization {
public:
	LibraryOrganization() : Organization(ORGANIZATION_LIBRARY) {}

private:

};

class ClinicOrganization : public Organization {
public:
	ClinicOrganization() : Organization(ORGANIZATION_CLINIC) {}

private:

};

class HospitalOrganization : public Organization {
public:
	HospitalOrganization() : Organization(ORGANIZATION_HOSPITAL) {}

private:

};

class InpatientOrganization : public Organization {
public:
	InpatientOrganization() : Organization(ORGANIZATION_INPATIENT) {}

private:

};

class SanatoriumOrganization : public Organization {
public:
	SanatoriumOrganization() : Organization(ORGANIZATION_SANATORIUM) {}

private:

};

class PoliceOrganization : public Organization {
public:
	PoliceOrganization() : Organization(ORGANIZATION_POLICE) {}

private:

};

class FireOrganization : public Organization {
public:
	FireOrganization() : Organization(ORGANIZATION_FIRE) {}

private:

};

class KinderOrganization : public Organization {
public:
	KinderOrganization() : Organization(ORGANIZATION_KINDER) {}

private:

};

class PrimaryOrganization : public Organization {
public:
	PrimaryOrganization() : Organization(ORGANIZATION_PRIMARY) {}

private:

};

class MiddleOrganization : public Organization {
public:
	MiddleOrganization() : Organization(ORGANIZATION_MIDDLE) {}

private:

};

class UniversityOrganization : public Organization {
public:
	UniversityOrganization() : Organization(ORGANIZATION_UNIVERSITY) {}

private:

};

class VocationalOrganization : public Organization {
public:
	VocationalOrganization() : Organization(ORGANIZATION_VOCATIONAL) {}

private:

};

class CrematoriumOrganization : public Organization {
public:
	CrematoriumOrganization() : Organization(ORGANIZATION_CREMATORIUM) {}

private:

};

class CemetryOrganization : public Organization {
public:
	CemetryOrganization() : Organization(ORGANIZATION_CEMETRY) {}

private:

};

class TVStationOrganization : public Organization {
public:
	TVStationOrganization() : Organization(ORGANIZATION_TVSTATION) {}

private:

};

class GasolineOrganization : public Organization {
public:
	GasolineOrganization() : Organization(ORGANIZATION_GASOLINE) {}

private:

};

class ToiletOrganization : public Organization {
public:
	ToiletOrganization() : Organization(ORGANIZATION_TOILET) {}

private:

};

class DeviceOrganization : public Organization {
public:
	DeviceOrganization() : Organization(ORGANIZATION_DEVICE) {}

private:

};

class PostOrganization : public Organization {
public:
	PostOrganization() : Organization(ORGANIZATION_POST) {}

private:

};

class StationOrganization : public Organization {
public:
	StationOrganization() : Organization(ORGANIZATION_STATION) {}

private:

};

class CommunityOrganization : public Organization {
public:
	CommunityOrganization() : Organization(ORGANIZATION_COMMUNITY) {}

private:

};

class EstateOrganization : public Organization {
public:
	EstateOrganization() : Organization(ORGANIZATION_ESTATE) {}

private:

};

class PropertyOrganization : public Organization {
public:
	PropertyOrganization() : Organization(ORGANIZATION_PROPERTY) {}

private:

};

class PackageOrganization : public Organization {
public:
	PackageOrganization() : Organization(ORGANIZATION_PACKAGE) {}

private:

};

class HotelOrganization : public Organization {
public:
	HotelOrganization() : Organization(ORGANIZATION_HOTEL) {}

private:

};

class RestaurantOrganization : public Organization {
public:
	RestaurantOrganization() : Organization(ORGANIZATION_RESTAURANT) {}

private:

};

class FastfoodOrganization : public Organization {
public:
	FastfoodOrganization() : Organization(ORGANIZATION_FASTFOOD) {}

private:

};

class BuffetOrganization : public Organization {
public:
	BuffetOrganization() : Organization(ORGANIZATION_BUFFET) {}

private:

};

class CoffeeOrganization : public Organization {
public:
	CoffeeOrganization() : Organization(ORGANIZATION_COFFEE) {}

private:

};

class DrinkOrganization : public Organization {
public:
	DrinkOrganization() : Organization(ORGANIZATION_DRINK) {}

private:

};

class MallOrganization : public Organization {
public:
	MallOrganization() : Organization(ORGANIZATION_MALL) {}

private:

};

class MarketOrganization : public Organization {
public:
	MarketOrganization() : Organization(ORGANIZATION_MARKET) {}

private:

};

class MusicOrganization : public Organization {
public:
	MusicOrganization() : Organization(ORGANIZATION_MUSIC) {}

private:

};

class IngredientOrganization : public Organization {
public:
	IngredientOrganization() : Organization(ORGANIZATION_INGREDIENT) {}

private:

};

class BrandOrganization : public Organization {
public:
	BrandOrganization() : Organization(ORGANIZATION_BRAND) {}

private:

};

class CarrentOrganization : public Organization {
public:
	CarrentOrganization() : Organization(ORGANIZATION_CARRENT) {}

private:

};

class TheaterOrganization : public Organization {
public:
	TheaterOrganization() : Organization(ORGANIZATION_THEATER) {}

private:

};

class MuseumOrganization : public Organization {
public:
	MuseumOrganization() : Organization(ORGANIZATION_MUSEUM) {}

private:

};

class ZooOrganization : public Organization {
public:
	ZooOrganization() : Organization(ORGANIZATION_ZOO) {}

private:

};

class BotanicOrganization : public Organization {
public:
	BotanicOrganization() : Organization(ORGANIZATION_BOTANIC) {}

private:

};

class AquariumOrganization : public Organization {
public:
	AquariumOrganization() : Organization(ORGANIZATION_AQUARIUM) {}

private:

};

class CinemaOrganization : public Organization {
public:
	CinemaOrganization() : Organization(ORGANIZATION_CINEMA) {}

private:

};

class PubOrganization : public Organization {
public:
	PubOrganization() : Organization(ORGANIZATION_PUB) {}

private:

};

class MassageOrganization : public Organization {
public:
	MassageOrganization() : Organization(ORGANIZATION_MASSAGE) {}

private:

};

class AmusementOrganization : public Organization {
public:
	AmusementOrganization() : Organization(ORGANIZATION_AMUSEMENT) {}

private:

};

class FurnishOrganization : public Organization {
public:
	FurnishOrganization() : Organization(ORGANIZATION_FURNISH) {}

private:

};

class MovingOrganization : public Organization {
public:
	MovingOrganization() : Organization(ORGANIZATION_MOVING) {}

private:

};

class OperatorOrganization : public Organization {
public:
	OperatorOrganization() : Organization(ORGANIZATION_OPERATOR) {}

private:

};

class GameOrganization : public Organization {
public:
	GameOrganization() : Organization(ORGANIZATION_GAME) {}

private:

};

class LeaseOrganization : public Organization {
public:
	LeaseOrganization() : Organization(ORGANIZATION_LEASE) {}

private:

};

class FinanceOrganization : public Organization {
public:
	FinanceOrganization() : Organization(ORGANIZATION_FINANCE) {}

private:

};

class LendingOrganization : public Organization {
public:
	LendingOrganization() : Organization(ORGANIZATION_LENDING) {}

private:

};

class SaleOrganization : public Organization {
public:
	SaleOrganization() : Organization(ORGANIZATION_SALE) {}

private:

};

class MedicalOrganization : public Organization {
public:
	MedicalOrganization() : Organization(ORGANIZATION_MEDICAL) {}

private:

};

class RelationOrganization : public Organization {
public:
	RelationOrganization() : Organization(ORGANIZATION_RELATION) {}

private:

};

class EshopOrganization : public Organization {
public:
	EshopOrganization() : Organization(ORGANIZATION_ESHOP) {}

private:

};

class StarOrganization : public Organization {
public:
	StarOrganization() : Organization(ORGANIZATION_STAR) {}

private:

};

class EngineerOrganization : public Organization {
public:
	EngineerOrganization() : Organization(ORGANIZATION_ENGINEER) {}

private:

};

class ConstructOrganization : public Organization {
public:
	ConstructOrganization() : Organization(ORGANIZATION_CONSTRUCT) {}

private:

};

class ArtOrganization : public Organization {
public:
	ArtOrganization() : Organization(ORGANIZATION_ART) {}

private:

};

class PublisherOrganization : public Organization {
public:
	PublisherOrganization() : Organization(ORGANIZATION_PUBLISHER) {}

private:

};

class TravelOrganization : public Organization {
public:
	TravelOrganization() : Organization(ORGANIZATION_TRAVEL) {}

private:

};

class MediaOrganization : public Organization {
public:
	MediaOrganization() : Organization(ORGANIZATION_MEDIA) {}

private:

};

class LawyerOrganization : public Organization {
public:
	LawyerOrganization() : Organization(ORGANIZATION_LAWYER) {}

private:

};

class CrewOrganization : public Organization {
public:
	CrewOrganization() : Organization(ORGANIZATION_CREW) {}

private:

};

class InsuranceOrganization : public Organization {
public:
	InsuranceOrganization() : Organization(ORGANIZATION_INSURANCE) {}

private:

};

class SecurityOrganization : public Organization {
public:
	SecurityOrganization() : Organization(ORGANIZATION_SECURITY) {}

private:

};

class CleaningOrganization : public Organization {
public:
	CleaningOrganization() : Organization(ORGANIZATION_CLEANING) {}

private:

};

class GreenOrganization : public Organization {
public:
	GreenOrganization() : Organization(ORGANIZATION_GREEN) {}

private:

};

class IntermediaryOrganization : public Organization {
public:
	IntermediaryOrganization() : Organization(ORGANIZATION_INTERMEDIARY) {}

private:

};

class StockOrganization : public Organization {
public:
	StockOrganization() : Organization(ORGANIZATION_STOCK) {}

private:

};

class CourtOrganization : public Organization {
public:
	CourtOrganization() : Organization(ORGANIZATION_COURT) {}

private:

};

class AdminOrganization : public Organization {
public:
	AdminOrganization() : Organization(ORGANIZATION_ADMIN) {}

private:

};

class EducationdeptOrganization : public Organization {
public:
	EducationdeptOrganization() : Organization(ORGANIZATION_EDUCATIONDEPT) {}

private:

};

class InfodeptOrganization : public Organization {
public:
	InfodeptOrganization() : Organization(ORGANIZATION_INFODEPT) {}

private:

};

class FinancedeptOrganization : public Organization {
public:
	FinancedeptOrganization() : Organization(ORGANIZATION_FINANCEDEPT) {}

private:

};

class TradedeptOrganization : public Organization {
public:
	TradedeptOrganization() : Organization(ORGANIZATION_TRADEDEPT) {}

private:

};

class PetitiondeptOrganization : public Organization {
public:
	PetitiondeptOrganization() : Organization(ORGANIZATION_PETITIONDEPT) {}

private:

};

class WeatherdeptOrganization : public Organization {
public:
	WeatherdeptOrganization() : Organization(ORGANIZATION_WEATHERDEPT) {}

private:

};

class TaxdeptOrganization : public Organization {
public:
	TaxdeptOrganization() : Organization(ORGANIZATION_TAXDEPT) {}

private:

};

class CivildeptOrganization : public Organization {
public:
	CivildeptOrganization() : Organization(ORGANIZATION_CIVILDEPT) {}

private:

};

class SciencedeptOrganization : public Organization {
public:
	SciencedeptOrganization() : Organization(ORGANIZATION_SCIENCEDEPT) {}

private:

};

class EngineerdeptOrganization : public Organization {
public:
	EngineerdeptOrganization() : Organization(ORGANIZATION_ENGINEERDEPT) {}

private:

};

class SocialdeptOrganization : public Organization {
public:
	SocialdeptOrganization() : Organization(ORGANIZATION_SOCIALDEPT) {}

private:

};

class CustomhouseOrganization : public Organization {
public:
	CustomhouseOrganization() : Organization(ORGANIZATION_CUSTOMHOUSE) {}

private:

};

class DogeOrganization : public Organization {
public:
	DogeOrganization() : Organization(ORGANIZATION_DOGE) {}

private:

};

class CommitteeOrganization : public Organization {
public:
	CommitteeOrganization() : Organization(ORGANIZATION_COMMITTEE) {}

private:

};

class LabOrganization : public Organization {
public:
	LabOrganization() : Organization(ORGANIZATION_LAB) {}

private:

};

class FactoryOrganization : public Organization {
public:
	FactoryOrganization() : Organization(ORGANIZATION_FACTORY) {}

private:

};

class WarehouseOrganization : public Organization {
public:
	WarehouseOrganization() : Organization(ORGANIZATION_WAREHOUSE) {}

private:

};

class RepairOrganization : public Organization {
public:
	RepairOrganization() : Organization(ORGANIZATION_REPAIR) {}

private:

};

class ResourceOrganization : public Organization {
public:
	ResourceOrganization() : Organization(ORGANIZATION_RESOURCE) {}

private:

};

class ParkOrganization : public Organization {
public:
	ParkOrganization() : Organization(ORGANIZATION_PARK) {}

private:

};

class PlazaOrganization : public Organization {
public:
	PlazaOrganization() : Organization(ORGANIZATION_PLAZA) {}

private:

};

class StatueOrganization : public Organization {
public:
	StatueOrganization() : Organization(ORGANIZATION_STATUE) {}

private:

};

class GymOrganization : public Organization {
public:
	GymOrganization() : Organization(ORGANIZATION_GYM) {}

private:

};

class StadiumOrganization : public Organization {
public:
	StadiumOrganization() : Organization(ORGANIZATION_STADIUM) {}

private:

};

class FootballOrganization : public Organization {
public:
	FootballOrganization() : Organization(ORGANIZATION_FOOTBALL) {}

private:

};

class BasketballOrganization : public Organization {
public:
	BasketballOrganization() : Organization(ORGANIZATION_BASKETBALL) {}

private:

};

class VolleyballOrganization : public Organization {
public:
	VolleyballOrganization() : Organization(ORGANIZATION_VOLLEYBALL) {}

private:

};

class TennisOrganization : public Organization {
public:
	TennisOrganization() : Organization(ORGANIZATION_TENNIS) {}

private:

};

class TabletennisOrganization : public Organization {
public:
	TabletennisOrganization() : Organization(ORGANIZATION_TABLETENNIS) {}

private:

};

class BadmintonOrganization : public Organization {
public:
	BadmintonOrganization() : Organization(ORGANIZATION_BADMINTON) {}

private:

};

class GolfOrganization : public Organization {
public:
	GolfOrganization() : Organization(ORGANIZATION_GOLF) {}

private:

};

class SkiOrganization : public Organization {
public:
	SkiOrganization() : Organization(ORGANIZATION_SKI) {}

private:

};

class SkateOrganization : public Organization {
public:
	SkateOrganization() : Organization(ORGANIZATION_SKATE) {}

private:

};

class SwimOrganization : public Organization {
public:
	SwimOrganization() : Organization(ORGANIZATION_SWIM) {}

private:

};

class ResortOrganization : public Organization {
public:
	ResortOrganization() : Organization(ORGANIZATION_RESORT) {}

private:

};

class RemainsOrganization : public Organization {
public:
	RemainsOrganization() : Organization(ORGANIZATION_REMAINS) {}

private:

};

class RocketOrganization : public Organization {
public:
	RocketOrganization() : Organization(ORGANIZATION_ROCKET) {}

private:

};

class PlaygroundOrganization : public Organization {
public:
	PlaygroundOrganization() : Organization(ORGANIZATION_PLAYGROUND) {}

private:

};

class PrisonOrganization : public Organization {
public:
	PrisonOrganization() : Organization(ORGANIZATION_PRISON) {}

private:

};

class GuardOrganization : public Organization {
public:
	GuardOrganization() : Organization(ORGANIZATION_GUARD) {}

private:

};

class CanteenOrganization : public Organization {
public:
	CanteenOrganization() : Organization(ORGANIZATION_CANTEEN) {}

private:

};

class DormitryOrganization : public Organization {
public:
	DormitryOrganization() : Organization(ORGANIZATION_DORMITRY) {}

private:

};

class DataOrganization : public Organization {
public:
	DataOrganization() : Organization(ORGANIZATION_DATA) {}

private:

};

class WaterOrganization : public Organization {
public:
	WaterOrganization() : Organization(ORGANIZATION_WATER) {}

private:

};

class SewageOrganization : public Organization {
public:
	SewageOrganization() : Organization(ORGANIZATION_SEWAGE) {}

private:

};

class PowerOrganization : public Organization {
public:
	PowerOrganization() : Organization(ORGANIZATION_POWER) {}

private:

};

class WindmillOrganization : public Organization {
public:
	WindmillOrganization() : Organization(ORGANIZATION_WINDMILL) {}

private:

};

class NuclearOrganization : public Organization {
public:
	NuclearOrganization() : Organization(ORGANIZATION_NUCLEAR) {}

private:

};

class RecycleOrganization : public Organization {
public:
	RecycleOrganization() : Organization(ORGANIZATION_RECYCLE) {}

private:

};

class TrashOrganization : public Organization {
public:
	TrashOrganization() : Organization(ORGANIZATION_TRASH) {}

private:

};

class IncinerationOrganization : public Organization {
public:
	IncinerationOrganization() : Organization(ORGANIZATION_INCINERATION) {}

private:

};

class BodyOrganization : public Organization {
public:
	BodyOrganization() : Organization(ORGANIZATION_BODY) {}

private:

};

class DentistOrganization : public Organization {
public:
	DentistOrganization() : Organization(ORGANIZATION_DENTIST) {}

private:

};

class MentalOrganization : public Organization {
public:
	MentalOrganization() : Organization(ORGANIZATION_MENTAL) {}

private:

};

class AffairOrganization : public Organization {
public:
	AffairOrganization() : Organization(ORGANIZATION_AFFAIR) {}

private:

};

class GoldOrganization : public Organization {
public:
	GoldOrganization() : Organization(ORGANIZATION_GOLD) {}

private:

};

class GroceryOrganization : public Organization {
public:
	GroceryOrganization() : Organization(ORGANIZATION_GROCERY) {}

private:

};

class ClothesOrganization : public Organization {
public:
	ClothesOrganization() : Organization(ORGANIZATION_CLOTHES) {}

private:

};

class CosmeticOrganization : public Organization {
public:
	CosmeticOrganization() : Organization(ORGANIZATION_COSMETIC) {}

private:

};

class HaircutOrganization : public Organization {
public:
	HaircutOrganization() : Organization(ORGANIZATION_HAIRCUT) {}

private:

};

class DrugOrganization : public Organization {
public:
	DrugOrganization() : Organization(ORGANIZATION_DRUG) {}

private:

};

class SmokewineteaOrganization : public Organization {
public:
	SmokewineteaOrganization() : Organization(ORGANIZATION_SMOKEWINETEA) {}

private:

};

class JewelryOrganization : public Organization {
public:
	JewelryOrganization() : Organization(ORGANIZATION_JEWELRY) {}

private:

};

class ExtracurricularOrganization : public Organization {
public:
	ExtracurricularOrganization() : Organization(ORGANIZATION_EXTRACURRICULAR) {}

private:

};

class ChesscardOrganization : public Organization {
public:
	ChesscardOrganization() : Organization(ORGANIZATION_CHESSCARD) {}

private:

};

class PetOrganization : public Organization {
public:
	PetOrganization() : Organization(ORGANIZATION_PET) {}

private:

};

class ElectronicOrganization : public Organization {
public:
	ElectronicOrganization() : Organization(ORGANIZATION_ELECTRONIC) {}

private:

};

class CopyOrganization : public Organization {
public:
	CopyOrganization() : Organization(ORGANIZATION_COPY) {}

private:

};

class StudioOrganization : public Organization {
public:
	StudioOrganization() : Organization(ORGANIZATION_STUDIO) {}

private:

};

class CarwashOrganization : public Organization {
public:
	CarwashOrganization() : Organization(ORGANIZATION_CARWASH) {}

private:

};

class BicycleOrganization : public Organization {
public:
	BicycleOrganization() : Organization(ORGANIZATION_BICYCLE) {}

private:

};

class HardwareOrganization : public Organization {
public:
	HardwareOrganization() : Organization(ORGANIZATION_HARDWARE) {}

private:

};

class BookOrganization : public Organization {
public:
	BookOrganization() : Organization(ORGANIZATION_BOOK) {}

private:

};

class BilliardOrganization : public Organization {
public:
	BilliardOrganization() : Organization(ORGANIZATION_BILLIARD) {}

private:

};

class NetOrganization : public Organization {
public:
	NetOrganization() : Organization(ORGANIZATION_NET) {}

private:

};

class KtvOrganization : public Organization {
public:
	KtvOrganization() : Organization(ORGANIZATION_KTV) {}

private:

};

class VendorOrganization : public Organization {
public:
	VendorOrganization() : Organization(ORGANIZATION_VENDOR) {}

private:

};

Organization* CreateOrganization(ORGANIZATION_TYPE type);