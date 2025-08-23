#pragma once

#include "building.h"
#include "room.h"

#include <vector>
#include <string>

class Building;

enum ORGANIZATION_TYPE {
	ORGANIZATION_NONE, // 无

	// 居住
	ORGANIZATION_COMMUNITY, // 社区

	// 商业
	ORGANIZATION_HOTEL, // 酒店
	ORGANIZATION_MALL, // 商场
	ORGANIZATION_SHOP, // 实体店
	ORGANIZATION_RESTAURANT, // 餐厅
	ORGANIZATION_CARRENT, // 租车行
	ORGANIZATION_THEATER, // 剧院
	ORGANIZATION_CINEMA, // 电影院
	ORGANIZATION_MUSEUM, // 博物馆
	ORGANIZATION_MASAGE, // 会所
	ORGANIZATION_PACKAGE, // 快递站

	// 办公
	ORGANIZATION_OFFICE, // 写字楼
	ORGANIZATION_FURNISH, // 装修公司
	ORGANIZATION_MOVING, // 搬家公司
	ORGANIZATION_OPERATOR, // 运营商
	ORGANIZATION_GAME, // 游戏公司
	ORGANIZATION_LEASE, // 外包公司
	ORGANIZATION_FINANCE, // 金融公司
	ORGANIZATION_LENDING, // 信贷公司
	ORGANIZATION_SALE, // 销售公司
	ORGANIZATION_MEDICAL, // 医药公司
	ORGANIZATION_RELATION, // 公关公司
	ORGANIZATION_ESHOP, // 电商
	ORGANIZATION_STAR, // 明星经纪公司
	ORGANIZATION_ENGINEER, // 工程设计公司
	ORGANIZATION_CONSTRUCT, // 建筑公司
	ORGANIZATION_ART, // 艺术设计公司
	ORGANIZATION_PUBLISHER, // 出版社
	ORGANIZATION_TRAVEL, // 旅行社
	ORGANIZATION_MEDIA, // 自媒体
	ORGANIZATION_LAWYER, // 律所
	ORGANIZATION_CREW, // 剧组
	ORGANIZATION_INSURANCE, // 保险公司
	ORGANIZATION_SECURITY, // 保安公司
	ORGANIZATION_CLEANING, // 保洁公司
	ORGANIZATION_GREEN, // 绿化公司
	ORGANIZATION_INTERMEDIARY, // 房屋中介
	ORGANIZATION_LAB, // 实验楼
	ORGANIZATION_GOVERNMENT, // 政府
	ORGANIZATION_EDUCATIONDEPT, // 教育部
	ORGANIZATION_INFODEPT, // 工信部
	ORGANIZATION_FINANCEDEPT, // 财政部
	ORGANIZATION_TRADEDEPT, // 商务部
	ORGANIZATION_PETITIONDEPT, // 信访局
	ORGANIZATION_WEATHERDEPT, // 气象局
	ORGANIZATION_TAXDEPT, // 税务局
	ORGANIZATION_CIVILDEPT, // 民政局
	ORGANIZATION_SCIENCEDEPT, // 科学院
	ORGANIZATION_ENGINEERDEPT, // 工程院
	ORGANIZATION_SOCIALDEPT, // 社科院
	ORGANIZATION_DOGE, // 反贪局
	ORGANIZATION_COMMITTEE, // 学术委员会

	// 工业
	ORGANIZATION_FACTORY, // 工厂
	ORGANIZATION_RESOURCE, // 资源区

	// 绿化
	ORGANIZATION_PARK, // 公园
	ORGANIZATION_PLAZA, // 广场
	ORGANIZATION_STATUE, // 雕像
	ORGANIZATION_ZOO, // 动物园
	ORGANIZATION_BOTANIC, // 植物园
	ORGANIZATION_AQUARIUM, // 水族馆
	ORGANIZATION_AMUSEMENT, // 游乐场
	ORGANIZATION_GYM, // 健身房
	ORGANIZATION_STADIUM, // 运动场
	ORGANIZATION_RESORT, // 度假村
	ORGANIZATION_REMAINS, // 遗迹

	// 公共服务
	ORGANIZATION_KINDER, // 幼儿园
	ORGANIZATION_PRIMARY, // 小学
	ORGANIZATION_MIDDLE, // 中学
	ORGANIZATION_UNIVERSITY, // 大学
	ORGANIZATION_VOCATIONAL, // 职业学校
	ORGANIZATION_CLINIC, // 诊所
	ORGANIZATION_HOSPITAL, // 医院
	ORGANIZATION_INPATIENT, // 住院部
	ORGANIZATION_SANATORIUM, // 疗养院
	ORGANIZATION_POLICE, // 警察局
	ORGANIZATION_PRISON, // 监狱
	ORGANIZATION_FIRE, // 消防局
	ORGANIZATION_COURT, // 法院
	ORGANIZATION_TVSTATION, // 电视台
	ORGANIZATION_POST, // 邮局
	ORGANIZATION_BANK, // 银行
	ORGANIZATION_STOCK, // 证券交易所
	ORGANIZATION_LIBRARY, // 图书馆
	ORGANIZATION_ROADFIX, // 路政中心
	ORGANIZATION_GASOLINE, // 加油站
	ORGANIZATION_CREMATORIUM, // 火葬场
	ORGANIZATION_CEMETRY, // 墓地
	ORGANIZATION_WATER, // 抽水站
	ORGANIZATION_SEWAGE, // 污水处理厂
	ORGANIZATION_POWER, // 火电厂
	ORGANIZATION_WINDMILL, // 风电机
	ORGANIZATION_NUCLEAR, // 核电厂
	ORGANIZATION_BATTERY, // 蓄电池
	ORGANIZATION_DATA, // 数据中心
	ORGANIZATION_RECYCLE, // 废品回收站
	ORGANIZATION_TRASH, // 垃圾填埋场
	ORGANIZATION_INCINERATION, // 焚烧厂

	// 组件
	ORGANIZATION_PARKING, // 停车场
	ORGANIZATION_GUARD, // 保安亭
	ORGANIZATION_TOILET, // 公厕
	ORGANIZATION_CANTEEN, // 食堂
	ORGANIZATION_DORMITRY, // 宿舍
	ORGANIZATION_PLAYGROUND, // 操场
	ORGANIZATION_DEVICE, // 设备

	// 交通
	ORGANIZATION_STATION, // 交通站

	ORGANIZATION_END
};

static std::string organizationText[ORGANIZATION_END] = {
	"无", // ORGANIZATION_NONE

	"社区", // ORGANIZATION_COMMUNITY

	"酒店", // ORGANIZATION_HOTEL
	"商场", // ORGANIZATION_MALL
	"实体店", // ORGANIZATION_SHOP
	"餐厅", // ORGANIZATION_RESTAURANT
	"租车行", // ORGANIZATION_CARRENT
	"剧院", // ORGANIZATION_THEATER
	"电影院", // ORGANIZATION_CINEMA
	"博物馆", // ORGANIZATION_MUSEUM
	"会所", // ORGANIZATION_MASAGE
	"快递站", // ORGANIZATION_PACKAGE

	"写字楼", // ORGANIZATION_OFFICE
	"装修公司", // ORGANIZATION_FURNISH
	"搬家公司", // ORGANIZATION_MOVING
	"运营商", // ORGANIZATION_OPERATOR
	"游戏公司", // ORGANIZATION_GAME
	"外包公司", // ORGANIZATION_LEASE
	"金融公司", // ORGANIZATION_FINANCE
	"信贷公司", // ORGANIZATION_LENDING
	"销售公司", // ORGANIZATION_SALE
	"医药公司", // ORGANIZATION_MEDICAL
	"公关公司", // ORGANIZATION_RELATION
	"电商", // ORGANIZATION_ESHOP
	"明星经纪公司", // ORGANIZATION_STAR
	"工程设计公司", // ORGANIZATION_ENGINEER
	"建筑公司", // ORGANIZATION_CONSTRUCT
	"艺术设计公司", // ORGANIZATION_ART
	"出版社", // ORGANIZATION_PUBLISHER
	"旅行社", // ORGANIZATION_TRAVEL
	"自媒体", // ORGANIZATION_MEDIA
	"律所", // ORGANIZATION_LAWYER
	"剧组", // ORGANIZATION_CREW
	"保险公司", // ORGANIZATION_INSURANCE
	"保安公司", // ORGANIZATION_SECURITY
	"保洁公司", // ORGANIZATION_CLEANING
	"绿化公司", // ORGANIZATION_GREEN
	"房屋中介", // ORGANIZATION_INTERMEDIARY
	"实验楼", // ORGANIZATION_LAB
	"政府", // ORGANIZATION_GOVERNMENT
	"教育部", // ORGANIZATION_EDUCATIONDEPT
	"工信部", // ORGANIZATION_INFODEPT
	"财政部", // ORGANIZATION_FINANCEDEPT
	"商务部", // ORGANIZATION_TRADEDEPT
	"信访局", // ORGANIZATION_PETITIONDEPT
	"气象局", // ORGANIZATION_WEATHERDEPT
	"税务局", // ORGANIZATION_TAXDEPT
	"民政局", // ORGANIZATION_CIVILDEPT
	"科学院", // ORGANIZATION_SCIENCEDEPT
	"工程院", // ORGANIZATION_ENGINEERDEPT
	"社科院", // ORGANIZATION_SOCIALDEPT
	"反贪局", // ORGANIZATION_DOGE
	"学术委员会", // ORGANIZATION_COMMITTEE

	"工厂", // ORGANIZATION_FACTORY
	"资源区", // ORGANIZATION_RESOURCE

	"公园", // ORGANIZATION_PARK
	"广场", // ORGANIZATION_PLAZA
	"雕像", // ORGANIZATION_STATUE
	"动物园", // ORGANIZATION_ZOO
	"植物园", // ORGANIZATION_BOTANIC
	"水族馆", // ORGANIZATION_AQUARIUM
	"游乐设施", // ORGANIZATION_AMUSEMENT
	"健身房", // ORGANIZATION_GYM
	"运动场", // ORGANIZATION_STADIUM
	"度假村", // ORGANIZATION_RESORT
	"遗迹", // ORGANIZATION_REMAINS

	"幼儿园", // ORGANIZATION_KINDER
	"小学", // ORGANIZATION_PRIMARY
	"中学", // ORGANIZATION_MIDDLE
	"大学", // ORGANIZATION_UNIVERSITY
	"职业学校", // ORGANIZATION_VOCATIONAL
	"诊所", // ORGANIZATION_CLINIC
	"医院", // ORGANIZATION_HOSPITAL
	"住院部", // ORGANIZATION_INPATIENT
	"疗养院", // ORGANIZATION_SANATORIUM
	"警察局", // ORGANIZATION_POLICE
	"监狱", // ORGANIZATION_PRISON
	"消防局", // ORGANIZATION_FIRE
	"法院", // ORGANIZATION_COURT
	"电视台", // ORGANIZATION_TVSTATION
	"邮局", // ORGANIZATION_POST
	"银行", // ORGANIZATION_BANK
	"证券交易所", // ORGANIZATION_STOCK
	"图书馆", // ORGANIZATION_LIBRARY
	"路政中心", // ORGANIZATION_ROADFIX
	"加油站", // ORGANIZATION_GASOLINE
	"火葬场", // ORGANIZATION_CREMATORIUM
	"墓地", // ORGANIZATION_CEMETRY
	"抽水站", // ORGANIZATION_WATER
	"污水处理厂", // ORGANIZATION_SEWAGE
	"火电厂", // ORGANIZATION_POWER
	"风电机", // ORGANIZATION_WINDMILL
	"核电厂", // ORGANIZATION_NUCLEAR
	"蓄电池", // ORGANIZATION_BATTERY
	"数据中心", // ORGANIZATION_DATA
	"废品回收站", // ORGANIZATION_RECYCLE
	"垃圾填埋场", // ORGANIZATION_TRASH
	"焚烧厂", // ORGANIZATION_INCINERATION

	"停车场", // ORGANIZATION_PARKING
	"保安亭", // ORGANIZATION_GUARD
	"公厕", // ORGANIZATION_TOILET
	"食堂", // ORGANIZATION_CANTEEN
	"宿舍", // ORGANIZATION_DORMITRY
	"操场", // ORGANIZATION_PLAYGROUND
	"设备", // ORGANIZATION_DEVICE

	"交通站" // ORGANIZATION_STATION
};

class Organization {
public:
	Organization(ORGANIZATION_TYPE type) : type(type) {}
	~Organization() {
		rooms.clear();
	}

	// 获取/设置类型
	ORGANIZATION_TYPE GetType() const;
	void SetType(ORGANIZATION_TYPE type);

	// 获取/添加房间
	std::vector<std::shared_ptr<Room>>& GetRooms() { return rooms; }
	void AddRoom(std::shared_ptr<Room> room) { rooms.push_back(room); }
	void UpdateRoom(std::vector<std::shared_ptr<Room>> rooms) { this->rooms = rooms; }

	// 获取组织名称
	std::string GetName() const { return name; }

private:
	ORGANIZATION_TYPE type;
	int id;
	std::string name;

	std::vector<std::shared_ptr<Room>> rooms;
};

class CommunityOrganization : public Organization {
public:
	CommunityOrganization() : Organization(ORGANIZATION_COMMUNITY) {}

private:

};

class HotelOrganization : public Organization {
public:
	HotelOrganization() : Organization(ORGANIZATION_HOTEL) {}

private:

};

class MallOrganization : public Organization {
public:
	MallOrganization() : Organization(ORGANIZATION_MALL) {}

private:

};

class ShopOrganization : public Organization {
public:
	ShopOrganization() : Organization(ORGANIZATION_SHOP) {}

private:

};

class RestaurantOrganization : public Organization {
public:
	RestaurantOrganization() : Organization(ORGANIZATION_RESTAURANT) {}

private:

};

class CarRentOrganization : public Organization {
public:
	CarRentOrganization() : Organization(ORGANIZATION_CARRENT) {}

private:

};

class TheaterOrganization : public Organization {
public:
	TheaterOrganization() : Organization(ORGANIZATION_THEATER) {}

private:

};

class CinemaOrganization : public Organization {
public:
	CinemaOrganization() : Organization(ORGANIZATION_CINEMA) {}

private:

};

class MuseumOrganization : public Organization {
public:
	MuseumOrganization() : Organization(ORGANIZATION_MUSEUM) {}

private:

};

class MasageOrganization : public Organization {
public:
	MasageOrganization() : Organization(ORGANIZATION_MASAGE) {}

private:

};

class PackageOrganization : public Organization {
public:
	PackageOrganization() : Organization(ORGANIZATION_PACKAGE) {}

private:

};

class OfficeOrganization : public Organization {
public:
	OfficeOrganization() : Organization(ORGANIZATION_OFFICE) {}

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

class LabOrganization : public Organization {
public:
	LabOrganization() : Organization(ORGANIZATION_LAB) {}

private:

};

class GovernmentOrganization : public Organization {
public:
	GovernmentOrganization() : Organization(ORGANIZATION_GOVERNMENT) {}

private:

};

class EducationDeptOrganization : public Organization {
public:
	EducationDeptOrganization() : Organization(ORGANIZATION_EDUCATIONDEPT) {}

private:

};

class InfoDeptOrganization : public Organization {
public:
	InfoDeptOrganization() : Organization(ORGANIZATION_INFODEPT) {}

private:

};

class FinanceDeptOrganization : public Organization {
public:
	FinanceDeptOrganization() : Organization(ORGANIZATION_FINANCEDEPT) {}

private:

};

class TradeDeptOrganization : public Organization {
public:
	TradeDeptOrganization() : Organization(ORGANIZATION_TRADEDEPT) {}

private:

};

class PetitionDeptOrganization : public Organization {
public:
	PetitionDeptOrganization() : Organization(ORGANIZATION_PETITIONDEPT) {}

private:

};

class WeatherDeptOrganization : public Organization {
public:
	WeatherDeptOrganization() : Organization(ORGANIZATION_WEATHERDEPT) {}

private:

};

class TaxDeptOrganization : public Organization {
public:
	TaxDeptOrganization() : Organization(ORGANIZATION_TAXDEPT) {}

private:

};

class CivilDeptOrganization : public Organization {
public:
	CivilDeptOrganization() : Organization(ORGANIZATION_CIVILDEPT) {}

private:

};

class ScienceDeptOrganization : public Organization {
public:
	ScienceDeptOrganization() : Organization(ORGANIZATION_SCIENCEDEPT) {}

private:

};

class EngineerDeptOrganization : public Organization {
public:
	EngineerDeptOrganization() : Organization(ORGANIZATION_ENGINEERDEPT) {}

private:

};

class SocialDeptOrganization : public Organization {
public:
	SocialDeptOrganization() : Organization(ORGANIZATION_SOCIALDEPT) {}

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

class FactoryOrganization : public Organization {
public:
	FactoryOrganization() : Organization(ORGANIZATION_FACTORY) {}

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

class AmusementOrganization : public Organization {
public:
	AmusementOrganization() : Organization(ORGANIZATION_AMUSEMENT) {}

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

class PrisonOrganization : public Organization {
public:
	PrisonOrganization() : Organization(ORGANIZATION_PRISON) {}

private:

};

class FireOrganization : public Organization {
public:
	FireOrganization() : Organization(ORGANIZATION_FIRE) {}

private:

};

class CourtOrganization : public Organization {
public:
	CourtOrganization() : Organization(ORGANIZATION_COURT) {}

private:

};

class TVStationOrganization : public Organization {
public:
	TVStationOrganization() : Organization(ORGANIZATION_TVSTATION) {}

private:

};

class PostOrganization : public Organization {
public:
	PostOrganization() : Organization(ORGANIZATION_POST) {}

private:

};

class BankOrganization : public Organization {
public:
	BankOrganization() : Organization(ORGANIZATION_BANK) {}

private:

};

class StockOrganization : public Organization {
public:
	StockOrganization() : Organization(ORGANIZATION_STOCK) {}

private:

};

class LibraryOrganization : public Organization {
public:
	LibraryOrganization() : Organization(ORGANIZATION_LIBRARY) {}

private:

};

class RoadFixOrganization : public Organization {
public:
	RoadFixOrganization() : Organization(ORGANIZATION_ROADFIX) {}

private:

};

class GasolineOrganization : public Organization {
public:
	GasolineOrganization() : Organization(ORGANIZATION_GASOLINE) {}

private:

};

class CrematoriumOrganization : public Organization {
public:
	CrematoriumOrganization() : Organization(ORGANIZATION_CREMATORIUM) {}

private:

};

class CemeteryOrganization : public Organization {
public:
	CemeteryOrganization() : Organization(ORGANIZATION_CEMETRY) {}

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

class BatteryOrganization : public Organization {
public:
	BatteryOrganization() : Organization(ORGANIZATION_BATTERY) {}

private:

};

class DataOrganization : public Organization {
public:
	DataOrganization() : Organization(ORGANIZATION_DATA) {}

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

class DeviceOrganization : public Organization {
public:
	DeviceOrganization() : Organization(ORGANIZATION_DEVICE) {}

private:

};

class ParkingOrganization : public Organization {
public:
	ParkingOrganization() : Organization(ORGANIZATION_PARKING) {}

private:

};

class GuardOrganization : public Organization {
public:
	GuardOrganization() : Organization(ORGANIZATION_GUARD) {}

private:

};

class ToiletOrganization : public Organization {
public:
	ToiletOrganization() : Organization(ORGANIZATION_TOILET) {}

private:

};

class CanteenOrganization : public Organization {
public:
	CanteenOrganization() : Organization(ORGANIZATION_CANTEEN) {}

private:

};

class DormitoryOrganization : public Organization {
public:
	DormitoryOrganization() : Organization(ORGANIZATION_DORMITRY) {}

private:

};

class PlaygroundOrganization : public Organization {
public:
	PlaygroundOrganization() : Organization(ORGANIZATION_PLAYGROUND) {}

private:

};

class StationOrganization : public Organization {
public:
	StationOrganization() : Organization(ORGANIZATION_STATION) {}

private:

};

std::shared_ptr<Organization> CreateOrganization(ORGANIZATION_TYPE type);