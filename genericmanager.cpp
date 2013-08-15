#include "genericmanager.h"

template <class Source, class Asset>
GenericManager<Source, Asset>::GenericManager()
{
}

template <class Source, class Asset>
const Asset* GenericManager<Source, Asset>::asset(const QString &name) const
{
    return m_assets[name];
}

template <class Source, class Asset>
QQmlListProperty<Source> GenericManager<Source, Asset>::sourcesQmlList()
{
    return QQmlListProperty<Source>(this, m_sources);
}



//QList<Source *> m_sources;
//QQmlListProperty<Source> m_sourcesQmlList();
//QHash<QString, Asset *> m_assets;

