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
    
    return 0;
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


void separateNumbers(int arr[], int size) {
    int i, j, temp;
    
    // Traverse the array from left to right
    for (i = 0; i < size; i++) {
        // If the current element is 0, swap it with the element at the beginning
        if (arr[i] == 0) {
            temp = arr[i];
            arr[i] = arr[0];
            arr[0] = temp;
        }
    }
    
    // Traverse the array from right to left
    for (i = size - 1; i >= 0; i--) {
        // If the current element is greater than 0, swap it with the element at the end
        if (arr[i] > 0) {
            temp = arr[i];
            for (j = i; j < size - 1; j++) {
                arr[j] = arr[j + 1];
            }
            arr[size - 1] = temp;
        }
    }
}

void
move(int n, int* ta, int* tb, int* tc) {
    
    usleep(1000000);
    if (n == 1) {    
            tb[MAXRINGS - n] = ta[MAXRINGS - n];
            ta[MAXRINGS - n] = 0;
            print_towers();
        return;
    }
    
    move(n - 1, ta, tc, tb);
        tb[MAXRINGS - n] = ta[MAXRINGS - n];
        ta[MAXRINGS - n] = 0;
        print_towers();
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
