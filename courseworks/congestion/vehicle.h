#ifndef VEHICLE_H
#define VEHICLE_H
using namespace std;

class Vehicle {
  friend class VehicleTest;

 public:
 Vehicle(const string reg) : registration(reg),congestion_bill(0),last_charged_date(1,1,1970) {
   // we always start the description of a newly registered vehicle with the same few characters
   cout << "***  A ";
 };
  // a method to set the conversion rate between congestion charge units and pounds
  void static set_rate(double new_rate);
  // a method to calculate how much a vehicle should be charged when it enters the congestion zone and updates the vehicle's bill
  void enter(const Date& date_entered, int hour_entered);

 protected:
  double static rate;  
  string registration;
  double congestion_bill;
  Date last_charged_date;
  virtual string description() const;
  double entry_charge(const Date& date_entered, int hour_entered) const;
  virtual int unit_entry_cost(const Date& date_entered, int hour_entered) const = 0;  
  void print_entry_details(const Date& date, int hour) const;
  void print_charging_details(double charge) const;
};

class Lorry : public Vehicle {
  friend class VehicleTest;
 public:
 Lorry(const string reg, int num_axles) : Vehicle(reg), axles(num_axles) {
    cout << description() << " has been registered" << endl << endl;
  }
  
 private:
  int axles;
  string description() const;
  int unit_entry_cost(const Date& date_entered, int hour_entered) const;
};

class Bus : public Vehicle {
  friend class VehicleTest;
 public:
  //initially the number of passengers on a bus is 0
 Bus(const string reg) : Vehicle(reg),passengers(0) {
    cout << description() << " has been registered" << endl << endl;
  };
  //methods to tracks passengers boarding and leaving a bus
  //for boarding and leaving, number of passengers cannot be negative
  void board(int passengers_boarding);
  //and for leaving number of passengers leaving cannot be more than the number of passengers on board
  void leave(int passengers_leaving);
  
 private:
  int passengers;
  string description() const;
  int unit_entry_cost(const Date& date_entered, int hour_entered) const;
};

class Car : public Vehicle {
 public:
 Car(const string reg) : Vehicle(reg) {}

 protected:
  int unit_entry_cost(const Date& date_entered, int hour_entered) const;
  virtual int fuel_specific_unit_entry_cost() const = 0;
};

class PetrolCar : public Car {
  friend class VehicleTest;
 public:
 PetrolCar(const string reg) : Car(reg) {
    cout << description() << " has been registered" << endl << endl;
  }

 private:
  string description() const;
  int fuel_specific_unit_entry_cost() const;
};

class DieselCar : public Car {
  friend class VehicleTest;
 public:
 DieselCar(const string reg, int pollution_emissions) : Car(reg), emissions(pollution_emissions) {
    cout << description() << " has been registered" << endl << endl;
  }
  // a method to set how high diesel car emissions can be before being charged the higher amount
  void static set_limit(double new_limit);

 private:
  double static limit;
  int emissions;
  string description() const;
  int fuel_specific_unit_entry_cost() const;
};

#endif
