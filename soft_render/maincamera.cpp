#include "maincamera.h"
#include "vector4.h"
#include "matrix.h"

maincamera::maincamera()
{
    pos = Vector3(0.0f, 1.0f, 3.0f);
    goal = Vector3(0, 0, 0);
    up = Vector3(0, 1, 0);
    fov = 45;
    asp = 8.f / 6;
    near = 0.1f;
    far = 5.f;
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