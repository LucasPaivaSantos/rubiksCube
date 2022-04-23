#include <stdio.h>
#define DI 3 // cube's dimensions
#define FACES 6

#define FRONT 0
#define LEFT 1
#define RIGHT 2
#define BACK 3
#define TOP 4
#define BOTTOM 5

#define GREEN 0
#define ORANGE 1
#define RED 2
#define BLUE 3
#define WHITE 4
#define YELLOW 5

char COLORS[FACES] = {'G', 'O', 'R', 'B', 'W', 'Y'};

void setFace(int face[][DI], int value)
{
    for (int i = 0; i < DI; i++)
    {
        for (int j = 0; j < DI; j++)
        {
            face[i][j] = value;
        }
    }
    return;
}

void showFace(int face[][DI])
{
    for (int i = 0; i < DI; i++)
    {
        for (int j = 0; j < DI; j++)
        {
            printf("%c", COLORS[face[i][j]]);
        }
        printf("\n");
    }
    return;
}

void showRow(int row, int face[][DI])
{
    for (int i = 0; i < DI; i++)
    {
        printf("%c", COLORS[face[row][i]]);
    }
    printf(" ");
    return;
}

void showBlankRow()
{
    printf("    ");
    return;
}

void showCube(int cube[FACES][DI][DI])
{
    printf("=== CUBE ===\n");
    // top section
    for (int i = 0; i < DI; i++)
    {
        showBlankRow();
        showRow(i, cube[TOP]);
        printf("\n");
    }
    // middle section
    for (int i = 0; i < DI; i++)
    {
        showRow(i, cube[LEFT]);
        showRow(i, cube[FRONT]);
        showRow(i, cube[RIGHT]);
        showRow(i, cube[BACK]);
        printf("\n");
    }
    // lower section
    for (int i = 0; i < DI; i++)
    {
        showBlankRow();
        showRow(i, cube[BOTTOM]);
        printf("\n");
    }
    return;
}

void slideRow(int row, int face1[][DI], int face2[][DI], int face3[][DI], int face4[][DI])
{
    int auxRow[DI];
    for (int c = 0; c < DI; c++)
    {
        auxRow[c] = face1[row][c];
    }
    for (int c = 0; c < DI; c++)
    {
        face1[row][c] = face4[row][c];
        face4[row][c] = face3[row][c];
        face3[row][c] = face2[row][c];
    }
    for (int c = 0; c < DI; c++)
    {
        face2[row][c] = auxRow[c];
    }
    return;
}

void slideRowInverted(int row, int face1[][DI], int face2[][DI], int face3[][DI], int face4[][DI])
{
    int auxRow[DI];
    for (int c = 0; c < DI; c++)
    {
        auxRow[c] = face1[row][c];
    }
    for (int c = 0; c < DI; c++)
    {
        face1[row][c] = face2[row][c];
        face2[row][c] = face3[row][c];
        face3[row][c] = face4[row][c];
    }
    for (int c = 0; c < DI; c++)
    {
        face4[row][c] = auxRow[c];
    }
    return;
}

void slideCol(int col, int face1[][DI], int face2[][DI], int face3[][DI], int face4[][DI])
{
    int auxCol[DI];
    for (int r = 0; r < DI; r++)
    {
        auxCol[r] = face1[r][col];
    }
    for (int r = 0; r < DI; r++)
    {
        face1[r][col] = face4[r][col];
        face4[r][col] = face3[r][col];
        face3[r][col] = face2[r][col];
    }
    for (int r = 0; r < DI; r++)
    {
        face2[r][col] = auxCol[r];
    }
    return;
}

void slideColInverted(int col, int face1[][DI], int face2[][DI], int face3[][DI], int face4[][DI])
{
    int auxCol[DI];
    for (int r = 0; r < DI; r++)
    {
        auxCol[r] = face1[r][col];
    }
    for (int r = 0; r < DI; r++)
    {
        face1[r][col] = face2[r][col];
        face2[r][col] = face3[r][col];
        face3[r][col] = face4[r][col];
    }
    for (int r = 0; r < DI; r++)
    {
        face4[r][col] = auxCol[r];
    }
    return;
}

void slideFace(int targetFace, int face1[][DI], int face2[][DI], int face3[][DI], int face4[][DI])
{
    int auxFace[DI][DI];
    for (int i = 0; i < DI; i++)
    {
        auxFace[i][targetFace] = face2[i][targetFace];
        // transposes
        face1[targetFace][i] = face4[i][targetFace];
        face2[targetFace][i] = face3[i][targetFace];
        // keeps orientation
        face3[i][targetFace] = face1[i][targetFace + 1];
        face4[i][targetFace] = auxFace[i][targetFace];
    }

    // top face perspective correction
    int auxRow[DI];
    int auxRow2[DI];
    for (int i = 0; i < DI; i++)
    {
        auxRow[i] = face1[DI - 1][i];

        face1[DI - 1][i] = face1[targetFace][i];

        face1[targetFace][i] = auxRow[i];
    }
    // left face perspective correction
    int auxCol[DI];
    int auxCol2[DI];
    for (int i = 0; i < DI; i++)
    {
        auxCol[i] = face3[i][DI - 1];

        face3[i][DI - 1] = face3[i][targetFace];

        face3[i][targetFace] = auxCol[i];
    }
    return;
}

void slideFaceInverted(int targetFace, int face1[][DI], int face2[][DI], int face3[][DI], int face4[][DI])
{
    int auxFace[DI][DI];
    for (int i = 0; i < DI; i++)
    {
        auxFace[i][targetFace] = face1[i][targetFace];
        // transposes
        face1[targetFace][i] = face3[i][targetFace];
        face2[targetFace][i] = face4[i][targetFace];
        // keeps orientation
        face3[i][targetFace] = face2[i][targetFace + 1];
        face4[i][targetFace] = auxFace[i][targetFace];
    }

    // top face perspective correction
    int auxRow[DI];
    int auxRow2[DI];
    for (int i = 0; i < DI; i++)
    {
        auxRow[i] = face1[DI - 1][i];

        face1[DI - 1][i] = face1[targetFace][i];

        face1[targetFace][i] = auxRow[i];
    }
    // left face perspective correction
    int auxCol[DI];
    int auxCol2[DI];
    for (int i = 0; i < DI; i++)
    {
        auxCol[i] = face3[i][DI - 1];

        face3[i][DI - 1] = face3[i][targetFace];

        face3[i][targetFace] = auxCol[i];
    }
    return;
}

// move interpretation
void doMove(char move, int cube[FACES][DI][DI])
{
    switch (move)
    {
    case 'U': // U
        slideRow(0, cube[FRONT], cube[LEFT], cube[BACK], cube[RIGHT]);
        break;

    case 'u': // U'
        slideRowInverted(0, cube[FRONT], cube[LEFT], cube[BACK], cube[RIGHT]);
        break;

    case 'D': // D
        slideRow(2, cube[FRONT], cube[LEFT], cube[BACK], cube[RIGHT]);
        break;

    case 'd': // D'
        slideRowInverted(2, cube[FRONT], cube[LEFT], cube[BACK], cube[RIGHT]);
        break;

    case 'L': // L
        slideCol(0, cube[FRONT], cube[TOP], cube[BACK], cube[BOTTOM]);
        break;

    case 'l': // L'
        slideColInverted(0, cube[FRONT], cube[TOP], cube[BACK], cube[BOTTOM]);
        break;

    case 'R': // R
        slideCol(2, cube[FRONT], cube[TOP], cube[BACK], cube[BOTTOM]);
        break;

    case 'r': // R'
        slideColInverted(2, cube[FRONT], cube[TOP], cube[BACK], cube[BOTTOM]);
        break;

    case 'F': // F
        slideFace(0, cube[TOP], cube[BOTTOM], cube[LEFT], cube[RIGHT]);
        break;

    case 'f': // F'
        slideFaceInverted(0, cube[TOP], cube[BOTTOM], cube[LEFT], cube[RIGHT]);
        break;

    case 'B': // B
        // slideFace(2, cube[TOP], cube[BOTTOM], cube[LEFT], cube[RIGHT]);
        break;

    case 'b': // B'
        // slideFaceInverted(2, cube[TOP], cube[BOTTOM], cube[LEFT], cube[RIGHT]);
        break;

    default:
        break;
    }
}

int main()
{
    int cube[FACES][DI][DI];
    char move;

    // initialization
    setFace(cube[FRONT], GREEN);
    setFace(cube[LEFT], ORANGE);
    setFace(cube[RIGHT], RED);
    setFace(cube[BACK], BLUE);
    setFace(cube[TOP], WHITE);
    setFace(cube[BOTTOM], YELLOW);

    // game loop
    do
    {
        showCube(cube);
        printf("Move: ");
        move = getchar();
        if (move == '0')
        {
            break;
        }
        doMove(move, cube);
        printf("\n");
        // cleans aditional character
        while ((move = getchar()) != '\n' && move != EOF)
        {
        }
    } while (1);

    return 0;
}