#include "cgui.h"
#include "ui_cgui.h"

CGUI::CGUI(CZDC *zdc, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CGUI)
{
    ui->setupUi(this);    

    _zdc = zdc;
    connect(_zdc, &CZDC::sig_erreur, this, &CGUI::on_erreur);
    T_JEU jeu = _zdc->getJeu();
    jeu.maze_h = ui->laMaze->geometry().height();
    jeu.maze_w = ui->laMaze->geometry().width();
    _zdc->setJeu(jeu);

    // Créer les ghosts
    T_GHOST ghost;
    QLabel *laGhost;
    QImage iGhost;
    QString filenameGhost;
    for (int i=0 ; i<jeu.nbGhosts ; i++) {
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
    _timerFw.start(20);
}

CGUI::~CGUI()
{
    delete ui;
}

void CGUI::keyPressEvent(QKeyEvent *e)
{
    E_DIRECTIONS dirAsked;
    switch(e->key()) {
    case Qt::Key_Q:
        dirAsked = GAUCHE;
        _zdc->setDirAskedPacman(dirAsked);
        break;
    case Qt::Key_D:
        dirAsked = DROITE;
        _zdc->setDirAskedPacman(dirAsked);
        break;
    case Qt::Key_Z:
        dirAsked = HAUT;
        _zdc->setDirAskedPacman(dirAsked);
        break;
    case Qt::Key_S:
        dirAsked = BAS;
        _zdc->setDirAskedPacman(dirAsked);
        break;
    } // sw

}

void CGUI::on_timeout()
{
    // // PACMAN
    // T_PACMAN pac = _zdc->getPacman();
    // if ((pac.dir == DROITE) && (_dirMem != pac.dir)) {
    //     ui->laPacman->setPixmap(QPixmap("super-mario-droite.png"));
    //     _dirMem = pac.dir;
    // } // if
    // if ((pac.dir == GAUCHE) && (_dirMem != pac.dir)) {
    //     _dirMem = pac.dir;
    //     ui->laPacman->setPixmap(QPixmap("super-mario-gauche.png"));
    // } // if
    // ui->laPacman->setGeometry(pac.x, pac.y, pac.w, pac.h);

    // GHOSTS
    T_GHOST ghost;
    for (int i=0 ; i<_laGhosts.size() ; i++) {
        ghost = _zdc->getGhostNo(i);
       _laGhosts.at(i)->setGeometry(ghost.x, ghost.y, ghost.w, ghost.h);
    }
}

void CGUI::on_erreur(QString txt)
{
  ui->statusbar->showMessage(txt);
}
