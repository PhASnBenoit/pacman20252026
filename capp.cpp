#include "capp.h"
#include <QFile>
CApp::CApp(QObject *parent, int argc, char *argv[])
    : QObject{parent}
{
    qDebug() << "CApp::CApp: new CZDC";
    _zdc = new CZDC();
    connect(_zdc, &CZDC::sig_erreur, this, &CApp::on_sig_erreurFromZDC);
    if (_zdc->init(true)) { // création de la ZDC
        qDebug() << "CApp::CApp: Erreur ZDC";
        qDebug() << "CApp::CApp: Fin du programme";
        delete _zdc;
        QCoreApplication::exit(-1);
    } // if
    initZDCFromSettings();

    // IHM
    _gui = new CGUI(_zdc);
    connect(_gui, &CGUI::destroyed, this, &CApp::on_destroyed);
    connect(this, &CApp::sig_erreurToGUI, _gui, &CGUI::on_erreur);
    _gui->show();

    // création et départ du pacman
    _pacman = new CPacman(); // TODO réglages par défaut
    _thPacman = new QThread();
    _pacman->moveToThread(_thPacman);
    connect(_thPacman, &QThread::started, _pacman, &CPacman::on_go);
    connect(_pacman, &CPacman::sig_finished, _thPacman, &QThread::quit);
    connect(_thPacman, &QThread::finished, _pacman, &CPacman::deleteLater);
    connect(_thPacman, &QThread::finished, _thPacman, &QThread::deleteLater);
    _thPacman->start(); // TOP DEPART

    // création et départ des fantomes
    CGhost *ghost;
    QThread *_thGhost;
    for (int i=0 ; i<_zdc->getJeu().nbGhosts ; i++) {
        ghost = new CGhost(i);// TODO Réglage par défaut
        _ghosts.append(ghost);
        _thGhost = new QThread();
        ghost->moveToThread(_thGhost);
        _thGhosts.append(_thGhost);
        connect(_thGhost, &QThread::started, ghost, &CGhost::on_go);
        connect(ghost, &CGhost::sig_finished, _thGhost, &QThread::quit);
        connect(_thGhost, &QThread::finished, ghost, &CGhost::deleteLater);
        connect(_thGhost, &QThread::finished, _thGhost, &QThread::deleteLater);
        _thGhost->start(); // TOP DEPART
    } // for
}

CApp::~CApp()
{
    qDebug() << "CApp::~CApp: Destructeur";

    for (int i=0 ; i<_ghosts.size() ; i++) {
        _ghosts[i]->stop();
    } // for
    _ghosts.clear();
    _thGhosts.clear();
    _pacman->stop();
    delete _settings;
    delete _zdc;
}

void CApp::initZDCFromSettings()
{
    T_JEU jeu;
    _settings = new CSettings("/home/philippe/devQt/appPacman20252026/pacman.ini");
    jeu = _settings->getJeu();
    _zdc->setJeu(jeu);
    _zdc->setPacman(_settings->getPacman());
    for(int i=0 ; i<_zdc->getJeu().nbGhosts ; i++) {
        _zdc->setGhostNo(i, _settings->getGhost(i));
    } // for
}

void CApp::on_destroyed()
{
    QCoreApplication::quit(); // arrêt de l'application
}

void CApp::on_sig_erreurFromZDC(QString err)
{
    emit sig_erreurToGUI(err);
}
