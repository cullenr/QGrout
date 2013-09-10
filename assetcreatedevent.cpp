#include "assetcreatedevent.h"

const QEvent::Type AssetCreatedEvent::AssetCreatedType =
        static_cast<QEvent::Type>(QEvent::registerEventType());

AssetCreatedEvent::AssetCreatedEvent(AbstractAsset *asset) :
    QEvent(AssetCreatedType),
    m_asset(asset)
{
}

AbstractAsset *AssetCreatedEvent::asset() const
{
    return m_asset;
}


