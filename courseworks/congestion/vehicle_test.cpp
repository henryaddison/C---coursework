#include <iostream>
#include <cassert>
#include "vehicle_test.h"
#include "date.h"
using namespace std;
#include "vehicle.h"

void VehicleTest::run() {
  cout << "Running Vehicle tests..." << endl;
  cout << "=========" << endl;
  testSetRate();
  testConstructBus();
  testBoardAndLeaveBus();
  testConstructLorry();
  testUnitEntryCost();
  testEntryCharge();
  testBusEnter();
  testLorryEnter();
  testMoreThanOneEntryPerDay();
  testConstructPetrolCar();
  testPetrolCarEnter();
  testConstructDieselCar();
  testDieselCarEnter();
  testSetLimit();
  testDescription();
  cout << endl;
}

void VehicleTest::testSetRate() {
  cout << __func__ << " running..." << endl;
  
  assert(Vehicle::rate == 1.00);
  Vehicle::set_rate(2.00);
  assert(Vehicle::rate == 2.00);

  cout << __func__ << " passed." << endl;
}

void VehicleTest::testConstructBus() {
  cout << __func__ << " running..." << endl;
  Bus testbus("TEST REG");
  assert(testbus.registration == "TEST REG");
  assert(testbus.passengers == 0);
  cout << __func__ << " passed." << endl;
}

void VehicleTest::testBoardAndLeaveBus() {
  cout << __func__ << " running..." << endl;
  Bus testbus("TEST REG");
  assert(testbus.passengers == 0);
  testbus.board(10);
  assert(testbus.passengers == 10);
  testbus.leave(5);
  assert(testbus.passengers == 5);

  cout << __func__ << " passed." << endl;
}

void VehicleTest::testConstructLorry() {
  cout << __func__ << " running..." << endl;
  Lorry testlorry("L10RRY", 12);
  assert(testlorry.axles == 12);
  cout << __func__ << " passed." << endl;
}

void VehicleTest::testUnitEntryCost() {
  cout << __func__ << " running..." << endl;
  //test with a lorry
  Date today(23,11,2011);
  Lorry testlorry("L10RRY", 12);
  Lorry anotherlorry("LORRY2", 6);
  assert(testlorry.unit_entry_cost(today, 17) == 12);
  assert(anotherlorry.unit_entry_cost(today, 17) == 6);

  //test with an emtpy bus
  Bus bus("TESTBUS");
  assert(bus.unit_entry_cost(today, 17) == 5);

  //test with a few people
  bus.passengers = 15;
  assert(bus.unit_entry_cost(today, 17) == 5);

  //test with lots of people
  bus.passengers = 25;
  assert(bus.unit_entry_cost(today, 17) == 0);

  //test around border
  bus.passengers = 19;
  assert(bus.unit_entry_cost(today, 17) == 5);

  bus.passengers = 20;
  assert(bus.unit_entry_cost(today, 17) == 0);

  bus.passengers = 21;
  assert(bus.unit_entry_cost(today, 17) == 0);

  //test with a petrol car
  PetrolCar petrol("PETROL1");
  //0 before 9
  assert(petrol.unit_entry_cost(today,8) == 0);
  assert(petrol.unit_entry_cost(today,9) == 2);
  //0 after 18
  assert(petrol.unit_entry_cost(today,17) == 2);
  assert(petrol.unit_entry_cost(today,18) == 0);
  //otherwise 2
  assert(petrol.unit_entry_cost(today,14) == 2);

  //test with a diesel car
  DieselCar polluting("DIESEL",20);
  DieselCar clean("DIESEL",4);
  //0 before 9
  assert(polluting.unit_entry_cost(today,8) == 0);
  assert(clean.unit_entry_cost(today,8) == 0);
  assert(polluting.unit_entry_cost(today,9) == 3);
  assert(clean.unit_entry_cost(today,9) == 1);
  
  //0 after 18
  assert(polluting.unit_entry_cost(today,18) == 0);
  assert(clean.unit_entry_cost(today,18) == 0);
  assert(polluting.unit_entry_cost(today,17) == 3);
  assert(clean.unit_entry_cost(today,17) == 1);

  //otherwise depends on emissions
  assert(polluting.unit_entry_cost(today,14) == 3);
  assert(clean.unit_entry_cost(today,14) == 1);

  cout << __func__ << " passed" << endl;
}

void VehicleTest::testEntryCharge() {
  cout << __func__ << " running..." << endl;

  Date today(25,11,2011);
  Bus bus("BUS");
  
  assert(bus.entry_charge(today, 14) == 10.0);


  cout << __func__ << " passed" << endl;
}

void VehicleTest::testBusEnter() {
  cout << __func__ << " running" << endl;
  Date today(24,11,2011);
  Bus quietbus("BUS");
  quietbus.passengers = 10;
  quietbus.enter(today,17);
  assert(quietbus.congestion_bill == 10.00);

  Bus busybus("BUS2");
  busybus.passengers = 25;
  busybus.enter(today,17);
  assert(busybus.congestion_bill == 0.00);

  cout << __func__ << " passed" << endl;
}

void VehicleTest::testLorryEnter() {
  cout << __func__ << " running..." << endl;

  Date today(24,11,2011);
  Lorry lorry("LORRY",12);
  lorry.enter(today,9);
  assert(lorry.congestion_bill == 24.0);

  Lorry anotherlorry("LORRY2",6);
  anotherlorry.enter(today,9);
  assert(anotherlorry.congestion_bill == 12.0);

  cout << __func__ << " passed" << endl;
}

void VehicleTest::testMoreThanOneEntryPerDay() {
  cout << __func__ << " running" << endl;
  
  Date today(24,11,2011);
  Date tomorrow(25,11,2011);
  Lorry lorry("LORRY",12);
  lorry.enter(today,9);
  assert(lorry.congestion_bill == 24.0);
  assert(lorry.last_charged_date == today);

  //bill shouldn't change if we try and enter again today
  lorry.enter(today,14);
  assert(lorry.congestion_bill == 24.0);
  
  //but then it should be charged tomorrow
  lorry.enter(tomorrow,1);
  assert(lorry.congestion_bill == 48.0);

  cout << __func__ << " passed" << endl;
}

void VehicleTest::testConstructPetrolCar() {
  cout << __func__ << " running..." << endl;
  PetrolCar car("CAR1");
  assert(car.registration == "CAR1");
  cout << __func__ << " passed." << endl;
}

void VehicleTest::testPetrolCarEnter() {
  cout << __func__ << " running..." << endl;
  Date today(25,11,2011);

  PetrolCar petrol("CAR1");
  PetrolCar petrol2("CAR2");
  PetrolCar petrol3("CAR3");

  petrol.enter(today, 7);
  assert(petrol.congestion_bill == 0);
  
  petrol2.enter(today, 15);
  assert(petrol2.congestion_bill == 4.0);
  
  petrol3.enter(today, 19);
  assert(petrol3.congestion_bill == 0);

  cout << __func__ << " passed." << endl;
}

void VehicleTest::testConstructDieselCar() {
  cout << __func__ << " running..." << endl;
  
  DieselCar diesel("DIESEL", 15);
  assert(diesel.registration == "DIESEL");
  assert(diesel.emissions == 15);
  
  cout << __func__ << " passed." << endl;
}

void VehicleTest::testDieselCarEnter() {
  cout << __func__ << " running..." << endl;

  Date today(25,11,2011);

  DieselCar polluting1("HUMMER1",20);
  DieselCar polluting2("HUMMER2",20);
  DieselCar clean1("SMUG1",3);
  DieselCar clean2("SMUG2",3);
  
  polluting1.enter(today, 7);
  assert(polluting1.congestion_bill == 0);
  clean1.enter(today, 7);
  assert(clean1.congestion_bill == 0);
  
  polluting2.enter(today, 14);
  assert(polluting2.congestion_bill == 6.0);
  clean2.enter(today, 14);
  assert(clean2.congestion_bill == 2.0);

  cout << __func__ << " passed." << endl;
}

void VehicleTest::testSetLimit() {
  cout << __func__ << " running..." << endl;

  assert(DieselCar::limit == 5);
  DieselCar::set_limit(20);
  assert(DieselCar::limit == 20);

  cout << __func__ << " passed." << endl;
}

void VehicleTest::testDescription() {
  cout << __func__ << " running..." << endl;
  
  assert(Lorry("L1ORRY", 7).description() == string("7-axle lorry (L1ORRY)"));
  assert(Bus("BUS1").description() == string("bus (BUS1)"));
  assert(PetrolCar("CAR").description() == string("petrol car (CAR)"));
  assert(DieselCar("D1ESEL", 15).description() == string("15-ppcm diesel car (D1ESEL)"));

  cout << __func__ << " passed." << endl;
}
