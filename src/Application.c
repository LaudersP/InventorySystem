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
	int error = 0;

	const char* errorMessage = "";

	do {
		// === Print graphics ===
		PrintTitle();

		// Print error if needed
		if (error) {
			PrintBannerMessage(errorMessage);
		}

		PrintMainMenu();

		// Get desired input
		scanf_s("%d", &userInput);

		// Act on 'userInput'
		switch (userInput) {
		case 1: {
			// === Search Part === 
			// Print graphics
			PrintTitle();
			PrintBannerMessage("TIP: DO NOT INCLUDE SPACES IN INPUTS!");
			PrintMessage("ENTER PART ID");

			// Data variable
			char partId[7];

			// Get desired part ID
			printf(" >> ");
			scanf("%s", partId);

			// SQL statement to select partId, partName, and quantity
			const char* selectInventorySQL = "SELECT p.partId, p.partName, p.quantity, pi.manufacturer, pi.manufacturerNumber, pi.siteOrderedFrom, pi.partCost "
				"FROM parts p "
				"JOIN partsInfo pi ON p.partId = pi.partId "
				"WHERE p.partId = ?;";

			// SQLite statement handle for executing the SELECT query
			sqlite3_stmt* stmt;

			// Prepare the SQL statement for execution
			int rc = sqlite3_prepare_v2(db, selectInventorySQL, -1, &stmt, 0);

			// Bind the partId as a parameter
			sqlite3_bind_text(stmt, 1, partId, -1, SQLITE_STATIC);

			// Execute the statement
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				// Fetch the values from the current row
				const char* id = (const char*)sqlite3_column_text(stmt, 0);

				// Check if the retrieved partId matches the entered one
				if (strcmp(id, partId) == 0) {
					const char* name = (const char*)sqlite3_column_text(stmt, 1);
					int qty = sqlite3_column_int(stmt, 2);
					const char* man = (const char*)sqlite3_column_text(stmt, 3);
					const char* manNum = (const char*)sqlite3_column_text(stmt, 4);
					const char* site = (const char*)sqlite3_column_text(stmt, 5);
					double unitCost = sqlite3_column_double(stmt, 6);

					PrintPartInfo(id, name, man, manNum, site, qty, unitCost);
				}
			}

			// Finalize the statement
			sqlite3_finalize(stmt);

			char input[2];

			printf("\n RETURN TO MAIN MENU? (Y/N): ");
			scanf("%s", input);

			if (input[0] == 'n' || input[0] == 'N') {
				done = 1;
			}

			error = 0;

			break;
		}
		case 2: {
			// === Update Part ===
			int partExists = -1;
			char partIdChar[7];

			// Check partId works
			do {
				PrintTitle();

				if (!partExists) {
					PrintBannerMessage("ERROR) PART DOES NOT EXIST!");
				}

				PrintBannerMessage("UPDATE PART");
				PrintMessage("PART TO UPDATE");

				printf(" >> ");
				scanf("%s", partIdChar);

				// SQL statement to check if partId exists
				const char* checkPartSQL = "SELECT 1 "
					"FROM parts "
					"WHERE partId = ? "
					"LIMIT 1;";

				// SQLite statement handle for executing the SELECT query
				sqlite3_stmt* checkStmt;

				// Prepare the SQL statement for checking partId existence
				int rc = sqlite3_prepare_v2(db, checkPartSQL, -1, &checkStmt, 0);

				// Bind the partId as a parameter
				sqlite3_bind_text(checkStmt, 1, partIdChar, -1, SQLITE_STATIC);

				// Execute the check statement
				if (sqlite3_step(checkStmt) == SQLITE_ROW) {
					partExists = 1;
				}
				else {
					partExists = 0;
				}

				// Finalize the check statement
				sqlite3_finalize(checkStmt);
			} while (partExists == 0);

			// Get update option
			int input = -1;
			do {
				PrintTitle();

				if ((input < 1 || input > 2) && input != -1) {
					PrintBannerMessage("ERROR) INVALID OPTION!");
				}

				PrintBannerMessage("UPDATE PART");
				PrintUpdateMenu();

				printf(" >> ");
				scanf("%d", &input);
			} while (input < 1 || input > 2);

			// Act on option
			switch (input) {
			case 1: {
				// === Part Info ===
				input = -1;

				// Get option
				do {
					PrintTitle();

					if ((input < 1 || input > 5) && input != -1) {
						PrintBannerMessage("ERROR) INVALID INPUT!");
					}

					PrintUpdatePartInfoMenu();

					printf(" >> ");
					scanf("%d", &input);
				} while (input < 1 || input > 2);

				// Act on option
				switch (input) {
				case 1: {
					// === Update Part Name ===
					PrintTitle();
					PrintBannerMessage("TIP: DO NOT INCLUDE SPACES IN INPUTS!");
					PrintMessage("ENTER NEW PART NAME");

					char partName[20];

					printf(" >> ");
					scanf("%s", partName);

					// Get old part name
					const char* nameSQL = "SELECT partId, partName "
						"FROM parts "
						"WHERE partId = ?;";

					// SQLite statement handle for executing the SELECT query
					sqlite3_stmt* stmt;

					// Prepare the SQL statement for execution
					int rc = sqlite3_prepare_v2(db, nameSQL, -1, &stmt, 0);

					// Bind the partId as a parameter
					sqlite3_bind_text(stmt, 1, partIdChar, -1, SQLITE_STATIC);

					char name[20] = "";

					// Execute the statement
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						// Fetch the values from the current row
						const char* id = (const char*)sqlite3_column_text(stmt, 0);

						// Check if the retrieved partId matches the entered one
						if (strcmp(id, partIdChar) == 0) {
							const char* retrievedName = (const char*)sqlite3_column_text(stmt, 1);

							// Copy the retrieved name to 'name'
							strncpy(name, retrievedName, 19);
							name[19] = '\0';
						}
					}

					// Finalize the statement
					sqlite3_finalize(stmt);

					// Ask user for confirmation
					PrintUpdateConfirm("PART NAME", name, partName);

					printf(" CONFIRM (Y/N): ");

					char input[2];
					scanf("%s", input);

					if (input[0] == 'y' || input[0] == 'Y') {
						// SQL statement for updating partName
						const char* updateNameSQL = "UPDATE parts "
							"SET partName = ?"
							"WHERE partId = ?;";

						// SQLite statement handle for executing the SELECT query
						sqlite3_stmt* stmt;

						// Prepare the SQL statement for execution
						int rc = sqlite3_prepare_v2(db, updateNameSQL, -1, &stmt, 0);

						// Bind the partId as a parameter
						sqlite3_bind_text(stmt, 1, partName, -1, SQLITE_STATIC);
						sqlite3_bind_text(stmt, 2, partIdChar, -1, SQLITE_STATIC);

						// Execute the statement
						rc = sqlite3_step(stmt);

						// Finalize the statement
						sqlite3_finalize(stmt);
					}

					break;
				}
				case 2: {
					// === Update Manufacturer ===
					PrintTitle();
					PrintBannerMessage("TIP: DO NOT INCLUDE SPACES IN INPUTS!");
					PrintMessage("ENTER NEW MANUFACTURER");

					char partManufacturer[20];

					printf(" >> ");
					scanf("%s", partManufacturer);

					// Get old part manufacturer
					const char* manufacturerSQL = "SELECT partId, manufacturer "
						"FROM partsInfo "
						"WHERE partId = ?;";

					// SQLite statement handle for executing the SELECT query
					sqlite3_stmt* stmt;

					// Prepare the SQL statement for execution
					int rc = sqlite3_prepare_v2(db, manufacturerSQL, -1, &stmt, 0);

					// Bind the partId as a parameter
					sqlite3_bind_text(stmt, 1, partIdChar, -1, SQLITE_STATIC);

					char manufacturer[20] = "";

					// Execute the statement
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						// Fetch the values from the current row
						const char* id = (const char*)sqlite3_column_text(stmt, 0);

						// Check if the retrieved partId matches the entered one
						if (strcmp(id, partIdChar) == 0) {
							const char* retrievedManufacturer = (const char*)sqlite3_column_text(stmt, 1);

							// Copy the retrieved name to 'manufacturer'
							strncpy(manufacturer, retrievedManufacturer, 19);
							manufacturer[19] = '\0';
						}
					}

					// Finalize the statement
					sqlite3_finalize(stmt);

					// Ask user for confirmation
					PrintUpdateConfirm("MANUFACTURER", manufacturer, partManufacturer);

					printf(" CONFIRM (Y/N): ");

					char input[2];
					scanf("%s", input);

					if (input[0] == 'y' || input[0] == 'Y') {
						// SQL statement for updating manufacturer
						const char* updateNameSQL = "UPDATE partsInfo "
							"SET manufacturer = ?"
							"WHERE partId = ?;";

						// SQLite statement handle for executing the SELECT query
						sqlite3_stmt* stmt;

						// Prepare the SQL statement for execution
						int rc = sqlite3_prepare_v2(db, updateNameSQL, -1, &stmt, 0);

						// Bind the partId as a parameter
						sqlite3_bind_text(stmt, 1, partManufacturer, -1, SQLITE_STATIC);
						sqlite3_bind_text(stmt, 2, partIdChar, -1, SQLITE_STATIC);

						// Execute the statement
						rc = sqlite3_step(stmt);

						// Finalize the statement
						sqlite3_finalize(stmt);
					}

					break;
				}
				case 3: {
					// === Update Manufacturer ID ===
					PrintTitle();
					PrintBannerMessage("TIP: DO NOT INCLUDE SPACES IN INPUTS!");
					PrintMessage("ENTER NEW MANUFACTURER ID");

					char partManufacturerID[20];

					printf(" >> ");
					scanf("%s", partManufacturerID);

					// Get old part manufacturer ID
					const char* manufacturerIdSQL = "SELECT partId, manufacturerNumber "
						"FROM partsInfo "
						"WHERE partId = ?;";

					// SQLite statement handle for executing the SELECT query
					sqlite3_stmt* stmt;

					// Prepare the SQL statement for execution
					int rc = sqlite3_prepare_v2(db, manufacturerIdSQL, -1, &stmt, 0);

					// Bind the partId as a parameter
					sqlite3_bind_text(stmt, 1, partIdChar, -1, SQLITE_STATIC);

					char manufacturerId[20] = "";

					// Execute the statement
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						// Fetch the values from the current row
						const char* id = (const char*)sqlite3_column_text(stmt, 0);

						// Check if the retrieved partId matches the entered one
						if (strcmp(id, partIdChar) == 0) {
							const char* retrievedManufacturerId = (const char*)sqlite3_column_text(stmt, 1);

							// Copy the retrieved name to 'manufacturerId'
							strncpy(manufacturerId, retrievedManufacturerId, 19);
							manufacturerId[19] = '\0';
						}
					}

					// Finalize the statement
					sqlite3_finalize(stmt);

					// Ask user for confirmation
					PrintUpdateConfirm("MANUFACTURER ID", manufacturerId, partManufacturerID);

					printf(" CONFIRM (Y/N): ");

					char input[2];
					scanf("%s", input);

					if (input[0] == 'y' || input[0] == 'Y') {
						// SQL statement for updating manufacturerNumber
						const char* updateNameSQL = "UPDATE partsInfo "
							"SET manufacturerNumber = ?"
							"WHERE partId = ?;";

						// SQLite statement handle for executing the SELECT query
						sqlite3_stmt* stmt;

						// Prepare the SQL statement for execution
						int rc = sqlite3_prepare_v2(db, updateNameSQL, -1, &stmt, 0);

						// Bind the partId as a parameter
						sqlite3_bind_text(stmt, 1, partManufacturerID, -1, SQLITE_STATIC);
						sqlite3_bind_text(stmt, 2, partIdChar, -1, SQLITE_STATIC);

						// Execute the statement
						rc = sqlite3_step(stmt);

						// Finalize the statement
						sqlite3_finalize(stmt);
					}

					break;
				}
				case 4: {
					// === Update Ordered From ===
					PrintTitle();
					PrintBannerMessage("TIP: DO NOT INCLUDE SPACES IN INPUTS!");
					PrintMessage("ENTER NEW SITE ORDERED FROM");

					char partSite[20];

					printf(" >> ");
					scanf("%s", partSite);

					// Get old site ordered from
					const char* siteSQL = "SELECT partId, siteOrderedFrom "
						"FROM partsInfo "
						"WHERE partId = ?;";

					// SQLite statement handle for executing the SELECT query
					sqlite3_stmt* stmt;

					// Prepare the SQL statement for execution
					int rc = sqlite3_prepare_v2(db, siteSQL, -1, &stmt, 0);

					// Bind the partId as a parameter
					sqlite3_bind_text(stmt, 1, partIdChar, -1, SQLITE_STATIC);

					char site[20] = "";

					// Execute the statement
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						// Fetch the values from the current row
						const char* id = (const char*)sqlite3_column_text(stmt, 0);

						// Check if the retrieved partId matches the entered one
						if (strcmp(id, partIdChar) == 0) {
							const char* retrievedSite = (const char*)sqlite3_column_text(stmt, 1);

							// Copy the retrieved name to 'site'
							strncpy(site, retrievedSite, 19);
							site[19] = '\0';
						}
					}

					// Finalize the statement
					sqlite3_finalize(stmt);

					// Ask user for confirmation
					PrintUpdateConfirm("SITE ORDERED FROM", site, partSite);

					printf(" CONFIRM (Y/N): ");

					char input[2];
					scanf("%s", input);

					if (input[0] == 'y' || input[0] == 'Y') {
						// SQL statement for updating siteOrderedFrom
						const char* updateNameSQL = "UPDATE partsInfo "
							"SET siteOrderedFrom = ?"
							"WHERE partId = ?;";

						// SQLite statement handle for executing the SELECT query
						sqlite3_stmt* stmt;

						// Prepare the SQL statement for execution
						int rc = sqlite3_prepare_v2(db, updateNameSQL, -1, &stmt, 0);

						// Bind the partId as a parameter
						sqlite3_bind_text(stmt, 1, partSite, -1, SQLITE_STATIC);
						sqlite3_bind_text(stmt, 2, partIdChar, -1, SQLITE_STATIC);

						// Execute the statement
						rc = sqlite3_step(stmt);

						// Finalize the statement
						sqlite3_finalize(stmt);
					}

					break;
				}
				case 5: {
					// === Update Cost ===
					PrintTitle();
					PrintBannerMessage("TIP: DO NOT INCLUDE SPACES IN INPUTS!");
					PrintMessage("ENTER NEW PART COST");

					double partCost;

					printf(" >> ");
					scanf("%lf", &partCost);

					// Get old part cost
					const char* partCostSQL = "SELECT partId, partCost "
						"FROM partsInfo "
						"WHERE partId = ?;";

					// SQLite statement handle for executing the SELECT query
					sqlite3_stmt* stmt;

					// Prepare the SQL statement for execution
					int rc = sqlite3_prepare_v2(db, partCostSQL, -1, &stmt, 0);

					// Bind the partId as a parameter
					sqlite3_bind_text(stmt, 1, partIdChar, -1, SQLITE_STATIC);

					char cost[20] = "";

					// Execute the statement
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						// Fetch the values from the current row
						const char* id = (const char*)sqlite3_column_text(stmt, 0);

						// Check if the retrieved partId matches the entered one
						if (strcmp(id, partIdChar) == 0) {
							double unitCost = sqlite3_column_double(stmt, 1);

							// Copy the retrieved cost
							sprintf(cost, "%.2f", unitCost);

							printf("%.2f", unitCost);
						}
					}

					// Finalize the statement
					sqlite3_finalize(stmt);

					char partCostChar[20] = "";

					// Copy new cost to char
					sprintf(partCostChar, "%.2f", partCost);

					// Ask user for confirmation
					PrintUpdateConfirm("PART COST", cost, partCostChar);

					printf(" CONFIRM (Y/N): "); 
					
					char input[2];
					scanf("%s", input);

					if (input[0] == 'y' || input[0] == 'Y') {
						// SQL statement for updating siteOrderedFrom
						const char* partCostSQL = "UPDATE partsInfo "
							"SET partCost = ?"
							"WHERE partId = ?;";

						// SQLite statement handle for executing the SELECT query
						sqlite3_stmt* stmt;

						// Prepare the SQL statement for execution
						int rc = sqlite3_prepare_v2(db, partCostSQL, -1, &stmt, 0);

						// Bind the partId as a parameter
						sqlite3_bind_double(stmt, 1, partCost, -1, SQLITE_STATIC);
						sqlite3_bind_text(stmt, 2, partIdChar, -1, SQLITE_STATIC);

						// Execute the statement
						rc = sqlite3_step(stmt);

						// Finalize the statement
						sqlite3_finalize(stmt);
					}

					break;
				}
				}

				break;
			}
			case 2: {
				// === Quantity ===
				// Get update option
				int input = -1;
				do {
					PrintTitle();

					if ((input < 1 || input > 2) && input != -1) {
						PrintBannerMessage("ERROR) INVALID OPTION!");
					}

					PrintUpdateQuantity();

					printf(" >> ");
					scanf("%d", &input);
				} while (input < 1 || input > 2);

				int qty = 0;

				// Act on selected option
				switch (input) {
				case 1: 
					PrintTitle();
					PrintBannerMessage("ADD QUANTITY");
					PrintMessage("ENTER QUANTITY AMOUNT");

					printf(" >> ");
					scanf("%d", &qty);

					break;
				case 2: 

					PrintTitle();
					PrintBannerMessage("REMOVE QUANTITY");
					PrintMessage("ENTER QUANTITY AMOUNT");

					printf(" >> ");
					scanf("%d", &qty);

					qty *= -1;

					break;
				}

				// == Get current quantity ==
				const char* getQuantitySQL = "SELECT partId, quantity "
					"FROM parts "
					"WHERE partId = ?;";

				// SQLite statement handle for executing the SELECT query
				sqlite3_stmt* stmt;

				// Prepare the SQL statement for execution
				int rc = sqlite3_prepare_v2(db, getQuantitySQL, -1, &stmt, 0);

				// Bind the partId as a parameter
				sqlite3_bind_text(stmt, 1, partIdChar, -1, SQLITE_STATIC);

				int quantity = 0;
				char quantityChar[20] = "";

				// Execute the statement
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					// Fetch the values from the current row
					const char* id = (const char*)sqlite3_column_text(stmt, 0);

					// Check if the retrieved partId matches the entered one
					if (strcmp(id, partIdChar) == 0) {
						quantity= sqlite3_column_int(stmt, 1);

						// Copy the retrieved cost
						sprintf(quantityChar, "%d", quantity);
					}
				}

				qty += quantity;

				char qtyChar[20] = "";
				sprintf(qtyChar, "%d", qty);

				// Finalize the statement
				sqlite3_finalize(stmt);

				PrintUpdateConfirm("QUANTITY", quantityChar, qtyChar);

				char userInput[2];
				printf(" CONFIRM (Y/N): ");
				scanf("%s", userInput);

				// == Update quantity ==
				if (userInput[0] == 'y' || userInput[0] == 'Y') {
					// SQL statement for updating quantity
					const char* updateQuantitySQL = "UPDATE parts "
						"SET quantity = ? "
						"WHERE partId = ?;";

					// SQLite statement handle for executing the SELECT query
					sqlite3_stmt* updateStmt;

					// Prepare the SQL statement for execution
					rc = sqlite3_prepare_v2(db, updateQuantitySQL, -1, &updateStmt, 0);

					// Bind the partId as a parameter
					sqlite3_bind_int(updateStmt, 1, qty);
					sqlite3_bind_text(updateStmt, 2, partIdChar, -1, SQLITE_STATIC);

					// Execute the statement
					rc = sqlite3_step(updateStmt);

					// Finalize the statement
					sqlite3_finalize(updateStmt);
				}
			}
			}

			error = 0;

			break;
		}
		case 3: {
			// === Add Part ===
			char partId[7];
			char partName[20];
			int quantity = 0;
			char manufacturer[20];
			char manufacturerNumber[20];
			char siteOrderedFrom[20];
			double partCost = 0.00;

			PrintTitle();
			PrintBannerMessage("TIP: DO NOT INCLUDE SPACES IN INPUTS!");
			PrintMessage("ADD PART");

			printf("   Enter Part ID: ");
			scanf("%s", partId);

			// SQL statement to check if partId exists
			const char* checkPartIdSQL = "SELECT 1 "
				"FROM parts "
				"WHERE partId = ? "
				"LIMIT 1;";

			// SQLite statement handle for executing the SELECT query
			sqlite3_stmt* checkStmt;

			// Prepare the SQL statement for checking partId existence
			rc = sqlite3_prepare_v2(db, checkPartIdSQL, -1, &checkStmt, 0);

			// Bind the partId as a parameter
			sqlite3_bind_text(checkStmt, 1, partId, -1, SQLITE_STATIC);

			// Execute the check statement
			if (sqlite3_step(checkStmt) == SQLITE_ROW) {
				error = 1;

				// partId alread exists
				errorMessage = "ERROR) PART ID ALREADY EXISTS!";

				// Finalize the check statement
				sqlite3_finalize(checkStmt);

				break;
			}

			// Finalize the check statement
			sqlite3_finalize(checkStmt);

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
			printf("   Enter Part Cost: $");
			scanf("%lf", &partCost);

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

			error = 0;

			break;
		}
		case 4: {
			// === Remove Part === 
			PrintClearTerminal();
			PrintTitle();
			PrintBannerMessage("REMOVE PART");
			PrintMessage("Enter Part ID");

			// Data variable
			char partId[7];

			// Get desired part ID
			printf(" >> ");
			scanf("%s", partId);

			// SQL statement to select partId, partName, and quantity
			const char* selectInventorySQL = "SELECT p.partId, p.partName, p.quantity, pi.manufacturer, pi.manufacturerNumber, pi.siteOrderedFrom, pi.partCost "
				"FROM parts p "
				"JOIN partsInfo pi ON p.partId = pi.partId "
				"WHERE p.partId = ?;";

			// SQLite statement handle for executing the SELECT query
			sqlite3_stmt* stmt;

			// Prepare the SQL statement for execution
			int rc = sqlite3_prepare_v2(db, selectInventorySQL, -1, &stmt, 0);

			// Bind the partId as a parameter
			sqlite3_bind_text(stmt, 1, partId, -1, SQLITE_STATIC);

			// Execute the statement
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				// Fetch the values from the current row
				const char* id = (const char*)sqlite3_column_text(stmt, 0);

				// Check if the retrieved partId matches the entered one
				if (strcmp(id, partId) == 0) {
					const char* name = (const char*)sqlite3_column_text(stmt, 1);
					int qty = sqlite3_column_int(stmt, 2);
					const char* man = (const char*)sqlite3_column_text(stmt, 3);
					const char* manNum = (const char*)sqlite3_column_text(stmt, 4);
					const char* site = (const char*)sqlite3_column_text(stmt, 5);
					double unitCost = sqlite3_column_double(stmt, 6);

					PrintPartInfo(id, name, man, manNum, site, qty, unitCost);
				}
			}

			// Finalize the statement
			sqlite3_finalize(stmt);

			char input[2];

			printf("\n ARE YOU SURE? (Y/N): ");
			scanf("%s", input);

			if (input[0] == 'n' || input[0] == 'N') {
				break;
			}

			// SQL statement to remove desired part from parts
			const char* removePart = "DELETE FROM parts "
				"WHERE partId = ?;";

			// SQL statement to remove desired part from partInfo
			const char* removePartInfo = "DELETE FROM partsInfo "
				"WHERE partId = ?;";

			// SQLite statement handle for executing the REMOVE query
			sqlite3_stmt* stmtPart;
			sqlite3_stmt* stmtPartInfo;

			// Prepare the SQL statement for execution
			rc = sqlite3_prepare_v2(db, removePart, -1, &stmtPart, 0);

			// Bind the partId as a parameter
			sqlite3_bind_text(stmtPart, 1, partId, -1, SQLITE_STATIC);

			// Execute the statement
			rc = sqlite3_step(stmtPart);

			// Finalize the statement
			sqlite3_finalize(stmtPart);

			// Prepare the SQL statement for execution
			rc = sqlite3_prepare_v2(db, removePartInfo, -1, &stmtPartInfo, 0);

			// Bind the partId as a parameter
			sqlite3_bind_text(stmtPartInfo, 1, partId, -1, SQLITE_STATIC);

			// Execute the statement
			rc = sqlite3_step(stmtPart);

			// Finalize the statement
			sqlite3_finalize(stmtPartInfo);

			error = 0;

			break;
		}
		case 5: {
			// === View Inventory === 
			PrintClearTerminal();
			PrintTitle();
			PrintBannerMessage("INVENTORY");

			// SQL statement to select partId, partName, and quantity
			const char* selectInventorySQL = "SELECT p.partId, p.partName, p.quantity, pi.partCost "
				"FROM parts p "
				"JOIN partsInfo pi ON p.partId = pi.partId "
				"ORDER BY p.partId ";

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
				//printf("Part ID: %s,     Part Name: %s,     Quantity: %d,     Part Cost: $%.2lf,     Inventory Value: $%.2lf\n", partId, partName, qty, unitCost, qty * unitCost);
				PrintInventory(partId, partName, qty);
			}

			GraphicBottom();

			// Finalize the statement
			sqlite3_finalize(stmt);

			char input[2];

			printf("\n RETURN TO MAIN MENU? (Y/N): ");
			scanf("%s", input);

			if (input[0] == 'n' || input[0] == 'N') {
				done = 1;
			}

			error = 0;

			break;
		}
		case 9:
			done = 1;

			break;
		default: {
			error = 1;

			errorMessage = "INVALID INPUT!";

			break;
		}
		}
	} while (!done);

	sqlite3_close(db);

	return 0;
}