#ifndef KEYBOARDCONTAINER_H
#define KEYBOARDCONTAINER_H

#include <QObject>
#include <QList>
#include <QVariant>
#include <QtDebug>

class KeyboardContainer : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariant enableKey READ   enableKey
               WRITE  setEnableKey
               NOTIFY enableKeyChanged)

public:
    // Your getter method must match the same return type :
    QVariant enableKey() const {
        return QVariant::fromValue(m_enableKey);
    }

public slots:
    // Your setter must put back the data from the QVariant to the QList<int>
    void setEnableKey (QVariant arg) {
        m_enableKey.clear();
        foreach (QVariant item, arg.toList()) {
            bool ok = false;
            int key = item.toInt(&ok);
            if (ok) {
                m_enableKey.append(key);
                qDebug() << key;
            }
        }
        emit enableKeyChanged ();
    }

signals:
    // you must have a signal named <property>Changed
    void enableKeyChanged();

private:
    // the private member can be QList<int> for convenience
    QList<int> m_enableKey;
};

#endif // KEYBOARDCONTAINER_H
