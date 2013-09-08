#include "gquickitem.h"
#include "assetcreatedevent.h"

GQuickItem::GQuickItem(QQuickItem *parent) :
    QQuickItem(parent)
{
}

bool GQuickItem::event(QEvent *event)
{
    if(event->type() == AssetCreatedEvent::AssetCreatedType)
    {
        return false;
    }

    return QObject::event(event);
}
