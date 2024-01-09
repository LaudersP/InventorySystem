#ifndef SQL_QUERIES_H
#define SQL_QUERIES_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite-amalgamation-3440200/sqlite3.h>

void SelectTextSQL(sqlite3* database, const char* table, const char* partId, const char* attribute, int resultSize, char* result);
void SelectDoubleSQL(sqlite3* database, const char* table, const char* partId, const char* attribute, double* result);
void SelectIntSQL(sqlite3* database, const char* table, const char* partId, const char* attribute, int* result);
void UpdateTextSQL(sqlite3* database, const char* table, const char* partId, const char* attribute, const char* newAttributeData);
void UpdateDoubleSQL(sqlite3* database, const char* table, const char* partId, const char* attribute, double newAttributeData);
void UpdateIntSQL(sqlite3* database, const char* table, const char* partId, const char* attribute, int newAttributeData);
void DeleteSQL(sqlite3* database, const char* table, const char* partId);

#endif