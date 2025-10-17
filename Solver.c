#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <ctype.h>


int lignes = 0;
int colonnes = 0;

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

			printf("%c", toupper(Mat[i][j]));
		}
		printf("\n");
	}


	Close_All(fichier, Mat);
	printf("Mot non présent dans la grille");
}