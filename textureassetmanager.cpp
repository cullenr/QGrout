#include "textureassetmanager.h"
#include <QSGTexture>
#include <QImage>
#include <QGLWidget>

TextureAssetManager::TextureAssetManager(QObject *parent) :
    QObject(parent)
{
}

TextureAssetManager::~TextureAssetManager()
{
    for(TextureAsset *textureAsset : m_textureSources)
    {
        //TODO: CLEANUP!
    }
}

void TextureAssetManager::loadTextures(QQuickWindow *window)
{
    for(int i = 0; i < m_textureSources.length(); i++)
    {
        TextureAsset *textureAsset = m_textureSources[i];
//        QSGTexture *texture = window->createTextureFromImage(QImage(m_textureSources[i]->texturePath()));// TODO profile this, is this a leak or an r-value?

//        textureAsset->setTexture(texture);

        QImage t;
        QImage b;

        if ( !b.load( m_textureSources[i]->texturePath() ) )
        {
            qDebug("Didn't found the image.");
            b = QImage( 16, 16, QImage::Format_RGB32 );
            b.fill( 1 );
        }

        GLuint textureId = 0;

        t = QGLWidget::convertToGLFormat( b.mirrored() );
        glGenTextures( 1, &textureId );
        glBindTexture( GL_TEXTURE_2D, textureId );
        glTexImage2D( GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits() );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        textureAsset->setGlTextureId(textureId);
    }
}

QQmlListProperty<TextureAsset> TextureAssetManager::m_textureSourcesQmlList()
{
    return QQmlListProperty<TextureAsset>(this, m_textureSources);
}
