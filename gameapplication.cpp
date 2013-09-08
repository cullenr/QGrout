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

        bool out = object->event(event);
        return out;
    }
    else
    {
        return QGuiApplication::notify(object, event);
    }
}
