#pragma warning(disable:4244)
#pragma warning(disable:4267)

#include "organization.h"


using namespace std;

ORGANIZATION_TYPE Organization::GetType() {
    return type;
}

void Organization::SetType(ORGANIZATION_TYPE type) {
    this->type = type;
}

Organization* CreateOrganization(ORGANIZATION_TYPE type) {
    switch (type) {
    case ORGANIZATION_NONE:
        return new Organization(type);
    case ORGANIZATION_ROADFIX:
        return new RoadfixOrganization();
    case ORGANIZATION_PARKING:
        return new ParkingOrganization();
    case ORGANIZATION_BANK:
        return new BankOrganization();
    case ORGANIZATION_LIBRARY:
        return new LibraryOrganization();
    case ORGANIZATION_CLINIC:
        return new ClinicOrganization();
    case ORGANIZATION_HOSPITAL:
        return new HospitalOrganization();
    case ORGANIZATION_INPATIENT:
        return new InpatientOrganization();
    case ORGANIZATION_SANATORIUM:
        return new SanatoriumOrganization();
    case ORGANIZATION_POLICE:
        return new PoliceOrganization();
    case ORGANIZATION_FIRE:
        return new FireOrganization();
    case ORGANIZATION_KINDER:
        return new KinderOrganization();
    case ORGANIZATION_PRIMARY:
        return new PrimaryOrganization();
    case ORGANIZATION_MIDDLE:
        return new MiddleOrganization();
    case ORGANIZATION_UNIVERSITY:
        return new UniversityOrganization();
    case ORGANIZATION_VOCATIONAL:
        return new VocationalOrganization();
    case ORGANIZATION_CREMATORIUM:
        return new CrematoriumOrganization();
    case ORGANIZATION_CEMETRY:
        return new CemetryOrganization();
    case ORGANIZATION_TVSTATION:
        return new TVStationOrganization();
    case ORGANIZATION_GASOLINE:
        return new GasolineOrganization();
    case ORGANIZATION_TOILET:
        return new ToiletOrganization();
    case ORGANIZATION_DEVICE:
        return new DeviceOrganization();
    case ORGANIZATION_POST:
        return new PostOrganization();
    case ORGANIZATION_STATION:
        return new StationOrganization();
    case ORGANIZATION_COMMUNITY:
        return new CommunityOrganization();
    case ORGANIZATION_ESTATE:
        return new EstateOrganization();
    case ORGANIZATION_PROPERTY:
        return new PropertyOrganization();
    case ORGANIZATION_PACKAGE:
        return new PackageOrganization();
    case ORGANIZATION_HOTEL:
        return new HotelOrganization();
    case ORGANIZATION_RESTAURANT:
        return new RestaurantOrganization();
    case ORGANIZATION_FASTFOOD:
        return new FastfoodOrganization();
    case ORGANIZATION_BUFFET:
        return new BuffetOrganization();
    case ORGANIZATION_COFFEE:
        return new CoffeeOrganization();
    case ORGANIZATION_DRINK:
        return new DrinkOrganization();
    case ORGANIZATION_MALL:
        return new MallOrganization();
    case ORGANIZATION_MARKET:
        return new MarketOrganization();
    case ORGANIZATION_MUSIC:
        return new MusicOrganization();
    case ORGANIZATION_INGREDIENT:
        return new IngredientOrganization();
    case ORGANIZATION_BRAND:
        return new BrandOrganization();
    case ORGANIZATION_CARRENT:
        return new CarrentOrganization();
    case ORGANIZATION_THEATER:
        return new TheaterOrganization();
    case ORGANIZATION_MUSEUM:
        return new MuseumOrganization();
    case ORGANIZATION_ZOO:
        return new ZooOrganization();
    case ORGANIZATION_BOTANIC:
        return new BotanicOrganization();
    case ORGANIZATION_AQUARIUM:
        return new AquariumOrganization();
    case ORGANIZATION_CINEMA:
        return new CinemaOrganization();
    case ORGANIZATION_PUB:
        return new PubOrganization();
    case ORGANIZATION_MASSAGE:
        return new MassageOrganization();
    case ORGANIZATION_AMUSEMENT:
        return new AmusementOrganization();
    case ORGANIZATION_FURNISH:
        return new FurnishOrganization();
    case ORGANIZATION_MOVING:
        return new MovingOrganization();
    case ORGANIZATION_OPERATOR:
        return new OperatorOrganization();
    case ORGANIZATION_GAME:
        return new GameOrganization();
    case ORGANIZATION_LEASE:
        return new LeaseOrganization();
    case ORGANIZATION_FINANCE:
        return new FinanceOrganization();
    case ORGANIZATION_LENDING:
        return new LendingOrganization();
    case ORGANIZATION_SALE:
        return new SaleOrganization();
    case ORGANIZATION_MEDICAL:
        return new MedicalOrganization();
    case ORGANIZATION_RELATION:
        return new RelationOrganization();
    case ORGANIZATION_ESHOP:
        return new EshopOrganization();
    case ORGANIZATION_STAR:
        return new StarOrganization();
    case ORGANIZATION_ENGINEER:
        return new EngineerOrganization();
    case ORGANIZATION_CONSTRUCT:
        return new ConstructOrganization();
    case ORGANIZATION_ART:
        return new ArtOrganization();
    case ORGANIZATION_PUBLISHER:
        return new PublisherOrganization();
    case ORGANIZATION_TRAVEL:
        return new TravelOrganization();
    case ORGANIZATION_MEDIA:
        return new MediaOrganization();
    case ORGANIZATION_LAWYER:
        return new LawyerOrganization();
    case ORGANIZATION_CREW:
        return new CrewOrganization();
    case ORGANIZATION_INSURANCE:
        return new InsuranceOrganization();
    case ORGANIZATION_SECURITY:
        return new SecurityOrganization();
    case ORGANIZATION_CLEANING:
        return new CleaningOrganization();
    case ORGANIZATION_GREEN:
        return new GreenOrganization();
    case ORGANIZATION_INTERMEDIARY:
        return new IntermediaryOrganization();
    case ORGANIZATION_STOCK:
        return new StockOrganization();
    case ORGANIZATION_COURT:
        return new CourtOrganization();
    case ORGANIZATION_ADMIN:
        return new AdminOrganization();
    case ORGANIZATION_EDUCATIONDEPT:
        return new EducationdeptOrganization();
    case ORGANIZATION_INFODEPT:
        return new InfodeptOrganization();
    case ORGANIZATION_FINANCEDEPT:
        return new FinancedeptOrganization();
    case ORGANIZATION_TRADEDEPT:
        return new TradedeptOrganization();
    case ORGANIZATION_PETITIONDEPT:
        return new PetitiondeptOrganization();
    case ORGANIZATION_WEATHERDEPT:
        return new WeatherdeptOrganization();
    case ORGANIZATION_TAXDEPT:
        return new TaxdeptOrganization();
    case ORGANIZATION_CIVILDEPT:
        return new CivildeptOrganization();
    case ORGANIZATION_SCIENCEDEPT:
        return new SciencedeptOrganization();
    case ORGANIZATION_ENGINEERDEPT:
        return new EngineerdeptOrganization();
    case ORGANIZATION_SOCIALDEPT:
        return new SocialdeptOrganization();
    case ORGANIZATION_CUSTOMHOUSE:
        return new CustomhouseOrganization();
    case ORGANIZATION_DOGE:
        return new DogeOrganization();
    case ORGANIZATION_COMMITTEE:
        return new CommitteeOrganization();
    case ORGANIZATION_LAB:
        return new LabOrganization();
    case ORGANIZATION_FACTORY:
        return new FactoryOrganization();
    case ORGANIZATION_WAREHOUSE:
        return new WarehouseOrganization();
    case ORGANIZATION_REPAIR:
        return new RepairOrganization();
    case ORGANIZATION_RESOURCE:
        return new ResourceOrganization();
    case ORGANIZATION_PARK:
        return new ParkOrganization();
    case ORGANIZATION_PLAZA:
        return new PlazaOrganization();
    case ORGANIZATION_STATUE:
        return new StatueOrganization();
    case ORGANIZATION_GYM:
        return new GymOrganization();
    case ORGANIZATION_STADIUM:
        return new StadiumOrganization();
    case ORGANIZATION_FOOTBALL:
        return new FootballOrganization();
    case ORGANIZATION_BASKETBALL:
        return new BasketballOrganization();
    case ORGANIZATION_VOLLEYBALL:
        return new VolleyballOrganization();
    case ORGANIZATION_TENNIS:
        return new TennisOrganization();
    case ORGANIZATION_TABLETENNIS:
        return new TabletennisOrganization();
    case ORGANIZATION_BADMINTON:
        return new BadmintonOrganization();
    case ORGANIZATION_GOLF:
        return new GolfOrganization();
    case ORGANIZATION_SKI:
        return new SkiOrganization();
    case ORGANIZATION_SKATE:
        return new SkateOrganization();
    case ORGANIZATION_SWIM:
        return new SwimOrganization();
    case ORGANIZATION_RESORT:
        return new ResortOrganization();
    case ORGANIZATION_REMAINS:
        return new RemainsOrganization();
    case ORGANIZATION_ROCKET:
        return new RocketOrganization();
    case ORGANIZATION_PLAYGROUND:
        return new PlaygroundOrganization();
    case ORGANIZATION_PRISON:
        return new PrisonOrganization();
    case ORGANIZATION_GUARD:
        return new GuardOrganization();
    case ORGANIZATION_CANTEEN:
        return new CanteenOrganization();
    case ORGANIZATION_DORMITRY:
        return new DormitryOrganization();
    case ORGANIZATION_DATA:
        return new DataOrganization();
    case ORGANIZATION_WATER:
        return new WaterOrganization();
    case ORGANIZATION_SEWAGE:
        return new SewageOrganization();
    case ORGANIZATION_POWER:
        return new PowerOrganization();
    case ORGANIZATION_WINDMILL:
        return new WindmillOrganization();
    case ORGANIZATION_NUCLEAR:
        return new NuclearOrganization();
    case ORGANIZATION_RECYCLE:
        return new RecycleOrganization();
    case ORGANIZATION_TRASH:
        return new TrashOrganization();
    case ORGANIZATION_INCINERATION:
        return new IncinerationOrganization();
    case ORGANIZATION_BODY:
        return new BodyOrganization();
    case ORGANIZATION_DENTIST:
        return new DentistOrganization();
    case ORGANIZATION_MENTAL:
        return new MentalOrganization();
    case ORGANIZATION_AFFAIR:
        return new AffairOrganization();
    case ORGANIZATION_GOLD:
        return new GoldOrganization();
    case ORGANIZATION_GROCERY:
        return new GroceryOrganization();
    case ORGANIZATION_CLOTHES:
        return new ClothesOrganization();
    case ORGANIZATION_COSMETIC:
        return new CosmeticOrganization();
    case ORGANIZATION_HAIRCUT:
        return new HaircutOrganization();
    case ORGANIZATION_DRUG:
        return new DrugOrganization();
    case ORGANIZATION_SMOKEWINETEA:
        return new SmokewineteaOrganization();
    case ORGANIZATION_JEWELRY:
        return new JewelryOrganization();
    case ORGANIZATION_EXTRACURRICULAR:
        return new ExtracurricularOrganization();
    case ORGANIZATION_CHESSCARD:
        return new ChesscardOrganization();
    case ORGANIZATION_PET:
        return new PetOrganization();
    case ORGANIZATION_ELECTRONIC:
        return new ElectronicOrganization();
    case ORGANIZATION_COPY:
        return new CopyOrganization();
    case ORGANIZATION_STUDIO:
        return new StudioOrganization();
    case ORGANIZATION_CARWASH:
        return new CarwashOrganization();
    case ORGANIZATION_BICYCLE:
        return new BicycleOrganization();
    case ORGANIZATION_HARDWARE:
        return new HardwareOrganization();
    case ORGANIZATION_BOOK:
        return new BookOrganization();
    case ORGANIZATION_BILLIARD:
        return new BilliardOrganization();
    case ORGANIZATION_NET:
        return new NetOrganization();
    case ORGANIZATION_KTV:
        return new KtvOrganization();
    case ORGANIZATION_VENDOR:
        return new VendorOrganization();
    default:
        return nullptr;
    }
}
