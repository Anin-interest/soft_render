#pragma once
#include "light.h"

class PointLight : public Light
{
public:
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    Vector3 position;
    Vector3 attenuation;

    virtual void lighting(const Material& material,
        const Vector3& pos,
        const Vector3& normal,
        const Vector3& eyeDir,
        Vector3& amb,
        Vector3& diff,
        Vector3& spec) const;
    virtual void setDirectLight(Vector3 amb, Vector3 diff, Vector3 spec,
        Vector3 dir) {
    }
    virtual void setSpotLight(Vector3 amb, Vector3 diff, Vector3 spec,
        double cut, Vector3 pos, Vector3 dir, Vector3 atte) {
    }

    void setPointLight(Vector3 amb, Vector3 diff, Vector3 spec,
        Vector3 pos, Vector3 atte)
    {
        ambient = amb;
        diffuse = diff;
        specular = spec;
        position = pos;
        attenuation = atte;
    }
};
