#include "cpacman.h"

CPacman::CPacman(QObject *parent)
    : CPersonnage{parent}
    , _running(true)      // ⭐️ liste d’initialisation
{
    _dir = _dirAsked = FIXE;
    _x = 26;
    _y = 23;
}

void CPacman::stop()
{
    _running = false;
}

void CPacman::on_go()
{
 // TODO
    while (_running) {

        // mettre tempo paramétrable
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

