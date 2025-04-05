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
void display_sequence(int a, int *b, double *c, int d);
void find_maxSequences(int a[M][M], int *b, int *c, int *d);
void process_maxShiftedSequence(int a[M][M], double b[M][M], int *c);
void display_genSEED27();
void process_all_sequences();


int main(void) {
    display_genSEED27(); // LCM generated sequence for SEED (X0) , 27
    process_all_sequences(); // 100 LCM generated sequences

    return 0;
}


// generate a sequence using LCG
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


// find all unique sequences for X0 in range [0, 99]
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


// display all sequences
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


// display single sequence
void display_sequence(int seed, int *sequence, double *random_numbers, int length) {
    printf("Generated Sequence for seed %d: ", seed);
    for (int i = 0; i < length; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n    : ");
    for (int i = 0; i < length; i++) {
        printf("%.2f ", random_numbers[i]);
    }
    printf("\n");
}


// find the maximal length sequences
void find_maxSequences(int sequences[M][M], int *sequence_lengths, int *max_seeds, int *max_count) {
    int max_length = 0;
    
    // find the maximal length
    for (int seed = 0; seed < M; ++seed) {
        if (sequence_lengths[seed] > max_length) {
            max_length = sequence_lengths[seed];
        }
    }
    printf("\n =>>> Maximal length of a Sequence is : %d \n", max_length);
    
    // collect all seeds with the maximal length
    *max_count = 0;
    for (int seed = 0; seed < M; ++seed) {
        if (sequence_lengths[seed] == max_length) {
            max_seeds[*max_count] = seed;
            (*max_count)++;
        }
    }
    printf("\n =>>> %d Sequences have maximal length. \n", *max_count);

}


// handle maximal length sequences and shifted sequences
void process_maxShiftedSequence(int sequences[M][M], double random_numbers[M][M], int *sequence_lengths) {
    int max_seeds[M], max_count;
    find_maxSequences(sequences, sequence_lengths, max_seeds, &max_count);
    
    // display and then shift maximal sequence
    if (max_count > 0) {
        int max_seed = max_seeds[0];
        printf("\nMaximal Length Sequence (Seed %d):\n", max_seed);
        display_sequence(max_seed, sequences[max_seed], random_numbers[max_seed], sequence_lengths[max_seed]);
        
        // shift seed, to 10th number in sequence
        //  if (sequence_length[max_seed] >= 10) {...}
        int new_seed = sequences[max_seed][9];
        int new_sequence[M], new_length;
        double new_random_numbers[M];
        generate_sequence(new_seed, new_sequence, new_random_numbers, &new_length);
        
        printf("\nUsing 10th number (%d) as new seed:\n", new_seed);
        display_sequence(new_seed, new_sequence, new_random_numbers, new_length);
    }
}


// display generated sequence for SEED 27
void display_genSEED27() {
    int sequence[M], length;
    double random_numbers[M];
    generate_sequence(SEED, sequence, random_numbers, &length);
    display_sequence(SEED, sequence, random_numbers, length);
}


// process and display all sequences 
void process_all_sequences() {
    // M = 100
    int all_sequences[M][M] = {{0}};
    double all_random_numbers[M][M] = {{0}};
    int sequence_lengths[M] = {0};
    
    find_all_sequences(all_sequences, all_random_numbers, sequence_lengths);
    display_all_sequences(all_sequences, all_random_numbers, sequence_lengths);
    process_maxShiftedSequence(all_sequences, all_random_numbers, sequence_lengths);
}