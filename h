#include <stdio.h>
#include <unistd.h>

#define MAXRINGS 5
#define SPACER 5
#define SP "     "

int moves = 0;
int a[MAXRINGS] = {5, 4, 3, 2, 1};
int b[MAXRINGS] = {};
int c[MAXRINGS] = {};

void print_towers() {
    int i = MAXRINGS;

    moves += 1;
    printf("\033[%dAMove: %d\n\n", MAXRINGS + 7, moves);
    while (i > 0) {
        printf("%*d%s%*d%s%*d\n", (int)(sizeof(a)/sizeof(a[0])), a[i-1], SP, (int)(sizeof(b)/sizeof(b[0])), b[i-1], SP, (int)(sizeof(c)/sizeof(c[0])), c[i-1]);
        i -= 1;
    }

    printf("--------------------------------------\n");
    printf("%*c%s%*c%s%*c\n\n", (int)(sizeof(a)/sizeof(a[0])), 'A', SP, (int)(sizeof(b)/sizeof(b[0])), 'B', SP, (int)(sizeof(c)/sizeof(c[0])), 'C');
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
    printf("\n\n\n\n\n\n\n\n");

    print_towers();
    move(MAXRINGS, a, c, b);

    return 0;
}
