#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

void gotoXY(int x, int y) {
	HANDLE hConsoleOutput;
	COORD koords;
	koords.X = x;
	koords.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, koords);
}

int verzeichnis_check_add(char* name) {
	FILE *ptr;
	char txt[25];
	if (ptr = fopen("eintraege.var", "r+t")){ /*Protokolldatei öffnen*/
		fseek(ptr, 0L, 0); /*an Dateianfang gehen*/
		while (fgets(txt, 25, ptr)) { /*Dateiinhalt lesen*/
			// strcat(name, "\n");
			if (strcmp(name, txt) == 0) {
				return 0;
			}
		}
		fseek(ptr, 0L, SEEK_END); /*an Dateiende gehen*/
		fprintf(ptr, "\n%s", name); /*und in Datei schreiben*/
		fclose(ptr); /*Datei schließen*/
		return 1;
	}
	else {
		printf("Die Datei eintraege.var konnte nicht ge\231ffnet werden\n\n");
		return 0;
	}
	return 0;
}

int verzeichnis_ueberpruefen(char* name) {
	FILE *ptr;
	char txt[25];
	if (ptr = fopen("eintraege.var", "r+t")){ /*Protokolldatei öffnen*/
		fseek(ptr, 0L, 0); /*an Dateianfang gehen*/
		while (fgets(txt, 25, ptr)) { /*Dateiinhalt lesen*/
			if (strcmp(name, txt) == 0) {
				return 1;
			}
		}
		fclose(ptr); /*Datei schließen*/
		return 0;
	}
	else
		printf("Die Datei eintraege.var konnte nicht ge\231ffnet werden\n\n");
	return 1;
}

void verzeichnis_hinzufuegen(char* eintrag) {
	FILE *ptr;
	// char txt[1024];
	if (ptr = fopen("eintraege.var", "r+t")){ /*Protokolldatei öffnen*/
		fseek(ptr, 0L, SEEK_END); /*an Dateiende gehen*/
		fprintf(ptr, "%s\n", eintrag); /*und in Datei schreiben*/
		fclose(ptr); /*Datei schließen*/
	}
	else
		printf("\n Die Datei eintraege.var konnte nicht ge\231ffnet werden");
}

void verzeichnis_anzeigen(void) {
	FILE *ptr;
	char txt[1024];
	if (ptr = fopen("eintraege.var", "r+t")){ /*Protokolldatei öffnen*/
		printf("Alle Dateieintr\204ge:\n");
		fseek(ptr, 0L, 0); /*an Dateianfang gehen*/
		while (fgets(txt, 1024, ptr)) /*Dateiinhalt lesen*/
			printf("%s", txt); /*und ausgeben*/
		fclose(ptr); /*Datei schließen*/
		printf("\n\n");
	}
	else
		printf("Die Datei eintraege.var konnte nicht ge\231ffnet werden\n\n");
}

int eingabe_num(char* text, int ug, int og) {
	int erfolg, eing;
	do {
		printf(text);
		fflush(stdin);
		erfolg = scanf_s("%d", &eing, 5);
	} while ((erfolg != 1) || (eing < ug) || (eing > og));
	printf("\n");
	return eing;

}

int eingabe_string(char* text, char* string) {
	printf(text);
	if (scanf_s("%19s", string, 20) == 1) return 1;
	else return 0;
}

void feld_leeren(char feld[50][50], int *hoehe, int *breite) {
	for (int i = 0; i < *hoehe; i++) {
		for (int j = 0; j < *hoehe; j++) {
			feld[i][j] = ' ';
		}
	}
}

void feld_fuellen(char feld[50][50], int *hoehe, int *breite) {
	for (int i = 0; i < *hoehe; i++) {
		for (int j = 0; j < *hoehe; j++) {
			feld[i][j] = '*';
		}
	}
}

int umliegende_zellen(char feld[20][20], int *hoehe, int *breite, int hpos, int bpos)
{
	int count = 0;

	if ((hpos == 0) && (bpos == 0)) {
		if (feld[hpos + 1][bpos]) count++;
		if (feld[hpos][bpos + 1]) count++;
		if (feld[hpos + 1][bpos + 1]) count++;
	}

	else if ((hpos == 0) && (bpos == (*breite) - 1)) {
		if (feld[hpos + 1][bpos]) count++;
		if (feld[hpos][bpos - 1]) count++;
		if (feld[hpos + 1][bpos - 1]) count++;
	}

	else if ((hpos == (*hoehe) - 1) && (bpos == 0)) {
		if (feld[hpos - 1][bpos]) count++;
		if (feld[hpos][bpos + 1]) count++;
		if (feld[hpos - 1][bpos + 1]) count++;
	}

	else if ((hpos == (*hoehe) - 1) && (bpos == (*breite) - 1)) {
		if (feld[hpos - 1][bpos]) count++;
		if (feld[hpos][bpos - 1]) count++;
		if (feld[hpos - 1][bpos - 1]) count++;
	}

	else {
		if (hpos == 0) {
			if (feld[hpos][bpos - 1]) count++;
			if (feld[hpos][bpos + 1]) count++;
			if (feld[hpos + 1][bpos - 1]) count++;
			if (feld[hpos + 1][bpos]) count++;
			if (feld[hpos + 1][bpos + 1]) count++;
		}

		else if (hpos == (*hoehe) - 1) {
			if (feld[hpos][bpos - 1]) count++;
			if (feld[hpos][bpos + 1]) count++;
			if (feld[hpos - 1][bpos - 1]) count++;
			if (feld[hpos - 1][bpos]) count++;
			if (feld[hpos - 1][bpos + 1]) count++;
		}

		else if (bpos == 0) {
			if (feld[hpos - 1][bpos]) count++;
			if (feld[hpos + 1][bpos]) count++;
			if (feld[hpos - 1][bpos + 1]) count++;
			if (feld[hpos][bpos + 1]) count++;
			if (feld[hpos + 1][bpos + 1]) count++;
		}

		else if (bpos == (*breite) - 1) {
			if (feld[hpos - 1][bpos]) count++;
			if (feld[hpos + 1][bpos]) count++;
			if (feld[hpos - 1][bpos - 1]) count++;
			if (feld[hpos][bpos - 1]) count++;
			if (feld[hpos + 1][bpos - 1]) count++;
		}

		else {
			if (feld[hpos - 1][bpos - 1]) count++;
			if (feld[hpos - 1][bpos]) count++;
			if (feld[hpos - 1][bpos + 1]) count++;
			if (feld[hpos][bpos - 1]) count++;
			if (feld[hpos][bpos + 1]) count++;
			if (feld[hpos + 1][bpos - 1]) count++;
			if (feld[hpos + 1][bpos]) count++;
			if (feld[hpos + 1][bpos + 1]) count++;
		}
	}
	return count;

}

int naechster_schritt_fliessend(char feld[50][50], int *hoehe, int *breite) {
	// nächster Schritt Funktion kopieren
	int hpos, bpos;
	char hilfsfeld[50][50];
	int count;
	int change = 0;

	//Mitte-Mitte
	for (hpos = 1; hpos < (*hoehe) - 1; hpos++) {
		for (bpos = 1; bpos < (*breite) - 1; bpos++) {
			count = (feld[hpos - 1][bpos - 1]) + (feld[hpos - 1][bpos]) + (feld[hpos - 1][bpos + 1]) + (feld[hpos][bpos - 1]) + (feld[hpos][bpos + 1]) + (feld[hpos + 1][bpos - 1]) + (feld[hpos + 1][bpos]) + (feld[hpos + 1][bpos + 1]);
			switch (count) {
			case 276: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
			case 286: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) {
				change++;
				gotoXY(2 * bpos, hpos);
				printf("%c", hilfsfeld[hpos][bpos]);
			} break;
			default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) {
				change++;
				gotoXY(2 * bpos, hpos);
				printf("%c", hilfsfeld[hpos][bpos]);
			} break;
			}
		}
	}

	//Oben-Mitte
	hpos = 0;
	for (bpos = 1; bpos < (*breite) - 1; bpos++) {
		count = (feld[hpos][bpos - 1]) + (feld[hpos][bpos + 1]) + (feld[hpos + 1][bpos - 1]) + (feld[hpos + 1][bpos]) + (feld[hpos + 1][bpos + 1]);
		switch (count) {
		case 180: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
		case 190: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) {
			change++;
			gotoXY(2 * bpos, hpos);
			printf("%c", hilfsfeld[hpos][bpos]);
		} break;
		default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) {
			change++;
			gotoXY(2 * bpos, hpos);
			printf("%c", hilfsfeld[hpos][bpos]);
		} break;
		}
	}

	//Unten-Mitte
	hpos = (*hoehe) - 1;
	for (bpos = 1; bpos < (*breite) - 1; bpos++) {
		count = (feld[hpos][bpos - 1]) + (feld[hpos][bpos + 1]) + (feld[hpos - 1][bpos - 1]) + (feld[hpos - 1][bpos]) + (feld[hpos - 1][bpos + 1]);
		switch (count) {
		case 180: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
		case 190: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) {
			change++;
			gotoXY(2 * bpos, hpos);
			printf("%c", hilfsfeld[hpos][bpos]);
		} break;
		default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) {
			change++;
			gotoXY(2 * bpos, hpos);
			printf("%c", hilfsfeld[hpos][bpos]);
		} break;
		}
	}

	//Mitte-Links
	bpos = 0;
	for (hpos = 1; hpos < (*hoehe) - 1; hpos++) {
		count = (feld[hpos - 1][bpos]) + (feld[hpos - 1][bpos + 1]) + (feld[hpos][bpos + 1]) + (feld[hpos + 1][bpos]) + (feld[hpos + 1][bpos + 1]);
		switch (count) {
		case 180: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
		case 190: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) {
			change++;
			gotoXY(2 * bpos, hpos);
			printf("%c", hilfsfeld[hpos][bpos]);
		} break;
		default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) {
			change++;
			gotoXY(2 * bpos, hpos);
			printf("%c", hilfsfeld[hpos][bpos]);
		} break;
		}
	}

	//Mitte-Rechts
	bpos = (*breite) - 1;
	for (hpos = 1; hpos < (*hoehe) - 1; hpos++) {
		count = (feld[hpos - 1][bpos]) + (feld[hpos - 1][bpos - 1]) + (feld[hpos][bpos - 1]) + (feld[hpos + 1][bpos]) + (feld[hpos + 1][bpos - 1]);
		switch (count) {
		case 180: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
		case 190: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) {
			change++;
			gotoXY(2 * bpos, hpos);
			printf("%c", hilfsfeld[hpos][bpos]);
		} break;
		default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) {
			change++;
			gotoXY(2 * bpos, hpos);
			printf("%c", hilfsfeld[hpos][bpos]);
		} break;
		}
	}

	//Ecken
	hpos = 0; bpos = 0;
	count = (feld[hpos][bpos + 1]) + (feld[hpos + 1][bpos]) + (feld[hpos + 1][bpos + 1]);
	switch (count) {
	case 116: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
	case 126: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) {
		change++;
		gotoXY(2 * bpos, hpos);
		printf("%c", hilfsfeld[hpos][bpos]);
	} break;
	default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) {
		change++;
		gotoXY(2 * bpos, hpos);
		printf("%c", hilfsfeld[hpos][bpos]);
	} break;
	}

	hpos = 0; bpos = (*breite) - 1;
	count = (feld[hpos][bpos - 1]) + (feld[hpos + 1][bpos]) + (feld[hpos + 1][bpos - 1]);
	switch (count) {
	case 116: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
	case 126: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) {
		change++;
		gotoXY(2 * bpos, hpos);
		printf("%c", hilfsfeld[hpos][bpos]);
	} break;
	default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) {
		change++;
		gotoXY(2 * bpos, hpos);
		printf("%c", hilfsfeld[hpos][bpos]);
	} break;
	}

	hpos = (*hoehe) - 1; bpos = 0;
	count = (feld[hpos][bpos + 1]) + (feld[hpos - 1][bpos]) + (feld[hpos - 1][bpos + 1]);
	switch (count) {
	case 116: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
	case 126: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) {
		change++;
		gotoXY(2 * bpos, hpos);
		printf("%c", hilfsfeld[hpos][bpos]);
	} break;
	default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) {
		change++;
		gotoXY(2 * bpos, hpos);
		printf("%c", hilfsfeld[hpos][bpos]);
	} break;
	}

	hpos = (*hoehe) - 1; bpos = (*breite) - 1;
	count = (feld[hpos][bpos - 1]) + (feld[hpos - 1][bpos]) + (feld[hpos - 1][bpos - 1]);
	switch (count) {
	case 116: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
	case 126: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) {
		change++;
		gotoXY(2 * bpos, hpos);
		printf("%c", hilfsfeld[hpos][bpos]);
	} break;
	default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) {
		change++;
		gotoXY(2 * bpos, hpos);
		printf("%c", hilfsfeld[hpos][bpos]);
	} break;
	}

	for (hpos = 0; hpos < *hoehe; hpos++) {
		for (bpos = 0; bpos < *breite; bpos++) {
			feld[hpos][bpos] = hilfsfeld[hpos][bpos];
		}
	}
	return change;
}

void feld_aktualisieren(char feld[50][50], int* hoehe, int* breite) {
	for (int i = 0; i<*hoehe; i++) {
		for (int j = 0; j<*breite; j++) {
			gotoXY(i, j);
			printf("%c", feld[i][j]);
		}
	}
}

int naechster_schritt(char feld[50][50], int *hoehe, int *breite) {
	int hpos, bpos;
	char hilfsfeld[50][50];
	int count;
	int change = 0;

	//Mitte-Mitte
	for (hpos = 1; hpos < (*hoehe) - 1; hpos++) {
		for (bpos = 1; bpos < (*breite) - 1; bpos++) {
			count = (feld[hpos - 1][bpos - 1]) + (feld[hpos - 1][bpos]) + (feld[hpos - 1][bpos + 1]) + (feld[hpos][bpos - 1]) + (feld[hpos][bpos + 1]) + (feld[hpos + 1][bpos - 1]) + (feld[hpos + 1][bpos]) + (feld[hpos + 1][bpos + 1]);
			switch (count) {
			case 276: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
			case 286: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) change++; break;
			default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) change++; break;
			}
		}
	}

	//Oben-Mitte
	hpos = 0;
	for (bpos = 1; bpos < (*breite) - 1; bpos++) {
		count = (feld[hpos][bpos - 1]) + (feld[hpos][bpos + 1]) + (feld[hpos + 1][bpos - 1]) + (feld[hpos + 1][bpos]) + (feld[hpos + 1][bpos + 1]);
		switch (count) {
		case 180: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
		case 190: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) change++; break;
		default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) change++; break;
		}
	}

	//Unten-Mitte
	hpos = (*hoehe) - 1;
	for (bpos = 1; bpos < (*breite) - 1; bpos++) {
		count = (feld[hpos][bpos - 1]) + (feld[hpos][bpos + 1]) + (feld[hpos - 1][bpos - 1]) + (feld[hpos - 1][bpos]) + (feld[hpos - 1][bpos + 1]);
		switch (count) {
		case 180: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
		case 190: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) change++; break;
		default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) change++; break;
		}
	}

	//Mitte-Links
	bpos = 0;
	for (hpos = 1; hpos < (*hoehe) - 1; hpos++) {
		count = (feld[hpos - 1][bpos]) + (feld[hpos - 1][bpos + 1]) + (feld[hpos][bpos + 1]) + (feld[hpos + 1][bpos]) + (feld[hpos + 1][bpos + 1]);
		switch (count) {
		case 180: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
		case 190: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) change++; break;
		default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) change++; break;
		}
	}

	//Mitte-Rechts
	bpos = (*breite) - 1;
	for (hpos = 1; hpos < (*hoehe) - 1; hpos++) {
		count = (feld[hpos - 1][bpos]) + (feld[hpos - 1][bpos - 1]) + (feld[hpos][bpos - 1]) + (feld[hpos + 1][bpos]) + (feld[hpos + 1][bpos - 1]);
		switch (count) {
		case 180: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
		case 190: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) change++; break;
		default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) change++; break;
		}
	}

	//Ecken
	hpos = 0; bpos = 0;
	count = (feld[hpos][bpos + 1]) + (feld[hpos + 1][bpos]) + (feld[hpos + 1][bpos + 1]);
	switch (count) {
	case 116: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
	case 126: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) change++; break;
	default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) change++; break;
	}

	hpos = 0; bpos = (*breite) - 1;
	count = (feld[hpos][bpos - 1]) + (feld[hpos + 1][bpos]) + (feld[hpos + 1][bpos - 1]);
	switch (count) {
	case 116: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
	case 126: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) change++; break;
	default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) change++; break;
	}

	hpos = (*hoehe) - 1; bpos = 0;
	count = (feld[hpos][bpos + 1]) + (feld[hpos - 1][bpos]) + (feld[hpos - 1][bpos + 1]);
	switch (count) {
	case 116: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
	case 126: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) change++; break;
	default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) change++; break;
	}

	hpos = (*hoehe) - 1; bpos = (*breite) - 1;
	count = (feld[hpos][bpos - 1]) + (feld[hpos - 1][bpos]) + (feld[hpos - 1][bpos - 1]);
	switch (count) {
	case 116: hilfsfeld[hpos][bpos] = feld[hpos][bpos]; break;
	case 126: hilfsfeld[hpos][bpos] = 42; if (feld[hpos][bpos] != 42) change++; break;
	default: hilfsfeld[hpos][bpos] = ' '; if (feld[hpos][bpos] != 32) change++; break;
	}

	for (hpos = 0; hpos < *hoehe; hpos++) {
		for (bpos = 0; bpos < *breite; bpos++) {
			feld[hpos][bpos] = hilfsfeld[hpos][bpos];
		}
	}
	return change;
}

void feld_anzeigen(char feld[50][50], int *hoehe, int *breite) {
	for (int hpos = 0; hpos<*hoehe; hpos++) {
		for (int bpos = 0; bpos<*breite; bpos++) {
			switch (feld[hpos][bpos]) {
			case 42: printf("* "); break;
			case 32: printf("  "); break;
			case 0: printf("0 "); break;
			default: printf("? "); break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void feld_fuellen_random(char feld[50][50], int *hoehe, int *breite) {
	if ((eingabe_num("Gr\231\341e des Feldes \204ndern\n1 - Nein\t2 - Ja\t", 1, 2)) == 2) {
		(*hoehe) = eingabe_num("H\231he angeben: ", 1, 39);
		(*breite) = eingabe_num("Breite angeben: ", 1, 39);
	}
	int prozent = eingabe_num("F\201llwert in Prozent angeben: ", 0, 100);
	srand(time(NULL));
	for (int hpos = 0; hpos < *hoehe; hpos++) {
		for (int bpos = 0; bpos < *breite; bpos++) {
			if ((rand() % 100) < prozent) feld[hpos][bpos] = 42;
			else feld[hpos][bpos] = 32;
		}

	}
}

void zustand_einlesen(char feld[50][50], int *hoehe, int *breite, char* datei) {
	FILE *stream;
	char trash;
	int i, j;
	if ((stream = fopen(datei, "r+t")) != 0) {
		fscanf(stream, "%d %d", hoehe, breite);
		trash = fgetc(stream);
		for (i = 0; i < *hoehe; i++) {
			for (j = 0; j < *breite; j++) {
				// feld[i][j] = fgetc(stream);
				fscanf(stream, "%c", &(feld[i][j]));
			}
			// trash = fgetc(stream);
			fscanf(stream, "%c", &trash);
		}
		fclose(stream);
	}
	else printf("\326ffnen nicht m\231glich\n");
}

void zustand_speichern(char feld[50][50], int *hoehe, int *breite, char* datei) {
	FILE *stream;
	int i, j;

	if ((stream = fopen(datei, "w+t")) != 0) {
		fprintf(stream, "%d %d", *hoehe, *breite);
		fprintf(stream, "\n");
		for (i = 0; i < *hoehe; i++) {
			for (j = 0; j < *breite; j++) {
				fprintf(stream, "%c", feld[i][j]);
			}
			fprintf(stream, "\n");
		}
		fclose(stream);
	}
	else printf("Speichern nicht m\231glich\n");
}

void feld_abarbeiten(char feld[50][50], int *hoehe, int *breite)  {
	int tempo;
	tempo = eingabe_num("Animationsgeschwindigkeit\nLangsam 1 - 10 Schnell ", 1, 10);
	
	int change[5] = { 1, 2, 3, 4, 5 };

	do {
		change[4] = change[3]; change[3] = change[2]; change[2] = change[1]; change[1] = change[0];
		change[0] = naechster_schritt_fliessend(feld, hoehe, breite);
		Sleep(1000/tempo);
		// change01 = naechster_schritt(feld, hoehe, breite);
		// system("cls");
		// feld_anzeigen(feld, hoehe, breite);
	} while ((change[0] != 0) && ((change[0] != change[1]) || (change[1] != change[2]) || (change[2] != change[3]) || (change[3] != change[4])));
}

void feld_bearbeiten(char feld[50][50], int *hoehe, int *breite) {
	gotoXY(0, (*hoehe) + 2);
	printf("SPACE zum Umschalten der Zelle");
	gotoXY(0, (*hoehe) + 3);
	printf("ENTER zum Beenden der Bearbeitung");
	gotoXY(0, 0);
	feld_anzeigen(feld, hoehe, breite);
	gotoXY(0, 0);
	int x = 0, y = 0, c;
	while (1) {
		// fflush(stdin);
		while (!kbhit()) {
			c = getch();
			if (c == 224) {
				switch (getch()) {
				case 75:
					x = (x - 2 + (2 * (*breite))) % (2 * (*breite));
					break;
				case 72:
					y = (--y + (*hoehe)) % (*hoehe);
					break;
				case 77:
					x = (x + 2 + (2 * (*breite))) % (2 * (*breite));
					break;
				case 80:
					y = (++y + (*hoehe)) % (*hoehe);
					break;
					// Konstante Werte durch Höhe und Breite ersetzen
				}
				gotoXY(x, y);
				fflush(stdin);
			}

			if (c == ' ') {
				if (feld[y][x / 2] == '*') feld[y][x / 2] = ' ';
				else if (feld[y][x / 2] == ' ') feld[y][x / 2] = '*';
				// system("cls");
				printf("%c", feld[y][x / 2]);
				gotoXY(x, y);
				fflush(stdin);
			}

			if (c == 13)
			{
				fflush(stdin);
				return;
			}
			fflush(stdin);
			// c = 0;
			break;
		}
	}
}

int menue(char feld[50][50], int *hoehe, int *breite) {
	char name[25];
	int namestate;
	int auswahl;
	int hoehe_old = *hoehe;
	int breite_old = *hoehe;
	int i, j;
		printf("1 - Zuf\204lliges Feld erzeugen\n2 - Feld bearbeiten\n3 - Datei einlesen\n4 - Datei abspeichern\n5 - N\204chster Simulationsschritt\n6 - Simulation automatisiert fortsetzen\n7 - Programm beenden\n\n");
	switch (auswahl = (eingabe_num("Bitte Men\201punkt w\204hlen: ", 1, 7))) {
	case 1:
		feld_fuellen_random(feld, hoehe, breite);
		system("cls");
		feld_anzeigen(feld, hoehe, breite);
		break;
	case 2:
		// system("cls");
		// feld_anzeigen(feld, hoehe, breite);
		if ((eingabe_num("Gr\231\341e des Feldes \204ndern\n1 - Nein\t2 - Ja\t", 1, 2)) == 2) {
			(*hoehe) = eingabe_num("H\231he angeben: ", 1, 39);
			(*breite) = eingabe_num("Breite angeben: ", 1, 39);
			if (hoehe_old < *hoehe) {
				for (i = hoehe_old; i < *hoehe; i++) {
					for (j = 0; j < *breite; j++) {
						feld[i][j] = ' ';
					}
				}
			}
			if (breite_old < *breite) {
				for (i = breite_old; i < *breite; i++) {
					for (j = 0; j < *hoehe; j++) {
						feld[j][i] = ' ';
					}
				}
			}
			if ((hoehe_old < *hoehe) && (breite_old < *breite)) {
				for (i = hoehe_old; i < *hoehe; i++) {
					for (j = breite_old; j < *breite; j++) {
						feld[i][j] = ' ';
					}
				}
			}
		}
		// system("cls");
		printf("1 - Feld leeren\n2 - Feld f\201llen\n3 - Feld manuell bearbeiten\n\n");
		switch (auswahl = (eingabe_num("Bitte Men\201punkt w\204hlen: ", 1, 3))) {
		case 1:
			feld_leeren(feld, hoehe, breite);
			break;
		case 2:
			feld_fuellen(feld, hoehe, breite);
			break;
		case 3:
			system("cls");
			feld_bearbeiten(feld, hoehe, breite);
			break;
		}
		system("cls");
		feld_anzeigen(feld, hoehe, breite);
		break;
	case 3:
		// verzeichnis_anzeigen("Z:\hello\prog1\Belegaufgabe\Belegaufgabe");
		// system("cls"); // Optional
		printf("1 - T\201mmler einlesen\n2 - Oktagon einlesen\n3 - Pulsator einlesen\n4 - Eigenen Dateinamen eingeben\n\n");
		switch (namestate = eingabe_num("Bitte Men\201punkt w\204hlen: ", 1, 4)) {
		case 1:
			strcpy_s(name, 20, "tuemmler.var");
			break;
		case 2:
			strcpy_s(name, 20, "oktagon.var");
			break;
		case 3:
			strcpy_s(name, 20, "pulsator.var");
			break;
		case 4:
			// verzeichnis_anzeigen();
			eingabe_string("Bitte Dateinamen angeben: ", name);
			strcat_s(name, 15, ".save");
			break;
		}
		zustand_einlesen(feld, hoehe, breite, name);
		system("cls");
		feld_anzeigen(feld, hoehe, breite);
		break;
	case 4:
		fflush(stdin);
		eingabe_string("Bitte Dateinamen angeben: ", name);
		// Überprüfen-Funktion funktioniert nicht
		// verzeichnis_check_add(name);
		strcat_s(name, 15, ".save");
		zustand_speichern(feld, hoehe, breite, name);
		system("cls");
		feld_anzeigen(feld, hoehe, breite);
		break;
	case 5:
		system("cls");
		naechster_schritt(feld, hoehe, breite);
		feld_anzeigen(feld, hoehe, breite);
		break;
	case 6:
		feld_abarbeiten(feld, hoehe, breite);
		system("cls");
		gotoXY(0, 0);
		feld_anzeigen(feld, hoehe, breite);
		break;
	case 7:
		system("cls");
		printf("by Sebastian Mischke");
		break;
	}
	return auswahl;
}

int main() {
	char feld[50][50];
	int hoehe = 30;
	int breite = 30;
	feld_leeren(feld, &hoehe, &breite);
	int exit;
	do {
		exit = menue(feld, &hoehe, &breite);
	} while (exit != 7);
	// getch();
	return 0;
}