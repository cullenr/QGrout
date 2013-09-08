#include "assetinitialisationvisitor.h"
#include "textureasset.h"
#include "shaderasset.h"
#include <QGLWidget>
#include <QDebug>
#include <QOpenGLShaderProgram>

AssetInitialisationVisitor::AssetInitialisationVisitor()
{
}

void AssetInitialisationVisitor::visit(ShaderAsset &shader)
{
    setlocale(LC_NUMERIC, "C");

    if (!shader.compile())
    {
        qWarning() << shader.shader()->log();
    }
    setlocale(LC_ALL, "");
}

void AssetInitialisationVisitor::visit(TextureAsset &texture)
{
    QImage qtImage;
    QImage glImage;
    GLuint textureId = 0;

    if (!qtImage.load(texture.texturePath()))
    {
        qDebug() << texture.texturePath() << "not found";

        qtImage = QImage( 16, 16, QImage::Format_RGB32 );
        qtImage.fill( 1 );
    }

    glImage = QGLWidget::convertToGLFormat(qtImage.mirrored());
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, glImage.width(), glImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, glImage.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    texture.setGlTextureId(textureId);
}
