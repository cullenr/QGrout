#include <QCoreApplication>
#include "assetcreatedevent.h"
#include "abstractasset.h"

AbstractAsset::AbstractAsset(QObject *parent) :
    QObject(parent)
{
}

void AbstractAsset::classBegin()
{
    //not used
}

void AbstractAsset::componentComplete()
{
    //new asset gets deleted by the event system, not a leak!
    QCoreApplication::postEvent(parent(), new AssetCreatedEvent(this));
}
