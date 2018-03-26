#include "main.h"

#ifndef BOSS_H
#define BOSS_H

class Boss {
public:
    Boss() {}
    Boss(float x, float y, float z);
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
    int score;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    
};

#endif // BOSS_H



Boss::Boss(float x, float y, float z) {
    this->position = glm::vec3(x, y, z - 0.8);
    this->rotation = 0;
    this->length = 3;
    this->height = 0.8*2;
    this->radius =0.5;
    this->flag = 1;
    this->breadth =3;
    this->score = 1500;
    int parts = 15;

    
    int j;
    float angle=(2*M_PI/parts);
    float current_angle = 0;
    GLfloat vertex_buffer_data[parts*18] ;
    GLfloat vertex_buffer_data1[parts*18] ;
    GLfloat vertex_buffer_data2[parts*18] ;
    GLfloat vertex_buffer_data3[parts*18] ;
    
    current_angle = 0;
    GLfloat vertex_buffer_data4[] =  {
      -this->breadth/2,-this->length/2,-this->height, //1
      -this->breadth/2,-this->length/2,this->height, //2
      -this->breadth/2,this->length/2,-this->height, //3
      -this->breadth/2,this->length/2,-this->height, //3
      -this->breadth/2,-this->length/2,this->height,//2
      -this->breadth/2,this->length/2,this->height, //4

      -this->breadth/2,this->length/2 ,-this->height, //3
      -this->breadth/2,this->length/2,this->height, //4
      this->breadth/2,this->length/2,this->height, //5
      -this->breadth/2,this->length/2 ,-this->height , //3
      this->breadth/2,this->length/2,this->height, //5
      this->breadth/2,this->length/2,-this->height, //6

      this->breadth/2,this->length/2,this->height, //5
      this->breadth/2,this->length/2,-this->height, //6
      this->breadth/2,-this->length/2,-this->height, //7
      this->breadth/2,this->length/2,this->height, //5
      this->breadth/2,-this->length/2,-this->height, //7
      this->breadth/2,-this->length/2,this->height, //8

      -this->breadth/2,-this->length/2,-this->height, //1
      -this->breadth/2,-this->length/2,this->height, //2
      this->breadth/2,-this->length/2,-this->height, //7
      -this->breadth/2,-this->length/2,this->height, //2
      this->breadth/2,-this->length/2,-this->height, //7
      this->breadth/2,-this->length/2,this->height, //8

      -this->breadth/2,-this->length/2,-this->height, //1
      -this->breadth/2,this->length/2,-this->height, //3
      this->breadth/2,this->length/2,-this->height, //6
      -this->breadth/2,-this->length/2,-this->height, //1
      this->breadth/2,this->length/2,-this->height, //6
      this->breadth/2,-this->length/2,-this->height, //7


    };
    for(j=0;j<parts;j++){
      
      vertex_buffer_data[j*18]    = this->radius*cos(current_angle);
      vertex_buffer_data[j*18+1]  = -this->length/2;
      vertex_buffer_data[j*18+2]  = this->radius*sin(current_angle) + this->height/2;
      vertex_buffer_data[j*18+3]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data[j*18+4]  = -this->length/2;
      vertex_buffer_data[j*18+5]  = this->radius*sin(current_angle + angle) + this->height/2 ;
      vertex_buffer_data[j*18+6]  = this->radius*cos(current_angle);
      vertex_buffer_data[j*18+7]  = -this->length - this->length/2;
      vertex_buffer_data[j*18+8]  = this->radius*sin(current_angle) + this->height/2;

      vertex_buffer_data[j*18+9]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data[j*18+10] = -this->length/2 ;
      vertex_buffer_data[j*18+11] = this->radius*sin(current_angle + angle) + this->height/2;
      vertex_buffer_data[j*18+12] = this->radius*cos(current_angle + angle);
      vertex_buffer_data[j*18+13] = -this->length - this->length/2;
      vertex_buffer_data[j*18+14] = this->radius*sin(current_angle + angle) + this->height/2;
      vertex_buffer_data[j*18+15] = this->radius*cos(current_angle);
      vertex_buffer_data[j*18+16] = -this->length - this->length/2;
      vertex_buffer_data[j*18+17] = this->radius*sin(current_angle) + this->height/2;

      vertex_buffer_data1[j*18]    = this->radius*cos(current_angle);
      vertex_buffer_data1[j*18+1]  = this->length/2;
      vertex_buffer_data1[j*18+2]  = this->radius*sin(current_angle) + this->height/2;
      vertex_buffer_data1[j*18+3]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data1[j*18+4]  = this->length/2;
      vertex_buffer_data1[j*18+5]  = this->radius*sin(current_angle + angle) + this->height/2 ;
      vertex_buffer_data1[j*18+6]  = this->radius*cos(current_angle);
      vertex_buffer_data1[j*18+7]  = this->length + this->length/2;
      vertex_buffer_data1[j*18+8]  = this->radius*sin(current_angle) + this->height/2;

      vertex_buffer_data1[j*18+9]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data1[j*18+10] = this->length/2 ;
      vertex_buffer_data1[j*18+11] = this->radius*sin(current_angle + angle) + this->height/2;
      vertex_buffer_data1[j*18+12] = this->radius*cos(current_angle + angle);
      vertex_buffer_data1[j*18+13] = this->length + this->length/2;
      vertex_buffer_data1[j*18+14] = this->radius*sin(current_angle + angle) + this->height/2;
      vertex_buffer_data1[j*18+15] = this->radius*cos(current_angle);
      vertex_buffer_data1[j*18+16] = this->length + this->length/2;
      vertex_buffer_data1[j*18+17] = this->radius*sin(current_angle) + this->height/2;

      vertex_buffer_data2[j*18]    = -this->breadth/2;
      vertex_buffer_data2[j*18+1]  = this->radius*cos(current_angle);
      vertex_buffer_data2[j*18+2]  = this->radius*sin(current_angle) + this->height/2;
      vertex_buffer_data2[j*18+3]  = -this->breadth/2;
      vertex_buffer_data2[j*18+4]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data2[j*18+5]  = this->radius*sin(current_angle + angle) + this->height/2 ;
      vertex_buffer_data2[j*18+6]  = -this->breadth/2 - this->breadth/2;
      vertex_buffer_data2[j*18+7]  = this->radius*cos(current_angle);
      vertex_buffer_data2[j*18+8]  = this->radius*sin(current_angle) + this->height/2;

      vertex_buffer_data2[j*18+9]  = -this->breadth/2 ;
      vertex_buffer_data2[j*18+10] = this->radius*cos(current_angle + angle);
      vertex_buffer_data2[j*18+11] = this->radius*sin(current_angle + angle) + this->height/2;
      vertex_buffer_data2[j*18+12] = -this->breadth/2 - this->breadth/2;
      vertex_buffer_data2[j*18+13] = this->radius*cos(current_angle + angle);
      vertex_buffer_data2[j*18+14] = this->radius*sin(current_angle + angle) + this->height/2;
      vertex_buffer_data2[j*18+15] = -this->breadth/2 - this->breadth/2;
      vertex_buffer_data2[j*18+16] = this->radius*cos(current_angle);
      vertex_buffer_data2[j*18+17] = this->radius*sin(current_angle) + this->height/2;

      vertex_buffer_data3[j*18]    = this->breadth/2;
      vertex_buffer_data3[j*18+1]  = this->radius*cos(current_angle);
      vertex_buffer_data3[j*18+2]  = this->radius*sin(current_angle) + this->height/2;
      vertex_buffer_data3[j*18+3]  = this->breadth/2;
      vertex_buffer_data3[j*18+4]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data3[j*18+5]  = this->radius*sin(current_angle + angle) + this->height/2 ;
      vertex_buffer_data3[j*18+6]  = this->breadth/2 + this->breadth/2;
      vertex_buffer_data3[j*18+7]  = this->radius*cos(current_angle);
      vertex_buffer_data3[j*18+8]  = this->radius*sin(current_angle) + this->height/2;

      vertex_buffer_data3[j*18+9]  = this->breadth/2 ;
      vertex_buffer_data3[j*18+10] = this->radius*cos(current_angle + angle);
      vertex_buffer_data3[j*18+11] = this->radius*sin(current_angle + angle) + this->height/2;
      vertex_buffer_data3[j*18+12] = this->breadth/2 + this->breadth/2;
      vertex_buffer_data3[j*18+13] = this->radius*cos(current_angle + angle);
      vertex_buffer_data3[j*18+14] = this->radius*sin(current_angle + angle) + this->height/2;
      vertex_buffer_data3[j*18+15] = this->breadth/2 + this->breadth/2;
      vertex_buffer_data3[j*18+16] = this->radius*cos(current_angle);
      vertex_buffer_data3[j*18+17] = this->radius*sin(current_angle) + this->height/2;

      
      current_angle+=angle;

    }
    
    this->object = create3DObject(GL_TRIANGLES,parts*6, vertex_buffer_data, BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, parts*6, vertex_buffer_data1, BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, parts*6, vertex_buffer_data2, BLACK, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, parts*6, vertex_buffer_data3, BLACK, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 30, vertex_buffer_data4, BROWN, GL_FILL);


}

void Boss::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,0 ,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);


}

void Boss::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Boss::tick() {
    
    this->rotation += 5;

}

