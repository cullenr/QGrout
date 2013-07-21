#ifndef SHADERASSET_H
#define SHADERASSET_H

#include <QObject>

class ShaderAsset : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString fragmentShaderPath MEMBER fragmentShaderPath);
    Q_PROPERTY(QString vertexShaderPath MEMBER vertexShaderPath);

public:
    explicit ShaderAsset(QObject *parent = 0);

    QString fragmentShaderPath;
    QString vertexShaderPath;
};


#endif // SHADERASSET_H
