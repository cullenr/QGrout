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
        bool accepted = false;
        QObject *receiver = object;

        do
        {
            accepted = receiver->event(event);
            receiver = receiver->parent();
        }
        while(receiver != nullptr || !accepted);

        return accepted;
    }
    else
    {
        return QGuiApplication::notify(object, event);
    }
}
