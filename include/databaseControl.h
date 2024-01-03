#ifndef DATABASE_CONTROL_H
#define DATABASE_CONTROL_H

#include <sqlite-amalgamation-3440200/sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

void Setup(sqlite3* database, const char* FILEPATH);
void CloseDatabase(sqlite3* database);
int executeSQL(sqlite3* database, const char* SQLstatment);
int addPart(sqlite3* db, const char* partName, int quantity,
    const char* manufacturer, const char* manufacturerNumber,
    const char* siteOrderedFrom, const char* link, double partCost);
void removePart();
void updatePart();
void viewInventory();
void generateReport();

#endif