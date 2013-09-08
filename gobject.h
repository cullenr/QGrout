#ifndef GOBJECT_H
#define GOBJECT_H

#include <QObject>
/*!
 * \brief The \c GObject should be considered where one might use a \c QObject
 *
 * \c GObjects are typically used instead of \c QObjects for items that will be
 * defined in QML files.
 *
 * \c GObjects propogate Grout events upwards whereas \c QObjects do not without
 * modification. If there is a posibility of a class becoming a parent of a class
 * that dispatches Grout events then consider using \c GObject as a base.
 */
class GObject : public QObject
{
    Q_OBJECT
public:
    explicit GObject(QObject *parent = 0);

    virtual bool event(QEvent *) override;

};

#endif // GOBJECT_H
