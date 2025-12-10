#include "cpacman.h"

CPacman::CPacman(QObject *parent)
    : CPersonnage{parent}
{
    qDebug() << "CPacman::CPacman: new CZDC";
    connect(_zdc, &CZDC::sig_erreur, this, &CPacman::on_sig_erreurFromZDC);
    connect(this, &CPacman::sig_refresh, this, &CPacman::on_go);
}

CPacman::~CPacman()
{
}

void CPacman::on_go()
{
    int possibleDirs;
    T_PACMAN pac = _zdc->getPacman();
    T_JEU jeu = _zdc->getJeu();

        possibleDirs = getDirs(pac.x, pac.y, pac.w, pac.h);
        // est ce que dirAsked est possible
        if (possibleDirs & pac.dirAsked)
            if (pac.dir != pac.dirAsked) {
                _dirMem = pac.dir;
                pac.dir = pac.dirAsked;
            } // if
        if (!(possibleDirs & pac.dir))
            pac.dir = FIXE;
        // avancer le pers
        switch(pac.dir) {
        case FIXE: break;
        case DROITE:
            pac.x+=1;
            if ( pac.x >= (jeu.maze_w-pac.w)) // changement de bord
                pac.x = 0;
            break;
        case GAUCHE:
            pac.x-=1;
            if (pac.x == 0) // changement de bord
                pac.x = jeu.maze_w-pac.w;
            break;
        case HAUT:
            pac.y-=1;
            break;
        case BAS:
            pac.y+=1;
            break;
        } // sw
        _zdc->setPacman(pac);
        QThread::msleep(jeu.vitesse); // pour ne pas aller trop vite
        if (!_running) {
            delete _zdc;
            emit sig_finished();
            return;
        } // if
        emit sig_refresh();
}

void CPacman::on_sig_erreurFromZDC(QString txt)
{
    emit sig_erreur(txt);
}

