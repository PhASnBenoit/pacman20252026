#ifndef CPACMAN_H
#define CPACMAN_H

#include "cpersonnage.h"
#include <QObject>
#include <QKeyEvent>
#include <QThread>
#include <QDebug>
#include "czdc.h"

class CPacman : public CPersonnage
{
    Q_OBJECT
public:
    explicit CPacman(QObject *parent = nullptr);
    ~CPacman();

private:
    E_DIRS _dirMem;  // mémoire dir précédent

public slots:
    void on_go() override;
    void on_sig_erreurFromZDC(QString txt);

signals:

};

#endif // CPACMAN_H
