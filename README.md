#QGrout

QGrout is a Tile Game framework written in C++ for Qt 5.1 with QML bindings. The goal of the project
 is to allow users to define a game entirely in QML.

##Overview

The QGrout engine provides an OpenGl based rendering system and Box2d based physics simulation as
 well as object lifecycle management.

The game engine manages objects through the `Scene` class. There are two types of object that can be
 managed by a `Scene`, these are `Asset` objects and `SceneElement`s. Both of these types of objects
 should be data models with no logic in them except that to expose thier members to the QML engine.
 Controllers are implemented using the visitor pattern. The `Scene` will apply the appropriate
 visitor when necesary.


    ISceneElement
    ========================================
    + virtual void accept(SceneElementVisitor &);
    |
    +-> AbstractGameObject : QObject, ISceneElement, QQmlParserStatus
        ========================================
        + "QQmlParserStatus definitions"
        + Vector2D transform;
        |
        +-> Actor : AbstractGameObject
        |   ========================================
        |   + void accept(SceneElementVisitor) override;
        |   + QVector<Component *> components;
        |
        +-> Light : AbstractGameObject
        |   ========================================
        |   + float radius() const;
        |   ...
        |
        ...


    IAssetElement
    ========================================
    + virtual void accept(AssetElementVisitor)
    |
    +-> AbstractAsset : QObject, IAssetElement, QQmlParserStatus
        ========================================
        + "QQmlParserStatus definitions"
        |
        +-> TextureAsset : AbstractAsset
        |   ========================================
        |   + QString path;
        |
        +-> ShaderAsset : AbstractAsset
        |   ========================================
        |   + QString fragmentSourcePath
        |   + QString vertexSourcePath
        |
        ...
