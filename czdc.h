#ifndef CZDC_H
#define CZDC_H

#include <QSharedMemory>
#include <QObject>
#include "commun.h"

#define MAX_GHOSTS 6
typedef struct s_zdc {
    T_GENERAL general;
    T_PACMAN pacman;
    T_GHOST ghosts[MAX_GHOSTS];
} T_ZDC;

class CZDC : public QSharedMemory
{
    Q_OBJECT
public:
    CZDC();
    ~CZDC();
    void clear();
    T_PACMAN getPacman();
    T_GHOST getGhostNb(int nb);
    T_GENERAL getGeneral();
    void setPacman(T_PACMAN pac);
    void setGhostNb(int nb, T_GHOST ghost);
    void setGeneral(T_GENERAL gen);
    int init();

private:
    T_ZDC *_data;

signals:
    void sig_erreur(int err);
};

#endif // CZDC_H
