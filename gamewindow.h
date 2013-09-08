#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QString>
#include <QList>
#include "qtquick2applicationviewer.h"

class GameWindow : public QtQuick2ApplicationViewer
{
    Q_OBJECT
public:
    GameWindow(QWindow *parent = 0);
    virtual ~GameWindow();

private slots:
    void logStatus(QQuickView::Status status);
    void handleSceneGraphInitialized();

private:
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // GAMEWINDOW_H
