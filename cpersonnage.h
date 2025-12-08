#ifndef CPERSONNAGE_H
#define CPERSONNAGE_H

#include <QObject>
#include <QImage>
#include <QRgb>

#include "commun.h"

class CPersonnage : public QObject
{
    Q_OBJECT
public:
    explicit CPersonnage(QObject *parent = nullptr);
    ~CPersonnage();
    int getDirsP(T_PACMAN pac);
    int getDirsG(T_GHOST ghost);

protected:
    int _num;
    QImage _maze;
    E_DIRECTIONS _dir; // direction effective

signals:

};

#endif // CPERSONNAGE_H
