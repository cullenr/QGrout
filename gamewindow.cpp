#include "qtquick2applicationviewer.h"
#include "gamewindow.h"
#include <QtDebug>
#include <QQmlError>

GameWindow::GameWindow(QWindow *parent)
    : QtQuick2ApplicationViewer(parent)
{
    connect(this, SIGNAL(statusChanged(QQuickView::Status)),
            SLOT(logStatus(QQuickView::Status)));
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
