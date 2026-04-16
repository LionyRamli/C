#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void cleanBuffer() {
	int c = 0;
	while ((c = getchar()) != '\n' && c!= EOF);
}

int readString(char*buffer, int size, const char* prompt) {
	printf("%s", prompt);
	if (fgets(buffer, size, stdin) == NULL) return 0;

	if (buffer[0] == '\n') {
		printf("You dont input anything bro\n");
		return 0;
	}

	if (strchr(buffer, '\n') == NULL) {
		printf("Your input exceeds maximum length(200 characters)!,write less pls\n");
		cleanBuffer;
		return 0;
	}
	int see = 0;
	for (int i = 0; buffer[i] != '\0' && buffer[i] != '\0'; i++) {
		if (isalnum(buffer[i])) {
			see++;
		}
	}
	if (see == 0) {
		printf("I KNOW YOU DONT INPUT ANYTHING, WRITE SOMETHING\n");
		return 0;
	}
	buffer[strcspn(buffer, "\n")] = '\0';
	return 1;
}

int loadAphorism(char aphoArray[][200]) {
	FILE* fp = fopen("aphorism.txt", "r");
	int count = 0;

	if (fp == NULL) {
		return 0;
	}

	while (fgets(aphoArray[count], 200, fp) != NULL) {
		aphoArray[count][strcspn(aphoArray[count], "\n")] = '\0';
		if (strlen(aphoArray[count]) > 0) {
			count++;
		}if (count >= 100)break;
	}
	fclose(fp);
	return count;
}
void addAphorism(char aphoArray[][200], int* count) {
	if (*count > 100) {
		printf("Sorry no more aphorism, you already write 100\n");
		return;
	}
	char newQuote[200] = { '\0' };;
	while (1) {
		if (!readString(newQuote, sizeof(newQuote), "Input New Aphorism (press enter to submit): \n")) continue;
		break;
	}
	strcpy(aphoArray[*count], newQuote);
	(*count)++;

	FILE* fp = fopen("aphorism.txt", "a");
	if (fp == NULL) {
		printf("Cannot open file to save!\n");
		return;
	}
	fprintf(fp, "%s\n", newQuote);
	fclose(fp);

	printf("Yay! New line just added\n");
}

void displayRandom(char aphoArray[][200], int count) {
	if (count == 0) {
		printf("No aphorism available, please add first\n");
		return;
	}

	int randomIndex = rand() % count;
	printf("Random Aphorsim: %s\n", aphoArray[randomIndex]);
}

void displayAll(char aphoArray[][200], int count) {
	if (count == 0) {
		printf("Nothing here\n");
		return;
	}
	printf("All aphorism\n");
	for (int i = 0; i < count; i++) {
		printf("%d.%s\n", i + 1, aphoArray[i]);
	}
}
int main() {
	char apho[100][200] = { '\0' };
	int count = 0;
	char menuInput[10] = { '\0' };
	srand(time(NULL));

	count = loadAphorism(apho);

	while (1) {
		printf("(1)Random Aphorism (2)Show All (3)Add new (-1)Exit: ");
		if (!readString(menuInput, sizeof(menuInput), ""))continue;
		int menu = atoi(menuInput);
		if (menu == -1) {
			break;
		}
		else if (menu == 1) {
			displayRandom(apho, count);
		}
		else if (menu == 2) {
			displayAll(apho, count);
		}
		else if (menu == 3) {
			addAphorism(apho, &count);
		}
		else {
			printf("Invalid Choice!\n");
		}
	}
	return 0;
}