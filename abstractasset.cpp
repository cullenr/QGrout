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
    QCoreApplication::postEvent(parent(), new AssetCreatedEvent(this));
}

void AbstractAsset::componentComplete()
{
    //new asset gets deleted by the event system, not a leak!

}
