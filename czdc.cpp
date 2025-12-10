#include "czdc.h"

CZDC::CZDC() : QSharedMemory(KEY)
{
    _data = nullptr;
}

CZDC::~CZDC() {
    detach();
}

int CZDC::init(bool capp)
{
    bool res, res2;

    if (capp) { // création
        qDebug() << "CZDC::init: CAPP veut créer la ZDC";
        while(attach())
            detach();
        res = create(sizeof(T_ZDC));
        if (!res) { // soit déjà créé, soit plus de mem
            qDebug() << "CZDC::init: création ZDC impossible !";
            emit sig_erreur("CZDC::init création ZDC impossible !");
            return -1;
        } // if res
        qDebug() << "CZDC::init: Récupération et raz ZDC !";
        lock();
            _data = (T_ZDC *) data();
            std::memset(_data, 0, sizeof(T_ZDC));
        unlock();
    } else {  // ensuite...
        res2 = attach();
        if (!res2) {
            qDebug() << "CZDC::init: attach ZDC impossible !";
            emit sig_erreur("CZDC::init attach impossible !");
            return -1;
        } // if res
        qDebug() << "CZDC::init: Récupération pointeur ZDC !";
        lock();
            _data = (T_ZDC *) data();
        unlock();
    } // else
    return 0;
}

void CZDC::setDirAskedPacman(E_DIRS dir)
{
    lock();
        _data->pacman.dirAsked = dir;
    unlock();
}

T_PACMAN CZDC::getPacman()
{
    T_PACMAN pac;
    lock();
        memcpy(&pac, &_data->pacman, sizeof(T_PACMAN));
    unlock();
    return pac;
}

T_GHOST CZDC::getGhostNo(int no)
{
    T_GHOST ghost;
    memset(&ghost, 0, sizeof(T_GHOST));
    if ((no<0) || (no>=_data->jeu.nbGhosts)) {
        emit sig_erreur("CZDC::getGhostNb Nb ghosts incompatible !");
        return ghost;
    } //
    lock();
        memcpy(&ghost, &_data->ghosts[no], sizeof(T_GHOST));
    unlock();
    return ghost;
}

T_JEU CZDC::getJeu()
{
    T_JEU jeu;
    lock();
        memcpy(&jeu, &_data->jeu, sizeof(T_JEU));
    unlock();
    return jeu;
}

QList<int> CZDC::getXYTousLesGhosts()
{
    QList<int> xy;

    lock();
        for (int i=0 ; i<_data->jeu.nbGhosts ; i++) {
            xy.append(_data->ghosts[i].x);
            xy.append(_data->ghosts[i].y);
        } // for
    unlock();
    return xy;
}

void CZDC::setPacman(T_PACMAN pac)
{
    lock();
        memcpy(&_data->pacman, &pac, sizeof(T_PACMAN));
    unlock();
}

void CZDC::setGhostNo(int no, T_GHOST ghost)
{
    if ((no<0) || (no>=_data->jeu.nbGhosts)) {
        emit sig_erreur("CZDC::setGhostNb N° ghost incompatible !");
        return;
    } //
    lock();
        memcpy(&_data->ghosts[no], &ghost, sizeof(T_GHOST));
    unlock();
}

void CZDC::setJeu(T_JEU jeu)
{
    lock();
        memcpy(&_data->jeu, &jeu, sizeof(T_JEU));
    unlock();
}

