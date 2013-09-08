#include "gobject.h"
#include "assetcreatedevent.h"

GObject::GObject(QObject *parent) :
    QObject(parent)
{
}


bool GObject::event(QEvent *event)
{
    if(event->type() == AssetCreatedEvent::AssetCreatedType)
    {
        //propogate event by default
        return false;
    }

    return QObject::event(event);
}
