#pragma once
#include "vector4.h"

class Material
{
public:
    Material() = default;
    ~Material() = default;
    double shininess;
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    Vector3 reflect;
    void setMaterial(Vector3 amb, Vector3 diff, Vector3 spec, double shin)
    {
        shininess = shin;
        ambient = amb;
        diffuse = diff;
        specular = spec;
    }
};

class Light
{
public:
    Light() = default;
    virtual ~Light() = default;

    virtual void lighting(const Material& material,
        const Vector3& pos,
        const Vector3& normal,
        const Vector3& eyeDir,
        Vector3& amb,
        Vector3& diff,
        Vector3& spec) const = 0;
    virtual void setDirectLight(Vector3 amb, Vector3 diff, Vector3 spec,
        Vector3 dir) = 0;
    virtual void setSpotLight(Vector3 amb, Vector3 diff, Vector3 spec,
        double cut, Vector3 pos, Vector3 dir, Vector3 atte) = 0;
    virtual void setPointLight(Vector3 amb, Vector3 diff, Vector3 spec,
        Vector3 pos, Vector3 atte) = 0;
};
