#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include <QGuiApplication>

class GameApplication : public QGuiApplication
{
public:
    GameApplication(int &argc, char **argv);

    bool notify(QObject * object, QEvent * event) override;
};

#endif // GAMEAPPLICATION_H
