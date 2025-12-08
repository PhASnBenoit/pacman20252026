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

int CPersonnage::getDirsP(T_PACMAN pac)
{
    QRgb p1, p2;
    int dirs = 0; // directions possibles
    // DROITE
    p1 = _maze.pixel(pac.x+pac.w, pac.y);
    p2 = _maze.pixel(pac.x+pac.w, pac.y+pac.h-1);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs = DROITE;
    } // if
    // GAUCHE
    p1 = _maze.pixel(pac.x-1, pac.y);
    p2 = _maze.pixel(pac.x-1, pac.y+pac.h-1);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs |= GAUCHE;
    } // if
    // HAUT
    p1 = _maze.pixel(pac.x, pac.y-1);
    p2 = _maze.pixel(pac.x+pac.w-1, pac.y-1);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs |= HAUT;
    } // if
    // BAS
    p1 = _maze.pixel(pac.x, pac.y+pac.h);
    p2 = _maze.pixel(pac.x+pac.w-1, pac.y+pac.h);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs |= BAS;
    } // if
    return dirs;
}

int CPersonnage::getDirsG(T_GHOST ghost)
{
    QRgb p1, p2;
    int dirs = 0; // directions possibles
    // DROITE
    p1 = _maze.pixel(ghost.x+ghost.w, ghost.y);
    p2 = _maze.pixel(ghost.x+ghost.w, ghost.y+ghost.h-1);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs = DROITE;
    } // if
    // GAUCHE
    p1 = _maze.pixel(ghost.x-1, ghost.y);
    p2 = _maze.pixel(ghost.x-1, ghost.y+ghost.h-1);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs |= GAUCHE;
    } // if
    // HAUT
    p1 = _maze.pixel(ghost.x, ghost.y-1);
    p2 = _maze.pixel(ghost.x+ghost.w-1, ghost.y-1);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs |= HAUT;
    } // if
    // BAS
    p1 = _maze.pixel(ghost.x, ghost.y+ghost.h);
    p2 = _maze.pixel(ghost.x+ghost.w-1, ghost.y+ghost.h);
    if ((p1==0xFF000000) && (p2==0xFF000000)) {
        dirs |= BAS;
    } // if
    return dirs;
}
