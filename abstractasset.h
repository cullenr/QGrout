#ifndef ABSTRACTASSET_H
#define ABSTRACTASSET_H

#include <QtQml/QQmlParserStatus>
#include <QtCore/QObject>
#include "assetelementinterface.h"

class AssetVisitor;

class AbstractAsset :
        public QObject,
        public QQmlParserStatus,
        public AssetElementInterface
{
    Q_OBJECT
public:
    explicit AbstractAsset(QObject *parent = 0);

    virtual void classBegin() override;
    virtual void componentComplete() override;
};

#endif // ABSTRACTASSET_H
