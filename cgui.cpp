#include "cgui.h"
#include "ui_cgui.h"

CGUI::CGUI(CZDC *zdc, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CGUI)
{
    ui->setupUi(this);    

    _zdc = zdc;
    connect(_zdc, &CZDC::sig_erreur, this, &CGUI::on_erreur);

    // Créer les ghosts
    T_GHOST ghost;
    QLabel *laGhost;
    QImage iGhost;
    QString filenameGhost;
    for (int i=0 ; i<_zdc->getJeu().nbGhosts ; i++) {
        ghost = _zdc->getGhostNo(i);
        // création des QLabels des Ghosts
        filenameGhost = QString(ghost.image);
        iGhost.load(filenameGhost);
        laGhost = new QLabel(this);
        laGhost->setObjectName("laGhost"+QString::number(i+1));
        laGhost->setPixmap(QPixmap::fromImage(iGhost));
        laGhost->setScaledContents(true);
        laGhost->setGeometry(ghost.x, ghost.y, ghost.w, ghost.h);
        _laGhosts.append(laGhost);
    } // for

    connect(&_timerFw, &QTimer::timeout, this, &CGUI::on_timeout);
    _timerFw.start(150);
}

CGUI::~CGUI()
{
    delete ui;
}

void CGUI::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_D: _zdc->setDirAskedPacman(DROITE); break;
    case Qt::Key_Q: _zdc->setDirAskedPacman(GAUCHE); break;
    case Qt::Key_Z: _zdc->setDirAskedPacman(HAUT); break;
    case Qt::Key_S: _zdc->setDirAskedPacman(BAS); break;
    } // sw
}

void CGUI::on_timeout()
{
    // PACMAN
    T_PACMAN pac = _zdc->getPacman();
    if ((pac.dir == DROITE) && (_dirMem != pac.dir)) {
        ui->laPacman->setPixmap(QPixmap("super-mario-droite.png"));
        _dirMem = pac.dir;
    } // if
    if ((pac.dir == GAUCHE) && (_dirMem != pac.dir)) {
        _dirMem = pac.dir;
        ui->laPacman->setPixmap(QPixmap("super-mario-gauche.png"));
    } // if
    ui->laPacman->setGeometry(pac.x, pac.y, pac.w, pac.h);

    // GHOSTS
    //T_GHOST ghost;
    QList<int> xy = _zdc->getXYTousLesGhosts();
    for (int i=0 ; i<_laGhosts.size() ; i++) {
        //ghost = _zdc->getGhostNo(i);
       _laGhosts.at(i)->setGeometry(xy[2*i],xy[2*i+1] , pac.w, pac.h);
    }
}

void CGUI::on_erreur(QString txt)
{
  ui->statusbar->showMessage(txt);
}
