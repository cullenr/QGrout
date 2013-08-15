#ifndef GENERICMANAGER_H
#define GENERICMANAGER_H

#include <QObject>
#include <QHash>
#include <QString>
#include <QQmlListProperty>

template <class Source, class Asset> class GenericManager
{
public:
    GenericManager();

    const Asset *asset(const QString &name) const;

signals:
    void sourcesUpdated(QList<Source *> sources);

protected:
    QQmlListProperty<Source> sourcesQmlList();

    QList<Source *> m_sources;
    QHash<QString, Asset *> m_assets;
};

#endif // GENERICMANAGER_H
