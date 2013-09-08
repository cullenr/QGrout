#ifndef GQUICKITEM_H
#define GQUICKITEM_H

#include <QQuickItem>

class GQuickItem : public QQuickItem
{
    Q_OBJECT
public:
    explicit GQuickItem(QQuickItem *parent = 0);

    virtual bool event(QEvent *event) override;
};

#endif // GQUICKITEM_H
