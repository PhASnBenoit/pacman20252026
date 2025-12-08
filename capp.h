#ifndef CAPP_H
#define CAPP_H

#include <QObject>
#include <QList>
#include <QThread>
#include <QCoreApplication>
#include <QDebug>

#include "cgui.h"
#include "cpacman.h"
#include "cghost.h"
#include "czdc.h"
#include "csettings.h"

class CApp : public QObject
{
    Q_OBJECT
public:
    explicit CApp(QObject *parent = nullptr, int argc = 0, char *argv[] = nullptr);
    ~CApp();

private:
    CZDC *_zdc;
    CSettings *_settings;
    CPacman *_pacman;
    QThread *_thPacman;
    QList<CGhost *> _ghosts;
    QList<QThread *> _thGhosts;
    CGUI *_gui;
    void initZDCFromSettings();
    
private slots:
    void on_destroyed();

public slots:
    void on_sig_erreurFromZDC(QString err);

signals:
    void sig_erreurToGUI(QString txt);
    void sig_goPacman();
    void sig_goGhosts();
    void sig_stopPacman();
    void sig_stopGhosts();
};

#endif // CAPP_H
