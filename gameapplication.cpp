#include "gameapplication.h"
#include "assetcreatedevent.h"

GameApplication::GameApplication(int &argc, char **argv)
    : QGuiApplication(argc, argv)
{
}


bool GameApplication::notify(QObject *object, QEvent *event)
{
    if(event->type() == AssetCreatedEvent::AssetCreatedType)
    {
        qDebug("notify override");

        event->ignore();
        bool ret = object->event(event);
        event->ignore();
        return false;
    }
    else
    {
        return QGuiApplication::notify(object, event);
    }
}
