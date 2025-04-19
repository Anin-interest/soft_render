#include "spotlight.h"

void SpotLight::lighting(const Material& material,
    const Vector3& pos,
    const Vector3& normal,
    const Vector3& eyeDir,
    Vector3& amb,
    Vector3& diff,
    Vector3& spec) const
{
    // ambient
    amb = ambient;

    // diffuse
    Vector3 lightDir = position - pos;
    lightDir.normalize();
    float t_diff = max(normal.dot(lightDir), 0.0f);
    diff = diffuse * t_diff;

    // specular
    Vector3 halfwayDir = eyeDir + lightDir;
    halfwayDir.normalize();
    float t_spec = pow(max(eyeDir.dot(halfwayDir), 0.0f), material.shininess);
    spec = specular * t_spec;

    // spotlight (soft edges)
    float theta = lightDir.dot(-direction);
    float epsilon = (cutoff - outcutoff);
    float intensity = (theta - outcutoff) / epsilon;
    if (intensity < 0.0f)intensity = 0.0f;
    if (intensity > 1.0f)intensity = 1.0f;
    diff *= intensity;
    spec *= intensity;

    // attenuation
    float distance = (position - pos).length();
    float attenuated = 1.0 / (
        attenuation.x +
        attenuation.y * distance +
        attenuation.z * (distance * distance));
    amb *= attenuated;
    diff *= attenuated;
    spec *= attenuated;
}