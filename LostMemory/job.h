#pragma once

#include <string>

enum JOB_TYPE {
	JOB_OUTPATIENT_DOCTOR, //门诊医生
	JOB_SURGEON_DOCTOR, //外科医生
	JOB_INTERNAL_DOCTOR, //内科医生
	JOB_SKIN_DOCTOR, //皮肤科医生
	JOB_EYE_DOCTOR, //眼科医生
	JOB_OTOLARY_DOCTOR, //耳鼻喉科医生
	JOB_MOUTH_DOCTOR, //牙科医生
	JOB_CHILD_DOCTOR, //儿科医生
	JOB_BIRTH_DOCTOR, //妇产科医生
	JOB_CANCER_DOCTOR, //肿瘤医生
	JOB_RECOVERY_DOCTOR, //康复科医生
	JOB_ANESTHESIA_DOCTOR, //麻醉科医生
	JOB_MENTAL_DOCTOR, //心理医生
	JOB_WARD_NURSE, //病房护士
	JOB_SURGERY_NURSE, //手术室护士
	JOB_ICU_NURSE, //急诊护士
	JOB_COMMUNITY_NURSE, //社区护士
	JOB_BABY_NURSE, //月嫂
	JOB_ELDER_NURSE, //老年护理员
	JOB_NUTRITION_EXPERT, //营养师
	JOB_KINDER_TEACHER, //幼儿园教师
	JOB_PRIMARY_TEACHER, //小学教师
	JOB_MIDDLE_TEACHER, //中学教师
	JOB_LECTURER_TEACHER, //大学讲师
	JOB_PROFESSOR_TEACHER, //大学教授
	JOB_VOCATIONAL_TEACHER, //技校教师
	JOB_FORIGN_TEACHER, //外国教师
	JOB_TEACHING_EXPERT, //教研员
	JOB_BUSINESS_LAWYER, //商务律师
	JOB_COURT_JUDGE, //法官
	JOB_COURT_PROSECUTER, //检察官
	JOB_CITY_POLICE, //城管
	JOB_CRIMINAL_POLICE, //刑警
	JOB_TRAFFIC_POLICE, //交警
	JOB_PRISON_POLICE, //狱警
	JOB_ARMED_POLICE, //武警
	JOB_PEOPLE_POLICE, //民警
	JOB_NET_POLICE, //网警
	JOB_DRUG_POLICE, //缉毒警
	JOB_FIRE_SOLDIER, //消防员
	JOB_GROUND_SOLDiER, //陆军
	JOB_NAVY_SOLDIER, //海军
	JOB_AIR_SOLDIER, //空军
	JOB_ROCKET_SOLDIER, //火箭军
	JOB_LOGISTICS_SOLDIER, //军队后勤
	JOB_ASTRONAUT_SOLDIER, //宇航员
	JOB_STEVEDORES_WORKER, //装卸工
	JOB_RUNWAY_WORKER, //机场地勤
	JOB_PLANE_CONTROL, //机场空管
	JOB_CIVILIAN_PILOT, //民航飞行员
	JOB_CARGO_PILOT, //货机飞行员
	JOB_HELICOPTOR_PILOT, //直升机飞行员
	JOB_PRIVATE_PILOT, //私人飞行员
	JOB_FLIGHT_ATTENDANT, //空乘
	JOB_PLANE_MAINTENANCE, //飞机检修员
	JOB_SHIP_CONTROL, //码头调度员
	JOB_OCEAN_SAILOR, //远洋海员
	JOB_OFFSHORE_SAILOR, //近海海员
	JOB_RIVER_SAILOR, //内河船员
	JOB_SHIP_SAILOR, //客轮船员
	JOB_CRUISE_SAILOR, //游轮船员
	JOB_BUS_DRIVER, //公交司机
	JOB_TAXI_DRIVER, //出租车司机
	JOB_TRUCK_DRIVER, //货车司机
	JOB_TRAIN_CONTROL, //火车调度员
	JOB_TRAIN_DRIVER, //火车司机
	JOB_METRO_DRIVER, //地铁司机
	JOB_DESIGNATED_DRIVER, //代驾
	JOB_BUSINESS_DRIVER, //公务司机
	JOB_PRIVATE_DRIVER, //私人司机
	JOB_CONSTRUCTION_LEADER, //包工头
	JOB_CONSTRUCTION_WORKER, //建筑工人
	JOB_MACHINE_OPERATOR, //机械操作员
	JOB_CARPENTER_WORKER, //木匠
	JOB_ELECTRIC_WORKER, //电工
	JOB_PLUMBER_WORKER, //管道工
	JOB_PAINTER_WORKER, //油漆工
	JOB_MASON_WORKER, //泥瓦匠
	JOB_ARCHITECTURE_DESIGNER, //建筑设计师
	JOB_VETERINARY_DOCTOR, //兽医
	JOB_PET_KEEPER, //宠物店员
	JOB_ANIMAL_BREEDER, //动物园饲养员
	JOB_FISH_BREEDER, //水族馆饲养员
	JOB_CHINESE_COOK, //中餐厨师
	JOB_WESTERN_COOK, //西餐厨师
	JOB_DOUGH_COOK, //面点师
	JOB_WINE_COOK, //调酒师
	JOB_TEA_COOK, //茶艺师
	JOB_COFFEE_COOK, //咖啡师
	JOB_DATA_ANALYZER, //数据分析师
	JOB_GAME_DEVELOPER, //游戏研发
	JOB_GAME_PLANNER, //游戏策划
	JOB_GAME_ARTIST, //美工
	JOB_PUBLICITY_DESIGNER, //公关
	JOB_SOFTWARE_ENGINEER, //软件工程师
	JOB_HARDWARE_ENGINEER, //硬件工程师
	JOB_ALGORITHM_ENGINEER, //算法工程师
	JOB_SYSTEM_DEVELOPER, //系统研发
	JOB_SOFTWARE_TESTER, //软件测试
	JOB_NET_SECURE, //网络安全
	JOB_SYSTEM_MAINTAIN, //网络运维
	JOB_CIVIL_ENGINEER, //土木工程师
	JOB_HYDRAULIC_ENGINEER, //水利工程师
	JOB_ELECTRIC_ENGINEER, //电力工程师
	JOB_MACHINE_ENGINEER, //机械工程师
	JOB_COMMUNICATION_ENGINEER, //通信工程师
	JOB_AUTOMATION_ENGINEER, //自动化工程师
	JOB_DEVICE_ENGINEER, //仪器工程师
	JOB_MATERIAL_ENGINEER, //材料工程师
	JOB_CHEMICAL_ENGINEER, //化工工程师
	JOB_ENERGY_ENGINEER, //能源工程师
	JOB_MEDIA_DIRECTOR, //导演
	JOB_MEDIA_WRITER, //编剧
	JOB_MEDIA_ACTOR, //影视演员
	JOB_STAGE_ACTOR, //舞台演员
	JOB_DANCE_ACTOR, //舞蹈演员
	JOB_ACROBATIC_ACTOR, //杂技演员
	JOB_MAGIC_ACTOR, //魔术师
	JOB_BLOG_OWNER, //博主
	JOB_LIVE_OWNER, //主播
	JOB_TV_HOST, //主持人
	JOB_CHANNEL_CONTROL, //导播
	JOB_LIVE_COMMENTARY, //解说
	JOB_WATER_DIVER, //潜水员
	JOB_CAR_RACER, //赛车手
	JOB_PROFESSONAL_ATHLETE, //运动员
	JOB_BUSINESS_COACH, //体育教练
	JOB_MATCH_REFEREE, //裁判
	JOB_CHESS_PLAYER, //棋手
	JOB_GAME_MATCHER, //电竞选手
	JOB_ELECTRIC_SHOPER, //电商店员
	JOB_FOOD_DELIVERY, //外卖员
	JOB_PACKAGE_DELIVERY, //快递员
	JOB_PACKAGE_SORTER, //快递分拣员
	JOB_WAREHOUSE_CONTROL, //仓库管理员
	JOB_TEXT_TRANSLATOR, //文字翻译
	JOB_INSTANT_TRANSLATOR, //口译
	JOB_TEXT_EDITOR, //编辑
	JOB_NEWS_REPORTER, //记者
	JOB_TEXT_WRITER, //作家
	JOB_PRINT_WORKER, //印刷工人
	JOB_SECURITY_BROKER, //证券经纪人
	JOB_STOCK_CONSULTANT, //投资顾问
	JOB_BANK_RECEPTION, //银行柜员
	JOB_FINANCIAL_AUDITOR, //审计员
	JOB_FINANCIAL_ACCOUNTANT, //会计师
	JOB_TAX_AGENT, //税务师
	JOB_FINANCIAL_ACTUARY, //精算师
	JOB_PAINTER_ARTIST, //画家
	JOB_ART_DESIGNER, //艺术设计
	JOB_TEXT_PLANNER, //文案策划
	JOB_INDOOR_DESIGNER, //室内设计师
	JOB_CLOTHES_DESIGNER, //服装设计师
	JOB_JEWERY_DESIGNER, //珠宝设计师
	JOB_FIGURE_DESIGNER, //形象设计师
	JOB_PHOTO_TAKER, //摄影师
	JOB_GARDEN_DESIGNER, //园艺师
	JOB_FLOWER_DESIGNER, //花艺师
	JOB_STAGE_SINGER, //歌手
	JOB_SONG_COMPOSER, //作曲家
	JOB_BAND_CONDUCTOR, //指挥
	JOB_INSTRUMENT_PLAYER, //演奏家
	JOB_FARM_WORKER, //农民
	JOB_PASTURE_WORKER, //牧民
	JOB_FISH_WORKER, //渔民
	JOB_BREED_RESERCHER, //育种员
	JOB_FRUIT_WORKER, //果农
	JOB_GEOLOGY_EXPLORER, //地质勘探员
	JOB_ARCHEOLOGY_EXPLORER, //考古学家
	JOB_ENVIRONMENT_PROTECTOR, //环境监测员
	JOB_FOREST_PROTECTOR, //护林员
	JOB_CAR_REPAIRER, //汽修
	JOB_INSTRUMENT_TUNER, //调音师
	JOB_LOCK_MAKER, //锁匠
	JOB_MASAGE_WORKER, //按摩师
	JOB_GLASS_OPTICIAN, //配镜师
	JOB_FACE_BEAUTICIAN, //美容师
	JOB_NAIL_BEAUTICIAL, //美甲师
	JOB_HAIR_BARBER, //理发师
	JOB_TATTOO_WORKER, //纹身师
	JOB_LIGHT_DESIGNER, //灯光师
	JOB_MUSIC_DESIGNER, //音响师
	JOB_VIDEO_DESIGNER, //视频剪辑师
	JOB_QUALITY_INSPECTOR, //质检员
	JOB_MACHINE_SUPERVISOR, //生产主管
	JOB_MACHINE_MAINTAIN, //设备维护员
	JOB_BOILER_WORKER, //锅炉工
	JOB_MACHINE_WORKER, //车间工人
	JOB_HANDICRAFT_WORKER, //手工工人
	JOB_PIPELINE_WORKER, //流水线工人
	JOB_MACHINE_INSTALLER, //设备安装工
	JOB_MINING_WORKER, //矿工
	JOB_RESTAURANT_WAITER, //服务员
	JOB_SHOP_CASHIER, //收银员
	JOB_HALL_MANAGER, //大堂经理
	JOB_HALL_RECEPTION, //前台
	JOB_CUSTOMER_SERVICE, //客服
	JOB_MISS_ETIQUETTE, //礼仪小姐
	JOB_TRAVEL_GUIDE, //导游
	JOB_SITE_ADMIN, //场地管理员
	JOB_ESTATE_DEVELOPER, //开发商
	JOB_HOUSE_SAILOR, //售楼员
	JOB_HOUSE_INTERMEDIARY, //中介
	JOB_SHOP_OWNER, //商店店主
	JOB_SHOP_WORKER, //商店店员
	JOB_RESTAURANT_OWNER, //餐厅店主
	JOB_STALL_OWNER, //路边摊主
	JOB_CIVIL_SERVANT, //公务员
	JOB_GOVERNMENT_OFFICIAL, //政府官员
	JOB_GOVERNMENT_SECRATORY, //行政秘书
	JOB_LIBRARY_ADMIN, //图书管理员
	JOB_FILER_ADMIN, //档案管理员
	JOB_COMPANY_CEO, //总裁
	JOB_DEPARTMENT_MANAGER, //经理
	JOB_PROCUREMENT_MANAGER, //采购
	JOB_SALES_MANAGER, //销售
	JOB_BUSINESS_SECRATORY, //商务秘书
	JOB_HUMAN_RESOURSE, //人力资源专员
	JOB_PERSONAL_NANNY, //保姆
	JOB_PERSONAL_CLEANNING, //保洁
	JOB_SITE_GUARD, //保安
	JOB_BODY_GUARD, //保镖
	JOB_HOUSE_KEEPER, //管家
	JOB_SECURITY_CHECK, //安检员
	JOB_ELEVATOR_WORKER, //电梯工
	JOB_AC_WORKER, //空调工
	JOB_PUBLIC_REPAIRER, //公共设施维修员
	JOB_SHARED_MAINTAIN, //共享服务检修员
	JOB_WASTE_RECYCLER, //废品回收员
	JOB_CEREMONY_MASTER, //司仪
	JOB_CORPSE_UNDERTAKER, //入殓师
	JOB_CEMETORY_ADMIN, //墓地管理员
	JOB_MATCH_MAKER, //红娘
	JOB_COMMUNITY_VOLUNTEER, //社区志愿者
	JOB_STREET_OFFICIAL, //街道工作者
	JOB_ORGAN_DOCTOR, //器官医师
	JOB_PHONE_FRAUD, //电诈
	JOB_STREET_THIEF, //小偷
	JOB_GAMBLE_DEALER, //荷官
	JOB_ADULT_ACTOR, //成人演员
	JOB_DRUG_SALOR, //毒贩
	JOB_DRUG_WORKER, //制毒工人
	JOB_TOMB_ROBBER, //盗墓贼
	JOB_SEX_SERVER //妓女
};

class Job {
public:
	Job() = default;
	Job(JOB_TYPE type) : type(type) {};

	std::string GetTitle() { return title; }

private:
	JOB_TYPE type;
	std::string title;
	int salary;
};

class OutpatientDoctorJob : public Job {
public:
	OutpatientDoctorJob() : Job(JOB_OUTPATIENT_DOCTOR) {}

private:

};

class SurgeonDoctorJob : public Job {
public:
	SurgeonDoctorJob() : Job(JOB_SURGEON_DOCTOR) {}

private:

};

class InternalDoctorJob : public Job {
public:
	InternalDoctorJob() : Job(JOB_INTERNAL_DOCTOR) {}

private:

};

class SkinDoctorJob : public Job {
public:
	SkinDoctorJob() : Job(JOB_SKIN_DOCTOR) {}

private:

};

class EyeDoctorJob : public Job {
public:
	EyeDoctorJob() : Job(JOB_EYE_DOCTOR) {}

private:

};

class OtolaryDoctorJob : public Job {
public:
	OtolaryDoctorJob() : Job(JOB_OTOLARY_DOCTOR) {}

private:

};

class MouthDoctorJob : public Job {
public:
	MouthDoctorJob() : Job(JOB_MOUTH_DOCTOR) {}

private:

};

class ChildDoctorJob : public Job {
public:
	ChildDoctorJob() : Job(JOB_CHILD_DOCTOR) {}

private:

};

class BirthDoctorJob : public Job {
public:
	BirthDoctorJob() : Job(JOB_BIRTH_DOCTOR) {}

private:

};

class CancerDoctorJob : public Job {
public:
	CancerDoctorJob() : Job(JOB_CANCER_DOCTOR) {}

private:

};

class RecoveryDoctorJob : public Job {
public:
	RecoveryDoctorJob() : Job(JOB_RECOVERY_DOCTOR) {}

private:

};

class AnesthesiaDoctorJob : public Job {
public:
	AnesthesiaDoctorJob() : Job(JOB_ANESTHESIA_DOCTOR) {}

private:

};

class MentalDoctorJob : public Job {
public:
	MentalDoctorJob() : Job(JOB_MENTAL_DOCTOR) {}

private:

};

class WardNurseJob : public Job {
public:
	WardNurseJob() : Job(JOB_WARD_NURSE) {}

private:

};

class SurgeryNurseJob : public Job {
public:
	SurgeryNurseJob() : Job(JOB_SURGERY_NURSE) {}

private:

};

class ICUNurseJob : public Job {
public:
	ICUNurseJob() : Job(JOB_ICU_NURSE) {}

private:

};

class CommunityNurseJob : public Job {
public:
	CommunityNurseJob() : Job(JOB_COMMUNITY_NURSE) {}

private:

};

class BabyNurseJob : public Job {
public:
	BabyNurseJob() : Job(JOB_BABY_NURSE) {}

private:

};

class ElderNurseJob : public Job {
public:
	ElderNurseJob() : Job(JOB_ELDER_NURSE) {}

private:

};

class NutritionExpertJob : public Job {
public:
	NutritionExpertJob() : Job(JOB_NUTRITION_EXPERT) {}

private:

};

class KinderTeacherJob : public Job {
public:
	KinderTeacherJob() : Job(JOB_KINDER_TEACHER) {}

private:

};

class PrimaryTeacherJob : public Job {
public:
	PrimaryTeacherJob() : Job(JOB_PRIMARY_TEACHER) {}

private:

};

class MiddleTeacherJob : public Job {
public:
	MiddleTeacherJob() : Job(JOB_MIDDLE_TEACHER) {}

private:

};

class LecturerTeacherJob : public Job {
public:
	LecturerTeacherJob() : Job(JOB_LECTURER_TEACHER) {}

private:

};

class ProfessorTeacherJob : public Job {
public:
	ProfessorTeacherJob() : Job(JOB_PROFESSOR_TEACHER) {}

private:

};

class VocationalTeacherJob : public Job {
public:
	VocationalTeacherJob() : Job(JOB_VOCATIONAL_TEACHER) {}

private:

};

class ForignTeacherJob : public Job {
public:
	ForignTeacherJob() : Job(JOB_FORIGN_TEACHER) {}

private:

};

class TeachingExpertJob : public Job {
public:
	TeachingExpertJob() : Job(JOB_TEACHING_EXPERT) {}

private:

};

class BusinessLawyerJob : public Job {
public:
	BusinessLawyerJob() : Job(JOB_BUSINESS_LAWYER) {}

private:

};

class CourtJudgeJob : public Job {
public:
	CourtJudgeJob() : Job(JOB_COURT_JUDGE) {}

private:

};

class CourtProsecuterJob : public Job {
public:
	CourtProsecuterJob() : Job(JOB_COURT_PROSECUTER) {}

private:

};

class CityPoliceJob : public Job {
public:
	CityPoliceJob() : Job(JOB_CITY_POLICE) {}

private:

};

class CriminalPoliceJob : public Job {
public:
	CriminalPoliceJob() : Job(JOB_CRIMINAL_POLICE) {}

private:

};

class TrafficPoliceJob : public Job {
public:
	TrafficPoliceJob() : Job(JOB_TRAFFIC_POLICE) {}

private:

};

class PrisonPoliceJob : public Job {
public:
	PrisonPoliceJob() : Job(JOB_PRISON_POLICE) {}

private:

};

class ArmedPoliceJob : public Job {
public:
	ArmedPoliceJob() : Job(JOB_ARMED_POLICE) {}

private:

};

class PeoplePoliceJob : public Job {
public:
	PeoplePoliceJob() : Job(JOB_PEOPLE_POLICE) {}

private:

};

class NetPoliceJob : public Job {
public:
	NetPoliceJob() : Job(JOB_NET_POLICE) {}

private:

};

class DrugPoliceJob : public Job {
public:
	DrugPoliceJob() : Job(JOB_DRUG_POLICE) {}

private:

};

class FireSoldierJob : public Job {
public:
	FireSoldierJob() : Job(JOB_FIRE_SOLDIER) {}

private:

};

class GroundSoldierJob : public Job {
public:
	GroundSoldierJob() : Job(JOB_GROUND_SOLDiER) {}

private:

};

class NavySoldierJob : public Job {
public:
	NavySoldierJob() : Job(JOB_NAVY_SOLDIER) {}

private:

};

class AirSoldierJob : public Job {
public:
	AirSoldierJob() : Job(JOB_AIR_SOLDIER) {}

private:

};

class RocketSoldierJob : public Job {
public:
	RocketSoldierJob() : Job(JOB_ROCKET_SOLDIER) {}

private:

};

class LogisticsSoldierJob : public Job {
public:
	LogisticsSoldierJob() : Job(JOB_LOGISTICS_SOLDIER) {}

private:

};

class AstronautSoldierJob : public Job {
public:
	AstronautSoldierJob() : Job(JOB_ASTRONAUT_SOLDIER) {}

private:

};

class StevedoresWorkerJob : public Job {
public:
	StevedoresWorkerJob() : Job(JOB_STEVEDORES_WORKER) {}

private:

};

class RunwayWorkerJob : public Job {
public:
	RunwayWorkerJob() : Job(JOB_RUNWAY_WORKER) {}

private:

};

class PlaneControlJob : public Job {
public:
	PlaneControlJob() : Job(JOB_PLANE_CONTROL) {}

private:

};

class CivilianPilotJob : public Job {
public:
	CivilianPilotJob() : Job(JOB_CIVILIAN_PILOT) {}

private:

};

class CargoPilotJob : public Job {
public:
	CargoPilotJob() : Job(JOB_CARGO_PILOT) {}

private:

};

class HelicopterPilotJob : public Job {
public:
	HelicopterPilotJob() : Job(JOB_HELICOPTOR_PILOT) {}

private:

};

class PrivatePilotJob : public Job {
public:
	PrivatePilotJob() : Job(JOB_PRIVATE_PILOT) {}

private:

};

class FlightAttendantJob : public Job {
public:
	FlightAttendantJob() : Job(JOB_FLIGHT_ATTENDANT) {}

private:

};

class PlaneMaintenanceJob : public Job {
public:
	PlaneMaintenanceJob() : Job(JOB_PLANE_MAINTENANCE) {}

private:

};

class ShipControlJob : public Job {
public:
	ShipControlJob() : Job(JOB_SHIP_CONTROL) {}

private:

};

class OceanSailorJob : public Job {
public:
	OceanSailorJob() : Job(JOB_OCEAN_SAILOR) {}

private:

};

class OffshoreSailorJob : public Job {
public:
	OffshoreSailorJob() : Job(JOB_OFFSHORE_SAILOR) {}

private:

};

class RiverSailorJob : public Job {
public:
	RiverSailorJob() : Job(JOB_RIVER_SAILOR) {}

private:

};

class ShipSailorJob : public Job {
public:
	ShipSailorJob() : Job(JOB_SHIP_SAILOR) {}

private:

};

class CruiseSailorJob : public Job {
public:
	CruiseSailorJob() : Job(JOB_CRUISE_SAILOR) {}

private:

};

class BusDriverJob : public Job {
public:
	BusDriverJob() : Job(JOB_BUS_DRIVER) {}

private:

};

class TaxiDriverJob : public Job {
public:
	TaxiDriverJob() : Job(JOB_TAXI_DRIVER) {}

private:

};

class TruckDriverJob : public Job {
public:
	TruckDriverJob() : Job(JOB_TRUCK_DRIVER) {}

private:

};

class TrainControlJob : public Job {
public:
	TrainControlJob() : Job(JOB_TRAIN_CONTROL) {}

private:

};

class TrainDriverJob : public Job {
public:
	TrainDriverJob() : Job(JOB_TRAIN_DRIVER) {}

private:

};

class MetroDriverJob : public Job {
public:
	MetroDriverJob() : Job(JOB_METRO_DRIVER) {}

private:

};

class DesignatedDriverJob : public Job {
public:
	DesignatedDriverJob() : Job(JOB_DESIGNATED_DRIVER) {}

private:

};

class BusinessDriverJob : public Job {
public:
	BusinessDriverJob() : Job(JOB_BUSINESS_DRIVER) {}

private:

};

class PrivateDriverJob : public Job {
public:
	PrivateDriverJob() : Job(JOB_PRIVATE_DRIVER) {}

private:

};

class ConstructionLeaderJob : public Job {
public:
	ConstructionLeaderJob() : Job(JOB_CONSTRUCTION_LEADER) {}

private:

};

class ConstructionWorkerJob : public Job {
public:
	ConstructionWorkerJob() : Job(JOB_CONSTRUCTION_WORKER) {}

private:

};

class MachineOperatorJob : public Job {
public:
	MachineOperatorJob() : Job(JOB_MACHINE_OPERATOR) {}

private:

};

class CarpenterWorkerJob : public Job {
public:
	CarpenterWorkerJob() : Job(JOB_CARPENTER_WORKER) {}

private:

};

class ElectricWorkerJob : public Job {
public:
	ElectricWorkerJob() : Job(JOB_ELECTRIC_WORKER) {}

private:

};

class PlumberWorkerJob : public Job {
public:
	PlumberWorkerJob() : Job(JOB_PLUMBER_WORKER) {}

private:

};

class PainterWorkerJob : public Job {
public:
	PainterWorkerJob() : Job(JOB_PAINTER_WORKER) {}

private:

};

class MasonWorkerJob : public Job {
public:
	MasonWorkerJob() : Job(JOB_MASON_WORKER) {}

private:

};

class ArchitectureDesignerJob : public Job {
public:
	ArchitectureDesignerJob() : Job(JOB_ARCHITECTURE_DESIGNER) {}

private:

};

class VeterinaryDoctorJob : public Job {
public:
	VeterinaryDoctorJob() : Job(JOB_VETERINARY_DOCTOR) {}

private:

};

class PetKeeperJob : public Job {
public:
	PetKeeperJob() : Job(JOB_PET_KEEPER) {}

private:

};

class AnimalBreederJob : public Job {
public:
	AnimalBreederJob() : Job(JOB_ANIMAL_BREEDER) {}

private:

};

class FishBreederJob : public Job {
public:
	FishBreederJob() : Job(JOB_FISH_BREEDER) {}

private:

};

class ChineseCookJob : public Job {
public:
	ChineseCookJob() : Job(JOB_CHINESE_COOK) {}

private:

};

class WesternCookJob : public Job {
public:
	WesternCookJob() : Job(JOB_WESTERN_COOK) {}

private:

};

class DoughCookJob : public Job {
public:
	DoughCookJob() : Job(JOB_DOUGH_COOK) {}

private:

};

class WineCookJob : public Job {
public:
	WineCookJob() : Job(JOB_WINE_COOK) {}

private:

};

class TeaCookJob : public Job {
public:
	TeaCookJob() : Job(JOB_TEA_COOK) {}

private:

};

class CoffeeCookJob : public Job {
public:
	CoffeeCookJob() : Job(JOB_COFFEE_COOK) {}

private:

};

class DataAnalyzerJob : public Job {
public:
	DataAnalyzerJob() : Job(JOB_DATA_ANALYZER) {}

private:

};

class GameDeveloperJob : public Job {
public:
	GameDeveloperJob() : Job(JOB_GAME_DEVELOPER) {}

private:

};

class GamePlannerJob : public Job {
public:
	GamePlannerJob() : Job(JOB_GAME_PLANNER) {}

private:

};

class GameArtistJob : public Job {
public:
	GameArtistJob() : Job(JOB_GAME_ARTIST) {}

private:

};

class PublicityDesignerJob : public Job {
public:
	PublicityDesignerJob() : Job(JOB_PUBLICITY_DESIGNER) {}

private:

};

class SoftwareEngineerJob : public Job {
public:
	SoftwareEngineerJob() : Job(JOB_SOFTWARE_ENGINEER) {}

private:

};

class HardwareEngineerJob : public Job {
public:
	HardwareEngineerJob() : Job(JOB_HARDWARE_ENGINEER) {}

private:

};

class AlgorithmEngineerJob : public Job {
public:
	AlgorithmEngineerJob() : Job(JOB_ALGORITHM_ENGINEER) {}

private:

};

class SystemDeveloperJob : public Job {
public:
	SystemDeveloperJob() : Job(JOB_SYSTEM_DEVELOPER) {}

private:

};

class SoftwareTesterJob : public Job {
public:
	SoftwareTesterJob() : Job(JOB_SOFTWARE_TESTER) {}

private:

};

class NetSecureJob : public Job {
public:
	NetSecureJob() : Job(JOB_NET_SECURE) {}

private:

};

class SystemMaintainJob : public Job {
public:
	SystemMaintainJob() : Job(JOB_SYSTEM_MAINTAIN) {}

private:

};

class CivilEngineerJob : public Job {
public:
	CivilEngineerJob() : Job(JOB_CIVIL_ENGINEER) {}

private:

};

class HydraulicEngineerJob : public Job {
public:
	HydraulicEngineerJob() : Job(JOB_HYDRAULIC_ENGINEER) {}

private:

};

class ElectricEngineerJob : public Job {
public:
	ElectricEngineerJob() : Job(JOB_ELECTRIC_ENGINEER) {}

private:

};

class MachineEngineerJob : public Job {
public:
	MachineEngineerJob() : Job(JOB_MACHINE_ENGINEER) {}

private:

};

class CommunicationEngineerJob : public Job {
public:
	CommunicationEngineerJob() : Job(JOB_COMMUNICATION_ENGINEER) {}

private:

};

class AutomationEngineerJob : public Job {
public:
	AutomationEngineerJob() : Job(JOB_AUTOMATION_ENGINEER) {}

private:

};

class DeviceEngineerJob : public Job {
public:
	DeviceEngineerJob() : Job(JOB_DEVICE_ENGINEER) {}

private:

};

class MaterialEngineerJob : public Job {
public:
	MaterialEngineerJob() : Job(JOB_MATERIAL_ENGINEER) {}

private:

};

class ChemicalEngineerJob : public Job {
public:
	ChemicalEngineerJob() : Job(JOB_CHEMICAL_ENGINEER) {}

private:

};

class EnergyEngineerJob : public Job {
public:
	EnergyEngineerJob() : Job(JOB_ENERGY_ENGINEER) {}

private:

};

class MediaDirectorJob : public Job {
public:
	MediaDirectorJob() : Job(JOB_MEDIA_DIRECTOR) {}

private:

};

class MediaWriterJob : public Job {
public:
	MediaWriterJob() : Job(JOB_MEDIA_WRITER) {}

private:

};

class MediaActorJob : public Job {
public:
	MediaActorJob() : Job(JOB_MEDIA_ACTOR) {}

private:

};

class StageActorJob : public Job {
public:
	StageActorJob() : Job(JOB_STAGE_ACTOR) {}

private:

};

class DanceActorJob : public Job {
public:
	DanceActorJob() : Job(JOB_DANCE_ACTOR) {}

private:

};

class AcrobaticActorJob : public Job {
public:
	AcrobaticActorJob() : Job(JOB_ACROBATIC_ACTOR) {}

private:

};

class MagicActorJob : public Job {
public:
	MagicActorJob() : Job(JOB_MAGIC_ACTOR) {}

private:

};

class BlogOwnerJob : public Job {
public:
	BlogOwnerJob() : Job(JOB_BLOG_OWNER) {}

private:

};

class LiveOwnerJob : public Job {
public:
	LiveOwnerJob() : Job(JOB_LIVE_OWNER) {}

private:

};

class TVHostJob : public Job {
public:
	TVHostJob() : Job(JOB_TV_HOST) {}

private:

};

class ChannelControlJob : public Job {
public:
	ChannelControlJob() : Job(JOB_CHANNEL_CONTROL) {}

private:

};

class LiveCommentaryJob : public Job {
public:
	LiveCommentaryJob() : Job(JOB_LIVE_COMMENTARY) {}

private:

};

class WaterDiverJob : public Job {
public:
	WaterDiverJob() : Job(JOB_WATER_DIVER) {}

private:

};

class CarRacerJob : public Job {
public:
	CarRacerJob() : Job(JOB_CAR_RACER) {}

private:

};

class ProfessionalAthleteJob : public Job {
public:
	ProfessionalAthleteJob() : Job(JOB_PROFESSONAL_ATHLETE) {}

private:

};

class BusinessCoachJob : public Job {
public:
	BusinessCoachJob() : Job(JOB_BUSINESS_COACH) {}

private:

};

class MatchRefereeJob : public Job {
public:
	MatchRefereeJob() : Job(JOB_MATCH_REFEREE) {}

private:

};

class ChessPlayerJob : public Job {
public:
	ChessPlayerJob() : Job(JOB_CHESS_PLAYER) {}

private:

};

class GameMatcherJob : public Job {
public:
	GameMatcherJob() : Job(JOB_GAME_MATCHER) {}

private:

};

class ElectricShoperJob : public Job {
public:
	ElectricShoperJob() : Job(JOB_ELECTRIC_SHOPER) {}

private:

};

class FoodDeliveryJob : public Job {
public:
	FoodDeliveryJob() : Job(JOB_FOOD_DELIVERY) {}

private:

};

class PackageDeliveryJob : public Job {
public:
	PackageDeliveryJob() : Job(JOB_PACKAGE_DELIVERY) {}

private:

};

class PackageSorterJob : public Job {
public:
	PackageSorterJob() : Job(JOB_PACKAGE_SORTER) {}

private:

};

class WarehouseControlJob : public Job {
public:
	WarehouseControlJob() : Job(JOB_WAREHOUSE_CONTROL) {}

private:

};

class TextTranslatorJob : public Job {
public:
	TextTranslatorJob() : Job(JOB_TEXT_TRANSLATOR) {}

private:

};

class InstantTranslatorJob : public Job {
public:
	InstantTranslatorJob() : Job(JOB_INSTANT_TRANSLATOR) {}

private:

};

class TextEditorJob : public Job {
public:
	TextEditorJob() : Job(JOB_TEXT_EDITOR) {}

private:

};

class NewsReporterJob : public Job {
public:
	NewsReporterJob() : Job(JOB_NEWS_REPORTER) {}

private:

};

class TextWriterJob : public Job {
public:
	TextWriterJob() : Job(JOB_TEXT_WRITER) {}

private:

};

class PrintWorkerJob : public Job {
public:
	PrintWorkerJob() : Job(JOB_PRINT_WORKER) {}

private:

};

class SecurityBrokerJob : public Job {
public:
	SecurityBrokerJob() : Job(JOB_SECURITY_BROKER) {}

private:

};

class StockConsultantJob : public Job {
public:
	StockConsultantJob() : Job(JOB_STOCK_CONSULTANT) {}

private:

};

class BankReceptionJob : public Job {
public:
	BankReceptionJob() : Job(JOB_BANK_RECEPTION) {}

private:

};

class FinancialAuditorJob : public Job {
public:
	FinancialAuditorJob() : Job(JOB_FINANCIAL_AUDITOR) {}

private:

};

class FinancialAccountantJob : public Job {
public:
	FinancialAccountantJob() : Job(JOB_FINANCIAL_ACCOUNTANT) {}

private:

};

class TaxAgentJob : public Job {
public:
	TaxAgentJob() : Job(JOB_TAX_AGENT) {}

private:

};

class FinancialActuaryJob : public Job {
public:
	FinancialActuaryJob() : Job(JOB_FINANCIAL_ACTUARY) {}

private:

};

class PainterArtistJob : public Job {
public:
	PainterArtistJob() : Job(JOB_PAINTER_ARTIST) {}

private:

};

class ArtDesignerJob : public Job {
public:
	ArtDesignerJob() : Job(JOB_ART_DESIGNER) {}

private:

};

class TextPlannerJob : public Job {
public:
	TextPlannerJob() : Job(JOB_TEXT_PLANNER) {}

private:

};

class IndoorDesignerJob : public Job {
public:
	IndoorDesignerJob() : Job(JOB_INDOOR_DESIGNER) {}

private:

};

class ClothesDesignerJob : public Job {
public:
	ClothesDesignerJob() : Job(JOB_CLOTHES_DESIGNER) {}

private:

};

class JeweryDesignerJob : public Job {
public:
	JeweryDesignerJob() : Job(JOB_JEWERY_DESIGNER) {}

private:

};

class FigureDesignerJob : public Job {
public:
	FigureDesignerJob() : Job(JOB_FIGURE_DESIGNER) {}

private:

};

class PhotoTakerJob : public Job {
public:
	PhotoTakerJob() : Job(JOB_PHOTO_TAKER) {}

private:

};

class GardenDesignerJob : public Job {
public:
	GardenDesignerJob() : Job(JOB_GARDEN_DESIGNER) {}

private:

};

class FlowerDesignerJob : public Job {
public:
	FlowerDesignerJob() : Job(JOB_FLOWER_DESIGNER) {}

private:

};

class StageSingerJob : public Job {
public:
	StageSingerJob() : Job(JOB_STAGE_SINGER) {}

private:

};

class SongComposerJob : public Job {
public:
	SongComposerJob() : Job(JOB_SONG_COMPOSER) {}

private:

};

class BandConductorJob : public Job {
public:
	BandConductorJob() : Job(JOB_BAND_CONDUCTOR) {}

private:

};

class InstrumentPlayerJob : public Job {
public:
	InstrumentPlayerJob() : Job(JOB_INSTRUMENT_PLAYER) {}

private:

};

class FarmWorkerJob : public Job {
public:
	FarmWorkerJob() : Job(JOB_FARM_WORKER) {}

private:

};

class PastureWorkerJob : public Job {
public:
	PastureWorkerJob() : Job(JOB_PASTURE_WORKER) {}

private:

};

class FishWorkerJob : public Job {
public:
	FishWorkerJob() : Job(JOB_FISH_WORKER) {}

private:

};

class BreedResearcherJob : public Job {
public:
	BreedResearcherJob() : Job(JOB_BREED_RESERCHER) {}

private:

};

class FruitWorkerJob : public Job {
public:
	FruitWorkerJob() : Job(JOB_FRUIT_WORKER) {}

private:

};

class GeologyExplorerJob : public Job {
public:
	GeologyExplorerJob() : Job(JOB_GEOLOGY_EXPLORER) {}

private:

};

class ArcheologyExplorerJob : public Job {
public:
	ArcheologyExplorerJob() : Job(JOB_ARCHEOLOGY_EXPLORER) {}

private:

};

class EnvironmentProtectorJob : public Job {
public:
	EnvironmentProtectorJob() : Job(JOB_ENVIRONMENT_PROTECTOR) {}

private:

};

class ForestProtectorJob : public Job {
public:
	ForestProtectorJob() : Job(JOB_FOREST_PROTECTOR) {}

private:

};

class CarRepairerJob : public Job {
public:
	CarRepairerJob() : Job(JOB_CAR_REPAIRER) {}

private:

};

class InstrumentTunerJob : public Job {
public:
	InstrumentTunerJob() : Job(JOB_INSTRUMENT_TUNER) {}

private:

};

class LockMakerJob : public Job {
public:
	LockMakerJob() : Job(JOB_LOCK_MAKER) {}

private:

};

class MasageWorkerJob : public Job {
public:
	MasageWorkerJob() : Job(JOB_MASAGE_WORKER) {}

private:

};

class GlassOpticianJob : public Job {
public:
	GlassOpticianJob() : Job(JOB_GLASS_OPTICIAN) {}

private:

};

class FaceBeauticianJob : public Job {
public:
	FaceBeauticianJob() : Job(JOB_FACE_BEAUTICIAN) {}

private:

};

class NailBeauticianJob : public Job {
public:
	NailBeauticianJob() : Job(JOB_NAIL_BEAUTICIAL) {}

private:

};

class HairBarberJob : public Job {
public:
	HairBarberJob() : Job(JOB_HAIR_BARBER) {}

private:

};

class TattooWorkerJob : public Job {
public:
	TattooWorkerJob() : Job(JOB_TATTOO_WORKER) {}

private:

};

class LightDesignerJob : public Job {
public:
	LightDesignerJob() : Job(JOB_LIGHT_DESIGNER) {}

private:

};

class MusicDesignerJob : public Job {
public:
	MusicDesignerJob() : Job(JOB_MUSIC_DESIGNER) {}

private:

};

class VideoDesignerJob : public Job {
public:
	VideoDesignerJob() : Job(JOB_VIDEO_DESIGNER) {}

private:

};

class QualityInspectorJob : public Job {
public:
	QualityInspectorJob() : Job(JOB_QUALITY_INSPECTOR) {}

private:

};

class MachineSupervisorJob : public Job {
public:
	MachineSupervisorJob() : Job(JOB_MACHINE_SUPERVISOR) {}

private:

};

class MachineMaintainJob : public Job {
public:
	MachineMaintainJob() : Job(JOB_MACHINE_MAINTAIN) {}

private:

};

class BoilerWorkerJob : public Job {
public:
	BoilerWorkerJob() : Job(JOB_BOILER_WORKER) {}

private:

};

class MachineWorkerJob : public Job {
public:
	MachineWorkerJob() : Job(JOB_MACHINE_WORKER) {}

private:

};

class HandicraftWorkerJob : public Job {
public:
	HandicraftWorkerJob() : Job(JOB_HANDICRAFT_WORKER) {}

private:

};

class PipelineWorkerJob : public Job {
public:
	PipelineWorkerJob() : Job(JOB_PIPELINE_WORKER) {}

private:

};

class MachineInstallerJob : public Job {
public:
	MachineInstallerJob() : Job(JOB_MACHINE_INSTALLER) {}

private:

};

class MiningWorkerJob : public Job {
public:
	MiningWorkerJob() : Job(JOB_MINING_WORKER) {}

private:

};

class RestaurantWaiterJob : public Job {
public:
	RestaurantWaiterJob() : Job(JOB_RESTAURANT_WAITER) {}

private:

};

class ShopCashierJob : public Job {
public:
	ShopCashierJob() : Job(JOB_SHOP_CASHIER) {}

private:

};

class HallManagerJob : public Job {
public:
	HallManagerJob() : Job(JOB_HALL_MANAGER) {}

private:

};

class HallReceptionJob : public Job {
public:
	HallReceptionJob() : Job(JOB_HALL_RECEPTION) {}

private:

};

class CustomerServiceJob : public Job {
public:
	CustomerServiceJob() : Job(JOB_CUSTOMER_SERVICE) {}

private:

};

class MissEtiquetteJob : public Job {
public:
	MissEtiquetteJob() : Job(JOB_MISS_ETIQUETTE) {}

private:

};

class TravelGuideJob : public Job {
public:
	TravelGuideJob() : Job(JOB_TRAVEL_GUIDE) {}

private:

};

class SiteAdminJob : public Job {
public:
	SiteAdminJob() : Job(JOB_SITE_ADMIN) {}

private:

};

class EstateDeveloperJob : public Job {
public:
	EstateDeveloperJob() : Job(JOB_ESTATE_DEVELOPER) {}

private:

};

class HouseSailorJob : public Job {
public:
	HouseSailorJob() : Job(JOB_HOUSE_SAILOR) {}

private:

};

class HouseIntermediaryJob : public Job {
public:
	HouseIntermediaryJob() : Job(JOB_HOUSE_INTERMEDIARY) {}

private:

};

class ShopOwnerJob : public Job {
public:
	ShopOwnerJob() : Job(JOB_SHOP_OWNER) {}

private:

};

class ShopWorkerJob : public Job {
public:
	ShopWorkerJob() : Job(JOB_SHOP_WORKER) {}

private:

};

class RestaurantOwnerJob : public Job {
public:
	RestaurantOwnerJob() : Job(JOB_RESTAURANT_OWNER) {}

private:

};

class StallOwnerJob : public Job {
public:
	StallOwnerJob() : Job(JOB_STALL_OWNER) {}

private:

};

class CivilServantJob : public Job {
public:
	CivilServantJob() : Job(JOB_CIVIL_SERVANT) {}

private:

};

class GovernmentOfficialJob : public Job {
public:
	GovernmentOfficialJob() : Job(JOB_GOVERNMENT_OFFICIAL) {}

private:

};

class GovernmentSecretaryJob : public Job {
public:
	GovernmentSecretaryJob() : Job(JOB_GOVERNMENT_SECRATORY) {}

private:

};

class LibraryAdminJob : public Job {
public:
	LibraryAdminJob() : Job(JOB_LIBRARY_ADMIN) {}

private:

};

class FilerAdminJob : public Job {
public:
	FilerAdminJob() : Job(JOB_FILER_ADMIN) {}

private:

};

class CompanyCEOJob : public Job {
public:
	CompanyCEOJob() : Job(JOB_COMPANY_CEO) {}

private:

};

class DepartmentManagerJob : public Job {
public:
	DepartmentManagerJob() : Job(JOB_DEPARTMENT_MANAGER) {}

private:

};

class ProcurementManagerJob : public Job {
public:
	ProcurementManagerJob() : Job(JOB_PROCUREMENT_MANAGER) {}

private:

};

class SalesManagerJob : public Job {
public:
	SalesManagerJob() : Job(JOB_SALES_MANAGER) {}

private:

};

class BusinessSecretaryJob : public Job {
public:
	BusinessSecretaryJob() : Job(JOB_BUSINESS_SECRATORY) {}

private:

};

class HumanResourceJob : public Job {
public:
	HumanResourceJob() : Job(JOB_HUMAN_RESOURSE) {}

private:

};

class PersonalNannyJob : public Job {
public:
	PersonalNannyJob() : Job(JOB_PERSONAL_NANNY) {}

private:

};

class PersonalCleaningJob : public Job {
public:
	PersonalCleaningJob() : Job(JOB_PERSONAL_CLEANNING) {}

private:

};

class SiteGuardJob : public Job {
public:
	SiteGuardJob() : Job(JOB_SITE_GUARD) {}

private:

};

class BodyGuardJob : public Job {
public:
	BodyGuardJob() : Job(JOB_BODY_GUARD) {}

private:

};

class HouseKeeperJob : public Job {
public:
	HouseKeeperJob() : Job(JOB_HOUSE_KEEPER) {}

private:

};

class SecurityCheckJob : public Job {
public:
	SecurityCheckJob() : Job(JOB_SECURITY_CHECK) {}

private:

};

class ElevatorWorkerJob : public Job {
public:
	ElevatorWorkerJob() : Job(JOB_ELEVATOR_WORKER) {}

private:

};

class ACWorkerJob : public Job {
public:
	ACWorkerJob() : Job(JOB_AC_WORKER) {}

private:

};

class PublicRepairerJob : public Job {
public:
	PublicRepairerJob() : Job(JOB_PUBLIC_REPAIRER) {}

private:

};

class SharedMaintainJob : public Job {
public:
	SharedMaintainJob() : Job(JOB_SHARED_MAINTAIN) {}

private:

};

class WasteRecyclerJob : public Job {
public:
	WasteRecyclerJob() : Job(JOB_WASTE_RECYCLER) {}

private:

};

class CeremonyMasterJob : public Job {
public:
	CeremonyMasterJob() : Job(JOB_CEREMONY_MASTER) {}

private:

};

class CorpseUndertakerJob : public Job {
public:
	CorpseUndertakerJob() : Job(JOB_CORPSE_UNDERTAKER) {}

private:

};

class CemeteryAdminJob : public Job {
public:
	CemeteryAdminJob() : Job(JOB_CEMETORY_ADMIN) {}

private:

};

class MatchMakerJob : public Job {
public:
	MatchMakerJob() : Job(JOB_MATCH_MAKER) {}

private:

};

class CommunityVolunteerJob : public Job {
public:
	CommunityVolunteerJob() : Job(JOB_COMMUNITY_VOLUNTEER) {}

private:

};

class StreetOfficialJob : public Job {
public:
	StreetOfficialJob() : Job(JOB_STREET_OFFICIAL) {}

private:

};

class OrganDoctorJob : public Job {
public:
	OrganDoctorJob() : Job(JOB_ORGAN_DOCTOR) {}

private:

};

class PhoneFraudJob : public Job {
public:
	PhoneFraudJob() : Job(JOB_PHONE_FRAUD) {}

private:

};

class StreetThiefJob : public Job {
public:
	StreetThiefJob() : Job(JOB_STREET_THIEF) {}

private:

};

class GambleDealerJob : public Job {
public:
	GambleDealerJob() : Job(JOB_GAMBLE_DEALER) {}

private:

};

class AdultActorJob : public Job {
public:
	AdultActorJob() : Job(JOB_ADULT_ACTOR) {}

private:

};

class DrugSalorJob : public Job {
public:
	DrugSalorJob() : Job(JOB_DRUG_SALOR) {}

private:

};

class DrugWorkerJob : public Job {
public:
	DrugWorkerJob() : Job(JOB_DRUG_WORKER) {}

private:

};

class TombRobberJob : public Job {
public:
	TombRobberJob() : Job(JOB_TOMB_ROBBER) {}

private:

};

class SexServerJob : public Job {
public:
	SexServerJob() : Job(JOB_SEX_SERVER) {}

private:

};