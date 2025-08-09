#include "util.h"
#include "building.h"

#include <filesystem>
#include <fstream>
#include <string>


using namespace std;

std::unordered_map<std::string, std::vector<std::pair<Facility::FACILITY_TYPE, std::vector<float>>>> Building::templateFacility = {};
std::unordered_map<std::string, std::vector<std::pair<FACE_DIRECTION, std::vector<float>>>> Building::templateUsage = {};

Room* Floor::SampleRoom(vector<Room> & complement, int idx) {
    if (idx < rooms.size())return rooms[idx];
    else return &complement[(idx - rooms.size()) % complement.size()];
}

Room* Floor::ApplyRoom(vector<Room>& complement, int idx) {
    if (idx < rooms.size())return rooms[idx];

    Room* room = new Room(complement[(idx - rooms.size()) % complement.size()]);
    room->SetLayer(level);
    rooms.push_back(room);
    return room;
}

void Floor::UsageLayout(vector<Room> complement) {
    int idx = 0;
    for (auto usage : usages) {
        vector<float> samples;
        if (usage.second == FACE_WEST || usage.second == FACE_EAST) {
            float y = 0;
            int idxBegin = idx;
            while(true) {
                Room* sample = SampleRoom(complement, idx);
                float step = (sample->GetAcreage() / 100.f) / usage.first.GetSizeX();
                if (y + step > usage.first.GetSizeY() + GLOBAL_EPS)break;
                Room *room = ApplyRoom(complement, idx++);
                room->SetPosition(
                    usage.first.GetLeft(), usage.first.GetRight(),
                    usage.first.GetTop() + y, usage.first.GetTop() + y + step);
                samples.push_back(y);
                y += step;
            }
            if (samples.size() == 0) {
                Room* room = ApplyRoom(complement, idx++);
                room->SetPosition(
                    usage.first.GetLeft(), usage.first.GetRight(),
                    usage.first.GetTop(), usage.first.GetBottom());
            }
            else {
                int idxEnd = idx;
                samples.push_back(y);
                float inflate = usage.first.GetSizeY() / y;
                for (auto& sample : samples) {
                    sample *= inflate;
                }
                for (int i = 0; i < idxEnd - idxBegin; i++) {
                    Room* room = SampleRoom(complement, idxBegin + i);
                    room->SetPosition(room->GetLeft(), room->GetRight(),
                        usage.first.GetTop() + samples[i], usage.first.GetTop() + samples[i + 1]);
                }
            }
        }
        if (usage.second == FACE_NORTH || usage.second == FACE_SOUTH) {
            float x = 0;
            int idxBegin = idx;
            while (true) {
                Room* sample = SampleRoom(complement, idx);
                float step = (sample->GetAcreage() / 100.f) / usage.first.GetSizeY();
                if (x + step > usage.first.GetSizeX() + GLOBAL_EPS)break;
                Room* room = ApplyRoom(complement, idx++);
                room->SetPosition(
                    usage.first.GetLeft() + x, usage.first.GetLeft() + x + step,
                    usage.first.GetTop(), usage.first.GetBottom());
                samples.push_back(x);
                x += step;
            }
            if (samples.size() == 0) {
                Room* room = ApplyRoom(complement, idx++);
                room->SetPosition(
                    usage.first.GetLeft(), usage.first.GetRight(),
                    usage.first.GetTop(), usage.first.GetBottom());
            }
            else {
                int idxEnd = idx;
                samples.push_back(x);
                float inflate = usage.first.GetSizeX() / x;
                for (auto& sample : samples) {
                    sample *= inflate;
                }
                for (int i = 0; i < idxEnd - idxBegin; i++) {
                    Room* room = SampleRoom(complement, idxBegin + i);
                    room->SetPosition(usage.first.GetLeft() + samples[i], usage.first.GetLeft() + samples[i + 1],
                        room->GetTop(), room->GetBottom());
                }
            }
        }
    }
}

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

void Building::TemplateLayout(string temp, FACE_DIRECTION face, float underScalar, float aboveScalar) {
    float aboveScalarX = aboveScalar;
    float aboveScalarY = aboveScalar;
    float underScalarX = underScalar;
    float underScalarY = underScalar;

    // 设定局部位置
    float minLength = 1.6f;
    float minGap = 0.4f;
    if (sizeX * aboveScalarX < minLength) {
        aboveScalarX = minLength / sizeX;
    }
    if (sizeY * aboveScalarY < minLength) {
        aboveScalarY = minLength / sizeY;
    }
    if (sizeX - minGap < sizeX * aboveScalarX) {
        aboveScalarX = 1.f - minGap / sizeX;
    }
    if (sizeY - minGap < sizeY * aboveScalarY) {
        aboveScalarY = 1.f - minGap / sizeY;
    }
    under = Rect(sizeX * (1.0f - underScalarX) / 2, sizeY * (1.0f - underScalarY) / 2,
        sizeX * underScalarX, sizeY * underScalarY);
    switch (face) {
    case FACE_WEST:
        above = Rect(sizeX * (1.0f + underScalarX) / 2 - sizeX * aboveScalarX, sizeY * (1.0f - aboveScalarY) / 2,
            sizeX * aboveScalarX, sizeY * aboveScalarY);
        break;
    case FACE_EAST:
        above = Rect(sizeX * (1.0f - underScalarX) / 2, sizeY * (1.0f - aboveScalarY) / 2,
            sizeX * aboveScalarX, sizeY * aboveScalarY);
        break;
    case FACE_NORTH:
        above = Rect(sizeX * (1.0f - aboveScalarX) / 2, sizeY * (1.0f + underScalarY) / 2 - sizeY * aboveScalarY,
            sizeX * aboveScalarX, sizeY * aboveScalarY);
        break;
    case FACE_SOUTH:
        above = Rect(sizeX * (1.0f - aboveScalarX) / 2, sizeY * (1.0f - underScalarY) / 2,
            sizeX * aboveScalarX, sizeY * aboveScalarY);
        break;
    default:
        break;
    }

    // 添加楼层
    float underX = sizeX * underScalar;
    float underY = sizeY * underScalar;
    for (int i = -basement; i < 0; i++) {
        floors.emplace_back(i, underX, underY);
    }
    floors.emplace_back(0, sizeX, sizeY);
    float aboveX = sizeX * aboveScalar;
    float aboveY = sizeY * aboveScalar;
    for (int i = 0; i < layers; i++) {
        floors.emplace_back(i + 1, aboveX, aboveY);
    }

    // 把房间加入楼层
    for (auto room : rooms) {
        floors[basement + room->GetLayer()].AddRoom(room);
    }

    //布局公共设施
    for (auto &floor : floors) {
        for (auto facility : templateFacility[temp + "_" + faceAbbr[face]]) {
            if (floor.GetLevel() == 0)continue;
            if (floor.GetLevel() < 0 && facility.first == Facility::FACILITY_CORRIDOR)continue;
            float l = facility.second[0] * floor.GetSizeX() + facility.second[1] * 0.1f;
            float t = facility.second[2] * floor.GetSizeY() + facility.second[3] * 0.1f;
            float r = facility.second[4] * floor.GetSizeX() + facility.second[5] * 0.1f;
            float b = facility.second[6] * floor.GetSizeY() + facility.second[7] * 0.1f;
            floor.AddFacility(Facility(facility.first, l, t, r - l, b - t));
        }
        for (auto usage : templateUsage[temp + "_" + faceAbbr[face]]) {
            if (floor.GetLevel() <= 0)continue;
            float l = usage.second[0] * floor.GetSizeX() + usage.second[1] * 0.1f;
            float t = usage.second[2] * floor.GetSizeY() + usage.second[3] * 0.1f;
            float r = usage.second[4] * floor.GetSizeX() + usage.second[5] * 0.1f;
            float b = usage.second[6] * floor.GetSizeY() + usage.second[7] * 0.1f;
            floor.AddUsage(make_pair(Rect(l, t, r - l, b - t), usage.first));
        }
    }

    // 分配房间位置
    for (int i = 0; i < floors.size(); i++) {
        int num = floors[i].GetRooms().size();
        floors[i].UsageLayout(complements[i]);

        if (num < floors[i].GetRooms().size()) {
            for (int j = num; j < floors[i].GetRooms().size(); j++) {
                rooms.push_back(floors[i].GetRooms()[j]);
            }
        }
    }
}

void Building::ReadTemplates(std::string path) {
    std::vector<std::pair<std::string, std::string>> templates;

    if (!filesystem::exists(path)) {
        throw std::runtime_error("Path does not exist: " + path);
    }

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            string filename = entry.path().filename().string();
            filename = filename.substr(0, filename.length() - 4);

            ifstream fin(entry.path());
            string type;
            float param;
            if (fin.is_open()) {
                templateFacility.emplace(filename, vector<pair<Facility::FACILITY_TYPE, std::vector<float>>>());
                templateUsage.emplace(filename, vector<pair<FACE_DIRECTION, std::vector<float>>>());
                while (!fin.eof()) {
                    pair<Facility::FACILITY_TYPE, std::vector<float>> facilities;
                    pair<FACE_DIRECTION, std::vector<float>> usages;

                    fin >> type;

                    if (type == "corridor")facilities.first = Facility::FACILITY_CORRIDOR;
                    else if (type == "stair")facilities.first = Facility::FACILITY_STAIR;
                    else if (type == "elevator")facilities.first = Facility::FACILITY_ELEVATOR;
                    else if (type == "usage") {
                        fin >> param;
                        usages.first = (FACE_DIRECTION)param;
                    }
                    else break;

                    if (type == "corridor" || type == "stair" || type == "elevator") {
                        for (int i = 0; i < 8; i++) {
                            fin >> param;
                            facilities.second.push_back(param);
                        }
                        templateFacility[filename].push_back(facilities);
                    }
                    else if (type == "usage") {
                        for (int i = 0; i < 8; i++) {
                            fin >> param;
                            usages.second.push_back(param);
                        }
                        templateUsage[filename].push_back(usages);
                    }
                    else break;
                }
            }
            else {
                throw std::runtime_error("Failed to open file: " + filename);
            }
        }
    }
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

}

vector<pair<Job*, int>> RoadfixBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void ParkingBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void ParkingBuilding::DistributeInside() {

}

vector<pair<Job*, int>> ParkingBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> BankBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> LibraryBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> ClinicBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> HospitalBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> InpatientBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> SanatoriumBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> PoliceBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> FireBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> SchoolBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> CrematoriumBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void CemetryBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void CemetryBuilding::DistributeInside() {

}

vector<pair<Job*, int>> CemetryBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> TVStationBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> GasolineBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> ToiletBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void SubstationBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void SubstationBuilding::DistributeInside() {

}

vector<pair<Job*, int>> SubstationBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> PostBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void MetroBuilding::InitBuilding() {

}

void MetroBuilding::DistributeInside() {

}

vector<pair<Job*, int>> MetroBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void TrainBuilding::InitBuilding() {

}

void TrainBuilding::DistributeInside() {

}

vector<pair<Job*, int>> TrainBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void PlaneBuilding::InitBuilding() {

}

void PlaneBuilding::DistributeInside() {

}

vector<pair<Job*, int>> PlaneBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void ShipBuilding::InitBuilding() {

}

void ShipBuilding::DistributeInside() {

}

vector<pair<Job*, int>> ShipBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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
    basement = GetRandom(2);
}

void ResidentBuilding::DistributeInside() {
    //Parking
    //Home

    auto resident = CreateOrganization<CommunityOrganization>();

    float aboveScalar = 0.8f;
    float underScalar = 0.8f;

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            resident->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    int standard = 100;
    string temp = "";
    int face = 0;
    int narrow = min(GetSizeX(), GetSizeY());
    if (GetAcreage() < 800) {
        standard = 80;
        temp = "straight_linear";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);
    }
    else if (GetAcreage() < 2000) {
        if (narrow <= 2) {
            standard = 60;
        }
        else {
            standard = 100;
        }
        temp = "straight_linear";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_WEST : FACE_EAST) :
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH);
    }
    else {
        if (narrow <= 4) {
            if (narrow <= 2) {
                standard = 60;
            }
            else {
                standard = 100;
            }
            temp = "straight_linear";
            face = (GetSizeX() > GetSizeY()) ?
                (GetRandom(2) ? FACE_WEST : FACE_EAST) :
                (GetRandom(2) ? FACE_NORTH : FACE_SOUTH);
        }
        else {
            standard = 160;
            switch (GetRandom(2)) {
            case 0:
                temp = "comb_double";
                face = (GetSizeX() > GetSizeY()) ?
                    (GetRandom(2) ? FACE_WEST : FACE_EAST) :
                    (GetRandom(2) ? FACE_NORTH : FACE_SOUTH);
                break;
            case 1:
                temp = "fence_double";
                face = (GetSizeX() > GetSizeY()) ?
                    (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
                    (GetRandom(2) ? FACE_WEST : FACE_EAST);
                break;
            default:
                break;
            }
        }
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto &complement : complements) {
        complement.push_back(HomeRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temp, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > resident->GetRooms().size()) {
        for (int i = resident->GetRooms().size(); i < rooms.size(); i++) {
            resident->AddRoom(rooms[i]);
        }
    }
}

vector<pair<Job*, int>> ResidentBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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
    //Warehouse
    //Home

    auto villa = CreateOrganization<CommunityOrganization>();

    float aboveScalar, underScalar;
    if (GetAcreage() < 1000) {
        aboveScalar = underScalar = 0.5f;
    }
    else if (GetAcreage() < 2000) {
        aboveScalar = underScalar = 0.4f;
    }
    else {
        aboveScalar = underScalar = 0.3f;
    }

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            villa->AddRoom(CreateRoom<WarehouseRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    int standard = 1e4;
    string temp = "single_room";
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(HomeRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temp, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > villa->GetRooms().size()) {
        for (int i = villa->GetRooms().size(); i < rooms.size(); i++) {
            villa->AddRoom(rooms[i]);
        }
    }
}

vector<pair<Job*, int>> VillaBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> EstateBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> PropertyBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> PackageBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> HotelBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> RestaurantBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> MallBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> MarketBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> MusicBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> IngredientBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

}

vector<pair<Job*, int>> BrandBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> CarRentBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> TheaterBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> MuseumBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> ZooBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> BotanicBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> AquariumBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> CinemaBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> PubBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> MasageBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> AmusementBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> OfficeBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> StockBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> CourtBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> GovernmentBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> LabBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> FactoryBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> WarehouseBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> RepairBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> MiningBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> OilingBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> QuarryBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> FarmBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> PastureBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> BreedingBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> FishingBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> OrchardBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> ForestBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void ParkBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void ParkBuilding::DistributeInside() {

}

vector<pair<Job*, int>> ParkBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void PlazaBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void PlazaBuilding::DistributeInside() {

}

vector<pair<Job*, int>> PlazaBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void StatueBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void StatueBuilding::DistributeInside() {

}

vector<pair<Job*, int>> StatueBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> GymBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> StadiumBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> ResortBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void RemainsBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void RemainsBuilding::DistributeInside() {

}

vector<pair<Job*, int>> RemainsBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> RocketBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> PlaygroundBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> PrisonBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> GuardBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> CanteenBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> DormitryBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> DataBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> WaterBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> SewageBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> PowerBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> WindmillBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> NuclearBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> BatteryBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> RecycleBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> TrashBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
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

vector<pair<Job*, int>> IncinerationBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}
