#include "cghost.h"

CGhost::CGhost(int no, QObject *parent)
    : CPersonnage{parent}
{
    _num = no;
    connect(_zdc, &CZDC::sig_erreur, this, &CGhost::on_sig_erreurFromZDC);
    connect(this, &CGhost::sig_refresh, this, &CGhost::on_go);
}

CGhost::~CGhost()
{
}

E_DIRS CGhost::getRandomDirection()
{
    int value = QRandomGenerator::global()->bounded(4);
    return (E_DIRS)(1<<value);
}

void CGhost::on_go()
{
    int possibleDirs;
    E_DIRS dir;
    T_GHOST ghost = _zdc->getGhostNo(_num);
    T_JEU jeu = _zdc->getJeu();
    possibleDirs = getDirs(ghost.x, ghost.y, ghost.w, ghost.h); // dirs possible
    switch (ghost.dir) {
        case FIXE:break;
        case DROITE: possibleDirs &= ~GAUCHE; break;
        case GAUCHE: possibleDirs &= ~DROITE; break;
        case HAUT: possibleDirs &= ~BAS; break;
        case BAS: possibleDirs &= ~HAUT; break;
    } // sw
    // // compte le nombre de bits à 1
    // int nbBits=0;
    // if (possibleDirs&DROITE) nbBits++;
    // if (possibleDirs&GAUCHE) nbBits++;
    // if (possibleDirs&HAUT) nbBits++;
    // if (possibleDirs&BAS) nbBits++;
    do {
        dir=getRandomDirection(); // dir aléatoire
        if (dir&possibleDirs) {
            ghost.dir = dir;
            break;
        } // if
    } while(1); // dangereux

    // avancer le ghost
    switch(ghost.dir) {
    case FIXE: break;
    case DROITE:
        ghost.x+=1;
        if ( ghost.x >= (jeu.maze_w-ghost.w-1)) // changement de bord
            ghost.x = 1;
        break;
    case GAUCHE:
        ghost.x-=1;
        if (ghost.x == 1) // changement de bord
            ghost.x = jeu.maze_w-ghost.w-1;
        break;
    case HAUT: ghost.y-=1; break;
    case BAS:  ghost.y+=1; break;
    } // sw
//    qDebug() << "Ghost : " << ghost.x << ghost.y;
    _zdc->setGhostNo(_num, ghost);
    QThread::msleep(jeu.vitesse); // pour ne pas aller trop vite
    if (!_running) {
        qDebug() << "FIN DU GHOST !";
        delete _zdc;
        emit sig_finished();
        return;
    } // if
    emit sig_refresh();
}

void CGhost::on_sig_erreurFromZDC(QString err)
{
    emit sig_erreur(err);
}

