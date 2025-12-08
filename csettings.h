#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QObject>
#include <QSettings>

#include "commun.h"

class CSettings : public QSettings
{
    Q_OBJECT
public:
    explicit CSettings(const QString &fileName = "/home/philippe/devQt/appPacman20252026/pacman.ini", QObject *parent = nullptr);
    T_PACMAN getPacman();
    T_GHOST getGhost(int no);
    T_JEU getJeu();
};

#endif // CSETTINGS_H
