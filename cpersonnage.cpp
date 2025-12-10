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
  //  delete _zdc;
}

int CPersonnage::getDirs(int x, int y, int w, int h)
{
    QRgb p1, p2;
    int dirs = 0; // directions possibles
    // DROITE
    p1 = _maze.pixel(x+w, y);
    p2 = _maze.pixel(x+w, y+h-1);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs = DROITE;
    } // if
    // GAUCHE
    p1 = _maze.pixel(x-1, y);
    p2 = _maze.pixel(x-1, y+h-1);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs |= GAUCHE;
    } // if
    // HAUT
    p1 = _maze.pixel(x, y-1);
    p2 = _maze.pixel(x+w-1, y-1);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs |= HAUT;
    } // if
    // BAS
    p1 = _maze.pixel(x, y+h);
    p2 = _maze.pixel(x+w-1, y+h);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs |= BAS;
    } // if
    return dirs;
}
