#pragma once
#include "mesh.h"
#include "matrix.h"
#include <QString>

class ObjModel : public Mesh
{
private:
    Vector3 minPoint, maxPoint;

public:
    ObjModel(const QString &path);
    virtual ~ObjModel();

private:
    void loadObjFile(const QString& path);
};

