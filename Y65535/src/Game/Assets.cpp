#include "Assets.hpp"

#include <vector>

namespace {
    std::vector<Y65535::GenericShader::Vertex> bulletAVertices{
        #include "Assets/BulletA.blend.ipp"
    };

    std::vector<Y65535::GenericShader::Vertex> junkAVertices{
        #include "Assets/JunkA.blend.ipp"
    };

    std::vector<Y65535::GenericShader::Vertex> enemyAVertices{
        #include "Assets/EnemyA.blend.ipp"
    };
}

Y65535::Assets::Assets()
    : bulletA(bulletAVertices)
    , junkA(junkAVertices)
    , enemyA(enemyAVertices) {
}
