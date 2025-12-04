#include "czdc.h"

CZDC::CZDC()
{
    _data = nullptr;
}

CZDC::~CZDC() {
}

int CZDC::init()
{
    bool res, res2;
    setKey(KEY);
    res = create(sizeof(T_ZDC));
    if (!res) { // soit déjà créé, soit plus de mem
        res2 = attach();
        if (!res2) {
            emit sig_erreur(-1);
            return -1;
        } // if res2
    } // if res
    _data = (T_ZDC *) data();
    return 0;
}

void CZDC::clear()
{
    memset(_data, 0, sizeof(T_ZDC));
}

T_PACMAN CZDC::getPacman()
{
    T_PACMAN pac;
    lock();
        memcpy(&pac, &_data->pacman, sizeof(T_PACMAN));
    unlock();
    return pac;
}

T_GHOST CZDC::getGhostNb(int nb)
{
    T_GHOST ghost;
    memset(&ghost, 0, sizeof(T_GHOST));
    if ((nb<0) || (nb>=MAX_GHOST)) {
        emit sig_erreur(-2);
        return ghost;
    } //
    lock();
        memcpy(&ghost, &_data->ghosts[nb], sizeof(T_GHOST));
    unlock();
    return ghost;
}

void CZDC::setPacman(T_PACMAN pac)
{
    lock();
        memcpy(&_data->pacman, &pac, sizeof(T_PACMAN));
    unlock();
}

void CZDC::setGhostNb(int nb, T_GHOST ghost)
{
    if ((nb<0) || (nb>=MAX_GHOST)) {
        emit sig_erreur(-2);
        return;
    } //
    lock();
        memcpy(&_data->ghosts[nb], &ghost, sizeof(T_GHOST));
        unlock();
}

