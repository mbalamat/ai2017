#include <stdio.h>
#include <stdlib.h>
#define N 5

int check_neighbors(int **grid, int i, int j){
    if (i == 0){
        if (j == 0){
            if (grid[i][j + 1] == 0){
                return 0;
            }
            if (grid[i + 1][j] == 0){
                return 0;
            }
        } else if (j == (N - 1)){
           if (grid[i][j - 1] == 0){
                return 0;
           }
           if (grid[i + 1][j] == 0){
                return 0;
           }
        } else {
            if (grid[i][j + 1] == 0 || grid[i][j - 1] == 0 || grid[i + 1][j] == 0){
                return 0;
            }
        }
    } else if (i == (N - 1)){
        if (j == 0){
            if (grid[i][j + 1] == 0){
                return 0;
            }
            if (grid[i - 1][j] == 0){
                return 0;
            }
        } else if (j == (N - 1)){
           if (grid[i][j - 1] == 0){
                return 0;
           }
           if (grid[i - 1][j] == 0){
                return 0;
           }
        } else {
            if (grid[i][j + 1] == 0 || grid[i][j - 1] == 0 || grid[i - 1][j] == 0){
                return 0;
            }
        }
    } else if (j == 0) {
        if (i != 0 && i != (N - 1)){
            if (grid[i - 1][j] == 0 || grid[i + 1][j] == 0 || grid[i][j + 1] == 0){
                return 0;
            }
        }
    } else if (j == (N - 1)){
        if (i != 0 && i != (N - 1)){
            if (grid[i - 1][j] == 0 || grid[i + 1][j] == 0 || grid[i][j - 1] == 0){
                return 0;
            }
        }
    } else if (i != 0 && i != (N - 1) && j != 0 && j != (N - 1)) {
        if (grid[i][j - 1] == 0 || grid[i][j + 1] == 0 || grid[i - 1][j] == 0 || grid[i + 1][j] == 0){
            return 0;
        }

    } else {
        return 1;
    }
    return 1;
}

void hitori(int **grid, int w, int z){
    int cx = 0, cy = 0, i, counter = 0;
    for (i = 0; i < N; i++){
        if (grid[w][i] == grid[w][z]){
            cy++;
        }
    }
    for (i = 0; i < N; i++){
        if (grid[i][z] == grid[w][z]){
            cx++;
        }
    }
    //cx = cx - 1;
    //cy = cy - 1;
    counter = cx + cy - 2;
    /*
    if (cx != 0){
        if (check_neighbors(grid, w, z)){
            grid[w][z] = 0;
        }
    }
    if (cy != 0){
        if (check_neighbors(grid, w, z)){
            grid[w][z] = 0;
        }
    }
    */
    if (counter != 0 && check_neighbors(grid, w, z) == 1){
        grid[w][z] = 0;
    }
}

int play(int **grid){
    int i, j;
    for (j = 0; j < N; j++){
        for (i = 0; i < N; i++){
            hitori(grid, i, j);
            //print_grid(grid);
        }
    }
    return 1;
}

void print_grid(int **grid){
    int i,j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            printf("%d  ", grid[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int **grid;
    grid = (int **) malloc(N * sizeof(int *));
    int i, j;
    for (i = 0; i < N; i++){
        grid[i] = (int *) malloc(N * sizeof(int));
    }

    /*
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            grid[i][j] = (rand() % (N - 2)) + 1;
        }
    }
    */

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

    print_grid(grid);
    play(grid);
    printf("\n\n");
    print_grid(grid);
    return 0;
}
