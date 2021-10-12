//Application program code
#include <iostream>
#include "CalculatorDynamic/CalculatorDynamic.h" //Including the dynamic library header file

using namespace std;

int main()
{  
    int choice, num1, num2;
    cout << "Calculator - Dynamic Library\n\n" << endl;
    cout << "OPTIONS\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n\nEnter your choice:\n" << endl;
    cin >> choice;
    if (choice > 4 || choice < 1)
    {
        cout << "Invalid choice" << endl;
        return 1;
    }
    cout << "Enter number 1:" << endl;
    cin >> num1;
    cout << "Enter number 2:" << endl;
    cin >> num2;

    cout << "Output:" << endl;
    cout << Calculate(num1, num2, choice) << std::endl;
}
