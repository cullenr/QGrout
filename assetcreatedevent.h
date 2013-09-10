#ifndef ASSETCREATEDEVENT_H
#define ASSETCREATEDEVENT_H

#include <QEvent>

class AbstractAsset;

class AssetCreatedEvent : public QEvent
{
public:
    explicit AssetCreatedEvent(AbstractAsset *asset);

    static const QEvent::Type AssetCreatedType;

    AbstractAsset *asset() const;
private:
    AbstractAsset *m_asset;
};

#endif // ASSETCREATEDEVENT_H
