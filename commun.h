#ifndef COMMUN_H
#define COMMUN_H

#define MAX_GHOSTS 6

typedef enum e_direction {
    FIXE=0,
    DROITE=1,
    GAUCHE=2,
    HAUT=4,
    BAS=8
} E_DIRECTIONS;

typedef struct s_jeu { // 16
    int nbGhosts;
    int maze_w, maze_h;
    int vitesse;
} T_JEU;

typedef struct s_pacman {   // 512+16 = 528
    int x,y,w,h;
    E_DIRECTIONS dirAsked;
    E_DIRECTIONS dir;
    char image_droite[256];
    char image_gauche[256];
} T_PACMAN;

typedef struct s_ghost {  // 320 * 6 = 1920
    int num;
    int x,y,w,h;
    char image[256];
    char comportement[48];
    E_DIRECTIONS dir;
} T_GHOST;

#endif // COMMUN_H
