#pragma warning(disable:4244)
#pragma warning(disable:4267)

#include "util.h"
#include "zone.h"


using namespace std;

ZONE_TYPE Zone::GetType() {
	return type;
}

void Zone::SetType(ZONE_TYPE type) {
	this->type = type;
}

AREA_TYPE Zone::GetAreaType() {
	return area;
}

void Zone::SetAreaType(AREA_TYPE type) {
	area = type;
}

vector<shared_ptr<Building>>& Zone::GetBuildings() {
	return buildings;
}

vector<shared_ptr<Plot>> Zone::GetPlots() {
	vector<shared_ptr<Plot>> plots;
	for (auto b : buildings)plots.push_back(b);
	return plots;
}

bool Zone::CalcAcreage(shared_ptr<Building> building, float scalar) {
	int content = 0;
	for (auto b : buildings) {
		content += b->GetAcreage();
	}
	int rest = GetAcreage() - content;

	int minAcreage = building->GetAcreageRange().first;
	int maxAcreage = building->GetAcreageRange().second;
	if (scalar < 1.0f) {
		maxAcreage = max(minAcreage, maxAcreage * scalar);
	}
	if (scalar > 1.0f) {
		minAcreage = min(minAcreage * scalar, maxAcreage);
	}

	if (rest < minAcreage) {
		return false;
	}

	if (rest > maxAcreage) {
		float range = log(maxAcreage) - log(minAcreage);
		range *= (GetRandom(1000) / 1000.0f);
		range = exp(log(minAcreage) + range);
		building->SetAcreage(range);
	}
	else {
		if (rest > minAcreage * 2) {
			if (GetRandom(2)) {
				building->SetAcreage(rest / 2);
			}
			else {
				building->SetAcreage(rest);
			}
		}
		else {
			building->SetAcreage(rest);
		}
	}

	return true;
}

shared_ptr<Zone> CreateZone(ZONE_TYPE type) {
	switch (type) {
	case ZONE_NONE:
		return nullptr;
	case ZONE_SPACE:
		return LM_NEW(SpaceZone);
	case ZONE_ARMY:
		return LM_NEW(ArmyZone);
	case ZONE_GENERATOR:
		return LM_NEW(GeneratorZone);
	case ZONE_WATER:
		return LM_NEW(WaterZone);
	case ZONE_GARBAGE:
		return LM_NEW(GarbageZone);
	case ZONE_PRISON:
		return LM_NEW(PrisonZone);
	case ZONE_HOSPITAL:
		return LM_NEW(HospitalZone);
	case ZONE_FILM:
		return LM_NEW(FilmZone);
	case ZONE_SPORT:
		return LM_NEW(SportZone);
	case ZONE_CAMPUS:
		return LM_NEW(CampusZone);
	case ZONE_COMMUNITY:
		return LM_NEW(CommunityZone);
	case ZONE_VILLA:
		return LM_NEW(VillaZone);
	case ZONE_SHOPPING:
		return LM_NEW(ShoppingZone);
	case ZONE_GOVERNMENT:
		return LM_NEW(GovernmentZone);
	case ZONE_COMPANY:
		return LM_NEW(CompanyZone);
	case ZONE_FINANCE:
		return LM_NEW(FinanceZone);
	case ZONE_RESEARCHING:
		return LM_NEW(ResearchingZone);
	case ZONE_EXHIBITION:
		return LM_NEW(ExhibitionZone);
	case ZONE_INDUSTRY:
		return LM_NEW(IndustryZone);
	case ZONE_RESOURCE:
		return LM_NEW(ResourceZone);
	case ZONE_AMUSEMENT:
		return LM_NEW(AmusementZone);
	case ZONE_TOURISM:
		return LM_NEW(TourismZone);
	default:
		return nullptr;
	}
	return nullptr;
}

ZONE_TYPE RandomZone(AREA_TYPE area, float prob) {
	switch (area) {
	case AREA_NONE:
		break;
	case AREA_ROAD:
		break;
	case AREA_CENTER:
		break;
	case AREA_RESIDENTH:
		if (prob < 0.4f)return ZONE_COMMUNITY;
		else break;
	case AREA_RESIDENTM:
		if (prob < 0.6f)return ZONE_COMMUNITY;
		else if (prob < 0.7f)return ZONE_VILLA;
		else break;
	case AREA_RESIDENTL:
		if (prob < 0.6f)return ZONE_VILLA;
		else break;
	case AREA_COMMERCEH:
		if (prob < 0.5f)return ZONE_SHOPPING;
		else break;
	case AREA_COMMERCEL:
		if (prob < 0.2f)return ZONE_SHOPPING;
		else break;
	case AREA_OFFICEH:
		if (prob < 0.1f)return ZONE_GOVERNMENT;
		else if (prob < 0.3f)return ZONE_COMPANY;
		else if (prob < 0.33f)return ZONE_FINANCE;
		else if (prob < 0.38f)return ZONE_RESEARCHING;
		else if (prob < 0.40f)return ZONE_EXHIBITION;
		else break;
	case AREA_OFFICEL:
		if (prob < 0.3f)return ZONE_COMPANY;
		else if (prob < 0.4f)return ZONE_RESEARCHING;
		else if (prob < 0.45f)return ZONE_EXHIBITION;
		else break;
		break;
	case AREA_INDUSTRY:
		if (prob < 0.6f)return ZONE_INDUSTRY;
		else if (prob < 0.7f)return ZONE_RESOURCE;
		else break;
	case AREA_GREEN:
		if (prob < 0.1f)return ZONE_AMUSEMENT;
		else if (prob < 0.25f)return ZONE_TOURISM;
		else break;
	default:
		break;
	}
	return ZONE_NONE;
}

void SpaceZone::ArrangeBuilding() {
	AddBuilding<RocketBuilding>(1);
	AddBuilding<LabBuilding>(1);
	AddBuilding<WarehouseBuilding>(1, 2.0f);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<ParkingBuilding>(1);
	AddBuilding<DormitryBuilding>(1);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<PlaygroundBuilding>(1);
	AddBuilding<ParkingBuilding>(1);
	AddBuilding<WarehouseBuilding>(2, 2.0f);
	AddBuilding<DormitryBuilding>(1);
	AddBuilding<ParkingBuilding>(1);
	AddBuilding<PlaygroundBuilding>(1);
	FillWithBuilding<ParkBuilding>();
}

void ArmyZone::ArrangeBuilding() {
	AddBuilding<PlaygroundBuilding>(2, 2.0f);
	AddBuilding<WarehouseBuilding>(2);
	AddBuilding<DormitryBuilding>(2);
	AddBuilding<CanteenBuilding>(2);
	AddBuilding<GuardBuilding>(2);
	AddBuilding<ParkingBuilding>(3, 2.0f);
	AddBuilding<PlaygroundBuilding>(2);
	AddBuilding<DormitryBuilding>(2);
	AddBuilding<WarehouseBuilding>(2);
	AddBuilding<ParkingBuilding>(3);
	FillWithBuilding<PlaygroundBuilding>();
}

void PrisonZone::ArrangeBuilding() {
	AddBuilding<GuardBuilding>(4, 0.5f);
	AddBuilding<DormitryBuilding>(3, 2.0f);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<WarehouseBuilding>(1);
	AddBuilding<PlaygroundBuilding>(1, 0.5f);
	AddBuilding<OfficeBuilding>(1);
	AddBuilding<ParkingBuilding>(1);
	AddBuilding<GuardBuilding>(4, 0.5f);
	AddBuilding<DormitryBuilding>(3, 2.0f);
	AddBuilding<WarehouseBuilding>(1);
	AddBuilding<PlaygroundBuilding>(1, 0.5f);
	AddBuilding<DormitryBuilding>(3);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<GuardBuilding>(4, 0.5f);
	AddBuilding<ParkingBuilding>(1);
	FillWithBuilding<PlaygroundBuilding>();
}

void GeneratorZone::ArrangeBuilding() {
	int type = GetRandom(3);
	if (type == 0) {
		AddBuilding<PowerBuilding>(1);
	}
	else if (type == 1) {
		AddBuilding<WindmillBuilding>(8);
	}
	else {
		AddBuilding<NuclearBuilding>(1);
	}
	AddBuilding<BatteryBuilding>(3);
	AddBuilding<WarehouseBuilding>(4);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<DormitryBuilding>(1);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<ParkingBuilding>(1);
	AddBuilding<BatteryBuilding>(3);
	AddBuilding<WarehouseBuilding>(4);
	FillWithBuilding<ParkBuilding>();
}

void WaterZone::ArrangeBuilding() {
	AddBuilding<WaterBuilding>(1);
	AddBuilding<SewageBuilding>(1);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<ParkingBuilding>(1);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<DormitryBuilding>(1);
	FillWithBuilding<ParkBuilding>();
}

void GarbageZone::ArrangeBuilding() {
	AddBuilding<RecycleBuilding>(1);
	AddBuilding<TrashBuilding>(1);
	AddBuilding<IncinerationBuilding>(1);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<ParkingBuilding>(1);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<DormitryBuilding>(1);
	FillWithBuilding<ParkBuilding>();
}

void HospitalZone::ArrangeBuilding() {
	AddBuilding<HospitalBuilding>(1);
	AddBuilding<InpatientBuilding>(1);
	AddBuilding<ParkingBuilding>(1);
	AddBuilding<GuardBuilding>(1, 0.5f);
	FillWithBuilding<HospitalBuilding>();
}

void FilmZone::ArrangeBuilding() {
	AddBuilding<PlaygroundBuilding>(4, 0.8f);
	AddBuilding<WarehouseBuilding>(2);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<ParkBuilding>(1);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<DormitryBuilding>(1);
	AddBuilding<PlaygroundBuilding>(2);
	AddBuilding<WarehouseBuilding>(2);
	FillWithBuilding<PlaygroundBuilding>();
}

void SportZone::ArrangeBuilding() {
	AddBuilding<StadiumBuilding>(1);
	AddBuilding<WarehouseBuilding>(1);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<ParkBuilding>(1);
	FillWithBuilding<PlaygroundBuilding>();
}

void CampusZone::ArrangeBuilding() {
	AddBuilding<SchoolBuilding>(4, 2.0f);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<ParkBuilding>(1, 0.5f);
	AddBuilding<LibraryBuilding>(1);
	AddBuilding<DormitryBuilding>(2);
	AddBuilding<LabBuilding>(1);
	AddBuilding<GymBuilding>(1);
	AddBuilding<PlaygroundBuilding>(1);
	AddBuilding<StatueBuilding>(1, 0.5f);
	AddBuilding<HospitalBuilding>(1, 0.5f);
	AddBuilding<DormitryBuilding>(2);
	AddBuilding<ParkBuilding>(1);
	AddBuilding<WarehouseBuilding>(1);
	AddBuilding<SchoolBuilding>(4);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<PackageBuilding>(1);
	AddBuilding<LabBuilding>(1);
	AddBuilding<DataBuilding>(1);
	AddBuilding<StatueBuilding>(1, 0.5f);
	FillWithBuilding<SchoolBuilding>();
}

void CommunityZone::ArrangeBuilding() {
	AddBuilding<ResidentBuilding>(4);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<ParkingBuilding>(1);
	AddBuilding<ParkBuilding>(2, 0.2f);
	FillWithBuilding<ResidentBuilding>();
}

void VillaZone::ArrangeBuilding() {
	AddBuilding<VillaBuilding>(4);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<ParkBuilding>(2, 0.2f);
	FillWithBuilding<VillaBuilding>();
}

void ShoppingZone::ArrangeBuilding() {
	AddBuilding<RestaurantBuilding>(1);
	AddBuilding<MallBuilding>(1);
	AddBuilding<MarketBuilding>(1);
	AddBuilding<BrandBuilding>(2);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<RestaurantBuilding>(2);
	AddBuilding<HotelBuilding>(2);
	AddBuilding<IngredientBuilding>(1);
	AddBuilding<BrandBuilding>(2);
	AddBuilding<MusicBuilding>(1);
	AddBuilding<CarRentBuilding>(2);
	AddBuilding<TheaterBuilding>(1);
	AddBuilding<CinemaBuilding>(1);
	AddBuilding<PubBuilding>(4);
	AddBuilding<MasageBuilding>(1);
	AddBuilding<BrandBuilding>(2);
	AddBuilding<RestaurantBuilding>(4);
	AddBuilding<HotelBuilding>(2);
	AddBuilding<MallBuilding>(1);
	AddBuilding<MarketBuilding>(1);
	FillWithBuilding<BrandBuilding>();
}

void GovernmentZone::ArrangeBuilding() {
	AddBuilding<GovernmentBuilding>(2);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<GovernmentBuilding>(2);
	AddBuilding<ParkBuilding>(1);
	FillWithBuilding<GovernmentBuilding>();
}

void CompanyZone::ArrangeBuilding() {
	AddBuilding<OfficeBuilding>(3);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<ParkBuilding>(1);
	FillWithBuilding<OfficeBuilding>();
}

void FinanceZone::ArrangeBuilding() {
	AddBuilding<OfficeBuilding>(1);
	AddBuilding<StockBuilding>(1);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<ParkBuilding>(2);
	FillWithBuilding<OfficeBuilding>();
}

void ResearchingZone::ArrangeBuilding() {
	AddBuilding<LabBuilding>(1);
	AddBuilding<OfficeBuilding>(1);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<CanteenBuilding>(1);
	AddBuilding<LabBuilding>(1);
	AddBuilding<OfficeBuilding>(1);
	AddBuilding<ParkBuilding>(1);
	FillWithBuilding<LabBuilding>();
}

void ExhibitionZone::ArrangeBuilding() {
	AddBuilding<MuseumBuilding>(2);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<ParkBuilding>(1);
	FillWithBuilding<MuseumBuilding>();
}

void IndustryZone::ArrangeBuilding() {
	AddBuilding<FactoryBuilding>(2);
	AddBuilding<WarehouseBuilding>(1);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<ParkBuilding>(1);
	AddBuilding<FactoryBuilding>(2);
	AddBuilding<WarehouseBuilding>(1);
	FillWithBuilding<FactoryBuilding>();
}

void ResourceZone::ArrangeBuilding() {
	int type = GetRandom(9);
	switch (type) {
	case 0:
		AddBuilding<MiningBuilding>(1);
		break;
	case 1:
		AddBuilding<OilingBuilding>(1);
		break;
	case 2:
		AddBuilding<QuarryBuilding>(1);
		break;
	case 3:
		AddBuilding<FarmBuilding>(1);
		break;
	case 4:
		AddBuilding<PastureBuilding>(1);
		break;
	case 5:
		AddBuilding<BreedingBuilding>(1);
		break;
	case 6:
		AddBuilding<FishingBuilding>(1);
		break;
	case 7:
		AddBuilding<OrchardBuilding>(1);
		break;
	case 8:
		AddBuilding<ForestBuilding>(1);
		break;
	}
	AddBuilding<WarehouseBuilding>(1);
	AddBuilding<ParkingBuilding>(1);
	FillWithBuilding<ParkBuilding>();
}

void AmusementZone::ArrangeBuilding() {
	AddBuilding<AmusementBuilding>(4);
	AddBuilding<GuardBuilding>(1);
	AddBuilding<ParkingBuilding>(1);
	AddBuilding<ParkBuilding>(1);
	AddBuilding<StatueBuilding>(1);
	FillWithBuilding<AmusementBuilding>();
}

void TourismZone::ArrangeBuilding() {
	int type = GetRandom(2);
	switch (type) {
	case 0:
		AddBuilding<ResortBuilding>(1);
		break;
	case 1:
		AddBuilding<RemainsBuilding>(1);
		break;
	}
	AddBuilding<GuardBuilding>(1);
	AddBuilding<ParkingBuilding>(1);
	FillWithBuilding<ParkBuilding>();
}
