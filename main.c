#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

//braye n>m javab nmidahad
////be ezaye x = 7 tx ra hamash 3 midahad what the shit!!!!!
const int y = 9, x = 11, nos = 3, noo = 3;
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
            else if (A[i][j] == -2)
                printf("|Dead!");
            else if (A[i][j] == -1)
                printf("|  T  ");
            else
                printf("|  D%d ", A[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

// eshqal nashode vali else mikhanad
void first_pos() {
    Tx = 0;
    Ty = 0;
    //printf("Tx=%d,Ty=%d\n", Tx, Ty);
    srand(time(NULL));
    Tx = rand() % x;   //first position of thief
    Ty = rand() % y;   //first position of thief
    A[Tx][Ty] = -1;
    //printf("Tx=%d,Ty=%d\n", Tx, Ty);
    for (int i = 1; i <= nos; i++) {
        //printf("nos=%d\n", i);
        for (int j = 0; j < noo; j++) {
            Px = 0;
            Py = 0;
            Px = rand() % x;   //first position of police
            Py = rand() % y;   //first position of police
            //printf("Px=%d,Py=%d\n", Px, Py);
            while (1) {
                if (A[Px][Py] == 0) {
                    A[Px][Py] = i;
                    break;
                } else {
                    Px = 0;
                    Py = 0;
                    Px = rand() % x;   //first position of police
                    Py = rand() % y;  //first position of police
                    //printf("else Px=%d,Py=%d\n", Px, Py);
                }
            }
        }

    }
}

void random_move() {
    int temp1 = 0;
    int temp2 = 0;
    temp1 = (rand() % 3);   //move
    temp2 = (rand() % 3);   //move
    if (temp1 == 0)
        Ta = 0;
    if (temp1 == 1)
        Ta = 1;
    if (temp1 == 2)
        Ta = -1;
    if (temp2 == 0)
        Tb = 0;
    if (temp2 == 1)
        Tb = 1;
    if (temp2 == 2)
        Tb = -1;
    //printf("ym=%d,xm=%d\n", Tb, Ta);
}

void thief_move() {
    A[Tx][Ty] = 0;
    random_move();
    Tx = Tx + Ta;
    Ty = Ty + Tb;
    while (1) {
        if ((Tx < x && Tx >= 0) && (Ty >= 0 && Ty < y) && (A[Tx][Ty] == 0)) {
            A[Tx][Ty] = -1;
            break;
        } else {
            Tx = Tx - Ta;
            Ty = Ty - Tb;
            random_move();
            Tx = Tx + Ta;
            Ty = Ty + Tb;
            //printf("ym=%d,xm=%d\n", Tb, Ta);
        }
    }
}

int police_check() {
    tempx = 0;
    tempy = 0;
    if ((sqrt(pow(Px - Tx, 2) + pow(Py - Ty, 2))) <= 2.9) {
        tempx = Px - Tx;
        tempy = Py - Ty;
        return 1;
    }
    return 0;
}

void follow_thief() {
    if (tempx == 0)
        Pa = 0;
    else if (tempx == 1 || tempx == 2)
        Pa = -1;
    else if (tempx == -1 || tempx == -2)
        Pa = 1;
    if (tempy == 0)
        Pa = 0;
    else if (tempy == 1 || tempy == 2)
        Pa = -1;
    else if (tempy == -1 || tempy == -2)
        Pa = 1;
}
// if (A[i][j] != 0 && A[i][j] != -1)
//bishtar chap mikonad

int police_move() {
    for (int k = 1; k <= nos; k++) {
        for (int j = 0; j < y; j++) {
            for (int i = 0; i < x; i++) {
                if (A[i][j] == k) {
                    Px = i;
                    Py = j;
                    if (police_check()) {
                        follow_thief();
                    } else
                        random_move();
                    Px = Px + Pa;
                    Py = Py + Pb;
                    while (1) {
                        if ((Px < x && Px >= 0) && (Py >= 0 && Py < y)) {
                            if (A[Px][Py] == -1) {
                                A[Px][Py] = -2;
                                //printf("where\n");
                                //print();
                                //return 0;
                            } else {
                                A[Px][Py] = k;
                                break;
                            }
                        } else {
                            Px = Px - Pa;
                            Py = Py - Pb;
                            if (police_check()) {
                                follow_thief();
                            } else
                                random_move();
                            Px = Px + Pa;
                            Py = Py + Pb;
                        }
                    }
                    A[Px - Pa][Py - Pb] = 0;
                }
            }
        }
    }
    return 1;
}


int main() {
    matrix();
    first_pos();
    print();
    sleep(1);
    while (1) {
        thief_move();
        print();
        sleep(1);
        police_move();
        sleep(1);
        print();
        for (int j = 0; j < y; j++) {
            for (int i = 0; i < x; i++) {
                if (A[i][j] = -2) {
                    printf("\nThe police went to the thief !\n");
                    return 0;
                }
            }
        }
    }
}






//printf("Please tell me size of town like X x Y:");
//scanf("%d%d",&x,&y);
//printf("Please tell me number of town police stations :");
//scanf("%d",&nos);
//printf("please tell me number of station officer : ");
//scanf("%d",&noo);
//printf("Ready !");
//sleep(1);



