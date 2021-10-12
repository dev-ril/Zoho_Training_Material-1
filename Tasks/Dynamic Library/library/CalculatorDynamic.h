#pragma once

#ifdef CALCULATORDYNAMIC_EXPORTS
#define CALCULATOR_API __declspec(dllexport)
#else
#define CALCULATOR_API __declspec(dllimport)
#endif


extern "C"  CALCULATOR_API double Calculate(double num1, double num2, int choice);
