#include <stdio.h>
#include <unistd.h>

#define MAXRINGS 3
#define SPACER 3
#define SP "     "

int moves = 0;
int a[MAXRINGS];
int b[MAXRINGS];
int c[MAXRINGS];

int getcell(int t[], int i) {
    if (i <= MAXRINGS) {
        return t[i - 1];
    }
    return -1;
}

void print_towers() {
    int i = MAXRINGS;

    moves += 1;
    printf("\033[%dAMove: %d\n\n", MAXRINGS + 7, moves);
    while (i > 0) {
         int cell_a = getcell(a, i);
        int cell_b = getcell(b, i);
        int cell_c = getcell(c, i);

        char char_a = (cell_a == -1) ? '|' : cell_a + '0';
        char char_b = (cell_b == -1) ? '|' : cell_b + '0';
        char char_c = (cell_c == -1) ? '|' : cell_c + '0';

        printf("%*c%*c%*c\n", SPACER, char_a, SPACER, char_b, SPACER, char_c);
        i--;
    }
 for (int j = 0; j < SPACER * 2 + 3 * MAXRINGS; j++) {
        printf("-");
    }
    printf("\n");
    printf("%*c%*c%*c\n\n", SPACER, 'A', SPACER, 'B', SPACER, 'C');
}

void move(int n, int* ta, int* tb, int* tc) {
    usleep(1000000);
    if (n == 1) {
        int a_index = MAXRINGS - n;
        int b_index = MAXRINGS - n;
        if (tb[b_index] == 0) {
            tb[b_index] = ta[a_index];
            ta[a_index] = 0;
            print_towers();
        }
        return;
    }

    move(n - 1, ta, tc, tb);

    int a_index = MAXRINGS - n;
    int b_index = MAXRINGS - n;
    if (tb[b_index] == 0) {
        tb[b_index] = ta[a_index];
        ta[a_index] = 0;
        print_towers();
    }
    else {
        int i = b_index - 1;
        while (i >= 0 && tb[i] == 0) {
            tb[i] = ta[a_index];
            ta[a_index] = 0;
            a_index = i;
            i--;
            print_towers();
        }
    }

    move(n - 1, tc, tb, ta);
}

int main() {
       for (int i = 0; i < MAXRINGS; i++) {
        a[i] = MAXRINGS - i;
        b[i] = 0;
        c[i] = 0;
    }
     printf("\033c");

    print_towers();
    move(MAXRINGS, a, c, b);

    return 0;
}
