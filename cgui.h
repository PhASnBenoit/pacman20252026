#ifndef CGUI_H
#define CGUI_H

#include <QMainWindow>
#include <QTimer>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QImage>
#include <QList>
#include <QLabel>
#include <QDebug>

#include "commun.h"
#include "czdc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CGUI; }
QT_END_NAMESPACE

class CGUI : public QMainWindow
{
    Q_OBJECT

public:
    CGUI(CZDC *zdc = nullptr, QWidget *parent = nullptr);
    ~CGUI();

private:
    Ui::CGUI *ui;
    CZDC *_zdc;
    QTimer _timerFw;
    QImage _maze;
    E_DIRECTIONS _dirMem;
    QList<QLabel *> _laGhosts;
    virtual void keyPressEvent(QKeyEvent *e);

private slots:
    void on_timeout();

public slots:
    void on_erreur(QString txt);

signals:
    void sig_key(QKeyEvent *e);
};
#endif // CGUI_H
