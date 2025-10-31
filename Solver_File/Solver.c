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
					printf("%s trouver : (%d;%d) (%d;%d)\n", Word, LD + 1, CD + 1, LF + 1, CF + 1);
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
					printf("%s trouver : (%d;%d) (%d;%d)\n", Word, LD + 1, CD + 1, LF + 1, CF + 1);
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
					printf("%s trouver : (%d;%d) (%d;%d)\n", Word, LD + 1, CD + 1, LF + 1, CF + 1);
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
					printf("%s trouver : (%d;%d) (%d;%d)\n", Word, LD + 1, CD + 1, LF + 1, CF + 1);
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

int Check_Diagonally(char* Word, char** Matrice) {
	int TailleWord = strlen(Word);
	int IntoWord = 0;

	for (int j = (TailleWord-1); j < colonnes; j++) {
		int i_tmp = 0, j_tmp = j;
		IntoWord = 0;
		while (j_tmp >=0 && i_tmp < lignes) {
			if (IntoWord == 0 && Word[IntoWord] == Matrice[i_tmp][j_tmp]) {
				LD = i_tmp;
				CD = j_tmp;
				IntoWord += 1;
			}
			else if (Word[IntoWord] == Matrice[i_tmp][j_tmp]) {

				IntoWord += 1;

				if (TailleWord == IntoWord) {
					CF = j_tmp;
					LF = i_tmp;
					printf("%s trouver : (%d;%d) (%d;%d)\n", Word, LD + 1, CD + 1, LF + 1, CF + 1);
					return 0;
				}

			}
			else if (IntoWord != 0) {
				i_tmp -= 1;
				j_tmp += 1;
				IntoWord = 0;
			}
			else {
				
				IntoWord = 0;
			}
			i_tmp+=1;
			j_tmp-=1;
		}
	}

	for (int i = 0; i < (lignes -TailleWord+1); i++) {
		int i_tmp = i, j_tmp = colonnes-1;
		IntoWord = 0;
		while (i_tmp < lignes && j_tmp >= 0) {
			if (IntoWord == 0 && Word[IntoWord] == Matrice[i_tmp][j_tmp]) {
				LD = i_tmp;
				CD = j_tmp;
				IntoWord += 1;
			}
			else if (Word[IntoWord] == Matrice[i_tmp][j_tmp]) {

				IntoWord += 1;

				if (TailleWord == IntoWord) {
					CF = j_tmp;
					LF = i_tmp;
					printf("%s trouver : (%d;%d) (%d;%d)\n", Word, LD + 1, CD + 1, LF + 1, CF + 1);
					return 0;
				}

			}
			else if (IntoWord != 0) {
				i_tmp -= 1;
				j_tmp += 1;
				IntoWord = 0;
			}
			else {
				
				IntoWord = 0;
			}
			i_tmp += 1;
			j_tmp -= 1;
		}
	}


	for (int j = (TailleWord - 1); j < colonnes; j++) {
		int i_tmp = lignes - 1;  
		int j_tmp = j;
		IntoWord = 0;

		while (i_tmp >= 0 && j_tmp < colonnes) {
			if (IntoWord == 0 && Word[IntoWord] == Matrice[i_tmp][j_tmp]) {
				LD = i_tmp;
				CD = j_tmp;
				IntoWord += 1;
			}
			else if (Word[IntoWord] == Matrice[i_tmp][j_tmp]) {
				IntoWord += 1;

				if (TailleWord == IntoWord) {
					LF = i_tmp;
					CF = j_tmp;
					printf("%s trouver : (%d;%d) (%d;%d)\n", Word, LD + 1, CD + 1, LF + 1, CF + 1);
					return 0;
				}
			}
			else if (IntoWord != 0) {
				i_tmp += 1;
				j_tmp -= 1;
				IntoWord = 0;
			}
			else {
				IntoWord = 0;
			}

			i_tmp -= 1;
			j_tmp += 1;
		}
	}
	for (int i = lignes - 1; i >= (TailleWord - 1); i--) {
		int i_tmp = i;
		int j_tmp = 0;  
		IntoWord = 0;

		while (i_tmp >= 0 && j_tmp < colonnes) {
			if (IntoWord == 0 && Word[IntoWord] == Matrice[i_tmp][j_tmp]) {
				LD = i_tmp;
				CD = j_tmp;
				IntoWord += 1;
			}
			else if (Word[IntoWord] == Matrice[i_tmp][j_tmp]) {
				IntoWord += 1;

				if (TailleWord == IntoWord) {
					LF = i_tmp;
					CF = j_tmp;
					printf("%s trouver : (%d;%d) (%d;%d)\n", Word, LD + 1, CD + 1, LF + 1, CF + 1);
					return 0;
				}
			}
			else if (IntoWord != 0) {
				i_tmp += 1;
				j_tmp -= 1;
				IntoWord = 0;
			}
			else {
				IntoWord = 0;
			}

			i_tmp -= 1;
			j_tmp += 1; 
		}
	}
	


	return 1;
}

int Check_Diagonnaly2(char* Word, char** Mat) {
	int TailleWord = strlen(Word);
	int IntoWord = 0;

	for (int j = (TailleWord - 1); j < colonnes; j++) {
		int i_tmp = lignes - 1, j_tmp = j;
		IntoWord = 0;
		while (j_tmp >= 0 && i_tmp  >= 0) {
			if (IntoWord == 0 && Word[IntoWord] == Mat[i_tmp][j_tmp]) {
				LD = i_tmp;
				CD = j_tmp;
				IntoWord += 1;
			}
			else if (Word[IntoWord] == Mat[i_tmp][j_tmp]) {

				IntoWord += 1;

				if (TailleWord == IntoWord) {
					CF = j_tmp;
					LF = i_tmp;
					printf("%s trouver : (%d;%d) (%d;%d)\n", Word, LD + 1, CD + 1, LF + 1, CF + 1);
					return 0;
				}

			}
			else if (IntoWord != 0) {
				i_tmp += 1;
				j_tmp += 1;
				IntoWord = 0;
			}
			else {

				IntoWord = 0;
			}
			i_tmp -= 1;
			j_tmp -= 1;
		}
	}

	for (int i = lignes-1; i >= (lignes - TailleWord + 1); i--) {
		int i_tmp = i, j_tmp = colonnes - 1;
		IntoWord = 0;
		while (i_tmp >= 0 && j_tmp >= 0) {
			if (IntoWord == 0 && Word[IntoWord] == Mat[i_tmp][j_tmp]) {
				LD = i_tmp;
				CD = j_tmp;
				IntoWord += 1;
			}
			else if (Word[IntoWord] == Mat[i_tmp][j_tmp]) {

				IntoWord += 1;

				if (TailleWord == IntoWord) {
					CF = j_tmp;
					LF = i_tmp;
					printf("%s trouver : (%d;%d) (%d;%d)\n", Word, LD + 1, CD + 1, LF + 1, CF + 1);
					return 0;
				}

			}
			else if (IntoWord != 0) {
				i_tmp += 1;
				j_tmp += 1;
				IntoWord = 0;
			}
			else {

				IntoWord = 0;
			}
			i_tmp -= 1;
			j_tmp -= 1;
		}
	}

	for (int j = 0; j <= colonnes - TailleWord; j++) {
		int i_tmp = 0, j_tmp = j;
		IntoWord = 0;
		while (i_tmp < lignes && j_tmp < colonnes) {
			if (IntoWord == 0 && Word[IntoWord] == Mat[i_tmp][j_tmp]) {
				LD = i_tmp;
				CD = j_tmp;
				IntoWord += 1;
			}
			else if (Word[IntoWord] == Mat[i_tmp][j_tmp]) {
				IntoWord += 1;
				if (TailleWord == IntoWord) {
					CF = j_tmp;
					LF = i_tmp;
					printf("%s trouver : (%d;%d) (%d;%d)\n", Word, LD + 1, CD + 1, LF + 1, CF + 1);
					return 0;
				}
			}
			else if (IntoWord != 0) {
				i_tmp -= 1;
				j_tmp -= 1;
				IntoWord = 0;
			}
			else {
				IntoWord = 0;
			}
			i_tmp += 1;
			j_tmp += 1;
		}
	}

	for (int i = 1; i <= lignes - TailleWord; i++) {
		int i_tmp = i, j_tmp = 0;
		IntoWord = 0;
		while (i_tmp < lignes && j_tmp < colonnes) {
			if (IntoWord == 0 && Word[IntoWord] == Mat[i_tmp][j_tmp]) {
				LD = i_tmp;
				CD = j_tmp;
				IntoWord += 1;
			}
			else if (Word[IntoWord] == Mat[i_tmp][j_tmp]) {
				IntoWord += 1;
				if (TailleWord == IntoWord) {
					CF = j_tmp;
					LF = i_tmp;
					printf("%s trouver : (%d;%d) (%d;%d)\n", Word, LD + 1, CD + 1, LF + 1, CF + 1);
					return 0;
				}
			}
			else if (IntoWord != 0) {
				i_tmp -= 1;
				j_tmp -= 1;
				IntoWord = 0;
			}
			else {
				IntoWord = 0;
			}
			i_tmp += 1;
			j_tmp += 1;
		}
	}
	
	return 1;

}


int main(int argc, char* argv[]) {

	if (argc <= 1) {

		errx(EXIT_FAILURE, "Pas bon nombre d'argument");

	}
	FILE* fichier = fopen("Solver_File/Grid.txt", "r");

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
				Mat[ipro][j] = toupper(buffer[j]);
			}
			else {
				Close_All(fichier, Mat);
				errx(EXIT_FAILURE, "Pas une lettre");
			}
			
		}
		
		ipro++;
	}

	for (int argument = 1; argument < argc; argument++) {

		for (int i = 0; i < strlen(argv[argument]); i++) {

			argv[argument][i] = toupper(argv[argument][i]);

		}

		if (Check_Vertically(argv[argument], Mat) == 0) {
			
		}
		else {
			if (Check_Horizontally(argv[argument], Mat) == 0) {

			}
			else {
				if (Check_Diagonally(argv[argument], Mat) == 0) {

				}
				else {
					if (Check_Diagonnaly2(argv[argument], Mat) == 0) {

					}
					else {
						printf("%s non trouver\n",argv[argument]);
					}
				}
			}
		}

	}
	Close_All(fichier, Mat);
}