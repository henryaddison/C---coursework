#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "date.h"
#include "vehicle.h"
#include "helper_functions.h"

using namespace std;

double Vehicle::rate = 1.00;
double DieselCar::limit = 5;

//two static methods for setting the two static attributes that need changing
void Vehicle::set_rate(double new_rate) {
  cout.setf(ios::fixed);
  cout.precision(2);
  rate = new_rate;
  cout << "***  The council sets the basic unit charge to #" << new_rate << endl << endl;
}

void DieselCar::set_limit(double new_limit) {
  cout.setf(ios::fixed);
  cout.precision(2);
  
  limit = new_limit;
  cout << "***  The council says diesel cars with emissions less than " << limit << " ppcm" << endl
       << "     should pay a reduced rate" << endl << endl;

}

//the methods for that return a description of each type of vehicle
string Vehicle::description() const {
  return string(" (") + registration + string(")");
}

string Lorry::description() const {
  string output = itostring(axles) + string("-axle lorry") + Vehicle::description();
  return output;
}

string Bus::description() const {
  return string("bus")+Vehicle::description();
}

string DieselCar::description() const {
  string output = itostring(emissions) + string("-ppcm diesel car") + Vehicle::description();
  return output;
}

string PetrolCar::description() const {
  return string("petrol car")+Vehicle::description();
}

//the method to be called when a vehicle enters the congestion charge zone
void Vehicle::enter(const Date& date_entered, int hour_entered) {  
  print_entry_details(date_entered, hour_entered);
  //assuming that each entry details of a vehicle will be entered in chronological order so only need to keep track of the last date the vehicle was charged
  if(date_entered == last_charged_date) {
    cout << "     The vehicle has already been charged today ; no action is taken" << endl << endl;
  } else {
    double charge = entry_charge(date_entered, hour_entered);
    if(charge > 0) {
      last_charged_date = date_entered;
      congestion_bill += charge;
    }
    print_charging_details(charge);
  }
}

//the helper methods for the enter method:
//a couple of printer helpers that output the desired details of when a vehicle enters the congestion charge zone and how much it is charged
void Vehicle::print_entry_details(const Date& date, int hour) const {
  cout.setf(ios::fixed);
  cout.precision(2);
  cout << "***  The " << description() << " enters on " << date << " at ";
  if(hour < 10)
    //print the leading 0 when hour is less than 10
    cout << "0";
  cout << hour <<"h00 hours" << endl;
}

void Vehicle::print_charging_details(double charge) const {
 if(charge > 0) {
   cout << "     The vehicle is charged #" << charge;
 } else {
   cout << "     The vehicle goes free";
 }
 cout << " (now owes #" << congestion_bill << ")" << endl << endl;
}

//this helper method returns the cost in pounds to the car entering the congestion charge zone
double Vehicle::entry_charge(const Date& date_entered, int hour_entered) const {
  return Vehicle::rate * unit_entry_cost(date_entered, hour_entered);
}

//then we have helpers for each type of vehicle that apply the individual rules of the congestion charges and return the number of units charged to the vehicle
int Lorry::unit_entry_cost(const Date& date_entered, int hour_entered) const {
  return axles;
}

int Bus::unit_entry_cost(const Date& date_entered, int hour_entered) const {
  if(passengers >= 20) {
    return 0;
  } else {
    return 5;
  }
}

int Car::unit_entry_cost(const Date& date_entered, int hour_entered) const {
  if(hour_entered < 9 || hour_entered >= 18) {
    return 0;
  } else {
    return fuel_specific_unit_entry_cost();
  }
}

int PetrolCar::fuel_specific_unit_entry_cost() const {
  return 2;
}

int DieselCar::fuel_specific_unit_entry_cost() const {
  if(emissions > DieselCar::limit) {
    return 3;
  } else {
    return 1;
  }
}

//methods to track passengers boarding and leaving a bus
void Bus::board(int passengers_boarding) {  
  if(passengers_boarding < 0) {
    cerr << "makes no sense to have a negative number of passengers boarding. Something has gone horribly wrong. Quitting" << endl;
    exit(1);
  }

  passengers += passengers_boarding;
  cout << "***  " << passengers_boarding << " " << pluralize_noun(passengers_boarding, string("passenger")) << " " << pluralize_verb(passengers_boarding, string("board")) << " the " << description() << ", so " << passengers << " " <<  pluralize_noun(passengers, string("passenger")) << " " << pluralize_verb(passengers, "is") << " on board" << endl << endl;
  
}

void Bus::leave(int passengers_leaving) {
  if(passengers_leaving < 0) {
    cerr << "makes no sense to have a negative number of passengers leaving. Something has gone  horribly wrong. Quitting" << endl;
    exit(1);
  }
  
  if(passengers_leaving > passengers) {
    cerr << "cannot have more passengers leaving than are on-board. Something has gone horribly wrong. Quitting." << endl;
    exit(1);
  }
  
  passengers -= passengers_leaving;

  cout << "***  " << passengers_leaving << " " << pluralize_noun(passengers_leaving, string("passenger")) << " leave the " << description() << ", leaving " << passengers << " " << pluralize_noun(passengers, string("passenger")) << " on board" << endl << endl;
}



