#include <menus.h>

// === Main Print Functions
// Function to clear the terminal
void PrintClearTerminal() {
#ifdef _WIN32 // For Windows
	system("cls");
#else // Assuming Unix-like system
	system("clear");
#endif
}

// Function to print title
void PrintTitle() {
	PrintClearTerminal();

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

// Function to print the main menu
void PrintMainMenu() {
	FillerLine();

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

	printf("%c   (9) EXIT           ", 179);

	FinishLine(79);

	FillerLine();

	GraphicBottom();

	printf("\n >> ");
}

// Function to print a message banner
void PrintBannerMessage(const char* bannerMessage) {
	printf("%c   %s", 179, bannerMessage);

	FinishLine(98 - (int)strlen(bannerMessage));

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

// Function to print input message
void PrintMessage(const char* inputMessage) {
	FillerLine();

	printf("%c   %s", 179, inputMessage);

	FinishLine(98 - (int)strlen(inputMessage));

	FillerLine();

	GraphicBottom();
}

// Function to print inventory
void PrintInventory(const char* id, const char* name, const int qty) {
	printf("%c%c", 179, 218);

	for (int i = 0; i < 99; i++) {
		printf("%c", 196);
	}

	printf("%c%c\n", 191, 179);

	printf("%c%c   PART ID: %s", 179, 179, id);
	
	for (int i = 0; i < 87 - (int)strlen(id); i++) {
		printf(" ");
	}

	printf("%c%c\n", 179, 179);

	printf("%c%c   PART NAME: %s", 179, 179, name);

	for (int i = 0; i < 85 - (int)strlen(name); i++) {
		printf(" ");
	}

	printf("%c%c\n", 179, 179);

	char qtyChar[20];

	sprintf_s(qtyChar, sizeof(qtyChar), "%d", (int)fabs(qty));

	printf("%c%c   QUANTITY: %s", 179, 179, qtyChar);

	for (int i = 0; i < 86 - (int)strlen(qtyChar); i++) {
		printf(" ");
	}

	printf("%c%c\n", 179, 179);

	for (int i = 0; i < 103; i++) {
		if (i == 0) {
			printf("%c", 179);
		}
		else if (i == 1) {
			printf("%c", 192);
		}
		else if (i == 101) {
			printf("%c", 217);
		}
		else if (i == 102) {
			printf("%c\n", 179);
		}
		else {
			printf("%c", 196);
		}
	}
}

// Functio to print part info
void PrintPartInfo(const char* id, const char* name, const char* man, const char* manNum, const char* site, const int qty, const double unitCost) {
	PrintClearTerminal();

	PrintTitle();

	PrintBannerMessage("PART INFO");

	FillerLine();

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
	printf("%c   PART COST: $%s", 179, unitCostChar);
	FinishLine(87 - (int)strlen(unitCostChar) - 1);

	double partValue = qty * unitCost;
	sprintf_s(partValueChar, sizeof(partValueChar), "%.2f", fabs(partValue));
	printf("%c   PART VALUE: $%s", 179, partValueChar);
	FinishLine(86 - (int)strlen(partValueChar) - 1);

	FillerLine();

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

void PrintUpdateMenu() {
	FillerLine();

	printf("%c   (1) PART INFO", 179);
	FinishLine(85);

	printf("%c   (2) QUANTITY", 179);
	FinishLine(86);

	FillerLine();

	GraphicBottom();
}

void PrintUpdatePartInfoMenu() {
	FillerLine();

	printf("%c   (1) PART NAME", 179);
	FinishLine(85);

	printf("%c   (2) MANUFACTURER", 179);
	FinishLine(82);

	printf("%c   (3) MANUFACTURER ID", 179);
	FinishLine(79);

	printf("%c   (4) ORDERED FROM", 179);
	FinishLine(82);

	printf("%c   (5) COST", 179);
	FinishLine(90);

	FillerLine();

	GraphicBottom();
}

void PrintUpdateConfirm(const char* infoBeingUpdated, const char* oldInfo, const char* newInfo) {
	PrintTitle();
	PrintBannerMessage("CONFIRM PART EDIT!");

	FillerLine();

	printf("%c   UPDATE %s: %s -> %s", 179, infoBeingUpdated, oldInfo, newInfo);

	FinishLine(85 - (int)strlen(infoBeingUpdated) - (int)strlen(oldInfo) - (int)strlen(newInfo));

	FillerLine();
	GraphicBottom();
}

void PrintUpdateQuantity() {
	PrintBannerMessage("PART QUANTITY UPDATE");
	FillerLine();

	printf("%c   1) ADD QUANTITY", 179);
	FinishLine(83);

	printf("%c   2) REMOVE QUANTITY", 179);
	FinishLine(80);

	FillerLine();

	GraphicBottom();

}

// === Sub Called Functions ===
// Function to output a blank line
void FillerLine() {
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

// Function to print the bottom of graphic section
void GraphicBottom() {
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

// Function to end the line
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

// Function to upper case a char
void ConvertToUpperCase(char* str) {
	for (int i = 0; i < strlen(str); i++) {
		str[i] = toupper((unsigned char)str[i]);
	}
}