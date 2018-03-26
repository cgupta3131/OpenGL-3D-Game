#include "main.h"

#ifndef LAKE_H
#define LAKE_H


class Lake {
public:
    Lake() {}
    Lake(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    float length;
    float breadth;
    // float height;
private:
    VAO *object1;
};

#endif // LAKE_H
