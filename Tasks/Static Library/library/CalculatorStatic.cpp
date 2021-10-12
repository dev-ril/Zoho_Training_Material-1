#include "CalculatorStatic.h"

double Arithmetic::CalculateS(double num1, double num2, int choice)
{
	switch (choice)
	{
	case 1:
		return num1 + num2;
		break;

	case 2:
		return num1 - num2;
		break;

	case 3:
		return num1 * num2;
		break;

	case 4:
		return num1 / num2;
		break;

	default:
		return 0.0;

		break;
	}

}
