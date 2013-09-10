#include <QtCore/QCoreApplication>
#include "assetcreatedevent.h"
#include "abstractasset.h"

AbstractAsset::AbstractAsset(QObject *parent) :
    QObject(parent)
{
}

void AbstractAsset::classBegin()
{
    //new asset gets deleted by the event system, not a leak!
    QCoreApplication::postEvent(parent(), new AssetCreatedEvent(this));
}

void AbstractAsset::componentComplete()
{
    //not used
}
