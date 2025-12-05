#ifndef COMMUN_H
#define COMMUN_H

#define KEY "pacman20252026"

typedef enum e_direction {
    FIXE=0,
    DROITE=1,
    GAUCHE=2,
    HAUT=4,
    BAS=8
} T_DIRECTION;

typedef struct s_general {
    int nbGhosts;
    int maze_w, maze_h;
    int vitesse;
} T_GENERAL;

typedef struct s_pacman {
    int x,y,w,h;
    char image_droite[255];
    char image_gauche[255];
} T_PACMAN;

typedef struct s_ghost {
    int x,y,w,h;
    char image[255];
    char comportement[50];
} T_GHOST;

#endif // COMMUN_H
