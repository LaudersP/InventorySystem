#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// === Main Print Functions ===
void PrintClearTerminal();
void PrintTitle();
void PrintMainMenu();
void PrintBannerMessage(const char* bannerMessage);
void PrintMessage(const char* inputMessage);
void PrintInventory(const char* id, const char* name, const int qty);
void PrintPartInfo(const char* id, const char* name, const char* man, const char* manNum, const char* site, const int qty, const double unitCost);

// === Sub Called Functions ===
void FillerLine();
void GraphicBottom();
void FinishLine(int length);
void ConvertToUpperCase(char* str);

#endif