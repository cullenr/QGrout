#ifndef ASSETCREATEDEVENT_H
#define ASSETCREATEDEVENT_H

#include <QEvent>

class AssetElementInterface;

class AssetCreatedEvent : public QEvent
{
public:
    explicit AssetCreatedEvent(AssetElementInterface *asset);

    static const QEvent::Type AssetCreatedType;

    AssetElementInterface *asset() const;
private:
    AssetElementInterface *m_asset;
};

#endif // ASSETCREATEDEVENT_H
