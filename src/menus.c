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