#include "Assets.hpp"

#include <vector>

namespace {
    std::vector<Y65535::GenericShader::Vertex> bombVertices{
        #include "Assets/Bomb.blend.ipp"
    };

    std::vector<Y65535::GenericShader::Vertex> bulletAVertices{
        #include "Assets/BulletA.blend.ipp"
    };

    std::vector<Y65535::GenericShader::Vertex> enemyAVertices{
        #include "Assets/EnemyA.blend.ipp"
    };

    std::vector<Y65535::GenericShader::Vertex> junkAVertices{
        #include "Assets/JunkA.blend.ipp"
    };

    std::vector<Y65535::ParticleShader::Vertex> explosionAVertices{
        #include "Assets/ExplosionA.blend.ipp"
    };
}

Y65535::Assets::Assets()
    : bomb(bombVertices)
    , bulletA(bulletAVertices)
    , enemyA(enemyAVertices)
    , junkA(junkAVertices)

    , explosionA(explosionAVertices) {
}
