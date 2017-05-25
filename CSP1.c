#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5

typedef struct cell{
    int value;
    int color; // 0 black, 2 white
} cell;

void print_grid(cell **grid){
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            if (grid[i][j].color != 0){
                printf(" %d ", grid[i][j].value);
            } else{
                printf(" %d ", 0);
            }
        }
        printf("\n");
    }
}

int score_grid(cell **grid){
    int i, j, k, score = 0;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            if (grid[i][j].color != 0){
                for (k = 0; k < N; k++){
                    if (grid[i][k].value == grid[i][j].value && k != j && grid[i][k].value != 0){
                        score += 10;
                    }
                }
                for (k = 0; k < N; k++){
                    if (grid[k][j].value == grid[i][j].value && k != i && grid[k][j].value != 0){
                        score += 10;
                    }
                }
            }
        }
    }
    return score;
}

void check_cell(cell **grid, int i, int j, int *score){
    int tmp_score, k;
    if (grid[i][j].color == 1 && grid[i][j].value != 0){
        grid[i][j].color = 0;
        tmp_score = score_grid(grid);
        if (!(tmp_score < *score)){
            grid[i][j].color = 1;
            return;
        }
        if (i == 0){
            if (j == 0){
                grid[0][1].color = 2;
                grid[1][0].color = 2;
            } else if (j == N - 1){
                grid[0][N - 2].color = 2;
                grid[1][N - 1].color = 2;
            } else {
                grid[0][j - 1].color = 2;
                grid[0][j + 1].color = 2;
                grid[1][j].color = 2;
            }
            *score = tmp_score;
            return;
        }
        if (i == N - 1){
            if (j == 0){
                grid[N - 1][1].color = 2;
                grid[N - 2][0].color = 2;
            } else if (j == N - 1){
                grid[N - 1][N - 2].color = 2;
                grid[N - 2][N - 1].color = 2;
            } else {
                grid[N - 1][j - 1].color = 2;
                grid[N - 1][j + 1].color = 2;
                grid[N - 2][j].color = 2;
            }
            *score = tmp_score;
            return;
        }
        if (j == 0){
            if (i == 0){
                grid[0][1].color = 2;
                grid[1][0].color = 2;
            } else if (i == N - 1){
                grid[N - 2][0].color = 2;
                grid[N - 1][1].color = 2;
            } else {
                grid[i - 1][0].color = 2;
                grid[i + 1][0].color = 2;
                grid[i][1].color = 2;
            }
            *score = tmp_score;
            return;
        }
        if (j == N - 1){
            if (i == 0){
                grid[0][N - 2].color = 2;
                grid[1][N - 1].color = 2;
            } else if (i == N - 1){
                grid[N - 1][N - 2].color = 2;
                grid[N - 2][N - 1].color = 2;
            } else {
                grid[i - 1][N - 1].color = 2;
                grid[i + 1][N - 1].color = 2;
                grid[i][N - 2].color = 2;
            }
            *score = tmp_score;
            return;
        }
        grid[i - 1][j].color = 2;
        grid[i + 1][j].color = 2;
        grid[i][j - 1].color = 2;
        grid[i][j + 1].color = 2;
        *score = tmp_score;
        return;
    }
}

int main(){
    time_t t;
    cell **grid;
    grid = (cell **) malloc(N * sizeof(cell *));
    int i, j;

    for (i = 0; i < N; i++){
        grid[i] = (cell *) malloc(N * sizeof(cell));
    }

    srand((unsigned) time(&t));
    double r;

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            grid[i][j].value = (rand() % (N)) + 1;
            grid[i][j].color = 2;
        }
    }

    print_grid(grid);
    printf("\n");

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            r = (rand() % 100) / 100.0;
            if (r < 0.4){
                if (i == 0){
                    if (j == 0){
                        if (grid[0][1].color != 0 && grid[1][0].color != 0){
                            grid[i][j].color = 0;
                        }
                    } else if (j == N - 1){
                        if (grid[0][N - 2].color != 0 && grid[1][N - 1].color != 0){
                            grid[i][j].color = 0;
                        }
                    } else {
                        if (grid[0][j - 1].color != 0 && grid[0][j - 1].color != 0 && grid[1][j].color != 0){
                            grid[i][j].color = 0;
                        }
                    }
                }
                if (i == N - 1){
                    if (j == 0){
                        if (grid[N - 1][1].color != 0 && grid[N - 2][0].color != 0){
                            grid[i][j].color = 0;
                        }
                    } else if (j == N - 1){
                        if (grid[N - 1][N - 2].color != 0 && grid[N - 2][N - 1].color != 0){
                            grid[i][j].color = 0;
                        }
                    } else {
                        if (grid[N - 1][j - 1].color != 0 && grid[N - 1][j + 1].color != 0 && grid[N - 2][j].color != 0){
                            grid[i][j].color = 0;
                        }
                    }
                }
                if (j == 0){
                    if (i == 0){
                        if (grid[0][1].color != 0 && grid[1][0].color != 0){
                            grid[i][j].color = 0;
                        }
                    } else if (i == N - 1){
                        if (grid[N - 2][0].color != 0 && grid[N - 1][1].color != 0){
                            grid[i][j].color = 0;
                        }
                    } else {
                        if (grid[i - 1][0].color != 0 && grid[i + 1][0].color != 0 && grid[i][1].color != 0){
                            grid[i][j].color = 0;
                        }
                    }
                }
                if (j == N - 1){
                    if (i == 0){
                        if (grid[0][N - 2].color != 0 && grid[1][N - 1].color != 0){
                            grid[i][j].color = 0;
                        }
                    } else if (i == N - 1){
                        if (grid[N - 1][N - 2].color != 0 && grid[N - 2][N - 1].color != 0){
                            grid[i][j].color = 0;
                        }
                    } else {
                        if (grid[i - 1][N - 1].color != 0 && grid[i + 1][N - 1].color != 0 && grid[i][N - 2].color != 0){
                            grid[i][j].color = 0;
                        }
                    }
                }
                if (grid[i - 1][j].color != 0 && grid[i + 1][j].color != 0 && grid[i][j - 1].color != 0 && grid[i][j + 1].color != 0){
                            grid[i][j].color = 0;
                }
            }
        }
    }

    print_grid(grid);
    int g;
    g = score_grid(grid);
    printf("grid's grade = %d\n", g);
    /*
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            check_cell(grid, i, j, &g);
        }
    }
    */
    print_grid(grid);
    g = score_grid(grid);
    printf("grid's grade = %d\n", g);
    /*  SOLVABLE GRID
    grid[0][0] = 1;
    grid[0][1] = 5;
    grid[0][2] = 3;
    grid[0][3] = 1;
    grid[0][4] = 2;

    grid[1][0] = 5;
    grid[1][1] = 4;
    grid[1][2] = 1;
    grid[1][3] = 3;
    grid[1][4] = 4;

    grid[2][0] = 3;
    grid[2][1] = 4;
    grid[2][2] = 3;
    grid[2][3] = 1;
    grid[2][4] = 5;

    grid[3][0] = 4;
    grid[3][1] = 4;
    grid[3][2] = 2;
    grid[3][3] = 3;
    grid[3][4] = 3;

    grid[4][0] = 2;
    grid[4][1] = 1;
    grid[4][2] = 5;
    grid[4][3] = 4;
    grid[4][4] = 4;
    */
    return 0;
}
