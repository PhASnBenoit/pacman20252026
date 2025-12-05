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
    T_PACMAN pac = _zdc.getPacman();

    ui->laPers->setGeometry(pac.x,pac.y, pac.w,pac.h);

}

void CGUI::on_erreur(QString txt)
{
  // TODO
}

/*void CGUI::on_timeoutDir()
{
    _dir = getRandomDirection();
}*/

