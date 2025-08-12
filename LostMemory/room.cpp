#pragma warning(disable:4244)
#pragma warning(disable:4267)

#include "room.h"


using namespace std;

ROOM_TYPE Room::GetType() {
	return type;
}

void Room::SetType(ROOM_TYPE type) {
	this->type = type;
}

Room* CreateRoom(ROOM_TYPE type) {
	switch (type) {
	case ROOM_DEVICE:
		return new DeviceRoom();
	case ROOM_PARKING:
		return new ParkingRoom();
	case ROOM_GUARD:
		return new GuardRoom();
	case ROOM_CLEAN:
		return new CleanRoom();
	case ROOM_HIGHWAY:
		return new HighwayRoom();
	case ROOM_GASOLINE:
		return new GasolineRoom();
	case ROOM_HOME:
		return new HomeRoom();
	case ROOM_VILLA:
		return new VillaRoom();
	case ROOM_WAREHOUSE:
		return new WarehouseRoom();
	case ROOM_PROPERTY:
		return new PropertyRoom();
	case ROOM_OFFICE:
		return new OfficeRoom();
	case ROOM_DOMITRY:
		return new DormitoryRoom();
	case ROOM_CANTEEN:
		return new CanteenRoom();
	case ROOM_ACTIVITY:
		return new ActivityRoom();
	case ROOM_STAGE:
		return new StageRoom();
	case ROOM_GROCERY:
		return new GroceryRoom();
	case ROOM_MUSIC:
		return new MusicRoom();
	case ROOM_TOILET:
		return new ToiletRoom();
	case ROOM_MARKET:
		return new MarketRoom();
	case ROOM_BUNK:
		return new BunkRoom();
	case ROOM_RECEPTION:
		return new ReceptionRoom();
	case ROOM_INGREDIENT:
		return new IngredientRoom();
	case ROOM_SALE:
		return new SaleRoom();
	case ROOM_BRAND:
		return new BrandRoom();
	case ROOM_CLOTHES:
		return new ClothesRoom();
	case ROOM_RESTAURANT:
		return new RestaurantRoom();
	case ROOM_FASTFOOD:
		return new FastfoodRoom();
	case ROOM_BUFFET:
		return new BuffetRoom();
	case ROOM_COFFEE:
		return new CoffeeRoom();
	case ROOM_DRINK:
		return new DrinkRoom();
	case ROOM_CINEMA:
		return new CinemaRoom();
	case ROOM_CARRENT:
		return new CarrentRoom();
	case ROOM_HAIRCUT:
		return new HaircutRoom();
	case ROOM_SMOKEWINETEA:
		return new SmokewineteaRoom();
	case ROOM_ELECTRONIC:
		return new ElectronicRoom();
	case ROOM_BOOK:
		return new BookRoom();
	case ROOM_MOVIE:
		return new MovieRoom();
	case ROOM_PUB:
		return new PubRoom();
	case ROOM_MASAGE:
		return new MasageRoom();
	case ROOM_SAUNA:
		return new SaunaRoom();
	case ROOM_BATH:
		return new BathRoom();
	case ROOM_CHANGING:
		return new ChangingRoom();
	case ROOM_PUBLICEAT:
		return new PublicEatRoom();
	case ROOM_PRIVATEEAT:
		return new PrivateEatRoom();
	case ROOM_KITCHEN:
		return new KitchenRoom();
	case ROOM_MEETING:
		return new MeetingRoom();
	case ROOM_COMPUTER:
		return new ComputerRoom();
	case ROOM_STOCK:
		return new StockRoom();
	case ROOM_STUDIO:
		return new StudioRoom();
	case ROOM_MAKEUP:
		return new MakeupRoom();
	case ROOM_ANIMAL:
		return new AnimalRoom();
	case ROOM_PLANT:
		return new PlantRoom();
	case ROOM_EXHIBITION:
		return new ExhibitionRoom();
	case ROOM_READING:
		return new ReadingRoom();
	case ROOM_COURT:
		return new CourtRoom();
	case ROOM_LAB:
		return new LabRoom();
	case ROOM_MACHINE:
		return new MachineRoom();
	case ROOM_PIPELINE:
		return new PipelineRoom();
	case ROOM_CONSTRUCTION:
		return new ConstructionRoom();
	case ROOM_CHICKEN:
		return new ChickenRoom();
	case ROOM_COW:
		return new CowRoom();
	case ROOM_PIG:
		return new PigRoom();
	case ROOM_SHEEP:
		return new SheepRoom();
	case ROOM_FOOTBALL:
		return new FootballRoom();
	case ROOM_BASKETBALL:
		return new BasketballRoom();
	case ROOM_VOLLEYBALL:
		return new VolleyballRoom();
	case ROOM_BADMINTON:
		return new BadmintonRoom();
	case ROOM_TABLETENNIS:
		return new TableTennisRoom();
	case ROOM_TENNIS:
		return new TennisRoom();
	case ROOM_SKATE:
		return new SkateRoom();
	case ROOM_BOWLING:
		return new BowlingRoom();
	case ROOM_ARCHERY:
		return new ArcheryRoom();
	case ROOM_RANGE:
		return new RangeRoom();
	case ROOM_POOL:
		return new PoolRoom();
	case ROOM_HAIR:
		return new HairRoom();
	case ROOM_COSMETIC:
		return new CosmeticRoom();
	case ROOM_GYM:
		return new GymRoom();
	case ROOM_CHESSCARD:
		return new ChessCardRoom();
	case ROOM_PET:
		return new PetRoom();
	case ROOM_COPY:
		return new CopyRoom();
	case ROOM_CARWASH:
		return new CarWashRoom();
	case ROOM_BICYCLE:
		return new BicycleRoom();
	case ROOM_NET:
		return new NetRoom();
	case ROOM_ARCADE:
		return new ArcadeRoom();
	case ROOM_KTV:
		return new KTVRoom();
	case ROOM_BILLIARD:
		return new BilliardRoom();
	case ROOM_FURNITURE:
		return new FurnitureRoom();
	case ROOM_REVIEW:
		return new ReviewRoom();
	case ROOM_EMERGENCY:
		return new EmergencyRoom();
	case ROOM_OUTPATIENT:
		return new OutpatientRoom();
	case ROOM_OPERATION:
		return new OperationRoom();
	case ROOM_ICU:
		return new ICURoom();
	case ROOM_DOCTOR:
		return new DoctorRoom();
	case ROOM_ASSAY:
		return new AssayRoom();
	case ROOM_CLASS:
		return new ClassRoom();
	case ROOM_PLAYGROUND:
		return new PlaygroundRoom();
	case ROOM_CELL:
		return new CellRoom();
	case ROOM_METRO:
		return new MetroRoom();
	case ROOM_TRAIN:
		return new TrainRoom();
	case ROOM_PLANE:
		return new PlaneRoom();
	case ROOM_SHIP:
		return new ShipRoom();
	case ROOM_CHECKIN:
		return new CheckinRoom();
	case ROOM_TICKET:
		return new TicketRoom();
	case ROOM_CUSTOM:
		return new CustomRoom();
	case ROOM_MOTUARY:
		return new MotuaryRoom();
	case ROOM_FUNERAL:
		return new FuneralRoom();
	case ROOM_CONDOLENCE:
		return new CondolenceRoom();
	case ROOM_BOILER:
		return new BoilerRoom();
	case ROOM_GOLD:
		return new GoldRoom();
	default:
		break;
	}

	return nullptr;
}