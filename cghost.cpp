#include "cghost.h"

CGhost::CGhost(int no, QObject *parent)
    : CPersonnage{parent}
    , _running(true), _dir(HAUT)     // ⭐️ liste d’initialisation
{
    _zdc = new CZDC();
    connect(_zdc, &CZDC::sig_erreur, this, &CGhost::on_sig_erreurFromZDC);
    if (_zdc->init(false)) { // attach à la ZDC
        qDebug() << "CGhost::CGhost: Erreur ZDC";
        delete _zdc;
        emit sig_finished();
        return;
    } // if
    connect(this, &CGhost::sig_refresh, this, &CGhost::on_go);
    _no = no;
}

CGhost::~CGhost()
{
    delete _zdc;
}

void CGhost::stop()
{
    _running = false;
}

E_DIRECTIONS CGhost::getRandomDirection()
{
    int value = QRandomGenerator::global()->bounded(4);
    return (E_DIRECTIONS)(1<<value);
}

void CGhost::on_go()
{
    int possibleDirs;
    E_DIRECTIONS dir;
    T_GHOST ghost = _zdc->getGhostNo(_no);
    T_JEU jeu = _zdc->getJeu();
    possibleDirs = getDirsG(ghost); // dirs possible
    if (!(possibleDirs & ghost.dir)) { // si pas compatible avec dir actuelle
        do {
            dir=getRandomDirection(); // dir aléatoire
            if (dir&possibleDirs) {
                ghost.dir = dir;
                break;
            } // if
        } while(1); // dangereux
    } // if
    // avancer le ghost
    switch(ghost.dir) {
    case FIXE: break;
    case DROITE:
        ghost.x+=1;
        if ( ghost.x >= (jeu.maze_w-ghost.w)) // changement de bord
            ghost.x = 0;
        break;
    case GAUCHE:
        ghost.x-=1;
        if (ghost.x == 0) // changement de bord
            ghost.x = jeu.maze_w-ghost.w;
        break;
    case HAUT:
        ghost.y-=1;
        break;
    case BAS:
        ghost.y+=1;
        break;
    } // sw
//    qDebug() << "Ghost : " << ghost.x << ghost.y;
    _zdc->setGhostNo(_no, ghost);
    QThread::msleep(jeu.vitesse); // pour ne pas aller trop vite
    if (!_running) {
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

