#include "cpersonnage.h"

CPersonnage::CPersonnage(QObject *parent)
    : QObject{parent}
{
    int res = _maze.load("pacman-maze.png");
    if (!res)
        return;
}

CPersonnage::~CPersonnage()
{

}

int CPersonnage::getDirs()
{
    QRgb p1, p2;
    int dirs = 0; // directions possibles
    // DROITE
    p1 = _maze.pixel(_x+_w, _y);
    p2 = _maze.pixel(_x+_w, _y+_h-1);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs = DROITE;
    } // if
    // GAUCHE
    p1 = _maze.pixel(_x-1, _y);
    p2 = _maze.pixel(_x-1, _y+_h-1);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs |= GAUCHE;
    } // if
    // HAUT
    p1 = _maze.pixel(_x, _y-1);
    p2 = _maze.pixel(_x+_w-1, _y-1);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs |= HAUT;
    } // if
    // BAS
    p1 = _maze.pixel(_x, _y+_h);
    p2 = _maze.pixel(_x+_w-1, _y+_h);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs |= BAS;
    } // if
    return dirs;
}

int CPersonnage::x() const
{
    return _x;
}

int CPersonnage::y() const
{
    return _y;
}

int CPersonnage::w() const
{
    return _w;
}

int CPersonnage::h() const
{
    return _h;
}
