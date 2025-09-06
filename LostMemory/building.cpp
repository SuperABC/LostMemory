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

void Building::TemplateLayout(vector<string> temps, FACE_DIRECTION face,
    float aboveScalar, float underScalar) {
    float aboveScalarX = aboveScalar;
    float aboveScalarY = aboveScalar;
    float underScalarX = underScalar;
    float underScalarY = underScalar;

    TemplateLayout(temps, face, aboveScalarX, aboveScalarY, underScalarX, underScalarY);
}

void Building::TemplateLayout(vector<string> temps, FACE_DIRECTION face,
    float aboveScalarX, float aboveScalarY, float underScalarX, float underScalarY) {
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
        underScalarX = 1.f - minGap / sizeX;
    }
    if (sizeY - minGap < sizeY * aboveScalarY) {
        aboveScalarY = 1.f - minGap / sizeY;
        underScalarY = 1.f - minGap / sizeY;
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

std::shared_ptr<Component> Building::CreateComponent(COMPONENT_TYPE type) {
    std::shared_ptr<Component> component = ::CreateComponent(type);
    components.push_back(component);
    return component;
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
        if (prob < 0.2f)return BUILDING_MALL;
        else if (prob < 0.56f)return BUILDING_SHOP;
        else if (prob < 0.60f)return BUILDING_CARRENT;
        else if (prob < 0.64f)return BUILDING_THEATER;
        else if (prob < 0.68f)return BUILDING_MUSEUM;
        else if (prob < 0.72f)return BUILDING_CINEMA;
        else if (prob < 0.82f)return BUILDING_HOTEL;
        else if (prob < 0.98f)return BUILDING_RESTAURANT;
        else if (prob < 0.99f)return BUILDING_MASAGE;
        else return BUILDING_AMUSEMENT;
    case AREA_COMMERCEL:
        if (prob < 0.08f)return BUILDING_MALL;
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
    int face = GetRandom(4);
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

vector<pair<shared_ptr<Job>, int>> ResidentBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> VillaBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

    hotel->AddRoom(CreateRoom<ToiletRoom>(1, 60));
    hotel->AddRoom(CreateRoom<ReceptionRoom>(1, 100));

    int standard = 80;
    string temp = "";
    int face = GetRandom(4);
    if (GetAcreage() < 5000) {
        temp = "straight_linear";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_WEST : FACE_EAST) :
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH);
    }
    else {
        temp = "ushape_single";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);
    }

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

vector<pair<shared_ptr<Job>, int>> HotelBuilding::GetJobs() {
    vector<pair<shared_ptr<Job>, int>> jobs;

    jobs.emplace_back(LM_NEW(HallManagerJob), 1);

    return jobs;
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

vector<pair<shared_ptr<Job>, int>> MallBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void ShopBuilding::InitBuilding() {
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

void ShopBuilding::DistributeInside() {
    static vector<pair<ROOM_TYPE, float>> probs_small = {
        {ROOM_GROCERY, 0.15f},
        {ROOM_INGREDIENT, 0.25f},
        {ROOM_CLOTHES, 0.45f},
        {ROOM_ANTIQUE, 0.48f},
        {ROOM_JEWERY, 0.50f},
        {ROOM_SMOKEWINETEA, 0.52f},
        {ROOM_ELECTRONIC, 0.56f},
        {ROOM_STUDIO, 0.60f},
        {ROOM_PET, 0.64f},
        {ROOM_MUSIC, 0.68f},
        {ROOM_BOOK, 0.70f},
        {ROOM_CHESSCARD, 0.74f},
        {ROOM_NET, 0.78f},
        {ROOM_KTV, 0.80f},
        {ROOM_ARCADE, 0.84f},
        {ROOM_BILLIARD, 0.88f},
        {ROOM_TOY, 0.92f},
        {ROOM_CARWASH, 0.95f},
        {ROOM_4S, 0.97f},
        {ROOM_REPAIR, 1.0f},
    };
    static vector<pair<ROOM_TYPE, float>> probs_mid = {
        {ROOM_MARKET, 0.10f},
        {ROOM_INGREDIENT, 0.15f},
        {ROOM_CLOTHES, 0.40f},
        {ROOM_ELECTRONIC, 0.45f},
        {ROOM_BOOK, 0.50f},
        {ROOM_ARCADE, 0.54f},
        {ROOM_BILLIARD, 0.58f},
        {ROOM_TOY, 0.64f},
        {ROOM_FURNITURE, 0.70f},
        {ROOM_4S, 0.92f},
        {ROOM_REPAIR, 1.0f},
    };
    static vector<pair<ROOM_TYPE, float>> probs_large = {
        {ROOM_MARKET, 0.05f},
        {ROOM_CLOTHES, 0.20f},
        {ROOM_ELECTRONIC, 0.25f},
        {ROOM_BOOK, 0.28f},
        {ROOM_FURNITURE, 0.58f},
        {ROOM_4S, 0.88f},
        {ROOM_REPAIR, 1.0f},
    };
    static vector<pair<ROOM_TYPE, float>>& probs = probs_small;

    auto shop = CreateComponent<ShopComponent>();

    float aboveScalar, underScalar;
    if (GetAcreage() < 2000) {
        aboveScalar = underScalar = 0.8f;
        probs = probs_small;
    }
    else if (GetAcreage() < 10000) {
        aboveScalar = underScalar = 0.6f;
        probs = probs_mid;
    }
    else {
        aboveScalar = underScalar = 0.5f;
        probs = probs_large;
    }

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            shop->AddRoom(CreateRoom<WarehouseRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    int standard = 1e4;
    string temp = "single_room";
    int face = GetRandom(4);

    float p = GetRandom(1000) / 1000.0f;
    ROOM_TYPE roomType = ROOM_NONE;
    for (int i = 0; i < probs.size(); i++) {
        if (p < probs[i].second) {
            roomType = probs[i].first;
            break;
        }
    }
    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        shared_ptr<Room> room = ::CreateRoom(roomType);
        complement.push_back(Room(*room));
        complement.back().SetAcreage(standard);
    }

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > shop->GetRooms().size()) {
        for (int i = shop->GetRooms().size(); i < rooms.size(); i++) {
            shop->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> ShopBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void RestaurantBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    if (area <= AREA_RESIDENTM && GetAcreage() > 5000) {
        layers = 2 + GetRandom(3);
    }
    else {
        layers = 1 + GetRandom(2);
    }
    basement = GetRandom(2);
}

void RestaurantBuilding::DistributeInside() {
    static vector<pair<ROOM_TYPE, float>> probs_small = {
        {ROOM_RESTAURANT, 0.2f},
        {ROOM_FASTFOOD, 0.5f},
        {ROOM_BUFFET, 0.7f},
        {ROOM_BAR, 1.0f},
    };
    static vector<pair<ROOM_TYPE, float>> probs_mid = {
        {ROOM_RESTAURANT, 0.4f},
        {ROOM_FASTFOOD, 0.7f},
        {ROOM_BUFFET, 1.0f},
    };
    static vector<pair<ROOM_TYPE, float>> probs_large = {
        {ROOM_RESTAURANT, 0.8f},
        {ROOM_BUFFET, 1.0f},
    };
    static vector<pair<ROOM_TYPE, float>>& probs = probs_small;

    auto restaurant = CreateComponent<RestaurantComponent>();

    float aboveScalar, underScalar;
    if (GetAcreage() < 2000) {
        aboveScalar = underScalar = 0.8f;
        probs = probs_small;
    }
    else if (GetAcreage() < 5000) {
        aboveScalar = underScalar = 0.7f;
        probs = probs_mid;
    }
    else {
        aboveScalar = underScalar = 0.6f;
        probs = probs_large;
    }

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            restaurant->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    int standard = 1e4;
    string temp = "single_room";
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
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
        complement.back().SetAcreage(standard);
    }

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > restaurant->GetRooms().size()) {
        for (int i = restaurant->GetRooms().size(); i < rooms.size(); i++) {
            restaurant->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> RestaurantBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
        basement = 0;
    }
    else {
        layers = 1 + GetRandom(2);
        basement = 1 + GetRandom(3);
    }
}

void CarRentBuilding::DistributeInside() {
    // Parking
    // Reception
    // Office

    auto carrent = CreateComponent<CarrentComponent>();

    float aboveScalar, underScalar;
    if (GetAcreage() < 10000) {
        aboveScalar = underScalar = 0.8f;
    }
    else {
        aboveScalar = underScalar = 0.4f;
    }

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            carrent->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    carrent->AddRoom(CreateRoom<ReceptionRoom>(1, 1e4));

    int standard = 120;
    vector<string> temps = { "single_room", "straight_linear" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(OfficeRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > carrent->GetRooms().size()) {
        for (int i = carrent->GetRooms().size(); i < rooms.size(); i++) {
            carrent->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> CarRentBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Parking
    // Stage

    auto theater = CreateComponent<TheaterComponent>();

    float aboveScalar, underScalar;
    if (GetAcreage() < 5000) {
        aboveScalar = underScalar = 0.8f;
    }
    else {
        aboveScalar = underScalar = 0.6f;
    }

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            theater->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    int standard = 1e4;
    vector<string> temps = { "single_room"  };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(StageRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > theater->GetRooms().size()) {
        for (int i = theater->GetRooms().size(); i < rooms.size(); i++) {
            theater->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> TheaterBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Parking
    // Reception
    // Toilet
    // Movie

    auto cinema = CreateComponent<CinemaComponent>();

    float aboveScalar, underScalar;
    if (GetAcreage() < 10000) {
        aboveScalar = underScalar = 0.8f;
    }
    else {
        aboveScalar = underScalar = 0.6f;
    }

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            cinema->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    for (int layer = 0; layer < layers; layer++) {
        cinema->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 1e4));
        cinema->AddRoom(CreateRoom<ReceptionRoom>(layer + 1, 1e4));
    }


    int standard = 400;
    vector<string> temps = { "pile_double" };
    int face = (GetSizeX() > GetSizeY()) ?
        (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
        (GetRandom(2) ? FACE_WEST : FACE_EAST);

    float aboveScalarX = aboveScalar;
    float aboveScalarY = aboveScalar;
    float underScalarX = underScalar;
    float underScalarY = underScalar;
    if (face == FACE_NORTH || face == FACE_SOUTH) {
        aboveScalarY = min(aboveScalarY, 4.0f / GetSizeY());
    }
    else {
        aboveScalarX = min(aboveScalarY, 4.0f / GetSizeX());
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(MovieRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalarX, aboveScalarY, underScalarX, underScalarY);
    if (rooms.size() > cinema->GetRooms().size()) {
        for (int i = cinema->GetRooms().size(); i < rooms.size(); i++) {
            cinema->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> CinemaBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
}

void MuseumBuilding::DistributeInside() {
    // Reception
    // Toilet
    // Exhibition

    auto museum = CreateComponent<MuseumComponent>();

    float aboveScalar, underScalar;
    if (GetAcreage() < 10000) {
        aboveScalar = underScalar = 0.8f;
    }
    else {
        aboveScalar = underScalar = 0.6f;
    }

    int standard = 400;
    string temp = "";
    int face = GetRandom(4);

    if (GetAcreage() < 10000) {
        standard = 400;
        temp = "straight_linear";
        face = (GetSizeX() < GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);
    }
    else {
        standard = 600;
        if (GetSizeX() / GetSizeY() > 1.8f || GetSizeY() / GetSizeX() > 1.8f) {
            temp = "straight_linear";
            face = (GetSizeX() < GetSizeY()) ?
                (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
                (GetRandom(2) ? FACE_WEST : FACE_EAST);
        }
        else {
            temp = "ushape_single";
            face = (GetSizeX() > GetSizeY()) ?
                (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
                (GetRandom(2) ? FACE_WEST : FACE_EAST);

            for (int layer = 0; layer < layers; layer++) {
                museum->AddRoom(CreateRoom<ReceptionRoom>(layer + 1, standard));
            }
        }
    }

    for (int layer = 0; layer < layers; layer++) {
        museum->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(ExhibitionRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > museum->GetRooms().size()) {
        for (int i = museum->GetRooms().size(); i < rooms.size(); i++) {
            museum->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> MuseumBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Parking
    // Reception
    // Toilet
    // Masage
    // Sauna
    // Bath

    auto masage = CreateComponent<MasageComponent>();

    float aboveScalar = 0.6f, underScalar = 0.6f;

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            masage->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    int standard = 80;
    string temp = "";
    int face = GetRandom(4);

    if (GetAcreage() < 2000) {
        temp = "pile_double";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);

        masage->AddRoom(CreateRoom<ToiletRoom>(1, standard));
        masage->AddRoom(CreateRoom<ReceptionRoom>(1, standard));
        masage->AddRoom(CreateRoom<BathRoom>(1, GetAcreage() * 0.36 * 0.4));
        masage->AddRoom(CreateRoom<BathRoom>(1, GetAcreage() * 0.36 * 0.4));
    }
    else if (GetAcreage() < 8000) {
        temp = "straight_linear";
        face = (GetSizeX() < GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);

        masage->AddRoom(CreateRoom<ReceptionRoom>(1, 1e4));
        masage->AddRoom(CreateRoom<ToiletRoom>(1, GetAcreage() * 0.36 * 0.4 * 0.1));
        masage->AddRoom(CreateRoom<BathRoom>(1, GetAcreage() * 0.36 * 0.4 * 0.3));
        masage->AddRoom(CreateRoom<SaunaRoom>(1, GetAcreage() * 0.36 * 0.4 * 0.15));
        masage->AddRoom(CreateRoom<BathRoom>(1, GetAcreage() * 0.36 * 0.4 * 0.3));
        masage->AddRoom(CreateRoom<SaunaRoom>(1, GetAcreage() * 0.36 * 0.4 * 0.15));
    }
    else {
        temp = "ushape_single";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);

        masage->AddRoom(CreateRoom<ReceptionRoom>(1, 1e4));
        masage->AddRoom(CreateRoom<ToiletRoom>(1, 1e4));
        masage->AddRoom(CreateRoom<BathRoom>(1, 1e4));
        masage->AddRoom(CreateRoom<SaunaRoom>(1, 1e4));
        masage->AddRoom(CreateRoom<BathRoom>(1, 1e4));
        masage->AddRoom(CreateRoom<SaunaRoom>(1, 1e4));
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(MasageRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > masage->GetRooms().size()) {
        for (int i = masage->GetRooms().size(); i < rooms.size(); i++) {
            masage->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> MasageBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    //Package

    auto package = CreateComponent<PackageComponent>();

    float aboveScalar = 0.6f, underScalar = 0.6f;

    int standard = 1e4;
    string temp = "single_room";
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(WarehouseRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > package->GetRooms().size()) {
        for (int i = package->GetRooms().size(); i < rooms.size(); i++) {
            package->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> PackageBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    static vector<pair<COMPONENT_TYPE, float>> probs_individual = {
        {COMPONENT_FURNISH, 0.05f},
        {COMPONENT_MOVING, 0.07f},
        {COMPONENT_OPERATOR, 0.08f},
        {COMPONENT_GAME, 0.15f},
        {COMPONENT_INTERNET, 0.25f},
        {COMPONENT_LEASE, 0.27f},
        {COMPONENT_FINANCE, 0.30f},
        {COMPONENT_LENDING, 0.32f},
        {COMPONENT_SALE, 0.42f},
        {COMPONENT_MEDICAL, 0.46f},
        {COMPONENT_RELATION, 0.48f},
        {COMPONENT_ESHOP, 0.54f},
        {COMPONENT_STAR, 0.55f},
        {COMPONENT_ENGINEER, 0.58f},
        {COMPONENT_CONSTRUCT, 0.62f},
        {COMPONENT_ART, 0.65f},
        {COMPONENT_PUBLISHER, 0.67f},
        {COMPONENT_TRAVEL, 0.69f},
        {COMPONENT_MEDIA, 0.77f},
        {COMPONENT_LAWYER, 0.82f},
        {COMPONENT_CREW, 0.83f},
        {COMPONENT_INSURANCE, 0.87f},
        {COMPONENT_SECURITY, 0.90f},
        {COMPONENT_CLEANING, 0.94f},
        {COMPONENT_GREEN, 0.96f},
        {COMPONENT_INTERMEDIARY, 1.0f},
    };
    static vector<pair<COMPONENT_TYPE, float>> probs_clustered = {
        {COMPONENT_GAME, 0.30f},
        {COMPONENT_MEDICAL, 0.36f},
        {COMPONENT_ESHOP, 0.46f},
        {COMPONENT_FINANCE, 0.52f},
        {COMPONENT_ENGINEER, 0.62f},
        {COMPONENT_CONSTRUCT, 0.70f},
        {COMPONENT_ART, 0.75f},
        {COMPONENT_PUBLISHER, 0.80f},
        {COMPONENT_OPERATOR, 0.84f},
        {COMPONENT_SALE, 0.96f},
        {COMPONENT_SECURITY, 1.0f}
    };
    static unordered_map<COMPONENT_TYPE, int> spaces = {
        {COMPONENT_FURNISH, 20},
        {COMPONENT_MOVING, 50},
        {COMPONENT_OPERATOR, 40},
        {COMPONENT_GAME, 100},
        {COMPONENT_INTERNET, 120},
        {COMPONENT_LEASE, 20},
        {COMPONENT_FINANCE, 100},
        {COMPONENT_LENDING, 50},
        {COMPONENT_SALE, 80},
        {COMPONENT_MEDICAL, 120},
        {COMPONENT_RELATION, 20},
        {COMPONENT_ESHOP, 20},
        {COMPONENT_STAR, 10},
        {COMPONENT_ENGINEER, 80},
        {COMPONENT_CONSTRUCT, 40},
        {COMPONENT_ART, 20},
        {COMPONENT_PUBLISHER, 100},
        {COMPONENT_TRAVEL, 40},
        {COMPONENT_MEDIA, 10},
        {COMPONENT_LAWYER, 50},
        {COMPONENT_CREW, 80},
        {COMPONENT_INSURANCE, 120},
        {COMPONENT_SECURITY, 80},
        {COMPONENT_CLEANING, 20},
        {COMPONENT_GREEN, 40},
        {COMPONENT_INTERMEDIARY, 10},
    };

    auto office = CreateComponent<OfficeComponent>();

    float aboveScalar = 0.8f, underScalar = 0.8f;

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            office->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    for (int layer = 0; layer < layers; layer++) {
        office->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 80));
    }

    int standard = 320;
    vector<string> temps;
    int face = GetRandom(4);

    if (GetAcreage() < 8000) {
        standard = 320;
        if (GetSizeX() / GetSizeY() > 1.5f || GetSizeY() / GetSizeX() > 1.5f) {
            temps = { "straight_linear" };
            face = (GetSizeX() < GetSizeY()) ?
                (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
                (GetRandom(2) ? FACE_WEST : FACE_EAST);
        }
        else {
            temps = { "fence_double" };
            face = (GetSizeX() > GetSizeY()) ?
                (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
                (GetRandom(2) ? FACE_WEST : FACE_EAST);
        }
    }
    else {
        standard = 480;
        if (GetRandom(2)) {
            temps = { "rotate_along" };
        }
        else {
            temps = { "rotate_inverse" };
        }
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        for (int i = 0; i < 20; i++) {
            complement.push_back(OfficeRoom());
            complement.back().SetAcreage(standard * exp(GetRandom(1000) / 1000.0f - 0.5f));
        }
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    Component* component = nullptr;
    int num = 0;
    if (rooms.size() > office->GetRooms().size()) {
        for (int i = office->GetRooms().size(); i < rooms.size(); i++) {
            if (component == nullptr) {
                float p = GetRandom(1000) / 1000.0f;
                int sample = 0;
                while(sample < probs_individual.size()) {
                    if (p < probs_individual[sample].second) {
                        break;
                    }
                    sample++;
                }
                component = CreateComponent(probs_individual[sample].first).get();
                num = spaces[probs_individual[sample].first] * exp(GetRandom(1000) / 1000.0f - 0.5f) / 20;
            }

            component->AddRoom(rooms[i]);
            num--;

            if (num <= 0) {
                component = nullptr;
                num = 0;
            }
        }
    }
}

vector<pair<shared_ptr<Job>, int>> OfficeBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    basement = 0;
}

void LabBuilding::DistributeInside() {
    static vector<pair<COMPONENT_TYPE, float>> probs = {
        {COMPONENT_SCIENCEDEPT, 0.3f},
        {COMPONENT_ENGINEERDEPT, 0.8f},
        {COMPONENT_SOCIALDEPT, 0.95f},
        {COMPONENT_COMMITTEE, 1.0f},
    };
    static unordered_map<COMPONENT_TYPE, int> spaces = {
        {COMPONENT_SCIENCEDEPT, 60},
        {COMPONENT_ENGINEERDEPT, 100},
        {COMPONENT_SOCIALDEPT, 40},
        {COMPONENT_COMMITTEE, 20},
    };

    auto lab = CreateComponent<LabComponent>();

    float aboveScalar = 0.8f, underScalar = 0.8f;

    for (int layer = 0; layer < layers; layer++) {
        lab->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 80));
    }

    int standard = 320;
    vector<string> temps;
    int face = GetRandom(4);

    if (GetAcreage() < 8000) {
        standard = 320;
        if (GetSizeX() / GetSizeY() > 1.5f || GetSizeY() / GetSizeX() > 1.5f) {
            temps = { "straight_linear" };
            face = (GetSizeX() < GetSizeY()) ?
                (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
                (GetRandom(2) ? FACE_WEST : FACE_EAST);
        }
        else {
            temps = { "fence_double" };
            face = (GetSizeX() > GetSizeY()) ?
                (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
                (GetRandom(2) ? FACE_WEST : FACE_EAST);
        }
    }
    else {
        standard = 480;
        if (GetRandom(2)) {
            temps = { "rotate_along" };
        }
        else {
            temps = { "rotate_inverse" };
        }
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        for (int i = 0; i < 20; i++) {
            complement.push_back(OfficeRoom());
            complement.back().SetAcreage(standard * exp(GetRandom(1000) / 1000.0f - 0.5f));
        }
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    Component* component = nullptr;
    int num = 0;
    if (rooms.size() > lab->GetRooms().size()) {
        for (int i = lab->GetRooms().size(); i < rooms.size(); i++) {
            if (component == nullptr) {
                float p = GetRandom(1000) / 1000.0f;
                int sample = 0;
                while (sample < probs.size()) {
                    if (p < probs[sample].second) {
                        break;
                    }
                    sample++;
                }
                component = CreateComponent(probs[sample].first).get();
                num = spaces[probs[sample].first] * exp(GetRandom(1000) / 1000.0f - 0.5f) / 20;
            }

            component->AddRoom(rooms[i]);
            num--;

            if (num <= 0) {
                component = nullptr;
                num = 0;
            }
        }
    }
}

vector<pair<shared_ptr<Job>, int>> LabBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    static vector<pair<COMPONENT_TYPE, float>> probs = {
        {COMPONENT_EDUCATIONDEPT, 0.15f},
        {COMPONENT_INFODEPT, 0.25f},
        {COMPONENT_FINANCEDEPT, 0.35f},
        {COMPONENT_TRADEDEPT, 0.45f},
        {COMPONENT_PETITIONDEPT, 0.55f},
        {COMPONENT_WEATHERDEPT, 0.60f},
        {COMPONENT_TAXDEPT, 0.70f},
        {COMPONENT_CIVILDEPT, 0.90f},
        {COMPONENT_DOGE, 1.0f},
    };
    static unordered_map<COMPONENT_TYPE, int> spaces = {
        {COMPONENT_EDUCATIONDEPT, 60},
        {COMPONENT_INFODEPT, 80},
        {COMPONENT_FINANCEDEPT, 40},
        {COMPONENT_TRADEDEPT, 50},
        {COMPONENT_PETITIONDEPT, 40},
        {COMPONENT_WEATHERDEPT, 20},
        {COMPONENT_TAXDEPT, 20},
        {COMPONENT_CIVILDEPT, 40},
        {COMPONENT_DOGE, 20},
    };

    auto government = CreateComponent<LabComponent>();

    float aboveScalar = 0.8f, underScalar = 0.8f;

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            government->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    for (int layer = 0; layer < layers; layer++) {
        government->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 80));
    }

    int standard = 320;
    vector<string> temps;
    int face = GetRandom(4);

    if (GetAcreage() < 8000) {
        standard = 320;
        if (GetSizeX() / GetSizeY() > 1.5f || GetSizeY() / GetSizeX() > 1.5f) {
            temps = { "straight_linear" };
            face = (GetSizeX() < GetSizeY()) ?
                (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
                (GetRandom(2) ? FACE_WEST : FACE_EAST);
        }
        else {
            temps = { "fence_double" };
            face = (GetSizeX() > GetSizeY()) ?
                (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
                (GetRandom(2) ? FACE_WEST : FACE_EAST);
        }
    }
    else {
        standard = 480;
        if (GetRandom(2)) {
            temps = { "rotate_along" };
        }
        else {
            temps = { "rotate_inverse" };
        }
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        for (int i = 0; i < 20; i++) {
            complement.push_back(OfficeRoom());
            complement.back().SetAcreage(standard * exp(GetRandom(1000) / 1000.0f - 0.5f));
        }
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    Component* component = nullptr;
    int num = 0;
    if (rooms.size() > government->GetRooms().size()) {
        for (int i = government->GetRooms().size(); i < rooms.size(); i++) {
            if (component == nullptr) {
                float p = GetRandom(1000) / 1000.0f;
                int sample = 0;
                while (sample < probs.size()) {
                    if (p < probs[sample].second) {
                        break;
                    }
                    sample++;
                }
                component = CreateComponent(probs[sample].first).get();
                num = spaces[probs[sample].first] * exp(GetRandom(1000) / 1000.0f - 0.5f) / 20;
            }

            component->AddRoom(rooms[i]);
            num--;

            if (num <= 0) {
                component = nullptr;
                num = 0;
            }
        }
    }
}

vector<pair<shared_ptr<Job>, int>> GovernmentBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Factory

    auto factory = CreateComponent<FactoryComponent>();

    float aboveScalar = 0.8f, underScalar = 0.8f;

    int standard = 1e5;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        if(GetRandom(2))
            complement.push_back(MachineRoom());
        else
            complement.push_back(PipelineRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > factory->GetRooms().size()) {
        for (int i = factory->GetRooms().size(); i < rooms.size(); i++) {
            factory->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> FactoryBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Factory

    auto warehouse = CreateComponent<WarehouseComponent>();

    float aboveScalar = 0.8f, underScalar = 0.8f;

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            warehouse->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    int standard = 1e5;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(WarehouseRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > warehouse->GetRooms().size()) {
        for (int i = warehouse->GetRooms().size(); i < rooms.size(); i++) {
            warehouse->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> WarehouseBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Mining

    auto resource = CreateComponent<ResourceComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(MiningRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > resource->GetRooms().size()) {
        for (int i = resource->GetRooms().size(); i < rooms.size(); i++) {
            resource->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> MiningBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Oiling

    auto resource = CreateComponent<ResourceComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(OilingRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > resource->GetRooms().size()) {
        for (int i = resource->GetRooms().size(); i < rooms.size(); i++) {
            resource->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> OilingBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Quarry

    auto resource = CreateComponent<ResourceComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(QuarryRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > resource->GetRooms().size()) {
        for (int i = resource->GetRooms().size(); i < rooms.size(); i++) {
            resource->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> QuarryBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Farm

    auto resource = CreateComponent<ResourceComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(FarmRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > resource->GetRooms().size()) {
        for (int i = resource->GetRooms().size(); i < rooms.size(); i++) {
            resource->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> FarmBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Pasture

    auto resource = CreateComponent<ResourceComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(PastureRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > resource->GetRooms().size()) {
        for (int i = resource->GetRooms().size(); i < rooms.size(); i++) {
            resource->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> PastureBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Breeding

    auto resource = CreateComponent<ResourceComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(BreedingRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > resource->GetRooms().size()) {
        for (int i = resource->GetRooms().size(); i < rooms.size(); i++) {
            resource->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> BreedingBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Fishing

    auto resource = CreateComponent<ResourceComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(FishingRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > resource->GetRooms().size()) {
        for (int i = resource->GetRooms().size(); i < rooms.size(); i++) {
            resource->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> FishingBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Orchard

    auto resource = CreateComponent<ResourceComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(OrchardRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > resource->GetRooms().size()) {
        for (int i = resource->GetRooms().size(); i < rooms.size(); i++) {
            resource->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> OrchardBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Forest

    auto resource = CreateComponent<ResourceComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(ForestRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > resource->GetRooms().size()) {
        for (int i = resource->GetRooms().size(); i < rooms.size(); i++) {
            resource->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> ForestBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void ParkBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1 + GetRandom(4);
    basement = GetRandom(3);
}

void ParkBuilding::DistributeInside() {
    // Parking

    auto parking = CreateComponent<ParkingComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            parking->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(ParkingRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > parking->GetRooms().size()) {
        for (int i = parking->GetRooms().size(); i < rooms.size(); i++) {
            parking->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> ParkBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void PlazaBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void PlazaBuilding::DistributeInside() {
    // Plaza

    auto plaza = CreateComponent<PlazaComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(PlazaRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > plaza->GetRooms().size()) {
        for (int i = plaza->GetRooms().size(); i < rooms.size(); i++) {
            plaza->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> PlazaBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void StatueBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void StatueBuilding::DistributeInside() {
    // Statue

    auto statue = CreateComponent<StatueComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(StatueRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > statue->GetRooms().size()) {
        for (int i = statue->GetRooms().size(); i < rooms.size(); i++) {
            statue->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> StatueBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Zoo

    auto zoo = CreateComponent<ZooComponent>();

    float aboveScalar = 0.8f, underScalar = 0.8f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(AnimalRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > zoo->GetRooms().size()) {
        for (int i = zoo->GetRooms().size(); i < rooms.size(); i++) {
            zoo->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> ZooBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Botanic

    auto botanic = CreateComponent<BotanicComponent>();

    float aboveScalar = 0.8f, underScalar = 0.8f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(PlantRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > botanic->GetRooms().size()) {
        for (int i = botanic->GetRooms().size(); i < rooms.size(); i++) {
            botanic->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> BotanicBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Aquarium

    auto aquarium = CreateComponent<AquariumComponent>();

    float aboveScalar = 0.8f, underScalar = 0.8f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(AquariumRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > aquarium->GetRooms().size()) {
        for (int i = aquarium->GetRooms().size(); i < rooms.size(); i++) {
            aquarium->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> AquariumBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void AmusementBuilding::InitBuilding() {
    if (GetRandom(5) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
}

void AmusementBuilding::DistributeInside() {
    // Amusement

    auto amusement = CreateComponent<AmusementComponent>();

    float aboveScalar = 0.8f, underScalar = 0.8f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(AmusementRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > amusement->GetRooms().size()) {
        for (int i = amusement->GetRooms().size(); i < rooms.size(); i++) {
            amusement->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> AmusementBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Gym

    auto gym = CreateComponent<GymComponent>();

    float aboveScalar = 0.8f, underScalar = 0.8f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(AmusementRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > gym->GetRooms().size()) {
        for (int i = gym->GetRooms().size(); i < rooms.size(); i++) {
            gym->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> GymBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    static vector<pair<ROOM_TYPE, float>> probs = {
        {ROOM_BASKETBALL, 0.20f},
        {ROOM_VOLLEYBALL, 0.25f},
        {ROOM_BADMINTON, 0.30f},
        {ROOM_TABLETENNIS, 0.50f},
        {ROOM_TENNIS, 0.60f},
        {ROOM_SKATE, 0.65f},
        {ROOM_BOWLING, 0.70f},
        {ROOM_ARCHERY, 0.75f},
        {ROOM_RANGE, 0.80f},
        {ROOM_POOL, 1.0f},
    };

    auto stadium = CreateComponent<StadiumComponent>();

    float aboveScalar, underScalar;
    if (GetAcreage() < 20000) {
        aboveScalar = underScalar = 0.8f;
    }
    else if (GetAcreage() < 50000) {
        aboveScalar = underScalar = 0.7f;
    }
    else {
        aboveScalar = underScalar = 0.6f;
    }

    for (int layer = 0; layer < layers; layer++) {
        stadium->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 320));
    }

    int standard = 600;
    string temp;
    int face = GetRandom(4);
    complements = vector<vector<Room>>(basement + layers + 1);

    if (GetAcreage() < 20000) {
        standard = 1e5;
        temp = "single_room";
        for (auto& complement : complements) {
            complement.push_back(FootballRoom());
            complement.back().SetAcreage(standard);
        }
    }
    else if (GetAcreage() < 50000) {
        standard = 800;
        if (GetRandom(2)) {
            temp = "pile_double";
            face = (GetSizeX() > GetSizeY()) ?
                (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
                (GetRandom(2) ? FACE_WEST : FACE_EAST);
        }
        else {
            temp = "straight_linear";
            face = (GetSizeX() < GetSizeY()) ?
                (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
                (GetRandom(2) ? FACE_WEST : FACE_EAST);
        }
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
    }
    else {
        standard = 1000;
        if (GetRandom(2)) {
            temp = "rotate_along";
        }
        else {
            temp = "rotate_inverse";
        }
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
    }

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > stadium->GetRooms().size()) {
        for (int i = stadium->GetRooms().size(); i < rooms.size(); i++) {
            stadium->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> StadiumBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void ResortBuilding::InitBuilding() {
    if (GetRandom(20) == 0) {
        status = CONSTRUCTION_ABANDON;
    }
    else {
        status = CONSTRUCTION_USING;
    }
    layers = 1;
}

void ResortBuilding::DistributeInside() {
    // Resort

    auto resort = CreateComponent<ResortComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(ResortRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > resort->GetRooms().size()) {
        for (int i = resort->GetRooms().size(); i < rooms.size(); i++) {
            resort->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> ResortBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void RemainsBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
}

void RemainsBuilding::DistributeInside() {
    // Remains

    auto remains = CreateComponent<RemainsComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(RemainsRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > remains->GetRooms().size()) {
        for (int i = remains->GetRooms().size(); i < rooms.size(); i++) {
            remains->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> RemainsBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
}

void SchoolBuilding::DistributeInside() {
    // Class
    // Office

    shared_ptr<Component> school;
    if (zone != ZONE_NONE) {
        school = CreateComponent<UniversityComponent>();
    }
    else {
        if (GetAcreage() < 4000) {
            school = CreateComponent<KinderComponent>();
        }
        else if (GetAcreage() < 8000) {
            if (GetRandom(3)) {
                school = CreateComponent<PrimaryComponent>();
            }
            else {
                school = CreateComponent<KinderComponent>();
            }
        }
        else if(GetAcreage() < 15000) {
            if (GetRandom(3)) {
                school = CreateComponent<MiddleComponent>();
            }
            else {
                school = CreateComponent<PrimaryComponent>();
            }
        }
        else {
            if (GetRandom(4)) {
                school = CreateComponent<VocationalComponent>();
            }
            else {
                school = CreateComponent<MiddleComponent>();
            }
        }
    }

    float aboveScalar = 0.8f;
    float underScalar = 0.8f;

    for (int layer = 0; layer < layers; layer++) {
        school->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
        school->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 120));
        school->AddRoom(CreateRoom<OfficeRoom>(layer + 1, 120));
    }

    int standard = 160;
    string temp = "";
    int face = GetRandom(4);
    if (GetAcreage() < 10000) {
        temp = "straight_linear";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_WEST : FACE_EAST) :
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH);
    }
    else {
        temp = "ushape_single";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(ClassRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > school->GetRooms().size()) {
        for (int i = school->GetRooms().size(); i < rooms.size(); i++) {
            school->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> SchoolBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Parking
    // Reception
    // Toilet
    // Doctor

    auto clinic = CreateComponent<ClinicComponent>();

    float aboveScalar, underScalar;
    if (GetAcreage() < 5000) {
        aboveScalar = underScalar = 0.8f;
    }
    else {
        aboveScalar = underScalar = 0.6f;
    }

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            clinic->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    for (int layer = 0; layer < layers; layer++) {
        clinic->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 1e4));
        clinic->AddRoom(CreateRoom<ReceptionRoom>(layer + 1, 1e4));
    }

    int standard = 80;
    vector<string> temps = { "pile_double" };
    int face = (GetSizeX() > GetSizeY()) ?
        (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
        (GetRandom(2) ? FACE_WEST : FACE_EAST);

    float aboveScalarX = aboveScalar;
    float aboveScalarY = aboveScalar;
    float underScalarX = underScalar;
    float underScalarY = underScalar;
    if (face == FACE_NORTH || face == FACE_SOUTH) {
        aboveScalarY = min(aboveScalarY, 4.0f / GetSizeY());
    }
    else {
        aboveScalarX = min(aboveScalarY, 4.0f / GetSizeX());
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(DoctorRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalarX, aboveScalarY, underScalarX, underScalarY);
    if (rooms.size() > clinic->GetRooms().size()) {
        for (int i = clinic->GetRooms().size(); i < rooms.size(); i++) {
            clinic->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> ClinicBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Parking
    // Motuary
    // Reception
    // Toilet
    // Emergency
    // Outpatient
    // Operation
    // ICU
    // Doctor
    // Assay

    auto hospital = CreateComponent<HospitalComponent>();

    float aboveScalar = 0.8f;
    float underScalar = 0.8f;

    if (basement > 1) {
        for (int i = 1; i < basement; i++)
            hospital->AddRoom(CreateRoom<MotuaryRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }
    if (basement > 0) {
        for (int i = 0; i < 1; i++)
            hospital->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    for (int layer = 0; layer < layers; layer++) {
        hospital->AddRoom(CreateRoom<ReceptionRoom>(layer + 1, 120));
        hospital->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
    }

    hospital->AddRoom(CreateRoom<EmergencyRoom>(1, 80));
    hospital->AddRoom(CreateRoom<OutpatientRoom>(1, 80));
    hospital->AddRoom(CreateRoom<AssayRoom>(1, 120));
    hospital->AddRoom(CreateRoom<EmergencyRoom>(1, 80));
    hospital->AddRoom(CreateRoom<OutpatientRoom>(1, 80));
    hospital->AddRoom(CreateRoom<EmergencyRoom>(1, 80));
    hospital->AddRoom(CreateRoom<OutpatientRoom>(1, 80));
    hospital->AddRoom(CreateRoom<EmergencyRoom>(1, 80));
    hospital->AddRoom(CreateRoom<OutpatientRoom>(1, 80));
    hospital->AddRoom(CreateRoom<OperationRoom>(2, 80));
    hospital->AddRoom(CreateRoom<IcuRoom>(2, 80));
    hospital->AddRoom(CreateRoom<OperationRoom>(2, 80));
    hospital->AddRoom(CreateRoom<IcuRoom>(2, 80));
    hospital->AddRoom(CreateRoom<OperationRoom>(2, 80));
    hospital->AddRoom(CreateRoom<IcuRoom>(2, 80));
    hospital->AddRoom(CreateRoom<OperationRoom>(2, 80));
    hospital->AddRoom(CreateRoom<IcuRoom>(2, 80));
    
    int standard = 80;
    string temp = "";
    int face = GetRandom(4);
    if (GetAcreage() < 5000) {
        temp = "straight_linear";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_WEST : FACE_EAST) :
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH);
    }
    else {
        temp = "ushape_single";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(DoctorRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > hospital->GetRooms().size()) {
        for (int i = hospital->GetRooms().size(); i < rooms.size(); i++) {
            hospital->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> HospitalBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Parking
    // Reception
    // Bunk

    auto inpatient = CreateComponent<InpatientComponent>();

    float aboveScalar = 0.8f;
    float underScalar = 0.8f;

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            inpatient->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    for (int layer = 0; layer < layers; layer++) {
        inpatient->AddRoom(CreateRoom<ReceptionRoom>(layer + 1, 120));
        inpatient->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
    }

    int standard = 80;
    string temp = "";
    int face = GetRandom(4);
    if (GetAcreage() < 5000) {
        temp = "straight_linear";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_WEST : FACE_EAST) :
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH);
    }
    else {
        temp = "ushape_single";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(BunkRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > inpatient->GetRooms().size()) {
        for (int i = inpatient->GetRooms().size(); i < rooms.size(); i++) {
            inpatient->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> InpatientBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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
    // Parking
    // Reception
    // Bunk

    auto sanatorium = CreateComponent<SanatoriumComponent>();

    float aboveScalar = 0.8f;
    float underScalar = 0.8f;

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            sanatorium->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    for (int layer = 0; layer < layers; layer++) {
        sanatorium->AddRoom(CreateRoom<ReceptionRoom>(layer + 1, 120));
        sanatorium->AddRoom(CreateRoom<ToiletRoom>(layer + 1, 60));
    }

    int standard = 80;
    string temp = "";
    int face = GetRandom(4);
    if (GetAcreage() < 5000) {
        temp = "straight_linear";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_WEST : FACE_EAST) :
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH);
    }
    else {
        temp = "ushape_single";
        face = (GetSizeX() > GetSizeY()) ?
            (GetRandom(2) ? FACE_NORTH : FACE_SOUTH) :
            (GetRandom(2) ? FACE_WEST : FACE_EAST);
    }

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(BunkRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout({ temp }, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > sanatorium->GetRooms().size()) {
        for (int i = sanatorium->GetRooms().size(); i < rooms.size(); i++) {
            sanatorium->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> SanatoriumBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> PoliceBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> PrisonBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> FireBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> CourtBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> TVStationBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> PostBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> BankBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> StockBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> LibraryBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void RoadfixBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1 + GetRandom(2);
    basement = 1 + GetRandom(2);
}

void RoadfixBuilding::DistributeInside() {

}

vector<pair<shared_ptr<Job>, int>> RoadfixBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> GasolineBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> CrematoriumBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void CemetryBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void CemetryBuilding::DistributeInside() {

}

vector<pair<shared_ptr<Job>, int>> CemetryBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> WaterBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> SewageBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> PowerBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> WindmillBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> NuclearBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> BatteryBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> DataBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> RecycleBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> TrashBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> IncinerationBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> RocketBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void SubstationBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void SubstationBuilding::DistributeInside() {

}

vector<pair<shared_ptr<Job>, int>> SubstationBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void ParkingBuilding::InitBuilding() {
    status = CONSTRUCTION_USING;
    layers = 1;
    basement = 0;
}

void ParkingBuilding::DistributeInside() {
    // Park

    auto park = CreateComponent<ParkComponent>();

    float aboveScalar = 1.0f, underScalar = 1.0f;

    if (basement > 0) {
        for (int i = 0; i < basement; i++)
            park->AddRoom(CreateRoom<ParkingRoom>(-i - 1, GetAcreage() * underScalar * underScalar));
    }

    int standard = 1e6;
    vector<string> temps = { "single_room" };
    int face = GetRandom(4);

    complements = vector<vector<Room>>(basement + layers + 1);
    for (auto& complement : complements) {
        complement.push_back(ParkRoom());
        complement.back().SetAcreage(standard);
    }

    TemplateLayout(temps, (FACE_DIRECTION)face, aboveScalar, underScalar);
    if (rooms.size() > park->GetRooms().size()) {
        for (int i = park->GetRooms().size(); i < rooms.size(); i++) {
            park->AddRoom(rooms[i]);
        }
    }
}

vector<pair<shared_ptr<Job>, int>> ParkingBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> GuardBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> ToiletBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> CanteenBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> DormitryBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
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

vector<pair<shared_ptr<Job>, int>> PlaygroundBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void MetroBuilding::InitBuilding() {

}

void MetroBuilding::DistributeInside() {

}

vector<pair<shared_ptr<Job>, int>> MetroBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void TrainBuilding::InitBuilding() {

}

void TrainBuilding::DistributeInside() {

}

vector<pair<shared_ptr<Job>, int>> TrainBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void PlaneBuilding::InitBuilding() {

}

void PlaneBuilding::DistributeInside() {

}

vector<pair<shared_ptr<Job>, int>> PlaneBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

void ShipBuilding::InitBuilding() {

}

void ShipBuilding::DistributeInside() {

}

vector<pair<shared_ptr<Job>, int>> ShipBuilding::GetJobs() {
    return vector<pair<shared_ptr<Job>, int>>();
}

