#ifndef CGHOST_H
#define CGHOST_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QRandomGenerator>
#include "cpersonnage.h"
#include "czdc.h"

class CGhost : public CPersonnage
{
    Q_OBJECT
public:
    explicit CGhost(int no=0, QObject *parent = nullptr);
    ~CGhost();

private:
    E_DIRS getRandomDirection();

private slots:
    void on_sig_erreurFromZDC(QString err);

public slots:
    void on_go();

signals:

};

#endif // CGHOST_H
