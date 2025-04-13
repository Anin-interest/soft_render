#pragma once
#include"vector3.h"

class maincamera
{
public:
    Vector3 pos, goal, up;
    float fov, asp, near, far;
public:
    maincamera();
    maincamera(Vector3 mpos, Vector3 mgoal, Vector3 mup, float mfov, float masp, float mnear, float mfar);
    void rotateY(float angle);
};

