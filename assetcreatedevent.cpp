#include "assetcreatedevent.h"

const QEvent::Type AssetCreatedEvent::AssetCreatedType =
        static_cast<QEvent::Type>(QEvent::registerEventType());

AssetCreatedEvent::AssetCreatedEvent(AssetElementInterface *asset) :
    QEvent(AssetCreatedType),
    m_asset(asset)
{
}

AssetElementInterface *AssetCreatedEvent::asset() const
{
    return m_asset;
}


