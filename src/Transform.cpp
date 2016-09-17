// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using glm::mat4() or glm::mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
#include "libs/glm/mat3x3.hpp"

// Helper rotation function.  Please implement this.  
glm::mat3 Transform::rotate(const float degrees, const glm::vec3& axis)
{
    const double rads = glm::radians(degrees);
    const float sinTheta = sin(rads);
    const float cosTheta = cos(rads);
    const float x = axis.x;
    const float y = axis.y;
    const float z = axis.z;
    return cosTheta * glm::mat3()
        + (1 - cosTheta) * glm::mat3(x * x, x * y, x * z, y * x, y * y, y * z, z * x, z * y, z * z)
        + sinTheta * glm::mat3(0, z, -y, -z, 0, x, y, -x, 0);
}

void Transform::left(float degrees, glm::vec3& eye, glm::vec3& up)
{
    glm::mat3 rot = rotate(degrees, glm::normalize(up));
    eye = rot * eye;
    up = rot * up;
    up = upvector(up, eye);
}

void Transform::up(float degrees, glm::vec3& eye, glm::vec3& up)
{
    glm::vec3 cr = glm::normalize(glm::cross(eye, up));
    glm::mat3 rot = rotate(degrees, cr);
    eye = rot * eye;
    up = rot * up;
}

glm::mat4 Transform::lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up)
{
    const glm::vec3 w = glm::normalize(eye);
    const glm::vec3 u = glm::normalize(glm::cross(up, w));
    const glm::vec3 v = glm::cross(w, u);
    const glm::mat4 rot(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, 0, 0, 0, 1);
    const glm::mat4 trans(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -eye.x, -eye.y, -eye.z, 1);
    return rot * trans;
}

glm::mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    const float theta = glm::radians(fovy / 2.0);
    const float d = cos(theta) / sin(theta); // ctg(theta)
    const float A = -(zFar + zNear) / (zFar - zNear);
    const float B = -2 * zNear * zFar / (zFar - zNear);
    return glm::mat4(
        d / aspect, 0, 0, 0,
        0, d, 0, 0,
        0, 0, A, -1,
        0, 0, B, 0
        );
}

glm::mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
    return glm::mat4(
        sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1
        );
}

glm::mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
    return glm::mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        tx, ty, tz, 1
        );
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

glm::vec3 Transform::upvector(const glm::vec3 &up, const glm::vec3 & zvec)
{
    glm::vec3 x = glm::cross(up, zvec);
    glm::vec3 y = glm::cross(zvec, x);
    glm::vec3 ret = glm::normalize(y);
    return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
