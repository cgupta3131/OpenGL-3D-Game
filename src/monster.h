#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H

const color_t DARKBLUE = {25, 25, 112};
const color_t SILVER = {169, 169, 169};
class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    float length;
    float height;
    float radius;
    float breadth;
    int flag;
    int gift;
    int flag1;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    
};

#endif // MONSTER_H



Monster::Monster(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->length = 0.9;
    this->height = 0.6;
    this->radius =1;
    this->flag = 1;
    this->breadth = 0.9;
    this->flag1 = 0;
    int parts = 15;

    
    int j;
    float angle=(2*M_PI/parts);
    float current_angle = 0;
    GLfloat vertex_buffer_data1[parts*9] ;
    
    current_angle = 0;
    for(j=0;j<parts;j++){
      

      vertex_buffer_data1[j*9]    = 0;
      vertex_buffer_data1[j*9+1]  = 0;
      vertex_buffer_data1[j*9+2]  = this->height;
      vertex_buffer_data1[j*9+3]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data1[j*9+4]  = this->radius*sin(current_angle + angle);
      vertex_buffer_data1[j*9+5]  = this->height;
      vertex_buffer_data1[j*9+6]  = this->radius*cos(current_angle);
      vertex_buffer_data1[j*9+7]  = this->radius*sin(current_angle);
      vertex_buffer_data1[j*9+8]  = this->height;

      current_angle+=angle;
    }
   
    
    
    GLfloat vertex_buffer_data[] = {
      0 - this->breadth/2 ,0 - this->length/2,0, //2
      0 - this->breadth/2 ,0 + this->length/2,0, //4
      0,0,0 + this->height, // 9

      0 - this->breadth/2 ,0 + this->length/2,0, //4
      0,0,0 + this->height, // 9
      0 + this->breadth/2 ,0 + this->length/2,0, //5

      0 + this->breadth/2 ,0 + this->length/2,0, //5
      0,0,0 + this->height, // 9
      0 + this->breadth/2 ,0 - this->length/2 ,0 , //8

      0 + this->breadth/2 ,0 - this->length/2,0, //8
      0,0,0 + this->height , // 9
      0 - this->breadth/2,0 - this->length/2 ,0, //2

    };
    GLfloat vertex_buffer_data2[] = {
      0 - this->breadth/2 ,0 - this->length/2,2*this->height, //2
      0 - this->breadth/2 ,0 + this->length/2,2*this->height, //4
      0,0,0 + this->height, // 9

      0 - this->breadth/2 ,0 + this->length/2,2*this->height, //4
      0,0,0 + this->height, // 9
      0 + this->breadth/2 ,0 + this->length/2,2*this->height, //5

      0 + this->breadth/2 ,0 + this->length/2,2*this->height, //5
      0,0,0 + this->height, // 9
      0 + this->breadth/2 ,0 - this->length/2 ,2*this->height, //8

      0 + this->breadth/2 ,0 - this->length/2,2*this->height, //8
      0,0,0 + this->height , // 9
      0 - this->breadth/2,0 - this->length/2 ,2*this->height, //2

    };
     GLfloat vertex_buffer_data3[] = {
      0 - this->breadth/2 + 0.3,0 - this->length/2 + 0.50,0 + this->height, //2
      0 - this->breadth/2 + 0.3,0 + this->length/2 - 0.50,0 + this->height, //4
      0,0,0 + this->height + 0.25, // 9

      0 - this->breadth/2 + 0.3,0 + this->length/2 - 0.50,0 + this->height, //4
      0,0,0 + this->height + 0.25, // 9
      0 + this->breadth/2 - 0.4,0 + this->length/2 - 0.50,0 + this->height, //5

      0 + this->breadth/2 - 0.3,0 + this->length/2 - 0.50,0 + this->height, //5
      0,0,0 + this->height + 0.25, // 9
      0 + this->breadth/2 - 0.3,0 - this->length/2 + 0.50,0 + this->height, //8

      0 + this->breadth/2 - 0.3,0 - this->length/2 + 0.50,0 + this->height, //8
      0,0,0 + this->height + 0.25, // 9
      0 - this->breadth/2 + 0.3,0 - this->length/2 + 0.50,0 + this->height, //2
    };
    GLfloat vertex_buffer_data4[] = {
      0 - this->breadth/2 + 0.3,0 - this->length/2 + 0.50,0 + this->height, //2
      0 - this->breadth/2 + 0.3,0 + this->length/2 - 0.50,0 + this->height, //4
      0,0,0 + this->height - 0.25, // 9

      0 - this->breadth/2 + 0.3,0 + this->length/2 - 0.50,0 + this->height, //4
      0,0,0 + this->height - 0.25, // 9
      0 + this->breadth/2 - 0.3,0 + this->length/2 - 0.50,0 + this->height, //5

      0 + this->breadth/2 - 0.3,0 + this->length/2 - 0.50,0 + this->height, //5
      0,0,0 + this->height - 0.25, // 9
      0 + this->breadth/2 - 0.3,0 - this->length/2 + 0.50,0 + this->height, //8

      0 + this->breadth/2 - 0.3,0 - this->length/2 + 0.50,0 + this->height, //8
      0,0,0 + this->height - 0.25, // 9
      0 - this->breadth/2 + 0.3,0 - this->length/2 + 0.50,0 + this->height, //2
    };
    

    this->object = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, SILVER, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, parts*3, vertex_buffer_data1, DARKBLUE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data2, SILVER, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES,12, vertex_buffer_data3, {210, 105, 30}, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES,12, vertex_buffer_data4, {210, 105, 30}, GL_FILL);


}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,0 ,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->flag == 1)
    { 
      draw3DObject(this->object);
      draw3DObject(this->object1);
      draw3DObject(this->object2);
    }
    if(this->flag1 == 1)
    {
      draw3DObject(this->object3);
      draw3DObject(this->object4);
    }
}

void Monster::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Monster::tick() {
    
    this->rotation += 5;

}

