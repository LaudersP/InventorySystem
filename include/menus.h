#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void ClearTerminal();
void PrintTitle();
void PrintMainMenu();
void PrintFillerLine();
void FinishLine(int length);
void PrintError(const char* error);
void PrintInputMessage(const char* inputMessage);
void ConvertToUpperCase(char* str);
void PrintPartInfo(const char* id, const char* name, const char* man, const char* manNum, const char* site, const int qty, const double unitCost);

#endif