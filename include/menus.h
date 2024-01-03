#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ClearTerminal();
void PrintTitle();
void PrintMainMenu();
void PrintFillerLine();
void FinishLine(int length);
void PrintError(const char* error);

#endif