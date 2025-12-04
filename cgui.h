#ifndef CGUI_H
#define CGUI_H

#include <QMainWindow>
#include <QTimer>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QImage>

#include "commun.h"
#include "czdc.h"
#include "csettings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CGUI; }
QT_END_NAMESPACE

class CGUI : public QMainWindow
{
    Q_OBJECT

public:
    CGUI(QWidget *parent = nullptr);
    ~CGUI();

private:
    Ui::CGUI *ui;
    QTimer _timerFw;
    QImage _maze;
    CZDC _zdc;
    virtual void keyPressEvent(QKeyEvent *e);
    int _wL, _hL;
    int _wW, _hW;
    CSettings _settings;

private slots:
    void on_timeout();

public slots:
    void on_erreur(QString txt);

signals:
    void sig_key(QKeyEvent *e);
};
#endif // CGUI_H
