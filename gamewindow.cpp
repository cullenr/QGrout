
#include "gamewindow.h"
#include "assetcreatedevent.h"
#include <QtDebug>
#include <QQmlError>
#include <QSurfaceFormat>
#include <QCoreApplication>


GameWindow::GameWindow(QWindow *parent)
    : QtQuick2ApplicationViewer(parent)
{
    connect(this, SIGNAL(statusChanged(QQuickView::Status)),
            SLOT(logStatus(QQuickView::Status)));

//    QSurfaceFormat format;
//    format.setMajorVersion(3);
//    format.setMajorVersion(2);
//    format.setStencilBufferSize(4);
//    format.setProfile(QSurfaceFormat::CompatibilityProfile);

//    setFormat(format);

    connect(this, SIGNAL(sceneGraphInitialized()), this, SLOT(handleSceneGraphInitialized()));

//    QCoreApplication::instance()->installEventFilter(this);
}

//bool GameWindow::eventFilter(QObject *object, QEvent *event)
//{
//    if(event->type() == AssetCreatedEvent::AssetCreatedType)
//    {
//        qDebug("Asset Created Event Received");

//        return false;
//    }

//    return false;
//}
void GameWindow::handleSceneGraphInitialized()
{
//    QOpenGLFunctions_3_0 *funcs = openglContext()->versionFunctions<QOpenGLFunctions_3_0>();
//    if (!funcs)
//    {
//        qWarning() << "Could not obtain required OpenGL context version in GameWindow";
//        exit(1);
//    }
//    funcs->initializeOpenGLFunctions();
//    funcs->glDisable(GL_DEPTH);

//    glDisable(GL_DEPTH);
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
