#include "cpacman.h"

CPacman::CPacman(QObject *parent)
    : CPersonnage{parent}
    , _running(true)      // ⭐️ liste d’initialisation
{
    _dir = _dirAsked = FIXE;
}

void CPacman::stop()
{
    _running = false;
}

void CPacman::on_go()
{
    int possibleDirs;
    T_PACMAN pac = _zdc->getPacman();
    T_GENERAL gen = _zdc->getGeneral();

    while (_running) {
        possibleDirs = getDirs(pac);
        // est ce que dirAsked est possible
        if (possibleDirs & _dirAsked)
            if (_dir != _dirAsked) {
                _dirMem = _dir;
                _dir = _dirAsked;
            } // if
        if (!(possibleDirs & _dir))
            _dir = FIXE;
        // avancer le pers
        switch(_dir) {
        case FIXE: break;
        case DROITE:
//            if (_dir != _dirMem)
//                ui->laPers->setPixmap(QPixmap("super-mario-droite.png"));
            pac.x+=1;
            if ( pac.x >= (gen.maze_w-pac.w)) // changement de bord
                pac.x = 0;
            break;
        case GAUCHE:
//            if (_dir != _dirMem)
//                ui->laPers->setPixmap(QPixmap("super-mario-gauche.png"));
            pac.x-=1;
            if (pac.x == 0) // changement de bord
                pac.x = gen.maze_w-pac.w;
            break;
        case HAUT:
            pac.y-=1;
            break;
        case BAS:
            pac.y+=1;
            break;
        } // sw
        _zdc->setPacman(pac);
        QThread::msleep(gen.vitesse); // pour ne pas aller trop vite
    } // wh
    emit sig_finished();
}

void CPacman::on_sig_key(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Q:
        _dirAsked = GAUCHE;
        break;
    case Qt::Key_D:
        _dirAsked = DROITE;
        break;
    case Qt::Key_Z:
        _dirAsked = HAUT;
        break;
    case Qt::Key_S:
        _dirAsked = BAS;
        break;
    } // sw
}

