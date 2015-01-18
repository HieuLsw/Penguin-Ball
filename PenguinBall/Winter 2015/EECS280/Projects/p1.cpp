//
//  p1.cpp
//  
//  Created by Vaishnavi Raghu Raman on 1/5/15.
//
//

#include "io.h"

int main () {
    
    double monthlyPayment = GetParam("Please enter the monthly payment: ", 1, 100000);
    double interestRate = GetParam("Please enter the interest rate: ", 0, 1);
    double loanDuration = GetParam("Please enter the duration of the loan, in years: "
        , 1, 100);
    
    //Error Checks to see if loanDuratoin is an integer and prompts the user to reenter the value if false
    while ( (static_cast<int> (loanDuration + 0.5)) != loanDuration) {
        loanDuration = GetParam("Please enter the duration of the loan, in years: ", 1, 100);
    }

    int months = loanDuration * 12;
    //Work backwards with balance starting at zero and reaching the total owed in last week
    double balance = 0;

    PrintHeader();
    
    //Decreases months until we reach month 1
    while(months != 0) {
        //Formula for balance copied from givens in project spec
        balance = (balance + monthlyPayment)/(1+interestRate/12);
        //Interest compounded monthly so divided by 12
        double interest = interestRate * balance/12;
        //Principal is how much is payed towards lowering remaining balance s
        double principal = monthlyPayment - interest;
        
        PrintMonthlyData(months, principal, interest, balance);
        
        months--;
    }
    
    return 0;
}

