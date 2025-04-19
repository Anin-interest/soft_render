#include "directlight.h"

void DirectLight::lighting(const Material& material,
    const Vector3& pos,
    const Vector3& normal,
    const Vector3& eyeDir,
    Vector3& amb,
    Vector3& diff,
    Vector3& spec) const
{
    float t_diff = max(normal.dot(-direction), 0.0f);
    Vector3 halfwayDir = eyeDir + direction;
    halfwayDir.normalize();
    float t_spec = pow(max(eyeDir.dot(halfwayDir), 0.0f), material.shininess);
    amb = ambient;
    diff = diffuse * t_diff;
    spec = specular * t_spec;
}