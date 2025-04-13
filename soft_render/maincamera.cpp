#include "maincamera.h"
#include "vector4.h"
#include "matrix.h"
#include "stdio.h"

maincamera::maincamera()
{
    pos = Vector3(0, 8, 0);
    goal = Vector3(0, 0, 0);
    up = Vector3(0, 0, -1);
    fov = 60;
    asp = 8.f / 6;
    near = 1.f;
    far = 50.f;
}
maincamera::maincamera(Vector3 mpos, Vector3 mgoal, Vector3 mup, float mfov, float masp, float mnear, float mfar)
{
    pos = mpos;
    goal = mgoal;
    up = mup;
    fov = mfov;
    asp = masp;
    near = mnear;
    far = mfar;
}

void maincamera::rotateY(float angle)
{
    Vector4 tpos(pos);
    Matrix rot;
    rot.normalize();
    rot.rotationY(angle);
    tpos = rot * tpos;
	pos.x = tpos.x;
	pos.y = tpos.y;
	pos.z = tpos.z;
}