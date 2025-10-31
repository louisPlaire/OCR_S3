#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <ctype.h>
#include <math.h>



double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double dsigmoid(double x) {
    return x * (1.0 - x);
}

double rand_weight() {
    return ((double)rand() / RAND_MAX) * 1.0 - 0.5;
}

typedef struct {
    int nb_entrees;
    int nb_cacher;
    int nb_sorties;

//These valued tell how many entries, how many hidden and how many outputs (i.e We have value for A and B (so 2 entries) and exit with 0 or 1 (so 1 outputs)

    double* entree;
    double* cacher;
    double* sortie;

//Arrays with the values of the neurones (i.e We can say that A will be the value in input[0] and B will be the value in input[1], 0 will be the value in output[0] 1 will be the value in output[0])

    double** w_input_hidden; // Weight between each input and hidden layers (arrays of array)
    double** w_hidden_output; // hidden layers between each input and outputs (arrays of array)


    double* b_hidden; // Bias for input to hidden
    double* b_output; // Bias for hidden to output

    double learning_rate;
} NeuralNetwork;

NeuralNetwork* NN;

NeuralNetwork* create_network(int n_input, int n_hidden, int n_output, double lr) {
    NN = malloc(sizeof(NeuralNetwork));
    NN->nb_entrees = n_input;
    NN->nb_cacher = n_hidden;
    NN->nb_sorties = n_output;
    NN->learning_rate = lr;

    NN->entree = calloc(n_input, sizeof(double));
    NN->cacher = calloc(n_hidden, sizeof(double));
    NN->sortie = calloc(n_output, sizeof(double));

    NN->b_hidden = calloc(n_hidden, sizeof(double));
    NN->b_output = calloc(n_output, sizeof(double));


    NN->w_input_hidden = malloc(n_input * sizeof(double*));
    for (int i = 0; i < n_input; i++) {
        NN->w_input_hidden[i] = malloc(n_hidden * sizeof(double));
        for (int j = 0; j < n_hidden; j++) {
            NN->w_input_hidden[i][j] = rand_weight();
        }
            
    }

    NN->w_hidden_output = malloc(n_hidden * sizeof(double*));
    for (int i = 0; i < n_hidden; i++) {
        NN->w_hidden_output[i] = malloc(n_output * sizeof(double));
        for (int j = 0; j < n_output; j++) {
            NN->w_hidden_output[i][j] = rand_weight();
        }
            
    }
    return NN;
}

void Free_All(NeuralNetwork* nn) {

    free(nn->entree);
    free(nn->cacher);
    free(nn->sortie);
    free(nn->b_hidden);
    free(nn->b_output);
 
    free(nn->w_input_hidden);
    
    free(nn->w_hidden_output);

    free(nn);

}

void Execute_Forward_Total(NeuralNetwork* nn, double* entree_data) {
    if (NN == NULL) {
        errx(EXIT_FAILURE,"Exec: NN n'est pas créé.\n");
   
    }
    for (int j = 0; j < nn->nb_cacher; j++) {
        double sum = nn->b_hidden[j];
        for (int i = 0; i < nn->nb_entrees; i++)
            sum += entree_data[i] * nn->w_input_hidden[i][j];
        nn->cacher[j] = sigmoid(sum);
    }


    for (int j= 0; j < nn->nb_sorties; j++) {
        double sum = nn->b_output[j];
        for (int i = 0; i < nn->nb_cacher; i++)
            sum += nn->cacher[i] * nn->w_hidden_output[i][j];
        nn->sortie[j] = sigmoid(sum);

    }
}

void Retropropagation(double* entree_data, double* sorties_attendues) {
    Execute_Forward_Total(NN, entree_data);
    double* Outputs = calloc(NN->nb_sorties, sizeof(double));
    double* Hiddens = calloc(NN->nb_cacher, sizeof(double));

    for (int k = 0; k < NN->nb_sorties; k++) {
        Outputs[k] = (sorties_attendues[k] - NN->sortie[k]) * dsigmoid(NN->sortie[k]);
    }

    for (int j = 0; j < NN->nb_cacher; j++) {
        double sum = 0.0;
        for (int k = 0; k < NN->nb_sorties; k++)
            sum += Outputs[k] * NN->w_hidden_output[j][k];
        Hiddens[j] = sum * dsigmoid(NN->cacher[j]);
    }

    for (int j = 0; j < NN->nb_cacher; j++) {
        for (int k = 0; k < NN->nb_sorties; k++) {
            NN->w_hidden_output[j][k] += (NN->learning_rate * Outputs[k] * NN->cacher[j]);
        }
    }

    for (int i = 0; i < NN->nb_entrees; i++) {
        for (int j = 0; j < NN->nb_cacher; j++) {
            NN->w_input_hidden[i][j] += NN->learning_rate * Hiddens[j] * entree_data[i];
        }
    }

    for (int j = 0; j < NN->nb_cacher; j++) {
        NN->b_hidden[j] += NN->learning_rate * Hiddens[j];
    }
    for (int k = 0; k < NN->nb_sorties; k++) {
        NN->b_output[k] += NN->learning_rate * Outputs[k];
    }

    free(Outputs);
    free(Hiddens);
}


int Trainer() {
    if (NN == NULL) {
        errx(EXIT_FAILURE, "NN n'est pas créé.\n");
        
    }
    double data_entree[4][2] = { {0,0}, { 1,0 }, { 0,1 }, { 1,1 } };
    double data_sortie[4][1] = { {1}, {0}, {0}, {1} };

    for (int i = 0; i < 100000; i++) {

        for (int j = 0; j < 4; j++) {
            Retropropagation(data_entree[j], data_sortie[j]);
        }
        if (i % 1000 == 0) {
            for (int j = 0; j < 4; j++) {
                Execute_Forward_Total(NN, data_entree[j]);
                printf("Input: %d %d -> Output: %f\n", (int)data_entree[j][0], (int)data_entree[j][1], NN->sortie[0]);
            }
        }
    }
    return 0;
}

void Saver() {

    FILE * save_file = fopen("SaverReseau.bin", "wb");
    if (save_file == NULL) {
        errx(EXIT_FAILURE, "Erreur lors de l'ouverture du fichier");

    }

    fwrite(&NN->nb_entrees, sizeof(int), 1, save_file);
    fwrite(&NN->nb_cacher, sizeof(int), 1, save_file);
    fwrite(&NN->nb_sorties, sizeof(int), 1, save_file);
    fwrite(&NN->learning_rate, sizeof(double), 1, save_file);

    fwrite(NN->b_hidden, sizeof(double), NN->nb_cacher, save_file);
    fwrite(NN->b_output, sizeof(double), NN->nb_sorties, save_file);


    for (int i = 0; i < NN->nb_entrees; i++) {
        fwrite(NN->w_input_hidden[i], sizeof(double), NN->nb_cacher, save_file);
    }

    for (int i = 0; i < NN->nb_cacher; i++) {
        fwrite(NN->w_hidden_output[i], sizeof(double), NN->nb_sorties, save_file);
    }

    fclose(save_file);
}

void Opener() {

    FILE* save_file = fopen("SaverReseau.bin", "rb");
    if (save_file == NULL) {
        errx(EXIT_FAILURE, "Erreur lors de l'ouverture du fichier");

    }

    NN = malloc(sizeof(NeuralNetwork));
    if (!NN) {
        errx(EXIT_FAILURE, "Malloc pas mis, pb");
    }
    fread(&NN->nb_entrees, sizeof(int), 1, save_file);
    fread(&NN->nb_cacher, sizeof(int), 1, save_file);
    fread(&NN->nb_sorties, sizeof(int), 1, save_file);
    fread(&NN->learning_rate, sizeof(double), 1, save_file);

    NN->b_hidden = malloc(NN->nb_cacher * sizeof(double));
    NN->b_output = malloc(NN->nb_sorties * sizeof(double));
    fread(NN->b_hidden, sizeof(double), NN->nb_cacher, save_file);
    fread(NN->b_output, sizeof(double), NN->nb_sorties, save_file);

    NN->w_input_hidden = malloc(NN->nb_entrees * sizeof(double*));
    for (int i = 0; i < NN->nb_entrees; i++) {
        NN->w_input_hidden[i] = malloc(NN->nb_cacher * sizeof(double));
        fread(NN->w_input_hidden[i], sizeof(double), NN->nb_cacher, save_file);
    }
    NN->w_hidden_output = malloc(NN->nb_cacher * sizeof(double*));
    for (int i = 0; i < NN->nb_cacher; i++) {
        NN->w_hidden_output[i] = malloc(NN->nb_sorties * sizeof(double));
        fread(NN->w_hidden_output[i], sizeof(double), NN->nb_sorties, save_file);
    }
    NN->cacher = calloc(NN->nb_cacher, sizeof(double));
    NN->sortie = calloc(NN->nb_sorties, sizeof(double));
    NN->entree = calloc(NN->nb_entrees, sizeof(double));
 
    fclose(save_file);
   
}

int main(int argc, char* argv[]) {

    if (argc == 2) {

        int Val = strcmp("Train", argv[1]);
        int Val2 = strcmp("Create", argv[1]);
        int Val3 = strcmp("Supress", argv[1]);

        if (Val == 0 ) {
            Opener();
            Trainer();
            if (NN == NULL) {
                errx(EXIT_FAILURE,"Erreur : réseau non chargé !\n");
                return 1;
            }
            Saver();
            printf("Trained");
            return 0;

        }
        if (Val2 == 0) {
            NN = create_network(2, 2, 1, .1);
            Saver();
            printf("Created Network");
            printf("%d", NN == NULL);
            return 0;

        }
        if (Val3 == 0) {
            Free_All(NN);
            printf("Freed Network");
            return 0;

        }
        return 0;
    }

    if (argc == 4) {
       
        int Val = strcmp("Execute", argv[1]);
        
        int Z1 =  strcmp("0", argv[2]);
        int Z2 = strcmp("0", argv[3]);
        
        int U1 = strcmp("1", argv[2]);
        int U2 = strcmp("1", argv[3]);
        
        
        if (Val == 0 && (Z1 == 0 || U1 == 0) && (Z2 == 0 || U2 == 0)) {
            Opener();
           
            if (NN == NULL) {
                printf("Erreur : réseau non chargé !\n");
                return 1;
            }
            double ee[2] = { atoi(argv[2]),atoi(argv[3]) };
            Execute_Forward_Total(NN, ee);
            printf("%d %d : %.3f\n", atoi(argv[2]), atoi(argv[3]), NN->sortie[0]);
            printf("Execution ended");
            Saver();
            return 0;
        }

    }
    return 0;
}



