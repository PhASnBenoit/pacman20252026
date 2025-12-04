#include "cghost.h"

CGhost::CGhost(QObject *parent)
    : CPersonnage{parent}
    , _running(true), _dir(HAUT)     // ⭐️ liste d’initialisation
{
    _zdc = new CZDC();
    connect(_zdc, &CZDC::sig_erreur, this, &CGhost::on_sig_erreurFromZDC);
    _zdc->init();  // création de la ZDC

}

void CGhost::stop()
{
    _running = false;
}

T_DIRECTION CGhost::getRandomDirection()
{
    int value = QRandomGenerator::global()->bounded(4);
    return (T_DIRECTION)(1<<value);
}

void CGhost::on_go()
{
    while (_running) {

        // TODO tempo
    } // wh
    emit sig_finished();
}

void CGhost::on_sig_erreurFromZDC(int no)
{
    emit sig_erreur("CGhost: Erreur d'accès ZDC");
}

