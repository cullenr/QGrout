#ifndef TILEMAP_H
#define TILEMAP_H

#include <QQuickItem>
#include <QGLFunctions>
#include <QVector>

#include "mesh.h"

class Visitor;
class Material;
class QOpenGLShaderProgram;

class Tilemap : public QQuickItem, public QGLFunctions
{
    Q_OBJECT
    Q_PROPERTY(Material *material MEMBER m_material);
    Q_PROPERTY(QList<int> map MEMBER m_map);
    Q_PROPERTY(int mapWidth MEMBER m_mapWidth);

public:
    explicit Tilemap(QQuickItem *parent = 0);

    void accept(Visitor &visitor);

    Material* material() const;
    QList<int> map() const;
    int mapWidth() const;
    QVector<Mesh> rows() const;
    void setRows(const QVector<Mesh> &rows);

    void componentComplete() override;

private:
    QVector<Mesh> m_rows;
    Material *m_material;

    QList<int> m_map;
    int m_mapWidth;
};

#endif // TILEMAP_H
