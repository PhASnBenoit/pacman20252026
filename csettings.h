#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QStringList>

class CSettings : public QSettings
{
    Q_OBJECT
public:
    explicit CSettings(const QString &fileName = "pacman.ini", QObject *parent = nullptr);
    QStringList getPacman();
    QStringList getGhost(int no);
    QStringList getGeneral();
};

#endif // CSETTINGS_H
