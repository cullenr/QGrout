
#include "gamewindow.h"
#include <QtDebug>
#include <QQmlError>
#include <QSurfaceFormat>
#include <QOpenGLFunctions_3_0>

GameWindow::GameWindow(QWindow *parent)
    : QtQuick2ApplicationViewer(parent)
{
    connect(this, SIGNAL(statusChanged(QQuickView::Status)),
            SLOT(logStatus(QQuickView::Status)));

    QSurfaceFormat format;
    format.setMajorVersion(4);
    format.setMajorVersion(3);
    format.setStencilBufferSize(4);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);

    setFormat(format);

    connect(this, SIGNAL(sceneGraphInitialized()), this, SLOT(handleSceneGraphInitialized()));
}

void GameWindow::handleSceneGraphInitialized()
{
    QOpenGLFunctions_3_0 *funcs = openglContext()->versionFunctions<QOpenGLFunctions_3_0>();
    if (!funcs)
    {
        qWarning() << "Could not obtain required OpenGL context version in GameWindow";
        exit(1);
    }
    funcs->initializeOpenGLFunctions();
    funcs->glDisable(GL_DEPTH);
}

GameWindow::~GameWindow()
{
}

void GameWindow::logStatus(QQuickView::Status status)
{
    switch (status) {
    case Loading:
        break;
    case Ready:
        break;
    case Error:
        qDebug("GameWindow::ERROR");

        QListIterator<QQmlError> i(errors());

        while(i.hasNext())
        {
            qDebug() << i.next();
        }

        break;
    }
}
