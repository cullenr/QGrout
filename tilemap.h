#ifndef TILEMAP_H
#define TILEMAP_H

#include <QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QGLFunctions>
#include <QOpenGLFunctions_2_0>

class Material;

class Tilemap : public QQuickItem, public QGLFunctions
{
    Q_OBJECT
    Q_PROPERTY(Material *material MEMBER m_material NOTIFY materialChanged);

public:
    explicit Tilemap(QQuickItem *parent = 0);

private:
    Material *m_material;
    QOpenGLShaderProgram *m_program;
    GLuint m_tileVao;
    GLuint m_vboIds[2];

    QOpenGLFunctions_2_0 *m_GlFuncs;
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
