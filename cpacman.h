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
    void stop();

private:
    E_DIRECTIONS _dirMem;  // mémoire dir précédent
    std::atomic_bool _running; // thread safe
    CZDC *_zdc;

public slots:
    void on_go();

signals:
    void sig_erreur(QString txt);
    void sig_finished();
    void sig_refresh();
};

#endif // CPACMAN_H
