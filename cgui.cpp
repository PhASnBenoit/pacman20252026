#include "cgui.h"
#include "ui_cgui.h"

CGUI::CGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CGUI)
{
    ui->setupUi(this);
    _wW = ui->laMaze->geometry().width();
    _hW = ui->laMaze->geometry().height();
    _wL = ui->laPers->geometry().width();
    _hL = ui->laPers->geometry().height();
    connect(&_timerFw, &QTimer::timeout,
            this, &CGUI::on_timeout);
    _timerFw.start(10);
}

CGUI::~CGUI()
{
    delete ui;
}

void CGUI::keyPressEvent(QKeyEvent *e)
{
    emit sig_key(e);
}

void CGUI::on_timeout()
{



/*
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
        if (_dir != _dirMem)
            ui->laPers->setPixmap(QPixmap("super-mario-droite.png"));
        x+=1;
        if ( x >= (_wW-_wL))
            x = 0;
        break;
    case GAUCHE:
        if (_dir != _dirMem)
            ui->laPers->setPixmap(QPixmap("super-mario-gauche.png"));
        x-=1;
        if (x == 0)
            x = _wW-_wL;
        break;
    case HAUT:
        y-=1;
        break;
    case BAS:
        y+=1;
        break;
    }
    ui->laPers->setGeometry(x,y,_wL,_hL);
    */
}

void CGUI::on_erreur(QString txt)
{
  // TODO
}

/*void CGUI::on_timeoutDir()
{
    _dir = getRandomDirection();
}*/

