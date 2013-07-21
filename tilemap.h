#ifndef TILEMAP_H
#define TILEMAP_H

#include <QQuickItem>
#include <QtGui/QOpenGLShaderProgram>

class Tilemap : public QQuickItem
{
    Q_OBJECT
public:
    explicit Tilemap(QQuickItem *parent = 0);

private:
    QOpenGLShaderProgram *m_program;

protected:
    virtual void componentComplete();
    
public slots:
    void draw();

private slots:
    void handleWindowChanged(QQuickWindow *win);
};

#endif // TILEMAP_H
