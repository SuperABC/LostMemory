#include "util.h"
#include "building.h"

#include <filesystem>
#include <fstream>
#include <string>


using namespace std;

std::unordered_map<std::string, std::vector<std::pair<Facility::FACILITY_TYPE, std::vector<float>>>> Building::templateFacility = {};
std::unordered_map<std::string, std::vector<std::pair<FACE_DIRECTION, std::vector<float>>>> Building::templateUsage = {};

const Room *Floor::SampleRoom(vector<Room> &complement, int idx, int start) {
    //只返回房间数据
    if (idx < rooms.size())return rooms[idx].get();
    else return &complement[(idx - start) % complement.size()];
}

shared_ptr<Room> Floor::ApplyRoom(vector<Room>& complement, int idx, int start) {
    if (idx < rooms.size())return rooms[idx];

    //把要循环的房间加入楼层
    shared_ptr<Room> room = LM_NEW(Room, complement[(idx - start) % complement.size()]);
    room->SetLayer(level);
    rooms.push_back(room);
    return room;
}

int Floor::UsageLayout(vector<Room> complement) {
    // 当前楼层已经布局完成的房间数量
    int idx = 0;

    // 初始添加的房间总数
    int start = rooms.size();

    // 每个功能区循环
    for (auto usage : usages) {
        //房间宽度记录
        vector<float> samples;
        if (usage.second == FACE_WEST || usage.second == FACE_EAST) {
            float y = 0;
            int idxBegin = idx;
            while(true) {
                const Room* sample = SampleRoom(complement, idx, start);
                float step = (sample->GetAcreage() / 100.f) / usage.first.GetSizeX();
                if (y + step > usage.first.GetSizeY() + GLOBAL_EPS)break;
                shared_ptr<Room> room = ApplyRoom(complement, idx++, start);
                room->SetPosition(
                    usage.first.GetLeft(), usage.first.GetRight(),
                    usage.first.GetTop() + y, usage.first.GetTop() + y + step);
                samples.push_back(y);
                y += step;
            }
            // 如果没有房间被添加，则强制添加一个房间
            if (samples.size() == 0) {
                shared_ptr<Room> room = ApplyRoom(complement, idx++, start);
                room->SetPosition(
                    usage.first.GetLeft(), usage.first.GetRight(),
                    usage.first.GetTop(), usage.first.GetBottom());
            }
            // 否则所有房间按比例填满功能区
            else {
                int idxEnd = idx;
                samples.push_back(y);
                float inflate = usage.first.GetSizeY() / y;
                for (auto& sample : samples) {
                    sample *= inflate;
                }
                for (int i = 0; i < idxEnd - idxBegin; i++) {
                    shared_ptr<Room> room = ApplyRoom(complement, idxBegin + i, start);
                    room->SetPosition(room->GetLeft(), room->GetRight(),
                        usage.first.GetTop() + samples[i], usage.first.GetTop() + samples[i + 1]);
                }
            }
        }
        if (usage.second == FACE_NORTH || usage.second == FACE_SOUTH) {
            float x = 0;
            int idxBegin = idx;
            while (true) {
                const Room* sample = SampleRoom(complement, idx, start);
                float step = (sample->GetAcreage() / 100.f) / usage.first.GetSizeY();
                if (x + step > usage.first.GetSizeX() + GLOBAL_EPS)break;
                shared_ptr<Room> room = ApplyRoom(complement, idx++, start);
                room->SetPosition(
                    usage.first.GetLeft() + x, usage.first.GetLeft() + x + step,
                    usage.first.GetTop(), usage.first.GetBottom());
                samples.push_back(x);
                x += step;
            }
            // 如果没有房间被添加，则强制添加一个房间
            if (samples.size() == 0) {
                shared_ptr<Room> room = ApplyRoom(complement, idx++, start);
                room->SetPosition(
                    usage.first.GetLeft(), usage.first.GetRight(),
                    usage.first.GetTop(), usage.first.GetBottom());
            }
            // 否则所有房间按比例填满功能区
            else {
                int idxEnd = idx;
                samples.push_back(x);
                float inflate = usage.first.GetSizeX() / x;
                for (auto& sample : samples) {
                    sample *= inflate;
                }
                for (int i = 0; i < idxEnd - idxBegin; i++) {
                    shared_ptr<Room> room = ApplyRoom(complement, idxBegin + i, start);
                    room->SetPosition(usage.first.GetLeft() + samples[i], usage.first.GetLeft() + samples[i + 1],
                        room->GetTop(), room->GetBottom());
                }
            }
        }
    }
    return idx;
}

BUILDING_TYPE Building::GetType() const {
    return type;
}

void Building::SetType(BUILDING_TYPE type) {
    this->type = type;
}

CONSTRUCTION_TYPE Building::GetStatus() const {
    return status;
}

AREA_TYPE Building::GetAreaType() const {
    return area;
}

void Building::SetAreaType(AREA_TYPE type) {
    area = type;
}

ZONE_TYPE Building::GetZoneType() const {
    return zone;
}

void Building::SetZoneType(ZONE_TYPE type) {
    zone = type;
}

Rect Building::GetAbove() {
    return above;
}

Rect Building::GetUnder() {
    return under;
}

void Building::TemplateLayout(vector<string> temps, FACE_DIRECTION face, float aboveScalar, float underScalar) {
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
    for (int i = -basement; i < 0; i++) {
        floors.emplace_back(i, under.GetSizeX(), under.GetSizeY());
    }
    floors.emplace_back(0, sizeX, sizeY);
    for (int i = 0; i < layers; i++) {
        floors.emplace_back(i + 1, above.GetSizeX(), above.GetSizeY());
    }

    // 把房间加入楼层
    for (auto room : rooms) {
        floors[basement + room->GetLayer()].AddRoom(room);
    }

    //布局公共设施
    string temp;
    for (auto &floor : floors) {
        if (floor.GetLevel() == 0)continue;
        else if (floor.GetLevel() > temps.size())temp = temps.back();
        else temp = temps[floor.GetLevel() - 1];
        for (auto facility : templateFacility[temp + "_" + faceAbbr[face]]) {
            if (floor.GetLevel() < 0 && facility.first == Facility::FACILITY_CORRIDOR)continue;
            float l = facility.second[0] * above.GetSizeX() + facility.second[1] * 0.1f;
            float t = facility.second[2] * above.GetSizeY() + facility.second[3] * 0.1f;
            float r = facility.second[4] * above.GetSizeX() + facility.second[5] * 0.1f;
            float b = facility.second[6] * above.GetSizeY() + facility.second[7] * 0.1f;
            floor.AddFacility(Facility(facility.first, l, t, r - l, b - t));
        }
        if (floor.GetLevel() <= 0)continue;
        for (auto usage : templateUsage[temp + "_" + faceAbbr[face]]) {
            float l = usage.second[0] * above.GetSizeX() + usage.second[1] * 0.1f;
            float t = usage.second[2] * above.GetSizeY() + usage.second[3] * 0.1f;
            float r = usage.second[4] * above.GetSizeX() + usage.second[5] * 0.1f;
            float b = usage.second[6] * above.GetSizeY() + usage.second[7] * 0.1f;
            floor.AddUsage(make_pair(Rect(l, t, r - l, b - t), usage.first));
        }
    }

    // 分配房间位置
    int idx = 0;
    for (int i = 0; i < floors.size(); i++) {
        if (floors[i].GetLevel() == 0)continue;
        else if (floors[i].GetLevel() < 0) {
            floors[i].GetRooms()[0]->SetPosition(under.GetLeft(), under.GetRight(), under.GetTop(), under.GetBottom());
        }
        else {
            int num = floors[i].GetRooms().size();
            idx += floors[i].UsageLayout(complements[i]);

            if (num < floors[i].GetRooms().size()) {
                for (int j = num; j < floors[i].GetRooms().size(); j++) {
                    rooms.push_back(floors[i].GetRooms()[j]);
                }
            }
        }
    }
}

void Building::ReadTemplates(std::string path) {
    if (!filesystem::exists(path)) {
        throw std::runtime_error("Path does not exist: " + path + "\n");
    }

    for (const auto& entry : filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            string filename = entry.path().filename().string();
            string basename = filename.substr(0, filename.length() - 4);
            string extension = filename.substr(filename.length() - 3, filename.length());
            if (extension != "txt")continue;

            ifstream fin(entry.path());
            if (!fin.is_open()) {
                throw std::runtime_error("Failed to open file: " + filename + "\n");
            }

            // 初始化当前文件的模板存储
            templateFacility[basename] = vector<pair<Facility::FACILITY_TYPE, vector<float>>>();
            templateUsage[basename] = vector<pair<FACE_DIRECTION, vector<float>>>();

            string type;
            while (fin >> type) {
                // 处理注释行
                if (type == "#") {
                    fin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    continue;
                }

                // 处理设施
                if (type == "corridor" || type == "stair" || type == "elevator") {
                    vector<float> params(8);
                    bool readError = false;

                    for (int i = 0; i < 8; i++) {
                        if (!(fin >> params[i])) {
                            readError = true;
                            break;
                        }
                    }

                    if (readError) {
                        throw std::runtime_error("Incomplete parameters for " + type +
                            " in file: " + filename + "\n");
                    }

                    // 转换为枚举类型
                    Facility::FACILITY_TYPE facType;
                    if (type == "corridor")facType = Facility::FACILITY_CORRIDOR;
                    else if (type == "stair")facType = Facility::FACILITY_STAIR;
                    else facType = Facility::FACILITY_ELEVATOR;

                    templateFacility[basename].push_back({ facType, params });
                }
                // 处理功能区
                else if (type == "usage") {
                    int directionInt;
                    if (!(fin >> directionInt)) {
                        throw std::runtime_error("Failed to read direction for usage in file: " + filename + "\n");
                    }

                    // 验证方向值有效性
                    if (directionInt < 0 || directionInt > 3) {
                        throw std::runtime_error("Invalid direction value " + to_string(directionInt) +
                            " in file: " + filename + "\n");
                    }
                    FACE_DIRECTION direction = static_cast<FACE_DIRECTION>(directionInt);

                    vector<float> params(8);
                    bool readError = false;
                    for (int i = 0; i < 8; i++) {
                        if (!(fin >> params[i])) {
                            readError = true;
                            break;
                        }
                    }

                    if (readError) {
                        throw std::runtime_error("Incomplete parameters for usage in file: " + filename + "\n");
                    }

                    templateUsage[basename].push_back({ direction, params });
                }
                // 处理未知类型
                else {
                    string errorMsg = "Unknown type identifier '" + type +
                        "' in file: " + filename + "\n";

                    // 跳过错误行的剩余内容
                    fin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    throw std::runtime_error(errorMsg);
                }
            }
        }
    }
}

shared_ptr<Building> CreateBuilding(BUILDING_TYPE type) {
    switch (type) {
    case BUILDING_RESIDENT:
        return LM_NEW(ResidentBuilding);
    case BUILDING_VILLA:
        return LM_NEW(VillaBuilding);
    case BUILDING_HOTEL:
        return LM_NEW(HotelBuilding);
    case BUILDING_MALL:
        return LM_NEW(MallBuilding);
    case BUILDING_SHOP:
        return LM_NEW(ShopBuilding);
    case BUILDING_RESTAURANT:
        return LM_NEW(RestaurantBuilding);
    case BUILDING_CARRENT:
        return LM_NEW(CarRentBuilding);
    case BUILDING_THEATER:
        return LM_NEW(TheaterBuilding);
    case BUILDING_CINEMA:
        return LM_NEW(CinemaBuilding);
    case BUILDING_MUSEUM:
        return LM_NEW(MuseumBuilding);
    case BUILDING_MASAGE:
        return LM_NEW(MasageBuilding);
    case BUILDING_PACKAGE:
        return LM_NEW(PackageBuilding);
    case BUILDING_OFFICE:
        return LM_NEW(OfficeBuilding);
    case BUILDING_LAB:
        return LM_NEW(LabBuilding);
    case BUILDING_GOVERNMENT:
        return LM_NEW(GovernmentBuilding);
    case BUILDING_FACTORY:
        return LM_NEW(FactoryBuilding);
    case BUILDING_WAREHOUSE:
        return LM_NEW(WarehouseBuilding);
    case BUILDING_MINING:
        return LM_NEW(MiningBuilding);
    case BUILDING_OILING:
        return LM_NEW(OilingBuilding);
    case BUILDING_QUARRY:
        return LM_NEW(QuarryBuilding);
    case BUILDING_FARM:
        return LM_NEW(FarmBuilding);
    case BUILDING_PASTURE:
        return LM_NEW(PastureBuilding);
    case BUILDING_BREEDING:
        return LM_NEW(BreedingBuilding);
    case BUILDING_FISHING:
        return LM_NEW(FishingBuilding);
    case BUILDING_ORCHARD:
        return LM_NEW(OrchardBuilding);
    case BUILDING_FOREST:
        return LM_NEW(ForestBuilding);
    case BUILDING_PARK:
        return LM_NEW(ParkBuilding);
    case BUILDING_PLAZA:
        return LM_NEW(PlazaBuilding);
    case BUILDING_STATUE:
        return LM_NEW(StatueBuilding);
    case BUILDING_ZOO:
        return LM_NEW(ZooBuilding);
    case BUILDING_BOTANIC:
        return LM_NEW(BotanicBuilding);
    case BUILDING_AQUARIUM:
        return LM_NEW(AquariumBuilding);
    case BUILDING_AMUSEMENT:
        return LM_NEW(AmusementBuilding);
    case BUILDING_GYM:
        return LM_NEW(GymBuilding);
    case BUILDING_STADIUM:
        return LM_NEW(StadiumBuilding);
    case BUILDING_RESORT:
        return LM_NEW(ResortBuilding);
    case BUILDING_REMAINS:
        return LM_NEW(RemainsBuilding);
    case BUILDING_SCHOOL:
        return LM_NEW(SchoolBuilding);
    case BUILDING_CLINIC:
        return LM_NEW(ClinicBuilding);
    case BUILDING_HOSPITAL:
        return LM_NEW(HospitalBuilding);
    case BUILDING_INPATIENT:
        return LM_NEW(InpatientBuilding);
    case BUILDING_SANATORIUM:
        return LM_NEW(SanatoriumBuilding);
    case BUILDING_POLICE:
        return LM_NEW(PoliceBuilding);
    case BUILDING_PRISON:
        return LM_NEW(PrisonBuilding);
    case BUILDING_FIRE:
        return LM_NEW(FireBuilding);
    case BUILDING_COURT:
        return LM_NEW(CourtBuilding);
    case BUILDING_TVSTATION:
        return LM_NEW(TVStationBuilding);
    case BUILDING_POST:
        return LM_NEW(PostBuilding);
    case BUILDING_BANK:
        return LM_NEW(BankBuilding);
    case BUILDING_STOCK:
        return LM_NEW(StockBuilding);
    case BUILDING_LIBRARY:
        return LM_NEW(LibraryBuilding);
    case BUILDING_ROADFIX:
        return LM_NEW(RoadfixBuilding);
    case BUILDING_GASOLINE:
        return LM_NEW(GasolineBuilding);
    case BUILDING_CREMATORIUM:
        return LM_NEW(CrematoriumBuilding);
    case BUILDING_CEMETRY:
        return LM_NEW(CemetryBuilding);
    case BUILDING_WATER:
        return LM_NEW(WaterBuilding);
    case BUILDING_SEWAGE:
        return LM_NEW(SewageBuilding);
    case BUILDING_POWER:
        return LM_NEW(PowerBuilding);
    case BUILDING_WINDMILL:
        return LM_NEW(WindmillBuilding);
    case BUILDING_NUCLEAR:
        return LM_NEW(NuclearBuilding);
    case BUILDING_BATTERY:
        return LM_NEW(BatteryBuilding);
    case BUILDING_DATA:
        return LM_NEW(DataBuilding);
    case BUILDING_RECYCLE:
        return LM_NEW(RecycleBuilding);
    case BUILDING_TRASH:
        return LM_NEW(TrashBuilding);
    case BUILDING_INCINERATION:
        return LM_NEW(IncinerationBuilding);
    case BUILDING_ROCKET:
        return LM_NEW(RocketBuilding);
    case BUILDING_SUBSTATION:
        return LM_NEW(SubstationBuilding);
    case BUILDING_PARKING:
        return LM_NEW(ParkingBuilding);
    case BUILDING_GUARD:
        return LM_NEW(GuardBuilding);
    case BUILDING_TOILET:
        return LM_NEW(ToiletBuilding);
    case BUILDING_CANTEEN:
        return LM_NEW(CanteenBuilding);
    case BUILDING_DORMITRY:
        return LM_NEW(DormitryBuilding);
    case BUILDING_PLAYGROUND:
        return LM_NEW(PlaygroundBuilding);
    case BUILDING_METRO:
        return LM_NEW(MetroBuilding);
    case BUILDING_TRAIN:
        return LM_NEW(TrainBuilding);
    case BUILDING_PLANE:
        return LM_NEW(PlaneBuilding);
    case BUILDING_SHIP:
        return LM_NEW(ShipBuilding);
    default:
        break;
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
        if (prob < 0.85f)return BUILDING_RESIDENT;
        else if (prob < 0.88f)return BUILDING_PACKAGE;
        else if (prob < 0.94f)return BUILDING_HOTEL;
        else return BUILDING_RESTAURANT;
    case AREA_RESIDENTM:
        if (prob < 0.55f)return BUILDING_RESIDENT;
        else if (prob < 0.80f)return BUILDING_VILLA;
        else if (prob < 0.82f)return BUILDING_PACKAGE;
        else if (prob < 0.90f)return BUILDING_HOTEL;
        else return BUILDING_RESTAURANT;
    case AREA_RESIDENTL:
        if (prob < 0.2f)return BUILDING_RESIDENT;
        else if (prob < 0.85f)return BUILDING_VILLA;
        else if (prob < 0.87f)return BUILDING_PACKAGE;
        else if (prob < 0.95f)return BUILDING_HOTEL;
        else return BUILDING_RESTAURANT;
    case AREA_COMMERCEH:
        if (prob < 0.36f)return BUILDING_MALL;
        else if (prob < 0.72f)return BUILDING_SHOP;
        else if (prob < 0.74f)return BUILDING_CARRENT;
        else if (prob < 0.77f)return BUILDING_THEATER;
        else if (prob < 0.80f)return BUILDING_MUSEUM;
        else if (prob < 0.82f)return BUILDING_CINEMA;
        else if (prob < 0.90f)return BUILDING_HOTEL;
        else if (prob < 0.98f)return BUILDING_RESTAURANT;
        else if (prob < 0.99f)return BUILDING_MASAGE;
        else return BUILDING_AMUSEMENT;
    case AREA_COMMERCEL:
        if (prob < 0.15f)return BUILDING_MALL;
        else if (prob < 0.40f)return BUILDING_SHOP;
        else if (prob < 0.42f)return BUILDING_CARRENT;
        else if (prob < 0.44f)return BUILDING_THEATER;
        else if (prob < 0.46f)return BUILDING_MUSEUM;
        else if (prob < 0.48f)return BUILDING_CINEMA;
        else if (prob < 0.60f)return BUILDING_HOTEL;
        else if (prob < 0.84f)return BUILDING_RESTAURANT;
        else if (prob < 0.87f)return BUILDING_MASAGE;
        else if (prob < 0.90f)return BUILDING_ZOO;
        else if (prob < 0.93f)return BUILDING_BOTANIC;
        else if (prob < 0.96f)return BUILDING_AQUARIUM;
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

void ResidentBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else if (GetRandom(20) == 0) {
        status = CONSTRUCTION_BREAK;
    }
    else if (GetRandom(8) == 0) {
        status = CONSTRUCTION_BUILDING;
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

    auto resident = CreateComponent<CommunityComponent>();

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
    for (auto& complement : complements) {
        complement.push_back(HomeRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
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
        status = CONSTRUCTION_BUILDING;
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

    auto villa = CreateComponent<CommunityComponent>();

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

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > villa->GetRooms().size()) {
        for (int i = villa->GetRooms().size(); i < rooms.size(); i++) {
            villa->AddRoom(rooms[i]);
        }
    }
}

vector<pair<Job*, int>> VillaBuilding::GetJobs() {
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
        status = CONSTRUCTION_BUILDING;
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
    // Parking
    // Reception
    // Bunk

    auto hotel = CreateComponent<HotelComponent>();

    float aboveScalar = 0.8f;
    float underScalar = 0.8f;

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            hotel->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    int standard = 80;
    string temp = "ushape_single";
    int face = (GetSizeX() > GetSizeY()) ?
        (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
        (GetRandom(2) ? FACE_WEST : FACE_EAST);

    hotel->AddRoom(CreateRoom<ReceptionRoom>(1, 100));

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(BunkRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > hotel->GetRooms().size()) {
        for (int i = hotel->GetRooms().size(); i < rooms.size(); i++) {
            hotel->AddRoom(rooms[i]);
        }
    }
}

vector<pair<Job*, int>> HotelBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void MallBuilding::InitBuilding() {
    if (GetRandom(10) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else if (GetRandom(8) == 0) {
        status = CONSTRUCTION_BUILDING;
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
    static vector<pair<ROOM_TYPE, float>> probs = {
        {ROOM_MARKET, 0.04f},
        {ROOM_CLOTHES, 0.24f},
        {ROOM_ANTIQUE, 0.25f},
        {ROOM_JEWERY, 0.30f},
        {ROOM_SMOKEWINETEA, 0.31f},
        {ROOM_ELECTRONIC, 0.34f},
        {ROOM_STUDIO, 0.35f},
        {ROOM_HAIRCUT, 0.40f},
        {ROOM_COSMETIC, 0.42f},
        {ROOM_PET, 0.44f},
        {ROOM_MUSIC, 0.45f},
        {ROOM_BOOK, 0.46f},
        {ROOM_CHESSCARD, 0.48f},
        {ROOM_NET, 0.50f},
        {ROOM_KTV, 0.55f},
        {ROOM_ARCADE, 0.60f},
        {ROOM_BILLIARD, 0.62f},
        {ROOM_TOY, 0.66f},
        {ROOM_RESTAURANT, 0.76f},
        {ROOM_FASTFOOD, 0.82f},
        {ROOM_BUFFET, 0.86f},
        {ROOM_DRINK, 0.92f},
        {ROOM_BAR, 0.94f},
        {ROOM_CARRENT, 0.95f},
        {ROOM_MOVIE, 0.98f},
        {ROOM_MASAGE, 1.0f},
    };
    static unordered_map<ROOM_TYPE, COMPONENT_TYPE> mapping = {
        {ROOM_MARKET, COMPONENT_SHOP},
        {ROOM_INGREDIENT, COMPONENT_SHOP},
        {ROOM_GROCERY, COMPONENT_SHOP},
        {ROOM_CLOTHES, COMPONENT_SHOP},
        {ROOM_ANTIQUE, COMPONENT_SHOP},
        {ROOM_JEWERY, COMPONENT_SHOP},
        {ROOM_SMOKEWINETEA, COMPONENT_SHOP},
        {ROOM_ELECTRONIC, COMPONENT_SHOP},
        {ROOM_STUDIO, COMPONENT_SHOP},
        {ROOM_HAIRCUT, COMPONENT_SHOP},
        {ROOM_COSMETIC, COMPONENT_SHOP},
        {ROOM_PET, COMPONENT_SHOP},
        {ROOM_COPY, COMPONENT_SHOP},
        {ROOM_MUSIC, COMPONENT_SHOP},
        {ROOM_BOOK, COMPONENT_SHOP},
        {ROOM_CHESSCARD, COMPONENT_SHOP},
        {ROOM_NET, COMPONENT_SHOP},
        {ROOM_KTV, COMPONENT_SHOP},
        {ROOM_ARCADE, COMPONENT_SHOP},
        {ROOM_BILLIARD, COMPONENT_SHOP},
        {ROOM_TOY, COMPONENT_SHOP},
        {ROOM_RESTAURANT, COMPONENT_RESTAURANT},
        {ROOM_FASTFOOD, COMPONENT_RESTAURANT},
        {ROOM_BUFFET, COMPONENT_RESTAURANT},
        {ROOM_DRINK, COMPONENT_RESTAURANT},
        {ROOM_BAR, COMPONENT_RESTAURANT},
        {ROOM_CARRENT, COMPONENT_CARRENT},
        {ROOM_MOVIE, COMPONENT_CINEMA},
        {ROOM_MASAGE, COMPONENT_MASAGE},
    };

    auto mall = CreateComponent<MallComponent>();

    float aboveScalar, underScalar;
    underScalar = 0.8f;
    if (GetAcreage() < 20000) {
        aboveScalar = 0.8f;
    }
    else if (GetAcreage() < 50000) {
        aboveScalar = 0.7f;
    }
    else {
        aboveScalar = 0.6f;
    }

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            mall->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    for (int layer = 0; layer < layers; layer++) {
        mall->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
    }

    int standard = 100;
    vector<string> temps;
    int face = GetRandom(4);

    if (GetAcreage() < 10000) {
        standard = 120;
        if (GetSizeX() / GetSizeY() > 1.8f || GetSizeY() / GetSizeX() > 1.8f)
            temps = { "circle_single" };
        else
            temps = { "circle_square" };
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);
    }
    else if (GetAcreage() < 20000) {
        standard = 160;
        if (GetSizeX() / GetSizeY() > 1.8f || GetSizeY() / GetSizeX() > 1.8f)
            temps = { "circle_double1", "circle_double2" };
        else if (GetSizeX() / GetSizeY() > 1.5f || GetSizeY() / GetSizeX() > 1.5f)
            temps = { "circle_single" };
        else
            temps = { "circle_square" };
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);
    }
    else {
        standard = 200;
        temps = { "circle_double1", "circle_double2" };
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        for (int i = 0; i < GetAcreage() / standard; i++) {
            float p = GetRandom(1000) / 1000.0f;
            ROOM_TYPE roomType = ROOM_NONE;
            for (int i = 0; i < probs.size(); i++) {
                if (p < probs[i].second) {
                    roomType = probs[i].first;
                    break;
                }
            }
            shared_ptr<Room> room = ::CreateRoom(roomType);
            complement.push_back(Room(*room));
            complement.back().SetAcreage(standard * exp(GetRandom(1000) / 1000.0f - 0.5f));
        }
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > mall->GetRooms().size()) {
        for (int i = mall->GetRooms().size(); i < rooms.size(); i++) {
            auto component = ::CreateComponent(mapping[rooms[i]->GetType()]);
            if (component) {
                component->AddRoom(rooms[i]);
                components.push_back(component);
            }
        }
    }
}

vector<pair<Job*, int>> MallBuilding::GetJobs() {
    return vector<pair<Job*, int>>();
}

void ShopBuilding::InitBuilding() {
    // 需要补充实现
}

void ShopBuilding::DistributeInside() {

}

vector<pair<Job*, int>> ShopBuilding::GetJobs() {
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
        status = CONSTRUCTION_BUILDING;
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

