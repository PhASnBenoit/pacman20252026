#ifndef CGHOST_H
#define CGHOST_H

#include <QObject>
#include <QRandomGenerator>
#include "cpersonnage.h"

class CGhost : public CPersonnage
{
    Q_OBJECT
public:
    explicit CGhost(QObject *parent = nullptr);
    void stop();

private:
    T_DIRECTION getRandomDirection();
    std::atomic_bool _running; // thread safe
    T_DIRECTION _dir;

private slots:
    void on_sig_erreurFromZDC(int no);

public slots:
    void on_go();

signals:
    void sig_erreur(QString txt);
    void sig_finished();

};

#endif // CGHOST_H
