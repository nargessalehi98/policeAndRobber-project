#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

const int y = 11, x = 20, nos = 3, noo = 2;
int A[x][y];
int Tx, Ty, Px, Py, Ta, Tb, Pa, Pb, tempx, tempy;

void matrix() {
    for (int j = 0; j < y; j++)
        for (int i = 0; i < x; i++)
            A[i][j] = 0;
}

int print() {
    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            if (A[i][j] == 0)
                printf("|     ");
            else if (A[i][j] == -1)
                printf("|  T  ");
            else if (A[i][j] == -2)
                printf("|Dead!");
            else
                printf("|  D%d ", A[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

void first_pos() {
    srand(time(NULL));
    Tx = rand() % x;   //first position of thief
    Ty = rand() % y;   //first position of thief
    A[Tx][Ty] = -1;
    for (int i = 0; i < nos; i++) {
        for (int j = 0; j < noo; j++) {
            Px = 0;
            Py = 0;
            Px = rand() % x;   //first position of police
            Py = rand() % y;   //first position of police
            while (1) {
                if (A[Px][Py] == 0) {
                    A[Px][Py] = i+1;
                    break;
                } else {
                    Px = 0;
                    Py = 0;
                    Px = rand() % x;   //first position of police
                    Py = rand() % y;  //first position of police
                }
            }
        }
    }
}

void thief_move() {
    A[Tx][Ty] = 0;
    int hold1=Tx;
    int hold2=Ty;
    Ta = rand() % 3 - 1;
    Tb = rand() % 3 - 1;
    Tx = Tx + Ta;
    Ty = Ty + Tb;
    if ((Tx < x && Tx >= 0) && (Ty >= 0 && Ty < y)) {
        if (A[Tx][Ty] > 0) {
            A[Tx][Ty] = -2;
        } else {
            A[Tx][Ty] = -1;
        }
    } else {
        Tx=hold1;
        Ty=hold2;
        thief_move();
    }
}

int police_check(int m) {
    tempx = 0;
    tempy = 0;
    for (int k = 0; k < y; k++) {
        for (int l = 0; l < x; l++) {
            if (A[l][k] == m && (sqrt(pow(l - Tx, 2) + pow(k - Ty, 2))) <= 2.9) {
                tempx = l - Tx;
                tempy = k - Ty;
                return 1;
            }
        }
    }
    return 0;
}

void police_move() {
    int AB[x][y];
    for (int k = 0; k < y; k++) {
        for (int l = 0; l < x; l++) {
            AB[l][k] = A[l][k];
        }
    }
    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            if (AB[i][j] > 0) {
                while (1) {
                    if ((sqrt(pow(i - Tx, 2) + pow(j - Ty, 2))) <= 2.9) {
                        tempx = i - Tx;
                        tempy = j - Ty;
                        //printf("if\n");
                        if (tempx < 0) {
                            Pa = 1;
                        } else if (tempx > 0) {
                            Pa = -1;
                        } else {
                            Pa = 0;
                        }
                        if (tempy < 0) {
                            Pb = 1;
                        } else if (tempy > 0) {
                            Pb = -1;
                        } else {
                            Pb = 0;
                        }

                    } else {
                        Pa = rand() % 3 - 1;
                        Pb = rand() % 3 - 1;
                    }
                    if ( i + Pa >= 0 && i + Pa < x && j + Pb >= 0 && j + Pb < y) {
                        //printf("if2\n");
                        if(A[i + Pa][j + Pb] <= 0 ){
                            int flag = 0;
                            if (A[i + Pa][j + Pb] < 0) {
                                flag = 1;
                            }
                            int hold;
                            hold = A[i][j];
                            A[i][j] = 0;
                            A[i + Pa][j + Pb] = hold;
                            if (flag == 1) {
                                A[i + Pa][j + Pb] = -2;
                            }
                            break;
                        }

                    }
                }

            }

        }
    }

}

int main() {
    matrix();
    first_pos();
    print();
    while (1) {
        thief_move();
        sleep(1);
        police_move();
        for (int j = 0; j < y; j++) {
            for (int i = 0; i < x; i++) {
                if (A[i][j] == -2) {
                    print();
                    return 0;
                }
            }
        }
        print();
    }
}



