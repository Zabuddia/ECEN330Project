#include "cube.h"

#define MAX_SCRAMBLE_LENGTH 100
#define MAX_ALGORITHM_LENGTH 100

void resetcube(RubiksCube *rubiks_cube) {
    rubiks_cube->n = 3;

    rubiks_cube->colors[0] = 'w';
    rubiks_cube->colors[1] = 'o';
    rubiks_cube->colors[2] = 'g';
    rubiks_cube->colors[3] = 'r';
    rubiks_cube->colors[4] = 'b';
    rubiks_cube->colors[5] = 'y';

    for (uint8_t i = 0; i < 6; ++i) {
        for (uint8_t j = 0; j < rubiks_cube->n; ++j) {
            for (uint8_t k = 0; k < rubiks_cube->n; ++k) {
                rubiks_cube->cube[i][j][k] = rubiks_cube->colors[i];
            }
        }
    }
}

void printcube(RubiksCube rubiks_cube) {
    for (uint8_t i = 0; i < 6; ++i) {
        for (uint8_t j = 0; j < rubiks_cube.n; ++j) {
            for (uint8_t k = 0; k < rubiks_cube.n; ++k) {
                printf("%c ", rubiks_cube.cube[i][j][k]);
            }
        }
    }
    printf("\n");
}

void showcube(RubiksCube rubiks_cube) {
    char top_row[12];
    char middle_row[12];
    char bottom_row[12];

    for (uint8_t i = 0; i < 6; ++i) {
        for (uint8_t j = 0; j < rubiks_cube.n; ++j) {
                if ((i == 0) || (i == 5)) {
                    printf("        ");
                }
            for (uint8_t k = 0; k < rubiks_cube.n; ++k) {
                if ((i == 0) || (i == 5)) {
                    printf("%c ", rubiks_cube.cube[i][j][k]);
                }
                if ((i != 0) && (i != 5)) {
                    if (j == 0) {
                        top_row[3 * i - 3 + k] = rubiks_cube.cube[i][j][k];
                    }
                    if (j == 1) {
                        middle_row[3 * i - 3 + k] = rubiks_cube.cube[i][j][k];
                    }
                    if (j == 2) {
                        bottom_row[3 * i - 3 + k] = rubiks_cube.cube[i][j][k];
                    }
                }
            }
            if ((i == 0) || (i == 5)) {
                printf("\n");
            }
        }
        if (i == 1) {
            printf("       _______\n");
        }
        if (i == 4) {
            for (uint8_t l = 0; l < 3; ++l) {
                for (uint8_t m = 0; m < 12; ++m) {
                    if (l == 0) {
                        if ((m == 2) || (m == 5) || (m == 8)) {
                            printf("%c | ", top_row[m]);
                        }
                        else {
                            printf("%c ", top_row[m]);
                        }

                    }
                    if (l == 1) {
                        if ((m == 2) || (m == 5) || (m == 8)) {
                            printf("%c | ", middle_row[m]);
                        }
                        else {
                            printf("%c ", middle_row[m]);
                        }
                    }
                    if (l == 2) {
                        if ((m == 2) || (m == 5) || (m == 8)) {
                            printf("%c | ", bottom_row[m]);
                        }
                        else {
                            printf("%c ", bottom_row[m]);
                        }
                    }
                }
                printf("\n");
            }
            printf("       %c%c%c%c%c%c%c\n", 45, 45, 45, 45, 45, 45, 45);
        }
    }
}

void display_draw_rubiks_cube(RubiksCube rubiks_cube) {
    lcdFillScreen(&dev, GRAY);
    lcdSetFontBackground(&dev, GRAY);
    lcdDrawString(&dev, 0, 0, "Cube", WHITE);
    lcdSetFontBackground(&dev, BLACK);
        lcdFillRect(&dev, 85, 5, 308, 228, BLACK);
    for (uint8_t j = 0; j < 3; ++j) {
        for (uint8_t i = 0; i < 3; ++i) {
            if (rubiks_cube.cube[2][j][i] == 'w') {
                lcdFillRect(&dev, (i * 74) + 88, (j * 74) + 8, (i * 74) + 157, (j * 74) + 77,
                                       WHITE);
            }
            if (rubiks_cube.cube[2][j][i] == 'o') {
                lcdFillRect(&dev, (i * 74) + 88, (j * 74) + 8, (i * 74) + 157, (j * 74) + 77,
                                       ORANGE);
            }
            if (rubiks_cube.cube[2][j][i] == 'g') {
                lcdFillRect(&dev, (i * 74) + 88, (j * 74) + 8, (i * 74) + 157, (j * 74) + 77,
                                       GREEN);
            }
            if (rubiks_cube.cube[2][j][i] == 'r') {
                lcdFillRect(&dev, (i * 74) + 88, (j * 74) + 8, (i * 74) + 157, (j * 74) + 77,
                                       RED);
            }
            if (rubiks_cube.cube[2][j][i] == 'b') {
                lcdFillRect(&dev, (i * 74) + 88, (j * 74) + 8, (i * 74) + 157, (j * 74) + 77,
                                       BLUE);
            }
            if (rubiks_cube.cube[2][j][i] == 'y') {
                lcdFillRect(&dev, (i * 74) + 88, (j * 74) + 8, (i * 74) + 157, (j * 74) + 77,
                                       YELLOW);
            }
        }
    }
}

void rotatefaceclockwise(RubiksCube *rubiks_cube, uint8_t face) {
    char buffer_1;
    char buffer_2;
    
    buffer_1 = rubiks_cube->cube[face][0][0];
    rubiks_cube->cube[face][0][0] = rubiks_cube->cube[face][2][0];
    rubiks_cube->cube[face][2][0] = rubiks_cube->cube[face][2][2];
    rubiks_cube->cube[face][2][2] = rubiks_cube->cube[face][0][2];
    rubiks_cube->cube[face][0][2] = buffer_1;

    buffer_2 = rubiks_cube->cube[face][0][1];
    rubiks_cube->cube[face][0][1] = rubiks_cube->cube[face][1][0];
    rubiks_cube->cube[face][1][0] = rubiks_cube->cube[face][2][1];
    rubiks_cube->cube[face][2][1] = rubiks_cube->cube[face][1][2];
    rubiks_cube->cube[face][1][2] = buffer_2;
}

void rotatefacecounterclockwise(RubiksCube *rubiks_cube, uint8_t face) {
    char buffer_1;
    char buffer_2;
    
    buffer_1 = rubiks_cube->cube[face][0][0];
    rubiks_cube->cube[face][0][0] = rubiks_cube->cube[face][0][2];
    rubiks_cube->cube[face][0][2] = rubiks_cube->cube[face][2][2];
    rubiks_cube->cube[face][2][2] = rubiks_cube->cube[face][2][0];
    rubiks_cube->cube[face][2][0] = buffer_1;

    buffer_2 = rubiks_cube->cube[face][0][1];
    rubiks_cube->cube[face][0][1] = rubiks_cube->cube[face][1][2];
    rubiks_cube->cube[face][1][2] = rubiks_cube->cube[face][2][1];
    rubiks_cube->cube[face][2][1] = rubiks_cube->cube[face][1][0];
    rubiks_cube->cube[face][1][0] = buffer_2;
}

void U(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[1][0][i];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[1][0][i] = rubiks_cube->cube[2][0][i];
        rubiks_cube->cube[2][0][i] = rubiks_cube->cube[3][0][i];
        rubiks_cube->cube[3][0][i] = rubiks_cube->cube[4][0][i];
        rubiks_cube->cube[4][0][i] = buffer[i];
    }

    rotatefaceclockwise(rubiks_cube, 0);
}

void Ui(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[1][0][i];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[1][0][i] = rubiks_cube->cube[4][0][i];
        rubiks_cube->cube[4][0][i] = rubiks_cube->cube[3][0][i];
        rubiks_cube->cube[3][0][i] = rubiks_cube->cube[2][0][i];
        rubiks_cube->cube[2][0][i] = buffer[i];
    }

    rotatefacecounterclockwise(rubiks_cube, 0);
}

void U2(RubiksCube *rubiks_cube) {
    U(rubiks_cube);
    U(rubiks_cube);
}

void R(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[0][i][2];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[0][i][2] = rubiks_cube->cube[2][i][2];
        rubiks_cube->cube[2][i][2] = rubiks_cube->cube[5][i][2];
        rubiks_cube->cube[5][i][2] = rubiks_cube->cube[4][-i + 2][0];
        rubiks_cube->cube[4][-i + 2][0] = buffer[i];
    }

    rotatefaceclockwise(rubiks_cube, 3);
}

void Ri(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[0][i][2];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[0][i][2] = rubiks_cube->cube[4][-i + 2][0];
        rubiks_cube->cube[4][-i + 2][0] = rubiks_cube->cube[5][i][2];
        rubiks_cube->cube[5][i][2] = rubiks_cube->cube[2][i][2];
        rubiks_cube->cube[2][i][2] = buffer[i];
    }

    rotatefacecounterclockwise(rubiks_cube, 3);
}

void R2(RubiksCube *rubiks_cube) {
    R(rubiks_cube);
    R(rubiks_cube);
}

void F(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[0][2][i];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[0][2][i] = rubiks_cube->cube[1][-i + 2][2];
        rubiks_cube->cube[1][-i + 2][2] = rubiks_cube->cube[5][0][-i + 2];
        rubiks_cube->cube[5][0][-i + 2] = rubiks_cube->cube[3][i][0];
        rubiks_cube->cube[3][i][0] = buffer[i];
    }

    rotatefaceclockwise(rubiks_cube, 2);
}

void Fi(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[0][2][i];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[0][2][i] = rubiks_cube->cube[3][i][0];
        rubiks_cube->cube[3][i][0] = rubiks_cube->cube[5][0][-i + 2];
        rubiks_cube->cube[5][0][-i + 2] = rubiks_cube->cube[1][-i + 2][2];
        rubiks_cube->cube[1][-i + 2][2] = buffer[i];
    }

    rotatefacecounterclockwise(rubiks_cube, 2);
}

void F2(RubiksCube *rubiks_cube) {
    F(rubiks_cube);
    F(rubiks_cube);
}

void D(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[1][2][i];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[1][2][i] = rubiks_cube->cube[4][2][i];
        rubiks_cube->cube[4][2][i] = rubiks_cube->cube[3][2][i];
        rubiks_cube->cube[3][2][i] = rubiks_cube->cube[2][2][i];
        rubiks_cube->cube[2][2][i] = buffer[i];
    }

    rotatefaceclockwise(rubiks_cube, 5);
}

void Di(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[1][2][i];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[1][2][i] = rubiks_cube->cube[2][2][i];
        rubiks_cube->cube[2][2][i] = rubiks_cube->cube[3][2][i];
        rubiks_cube->cube[3][2][i] = rubiks_cube->cube[4][2][i];
        rubiks_cube->cube[4][2][i] = buffer[i];
    }

    rotatefacecounterclockwise(rubiks_cube, 5);
}

void D2(RubiksCube *rubiks_cube) {
    D(rubiks_cube);
    D(rubiks_cube);
}

void L(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[0][i][0];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[0][i][0] = rubiks_cube->cube[4][-i + 2][2];
        rubiks_cube->cube[4][-i + 2][2] = rubiks_cube->cube[5][i][0];
        rubiks_cube->cube[5][i][0] = rubiks_cube->cube[2][i][0];
        rubiks_cube->cube[2][i][0] = buffer[i];
    }

    rotatefaceclockwise(rubiks_cube, 1);
}

void Li(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[0][i][0];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[0][i][0] = rubiks_cube->cube[2][i][0];
        rubiks_cube->cube[2][i][0] = rubiks_cube->cube[5][i][0];
        rubiks_cube->cube[5][i][0] = rubiks_cube->cube[4][-i + 2][2];
        rubiks_cube->cube[4][-i + 2][2] = buffer[i];
    }

    rotatefacecounterclockwise(rubiks_cube, 1);
}

void L2(RubiksCube *rubiks_cube) {
    L(rubiks_cube);
    L(rubiks_cube);
}

void B(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[0][0][i];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[0][0][i] = rubiks_cube->cube[3][i][2];
        rubiks_cube->cube[3][i][2] = rubiks_cube->cube[5][2][-i + 2];
        rubiks_cube->cube[5][2][-i + 2] = rubiks_cube->cube[1][-i + 2][0];
        rubiks_cube->cube[1][-i + 2][0] = buffer[i];
    }

    rotatefaceclockwise(rubiks_cube, 4);
}

void Bi(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[0][0][i];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[0][0][i] = rubiks_cube->cube[1][-i + 2][0];
        rubiks_cube->cube[1][-i + 2][0] = rubiks_cube->cube[5][2][-i + 2];
        rubiks_cube->cube[5][2][-i + 2] = rubiks_cube->cube[3][i][2];
        rubiks_cube->cube[3][i][2] = buffer[i];
    }

    rotatefacecounterclockwise(rubiks_cube, 4);
}

void B2(RubiksCube *rubiks_cube) {
    B(rubiks_cube);
    B(rubiks_cube);
}

void M(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[0][i][1];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[0][i][1] = rubiks_cube->cube[4][-i + 2][1];
        rubiks_cube->cube[4][-i + 2][1] = rubiks_cube->cube[5][i][1];
        rubiks_cube->cube[5][i][1] = rubiks_cube->cube[2][i][1];
        rubiks_cube->cube[2][i][1] = buffer[i];
    }
}

void Mi(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[0][i][1];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[0][i][1] = rubiks_cube->cube[2][i][1];
        rubiks_cube->cube[2][i][1] = rubiks_cube->cube[5][i][1];
        rubiks_cube->cube[5][i][1] = rubiks_cube->cube[4][-i + 2][1];
        rubiks_cube->cube[4][-i + 2][1] = buffer[i];
    }
}

void M2(RubiksCube *rubiks_cube) {
    M(rubiks_cube);
    M(rubiks_cube);
}

void E(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[1][1][i];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[1][1][i] = rubiks_cube->cube[4][1][i];
        rubiks_cube->cube[4][1][i] = rubiks_cube->cube[3][1][i];
        rubiks_cube->cube[3][1][i] = rubiks_cube->cube[2][1][i];
        rubiks_cube->cube[2][1][i] = buffer[i];
    }
}

void Ei(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[1][1][i];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[1][1][i] = rubiks_cube->cube[2][1][i];
        rubiks_cube->cube[2][1][i] = rubiks_cube->cube[3][1][i];
        rubiks_cube->cube[3][1][i] = rubiks_cube->cube[4][1][i];
        rubiks_cube->cube[4][1][i] = buffer[i];
    }
}

void E2(RubiksCube *rubiks_cube) {
    E(rubiks_cube);
    E(rubiks_cube);
}

void S(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[0][1][i];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[0][1][i] = rubiks_cube->cube[1][-i + 2][1];
        rubiks_cube->cube[1][-i + 2][1] = rubiks_cube->cube[5][1][-i + 2];
        rubiks_cube->cube[5][1][-i + 2] = rubiks_cube->cube[3][i][1];
        rubiks_cube->cube[3][i][1] = buffer[i];
    }
}

void Si(RubiksCube *rubiks_cube) {
    char buffer[3];

    for (uint8_t i = 0; i < 3; ++i) {
        buffer[i] = rubiks_cube->cube[0][1][i];
    }

    for (uint8_t i = 0; i < 3; ++i) {
        rubiks_cube->cube[0][1][i] = rubiks_cube->cube[3][i][1];
        rubiks_cube->cube[3][i][1] = rubiks_cube->cube[5][1][-i + 2];
        rubiks_cube->cube[5][1][-i + 2] = rubiks_cube->cube[1][-i + 2][1];
        rubiks_cube->cube[1][-i + 2][1] = buffer[i];
    }
}

void S2(RubiksCube *rubiks_cube) {
    S(rubiks_cube);
    S(rubiks_cube);
}

void Uw(RubiksCube *rubiks_cube) {
    U(rubiks_cube);
    Ei(rubiks_cube);
}

void Uwi(RubiksCube *rubiks_cube) {
    Ui(rubiks_cube);
    E(rubiks_cube);
}

void Uw2(RubiksCube *rubiks_cube) {
    Uw(rubiks_cube);
    Uw(rubiks_cube);
}

void Rw(RubiksCube *rubiks_cube) {
    R(rubiks_cube);
    Mi(rubiks_cube);
}

void Rwi(RubiksCube *rubiks_cube) {
    Ri(rubiks_cube);
    M(rubiks_cube);
}

void Rw2(RubiksCube *rubiks_cube) {
    Rw(rubiks_cube);
    Rw(rubiks_cube);
}

void Fw(RubiksCube *rubiks_cube) {
    F(rubiks_cube);
    S(rubiks_cube);
}

void Fwi(RubiksCube *rubiks_cube) {
    Fi(rubiks_cube);
    Si(rubiks_cube);
}

void Fw2(RubiksCube *rubiks_cube) {
    Fw(rubiks_cube);
    Fw(rubiks_cube);
}

void Dw(RubiksCube *rubiks_cube) {
    D(rubiks_cube);
    E(rubiks_cube);
}

void Dwi(RubiksCube *rubiks_cube) {
    Di(rubiks_cube);
    Ei(rubiks_cube);
}

void Dw2(RubiksCube *rubiks_cube) {
    Dw(rubiks_cube);
    Dw(rubiks_cube);
}

void Lw(RubiksCube *rubiks_cube) {
    L(rubiks_cube);
    M(rubiks_cube);
}

void Lwi(RubiksCube *rubiks_cube) {
    Li(rubiks_cube);
    Mi(rubiks_cube);
}

void Lw2(RubiksCube *rubiks_cube) {
    Lw(rubiks_cube);
    Lw(rubiks_cube);
}

void Bw(RubiksCube *rubiks_cube) {
    B(rubiks_cube);
    Si(rubiks_cube);
}

void Bwi(RubiksCube *rubiks_cube) {
    Bi(rubiks_cube);
    S(rubiks_cube);
}

void Bw2(RubiksCube *rubiks_cube) {
    Bw(rubiks_cube);
    Bw(rubiks_cube);
}

void X(RubiksCube *rubiks_cube) {
    Li(rubiks_cube);
    Mi(rubiks_cube);
    R(rubiks_cube);
}

void Xi(RubiksCube *rubiks_cube) {
    L(rubiks_cube);
    M(rubiks_cube);
    Ri(rubiks_cube);
}

void X2(RubiksCube *rubiks_cube) {
    X(rubiks_cube);
    X(rubiks_cube);
}

void Y(RubiksCube *rubiks_cube) {
    U(rubiks_cube);
    Ei(rubiks_cube);
    Di(rubiks_cube);
}

void Yi(RubiksCube *rubiks_cube) {
    Ui(rubiks_cube);
    E(rubiks_cube);
    D(rubiks_cube);
}

void Y2(RubiksCube *rubiks_cube) {
    Y(rubiks_cube);
    Y(rubiks_cube);
}

void Z(RubiksCube *rubiks_cube) {
    F(rubiks_cube);
    S(rubiks_cube);
    Bi(rubiks_cube);
}

void Zi(RubiksCube *rubiks_cube) {
    Fi(rubiks_cube);
    Si(rubiks_cube);
    B(rubiks_cube);
}

void Z2(RubiksCube *rubiks_cube) {
    Z(rubiks_cube);
    Z(rubiks_cube);
}

void sexymove(RubiksCube *rubiks_cube) {
    R(rubiks_cube);
    U(rubiks_cube);
    Ri(rubiks_cube);
    Ui(rubiks_cube);
}

void inversesexymove(RubiksCube *rubiks_cube) {
    U(rubiks_cube);
    R(rubiks_cube);
    Ui(rubiks_cube);
    Ri(rubiks_cube);
}

void sledgehammer(RubiksCube *rubiks_cube) {
    Ri(rubiks_cube);
    F(rubiks_cube);
    R(rubiks_cube);
    Fi(rubiks_cube);
}

void hedgeslammer(RubiksCube *rubiks_cube) {
    F(rubiks_cube);
    Ri(rubiks_cube);
    Fi(rubiks_cube);
    R(rubiks_cube);
}

void sexysledge(RubiksCube *rubiks_cube) {
    sexymove(rubiks_cube);
    sledgehammer(rubiks_cube);
}

void tperm(RubiksCube *rubiks_cube) {
    sexymove(rubiks_cube);
    Ri(rubiks_cube);
    F(rubiks_cube);
    R2(rubiks_cube);
    Ui(rubiks_cube);
    Ri(rubiks_cube);
    Ui(rubiks_cube);
    R(rubiks_cube);
    U(rubiks_cube);
    Ri(rubiks_cube);
    Fi(rubiks_cube);
}

void yperm(RubiksCube *rubiks_cube) {
    F(rubiks_cube);
    R(rubiks_cube);
    Ui(rubiks_cube);
    Ri(rubiks_cube);
    Ui(rubiks_cube);
    R(rubiks_cube);
    U(rubiks_cube);
    Ri(rubiks_cube);
    Fi(rubiks_cube);
    sexysledge(rubiks_cube);
}

void jbperm(RubiksCube *rubiks_cube) {
    R(rubiks_cube);
    U(rubiks_cube);
    Ri(rubiks_cube);
    Fi(rubiks_cube);
    sexymove(rubiks_cube);
    Ri(rubiks_cube);
    F(rubiks_cube);
    R2(rubiks_cube);
    Ui(rubiks_cube);
    Ri(rubiks_cube);
    Ui(rubiks_cube);
}

void japerm(RubiksCube *rubiks_cube) {
    R2(rubiks_cube);
    D(rubiks_cube);
    R(rubiks_cube);
    Di(rubiks_cube);
    R(rubiks_cube);
    F2(rubiks_cube);
    Li(rubiks_cube);
    U(rubiks_cube);
    L(rubiks_cube);
    F2(rubiks_cube);
}

void raperm(RubiksCube *rubiks_cube) {
    R(rubiks_cube);
    Ui(rubiks_cube);
    Ri(rubiks_cube);
    Ui(rubiks_cube);
    R(rubiks_cube);
    U(rubiks_cube);
    R(rubiks_cube);
    D(rubiks_cube);
    Ri(rubiks_cube);
    Ui(rubiks_cube);
    R(rubiks_cube);
    Di(rubiks_cube);
    Ri(rubiks_cube);
    U2(rubiks_cube);
    Ri(rubiks_cube);
    Ui(rubiks_cube);
}

char *getscramble() {
    char *scramble = (char *)malloc(MAX_SCRAMBLE_LENGTH);
    printf("Enter the scramble with no spaces between the characters.\nUse uppercase letters to indicate clockwise turns and lowercase letters to indicate counterclockwise turns: ");
    scanf("%s", scramble);

    return scramble;
}

char getmove() {
    char move;
    printf("Enter a letter to move the Rubik's cube.\nUse uppercase letters to indicate clockwise turns and lowercase letters to indicate counterclockwise turns (enter q to stop): ");
    scanf("%c", &move);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    // if (move == 'q') {
    //     exit(0);
    // }
    return move;
}

char *getalgorithm() {
    char *algorithm = (char *)malloc(MAX_ALGORITHM_LENGTH);
    printf("Enter an algorithm that you would like to be performed on the cube: ");
    scanf("%s", algorithm);

    return algorithm;
}

void makemove(RubiksCube *rubiks_cube, char move) {
    switch (move) {
    case 'U':
        U(rubiks_cube);
        break;
    case 'u':
        Ui(rubiks_cube);
        break;
    case 'R':
        R(rubiks_cube);
        break;
    case 'r':
        Ri(rubiks_cube);
        break;
    case 'F':
        F(rubiks_cube);
        break;
    case 'f':
        Fi(rubiks_cube);
        break;
    case 'D':
        D(rubiks_cube);
        break;
    case 'd':
        Di(rubiks_cube);
        break;
    case 'L':
        L(rubiks_cube);
        break;
    case 'l':
        Li(rubiks_cube);
        break;
    case 'B':
        B(rubiks_cube);
        break;
    case 'b':
        Bi(rubiks_cube);
        break;
    case 'X':
        X(rubiks_cube);
        break;
    case 'x':
        Xi(rubiks_cube);
        break;
    case 'Y':
        Y(rubiks_cube);
        break;
    case 'y':
        Yi(rubiks_cube);
        break;
    case 'Z':
        Z(rubiks_cube);
        break;
    case 'z':
        Zi(rubiks_cube);
        break;
    case 'M':
        M(rubiks_cube);
        break;
    case 'm':
        Mi(rubiks_cube);
        break;
    case 'S':
        S(rubiks_cube);
        break;
    case 's':
        Si(rubiks_cube);
        break;
    case 'E':
        E(rubiks_cube);
        break;
    case 'e':
        Ei(rubiks_cube);
        break;
    case 'q':
        return;
    default:
        printf("%c is not a valid move.\n", move);
    }
}

void scramble(RubiksCube *rubiks_cube, char *scramble_letters) {
    for (int i = 0; i < strlen(scramble_letters); ++i) {
        char letter = scramble_letters[i];
        makemove(rubiks_cube, letter);
    }
}

void performalgorithm(RubiksCube *rubiks_cube, char *algorithm_string) {
    AlgorithmMapping algorithms[] = {
        {"tperm", tperm},
        {"sexymove", sexymove},
        {"inversesexymove", inversesexymove},
        {"sledgehammer", sledgehammer},
        {"hedgeslammer", hedgeslammer},
        {"sexysledge", sexysledge},
        {"yperm", yperm},
        {"jbperm", jbperm},
        {"japerm", japerm},
        {"raperm", raperm}
        // Add more as needed
    };

    // Search for the algorithm name in the array
    for (int i = 0; i < sizeof(algorithms) / sizeof(algorithms[0]); i++) {
        if (strcmp(algorithm_string, algorithms[i].name) == 0) {
            // If found, execute the corresponding function
            algorithms[i].function(rubiks_cube);
            return;
        }
    }

    // If the algorithm name is not found, print an error message
    printf("%s is not a valid algorithm name\n", algorithm_string);
}