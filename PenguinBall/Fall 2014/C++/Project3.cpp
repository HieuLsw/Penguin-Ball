//
//  Project3.cpp
//  Project3
//
//  Created by Vaishnavi Raghu Raman on 9/21/14.
//  Copyright (c) 2014 Vaishnavi Raghu Raman. All rights reserved.
//

#include <iostream>
#include<stdlib.h>
#include<cmath>

using namespace std;




int fastPCRequested, blazingPCRequested, fastPCAvailable = 0,
    blazingPCAvailable = 0, fastPCLeft, blazingPCLeft, fastPCMade=0,
    blazingPCMade=0; // all variables usesd to keep track of production data
int daysAvailable; //until buyer wants order
int i = 0; //counts number of days of production
int w = 0; // counts number of weeks of production
int switches = 0; // counts number of production switches
int x=0; // helps with the switch case for the exit productions (ExitProduction), incremented value
int q = 0; //stores PC Production on the last day
int fastLastProduction;// fast computers made in the final week
int blazingLastProduction; //blazing computers made in the final week
int totalFastWeeks; //number of weeks entire order takes to complete starting with fast production
int totalBlazingWeeks; //number of weeks entire order takes to complete starting with blazing production
int weeksAvaialable; //until buyer wants order
int daysLeftAfter;//days of production possible on the last week until buyer wants order
int fastStore1 = 0, fastStore2 = 0, blazingStore1 = 0,
    blazingStore2 = 0;





// function works to calculate the number of days that each production (both fast and blazing) takes and then outputs the stortest makespan after comparing the two. Inputs for the function include the number of weeks of production until order is complete and the number of PC's produced on the last week.
void CompareProduction() {

    
    int totalBlazingDays;
    int totalFastDays;
    
    double blazingLastProduction2;
    double fastLastProduction2;
    
    blazingLastProduction2 = static_cast<double>(blazingLastProduction);
    fastLastProduction2 = static_cast<double>(fastLastProduction);

    
    blazingLastProduction2 = (blazingLastProduction2/100.0);
    
    fastLastProduction2 = (fastLastProduction2/100.0);

    totalBlazingDays = ((totalBlazingWeeks - 1) * 7) +
    (ceil(blazingLastProduction2));
    
    totalFastDays = ((totalFastWeeks - 1) * 7) +
    (ceil(fastLastProduction2)); // ceil used to round up value because cannot have half days or ignore a day by rounding down
    
    if (totalFastDays <= totalBlazingDays){ //determines which makespan is shorter and outputs it
        
        cout << "Shortest makespan (Fast) is "
        << totalFastDays << " days." << endl;
    }
    
    else {
        
         cout << "Shortest makespan (Blazing) is "
        << totalBlazingDays << " days." << endl;
    }
    
    exit(0);
    
}


// function declared here but description is below
void BlazingProduction();

// Ends the loops of production for fast and blazing PCs. Calculates and outputs the number of each type of PC created by the time requested. Inputs include the number of PC's made up until the week before the final week of production and the number of days available in final week available for production. This information is used to calculate the number of PC's made in the final week depending on if the number producable during the days available is larger to the total number prodcuded that week is larger. At the end we link to blazing production and re-do all calculations assuming that this time blazing started first.
void ExitProduction() {
    
        switch(x) {
                
            case 0:
            {
             
                
                int fastDifference;
                int blazingDifference;
                
                fastDifference = fastStore2 - fastStore1;
                blazingDifference = blazingStore2 - blazingStore1;
                
                int fastMadeLastWeek;
                int blazingMadeLastWeek;
               
                
                if (fastDifference >= (daysLeftAfter * 100)) {
                    
                    fastMadeLastWeek = (daysLeftAfter * 100);
                    
                }
                else if ((daysLeftAfter * 100) > fastDifference ) {
                    
                    fastMadeLastWeek = fastDifference;
                    
                }
                
                if (blazingDifference >= (daysLeftAfter * 100)) {
                    
                    blazingMadeLastWeek = (daysLeftAfter * 100);
                    
                }
                else if ((daysLeftAfter * 100) > blazingDifference ) {
                    
                    blazingMadeLastWeek = blazingDifference;
                }
                
         
                int fastMadeOnTime;
                int blazingMadeOnTime;
                
                fastMadeOnTime = fastStore1 + fastMadeLastWeek;
                blazingMadeOnTime = blazingStore1 + blazingMadeLastWeek;
            
                
                cout << "Deliver on time " << fastMadeOnTime  <<
                " fast PCs, " << blazingMadeOnTime
                << " blazing PCs." << endl;
                
                cout << switches << " switches." << endl;
                
            }
                
                cout << "Start with Blazing production." << endl;
    
                blazingPCLeft = blazingPCRequested;
                fastPCLeft = fastPCRequested;
                switches = 0;
                
                totalFastWeeks = w;
                w = 0;
                
                fastPCAvailable = 0;
                blazingPCAvailable=0;
                fastPCMade =0;
                blazingPCMade = 0;
                
                fastLastProduction = q;
                
                fastStore1 = 0;
                fastStore2 = 0;
                blazingStore1 = 0;
                blazingStore2 = 0;
                
                x++;
                BlazingProduction(); // reruns with original requested values, but starting with blazing this time
                
            break;
                
            case 1:
                
            {
            
                int fastDifference;
                int blazingDifference;
                
                fastDifference = fastStore2 - fastStore1;
                blazingDifference = blazingStore2 - blazingStore1;
                
                int fastMadeLastWeek;
                int blazingMadeLastWeek;
                
                
                if (fastDifference >= (daysLeftAfter * 100)) {
                    
                    fastMadeLastWeek = (daysLeftAfter * 100);
                    
                }
                else if ((daysLeftAfter * 100) > fastDifference ) {
                    
                    fastMadeLastWeek = fastDifference;
                    
                }
                
                if (blazingDifference >= (daysLeftAfter * 100)) {
                    
                    blazingMadeLastWeek = (daysLeftAfter * 100);
                    
                }
                else if ((daysLeftAfter * 100) > blazingDifference ) {
                    
                    blazingMadeLastWeek = blazingDifference;
                }
                
                
                int fastMadeOnTime;
                int blazingMadeOnTime;
                
                fastMadeOnTime = fastStore1 + fastMadeLastWeek;
                blazingMadeOnTime = blazingStore1 + blazingMadeLastWeek;
                
                
                cout << "Deliver on time " << fastMadeOnTime
                << " fast PCs, " << blazingMadeOnTime
                << " blazing PCs." << endl;
                cout << switches << " switches." << endl;

                
            }
                
                blazingLastProduction = q;
                totalBlazingWeeks = w;
                
                CompareProduction();
                
            break;
        }
        
    }

// Calculates the number of fast PC's made each week and stores them. Inputs include the actuall number of fast and blazing Pc's requested. At the end of each proudction week, we determine whether or not to switch the types of PC's manufatured. Futher details provided below.
void FastProduction() {
    
    w = w + 1; //increments weeks and the beginning of production
    
    
    // increments new supply of fast and blazing PC's each week
    fastPCAvailable = fastPCAvailable + 500;
    blazingPCAvailable = blazingPCAvailable + 300;
    q = fastPCLeft;
    
    
    if (fastPCLeft <= fastPCAvailable) {
        if (fastPCLeft >= 700) {
            fastPCLeft = fastPCLeft - 700;
            fastPCAvailable = fastPCAvailable - 700;
            fastPCMade = fastPCMade + 700;
            if (w <= weeksAvaialable){
                fastStore1 = fastPCMade;
            }
            if (w <= (weeksAvaialable + 1)) {
                fastStore2 = fastPCMade;
            }
            
        }
        else {
            fastPCAvailable = fastPCAvailable - fastPCLeft;
            fastPCMade = fastPCRequested; //because order is complete
            fastPCLeft = 0;
            if (w <= weeksAvaialable){
                fastStore1 = fastPCMade;
            }
            if (w <= (weeksAvaialable + 1)) {
                fastStore2 = fastPCMade;
            }
            
        }
    }
    else {
        if (fastPCAvailable >= 700) {
            fastPCLeft = fastPCLeft - 700;
            fastPCAvailable = fastPCAvailable - 700;
            fastPCMade = fastPCMade + 700;
            if (w <= weeksAvaialable){
                fastStore1 = fastPCMade;
            }
            if (w <= (weeksAvaialable + 1)) {
                fastStore2 = fastPCMade;
            }
            
        }
        else {
            fastPCLeft = fastPCLeft - fastPCAvailable;
            fastPCMade = fastPCMade + fastPCAvailable;
            fastPCAvailable = 0;
            if (w <= weeksAvaialable){
                fastStore1 = fastPCMade;
            }
            if (w <= (weeksAvaialable + 1)) {
                fastStore2 = fastPCMade;
            }
            
        }

    }

    
    //following code determines whether or not we should switch production to blazing
    if (fastPCLeft == 0) { // if no fast PC's are left in inventory or needed to fulfill order we switch to blazing unless blazing is done too. In that case production exits.
        if (blazingPCLeft == 0) {
            ExitProduction();
        }
        else {
            switches = switches + 1;
            BlazingProduction();
        }
    }
    if (fastPCAvailable == 0) {
        if (blazingPCLeft > 0) {
            switches = switches + 1;
            BlazingProduction();
        }
    }
// if all of the above conditions fail we have another week of fast production
    FastProduction();
}


// Calculates the number of blazing PC's made each week and stores them. Inputs include the actuall number of fast and blazing Pc's requested. At the end of each proudction week, we determine whether or not to switch the types of PC's manufatured. Futher details provided below.
void BlazingProduction() {
    
    w = w + 1; // increments week at the beginning of production
    
    // increments new supply of fast and blazing PC's each week
    blazingPCAvailable = blazingPCAvailable + 300;
    fastPCAvailable = fastPCAvailable + 500;
    q = blazingPCLeft;

    
    if (blazingPCLeft <= blazingPCAvailable) {
        if (blazingPCLeft >= 700) {
            blazingPCLeft = blazingPCLeft - 700;
            blazingPCAvailable = blazingPCAvailable - 700;
            blazingPCMade = blazingPCMade + 700;
            if (w <= weeksAvaialable){
                blazingStore1 = blazingPCMade;
            }
            if (w <= (weeksAvaialable + 1)) {
                blazingStore2 = blazingPCMade;
            }
            
         
        }
        else {
            blazingPCMade = blazingPCRequested; //order is complete
            blazingPCAvailable = blazingPCAvailable - blazingPCLeft;
            blazingPCLeft = 0;
            
            if (w <= weeksAvaialable){
                blazingStore1 = blazingPCMade;
            }
            if (w <= (weeksAvaialable + 1)) {
                blazingStore2 = blazingPCMade;
            }

        }
    }
    else  {
        if (blazingPCAvailable >= 700) {
            blazingPCLeft = blazingPCLeft - 700;
            blazingPCAvailable = blazingPCAvailable - 700;
            blazingPCMade = blazingPCMade + 700;
            
            if (w <= weeksAvaialable){
                blazingStore1 = blazingPCMade;
            }
            if (w <= (weeksAvaialable + 1)) {
                blazingStore2 = blazingPCMade;
            }
        
        }

        else {
            blazingPCLeft = blazingPCLeft - blazingPCAvailable;
            blazingPCMade = blazingPCMade + blazingPCAvailable;
            blazingPCAvailable = 0;
            
            if (w <= weeksAvaialable){
                blazingStore1 = blazingPCMade;
            }
            if (w <= (weeksAvaialable + 1)) {
                blazingStore2 = blazingPCMade;
            }
 
        }
    }
    

    //following code determines whether or not we should switch production to fast
    
    if (blazingPCLeft == 0) { // if no fast PC's are left in inventory or needed to fulfill order we switch to fast unless blazing is done too. In that case production exits.
        if (fastPCLeft == 0) {
            ExitProduction();
        }
        if (fastPCLeft > 0) {
            switches = switches + 1;
            FastProduction();
        }
       
    }
    if (blazingPCAvailable == 0) {
        if (fastPCLeft > 0) {
            switches = switches + 1;
            FastProduction();
        }
    }
    // if all of the above conditions fail we have another week of blazing production
    BlazingProduction();
}



int main() {
    
    cin >> fastPCRequested >> blazingPCRequested >> daysAvailable;
    blazingPCLeft = blazingPCRequested;
    fastPCLeft = fastPCRequested;
    cout << "Start with Fast production." << endl;
    
    weeksAvaialable = (daysAvailable/7); //determines number of full weeks of production
    daysLeftAfter = (daysAvailable%7); //determines the number of days of production on the final week
    
    FastProduction (); // starts with fast production, outputs how long to make full
    
    return 0;
}
    





