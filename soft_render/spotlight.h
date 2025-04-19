#pragma once
#include "light.h"

class SpotLight : public Light
{
public:
    double cutoff, outcutoff;
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    Vector3 position;
    Vector3 direction;
    Vector3 attenuation;

    virtual void lighting(const Material& material,
        const Vector3& pos,
        const Vector3& normal,
        const Vector3& eyeDir,
        Vector3& ambient,
        Vector3& diffuse,
        Vector3& specular) const;
    virtual void setDirectLight(Vector3 amb, Vector3 diff, Vector3 spec,
        Vector3 dir) {
    }
    virtual void setPointLight(Vector3 amb, Vector3 diff, Vector3 spec,
        Vector3 pos, Vector3 atte) {
    }

    void setSpotLight(Vector3 amb, Vector3 diff, Vector3 spec,
        double cut, Vector3 pos, Vector3 dir, Vector3 atte)
    {
        cutoff = cos(cut * PI / 180.0);
        outcutoff = cos((cut + 10.0) * PI / 180.0);
        ambient = amb;
        diffuse = diff;
        specular = spec;
        position = pos;
        direction = dir;
        attenuation = atte;
        direction.normalize();
    }
};

