#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<string.h>

#define MAX 2000
#define ECHANTILLON_MAX 100
#define DX1 11
#define DY1 3
#define DX2 24
#define DY2 10
typedef unsigned char uchar;
typedef unsigned char monplan [MAX][MAX];



void affiche (int sizex, int sizey, monplan pl) {
    int i, j;
    for(j = sizey; j >= 0; j--) {
        for (i = 0; i <= sizex; i++)
            printf("%c", pl[i][j]);
        printf("\n");
  }
}

int droitesIdentiques(int sizex, int sizey, monplan pl1, monplan pl2) {
    int i, j;
    for (j = sizey; j >= 0; j--) {
        for (i = 0; i <= sizex; i++) {
            if (pl1[i][j] != pl2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

void testDroite(const char *nom_algo, void (*fonction)(int, int, monplan), int x, int y, monplan plan) {
    memset(plan, ' ', MAX * MAX);

    printf("%s (%d, %d)\n", nom_algo, x, y);
    fonction(x, y, plan);
    affiche(x, y, plan);

    printf("\n \n");
}

void comparerDroites(int x, int y, monplan plan1, monplan plan2) {
    droitesIdentiques(x, y, plan1, plan2) ? printf("Les droites sont identiques\n") : printf("Les droites ne sont pas identiques\n");
    printf("\n \n");
}

double testerAlgorithme(void (*fonction)(int, int), int DX, int DY) {
    struct timespec td, ta;
    int i;

    clock_gettime(CLOCK_MONOTONIC, &td);
    for (i = 0; i < ECHANTILLON_MAX; i++) {
        fonction(DX, DY);
    }
    clock_gettime(CLOCK_MONOTONIC, &ta);

    double elapsed_time = (ta.tv_sec - td.tv_sec) * 1e6 + (ta.tv_nsec - td.tv_nsec) / 1e3;
    
    return elapsed_time;
    
}


void droite_br(int dx, int dy){

    int delta, incH, incO;
    incH = - dy - dy;
    delta = incH + dx;
    incO = delta + dx;
    for(int x = 0, y = 0; x <= dx; x++){
        // affiche(x, y, pl);
        if(delta < 0){
            y++;
            delta += incO;
        }
        else delta += incH;
    }
}

// Fonction qui permet d'afficher le résultat obtenu dans le plan pl.
void droite_br_verif (int dx, int dy, monplan pl) {
    int x, y;
    
    int delta, incH, incO;
    incH = - dy - dy;
    delta = incH + dx;
    incO = delta + dx;
    for(x = 0, y = 0; x <= dx; x++){
        pl [x][y] = '.';
        if(delta <= 0){
            y++;
            delta += incO;
        }
        else
            delta += incH;
    }
}

// Pas de 2

void droite_rww(int dx, int dy) {
    int incr1, incr2, D, x, y, xend, c, parity;

    x = 0;
    y = 0;

    parity = dx & 1;
    if (parity == 0) {
        xend = dx;
    } else {
        xend = dx - 1;
    }

    incr2 = 4 * dy - 2 * dx;

    if (incr2 < 0) {
        c = 2 * dy;
        incr1 = 2 * c;
        D = incr1 - dx;
        while (x != xend) {
            if (D < 0) { // pattern 1
                x++;
                x++;
                D += incr1;
            } else {
                if (D < c) {  // pattern 2
                    x++;
                    x++;
                    y++;
                } else { // pattern 3
                    x++;
                    y++;
                    x++;
                }
                D += incr2;
            }
        }
    } else {
        c = 2 * (dy - dx);
        incr1 = 2 * c;
        D = incr1 + dx;
        while (x != xend) {
            if (D >= 0) { // pattern 4
                x++;
                y++;
                x++;
                y++;
                D += incr1;
            } else {
                if (D < c) { // pattern 2
                    x++;
                    x++;
                    y++;
                } else { // pattern 3
                    x++;
                    y++;
                    x++;
                }
                D += incr2;
            }
        }
    }
    
    if (parity == 1) {
    }
}

void droite_rww_verif(int dx, int dy, monplan pl) {
    int incr1, incr2, D, x, y, xend, c, parity;


    x = 0;
    y = 0;

    parity = dx & 1;
    if (parity == 0) {
        xend = dx;
    } else {
        xend = dx - 1;
    }

    pl [x][y] = '.';
    incr2 = 4 * dy - 2 * dx;

    if (incr2 < 0) {
        c = 2 * dy;
        incr1 = 2 * c;
        D = incr1 - dx;
        while (x != xend) {
            if (D < 0) { // pattern 1
                x++;
                pl [x][y] = '.';
                x++;
                pl [x][y] = '.';
                D += incr1;
            } else {
                if (D < c) {  // pattern 2
                    x++;
                    pl [x][y] = '.';
                    x++;
                    y++;
                    pl [x][y] = '.';
                } else { // pattern 3
                    x++;
                    y++;
                    pl [x][y] = '.';
                    x++;
                    pl [x][y] = '.';
                }
                D += incr2;
            }
        }
    } else {
        c = 2 * (dy - dx);
        incr1 = 2 * c;
        D = incr1 + dx;
        while (x != xend) {
            if (D >= 0) { // pattern 4
                x++;
                y++;
                pl [x][y] = '.';
                x++;
                y++;
                pl [x][y] = '.';
                D += incr1;
            } else {
                if (D < c) { // pattern 2
                    x++;
                    pl [x][y] = '.';
                    x++;
                    y++;
                    pl [x][y] = '.';
                } else { // pattern 3
                    x++;
                    y++;
                    pl [x][y] = '.';
                    x++;
                    pl [x][y] = '.';
                }
                D += incr2;
            }
        }
    }
    
    if (parity == 1) {
        pl [dx][dy] = '.';
    }
}

// Pas de 3

void droite_gi_verif(int a2, int b2, monplan pl) {
    int dx, dy, incr1, incr2, incr3, D, x, y, xend, c;

    dx = a2 - 0;
    dy = b2 - 0;
    x = 0;
    y = 0;

    xend = a2 - 1;
    

    pl [x][y] = '.';
    incr2 = 4 * dy - 2 * dx;

    if (incr2 <= 0) {
        c = 2 * dy;
        incr1 = 2 * c;
        incr3 = incr2 + c;
        D = incr1 - dx;
        while (x < xend) {
            if (D < 0) { // pattern 1
                x++;
                pl [x][y] = '.';
                x++;
                pl [x][y] = '.';
                D += incr1;
            } 
            else if (D >= c) {  // pattern 3
                    x++;
                    y++;
                    pl [x][y] = '.';
                    x++;
                    pl [x][y] = '.';
                    D += incr2;
            } 
            else { // pattern 5
                    x++;
                    pl [x][y] = '.';
                    x++;
                    y++;
                    pl [x][y] = '.';
                    x++;
                    pl [x][y] = '.';
                    D += incr3;
                }
            
        }
    } else {
        c = 2 * (dy - dx);
        incr1 = 2 * c;
        incr3 = incr2 + c;
        D = incr1 + dx;
        while (x < xend) {
            if (D >= 0) { // pattern 4
                x++;
                y++;
                pl [x][y] = '.';
                x++;
                y++;
                pl [x][y] = '.';
                D += incr1;
            } 
            else if (D < c) { // pattern 2
                    x++;
                    pl [x][y] = '.';
                    x++;
                    y++;
                    pl [x][y] = '.';
                    D += incr2;
            } 
            else { // pattern 6
                    x++;
                    y++;
                    pl [x][y] = '.';
                    x++;
                    pl [x][y] = '.';
                    x++;
                    y++;
                    pl [x][y] = '.';
                    D += incr3;
                }
            
        }
    }
    
    if (x < a2) {
        pl [a2][b2] = '.';
    }
}

void droite_gi(int dx, int dy) {
    int incr1, incr2, incr3, D, x, y, xend, c;

    x = 0;
    y = 0;

    xend = dx - 1;
    
    incr2 = 4 * dy - 2 * dx;

    if (incr2 <= 0) {
        c = 2 * dy;
        incr1 = 2 * c;
        incr3 = incr2 + c;
        D = incr1 - dx;
        while (x < xend) {
            if (D < 0) { // pattern 1
                x++;
                x++;
                D += incr1;
            } 
            else if (D >= c) {  // pattern 3
                    x++;
                    y++;
                    x++;
                    D += incr2;
            }
            else { // pattern 5
                    x++;
                    x++;
                    y++;
                    x++;
                    D += incr3;
                }
            
        }
    } else {
        c = 2 * (dy - dx);
        incr1 = 2 * c;
        incr3 = incr2 + c;
        D = incr1 + dx;
        while (x < xend) {
            if (D >= 0) { // pattern 4
                x++;
                y++;
                x++;
                y++;
                D += incr1;
            } 
            else if (D < c) { // pattern 2
                    x++;
                    x++;
                    y++;
                    D += incr2;
            } 
            else { // pattern 6
                    x++;
                    y++;
                    x++;
                    x++;
                    y++;
                    D += incr3;
                }
            }
        }
    
    
    if (x < dx) {
    }
}

int main (int argc, char ** argv) {

    int DX = 100;
    int DY = 0;
    
    if (argc == 3){
        DX = atoi (argv[1]);
        DY = atoi (argv[2]);
    }
    monplan plan;
    monplan plan2;

    /* Test des fonctions */

    testDroite("Bresenham", droite_br_verif, DX1, DY1, plan);
    testDroite("Rokne, Wyvill & Wu", droite_rww_verif, DX1, DY1, plan2);
    comparerDroites(DX1, DY1, plan, plan2);

    testDroite("Graham, Iyengar", droite_gi_verif, DX1, DY1, plan);
    comparerDroites(DX1, DY1, plan, plan2);

    testDroite("Bresenham", droite_br_verif, DX2, DY2, plan);
    testDroite("Rokne, Wyvill & Wu", droite_rww_verif, DX2, DY2, plan2);
    comparerDroites(DX2, DY2, plan, plan2);

    testDroite("Graham, Iyengar", droite_gi_verif, DX2, DY2, plan);
    comparerDroites(DX2, DY2, plan, plan2);

    double br = testerAlgorithme(droite_br, DX, DY);
    double rww = testerAlgorithme(droite_rww, DX, DY);
    double gi = testerAlgorithme(droite_gi, DX, DY);

    // Éviter les valeurs négatives

    while((1 - gi / br) * 100 < 0 || (1 - rww / br) * 100 < 0 || (1 - gi / rww) * 100 < 0){
        br = testerAlgorithme(droite_br, DX, DY);
        rww = testerAlgorithme(droite_rww, DX, DY);
        gi = testerAlgorithme(droite_gi, DX, DY);
    }
    printf("\nDroite (%d, %d) sur %d itérations (en µs):\n\n\n", DX, DY, ECHANTILLON_MAX);

    printf("Bresenham (B5) : %.2f\n", br);
    printf("Rokne, Wyvill & Wu (P2) : %.2f\n", rww);
    printf("Graham, Iyengar (P3) : %.2f\n\n", gi);

    printf("Réduction P3 par rapport à B5 : %.2f %%\n", (1 - gi / br) * 100);
    printf("Réduction P3 par rapport au P2 : %.2f %%\n\n", (1 - gi / rww) * 100);

    return 0; 

}

