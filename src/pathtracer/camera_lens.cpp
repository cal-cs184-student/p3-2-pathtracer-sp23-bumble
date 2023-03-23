#include "camera.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "CGL/misc.h"
#include "CGL/vector2D.h"
#include "CGL/vector3D.h"

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::ifstream;
using std::ofstream;

namespace CGL {

using Collada::CameraInfo;

Ray Camera::generate_ray_for_thin_lens(double x, double y, double rndR, double rndTheta) const {

    // TODO Project 3-2: Part 4
    // compute position and direction of ray from the input sensor sample coordinate.
    // Note: use rndR and rndTheta to uniformly sample a unit disk.
    double xTransform = x * tan(.5 * radians(hFov)) + (x - 1) * tan(.5 * radians(hFov));
    double yTransform = y * tan(.5 * radians(vFov)) + (y - 1) * tan(.5 * radians(vFov));

    Vector3D p_lens = Vector3D(lensRadius * sqrt(rndR) * cos(rndTheta), lensRadius * sqrt(rndR) * sin(rndTheta), 0);
    Vector3D p_focus = Vector3D(xTransform * focalDistance, yTransform * focalDistance, -focalDistance);
    Vector3D direction = p_focus - p_lens;
    direction = c2w * direction;
    direction.normalize();
    p_lens = c2w * p_lens;
    p_lens += pos;

    Ray ray = Ray(p_lens, direction);
    ray.min_t = nClip;
    ray.max_t = fClip;

    return ray;
}


} // namespace CGL
