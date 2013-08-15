#include "material.h"

Material::Material(QObject *parent) :
    QObject(parent),
    m_shader(0),
    m_texture(0)
{
}

ShaderAsset * Material::shader() const
{
    return m_shader;
}

TextureAsset * Material::texture() const
{
    return m_texture;
}
