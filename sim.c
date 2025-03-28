#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// LCG parameters
#define A 17
#define C 43
#define M 100
#define SEED 27

// function prototypes
void generate_sequence(int a, int *b, double *c, int *d);
void find_all_sequences(int a[M][M], double b[M][M], int *c);
void display_all_sequences(int a[M][M], double b[M][M], int *c);




int main() {
    int sequence[M], length;
    double random_numbers[M];
    generate_sequence(SEED, sequence, random_numbers, &length);

    printf("Generated Sequences (Ri, Rn)  for seed %d: ", SEED);
    for (int i = 0; i < length; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n    : ");
    for (int i = 0; i < length; i++) {
        printf("%.2f ", random_numbers[i]);
    }

    printf("\n\n Finding all possible sequences...\n");
    int all_sequences[M][M] = {{0}};
    double all_random_numbers[M][M] = {{0}};
    int sequence_lengths[M] = {0};
    find_all_sequences(all_sequences, all_random_numbers, sequence_lengths);
    display_all_sequences(all_sequences, all_random_numbers, sequence_lengths);

    return 0;
}


// function to generate a sequence using LCG
void generate_sequence(int seed, int *sequence, double *random_numbers, int *length) {
    bool seen[M] = {false};
    int Xn = seed;
    *length = 0;
    
    // generating random integers, then random numbers
    while (!seen[Xn]) {
        sequence[(*length)] = Xn;
        random_numbers[(*length)] = (double)Xn / M;
        (*length)++;
        seen[Xn] = true;
        Xn = (A * Xn + C) % M;
    }
}



// function to find all unique sequences for X0 in range [0, 99]
void find_all_sequences(int sequences[M][M], double random_numbers[M][M], int *sequence_lengths) {
    bool unique[M] = {false};
    int temp_sequence[M], length;
    double temp_random_numbers[M];
    
    for (int seed = 0; seed < M; ++seed) {
        generate_sequence(seed, temp_sequence, temp_random_numbers, &length);
        
        if (!unique[temp_sequence[0]]) {
            unique[temp_sequence[0]] = true;
            memcpy(sequences[seed], temp_sequence, length * sizeof(int));
            memcpy(random_numbers[seed], temp_random_numbers, length * sizeof(double));
            sequence_lengths[seed] = length;
        }
    }
}


// function to display all sequences
void display_all_sequences(int sequences[M][M], double random_numbers[M][M], int *sequence_lengths) {
    printf("\n Finding all possible sequences...\n");
    printf("Seed | Sequence \n");
    printf("-----------------------------\n");
    
    for (int seed = 0; seed < M; ++seed) {
        if (sequence_lengths[seed] > 0) {
            printf("%2d : ", seed);
            for (int i = 0; i < sequence_lengths[seed]; i++) {
                printf("%d ", sequences[seed][i]);
            }
            printf("\n    : ");
            for (int i = 0; i < sequence_lengths[seed]; i++) {
                printf("%.2f ", random_numbers[seed][i]);
            }
            printf("\n");
        }
    }
}