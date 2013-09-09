#ifndef TILESHEET_H
#define TILESHEET_H

#include <QObject>

class Material;

class TileSheet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Material * material MEMBER m_material);
    Q_PROPERTY(int tilesAcross MEMBER m_tilesAcross);
    Q_PROPERTY(int tilesSize MEMBER m_tileSize);
public:
    explicit TileSheet(QObject *parent = 0);
    
    Material* material() const;
    int tileSize() const;
    int tilesAcross() const;

private:
    Material *m_material;
    int m_tileSize;
    int m_tilesAcross;
};

#endif // TILESHEET_H
