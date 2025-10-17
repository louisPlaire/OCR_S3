#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <ctype.h>


int lignes = 0;
int colonnes = 0;

int LD = 0;
int CD = 0;
int LF = 0;
int CF = 0;

void Close_All(FILE* file, char** Matrice) {

	if (file != NULL) {

		fclose(file);
	}

	if (Matrice != NULL) {
		for (size_t i = 0; i < (size_t)lignes; i++) {

			free(Matrice[i]);


		}
		free(Matrice);

	}

}

int Check_Vertically(char* Word, char** Matrice) {

	LD = 0;
	CD = 0;
	int IntoWord = 0;
	int TailleWord = strlen(Word);

	int i = 0;
	
	for (int j = 0; j < colonnes; j++) {
		IntoWord = 0;
		i = 0;
		while (i < lignes && (lignes - i) >= (TailleWord - IntoWord)) {
			
			if (IntoWord == 0 && Word[IntoWord] == Matrice[i][j]) {
				LD = i;
				CD = j;
				IntoWord += 1;
				

			}
			else if (Word[IntoWord] == Matrice[i][j]) {

				IntoWord += 1;
				
				if (TailleWord == IntoWord) {
					CF = j;
					LF = i;
					printf("Mot trouver : (%d;%d) (%d;%d)\n", LD+1, CD+1, LF+1, CF+1);
					return 0;
				}

			}
			else if (IntoWord != 0) {
				i -= 1;
				IntoWord = 0;
			}
			else {

				IntoWord = 0;
			}

			i += 1;

		}

	}

	for (int j = 0; j < colonnes; j++) {
		IntoWord = 0;
		i = lignes -1;
		while (i >= 0 && (i+1) >= (TailleWord - IntoWord)) {

			if (IntoWord == 0 && Word[IntoWord] == Matrice[i][j]) {
				LD = i;
				CD = j;
				IntoWord += 1;


			}
			else if (Word[IntoWord] == Matrice[i][j]) {

				IntoWord += 1;

				if (TailleWord == IntoWord) {
					CF = j;
					LF = i;
					printf("Mot trouver : (%d;%d) (%d;%d)\n", LD + 1, CD + 1, LF + 1, CF + 1);
					return 0;
				}

			}
			else if (IntoWord != 0) {
				i+= 1;
				IntoWord = 0;
			}
			else {

				IntoWord = 0;
			}

			i -= 1;

		}

	}
	return 1;
}

int Check_Horizontally(char* Word, char** Matrice) {

	LD = 0;
	CD = 0;
	int IntoWord = 0;
	int TailleWord = strlen(Word);
	
	int j = 0;

	for (int i = 0; i < lignes; i++) {
		IntoWord = 0;
		j = 0;
		while (j < colonnes && (colonnes - j) >= (TailleWord - IntoWord)) {

			if (IntoWord == 0 && Word[IntoWord] == Matrice[i][j]) {
				LD = i;
				CD = j;
				IntoWord += 1;


			}
			else if (Word[IntoWord] == Matrice[i][j]) {

				IntoWord += 1;

				if (TailleWord == IntoWord) {
					CF = j;
					LF = i;
					printf("Mot trouver : (%d;%d) (%d;%d)\n", LD + 1, CD + 1, LF + 1, CF + 1);
					return 0;
				}

			}
			else if (IntoWord != 0) {
				j -= 1;
				IntoWord = 0;
			}
			else {

				IntoWord = 0;
			}

			j += 1;

		}

	}

	for (int i = 0; i < lignes; i++) {
		IntoWord = 0;
		j = colonnes-1;
		while (j >=  0 && (j + 1) >= (TailleWord - IntoWord)) {
			
			if (IntoWord == 0 && Word[IntoWord] == Matrice[i][j]) {
				LD = i;
				CD = j;
				IntoWord += 1;
			}
			else if (Word[IntoWord] == Matrice[i][j]) {
				
				IntoWord += 1;

				if (TailleWord == IntoWord) {
					CF = j;
					LF = i;
					printf("Mot trouver : (%d;%d) (%d;%d)\n", LD + 1, CD + 1, LF + 1, CF + 1);
					return 0;
				}

			}
			else if (IntoWord != 0){
				j += 1;
				IntoWord = 0;
			}
			else {
				IntoWord = 0;
			}

			j -= 1;

		}

	}
	return 1;
}

int main(int argc, char* argv[]) {

	if (argc != 2) {

		errx(EXIT_FAILURE, "Pas bon nombre d'argument");

	}
	FILE* fichier = fopen("Grid.txt", "r");

	if (fichier == NULL) {
		errx(EXIT_FAILURE, "Erreur lors de l'ouverture du fichier");
		
	}
	char maxParligne[256];

	while (fgets(maxParligne, sizeof(maxParligne), fichier) != NULL) {
		lignes += 1;

		int TailleLigne = strlen(maxParligne);

		if (maxParligne[TailleLigne - 1] == '\n') {

			maxParligne[TailleLigne - 1] = '\0';
			TailleLigne -= 1;
		}
		
		if (TailleLigne == 0) {
			Close_All(fichier, NULL);
			errx(EXIT_FAILURE, "Ya 0 char dans la ligne chef");
		}
		
		if (colonnes == 0 ) {
			colonnes = TailleLigne;
		}
		
		if (colonnes != TailleLigne) {
			Close_All(fichier, NULL);
			errx(EXIT_FAILURE, "Pas le même nombre de char dans chaque lignes");
		}

	}

	char** Mat = calloc(lignes, sizeof(char*));
	for (size_t in = 0; in < (size_t)lignes; in++) {

		Mat[in] = calloc(colonnes, sizeof(char));

	}

	rewind(fichier);

	int ipro = 0;
	char buffer[256];
	while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
		
		for (size_t j = 0; j < (size_t)colonnes; j++) {
			if (isalpha(buffer[j])) {
				Mat[ipro][j] = buffer[j];
			}
			else {
				Close_All(fichier, Mat);
				errx(EXIT_FAILURE, "Pas une lettre");
			}
			
		}
		
		ipro++;
	}
	for (size_t i = 0; i < (size_t)lignes; i++) {

		for (size_t j = 0; j < (size_t)colonnes; j++) {

			Mat[i][j] = toupper(Mat[i][j]);
		}
		
	}

	for (int i = 0; i < strlen(argv[1]); i++) {

		argv[1][i] = toupper(argv[1][i]);

	}

	if (Check_Vertically(argv[1], Mat) == 0) {
		Close_All(fichier, Mat);
		return 0;
	}
	if (Check_Horizontally(argv[1], Mat) == 0) {
		Close_All(fichier, Mat);
		return 0;
	}

	Close_All(fichier, Mat);
	printf("Mot non présent dans la grille\n");


	for (size_t i = 0; i < (size_t)lignes; i++) {

		for (size_t j = 0; j < (size_t)colonnes; j++) {

			//printf("%c", toupper(Mat[i][j]));
		}
		//printf("\n");
	}

	for (int i = 0; i < strlen(argv[1]); i++) {

		//printf("%c", toupper(argv[1][i]));

	}
}