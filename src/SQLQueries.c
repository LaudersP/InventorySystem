#include <SQLQueries.h>

// Function for item query (type: text)
void SelectTextSQL(sqlite3* database, const char* table, const char* partId, const char* attribute, int resultSize, char* result) {
	const char* selectSQL = "SELECT partId, %s "
		"FROM %s "
		"WHERE partId = ?;";

	// Allocate memory for the complete SQL statement
	int sqlSize = strlen(selectSQL) + strlen(attribute) + strlen(table) + 1;
	char* completeSQL = (char*)malloc(sqlSize);

	// Format the complete SQL statement
	snprintf(completeSQL, sqlSize, selectSQL, attribute, table);

	// SQLite statment
	sqlite3_stmt* stmt;

	// Prepare the statement
	int rc = sqlite3_prepare_v2(database, completeSQL, -1, &stmt, 0);

	// Bind parameters partId
	sqlite3_bind_text(stmt, 1, partId, -1, SQLITE_STATIC);

	// Execute the statement
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		// Fetch the values from the current row
		const char* id = (const char*)sqlite3_column_text(stmt, 0);

		// Check if the retrieved partId matches the entered one
		if (strcmp(id, partId) == 0) {
			const char* retrievedValue = (const char*)sqlite3_column_text(stmt, 1);

			// Copy the retrieved value to the result buffer
			strncpy(result, retrievedValue, resultSize - 1);
			result[resultSize - 1] = '\0';
		}
	}

	// Free memory
	free(completeSQL);

	// Finalize the statement
	sqlite3_finalize(stmt);
}

// Function for item query (type: double)
void SelectDoubleSQL(sqlite3* database, const char* table, const char* partId, const char* attribute, double* result) {
	const char* selectSQL = "SELECT partId, %s "
		"FROM %s "
		"WHERE partId = ?;";

	// Allocate memory for the complete SQL statement
	int sqlSize = strlen(selectSQL) + strlen(attribute) + strlen(table) + 1;
	char* completeSQL = (char*)malloc(sqlSize);

	// Format the complete SQL statement
	snprintf(completeSQL, sqlSize, selectSQL, attribute, table);

	// SQLite statement handle for executing the SELECT query
	sqlite3_stmt* stmt;

	// Prepare the SQL statement for execution
	int rc = sqlite3_prepare_v2(database, completeSQL, -1, &stmt, 0);

	// Bind the partId as a parameter
	sqlite3_bind_text(stmt, 1, partId, -1, SQLITE_STATIC);

	// Execute the statement
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		// Fetch the values from the current row
		const char* id = (const char*)sqlite3_column_text(stmt, 0);

		// Check if the retrieved partId matches the entered one
		if (strcmp(id, partId) == 0) {
			*result = sqlite3_column_double(stmt, 1);
		}
	}

	// Free memory
	free(completeSQL);

	// Finalize the statement
	sqlite3_finalize(stmt);
}

// Function for item query (type: int)
void SelectIntSQL(sqlite3* database, const char* table, const char* partId, const char* attribute, int* result) {
	const char* selectSQL = "SELECT partId, %s "
		"FROM %s "
		"WHERE partId = ?;";

	// Allocate memory for the complete SQL statement
	int sqlSize = strlen(selectSQL) + strlen(attribute) + strlen(table) + 1;
	char* completeSQL = (char*)malloc(sqlSize);

	// Format the complete SQL statement
	snprintf(completeSQL, sqlSize, selectSQL, attribute, table);

	// SQLite statement handle for executing the SELECT query
	sqlite3_stmt* stmt;

	// Prepare the SQL statement for execution
	int rc = sqlite3_prepare_v2(database, completeSQL, -1, &stmt, 0);

	// Bind the partId as a parameter
	sqlite3_bind_text(stmt, 1, partId, -1, SQLITE_STATIC);

	// Execute the statement
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		// Fetch the values from the current row
		const char* id = (const char*)sqlite3_column_text(stmt, 0);

		// Check if the retrieved partId matches the entered one
		if (strcmp(id, partId) == 0) {
			*result = sqlite3_column_int(stmt, 1);
		}
	}

	// Free memory
	free(completeSQL);

	// Finalize the statement
	sqlite3_finalize(stmt);
}