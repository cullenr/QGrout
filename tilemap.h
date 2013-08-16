#ifndef TILEMAP_H
#define TILEMAP_H

#include <QQuickItem>
#include <QGLFunctions>

class Material;
class QOpenGLShaderProgram;

class Tilemap : public QQuickItem, public QGLFunctions
{
    Q_OBJECT
    Q_PROPERTY(Material *material MEMBER m_material NOTIFY materialChanged);


public:
    explicit Tilemap(QQuickItem *parent = 0);

private:
    Material *m_material;
    QOpenGLShaderProgram *m_program;
    GLuint m_vboIds[2];

protected:
    virtual void componentComplete();
    
signals:
    void materialChanged(Material *);

public slots:
    void draw();

private slots:
    void handleWindowChanged(QQuickWindow *win);
};

#endif // TILEMAP_H
