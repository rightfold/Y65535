#pragma once

// The order of these includes is important. That's all I know.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace glm {
    /// Build a look at quaternion based on the default handedness.
    ///
    /// @param direction Desired direction of the camera.
    /// @param up Up vector, how the camera is oriented. Typically (0, 1, 0).
    template<typename T, precision P>
    GLM_FUNC_DECL tquat<T, P> quatLookAt(
        tvec3<T, P> const & direction,
        tvec3<T, P> const & up);

    /// Build a right-handed look at quaternion.
    ///
    /// @param direction Desired direction of the camera.
    /// @param up Up vector, how the camera is oriented. Typically (0, 1, 0).
    template<typename T, precision P>
    GLM_FUNC_DECL tquat<T, P> quatLookAtRH(
        tvec3<T, P> const & direction,
        tvec3<T, P> const & up);

    /// Build a left-handed look at quaternion.
    ///
    /// @param eye Position of the camera
    /// @param direction Desired direction onto which the +z-axis gets mapped
    /// @param up Up vector, how the camera is oriented. Typically (0, 1, 0).
    template<typename T, precision P>
    GLM_FUNC_DECL tquat<T, P> quatLookAtLH(
        tvec3<T, P> const & direction,
        tvec3<T, P> const & up);
}

namespace glm {
    template<typename T, precision P>
    GLM_FUNC_QUALIFIER tquat<T, P> quatLookAt(tvec3<T, P> const& direction, tvec3<T, P> const& up)
    {
#        if GLM_COORDINATE_SYSTEM == GLM_LEFT_HANDED
            return quatLookAtLH(direction, up);
#        else
            return quatLookAtRH(direction, up);
#         endif
    }

    template<typename T, precision P>
    GLM_FUNC_QUALIFIER tquat<T, P> quatLookAtRH(tvec3<T, P> const& direction, tvec3<T, P> const& up)
    {
        tmat3x3<T, P> Result(uninitialize);

        Result[2] = -normalize(direction);
        Result[0] = normalize(cross(up, Result[2]));
        Result[1] = cross(Result[2], Result[0]);

        return quat_cast(Result);
    }

    template<typename T, precision P>
    GLM_FUNC_QUALIFIER tquat<T, P> quatLookAtLH(tvec3<T, P> const& direction, tvec3<T, P> const& up)
    {
        tmat3x3<T, P> Result(uninitialize);

        Result[2] = normalize(direction);
        Result[0] = normalize(cross(up, Result[2]));
        Result[1] = cross(Result[2], Result[0]);

        return quat_cast(Result);
    }
}

namespace Y65535 {
    struct Sphere {
        glm::vec3 position;
        float radius;
    };

    inline
    bool Intersect(Sphere a, Sphere b) {
        return glm::distance2(a.position, b.position)
                   < glm::distance2(a.radius, b.radius);
    }
}
