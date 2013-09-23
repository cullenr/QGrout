#include "tilemap.h"
#include "tilesheet.h"
#include "material.h"
#include "shaderasset.h"
#include "textureasset.h"
#include "vertexdata.h"
#include "sceneitemvisitor.h"

#include <QtQuick/qquickwindow.h>

TileMap::TileMap(QObject *parent) :
    AbstractSceneItem(parent),
    m_tileSheet(nullptr)
{
}

void TileMap::accept(SceneItemVisitor &visitor)
{
    visitor.visit(*this);
}

QVector<Mesh> TileMap::rows() const
{
    return m_rows;
}

void TileMap::setRows(const QVector<Mesh> &rows)
{
    m_rows = rows;
}

TileSheet *TileMap::tileSheet() const
{
    return m_tileSheet;
}
QList<int> TileMap::map() const
{   
    return m_map;
}

int TileMap::mapWidth() const
{
    return m_mapWidth;
}

int TileMap::tileSize() const
{
    return m_tileSize;
}

