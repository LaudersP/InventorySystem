#include <menus.h>

// Function to clear the terminal
void ClearTerminal() {
#ifdef _WIN32 // For Windows
	system("cls");
#else // Assuming Unix-like system
	system("clear");
#endif
}

void PrintTitle() {
	ClearTerminal();

	printf("%c", 218);

	for (int i = 0; i < 101; i++) {
		printf("%c", 196);
	}

	printf("%c\n", 191);

	const char* titleLine1 = "    ____                      __                   _____            __               ";
	const char* titleLine2 = "   /  _/___ _   _____  ____  / /_____  _______  __/ ___/__  _______/ /____  ____ ___ ";
	const char* titleLine3 = "   / // __ \\ | / / _ \\/ __ \\/ __/ __ \\/ ___/ / / /\\__ \\/ / / / ___/ __/ _ \\/ __ `__ \\";
	const char* titleLine4 = " _/ // / / / |/ /  __/ / / / /_/ /_/ / /  / /_/ /___/ / /_/ (__  ) /_/  __/ / / / / /";
	const char* titleLine5 = "/___/_/ /_/|___/\\___/_/ /_/\\__/\\____/_/   \\__, //____/\\__, /____/\\__/\\___/_/ /_/ /_/ ";
	const char* titleLine6 = "/____/";

	printf("%c        %s        %c\n", 179, titleLine1, 179);
	printf("%c        %s        %c\n", 179, titleLine2, 179);
	printf("%c        %s        %c\n", 179, titleLine3, 179);
	printf("%c        %s        %c\n", 179, titleLine4, 179);
	printf("%c        %s        %c\n", 179, titleLine5, 179);

	printf("%c", 195);

	for (int i = 0; i < 49; i++) {
		printf("%c", 196);
	}

	printf("%s", titleLine6);

	for (int i = 0; i < 6; i++) {
		printf("%c", 196);
	}

	printf("%s", titleLine6);

	for (int i = 0; i < 34; i++) {
		printf("%c", 196);
	}

	printf("%c\n", 180);
}

void PrintMainMenu() {
	PrintFillerLine();

	printf("%c   (1) SEARCH PART    ", 179);

	FinishLine(79);

	printf("%c   (2) UPDATE PART    ", 179);

	FinishLine(79);

	printf("%c   (3) ADD PART       ", 179);

	FinishLine(79);

	printf("%c   (4) REMOVE PART    ", 179);

	FinishLine(79);

	printf("%c   (5) VIEW INVENTORY ", 179);

	FinishLine(79);

	printf("%c   (6) GENERATE REPORT", 179);

	FinishLine(79);

	printf("%c   (9) EXIT           ", 179);

	FinishLine(79);

	PrintFillerLine();

	for (int i = 0; i < 103; i++) {
		if (i == 0) {
			printf("%c", 192);
		}
		else if (i == 102) {
			printf("%c", 217);
		}
		else {
			printf("%c", 196);
		}
	}

	printf("\n >> ");
}

void PrintFillerLine() {
	for (int i = 0; i < 103; i++) {
		if (i == 0) {
			printf("%c", 179);
		}
		else if (i == 102) {
			printf("%c\n", 179);
		}
		else {
			printf(" ");
		}
	}
}

void FinishLine(int length) {
	for (int i = 0; i < length + 1; i++) {
		if (i == length) {
			printf("%c\n", 179);
		}
		else {
			printf(" ");
		}
	}
}

void PrintError(const char* error) {
	printf("%c   ERROR) ", 179);

	size_t errorLength = strlen(error);

	printf("%s", error);

	FinishLine(91 - (int)errorLength);

	for (int i = 0; i < 103; i++) {
		if (i == 0) {
			printf("%c", 195);
		}
		else if (i == 102) {
			printf("%c\n", 180);
		}
		else {
			printf("%c", 196);
		}
	}
}

void PrintInputMessage(const char* inputMessage) {
	ClearTerminal();

	PrintTitle();
	PrintFillerLine();

	const char* tipMessaage = "TIP: DO NOT INCLUDE SPACES IN INPUTS!";

	printf("%c   %s", 179, tipMessaage);

	FinishLine(98 - (int)strlen(tipMessaage));

	PrintFillerLine();

	for (int i = 0; i < 103; i++) {
		if (i == 0) {
			printf("%c", 192);
		}
		else if (i == 102) {
			printf("%c\n", 217);
		}
		else {
			printf("%c", 196);
		}
	}
}

void ConvertToUpperCase(char* str) {
	for (int i = 0; i < strlen(str); i++) {
		str[i] = toupper((unsigned char)str[i]);
	}
}

void PrintPartInfo(const char* id, const char* name, const char* man, const char* manNum, const char* site, const int qty, const double unitCost) {
	ClearTerminal();

	PrintTitle();
	PrintFillerLine();

	// Convert strings to uppercase
	char idUpper[100], nameUpper[100], manUpper[100], manNumUpper[100], siteUpper[100], qtyChar[100], unitCostChar[100], partValueChar[100];

	strcpy_s(idUpper, sizeof(idUpper), id);
	strcpy_s(nameUpper, sizeof(nameUpper), name);
	strcpy_s(manUpper, sizeof(manUpper), man);
	strcpy_s(manNumUpper, sizeof(manNumUpper), manNum);
	strcpy_s(siteUpper, sizeof(siteUpper), site);

	ConvertToUpperCase(idUpper);
	ConvertToUpperCase(nameUpper);
	ConvertToUpperCase(manUpper);
	ConvertToUpperCase(manNumUpper);
	ConvertToUpperCase(siteUpper);

	printf("%c   PART ID: %s", 179, idUpper);
	FinishLine(89 - (int)strlen(idUpper));

	printf("%c   PART NAME: %s", 179, nameUpper);
	FinishLine(87 - (int)strlen(nameUpper));

	printf("%c   MANUFACTURER: %s", 179, manUpper);
	FinishLine(84 - (int)strlen(manUpper));

	printf("%c   MANUFACTURER ID: %s", 179, manNumUpper);
	FinishLine(81 - (int)strlen(manNumUpper));

	printf("%c   ORDERED FROM: %s", 179, siteUpper);
	FinishLine(84 - (int)strlen(siteUpper));

	sprintf_s(qtyChar, sizeof(qtyChar), "%d", (int)fabs(qty));
	printf("%c   QUANTITY: %s", 179, qtyChar);
	FinishLine(88 - (int)strlen(qtyChar));

	sprintf_s(unitCostChar, sizeof(unitCostChar), "%.2f", fabs(unitCost));
	printf("%c   PART COST: %s", 179, unitCostChar);
	FinishLine(88 - (int)strlen(unitCostChar) - 1);

	double partValue = qty * unitCost;
	sprintf_s(partValueChar, sizeof(partValueChar), "%.2f", fabs(partValue));
	printf("%c   PART COST: %s", 179, partValueChar);
	FinishLine(88 - (int)strlen(partValueChar) - 1);

	PrintFillerLine();

	for (int i = 0; i < 103; i++) {
		if (i == 0) {
			printf("%c", 192);
		}
		else if (i == 102) {
			printf("%c\n", 217);
		}
		else {
			printf("%c", 196);
		}
	}
}