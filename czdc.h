#ifndef CZDC_H
#define CZDC_H

#include <QSharedMemory>
#include <QObject>
#include <QDebug>
#include "commun.h"

#define KEY "pacman"

typedef struct s_zdc {
    T_JEU jeu;
    T_PACMAN pacman;
    T_GHOST ghosts[MAX_GHOSTS];
} T_ZDC;

class CZDC : public QSharedMemory
{
    Q_OBJECT
public:
    CZDC();
    ~CZDC();
    T_PACMAN getPacman();
    T_GHOST getGhostNo(int no);
    T_JEU getJeu();
    QList<int> getXYTousLesGhosts();
    void setPacman(T_PACMAN pac);
    void setGhostNo(int no, T_GHOST ghost);
    void setJeu(T_JEU jeu);
    int init(bool capp);
    void setDirAskedPacman(E_DIRS dir);

private:
    T_ZDC *_data;

signals:
    void sig_erreur(QString err);
};

#endif // CZDC_H
