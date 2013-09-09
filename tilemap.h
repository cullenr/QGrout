#ifndef TILEMAP_H
#define TILEMAP_H

#include <QGLFunctions>
#include <QVector>
#include <QQuickItem>

#include "visitee.h"
#include "mesh.h"

class Visitor;
class TileSheet;

class TileMap : public QQuickItem, public QGLFunctions, public Visitee
{
    Q_OBJECT
    Q_PROPERTY(TileSheet * tileSheet MEMBER m_tileSheet);
    Q_PROPERTY(QList<int> map MEMBER m_map);
    Q_PROPERTY(int mapWidth MEMBER m_mapWidth);
    Q_PROPERTY(int tileSize MEMBER m_tileSize);

public:
    explicit TileMap(QQuickItem *parent = 0);

    void accept(Visitor &visitor);

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
