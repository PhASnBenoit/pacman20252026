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
    int getDirs(int x, int y, int w, int h);
    void stop();

protected:
    int _num;
    QImage _maze;
    std::atomic_bool _running; // thread safe
    CZDC *_zdc;

public slots:
    virtual void on_go()=0;

signals:
    void sig_erreur(QString txt);
    void sig_finished();
    void sig_refresh();
};

#endif // CPERSONNAGE_H
