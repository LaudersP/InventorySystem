#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sqlite-amalgamation-3440200\sqlite3.h>
#include <menus.h>

#define DATABASE_FILE_PATH "InventorySystem.db"

int main() {
	// Pointer to inventory database file
	sqlite3* db;

	// Open database
	int rc = sqlite3_open(DATABASE_FILE_PATH, &db);

	// ==== Table creation/check for parts table ====

	// SQL statement for table creation
	// ... only performed if table does NOT exist
	const char* createPartsTableSQL = "CREATE TABLE IF NOT EXISTS parts ("
		"	partId TEXT PRIMARY KEY,"
		"	partName TEXT,"
		"	quantity INTEGER"
		");";

	// Execute the SQL statement to create the table
	rc = sqlite3_exec(db, createPartsTableSQL, 0, 0, 0);

	// ==== Table creation/check for PartDetail table ====

	// SQL statement for table creation
	// ... only performed if table does NOT exist
	const char* createPartsInfoTableSQL = "CREATE TABLE IF NOT EXISTS partsInfo ("
		"	partId TEXT PRIMARY KEY,"
		"	manufacturer TEXT,"
		"	manufacturerNumber TEXT,"
		"	siteOrderedFrom TEXT,"
		"	partCost DECIMAL(4,2)"
		");";

	// Execute the SQL statement to create the table
	rc = sqlite3_exec(db, createPartsInfoTableSQL, 0, 0, 0);

	// Variable to hold user input
	int userInput;

	int done = 0;

	do {
		// Print graphics
		PrintTitle();
		PrintMainMenu();

		// Get desired input
		scanf_s("%d", &userInput);

		// Act on 'userInput'
		switch (userInput) {
		case 1:
			// === Search Part === 
			break;
		case 2:
			// === Update Part === 
			break;
		case 3: {
			// === Get Part Info ===
			char partId[7];
			char partName[20];
			int quantity = 0;
			char manufacturer[20];
			char manufacturerNumber[20];
			char siteOrderedFrom[20];
			double partCost = 0.00;

			PrintInputMessage("Enter Part ID");
			printf("   Enter Part ID: ");
			scanf("%s", partId);
			printf("   Enter Part Name: ");
			scanf("%s", partName);
			printf("   Enter Quantity: ");
			scanf("%d", &quantity);
			printf("   Enter Part Manufacturer: ");
			scanf("%s", manufacturer);
			printf("   Enter Manufacturer Part ID: ");
			scanf("%s", manufacturerNumber);
			printf("   Enter Site Ordered From: ");
			scanf("%s", siteOrderedFrom);
			printf("   Enter Part Cost: ");
			scanf("%lf", &partCost);

			// === Add Part ===
			// SQL statement for inserting data into partsInfo table
			const char* insertPartsInfoSQL = "INSERT INTO partsInfo (partId, manufacturer, manufacturerNumber, siteOrderedFrom, partCost) "
				"VALUES (?, ?, ?, ?, ?);";

			// SQL statement for inserting data into parts table
			const char* insertPartsSQL = "INSERT INTO parts (partId, partName, quantity) VALUES (?, ?, ?);";

			// SQLite statement handles for executing prepared statements
			sqlite3_stmt* stmtInfo, * stmtParts;

			// Prepare the 'partsinfo' SQL statement for execution
			rc = sqlite3_prepare_v2(db, insertPartsInfoSQL, -1, &stmtInfo, 0);
			if (rc != SQLITE_OK) return rc;

			// Bind parameters for the 'partsInfo' insertion
			sqlite3_bind_text(stmtInfo, 1, partId, -1, SQLITE_STATIC);
			sqlite3_bind_text(stmtInfo, 2, manufacturer, -1, SQLITE_STATIC);
			sqlite3_bind_text(stmtInfo, 3, manufacturerNumber, -1, SQLITE_STATIC);
			sqlite3_bind_text(stmtInfo, 4, siteOrderedFrom, -1, SQLITE_STATIC);
			sqlite3_bind_double(stmtInfo, 5, partCost);

			// Execute the 'partsInfo' insertion
			rc = sqlite3_step(stmtInfo);
			sqlite3_finalize(stmtInfo);
			if (rc != SQLITE_DONE) return rc;

			// Prepare the 'parts' SQL statement for execution
			rc = sqlite3_prepare_v2(db, insertPartsSQL, -1, &stmtParts, 0);
			if (rc != SQLITE_OK) return rc;

			// Bind parameters for the 'parts; insertion
			sqlite3_bind_text(stmtParts, 1, partId, -1, SQLITE_STATIC);
			sqlite3_bind_text(stmtParts, 2, partName, -1, SQLITE_STATIC);
			sqlite3_bind_int(stmtParts, 3, quantity);

			// Execute the 'parts' insertion
			rc = sqlite3_step(stmtParts);
			sqlite3_finalize(stmtParts);

			break;
		}

		case 4:
			// === Remove Part === 
			break;
		case 5: {
			// === View Inventory === 
			ClearTerminal();

			// SQL statement to select partId, partName, and quantity
			const char* selectInventorySQL = "SELECT p.partId, p.partName, p.quantity, pi.partCost "
				"FROM parts p "
				"JOIN partsInfo pi ON p.partId = pi.partId;";

			// SQLite statement handle for executing the SELECT query
			sqlite3_stmt* stmt;

			// Prepare the SQL statement for execution
			int rc = sqlite3_prepare_v2(db, selectInventorySQL, -1, &stmt, 0);

			// Execute the SELECT query
			while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
				// Fetch the values from the current row
				const char* partId = (const char*)sqlite3_column_text(stmt, 0);
				const char* partName = (const char*)sqlite3_column_text(stmt, 1);
				int qty = sqlite3_column_int(stmt, 2);
				double unitCost = sqlite3_column_double(stmt, 3);

				// Display the information
				printf("Part ID: %s,     Part Name: %s,     Quantity: %d,     Part Cost: $%.2lf,     Inventory Value: $%.2lf\n", partId, partName, qty, unitCost, qty * unitCost);
			}

			// Finalize the statement
			sqlite3_finalize(stmt);

			char input[2];

			printf("\nRETURN TO MAIN MENU? (Y/N): ");
			scanf("%s", input);

			if (input[0] == 'n' || input[0] == 'N') {
				done = 1;
			}

			break;
		}
		case 6:
			// === Generate Report === 
			break;
		case 9:
			done = 1;

			break;
		default: {
			PrintTitle();

			const char* errorMessage = "INVALID INPUT!";

			PrintError(errorMessage);

			PrintMainMenu();

			break;
		}
		}
	} while (!done);

	sqlite3_close(db);

	return 0;
}