#include "pch.h"
#include "framework.h"
#include <utility>
#include <limits.h>
#include "CalculatorDynamic.h"

double Calculate(double num1, double num2, int choice) 
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
