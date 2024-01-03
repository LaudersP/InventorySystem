#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sqlite-amalgamation-3440200\sqlite3.h>
#include <menus.h>

#define DATABASE_FILE_PATH "InventorySystem.db"

void GetPartInfo(char** id, char** name, int* qty, char** man, char** manNum, char** site, char** url, double* unitCost);

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
		"	link TEXT,"
		"	partCost DECIMAL(4,2)"
		");";

	// Execute the SQL statement to create the table
	rc = sqlite3_exec(db, createPartsInfoTableSQL, 0, 0, 0);

	// ==== Table data variables ====
	char* partId;
	char* partName;
	int quantity;
	char* manufacturer;
	char* manufacturerNumber;
	char* siteOrderedFrom;
	char* link;
	double partCost;

	// Variable to hold user input
	int userInput;

	// Print graphics
	PrintTitle();
	PrintMainMenu();

	do {
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
			// === Add Part ===  
			// Assign values to data variables
			GetPartInfo(&partId, &partName, &quantity, &manufacturer, &manufacturerNumber, &siteOrderedFrom, &link, &partCost);
		
			// SQL statement for inserting data into partsInfo table
			const char* insertPartsInfoSQL = "INSERT INTO partsInfo (partId, manufacturer, manufacturerNumber, siteOrderedFrom, link, partCost) "
				"VALUES (?, ?, ?, ?, ?, ?);";

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
			sqlite3_bind_text(stmtInfo, 5, link, -1, SQLITE_STATIC);
			sqlite3_bind_double(stmtInfo, 6, partCost);

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
		case 5:
			// === View Inventory === 
			break;
		case 6:
			// === Generate Report === 
			break;
		case 9:
			break;
		default: {
			PrintTitle();

			const char* errorMessage = "INVALID INPUT!";

			PrintError(errorMessage);

			PrintMainMenu();

			break;
		}	
		}
	} while (userInput != 9);

	sqlite3_close(db);

	return 0;
}

// Function for getting part detail from user
void GetPartInfo(char** id, char** name, int* qty, char** man, char** manNum, char** site, char** url, double* unitCost) {
	*id = _strdup("P004");
	*name = _strdup("SamplePart");
	*qty = 10;
	*man = _strdup("SampleManufacturer");
	*manNum = _strdup("1234");
	*site = _strdup("SampleSite");
	*url = _strdup("https://samplelink.com");
	*unitCost = 1.23;
}