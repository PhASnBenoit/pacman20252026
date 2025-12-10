#ifndef COMMUN_H
#define COMMUN_H

#define MAX_GHOSTS 6

typedef enum e_direction {
    FIXE=0,
    DROITE=1,
    GAUCHE=2,
    HAUT=4,
    BAS=8
} E_DIRS;

typedef struct s_jeu {
    int nbGhosts;
    int maze_w, maze_h;
    int vitesse;
} T_JEU;

typedef struct s_pacman {
    int x,y,w,h;
    E_DIRS dirAsked;
    E_DIRS dir;
    char image_droite[256];
    char image_gauche[256];
} T_PACMAN;

typedef struct s_ghost {
    int num;
    int x,y,w,h;
    char image[256];
    char comportement[48];
    E_DIRS dir;
} T_GHOST;

#endif // COMMUN_H
