#include "csettings.h"

CSettings::CSettings(const QString &fileName, QObject *parent)
    : QSettings(fileName, QSettings::IniFormat, parent)
{

}

QStringList CSettings::getPacman()
{
    QStringList lst;
    lst.append(value("PACMAN/PACMAN_POS_DEP_X", 26).toString());
    lst.append(value("PACMAN/PACMAN_POS_DEP_Y", 23).toString());
    lst.append(value("PACMAN/PACMAN_WIDTH", 26).toString());
    lst.append(value("PACMAN/PACMAN_HEIGHT", 23).toString());
    lst.append(value("PACMAN/PACMAN_IMAGE_DROITE", "super-mario-droite.png").toString());
    lst.append(value("PACMAN/PACMAN_IMAGE_GAUCHE", "super-mario-droite.png").toString());
    return lst;
}

QStringList CSettings::getGhost(int no)
{
    if ( (no<1) || (no>6)) // TODO A améliorer
        return QStringList();
    QStringList lst;
    lst.append(value("GHOST/GHOST_WITDH", 26).toString());
    lst.append(value("GHOST/GHOST_HEIGHT", 23).toString());
    QString name="GHOST"+QString::number(no)+"_";
    lst.append(value("GHOST/"+name+"POS_DEP_X", 184).toString());
    lst.append(value("GHOST/"+name+"POS_DEP_Y", 23).toString());
    lst.append(value("GHOST/"+name+"IMAGE", "redGhost.png").toString());
    lst.append(value("GHOST/"+name+"COMPORTEMENT", "ALEATOIRE").toString());
    return lst;
}

QStringList CSettings::getGeneral()
{
    QStringList lst;
    lst.append(value("GENERAL/MAX_GHOSTS", 6).toString());
    lst.append(value("GENERAL/NB_GHOSTS", 5).toString());
    lst.append(value("GENERAL/VITESSE", 10).toString());
    lst.append(value("GENERAL/MAZE_WIDTH", 492).toString());
    lst.append(value("GENERAL/MAZE_HEIGHT", 345).toString());
    return lst;
}
