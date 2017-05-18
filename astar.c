#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define M 100
#define p 0.3

typedef struct cell {
    int x;
    int y;
    int up;
    int down;
    int left;
    int right;
    int type;
} cell;

typedef struct stack {
    struct cell;
    cell *mat[M];
    int top;
} stack;

void move(int x1, int y1, int x2, int y2, stack *s, cell **maze){
    printf("Sx: %d, Sy: %d\n", s->mat[s->top]->x, s->mat[s->top]->y);
    s->mat[s->top]->type = 8;
}

float weighted_manhattan(int x1, int y1, int x2, int y2){
    float d;
    d = abs(x1 - x2) + 0.5 * abs(y1 - y2);
    return d;
}

void print_maze(cell **maze){
    int i,j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            printf("%d ", maze[i][j].type);
        }
        printf("\n");
    }
}

int main(){
    int i, j;
    cell **maze;
    double r;
    maze = (cell **) malloc(N * sizeof(cell *));
    for (i = 0; i < N; i++){
        maze[i] = (cell *) malloc(N * sizeof(cell));
    }
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            maze[i][j].x = i;
            maze[i][j].y = j;
            r = (rand() % 100) / 100.0;
            if (r < p){
                maze[i][j].type = 1; //set obstacle
                maze[i][j].up = 0; //0 means that it hasn't been visited
                maze[i][j].down = 0;
                maze[i][j].right = 0;
                maze[i][j].left = 0;
                if (i == 0){            //set the walls of the maze
                    maze[i][j].up = 1;
                }
                if (i == (N - 1)){
                    maze[i][j].down = 1;
                }
                if (j == 0){
                    maze[i][j].left = 1;
                }
                if (j == (N - 1)){
                    maze[i][j].right = 1;
                }
            } else {
                maze[i][j].type = 0;
                maze[i][j].up = 0;
                maze[i][j].down = 0;
                maze[i][j].right = 0;
                maze[i][j].left = 0;
                if (i == 0){            //set the walls of the maze
                    maze[i][j].up = 1;
                }
                if (i == (N - 1)){
                    maze[i][j].down = 1;
                }
                if (j == 0){
                    maze[i][j].left = 1;
                }
                if (j == (N - 1)){
                    maze[i][j].right = 1;
                }
            }
        }
    }

    int Sx;
    int Sy;
    int G1x;
    int G1y;
    int G2x;
    int G2y;
    int valid = 1;

    while (valid){
        printf("Give Sx: ");
        scanf("%d", &Sx);
        printf("\n");

        printf("Give Sy: ");
        scanf("%d", &Sy);
        printf("\n");

        if (maze[Sx][Sy].type == 0){
            printf("Valid starting point...\n");
            valid = 0;
        } else {
            printf("Not valid starting point, choose coordinates again\n");
        }
    }

    valid = 1;
    while (valid){
        printf("Give G1x: ");
        scanf("%d", &G1x);
        printf("\n");

        printf("Give G1y: ");
        scanf("%d", &G1y);
        printf("\n");

        if (maze[G1x][G1y].type == 0){
            printf("Valid G1 point...\n");
            valid = 0;
        } else {
            printf("Not valid G1 point, choose coordinates again\n");
        }
    }

    valid = 1;
    while (valid){
        printf("Give G2x: ");
        scanf("%d", &G2x);
        printf("\n");

        printf("Give G2y: ");
        scanf("%d", &G2y);
        printf("\n");

        if (maze[G2x][G2y].type == 0){
            printf("Valid G2 point...\n");
            valid = 0;
        } else {
            printf("Not valid G2 point, choose coordinates again\n");
        }
    }

    stack st;
    st.top = 0;
    st.mat[st.top] = &maze[Sx][Sy];
//    maze[G1x][G1y].type = 5;

    print_maze(maze);


//    printf("\n%f\n", weighted_manhattan(Sx, Sy, G1x, G1y));
    if (weighted_manhattan(Sx, Sy, G1x, G1y) <= weighted_manhattan(Sx, Sy, G2x, G2y)){
        //select G1, it is closer to S
        move(Sx, Sy, G1x, G1y, &st, maze);
    } else {
        //select G2, it is closer to S
        move(Sx, Sy, G2x, G2y, &st, maze);
    }

    print_maze(maze);

    return 0;
}
