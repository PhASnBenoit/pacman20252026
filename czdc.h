#ifndef CZDC_H
#define CZDC_H

#include <QSharedMemory>
#include <QObject>
#include "commun.h"
#include "csettings.h"

#define MAX_GHOST 5

typedef struct s_zdc {
    int nb_ghosts;
    T_PACMAN pacman;
    T_GHOST ghosts[MAX_GHOST];
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
    void setPacman(T_PACMAN pac);
    void setGhostNb(int nb, T_GHOST ghost);
    int init();

private:
    T_ZDC *_data;
    CSettings _settings;

signals:
    void sig_erreur(int err);
};

#endif // CZDC_H
