#ifndef CPERSONNAGE_H
#define CPERSONNAGE_H

#include <QObject>
#include <QImage>
#include <QRgb>

#include "commun.h"
#include "czdc.h"

class CPersonnage : public QObject
{
    Q_OBJECT
public:
    explicit CPersonnage(QObject *parent = nullptr);
    ~CPersonnage();
    int getDirs(T_PACMAN pac);

protected:
    int _num;
    QImage _maze;
    T_DIRECTION _dir; // direction effective
    CZDC *_zdc;

signals:

};

#endif // CPERSONNAGE_H
