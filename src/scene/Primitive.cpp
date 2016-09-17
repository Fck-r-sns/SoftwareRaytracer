#include "Primitive.h"

Primitive::Primitive(int materialIndex, const glm::mat4 &inversedTransform) :
    materialIndex(materialIndex),
    inversedTransform(inversedTransform)
{
}

Primitive::~Primitive()
{

}
