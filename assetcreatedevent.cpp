#include "assetcreatedevent.h"

const QEvent::Type AssetCreatedEvent::AssetCreatedType =
        static_cast<QEvent::Type>(QEvent::registerEventType());

AssetCreatedEvent::AssetCreatedEvent() :
    QEvent(AssetCreatedType)
{
}
