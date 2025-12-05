#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QStringList>

#include "commun.h"

class CSettings : public QSettings
{
    Q_OBJECT
public:
    explicit CSettings(const QString &fileName = "pacman.ini", QObject *parent = nullptr);
    T_PACMAN getPacman();
    T_GHOST getGhost(int no);
    T_GENERAL getGeneral();
};

#endif // CSETTINGS_H
