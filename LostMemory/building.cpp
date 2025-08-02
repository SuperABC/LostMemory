#pragma warning(disable:4244)
#pragma warning(disable:4267)

#include "building.h"
#include "util.h"


using namespace std;

BUILDING_TYPE Building::GetType() {
    return type;
}

void Building::SetType(BUILDING_TYPE type) {
    this->type = type;
}

CONSTRUCTION_TYPE Building::GetStatus() {
    return status;
}

AREA_TYPE Building::GetAreaType() {
    return area;
}

void Building::SetAreaType(AREA_TYPE type) {
    area = type;
}

ZONE_TYPE Building::GetZoneType() {
    return zone;
}

void Building::SetZoneType(ZONE_TYPE type) {
    zone = type;
}

Building* CreateBuilding(BUILDING_TYPE type) {
    switch (type) {
    case BUILDING_ROADFIX:
        return new RoadfixBuilding();
    case BUILDING_PARKING:
        return new ParkingBuilding();
    case BUILDING_BANK:
        return new BankBuilding();
    case BUILDING_LIBRARY:
        return new LibraryBuilding();
    case BUILDING_CLINIC:
        return new ClinicBuilding();
    case BUILDING_HOSPITAL:
        return new HospitalBuilding();
    case BUILDING_SANATORIUM:
        return new SanatoriumBuilding();
    case BUILDING_POLICE:
        return new PoliceBuilding();
    case BUILDING_FIRE:
        return new FireBuilding();
    case BUILDING_SCHOOL:
        return new SchoolBuilding();
    case BUILDING_CREMATORIUM:
        return new CrematoriumBuilding();
    case BUILDING_CEMETRY:
        return new CemetryBuilding();
    case BUILDING_TVSTATION:
        return new TVStationBuilding();
    case BUILDING_GASOLINE:
        return new GasolineBuilding();
    case BUILDING_TOILET:
        return new ToiletBuilding();
    case BUILDING_WATER:
        return new WaterBuilding();
    case BUILDING_SEWAGE:
        return new SewageBuilding();
    case BUILDING_SUBSTATION:
        return new SubstationBuilding();
    case BUILDING_POWER:
        return new PowerBuilding();
    case BUILDING_WINDMILL:
        return new WindmillBuilding();
    case BUILDING_NUCLEAR:
        return new NuclearBuilding();
    case BUILDING_RECYCLE:
        return new RecycleBuilding();
    case BUILDING_TRASH:
        return new TrashBuilding();
    case BUILDING_INCINERATION:
        return new IncinerationBuilding();
    case BUILDING_POST:
        return new PostBuilding();
    case BUILDING_METRO:
        return new MetroBuilding();
    case BUILDING_TRAIN:
        return new TrainBuilding();
    case BUILDING_PLANE:
        return new PlaneBuilding();
    case BUILDING_SHIP:
        return new ShipBuilding();
    case BUILDING_RESIDENT:
        return new ResidentBuilding();
    case BUILDING_VILLA:
        return new VillaBuilding();
    case BUILDING_ESTATE:
        return new EstateBuilding();
    case BUILDING_PROPERTY:
        return new PropertyBuilding();
    case BUILDING_PACKAGE:
        return new PackageBuilding();
    case BUILDING_HOTEL:
        return new HotelBuilding();
    case BUILDING_RESTAURANT:
        return new RestaurantBuilding();
    case BUILDING_MALL:
        return new MallBuilding();
    case BUILDING_MARKET:
        return new MarketBuilding();
    case BUILDING_MUSIC:
        return new MusicBuilding();
    case BUILDING_INGREDIENT:
        return new IngredientBuilding();
    case BUILDING_BRAND:
        return new BrandBuilding();
    case BUILDING_CARRENT:
        return new CarRentBuilding();
    case BUILDING_THEATER:
        return new TheaterBuilding();
    case BUILDING_MUSEUM:
        return new MuseumBuilding();
    case BUILDING_ZOO:
        return new ZooBuilding();
    case BUILDING_BOTANIC:
        return new BotanicBuilding();
    case BUILDING_AQUARIUM:
        return new AquariumBuilding();
    case BUILDING_CINEMA:
        return new CinemaBuilding();
    case BUILDING_PUB:
        return new PubBuilding();
    case BUILDING_MASAGE:
        return new MasageBuilding();
    case BUILDING_AMUSEMENT:
        return new AmusementBuilding();
    case BUILDING_OFFICE:
        return new OfficeBuilding();
    case BUILDING_STOCK:
        return new StockBuilding();
    case BUILDING_COURT:
        return new CourtBuilding();
    case BUILDING_GOVERNMENT:
        return new GovernmentBuilding();
    case BUILDING_LAB:
        return new LabBuilding();
    case BUILDING_FACTORY:
        return new FactoryBuilding();
    case BUILDING_WAREHOUSE:
        return new WarehouseBuilding();
    case BUILDING_REPAIR:
        return new RepairBuilding();
    case BUILDING_MINING:
        return new MiningBuilding();
    case BUILDING_OILING:
        return new OilingBuilding();
    case BUILDING_QUARRY:
        return new QuarryBuilding();
    case BUILDING_FARM:
        return new FarmBuilding();
    case BUILDING_PASTURE:
        return new PastureBuilding();
    case BUILDING_BREEDING:
        return new BreedingBuilding();
    case BUILDING_FISHING:
        return new FishingBuilding();
    case BUILDING_ORCHARD:
        return new OrchardBuilding();
    case BUILDING_FOREST:
        return new ForestBuilding();
    case BUILDING_PARK:
        return new ParkBuilding();
    case BUILDING_PLAZA:
        return new PlazaBuilding();
    case BUILDING_STATUE:
        return new StatueBuilding();
    case BUILDING_GYM:
        return new GymBuilding();
    case BUILDING_RESORT:
        return new ResortBuilding();
    case BUILDING_REMAINS:
        return new RemainsBuilding();
    case BUILDING_GUARD:
        return new GuardBuilding();
    case BUILDING_CANTEEN:
        return new CanteenBuilding();
    case BUILDING_DORMITRY:
        return new DormitryBuilding();
    default:
        return nullptr;;
    }
    return nullptr;
}

BUILDING_TYPE RandomBuilding(AREA_TYPE area, float prob) {
    switch (area) {
    case AREA_NONE:
        break;
    case AREA_ROAD:
        break;
    case AREA_CENTER:
        break;
    case AREA_RESIDENTH:
        if (prob < 0.8f)return BUILDING_RESIDENT;
        else if (prob < 0.82f)return BUILDING_ESTATE;
        else if (prob < 0.85f)return BUILDING_PROPERTY;
        else if (prob < 0.88f)return BUILDING_PACKAGE;
        else if (prob < 0.94f)return BUILDING_HOTEL;
        else return BUILDING_RESTAURANT;
    case AREA_RESIDENTM:
        if (prob < 0.5f)return BUILDING_RESIDENT;
        else if (prob < 0.75f)return BUILDING_VILLA;
        else if (prob < 0.78f)return BUILDING_ESTATE;
        else if (prob < 0.82f)return BUILDING_PROPERTY;
        else if (prob < 0.86f)return BUILDING_PACKAGE;
        else if (prob < 0.92f)return BUILDING_HOTEL;
        else return BUILDING_RESTAURANT;
    case AREA_RESIDENTL:
        if (prob < 0.2f)return BUILDING_RESIDENT;
        else if (prob < 0.85f)return BUILDING_VILLA;
        else if (prob < 0.86f)return BUILDING_ESTATE;
        else if (prob < 0.88f)return BUILDING_PROPERTY;
        else if (prob < 0.90f)return BUILDING_PACKAGE;
        else if (prob < 0.95f)return BUILDING_HOTEL;
        else return BUILDING_RESTAURANT;
    case AREA_COMMERCEH:
        if (prob < 0.5f)return BUILDING_MALL;
        else if (prob < 0.63f)return BUILDING_MARKET;
        else if (prob < 0.70f)return BUILDING_INGREDIENT;
        else if (prob < 0.80f)return BUILDING_BRAND;
        else if (prob < 0.84f)return BUILDING_CARRENT;
        else if (prob < 0.87f)return BUILDING_THEATER;
        else if (prob < 0.90f)return BUILDING_MUSEUM;
        else if (prob < 0.94f)return BUILDING_CINEMA;
        else if (prob < 0.96f)return BUILDING_MUSIC;
        else if (prob < 0.98f)return BUILDING_PUB;
        else if (prob < 0.99f)return BUILDING_MASAGE;
        else return BUILDING_AMUSEMENT;
    case AREA_COMMERCEL:
        if (prob < 0.2f)return BUILDING_MALL;
        else if (prob < 0.30f)return BUILDING_MARKET;
        else if (prob < 0.38f)return BUILDING_INGREDIENT;
        else if (prob < 0.48f)return BUILDING_BRAND;
        else if (prob < 0.50f)return BUILDING_CARRENT;
        else if (prob < 0.53f)return BUILDING_THEATER;
        else if (prob < 0.55f)return BUILDING_MUSEUM;
        else if (prob < 0.65f)return BUILDING_CINEMA;
        else if (prob < 0.70f)return BUILDING_MUSIC;
        else if (prob < 0.78f)return BUILDING_PUB;
        else if (prob < 0.81f)return BUILDING_MASAGE;
        else if (prob < 0.84f)return BUILDING_ZOO;
        else if (prob < 0.87f)return BUILDING_BOTANIC;
        else if (prob < 0.90f)return BUILDING_AQUARIUM;
        else return BUILDING_AMUSEMENT;
    case AREA_OFFICEH:
        if (prob < 0.8f)return BUILDING_OFFICE;
        else if (prob < 0.82f)return BUILDING_STOCK;
        else if (prob < 0.84f)return BUILDING_COURT;
        else if (prob < 0.90f)return BUILDING_GOVERNMENT;
        else return BUILDING_LAB;
    case AREA_OFFICEL:
        if (prob < 0.9f)return BUILDING_OFFICE;
        else return BUILDING_LAB;
    case AREA_INDUSTRY:
        if (prob < 0.3f)return BUILDING_FACTORY;
        else if (prob < 0.43f)return BUILDING_WAREHOUSE;
        else if (prob < 0.45f)return BUILDING_REPAIR;
        else if (prob < 0.55f)return BUILDING_MINING;
        else if (prob < 0.65f)return BUILDING_OILING;
        else if (prob < 0.70f)return BUILDING_QUARRY;
        else if (prob < 0.78f)return BUILDING_FARM;
        else if (prob < 0.85f)return BUILDING_PASTURE;
        else if (prob < 0.89f)return BUILDING_BREEDING;
        else if (prob < 0.92f)return BUILDING_ORCHARD;
        else return BUILDING_FOREST;
    case AREA_GREEN:
        if (prob < 0.6f)return BUILDING_PARK;
        else if (prob < 0.80f)return BUILDING_PLAZA;
        else if (prob < 0.85f)return BUILDING_STATUE;
        else if (prob < 0.95f)return BUILDING_GYM;
        else if (prob < 0.98f)return BUILDING_RESORT;
        else return BUILDING_REMAINS;
    default:
        break;
    }
    return BUILDING_NONE;
}

void RoadfixBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1 + GetRandom(2);
    basement = 1 + GetRandom(2);
}

void RoadfixBuilding::DistributeInside() {
    //Parking
    //Guard
    //Clean
    //Toilet
    //Warehouse
    //Office

    vector<int> acreages(layers, GetAcreage() * 0.16);

    auto roadfix = CreateOrganization<RoadfixOrganization>();

    roadfix->AddRoom(CreateRoom<ParkingRoom>(0, GetAcreage() * 0.48));

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            roadfix->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    if (zone == ZONE_NONE) {
        roadfix->AddRoom(CreateRoom<GuardRoom>(1, 40));
        acreages[0] -= 40;
    }
    roadfix->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    for (int layer = 0; layer < layers; layer++) {
        roadfix->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 40));
        acreages[layer] -= 40;
    }
    for (int i = 0; i < acreages[0] / 200; i++) {
        roadfix->AddRoom(CreateRoom<OfficeRoom>(1, 40));
        roadfix->AddRoom(CreateRoom<WarehouseRoom>(1, 160));
    }
    for (int layer = 1; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 80; i++) {
            roadfix->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
        }
    }
}

void RoadfixBuilding::ArrangeLayout() {

}

void ParkingBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void ParkingBuilding::DistributeInside() {
    //Parking
    //Guard

    vector<int> acreages(layers, GetAcreage() * 0.64);

    auto parking = CreateOrganization<ParkingOrganization>();

    if (layers == 1) {
        parking->AddRoom(CreateRoom<ParkingRoom>(0, GetAcreage() * 0.64));
    }

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            parking->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    if (zone == ZONE_NONE) {
        parking->AddRoom(CreateRoom<GuardRoom>(1, 40));
    }
    if (layers > 1) {
        for (int layer = 0; layer < layers; layer++) {
            parking->AddRoom(CreateRoom<ParkingRoom>(layer + 1, acreages[layer]));
        }
    }
}

void ParkingBuilding::ArrangeLayout() {

}

void BankBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 3 + GetRandom(3);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = GetRandom(2);
}

void BankBuilding::DistributeInside() {
    //Guard
    //Clean
    //Toilet
    //Office
    //Reception
    //Gold
    //Warehouse

    vector<int> acreages(layers, GetAcreage() * 0.64);

    auto bank = CreateOrganization<BankOrganization>();

    if (basement > 0) {
        for (int i = 0; i < basement; i++) {
            if (GetRandom(10) == 0) {
                bank->AddRoom(CreateRoom<GoldRoom>(-i, GetAcreage() * 0.16));
            }
            else {
                bank->AddRoom(CreateRoom<WarehouseRoom>(-i - 1, GetAcreage() * 0.16));
            }
        }
    }

    if (zone == ZONE_NONE) {
        bank->AddRoom(CreateRoom<GuardRoom>(1, 40));
        acreages[0] -= 40;
    }
    bank->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    for (int layer = 0; layer < layers; layer++) {
        bank->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
    }
    if (acreages[0] > 200) {
        bank->AddRoom(CreateRoom<ReceptionRoom>(1, 200));
    }
    else {
        bank->AddRoom(CreateRoom<ReceptionRoom>(1, acreages[0]));
    }
    for (int layer = 1; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 80; i++) {
            bank->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
        }
    }
}

void BankBuilding::ArrangeLayout() {

}

void LibraryBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 3 + GetRandom(3);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = GetRandom(2);
}

void LibraryBuilding::DistributeInside() {
    //Parking
    //Guard
    //Clean
    //Toilet
    //Warehouse
    //Office
    //Reception
    //Reading

    vector<int> acreages(layers, GetAcreage() * 0.64);

    auto library = CreateOrganization<LibraryOrganization>();

    if (zone == ZONE_NONE) {
        if (basement > 0) {
            library->AddRoom(CreateRoom<WarehouseRoom>(-1, GetAcreage() * 0.16));
            library->AddRoom(CreateRoom<ParkingRoom>(-1, GetAcreage() * 0.48));
        }
        if (basement > 1) {
            for (int i = 1; i < basement; i++)
                library->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
        }
    }
    else {
        basement = 1;
        library->AddRoom(CreateRoom<WarehouseRoom>(-1, GetAcreage() * 0.16));
    }

    if (zone == ZONE_NONE) {
        library->AddRoom(CreateRoom<GuardRoom>(1, 40));
        acreages[0] -= 40;
    }
    library->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    for (int layer = 0; layer < layers; layer++) {
        library->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
    }
    library->AddRoom(CreateRoom<ReceptionRoom>(1, 120));
    acreages[0] -= 120;
    library->AddRoom(CreateRoom<OfficeRoom>(1, 80));
    acreages[0] -= 80;
    for (int layer = 0; layer < layers; layer++) {
        int n = 2 + GetRandom(3);
        for (int i = 0; i < n; i++) {
            library->AddRoom(CreateRoom<ReadingRoom>(layer + 1, acreages[layer] / n));
        }
    }
}

void LibraryBuilding::ArrangeLayout() {

}

void ClinicBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 3 + GetRandom(2);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = GetRandom(2);
}

void ClinicBuilding::DistributeInside() {
    //Parking
    //Toilet
    //Office
    //Doctor
    //Reception

    vector<int> acreages(layers, GetAcreage() * 0.64);

    auto clinic = CreateOrganization<ClinicOrganization>();

    if (zone == ZONE_NONE) {
        if (basement > 0) {
            for (int i = 0; i < basement; i++)
                clinic->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
        }
    }

    for (int layer = 0; layer < layers; layer++) {
        clinic->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 40));
        acreages[layer] -= 40;
    }
    clinic->AddRoom(CreateRoom<ReceptionRoom>(1, 80));
    acreages[0] -= 80;
    for (int i = 0; i < acreages[0] / 200; i++) {
        clinic->AddRoom(CreateRoom<OfficeRoom>(1, 40));
        clinic->AddRoom(CreateRoom<DoctorRoom>(1, 80));
        clinic->AddRoom(CreateRoom<DoctorRoom>(1, 80));
    }
    for (int layer = 1; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 120; i++) {
            clinic->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 40));
            clinic->AddRoom(CreateRoom<DoctorRoom>(layer + 1, 80));
        }
    }
}

void ClinicBuilding::ArrangeLayout() {

}

void HospitalBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area < AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 6 + GetRandom(10);
    }
    else if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 4 + GetRandom(2);
    }
    else {
        layers = 2 + GetRandom(2);
    }
    basement = 1 + GetRandom(3);
}

void HospitalBuilding::DistributeInside() {
    //Parking
    //Toilet
    //Office
    //Doctor
    //Reception
    //Warehouse
    //Outpatient
    //Emergency
    //ICU
    //Operation

    vector<int> acreages(layers, GetAcreage() * 0.64);

    auto hospital = CreateOrganization<HospitalOrganization>();

    if (zone == ZONE_NONE) {
        if (basement > 0) {
            for (int i = 0; i < basement - 1; i++)
                hospital->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
            hospital->AddRoom(CreateRoom<WarehouseRoom>(-basement, GetAcreage() * 0.16));
        }
    }
    else {
        basement = 1;
        hospital->AddRoom(CreateRoom<WarehouseRoom>(-basement, GetAcreage() * 0.16));
    }

    if (zone == ZONE_NONE) {
        hospital->AddRoom(CreateRoom<GuardRoom>(1, 40));
        acreages[0] -= 40;
    }
    hospital->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    for (int layer = 0; layer < layers; layer++) {
        hospital->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 80));
        acreages[0] -= 80;
    }
    hospital->AddRoom(CreateRoom<ReceptionRoom>(1, 120));
    acreages[0] -= 120;
    for (int layer = 0; layer < 1; layer++) {
        for (int i = 0; i < acreages[layer] / 200; i++) {
            hospital->AddRoom(CreateRoom<OutpatientRoom>(layer + 1, 40));
            hospital->AddRoom(CreateRoom<OutpatientRoom>(layer + 1, 40));
            hospital->AddRoom(CreateRoom<EmergencyRoom>(layer + 1, 120));
        }
    }
    for (int layer = 2; layer < layers - 2; layer++) {
        for (int i = 0; i < acreages[layer] / 240; i++) {
            hospital->AddRoom(CreateRoom<ICURoom>(layer + 1, 120));
            hospital->AddRoom(CreateRoom<OperationRoom>(layer + 1, 120));
        }
    }
    for (int layer = max(2, layers - 2); layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 120; i++) {
            hospital->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
            hospital->AddRoom(CreateRoom<DoctorRoom>(layer + 1, 40));
        }
    }
}

void HospitalBuilding::ArrangeLayout() {

}

void InpatientBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 8 + GetRandom(3) * 2;
    }
    else {
        layers = 5 + GetRandom(4);
    }
    basement = 1;
}

void InpatientBuilding::DistributeInside() {
    //Parking
    //Warehouse
    //Toilet
    //Office
    //Doctor
    //Reception
    //Bunk

    vector<int> acreages(layers, GetAcreage() * 0.64);

    auto inpatient = CreateOrganization<InpatientOrganization>();

    if (zone == ZONE_NONE) {
        if (basement > 0) {
            inpatient->AddRoom(CreateRoom<WarehouseRoom>(-1, GetAcreage() * 0.64));
            for (int i = 1; i < basement; i++)
                inpatient->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
        }
    }
    else {
        basement = 1;
        inpatient->AddRoom(CreateRoom<WarehouseRoom>(-basement, GetAcreage() * 0.64));
    }

    if (zone == ZONE_NONE) {
        inpatient->AddRoom(CreateRoom<GuardRoom>(1, 40));
        acreages[0] -= 40;
    }
    inpatient->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    for (int layer = 0; layer < layers; layer++) {
        inpatient->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 80));
        acreages[layer] -= 80;
        inpatient->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 40));
        acreages[layer] -= 40;
        inpatient->AddRoom(CreateRoom<DoctorRoom>(layer + 1, 40));
        acreages[layer] -= 40;
    }
    inpatient->AddRoom(CreateRoom<ReceptionRoom>(1, 80));
    acreages[0] -= 80;
    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 80; i++) {
            inpatient->AddRoom(CreateRoom<BunkRoom>(layer + 1, 80));
        }
    }
}

void InpatientBuilding::ArrangeLayout() {

}

void SanatoriumBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 4 + GetRandom(2);
    }
    else {
        layers = 2 + GetRandom(2);
    }
    basement = 0;
}

void SanatoriumBuilding::DistributeInside() {
    //Parking
    //Warehouse
    //Toilet
    //Office
    //Doctor
    //Reception
    //Bunk

    vector<int> acreages(layers, GetAcreage() * 0.64);

    auto sanatorium = CreateOrganization<SanatoriumOrganization>();

    if (zone == ZONE_NONE) {
        if (basement > 0) {
            sanatorium->AddRoom(CreateRoom<WarehouseRoom>(-1, GetAcreage() * 0.64));
            for (int i = 1; i < basement; i++)
                sanatorium->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
        }
    }
    else {
        basement = 1;
        sanatorium->AddRoom(CreateRoom<WarehouseRoom>(-basement, GetAcreage() * 0.64));
    }

    for (int layer = 0; layer < layers; layer++) {
        sanatorium->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 80));
        acreages[layer] -= 80;
        sanatorium->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 40));
        acreages[layer] -= 40;
        sanatorium->AddRoom(CreateRoom<DoctorRoom>(layer + 1, 40));
        acreages[layer] -= 40;
        sanatorium->AddRoom(CreateRoom<DoctorRoom>(layer + 1, 40));
        acreages[layer] -= 40;
    }
    sanatorium->AddRoom(CreateRoom<ReceptionRoom>(1, 80));
    acreages[0] -= 80;
    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 80; i++) {
            sanatorium->AddRoom(CreateRoom<BunkRoom>(layer + 1, 80));
        }
    }
}

void SanatoriumBuilding::ArrangeLayout() {

}

void PoliceBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 3 + GetRandom(2);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = 1 + GetRandom(3);
}

void PoliceBuilding::DistributeInside() {
    //Parking
    //Guard
    //Clean
    //Toilet
    //Warehouse
    //Office
    //Reception

    vector<int> acreages(layers, GetAcreage() * 0.16);

    auto police = CreateOrganization<PoliceOrganization>();

    police->AddRoom(CreateRoom<ParkingRoom>(0, GetAcreage() * 0.48));

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            police->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    police->AddRoom(CreateRoom<GuardRoom>(1, 40));
    acreages[0] -= 40;
    police->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    for (int layer = 0; layer < layers; layer++) {
        police->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
    }
    police->AddRoom(CreateRoom<ReceptionRoom>(1, 60));
    acreages[0] -= 60;
    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 80; i++) {
            police->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
        }
    }
}

void PoliceBuilding::ArrangeLayout() {

}

void FireBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 4 + GetRandom(2);
    }
    else {
        layers = 2 + GetRandom(2);
    }
    basement = 1 + GetRandom(2);
}

void FireBuilding::DistributeInside() {
    //Parking
    //Guard
    //Clean
    //Toilet
    //Warehouse
    //Office
    //Reception

    vector<int> acreages(layers, GetAcreage() * 0.16);

    auto fire = CreateOrganization<FireOrganization>();

    fire->AddRoom(CreateRoom<ParkingRoom>(0, GetAcreage() * 0.48));

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            fire->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    fire->AddRoom(CreateRoom<GuardRoom>(1, 40));
    acreages[0] -= 40;
    fire->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    for (int layer = 0; layer < layers; layer++) {
        fire->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
    }
    fire->AddRoom(CreateRoom<ReceptionRoom>(1, 60));
    acreages[0] -= 60;
    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 80; i++) {
            fire->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
        }
    }
}

void FireBuilding::ArrangeLayout() {

}

void SchoolBuilding::InitBuilding() {
    if (GetRandom(8) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area < AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 6 + GetRandom(10);
    }
    else if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 4 + GetRandom(2);
    }
    else {
        layers = 2 + GetRandom(2);
    }
    basement = 0;
}

void SchoolBuilding::DistributeInside() {
    //Guard
    //Clean
    //Toilet
    //Class
    //Office
    //Meeting
    //Grocery
    //Computer
    //Review
    //Playground

    vector<int> acreages;
    if (zone == ZONE_NONE) {
        acreages = vector<int>(layers, GetAcreage() * 0.16);
    }
    else {
        acreages = vector<int>(layers, GetAcreage() * 0.64);
    }

    Organization* school;
    if (zone == ZONE_NONE) {
        if (GetRandom(2) == 0)
            school = CreateOrganization<PrimaryOrganization>();
        else if (GetRandom(2) == 0)
            school = CreateOrganization<MiddleOrganization>();
        else
            school = CreateOrganization<VocationalOrganization>();
    }
    else {
        school = CreateOrganization<UniversityOrganization>();
    }

    if (zone == ZONE_NONE) {
        school->AddRoom(CreateRoom<PlaygroundRoom>(0, GetAcreage() * 0.48));
        school->AddRoom(CreateRoom<GuardRoom>(1, 40));
        acreages[0] -= 40;
    }
    school->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    for (int layer = 0; layer < layers; layer++) {
        school->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
        school->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
        acreages[layer] -= 80;
        school->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
        acreages[layer] -= 80;
    }
    school->AddRoom(CreateRoom<ComputerRoom>(layers - 1, 120));
    acreages[0] -= 120;
    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 120; i++) {
            school->AddRoom(CreateRoom<ClassRoom>(layer + 1, 120));
        }
    }
}

void SchoolBuilding::ArrangeLayout() {

}

void CrematoriumBuilding::InitBuilding() {
    if (GetRandom(8) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1 + GetRandom(2);
    basement = 1;
}

void CrematoriumBuilding::DistributeInside() {
    //Reception
    //Clean
    //Parking
    //Office
    //Condolence
    //Funeral
    //Boiler

    vector<int> acreages(layers, GetAcreage() * 0.64);

    auto crematorium = CreateOrganization<CrematoriumOrganization>();

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            crematorium->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    crematorium->AddRoom(CreateRoom<ReceptionRoom>(1, 80));
    acreages[0] -= 80;
    crematorium->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    crematorium->AddRoom(CreateRoom<CondolenceRoom>(1, 240));
    acreages[0] -= 240;
    crematorium->AddRoom(CreateRoom<FuneralRoom>(1, 160));
    acreages[0] -= 160;
    crematorium->AddRoom(CreateRoom<FuneralRoom>(1, 160));
    acreages[0] -= 160;
    crematorium->AddRoom(CreateRoom<BoilerRoom>(1, 240));
    acreages[0] -= 240;
    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 120; i++) {
            crematorium->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 120));
        }
    }
}

void CrematoriumBuilding::ArrangeLayout() {

}

void CemetryBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void CemetryBuilding::DistributeInside() {
    //Funeral
    //Parking

    auto cemetry = CreateOrganization<CemetryOrganization>();

    cemetry->AddRoom(CreateRoom<ParkingRoom>(0, GetAcreage() * 0.16));
    cemetry->AddRoom(CreateRoom<FuneralRoom>(0, GetAcreage() * 0.48));
}

void CemetryBuilding::ArrangeLayout() {

}

void TVStationBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area < AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 16 + GetRandom(6) * 10;
    }
    else if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 6 + GetRandom(10);
    }
    else {
        layers = 4 + GetRandom(2);
    }
    basement = 1 + GetRandom(2);
}

void TVStationBuilding::DistributeInside() {
    //Parking
    //Guard
    //Clean
    //Toilet
    //Warehouse
    //Office
    //Studio
    //Stage

    vector<int> acreages(layers, GetAcreage() * 0.36);

    auto tv = CreateOrganization<TVStationOrganization>();

    tv->AddRoom(CreateRoom<ParkingRoom>(0, GetAcreage() * 0.28));

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            tv->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    tv->AddRoom(CreateRoom<GuardRoom>(1, 40));
    acreages[0] -= 40;
    tv->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    for (int layer = 0; layer < layers; layer++) {
        tv->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
        tv->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
        acreages[layer] -= 80;
        tv->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
        acreages[layer] -= 80;
        tv->AddRoom(CreateRoom<StageRoom>(layer + 1, 400));
        acreages[layer] -= 400;
    }
    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 200; i++) {
            tv->AddRoom(CreateRoom<StudioRoom>(layer + 1, 200));
        }
    }
}

void TVStationBuilding::ArrangeLayout() {

}

void GasolineBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void GasolineBuilding::DistributeInside() {
    //Gasoline
    //Market

    auto gasoline = CreateOrganization<GasolineOrganization>();

    gasoline->AddRoom(CreateRoom<GasolineRoom>(0, GetAcreage() * 0.36));
    gasoline->AddRoom(CreateRoom<MarketRoom>(0, GetAcreage() * 0.28));
}

void GasolineBuilding::ArrangeLayout() {

}

void ToiletBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void ToiletBuilding::DistributeInside() {
    //Toilet

    auto toilet = CreateOrganization<ToiletOrganization>();

    toilet->AddRoom(CreateRoom<ToiletRoom>(0, GetAcreage() * 0.64));
}

void ToiletBuilding::ArrangeLayout() {

}

void SubstationBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void SubstationBuilding::DistributeInside() {
    //Device

    auto substation = CreateOrganization<DeviceOrganization>();

    substation->AddRoom(CreateRoom<DeviceRoom>(0, GetAcreage() * 0.64));
}

void SubstationBuilding::ArrangeLayout() {

}

void PostBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 2 + GetRandom(2);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = 0;
}

void PostBuilding::DistributeInside() {
    //Parking
    //Reception
    //Guard
    //Clean
    //Warehouse
    //Toilet
    //Office

    vector<int> acreages(layers, GetAcreage() * 0.64);

    auto post = CreateOrganization<PostOrganization>();

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            post->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    post->AddRoom(CreateRoom<ReceptionRoom>(1, 200));
    acreages[0] -= 200;
    post->AddRoom(CreateRoom<GuardRoom>(1, 40));
    acreages[0] -= 40;
    post->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    post->AddRoom(CreateRoom<WarehouseRoom>(1, 200));
    acreages[0] -= 200;
    for (int layer = 0; layer < layers; layer++) {
        post->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
    }
    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 80; i++) {
            post->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
        }
    }
}

void PostBuilding::ArrangeLayout() {

}

void MetroBuilding::InitBuilding() {

}

void MetroBuilding::DistributeInside() {

}

void MetroBuilding::ArrangeLayout() {

}

void TrainBuilding::InitBuilding() {

}

void TrainBuilding::DistributeInside() {

}

void TrainBuilding::ArrangeLayout() {

}

void PlaneBuilding::InitBuilding() {

}

void PlaneBuilding::DistributeInside() {

}

void PlaneBuilding::ArrangeLayout() {

}

void ShipBuilding::InitBuilding() {

}

void ShipBuilding::DistributeInside() {

}

void ShipBuilding::ArrangeLayout() {

}

void ResidentBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else if (GetRandom(20) == 0) {
        status = CONSTRUCTION_BREAK;
    }
    else if (GetRandom(8) == 0) {
        status = CONSTRUCTION_WORKING;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area < AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 16 + GetRandom(5) * 5;
    }
    else if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 7 + GetRandom(10);
    }
    else {
        layers = 3 + GetRandom(5);
    }
    basement = 1 + GetRandom(2);
}

void ResidentBuilding::DistributeInside() {
    //Parking
    //Home

    vector<int> acreages(layers, GetAcreage() * 0.64);

    auto property = CreateOrganization<CommunityOrganization>();

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            property->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    int standard;
    switch (GetRandom(10))
    {
    case 0:
        standard = 400;
        break;
    case 1:
    case 2:
        standard = 320;
        break;
    case 3:
    case 4:
    case 5:
        standard = 200;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    default:
        standard = 120;
        break;
    }

    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / standard; i++) {
            property->AddRoom(CreateRoom<HomeRoom>(layer + 1, standard));
        }
    }
}

void ResidentBuilding::ArrangeLayout() {

}

void VillaBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else if (GetRandom(8) == 0) {
        status = CONSTRUCTION_WORKING;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 3 + GetRandom(2);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = GetRandom(2);
}

void VillaBuilding::DistributeInside() {
    //Parking
    //Home

    vector<int> acreages(layers, GetAcreage() * 0.36);

    auto property = CreateOrganization<CommunityOrganization>();

    if (basement > 0) {
        for (int i = 0; i < basement; i++) {
            property->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.16));
            property->AddRoom(CreateRoom<WarehouseRoom>(-i - 1, GetAcreage() * 0.20));
        }
    }

    property->AddRoom(CreateRoom<ParkingRoom>(0, 80));

    int standard;
    switch (GetRandom(6))
    {
    case 0:
        standard = 640;
        break;
    case 1:
    case 2:
        standard = 400;
        break;
    case 3:
    case 4:
    case 5:
    default:
        standard = 240;
        break;
    }

    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / standard; i++) {
            property->AddRoom(CreateRoom<VillaRoom>(layer + 1, standard));
        }
    }
}

void VillaBuilding::ArrangeLayout() {

}

void EstateBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1 + GetRandom(2);
    basement = 0;
}

void EstateBuilding::DistributeInside() {
    //Parking
    //Reception
    //Clean
    //Home
    //Office

    vector<int> acreages(layers, GetAcreage() * 0.64);

    auto estate = CreateOrganization<EstateOrganization>();

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            estate->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    estate->AddRoom(CreateRoom<ReceptionRoom>(1, 200));
    acreages[0] -= 200;
    estate->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    estate->AddRoom(CreateRoom<HomeRoom>(1, 200));
    acreages[0] -= 200;
    estate->AddRoom(CreateRoom<HomeRoom>(1, 320));
    acreages[0] -= 320;
    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 80; i++) {
            estate->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
        }
    }
}

void EstateBuilding::ArrangeLayout() {

}

void PropertyBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1 + GetRandom(4);
    basement = 0;
}

void PropertyBuilding::DistributeInside() {
    //Parking
    //Reception
    //Clean
    //Toilet
    //Office

    vector<int> acreages(layers, GetAcreage() * 0.64);

    auto property = CreateOrganization<PropertyOrganization>();

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            property->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    property->AddRoom(CreateRoom<ReceptionRoom>(1, 200));
    acreages[0] -= 200;
    property->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    property->AddRoom(CreateRoom<CleanRoom>(1, 40));
    acreages[0] -= 40;
    for (int layer = 0; layer < layers; layer++) {
        property->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
    }
    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 80; i++) {
            property->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
        }
    }
}

void PropertyBuilding::ArrangeLayout() {

}

void PackageBuilding::InitBuilding() {
    if (GetRandom(8) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1 + GetRandom(2);
    basement = 0;
}

void PackageBuilding::DistributeInside() {
    //Parking
    //Reception
    //Office

    vector<int> acreages(layers, GetAcreage() * 0.36);

    auto package = CreateOrganization<PackageOrganization>();

    package->AddRoom(CreateRoom<ParkingRoom>(1, GetAcreage() * 0.28));

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            package->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    package->AddRoom(CreateRoom<ReceptionRoom>(1, 40));
    acreages[0] -= 40;
    package->AddRoom(CreateRoom<WarehouseRoom>(1, acreages[0]));
    for (int layer = 1; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 80; i++) {
            package->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 80));
        }
    }
}

void PackageBuilding::ArrangeLayout() {

}

void HotelBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else if (GetRandom(20) == 0) {
        status = CONSTRUCTION_BREAK;
    }
    else if (GetRandom(8) == 0) {
        status = CONSTRUCTION_WORKING;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area < AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 16 + GetRandom(5) * 5;
    }
    else if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 7 + GetRandom(10);
    }
    else {
        layers = 3 + GetRandom(5);
    }
    basement = GetRandom(2);
}

void HotelBuilding::DistributeInside() {
    //Parking
    //Guard
    //Reception
    //Toilet
    //Kitchen
    //Canteen
    //Warehouse
    //Clean
    //Bunk
    //Office
    //Meeting

    vector<int> acreages;
    if (zone == ZONE_NONE) {
        acreages = vector<int>(layers, GetAcreage() * 0.36);
    }
    else {
        acreages = vector<int>(layers, GetAcreage() * 0.64);
    }

    auto hotel = CreateOrganization<HotelOrganization>();

    if (zone == ZONE_NONE) {
        hotel->AddRoom(CreateRoom<ParkingRoom>(0, GetAcreage() * 0.28));
    }

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            hotel->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    hotel->AddRoom(CreateRoom<GuardRoom>(1, 40));
    acreages[0] -= 40;
    hotel->AddRoom(CreateRoom<ReceptionRoom>(1, 200));
    acreages[0] -= 200;
    hotel->AddRoom(CreateRoom<ToiletRoom>(1, 60));
    acreages[0] -= 60;
    hotel->AddRoom(CreateRoom<KitchenRoom>(1, 120));
    acreages[0] -= 120;
    hotel->AddRoom(CreateRoom<CanteenRoom>(1, 200));
    acreages[0] -= 200;
    hotel->AddRoom(CreateRoom<OfficeRoom>(1, 120));
    acreages[0] -= 120;
    if (GetAcreage() > 4000) {
        hotel->AddRoom(CreateRoom<MeetingRoom>(1, 400));
        acreages[0] -= 400;
    }
    hotel->AddRoom(CreateRoom<WarehouseRoom>(1, acreages[0]));
    for (int layer = 1; layer < layers; layer++) {
        hotel->AddRoom(CreateRoom<CleanRoom>(layer + 1, 60));
        acreages[layer] -= 60;
    }
    for (int layer = 1; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 80; i++) {
            hotel->AddRoom(CreateRoom<BunkRoom>(layer + 1, 80));
        }
    }
}

void HotelBuilding::ArrangeLayout() {

}

void RestaurantBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area < AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 6 + GetRandom(5);
    }
    else if (area <= AREA_RESIDENTM && GetAcreage() > 4000) {
        layers = 3 + GetRandom(4);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = GetRandom(2);
}

void RestaurantBuilding::DistributeInside() {
    //Parking
    //Toilet
    //Kitchen
    //PublicEat
    //PrivateEat

    vector<int> acreages;
    if (zone == ZONE_NONE) {
        acreages = vector<int>(layers, GetAcreage() * 0.36);
    }
    else {
        acreages = vector<int>(layers, GetAcreage() * 0.64);
    }

    auto restaurant = CreateOrganization<RestaurantOrganization>();

    if (zone == ZONE_NONE) {
        restaurant->AddRoom(CreateRoom<ParkingRoom>(0, GetAcreage() * 0.28));
    }

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            restaurant->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * 0.64));
    }

    for (int layer = 0; layer < layers; layer++) {
        restaurant->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
    }
    restaurant->AddRoom(CreateRoom<KitchenRoom>(1, acreages[0] / 2));
    if (GetAcreage() > 4000 && layers > 1) {
        restaurant->AddRoom(CreateRoom<PublicEatRoom>(1, acreages[0] / 2));
        restaurant->AddRoom(CreateRoom<MeetingRoom>(2, 400));
        acreages[1] -= 400;
    }
    else {
        restaurant->AddRoom(CreateRoom<PublicEatRoom>(1, acreages[0] / 3));
        for (int i = 0; i < acreages[0] / 6 / 40; i++) {
            restaurant->AddRoom(CreateRoom<PrivateEatRoom>(1, 40));
        }
    }
    for (int layer = 1; layer < layers; layer++) {
        for (int i = 0; i < acreages[layer] / 40; i++) {
            restaurant->AddRoom(CreateRoom<PrivateEatRoom>(layer + 1, 40));
        }
    }
}

void RestaurantBuilding::ArrangeLayout() {

}

void MallBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else if (GetRandom(8) == 0) {
        status = CONSTRUCTION_WORKING;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 20000) {
        layers = 4 + GetRandom(3);
    }
    else {
        layers = 2 + GetRandom(2);
    }
    basement = 1 + GetRandom(2);
}

void MallBuilding::DistributeInside() {
    vector<Organization*> organizations;

    static vector<pair<ORGANIZATION_TYPE, float>> probs = {
        {ORGANIZATION_BRAND, 0.0},
        {ORGANIZATION_CLOTHES, 0.2},
        {ORGANIZATION_RESTAURANT, 0.4},
        {ORGANIZATION_FASTFOOD, 0.55},
        {ORGANIZATION_BUFFET, 0.63},
        {ORGANIZATION_COFFEE, 0.68},
        {ORGANIZATION_DRINK, 0.70},
        {ORGANIZATION_CINEMA, 0.76},
        {ORGANIZATION_MARKET, 0.77},
        {ORGANIZATION_CARRENT, 0.78},
        {ORGANIZATION_MUSIC, 0.79},
        {ORGANIZATION_COSMETIC, 0.81},
        {ORGANIZATION_HAIRCUT, 0.83},
        {ORGANIZATION_SMOKEWINETEA, 0.85},
        {ORGANIZATION_CHESSCARD, 0.86},
        {ORGANIZATION_PET, 0.87},
        {ORGANIZATION_ELECTRONIC, 0.89},
        {ORGANIZATION_STUDIO, 0.94},
        {ORGANIZATION_BOOK, 0.95},
        {ORGANIZATION_BILLIARD, 0.97},
        {ORGANIZATION_NET, 0.98},
        {ORGANIZATION_KTV, 0.99},
    };

    vector<int> acreages;
    if (zone == ZONE_NONE) {
        acreages = vector<int>(layers, GetAcreage() * 0.36);
    }
    else {
        acreages = vector<int>(layers, GetAcreage() * 0.64);
    }

    auto mall = CreateOrganization<MallOrganization>();

    for (int layer = 0; layer < layers; layer++) {
        mall->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
    }

    int layer = 0;
    while (acreages[layer] > 0) {
        float p = GetRandom(1000) / 1000.0f;
        ORGANIZATION_TYPE organizationType = ORGANIZATION_NONE;
        for (int i = 0; i < probs.size(); i++) {
            if (p >= probs[i].second) {
                organizationType = probs[i].first;
                break;
            }
        }
        auto organization = ::CreateOrganization(organizationType);
        if (organization) {
            acreages[layer] -= organization->AutoRoom(acreages[layer]);
        }
        if (acreages[layer] <= 0) {
            layer++;
        }
        if (layer >= layers)break;
    }
}

void MallBuilding::ArrangeLayout() {

}

void MarketBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 2 + GetRandom(2);
    }
    else {
        layers = 1;
    }
    basement = GetRandom(2);
}

void MarketBuilding::DistributeInside() {
    //Parking
    //Warehouse
    //Reception
    //Toilet
    //Office
    //Market
    
    vector<int> acreages;
    if (zone == ZONE_NONE) {
        acreages = vector<int>(layers, GetAcreage() * 0.36);
    }
    else {
        acreages = vector<int>(layers, GetAcreage() * 0.64);
    }

    auto market = CreateOrganization<MarketOrganization>();

    if (zone == ZONE_NONE) {
        market->AddRoom(CreateRoom<ParkingRoom>(0, GetAcreage() * 0.28));
        if (basement > 0) {
            for (int i = 0; i < basement; i++) {
                market->AddRoom(CreateRoom<WarehouseRoom>(-i - 1, GetAcreage() * 0.64));
            }
        }
    }
    else {
        if (basement > 0) {
            market->AddRoom(CreateRoom<ParkingRoom>(-1, GetAcreage() * 0.32));
            market->AddRoom(CreateRoom<WarehouseRoom>(-1, GetAcreage() * 0.32));
            for (int i = 1; i < basement; i++) {
                market->AddRoom(CreateRoom<WarehouseRoom>(-i - 1, GetAcreage() * 0.64));
            }
        }
    }

    market->AddRoom(CreateRoom<ReceptionRoom>(1, 120));
    acreages[0] -= 120;
    for (int layer = 0; layer < layers; layer++) {
        market->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
        market->AddRoom(CreateRoom<OfficeRoom>(1, 80));
        acreages[layer] -= 80;
    }

    for (int layer = 0; layer < layers; layer++) {
        market->AddRoom(CreateRoom<MarketRoom>(1, acreages[0]));
    }
}

void MarketBuilding::ArrangeLayout() {

}

void MusicBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1 + GetRandom(2);
    basement = 0;
}

void MusicBuilding::DistributeInside() {
    //Warehouse
    //Reception
    //Toilet
    //Music
    //Class

    vector<int> acreages = vector<int>(layers, GetAcreage() * 0.64);

    auto music = CreateOrganization<MusicOrganization>();

    music->AddRoom(CreateRoom<ReceptionRoom>(1, 40));
    acreages[0] -= 40;
    for (int layer = 0; layer < layers; layer++) {
        music->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
    }
    music->AddRoom(CreateRoom<WarehouseRoom>(1, acreages[0] / 2));
    music->AddRoom(CreateRoom<MusicRoom>(1, acreages[0] / 2));

    for (int layer = 1; layer < layers; layer++) {
        if (layer == layers - 1) {
            for (int i = 0; i < acreages[layer] / 40; i++) {
                music->AddRoom(CreateRoom<ClassRoom>(layer + 1, 40));
            }
        }
        else {
            music->AddRoom(CreateRoom<MusicRoom>(1, acreages[0]));
        }
    }
}

void MusicBuilding::ArrangeLayout() {

}

void IngredientBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 2 + GetRandom(2);
    }
    else {
        layers = 1;
    }
    basement = 0;
}

void IngredientBuilding::DistributeInside() {
    // Market

    vector<int> acreages = vector<int>(layers, GetAcreage() * 64);
    auto ingredient = CreateOrganization<IngredientOrganization>();

    for (int layer = 0; layer < layers; layer++) {
        ingredient->AddRoom(CreateRoom<MarketRoom>(1, acreages[0]));
    }
}

void IngredientBuilding::ArrangeLayout() {

}

void BrandBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 3 + GetRandom(2);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = GetRandom(2);
}

void BrandBuilding::DistributeInside() {
    //Parking
    //Warehouse
    //Reception
    //Toilet
    //Sale

    vector<int> acreages;
    if (zone == ZONE_NONE) {
        acreages = vector<int>(layers, GetAcreage() * 0.36);
    }
    else {
        acreages = vector<int>(layers, GetAcreage() * 0.64);
    }

    auto brand = CreateOrganization<BrandOrganization>();

    if (zone == ZONE_NONE) {
        brand->AddRoom(CreateRoom<ParkingRoom>(0, GetAcreage() * 0.28));
        if (basement > 0) {
            for (int i = 0; i < basement; i++) {
                brand->AddRoom(CreateRoom<WarehouseRoom>(-i - 1, GetAcreage() * 0.64));
            }
        }
    }
    else {
        if (basement > 0) {
            brand->AddRoom(CreateRoom<ParkingRoom>(-1, GetAcreage() * 0.32));
            brand->AddRoom(CreateRoom<WarehouseRoom>(-1, GetAcreage() * 0.32));
            for (int i = 1; i < basement; i++) {
                brand->AddRoom(CreateRoom<WarehouseRoom>(-i - 1, GetAcreage() * 0.64));
            }
        }
    }

    brand->AddRoom(CreateRoom<ReceptionRoom>(1, 40));
    acreages[0] -= 40;
    for (int layer = 0; layer < layers; layer++) {
        brand->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        acreages[layer] -= 60;
        brand->AddRoom(CreateRoom<SaleRoom>(layer + 1, acreages[layer]));
    }
}

void BrandBuilding::ArrangeLayout() {

}

void CarRentBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 2 + GetRandom(2);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = 1 + GetRandom(3);
}

void CarRentBuilding::DistributeInside() {

}

void CarRentBuilding::ArrangeLayout() {

}

void TheaterBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1 + GetRandom(2);
    basement = GetRandom(2);
}

void TheaterBuilding::DistributeInside() {

}

void TheaterBuilding::ArrangeLayout() {

}

void MuseumBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 2 + GetRandom(2);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = GetRandom(2);
}

void MuseumBuilding::DistributeInside() {

}

void MuseumBuilding::ArrangeLayout() {

}

void ZooBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void ZooBuilding::DistributeInside() {

}

void ZooBuilding::ArrangeLayout() {

}

void BotanicBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void BotanicBuilding::DistributeInside() {

}

void BotanicBuilding::ArrangeLayout() {

}

void AquariumBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void AquariumBuilding::DistributeInside() {

}

void AquariumBuilding::ArrangeLayout() {

}

void CinemaBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 2 + GetRandom(2);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = GetRandom(2);
}

void CinemaBuilding::DistributeInside() {

}

void CinemaBuilding::ArrangeLayout() {

}

void PubBuilding::InitBuilding() {
    if (GetRandom(8) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1 + GetRandom(2);
    basement = 0;
}

void PubBuilding::DistributeInside() {

}

void PubBuilding::ArrangeLayout() {

}

void MasageBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 5000) {
        layers = 3 + GetRandom(2);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = GetRandom(2);
}

void MasageBuilding::DistributeInside() {

}

void MasageBuilding::ArrangeLayout() {

}

void AmusementBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 1;
}

void AmusementBuilding::DistributeInside() {

}

void AmusementBuilding::ArrangeLayout() {

}

void OfficeBuilding::InitBuilding() {
    if (GetRandom(8) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area < AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 16 + GetRandom(5) * 5;
    }
    else if (area <= AREA_RESIDENTM && GetAcreage() > 5000) {
        layers = 7 + GetRandom(8) * 2;
    }
    else {
        layers = 3 + GetRandom(5);
    }
    basement = GetRandom(3);
}

void OfficeBuilding::DistributeInside() {

}

void OfficeBuilding::ArrangeLayout() {

}

void StockBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 5000) {
        layers = 3 + GetRandom(2);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = GetRandom(2);
}

void StockBuilding::DistributeInside() {

}

void StockBuilding::ArrangeLayout() {

}

void CourtBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 5000) {
        layers = 3 + GetRandom(2);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = 0;
}

void CourtBuilding::DistributeInside() {

}

void CourtBuilding::ArrangeLayout() {

}

void GovernmentBuilding::InitBuilding() {
    if (GetRandom(50) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 5000) {
        layers = 6 + GetRandom(4) * 2;
    }
    else {
        layers = 2 + GetRandom(4);
    }
    basement = GetRandom(2);
}

void GovernmentBuilding::DistributeInside() {

}

void GovernmentBuilding::ArrangeLayout() {

}

void LabBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area < AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 10 + GetRandom(4) * 2;
    }
    else if (area <= AREA_RESIDENTM && GetAcreage() > 5000) {
        layers = 5 + GetRandom(4);
    }
    else {
        layers = 1 + GetRandom(3);
    }
    basement = GetRandom(3);
}

void LabBuilding::DistributeInside() {

}

void LabBuilding::ArrangeLayout() {

}

void FactoryBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1 + GetRandom(2);
    basement = 0;
}

void FactoryBuilding::DistributeInside() {

}

void FactoryBuilding::ArrangeLayout() {

}

void WarehouseBuilding::InitBuilding() {
    if (GetRandom(8) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = GetRandom(2);
}

void WarehouseBuilding::DistributeInside() {

}

void WarehouseBuilding::ArrangeLayout() {

}

void RepairBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void RepairBuilding::DistributeInside() {

}

void RepairBuilding::ArrangeLayout() {

}

void MiningBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void MiningBuilding::DistributeInside() {

}

void MiningBuilding::ArrangeLayout() {

}

void OilingBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void OilingBuilding::DistributeInside() {

}

void OilingBuilding::ArrangeLayout() {

}

void QuarryBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void QuarryBuilding::DistributeInside() {

}

void QuarryBuilding::ArrangeLayout() {

}

void FarmBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void FarmBuilding::DistributeInside() {

}

void FarmBuilding::ArrangeLayout() {

}

void PastureBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void PastureBuilding::DistributeInside() {

}

void PastureBuilding::ArrangeLayout() {

}

void BreedingBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void BreedingBuilding::DistributeInside() {

}

void BreedingBuilding::ArrangeLayout() {

}

void FishingBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void FishingBuilding::DistributeInside() {

}

void FishingBuilding::ArrangeLayout() {

}

void OrchardBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void OrchardBuilding::DistributeInside() {

}

void OrchardBuilding::ArrangeLayout() {

}

void ForestBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void ForestBuilding::DistributeInside() {

}

void ForestBuilding::ArrangeLayout() {

}

void ParkBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void ParkBuilding::DistributeInside() {

}

void ParkBuilding::ArrangeLayout() {

}

void PlazaBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void PlazaBuilding::DistributeInside() {

}

void PlazaBuilding::ArrangeLayout() {

}

void StatueBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void StatueBuilding::DistributeInside() {

}

void StatueBuilding::ArrangeLayout() {

}

void GymBuilding::InitBuilding() {
    if (GetRandom(8) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void GymBuilding::DistributeInside() {

}

void GymBuilding::ArrangeLayout() {

}

void StadiumBuilding::InitBuilding() {
    if (GetRandom(8) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void StadiumBuilding::DistributeInside() {

}

void StadiumBuilding::ArrangeLayout() {

}

void ResortBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void ResortBuilding::DistributeInside() {

}

void ResortBuilding::ArrangeLayout() {

}

void RemainsBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void RemainsBuilding::DistributeInside() {

}

void RemainsBuilding::ArrangeLayout() {

}

void RocketBuilding::InitBuilding() {
    if (GetRandom(50) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void RocketBuilding::DistributeInside() {

}

void RocketBuilding::ArrangeLayout() {

}

void PlaygroundBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void PlaygroundBuilding::DistributeInside() {

}

void PlaygroundBuilding::ArrangeLayout() {

}

void PrisonBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 10000) {
        layers = 4 + GetRandom(4);
    }
    else {
        layers = 1 + GetRandom(3);
    }
    basement = GetRandom(3);
}

void PrisonBuilding::DistributeInside() {

}

void PrisonBuilding::ArrangeLayout() {

}

void GuardBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void GuardBuilding::DistributeInside() {

}

void GuardBuilding::ArrangeLayout() {

}

void CanteenBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 5000) {
        layers = 4 + GetRandom(4);
    }
    else {
        layers = 1 + GetRandom(3);
    }
    basement = 0;
}

void CanteenBuilding::DistributeInside() {

}

void CanteenBuilding::ArrangeLayout() {

}

void DormitryBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else if (GetRandom(8) == 0) {
        status = CONSTRUCTION_WORKING;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 5000) {
        layers = 7 + GetRandom(10);
    }
    else {
        layers = 3 + GetRandom(5);
    }
    basement = GetRandom(2);
}

void DormitryBuilding::DistributeInside() {

}

void DormitryBuilding::ArrangeLayout() {

}

void DataBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1 + GetRandom(2);
    basement = 0;
}

void DataBuilding::DistributeInside() {

}

void DataBuilding::ArrangeLayout() {

}

void WaterBuilding::InitBuilding() {
    if (GetRandom(50) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void WaterBuilding::DistributeInside() {

}

void WaterBuilding::ArrangeLayout() {

}

void SewageBuilding::InitBuilding() {
    if (GetRandom(50) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void SewageBuilding::DistributeInside() {

}

void SewageBuilding::ArrangeLayout() {

}

void PowerBuilding::InitBuilding() {
    if (GetRandom(50) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void PowerBuilding::DistributeInside() {

}

void PowerBuilding::ArrangeLayout() {

}

void WindmillBuilding::InitBuilding() {
    if (GetRandom(50) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void WindmillBuilding::DistributeInside() {

}

void WindmillBuilding::ArrangeLayout() {

}

void NuclearBuilding::InitBuilding() {
    if (GetRandom(50) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void NuclearBuilding::DistributeInside() {

}

void NuclearBuilding::ArrangeLayout() {

}

void BatteryBuilding::InitBuilding() {
    if (GetRandom(50) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void BatteryBuilding::DistributeInside() {

}

void BatteryBuilding::ArrangeLayout() {

}

void RecycleBuilding::InitBuilding() {
    if (GetRandom(50) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void RecycleBuilding::DistributeInside() {

}

void RecycleBuilding::ArrangeLayout() {

}

void TrashBuilding::InitBuilding() {
    if (GetRandom(50) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void TrashBuilding::DistributeInside() {

}

void TrashBuilding::ArrangeLayout() {

}

void IncinerationBuilding::InitBuilding() {
    if (GetRandom(50) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
    basement = 0;
}

void IncinerationBuilding::DistributeInside() {

}

void IncinerationBuilding::ArrangeLayout() {

}

