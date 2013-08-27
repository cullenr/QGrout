#ifndef ASSETCREATEDEVENT_H
#define ASSETCREATEDEVENT_H

#include <QEvent>

class AssetCreatedEvent : public QEvent
{
public:
    explicit AssetCreatedEvent();

    static const QEvent::Type AssetCreatedType;
};

#endif // ASSETCREATEDEVENT_H
