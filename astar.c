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
    int visited;
} cell;

typedef struct stack {
    struct cell;
    cell *mat[M];
    int top;
} stack;

float weighted_manhattan(int x1, int y1, int x2, int y2){
    float d;
    d = abs(x1 - x2) + 0.5 * abs(y1 - y2);
    return d;
}

int calculate_direction_based_on_en(int target_x, int target_y, stack *s, cell **maze, float *gn, int selector){
    float en_left = 5555.0, en_right = 5555.0, en_up = 5555.0, en_down = 5555.0;
    float values[4];
    int keys[4];

    if (s->mat[s->top]->y - 1 > 0){
        printf("y= %d\n", s->mat[s->top]->y);
        if (maze[s->mat[s->top]->x][((s->mat[s->top]->y) - 1)].type != 1 ) {
            en_left = *gn + weighted_manhattan(s->mat[s->top]->x, ((s->mat[s->top]->y) - 1), target_x, target_y);
        }
    }

    if (s->mat[s->top]->y + 1 < N){
        if (maze[s->mat[s->top]->x][((s->mat[s->top]->y) + 1)].type != 1 ){
                en_right = *gn + weighted_manhattan(s->mat[s->top]->x, ((s->mat[s->top]->y) + 1), target_x, target_y);
        }
    }

    if (s->mat[s->top]->x - 1 > 0){
        if (maze[((s->mat[s->top]->x) - 1)][s->mat[s->top]->y].type != 1){
            en_up = *gn + weighted_manhattan(((s->mat[s->top]->x) - 1), s->mat[s->top]->y, target_x, target_y);
        }
    }

    if (s->mat[s->top]->x + 1 < N){
        if (maze[((s->mat[s->top]->x) + 1)][s->mat[s->top]->y].type != 1){
            en_down = *gn + weighted_manhattan(((s->mat[s->top]->x) + 1), s->mat[s->top]->y, target_x, target_y);
        }
    }

    float min = 100000.0;
    int direction = 0;
    int temp_int;
    float temp_float;

    values[0] = en_up;
    values[1] = en_right;
    values[2] = en_down;
    values[3] = en_left;

    keys[0] = 1;
    keys[1] = 2;
    keys[2] = 3;
    keys[3] = 4;
    int i, j;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3 - j; j++){
            if (values[j] > values[j + 1]){
                temp_float = values[j];
                temp_int = keys[j];
                values[j] = values[j + 1];
                keys[j] = keys[j + 1];
                values[j + 1] = temp_float;
                keys[j + 1] = temp_int;
            }
        }
    }

    if (selector == 0){
        if (values[selector] != 5555.0){
            direction = keys[selector];
        } else {
            calculate_direction_based_on_en(target_x, target_y, &(*s), maze, &(*gn), 1);
        }
    }
    if (selector == 1){
        if (values[selector] != 5555.0){
            direction = keys[selector];
        } else {
            calculate_direction_based_on_en(target_x, target_y, &(*s), maze, &(*gn), 2);
        }
    }
    if (selector == 2){
        if (values[selector] != 5555.0){
            direction = keys[selector];
        } else {
            calculate_direction_based_on_en(target_x, target_y, &(*s), maze, &(*gn), 3);
        }
    }
    if (selector == 3){
        if (values[selector] != 5555.0){
            direction = keys[selector];
        } else {
            calculate_direction_based_on_en(target_x, target_y, &(*s), maze, &(*gn), 4);
        }
    }
    if (selector == 4){
        direction = 0;
    }

    return direction;
}

void move(int target_x, int target_y, stack *s, cell **maze, float *gn, int selector, int *extensions){
    int direction;

    direction = calculate_direction_based_on_en(target_x, target_y, &(*s), maze, &(*gn), selector);

    if (direction == 0){
        if (s->top == 0){
            printf("No solution found!\n");
            exit(0);
        }
        if (s->mat[(s->top - 1)]->x == s->mat[s->top]->x){
            *gn -= 0.5;
        } else {
            *gn -= 1.0;
        }

        if ((s->mat[(s->top - 1)]->x - s->mat[s->top]->x) == 1 && s->mat[(s->top - 1)]->y == s->mat[s->top]->y) {
            s->mat[(s->top - 1)]->up = 1;
        }
        if ((s->mat[(s->top - 1)]->x - s->mat[s->top]->x) == -1 && s->mat[(s->top - 1)]->y == s->mat[s->top]->y) {
            s->mat[(s->top - 1)]->down = 1;
        }

        if ((s->mat[(s->top - 1)]->y - s->mat[s->top]->y) == -1 && s->mat[(s->top - 1)]->x == s->mat[s->top]->x) {
            s->mat[(s->top - 1)]->right = 1;
        }
        if ((s->mat[(s->top - 1)]->y - s->mat[s->top]->y) == 1 && s->mat[(s->top - 1)]->x == s->mat[s->top]->x) {
            s->mat[(s->top - 1)]->left = 1;
        }

        s->mat[s->top]->visited = 1;
        s->top -= 1;

        move(target_x, target_y, &(*s), maze, &(*gn), 0, &(*extensions));
    }

    if (direction == 1){
        s->mat[s->top + 1] = &maze[s->mat[s->top]->x - 1][s->mat[s->top]->y];
        s->top += 1;
        *gn += 1.0;
        *extensions += 1;
        if (s->mat[s->top]->x == target_x && s->mat[s->top]->y == target_y){
            return;
        }
        move(target_x, target_y, &(*s), maze, &(*gn), 0, &(*extensions));
    }
    if (direction == 2){
        s->mat[s->top + 1] = &maze[s->mat[s->top]->x][s->mat[s->top]->y + 1];
        s->top += 1;
        *gn += 0.5;
        *extensions += 1;
        if (s->mat[s->top]->x == target_x && s->mat[s->top]->y == target_y){
            return;
        }
        move(target_x, target_y, &(*s), maze, &(*gn), 0, &(*extensions));
    }
    if (direction == 3){
        s->mat[s->top + 1] = &maze[s->mat[s->top]->x + 1][s->mat[s->top]->y];
        s->top += 1;
        *gn += 1.0;
        *extensions += 1;
        if (s->mat[s->top]->x == target_x && s->mat[s->top]->y == target_y){
            return;
        }
        move(target_x, target_y, &(*s), maze, &(*gn), 0, &(*extensions));
    }
    if (direction == 4){
        s->mat[s->top + 1] = &maze[s->mat[s->top]->x][s->mat[s->top]->y - 1];
        s->top += 1;
        *gn += 0.5;
        *extensions += 1;
        if (s->mat[s->top]->x == target_x && s->mat[s->top]->y == target_y){
            return;
        }
        move(target_x, target_y, &(*s), maze, &(*gn), 0, &(*extensions));
    }
}

void print_maze(cell **maze){
    int i,j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            if (maze[i][j].visited == 0){
                printf("%d ", maze[i][j].type);
            } else {
                printf("%d ", 5); //printing the wrong path
            }
        }
        printf("\n");
    }
}

void print_stack(stack *s){
    int i;
    for (i = 0; i < s->top; i++){
        printf("The path found is: \n");
        printf("[%d, %d]\n", s->mat[i]->x, s->mat[i]->y);
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
                maze[i][j].visited = 0;
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
                maze[i][j].visited = 0;
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

    print_maze(maze);
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

    print_maze(maze);

    float gn = 0;
    float sum_gn = 0;
    int extensions = 0;
    if (weighted_manhattan(Sx, Sy, G1x, G1y) <= weighted_manhattan(Sx, Sy, G2x, G2y)){
        //select G1, it is closer to S
        move(G1x, G1y, &st, maze, &gn, 0, &extensions);
        print_stack(&st);
        sum_gn += gn;
        gn = 0;
        move(G2x, G2y, &st, maze, &gn, 0, &extensions);
    } else {
        //select G2, it is closer to S
        move(G2x, G2y, &st, maze, &gn, 0, &extensions);
        print_stack(&st);
        sum_gn += gn;
        gn = 0;
        move(G1x, G1y, &st, maze, &gn, 0, &extensions);
    }
    print_stack(&st);
    print_maze(maze);

    return 0;
}
