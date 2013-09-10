#ifndef TILEMAP_H
#define TILEMAP_H

#include <QtOpenGL/QGLFunctions>
#include <QtCore/QVector>
#include <QtCore/QObject>

#include "abstractgameobject.h"
#include "mesh.h"

class SceneElementVisitor;
class TileSheet;

class TileMap : public AbstractGameObject, public QGLFunctions
{
    Q_OBJECT
    Q_PROPERTY(TileSheet * tileSheet MEMBER m_tileSheet);
    Q_PROPERTY(QList<int> map MEMBER m_map);
    Q_PROPERTY(int mapWidth MEMBER m_mapWidth);
    Q_PROPERTY(int tileSize MEMBER m_tileSize);

public:
    explicit TileMap(QObject *parent = 0);

    void accept(SceneElementVisitor &visitor);

    TileSheet* tileSheet() const;

    QList<int> map() const;

    int mapWidth() const;

    int tileSize() const;

    QVector<Mesh> rows() const;
    void setRows(const QVector<Mesh> &rows);

private:
    QVector<Mesh> m_rows;
    TileSheet *m_tileSheet;

    QList<int> m_map;
    int m_mapWidth;
    int m_tileSize;
};

#endif // TILEMAP_H
