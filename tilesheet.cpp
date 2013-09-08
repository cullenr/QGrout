#include "tilesheet.h"

TileSheet::TileSheet(QObject *parent) :
    GObject(parent)
{
}

Material* TileSheet::material() const
{
    return m_material;
}

int TileSheet::tileSize() const
{
    return m_tileSize;
}

int TileSheet::tilesAcross() const
{
    return m_tilesAcross;
}
