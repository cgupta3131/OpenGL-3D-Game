#include "main.h"

#ifndef OBSTACLE_H
#define OBSTACLE_H


class Obstacle {
public:
    Obstacle() {}
    Obstacle(float x, float y, float z,int a);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    float length;
    float breadth;
    float height;
    float radius;
    int ab;
    int flag;
    // float height;
private:
    VAO *object;
    VAO *object1;

};

#endif // OBSTACLE_H
