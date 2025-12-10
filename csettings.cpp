#include "csettings.h"

CSettings::CSettings(const QString &fileName, QObject *parent)
    : QSettings(fileName, QSettings::IniFormat, parent)
{
}

T_PACMAN CSettings::getPacman()
{
    T_PACMAN pac;
    pac.x = value("PACMAN/PACMAN_POS_DEP_X", 0).toInt();
    pac.y = value("PACMAN/PACMAN_POS_DEP_Y", 0).toInt();
    pac.w = value("PACMAN/PACMAN_WIDTH", 26).toInt();
    pac.h = value("PACMAN/PACMAN_HEIGHT", 23).toInt();
    memcpy(pac.image_droite, value("PACMAN/IMAGE_DROITE", "super-mario-droite.png").toString().toStdString().c_str(), sizeof(pac.image_droite));
    memcpy(pac.image_gauche, value("PACMAN/IMAGE_GAUCHE", "super-mario-gauche.png").toString().toStdString().c_str(), sizeof(pac.image_gauche));
    return pac;
}

T_GHOST CSettings::getGhost(int no)
{
    T_GHOST ghost;
    if ( (no<0) || (no>=MAX_GHOSTS)) // TODO A améliorer
        return ghost;
    no++;
    ghost.w = value("GHOSTS/GHOST_WIDTH", 0).toInt();
    ghost.h = value("GHOSTS/GHOST_HEIGHT", 0).toInt();
    QString name="GHOST"+QString::number(no)+"_";
    ghost.x = value("GHOSTS/"+name+"POS_DEP_X", 184).toInt();
    ghost.y = value("GHOSTS/"+name+"POS_DEP_Y", 23).toInt();
    memcpy(ghost.image, value("GHOSTS/"+name+"IMAGE", "redGhost.png").toString().toStdString().c_str(), sizeof(ghost.image));
    memcpy(ghost.comportement, value("GHOSTS/"+name+"COMPORTEMENT", "ALEATOIRE").toString().toStdString().c_str(), sizeof(ghost.comportement));
    ghost.num = no;
    return ghost;
}

T_JEU CSettings::getJeu()
{
    T_JEU jeu;
    jeu.nbGhosts = value("JEU/NB_GHOSTS", 0).toInt();
    jeu.vitesse = value("JEU/VITESSE", 200).toInt();
    jeu.maze_w = value("JEU/MAZE_WIDTH", 0).toInt();
    jeu.maze_h = value("JEU/MAZE_HEIGHT", 0).toInt();
    return jeu;
}
