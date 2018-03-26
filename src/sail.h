#include "main.h"

#ifndef SAIL_H
#define SAIL_H

class Sail {
public:
    Sail() {}
    Sail(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick(float angle,int timer);
    float length;
    float height;
    float radius;
    int flag;
    int gift;
    int timer;
    float angle;
private:
    VAO *object;
   

};

#endif // SAIL_H



Sail::Sail(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    
    this->angle = 0.0;
    int parts = 15;

    GLfloat vertex_buffer_data[] = {
        0 ,0  , 0+ 0.55, 
        0 ,0  , 0+ 0.25, 
        0 ,-0.15, 0+ 0.25,
        
      };
    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data,{255,255,0}, GL_FILL);
   


}

void Sail::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,0 ,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

}

void Sail::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Sail::tick(float angle,int timer) {
    
    if(timer >= 480 && timer < 540)
    { 
      printf("HIII\n");
      this->rotation = angle + 315;
    }
    else
    {
      this->rotation = angle;
    }
}

