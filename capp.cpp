#include "capp.h"

CApp::CApp(QObject *parent, int argc, char *argv[])
    : QObject{parent}
{
    // TODO INIT ZDC avec CSETTINGS
    _zdc = new CZDC();
    connect(_zdc, &CZDC::sig_erreur, this, &CApp::on_sig_erreurFromZDC);
    if (_zdc->init())  // création de la ZDC
        return;
    _zdc->clear(); // RAZ
    _zdc->setGeneral(_settings.getGeneral());
    _zdc->setPacman(_settings.getPacman());
    for(int i=0 ; i<_zdc->getGeneral().nbGhosts ; i++) {
        _zdc->setGhostNb(i, _settings.getGhost(i));
    }

    // IHM
    _gui = new CGUI();
    connect(_gui, &CGUI::destroyed, this, &CApp::on_destroyed);
    connect(this, &CApp::sig_erreurToGUI, _gui, &CGUI::on_erreur);
    _gui->show();

    // création et départ du pacman
    _pacman = new CPacman(nullptr); // TODO réglages par défaut
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
    for (int i=0 ; i<_zdc->getGeneral().nbGhosts ; i++) {
        ghost = new CGhost(nullptr);// TODO Réglage par défaut
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
    for (int i=0 ; i<_ghosts.size() ; i++) {
        _ghosts[i]->stop();
        _thGhosts[i]->wait(100);
        delete _thGhosts[i];
    } // for
    _ghosts.clear();
    _thGhosts.clear();
    _pacman->stop();
    _thPacman->wait(100);
    delete _pacman;
}

void CApp::on_destroyed()
{
    QCoreApplication::quit(); // arrêt de l'application
}

void CApp::on_sig_erreurFromZDC(int no)
{
    emit sig_erreurToGUI("Impossible de créer la ZDC !");
}
