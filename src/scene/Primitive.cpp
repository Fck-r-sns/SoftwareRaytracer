#include "Primitive.h"

Primitive::Primitive(int materialIndex, const glm::mat4 &transform) :
    materialIndex(materialIndex),
    transform(transform)
{
}

Primitive::~Primitive()
{

}
