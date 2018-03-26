#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
    float length;
    float breadth;
    float height;
    float accY;
    float speedY;
    float radius; 
    float length1;
    float health;
    float score; 
    float cannon_rotx ;
    float cannon_rotz ;
    int timer;
    int timer1;
    int boost;
    float noob;
    float angle;
    int timer2;
    long long angle1;

    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;

};

#endif // BOAT_H
