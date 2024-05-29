#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "lcd.h"

extern TFT_t dev;

typedef struct {
    uint8_t n;
    char colors[6];
    char cube[6][3][3];
} RubiksCube;

// Define a function pointer type for Rubik's cube algorithms
typedef void (*AlgorithmFunction)(RubiksCube *);

// Define a struct to map algorithm names to functions
typedef struct {
    char *name;
    AlgorithmFunction function;
} AlgorithmMapping;

void resetcube(RubiksCube *rubiks_cube);

void printcube(RubiksCube rubiks_cube);

void showcube(RubiksCube rubiks_cube);

void display_draw_rubiks_cube(RubiksCube rubiks_cube);

void rotatefaceclockwise(RubiksCube *rubiks_cube, uint8_t face);

void rotatefacecounterclockwise(RubiksCube *rubiks_cube, uint8_t face);

void U(RubiksCube *rubiks_cube);

void Ui(RubiksCube *rubiks_cube);

void U2(RubiksCube *rubiks_cube);

void R(RubiksCube *rubiks_cube);

void Ri(RubiksCube *rubiks_cube);

void R2(RubiksCube *rubiks_cube);

void F(RubiksCube *rubiks_cube);

void Fi(RubiksCube *rubiks_cube);

void F2(RubiksCube *rubiks_cube);

void D(RubiksCube *rubiks_cube);

void Di(RubiksCube *rubiks_cube);

void D2(RubiksCube *rubiks_cube);

void L(RubiksCube *rubiks_cube);

void Li(RubiksCube *rubiks_cube);

void L2(RubiksCube *rubiks_cube);

void B(RubiksCube *rubiks_cube);

void Bi(RubiksCube *rubiks_cube);

void B2(RubiksCube *rubiks_cube);

void M(RubiksCube *rubiks_cube);

void Mi(RubiksCube *rubiks_cube);

void M2(RubiksCube *rubiks_cube);

void E(RubiksCube *rubiks_cube);

void Ei(RubiksCube *rubiks_cube);

void E2(RubiksCube *rubiks_cube);

void S(RubiksCube *rubiks_cube);

void Si(RubiksCube *rubiks_cube);

void S2(RubiksCube *rubiks_cube);

void Uw(RubiksCube *rubiks_cube);

void Uwi(RubiksCube *rubiks_cube);

void Uw2(RubiksCube *rubiks_cube);

void Rw(RubiksCube *rubiks_cube);

void Rwi(RubiksCube *rubiks_cube);

void Rw2(RubiksCube *rubiks_cube);

void Fw(RubiksCube *rubiks_cube);

void Fwi(RubiksCube *rubiks_cube);

void Fw2(RubiksCube *rubiks_cube);

void Dw(RubiksCube *rubiks_cube);

void Dwi(RubiksCube *rubiks_cube);

void Dw2(RubiksCube *rubiks_cube);

void Lw(RubiksCube *rubiks_cube);

void Lwi(RubiksCube *rubiks_cube);

void Lw2(RubiksCube *rubiks_cube);

void Bw(RubiksCube *rubiks_cube);

void Bwi(RubiksCube *rubiks_cube);

void Bw2(RubiksCube *rubiks_cube);

void X(RubiksCube *rubiks_cube);

void Xi(RubiksCube *rubiks_cube);

void X2(RubiksCube *rubiks_cube);

void Y(RubiksCube *rubiks_cube);

void Yi(RubiksCube *rubiks_cube);

void Y2(RubiksCube *rubiks_cube);

void Z(RubiksCube *rubiks_cube);

void Zi(RubiksCube *rubiks_cube);

void Z2(RubiksCube *rubiks_cube);

void sexymove(RubiksCube *rubiks_cube);

void inversesexymove(RubiksCube *rubiks_cube);

void sledgehammer(RubiksCube *rubiks_cube);

void hedgeslammer(RubiksCube *rubiks_cube);

void sexysledge(RubiksCube *rubiks_cube);

void tperm(RubiksCube *rubiks_cube);

void yperm(RubiksCube *rubiks_cube);

void jbperm(RubiksCube *rubiks_cube);

void japerm(RubiksCube *rubiks_cube);

void raperm(RubiksCube *rubiks_cube);

char *getscramble();

char getmove();

char *getalgorithm();

void makemove(RubiksCube *rubiks_cube, char move);

void scramble(RubiksCube *rubiks_cube, char* scramble_letters);

void performalgorithm(RubiksCube *rubiks_cube, char *algorithm_string);

#endif // CUBE_H