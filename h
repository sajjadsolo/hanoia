#include <stdio.h>
#include <unistd.h>

#define MAXRINGS 3
#define SPACER 3
#define SP 3

int moves = 0;
int a[MAXRINGS];
int b[MAXRINGS];
int c[MAXRINGS];

int 
getcell(int *t, int i) {
    if (i <= MAXRINGS) {
        return t[i - 1];
    }
    
    return -1;
}

void 
print_towers() {
    int i = MAXRINGS;

    moves ++;
    printf("\033[%dAMove: %d\n\n", MAXRINGS + 7, moves);
    while (i > 0) {
        int cella = getcell(a, i);
        int cellb = getcell(b, i);
        int cellc = getcell(c, i);

        printf("%*d%*d%*d\n", SPACER, cella, SPACER, cellb, SPACER, cellc);
        i--;
    }
 for (int j = 0; j < SPACER * 2 + 3 * MAXRINGS; j++) {
        printf("-");
    }
    printf("\n");
    printf("%*c%*c%*c\n\n", SPACER, 'A', SPACER, 'B', SPACER, 'C');
}

void
move(int n, int* ta, int* tb, int* tc) {
    int aindex = MAXRINGS - n;
    int bindex = MAXRINGS - n;
    
    usleep(1000000);
    if (n == 1) {    
        if (tb[bindex] == 0) {
            tb[bindex] = ta[aindex];
            ta[aindex] = 0;
            print_towers();
        }
        return;
    }
    
    move(n - 1, ta, tc, tb);
    if (tb[bindex] == 0) {
        tb[bindex] = ta[aindex];
        ta[aindex] = 0;
        print_towers();
    }
    else {
        int i = bindex - 1;
        while (i >= 0 && tb[i] == 0) {
            tb[i] = ta[aindex];
            ta[aindex] = 0;
            aindex = i;
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
