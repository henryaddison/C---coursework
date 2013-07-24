/* trafficLightsMain.cpp - for MSc Conversion C++ Assessed Exercise 2.  */

/* Authors: Sophia Drossopoulou  &  Rob Miller
   Program last changed: 21st December 2002    */

#include <iostream>
#include "time.h"
#include "trafficLight.h"
#include "trafficJunction.h"

using namespace std;


 
int main ()
{ 
    cout << "==========================\n" 
	 << "Roads open in Sleepy Town:\n" 
	 << "==========================\n";

    // (b) create a pair of traffic lights with delays 15 minutes and
    //     5 minutes respectively:
    cout << "\nA pair T1 and T2 of (slow) collaborating "
         << "lights is set up:\n";

    char  T1Name[] = "T1 (North South)";
    char  T2Name[] = "T2 (East West)";
    Time delayT1 (0, 15, 0);
    Time delayT2 (0, 5, 0);

    TrafficJunction J1 ( delayT1, T1Name, delayT2, T2Name );

    // (c)-(f) begin the simulation with 4 car crossings:
    J1.carWantsToCross ('N');    // event (c) completed
    J1.carWantsToCross ('W');    // event (d) completed
    J1.carWantsToCross ('S');    // event (e) completed
    J1.carWantsToCross ('E');    // event (f) completed


    /* (g) create another pair of traffic lights with extra long
       delays of 6hrs, 15mins, 44secs and 14hrs, 5mins, 57secs
       respectively: */
    cout << "\nA new pair T3 and T4 of (very slow!) "
	 << "collaborating lights is now set up:\n";

    char  T3Name[]="T3 (North South)";
    char  T4Name[]="T4 (East West)";
    Time delayT3(6, 15, 44);
    Time delayT4(14, 5, 57);

    TrafficJunction J2 ( delayT3, T3Name, delayT4, T4Name );
    // event (g) completed

    /* (h)-(m) continue the simulation with 6 more car crossings: */
    J2.carWantsToCross ('N'); // event (h) completed
    J2.carWantsToCross ('N'); // event (i) completed
    J2.carWantsToCross ('W'); // event (j) completed
    J2.carWantsToCross ('E'); // event (k) completed
    J2.carWantsToCross ('S'); // event (l) completed
    J2.carWantsToCross ('E'); // event (m) completed
 
    cout << "\n===================================\n"
	 << "Roads close forever in Sleepy Town.\n" 
	 << "===================================\n";
    
    return 0;
}



