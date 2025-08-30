#pragma once

#include "building.h"
#include "room.h"

#include <vector>
#include <string>

class Building;

enum COMPONENT_TYPE {
	COMPONENT_NONE, // 无

	// 居住
	COMPONENT_COMMUNITY, // 社区

	// 商业
	COMPONENT_HOTEL, // 酒店
	COMPONENT_MALL, // 商场
	COMPONENT_SHOP, // 实体店
	COMPONENT_RESTAURANT, // 餐厅
	COMPONENT_CARRENT, // 租车行
	COMPONENT_THEATER, // 剧院
	COMPONENT_CINEMA, // 电影院
	COMPONENT_MUSEUM, // 博物馆
	COMPONENT_MASAGE, // 会所
	COMPONENT_PACKAGE, // 快递站

	// 办公
	COMPONENT_OFFICE, // 写字楼
	COMPONENT_FURNISH, // 装修公司
	COMPONENT_MOVING, // 搬家公司
	COMPONENT_OPERATOR, // 运营商
	COMPONENT_GAME, // 游戏公司
	COMPONENT_INTERNET, // 互联网公司
	COMPONENT_LEASE, // 外包公司
	COMPONENT_FINANCE, // 金融公司
	COMPONENT_LENDING, // 信贷公司
	COMPONENT_SALE, // 销售公司
	COMPONENT_MEDICAL, // 医药公司
	COMPONENT_RELATION, // 公关公司
	COMPONENT_ESHOP, // 电商
	COMPONENT_STAR, // 明星经纪公司
	COMPONENT_ENGINEER, // 工程设计公司
	COMPONENT_CONSTRUCT, // 建筑公司
	COMPONENT_ART, // 艺术设计公司
	COMPONENT_PUBLISHER, // 出版社
	COMPONENT_TRAVEL, // 旅行社
	COMPONENT_MEDIA, // 自媒体
	COMPONENT_LAWYER, // 律所
	COMPONENT_CREW, // 剧组
	COMPONENT_INSURANCE, // 保险公司
	COMPONENT_SECURITY, // 保安公司
	COMPONENT_CLEANING, // 保洁公司
	COMPONENT_GREEN, // 绿化公司
	COMPONENT_INTERMEDIARY, // 房屋中介
	COMPONENT_LAB, // 实验楼
	COMPONENT_SCIENCEDEPT, // 科学院
	COMPONENT_ENGINEERDEPT, // 工程院
	COMPONENT_SOCIALDEPT, // 社科院
	COMPONENT_COMMITTEE, // 学术委员会
	COMPONENT_GOVERNMENT, // 政府
	COMPONENT_EDUCATIONDEPT, // 教育部
	COMPONENT_INFODEPT, // 工信部
	COMPONENT_FINANCEDEPT, // 财政部
	COMPONENT_TRADEDEPT, // 商务部
	COMPONENT_PETITIONDEPT, // 信访局
	COMPONENT_WEATHERDEPT, // 气象局
	COMPONENT_TAXDEPT, // 税务局
	COMPONENT_CIVILDEPT, // 民政局
	COMPONENT_DOGE, // 反贪局

	// 工业
	COMPONENT_FACTORY, // 工厂
	COMPONENT_WAREHOUSE, // 仓库
	COMPONENT_RESOURCE, // 资源区

	// 绿化
	COMPONENT_PARK, // 公园
	COMPONENT_PLAZA, // 广场
	COMPONENT_STATUE, // 雕像
	COMPONENT_ZOO, // 动物园
	COMPONENT_BOTANIC, // 植物园
	COMPONENT_AQUARIUM, // 水族馆
	COMPONENT_AMUSEMENT, // 游乐场
	COMPONENT_GYM, // 健身房
	COMPONENT_STADIUM, // 运动场
	COMPONENT_RESORT, // 度假村
	COMPONENT_REMAINS, // 遗迹

	// 公共服务
	COMPONENT_KINDER, // 幼儿园
	COMPONENT_PRIMARY, // 小学
	COMPONENT_MIDDLE, // 中学
	COMPONENT_UNIVERSITY, // 大学
	COMPONENT_VOCATIONAL, // 职业学校
	COMPONENT_CLINIC, // 诊所
	COMPONENT_HOSPITAL, // 医院
	COMPONENT_INPATIENT, // 住院部
	COMPONENT_SANATORIUM, // 疗养院
	COMPONENT_POLICE, // 警察局
	COMPONENT_PRISON, // 监狱
	COMPONENT_FIRE, // 消防局
	COMPONENT_COURT, // 法院
	COMPONENT_TVSTATION, // 电视台
	COMPONENT_POST, // 邮局
	COMPONENT_BANK, // 银行
	COMPONENT_STOCK, // 证券交易所
	COMPONENT_LIBRARY, // 图书馆
	COMPONENT_ROADFIX, // 路政中心
	COMPONENT_GASOLINE, // 加油站
	COMPONENT_CREMATORIUM, // 火葬场
	COMPONENT_CEMETRY, // 墓地
	COMPONENT_WATER, // 抽水站
	COMPONENT_SEWAGE, // 污水处理厂
	COMPONENT_POWER, // 火电厂
	COMPONENT_WINDMILL, // 风电机
	COMPONENT_NUCLEAR, // 核电厂
	COMPONENT_BATTERY, // 蓄电池
	COMPONENT_DATA, // 数据中心
	COMPONENT_RECYCLE, // 废品回收站
	COMPONENT_TRASH, // 垃圾填埋场
	COMPONENT_INCINERATION, // 焚烧厂

	// 组件
	COMPONENT_PARKING, // 停车场
	COMPONENT_GUARD, // 保安亭
	COMPONENT_TOILET, // 公厕
	COMPONENT_CANTEEN, // 食堂
	COMPONENT_DORMITRY, // 宿舍
	COMPONENT_PLAYGROUND, // 操场
	COMPONENT_DEVICE, // 设备

	// 交通
	COMPONENT_STATION, // 交通站

	COMPONENT_END
};

static std::string componentText[COMPONENT_END] = {
	"无", // COMPONENT_NONE

	"社区", // COMPONENT_COMMUNITY

	"酒店", // COMPONENT_HOTEL
	"商场", // COMPONENT_MALL
	"实体店", // COMPONENT_SHOP
	"餐厅", // COMPONENT_RESTAURANT
	"租车行", // COMPONENT_CARRENT
	"剧院", // COMPONENT_THEATER
	"电影院", // COMPONENT_CINEMA
	"博物馆", // COMPONENT_MUSEUM
	"会所", // COMPONENT_MASAGE
	"快递站", // COMPONENT_PACKAGE

	"写字楼", // COMPONENT_OFFICE
	"装修公司", // COMPONENT_FURNISH
	"搬家公司", // COMPONENT_MOVING
	"运营商", // COMPONENT_OPERATOR
	"游戏公司", // COMPONENT_GAME
	"互联网公司", // COMPONENT_INTERNET
	"外包公司", // COMPONENT_LEASE
	"金融公司", // COMPONENT_FINANCE
	"信贷公司", // COMPONENT_LENDING
	"销售公司", // COMPONENT_SALE
	"医药公司", // COMPONENT_MEDICAL
	"公关公司", // COMPONENT_RELATION
	"电商", // COMPONENT_ESHOP
	"明星经纪公司", // COMPONENT_STAR
	"工程设计公司", // COMPONENT_ENGINEER
	"建筑公司", // COMPONENT_CONSTRUCT
	"艺术设计公司", // COMPONENT_ART
	"出版社", // COMPONENT_PUBLISHER
	"旅行社", // COMPONENT_TRAVEL
	"自媒体", // COMPONENT_MEDIA
	"律所", // COMPONENT_LAWYER
	"剧组", // COMPONENT_CREW
	"保险公司", // COMPONENT_INSURANCE
	"保安公司", // COMPONENT_SECURITY
	"保洁公司", // COMPONENT_CLEANING
	"绿化公司", // COMPONENT_GREEN
	"房屋中介", // COMPONENT_INTERMEDIARY
	"实验楼", // COMPONENT_LAB
	"政府", // COMPONENT_GOVERNMENT
	"教育部", // COMPONENT_EDUCATIONDEPT
	"工信部", // COMPONENT_INFODEPT
	"财政部", // COMPONENT_FINANCEDEPT
	"商务部", // COMPONENT_TRADEDEPT
	"信访局", // COMPONENT_PETITIONDEPT
	"气象局", // COMPONENT_WEATHERDEPT
	"税务局", // COMPONENT_TAXDEPT
	"民政局", // COMPONENT_CIVILDEPT
	"科学院", // COMPONENT_SCIENCEDEPT
	"工程院", // COMPONENT_ENGINEERDEPT
	"社科院", // COMPONENT_SOCIALDEPT
	"反贪局", // COMPONENT_DOGE
	"学术委员会", // COMPONENT_COMMITTEE

	"工厂", // COMPONENT_FACTORY
	"仓库", // COMPONENT_WAREHOUSE
	"资源区", // COMPONENT_RESOURCE

	"公园", // COMPONENT_PARK
	"广场", // COMPONENT_PLAZA
	"雕像", // COMPONENT_STATUE
	"动物园", // COMPONENT_ZOO
	"植物园", // COMPONENT_BOTANIC
	"水族馆", // COMPONENT_AQUARIUM
	"游乐设施", // COMPONENT_AMUSEMENT
	"健身房", // COMPONENT_GYM
	"运动场", // COMPONENT_STADIUM
	"度假村", // COMPONENT_RESORT
	"遗迹", // COMPONENT_REMAINS

	"幼儿园", // COMPONENT_KINDER
	"小学", // COMPONENT_PRIMARY
	"中学", // COMPONENT_MIDDLE
	"大学", // COMPONENT_UNIVERSITY
	"职业学校", // COMPONENT_VOCATIONAL
	"诊所", // COMPONENT_CLINIC
	"医院", // COMPONENT_HOSPITAL
	"住院部", // COMPONENT_INPATIENT
	"疗养院", // COMPONENT_SANATORIUM
	"警察局", // COMPONENT_POLICE
	"监狱", // COMPONENT_PRISON
	"消防局", // COMPONENT_FIRE
	"法院", // COMPONENT_COURT
	"电视台", // COMPONENT_TVSTATION
	"邮局", // COMPONENT_POST
	"银行", // COMPONENT_BANK
	"证券交易所", // COMPONENT_STOCK
	"图书馆", // COMPONENT_LIBRARY
	"路政中心", // COMPONENT_ROADFIX
	"加油站", // COMPONENT_GASOLINE
	"火葬场", // COMPONENT_CREMATORIUM
	"墓地", // COMPONENT_CEMETRY
	"抽水站", // COMPONENT_WATER
	"污水处理厂", // COMPONENT_SEWAGE
	"火电厂", // COMPONENT_POWER
	"风电机", // COMPONENT_WINDMILL
	"核电厂", // COMPONENT_NUCLEAR
	"蓄电池", // COMPONENT_BATTERY
	"数据中心", // COMPONENT_DATA
	"废品回收站", // COMPONENT_RECYCLE
	"垃圾填埋场", // COMPONENT_TRASH
	"焚烧厂", // COMPONENT_INCINERATION

	"停车场", // COMPONENT_PARKING
	"保安亭", // COMPONENT_GUARD
	"公厕", // COMPONENT_TOILET
	"食堂", // COMPONENT_CANTEEN
	"宿舍", // COMPONENT_DORMITRY
	"操场", // COMPONENT_PLAYGROUND
	"设备", // COMPONENT_DEVICE

	"交通站" // COMPONENT_STATION
};

class Component {
public:
	Component(COMPONENT_TYPE type) : type(type) {}
	~Component() {
		rooms.clear();
	}

	// 获取/设置类型
	COMPONENT_TYPE GetType() const;
	void SetType(COMPONENT_TYPE type);

	// 获取/添加房间
	std::vector<std::shared_ptr<Room>>& GetRooms() { return rooms; }
	void AddRoom(std::shared_ptr<Room> room) { rooms.push_back(room); }
	void UpdateRoom(std::vector<std::shared_ptr<Room>> rooms) { this->rooms = rooms; }

	// 获取组织名称
	std::string GetName() const { return name; }

private:
	COMPONENT_TYPE type;
	int id;
	std::string name;

	std::vector<std::shared_ptr<Room>> rooms;
};

class CommunityComponent : public Component {
public:
	CommunityComponent() : Component(COMPONENT_COMMUNITY) {}

private:

};

class HotelComponent : public Component {
public:
	HotelComponent() : Component(COMPONENT_HOTEL) {}

private:

};

class MallComponent : public Component {
public:
	MallComponent() : Component(COMPONENT_MALL) {}

private:

};

class ShopComponent : public Component {
public:
	ShopComponent() : Component(COMPONENT_SHOP) {}

private:

};

class RestaurantComponent : public Component {
public:
	RestaurantComponent() : Component(COMPONENT_RESTAURANT) {}

private:

};

class CarrentComponent : public Component {
public:
	CarrentComponent() : Component(COMPONENT_CARRENT) {}

private:

};

class TheaterComponent : public Component {
public:
	TheaterComponent() : Component(COMPONENT_THEATER) {}

private:

};

class CinemaComponent : public Component {
public:
	CinemaComponent() : Component(COMPONENT_CINEMA) {}

private:

};

class MuseumComponent : public Component {
public:
	MuseumComponent() : Component(COMPONENT_MUSEUM) {}

private:

};

class MasageComponent : public Component {
public:
	MasageComponent() : Component(COMPONENT_MASAGE) {}

private:

};

class PackageComponent : public Component {
public:
	PackageComponent() : Component(COMPONENT_PACKAGE) {}

private:

};

class OfficeComponent : public Component {
public:
	OfficeComponent() : Component(COMPONENT_OFFICE) {}

private:

};

class FurnishComponent : public Component {
public:
	FurnishComponent() : Component(COMPONENT_FURNISH) {}

private:

};

class MovingComponent : public Component {
public:
	MovingComponent() : Component(COMPONENT_MOVING) {}

private:

};

class OperatorComponent : public Component {
public:
	OperatorComponent() : Component(COMPONENT_OPERATOR) {}

private:

};

class GameComponent : public Component {
public:
	GameComponent() : Component(COMPONENT_GAME) {}

private:

};

class InternetComponent : public Component {
public:
	InternetComponent() : Component(COMPONENT_INTERNET) {}

private:

};

class LeaseComponent : public Component {
public:
	LeaseComponent() : Component(COMPONENT_LEASE) {}

private:

};

class FinanceComponent : public Component {
public:
	FinanceComponent() : Component(COMPONENT_FINANCE) {}

private:

};

class LendingComponent : public Component {
public:
	LendingComponent() : Component(COMPONENT_LENDING) {}

private:

};

class SaleComponent : public Component {
public:
	SaleComponent() : Component(COMPONENT_SALE) {}

private:

};

class MedicalComponent : public Component {
public:
	MedicalComponent() : Component(COMPONENT_MEDICAL) {}

private:

};

class RelationComponent : public Component {
public:
	RelationComponent() : Component(COMPONENT_RELATION) {}

private:

};

class EshopComponent : public Component {
public:
	EshopComponent() : Component(COMPONENT_ESHOP) {}

private:

};

class StarComponent : public Component {
public:
	StarComponent() : Component(COMPONENT_STAR) {}

private:

};

class EngineerComponent : public Component {
public:
	EngineerComponent() : Component(COMPONENT_ENGINEER) {}

private:

};

class ConstructComponent : public Component {
public:
	ConstructComponent() : Component(COMPONENT_CONSTRUCT) {}

private:

};

class ArtComponent : public Component {
public:
	ArtComponent() : Component(COMPONENT_ART) {}

private:

};

class PublisherComponent : public Component {
public:
	PublisherComponent() : Component(COMPONENT_PUBLISHER) {}

private:

};

class TravelComponent : public Component {
public:
	TravelComponent() : Component(COMPONENT_TRAVEL) {}

private:

};

class MediaComponent : public Component {
public:
	MediaComponent() : Component(COMPONENT_MEDIA) {}

private:

};

class LawyerComponent : public Component {
public:
	LawyerComponent() : Component(COMPONENT_LAWYER) {}

private:

};

class CrewComponent : public Component {
public:
	CrewComponent() : Component(COMPONENT_CREW) {}

private:

};

class InsuranceComponent : public Component {
public:
	InsuranceComponent() : Component(COMPONENT_INSURANCE) {}

private:

};

class SecurityComponent : public Component {
public:
	SecurityComponent() : Component(COMPONENT_SECURITY) {}

private:

};

class CleaningComponent : public Component {
public:
	CleaningComponent() : Component(COMPONENT_CLEANING) {}

private:

};

class GreenComponent : public Component {
public:
	GreenComponent() : Component(COMPONENT_GREEN) {}

private:

};

class IntermediaryComponent : public Component {
public:
	IntermediaryComponent() : Component(COMPONENT_INTERMEDIARY) {}

private:

};

class LabComponent : public Component {
public:
	LabComponent() : Component(COMPONENT_LAB) {}

private:

};

class ScienceDeptComponent : public Component {
public:
	ScienceDeptComponent() : Component(COMPONENT_SCIENCEDEPT) {}

private:

};

class EngineerDeptComponent : public Component {
public:
	EngineerDeptComponent() : Component(COMPONENT_ENGINEERDEPT) {}

private:

};

class SocialDeptComponent : public Component {
public:
	SocialDeptComponent() : Component(COMPONENT_SOCIALDEPT) {}

private:

};

class CommitteeComponent : public Component {
public:
	CommitteeComponent() : Component(COMPONENT_COMMITTEE) {}

private:

};

class GovernmentComponent : public Component {
public:
	GovernmentComponent() : Component(COMPONENT_GOVERNMENT) {}

private:

};

class EducationDeptComponent : public Component {
public:
	EducationDeptComponent() : Component(COMPONENT_EDUCATIONDEPT) {}

private:

};

class InfoDeptComponent : public Component {
public:
	InfoDeptComponent() : Component(COMPONENT_INFODEPT) {}

private:

};

class FinanceDeptComponent : public Component {
public:
	FinanceDeptComponent() : Component(COMPONENT_FINANCEDEPT) {}

private:

};

class TradeDeptComponent : public Component {
public:
	TradeDeptComponent() : Component(COMPONENT_TRADEDEPT) {}

private:

};

class PetitionDeptComponent : public Component {
public:
	PetitionDeptComponent() : Component(COMPONENT_PETITIONDEPT) {}

private:

};

class WeatherDeptComponent : public Component {
public:
	WeatherDeptComponent() : Component(COMPONENT_WEATHERDEPT) {}

private:

};

class TaxDeptComponent : public Component {
public:
	TaxDeptComponent() : Component(COMPONENT_TAXDEPT) {}

private:

};

class CivilDeptComponent : public Component {
public:
	CivilDeptComponent() : Component(COMPONENT_CIVILDEPT) {}

private:

};

class DogeComponent : public Component {
public:
	DogeComponent() : Component(COMPONENT_DOGE) {}

private:

};

class ScienceDeptComponent : public Component {
public:
	ScienceDeptComponent() : Component(COMPONENT_SCIENCEDEPT) {}

private:

};

class EngineerDeptComponent : public Component {
public:
	EngineerDeptComponent() : Component(COMPONENT_ENGINEERDEPT) {}

private:

};

class SocialDeptComponent : public Component {
public:
	SocialDeptComponent() : Component(COMPONENT_SOCIALDEPT) {}

private:

};

class DogeComponent : public Component {
public:
	DogeComponent() : Component(COMPONENT_DOGE) {}

private:

};

class CommitteeComponent : public Component {
public:
	CommitteeComponent() : Component(COMPONENT_COMMITTEE) {}

private:

};

class FactoryComponent : public Component {
public:
	FactoryComponent() : Component(COMPONENT_FACTORY) {}

private:

};

class WarehouseComponent : public Component {
public:
	WarehouseComponent() : Component(COMPONENT_WAREHOUSE) {}

private:

};

class ResourceComponent : public Component {
public:
	ResourceComponent() : Component(COMPONENT_RESOURCE) {}

private:

};

class ParkComponent : public Component {
public:
	ParkComponent() : Component(COMPONENT_PARK) {}

private:

};

class PlazaComponent : public Component {
public:
	PlazaComponent() : Component(COMPONENT_PLAZA) {}

private:

};

class StatueComponent : public Component {
public:
	StatueComponent() : Component(COMPONENT_STATUE) {}

private:

};

class ZooComponent : public Component {
public:
	ZooComponent() : Component(COMPONENT_ZOO) {}

private:

};

class BotanicComponent : public Component {
public:
	BotanicComponent() : Component(COMPONENT_BOTANIC) {}

private:

};

class AquariumComponent : public Component {
public:
	AquariumComponent() : Component(COMPONENT_AQUARIUM) {}

private:

};

class AmusementComponent : public Component {
public:
	AmusementComponent() : Component(COMPONENT_AMUSEMENT) {}

private:

};

class GymComponent : public Component {
public:
	GymComponent() : Component(COMPONENT_GYM) {}

private:

};

class StadiumComponent : public Component {
public:
	StadiumComponent() : Component(COMPONENT_STADIUM) {}

private:

};

class ResortComponent : public Component {
public:
	ResortComponent() : Component(COMPONENT_RESORT) {}

private:

};

class RemainsComponent : public Component {
public:
	RemainsComponent() : Component(COMPONENT_REMAINS) {}

private:

};

class KinderComponent : public Component {
public:
	KinderComponent() : Component(COMPONENT_KINDER) {}

private:

};

class PrimaryComponent : public Component {
public:
	PrimaryComponent() : Component(COMPONENT_PRIMARY) {}

private:

};

class MiddleComponent : public Component {
public:
	MiddleComponent() : Component(COMPONENT_MIDDLE) {}

private:

};

class UniversityComponent : public Component {
public:
	UniversityComponent() : Component(COMPONENT_UNIVERSITY) {}

private:

};

class VocationalComponent : public Component {
public:
	VocationalComponent() : Component(COMPONENT_VOCATIONAL) {}

private:

};

class ClinicComponent : public Component {
public:
	ClinicComponent() : Component(COMPONENT_CLINIC) {}

private:

};

class HospitalComponent : public Component {
public:
	HospitalComponent() : Component(COMPONENT_HOSPITAL) {}

private:

};

class InpatientComponent : public Component {
public:
	InpatientComponent() : Component(COMPONENT_INPATIENT) {}

private:

};

class SanatoriumComponent : public Component {
public:
	SanatoriumComponent() : Component(COMPONENT_SANATORIUM) {}

private:

};

class PoliceComponent : public Component {
public:
	PoliceComponent() : Component(COMPONENT_POLICE) {}

private:

};

class PrisonComponent : public Component {
public:
	PrisonComponent() : Component(COMPONENT_PRISON) {}

private:

};

class FireComponent : public Component {
public:
	FireComponent() : Component(COMPONENT_FIRE) {}

private:

};

class CourtComponent : public Component {
public:
	CourtComponent() : Component(COMPONENT_COURT) {}

private:

};

class TVStationComponent : public Component {
public:
	TVStationComponent() : Component(COMPONENT_TVSTATION) {}

private:

};

class PostComponent : public Component {
public:
	PostComponent() : Component(COMPONENT_POST) {}

private:

};

class BankComponent : public Component {
public:
	BankComponent() : Component(COMPONENT_BANK) {}

private:

};

class StockComponent : public Component {
public:
	StockComponent() : Component(COMPONENT_STOCK) {}

private:

};

class LibraryComponent : public Component {
public:
	LibraryComponent() : Component(COMPONENT_LIBRARY) {}

private:

};

class RoadFixComponent : public Component {
public:
	RoadFixComponent() : Component(COMPONENT_ROADFIX) {}

private:

};

class GasolineComponent : public Component {
public:
	GasolineComponent() : Component(COMPONENT_GASOLINE) {}

private:

};

class CrematoriumComponent : public Component {
public:
	CrematoriumComponent() : Component(COMPONENT_CREMATORIUM) {}

private:

};

class CemeteryComponent : public Component {
public:
	CemeteryComponent() : Component(COMPONENT_CEMETRY) {}

private:

};

class WaterComponent : public Component {
public:
	WaterComponent() : Component(COMPONENT_WATER) {}

private:

};

class SewageComponent : public Component {
public:
	SewageComponent() : Component(COMPONENT_SEWAGE) {}

private:

};

class PowerComponent : public Component {
public:
	PowerComponent() : Component(COMPONENT_POWER) {}

private:

};

class WindmillComponent : public Component {
public:
	WindmillComponent() : Component(COMPONENT_WINDMILL) {}

private:

};

class NuclearComponent : public Component {
public:
	NuclearComponent() : Component(COMPONENT_NUCLEAR) {}

private:

};

class BatteryComponent : public Component {
public:
	BatteryComponent() : Component(COMPONENT_BATTERY) {}

private:

};

class DataComponent : public Component {
public:
	DataComponent() : Component(COMPONENT_DATA) {}

private:

};

class RecycleComponent : public Component {
public:
	RecycleComponent() : Component(COMPONENT_RECYCLE) {}

private:

};

class TrashComponent : public Component {
public:
	TrashComponent() : Component(COMPONENT_TRASH) {}

private:

};

class IncinerationComponent : public Component {
public:
	IncinerationComponent() : Component(COMPONENT_INCINERATION) {}

private:

};

class DeviceComponent : public Component {
public:
	DeviceComponent() : Component(COMPONENT_DEVICE) {}

private:

};

class ParkingComponent : public Component {
public:
	ParkingComponent() : Component(COMPONENT_PARKING) {}

private:

};

class GuardComponent : public Component {
public:
	GuardComponent() : Component(COMPONENT_GUARD) {}

private:

};

class ToiletComponent : public Component {
public:
	ToiletComponent() : Component(COMPONENT_TOILET) {}

private:

};

class CanteenComponent : public Component {
public:
	CanteenComponent() : Component(COMPONENT_CANTEEN) {}

private:

};

class DormitoryComponent : public Component {
public:
	DormitoryComponent() : Component(COMPONENT_DORMITRY) {}

private:

};

class PlaygroundComponent : public Component {
public:
	PlaygroundComponent() : Component(COMPONENT_PLAYGROUND) {}

private:

};

class StationComponent : public Component {
public:
	StationComponent() : Component(COMPONENT_STATION) {}

private:

};

std::shared_ptr<Component> CreateComponent(COMPONENT_TYPE type);