#include "csettings.h"

CSettings::CSettings(const QString &fileName, QObject *parent)
    : QSettings(fileName, QSettings::IniFormat, parent)
{

}

T_PACMAN CSettings::getPacman()
{
    T_PACMAN pac;
    pac.x = value("PACMAN/PACMAN_POS_DEP_X", 26).toInt();
    pac.y = value("PACMAN/PACMAN_POS_DEP_Y", 23).toInt();
    pac.w = value("PACMAN/PACMAN_WIDTH", 26).toInt();
    pac.h = value("PACMAN/PACMAN_HEIGHT", 23).toInt();
    memcpy(pac.image_droite, value("PACMAN/IMAGE_DROITE", "super-mario-droite.png").toString().toStdString().c_str(), sizeof(pac.image_droite));
    memcpy(pac.image_gauche, value("PACMAN/IMAGE_GAUCHE", "super-mario-gauche.png").toString().toStdString().c_str(), sizeof(pac.image_gauche));
    return pac;
}

T_GHOST CSettings::getGhost(int no)
{
    T_GHOST ghost;
    if ( (no<1) || (no>6)) // TODO A améliorer
        return ghost;
    ghost.w = value("GHOST/GHOST_WITDH", 26).toInt();
    ghost.h = value("GHOST/GHOST_HEIGHT", 23).toInt();
    QString name="GHOST"+QString::number(no)+"_";
    ghost.x = value("GHOST/"+name+"POS_DEP_X", 184).toInt();
    ghost.y = value("GHOST/"+name+"POS_DEP_Y", 23).toInt();
    memcpy(ghost.image, value("GHOST/"+name+"IMAGE", "redGhost.png").toString().toStdString().c_str(), sizeof(ghost.image));
    memcpy(ghost.image, value("GHOST/"+name+"COMPORTEMENT", "ALEATOIRE").toString().toStdString().c_str(), sizeof(ghost.comportement));
    return ghost;
}

T_GENERAL CSettings::getGeneral()
{
    T_GENERAL gen;
    gen.nbGhosts = value("GENERAL/NB_GHOSTS", 5).toInt();
    gen.vitesse = value("GENERAL/VITESSE", 10).toInt();
    gen.maze_w = value("GENERAL/MAZE_WIDTH", 492).toInt();
    gen.maze_h = value("GENERAL/MAZE_HEIGHT", 345).toInt();
    return gen;
}
