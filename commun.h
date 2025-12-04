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

typedef struct s_pacman {
    int x,y,w,h;
} T_PACMAN;

typedef struct s_ghost {
    int x,y,w,h;
} T_GHOST;

#endif // COMMUN_H
