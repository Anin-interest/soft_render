#pragma once
#include "polygon.h"
#include "matrix.h"
#include <QString>

class ObjModel : public Mesh
{
private:
    Vector3 minPoint, maxPoint;

public:
    // ctor/dtor.
    ObjModel(const QString &path);
    virtual ~ObjModel();

    // Size setting.
    Vector3 setSizeToVector(float sx, float sy, float sz) const;
    Matrix setSizeToMatrix(float sx, float sy, float sz) const;

private:
    // Obj file loader.
    void loadObjFile(const QString& path);
};

