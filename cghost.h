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
    void stop();

private:
    E_DIRECTIONS getRandomDirection();
    std::atomic_bool _running; // thread safe
    E_DIRECTIONS _dir;
    CZDC *_zdc;
    int _no;

private slots:
    void on_sig_erreurFromZDC(QString err);

public slots:
    void on_go();

signals:
    void sig_erreur(QString txt);
    void sig_finished();
    void sig_refresh();

};

#endif // CGHOST_H
