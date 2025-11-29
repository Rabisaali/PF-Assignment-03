#include <stdio.h>
#include <math.h>
int yearToBePrinted=1;
#define FIXED_INSTALLMENT 40000

void calculateRepayment(float loan, float interestRate, int years);
int main () {
    float loan=100000;
    float interestRate=5;
    int years=3;
    calculateRepayment(loan, interestRate, years);
    return 0;
}
void calculateRepayment(float loan, float interestRate, int years) {
    if (loan<=0 || years==0) {
        return;
    }
    else {
        loan = loan * (1+(interestRate/100)) - FIXED_INSTALLMENT;

        if (loan<0) loan=0;

        printf("Year %d: Remaining Loan = %.0f\n", yearToBePrinted, loan);
        yearToBePrinted++;
        years--;
        calculateRepayment(loan, interestRate, years);
        return;
    }
}