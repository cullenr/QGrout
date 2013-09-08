#ifndef ABSTRACTASSET_H
#define ABSTRACTASSET_H

#include <QQmlParserStatus>

class AssetVisitor;

///
/// \brief The AbstractAsset should be an abstract class however the constraints of the
/// qt framework prevent this. This interface should be implemented on all assets that
/// need to be processed by the AssetVisitor interfaced classes. The following code must
/// be implemented in some way.
///
/// \code
/// void MyAsset::componentComplete()
/// {
///    //new asset gets deleted by the event system
///    QCoreApplication::postEvent(parent(), new AssetCreatedEvent());
/// }
/// \endcode
///
/// note the call to parent(), this needs to be called from a QObject, inheriting QObject
/// here will stop child classes being able to implement macros, and QObjects are not
/// compatible with template programming.
///
class AbstractAsset : public QQmlParserStatus
{
    virtual void accept(AssetVisitor &visitor) = 0;
};

#endif // ABSTRACTASSET_H
