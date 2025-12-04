#ifndef CPACMAN_H
#define CPACMAN_H

#include "cpersonnage.h"
#include <QObject>
#include <QKeyEvent>

class CPacman : public CPersonnage
{
    Q_OBJECT
public:
    explicit CPacman(QObject *parent = nullptr);
    void stop();

private:
    T_DIRECTION _dirAsked; // direction demandée
    std::atomic_bool _running; // thread safe

public slots:
    void on_sig_key(QKeyEvent *e);
    void on_go();

signals:
    void sig_erreur(QString txt);
    void sig_finished();
};

#endif // CPACMAN_H
