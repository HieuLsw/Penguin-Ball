
//
//  Monopoly.cpp
//  test1
//
//  Created by Vaishnavi Raghu Raman on 10/15/14.
//  Copyright (c) 2014 Vaishnavi Raghu Raman. All rights reserved.
//

#include <iostream>
using namespace std;

int Reverse (int x, int y=10, int z=0){
temp = x%y;
temp -= z;
z = (z*10) + (temp/y*10);
if (x%y == x) {
    return z;
}
else {
Reverse(x,y*10); 
}
}

int main() {
    
int x; 
cout << “Input x: “;
cin >> x; 
cout << Reverse(x); 
    
    return 0;
    
}



                            

