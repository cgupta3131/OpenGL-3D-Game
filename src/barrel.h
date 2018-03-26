#include "main.h"

#ifndef BARREL_H
#define BARREL_H
const color_t BROWN = {165, 42, 42};
const color_t BLACK = {0,0,0};
const color_t AQUA = {0, 206, 209};
const color_t AQUAM = {0, 100, 0};
const color_t KHAKI = {139, 0, 0};
const color_t SEXYGREEN = {0, 255, 127};
class Barrel {
public:
    Barrel() {}
    Barrel(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    float length;
    float height;
    float radius;
    int flag;
    int gift;
    float angle;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    

};

#endif // BARREL_H



Barrel::Barrel(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->length = 0.9;
    this->height = 0.1;
    this->radius =0.5;
    this->flag = 1;
    this->gift = 0;
    this->angle = 0.0;
    int parts = 15;

    GLfloat vertex_buffer_data[parts*18] ;
    int j;
    float angle=(2*M_PI/parts);
    float current_angle = 0;
    GLfloat vertex_buffer_data1[parts*18] ;
    
    for(j=0;j<parts;j++){
      

      vertex_buffer_data[j*18]    = this->radius*cos(current_angle);
      vertex_buffer_data[j*18+1]  = this->length/2;
      vertex_buffer_data[j*18+2]  = this->radius*sin(current_angle) + this->height;
      vertex_buffer_data[j*18+3]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data[j*18+4]  = this->length/2;
      vertex_buffer_data[j*18+5]  = this->radius*sin(current_angle + angle) + this->height ;
      vertex_buffer_data[j*18+6]  = this->radius*cos(current_angle);
      vertex_buffer_data[j*18+7]  = this->length + this->length/2;
      vertex_buffer_data[j*18+8]  = this->radius*sin(current_angle) + this->height;

      vertex_buffer_data[j*18+9]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data[j*18+10] = this->length/2 ;
      vertex_buffer_data[j*18+11] = this->radius*sin(current_angle + angle) + this->height;
      vertex_buffer_data[j*18+12] = this->radius*cos(current_angle + angle);
      vertex_buffer_data[j*18+13] = this->length/2 + this->length;
      vertex_buffer_data[j*18+14] = this->radius*sin(current_angle + angle) + this->height;
      vertex_buffer_data[j*18+15] = this->radius*cos(current_angle);
      vertex_buffer_data[j*18+16] = this->length/2 + this->length;
      vertex_buffer_data[j*18+17] = this->radius*sin(current_angle) + this->height;

      current_angle+=angle;
    }
    current_angle = 0;
    for(j=0;j<parts;j++){
      

      vertex_buffer_data1[j*18]    = 0;
      vertex_buffer_data1[j*18+1]  = this->length/2;
      vertex_buffer_data1[j*18+2]  = this->height;
      vertex_buffer_data1[j*18+3]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data1[j*18+4]  = this->length/2;
      vertex_buffer_data1[j*18+5]  = this->radius*sin(current_angle + angle) + this->height;
      vertex_buffer_data1[j*18+6]  = this->radius*cos(current_angle);
      vertex_buffer_data1[j*18+7]  = this->length/2;
      vertex_buffer_data1[j*18+8]  = this->radius*sin(current_angle) + this->height;

      vertex_buffer_data1[j*18+9]    = 0;
      vertex_buffer_data1[j*18+10]  = this->length*3/2;
      vertex_buffer_data1[j*18+11]  = this->height;
      vertex_buffer_data1[j*18+12]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data1[j*18+13]  = this->length*3/2;
      vertex_buffer_data1[j*18+14]  = this->radius*sin(current_angle + angle) + this->height;
      vertex_buffer_data1[j*18+15]  = this->radius*cos(current_angle);
      vertex_buffer_data1[j*18+16]  = this->length*3/2;
      vertex_buffer_data1[j*18+17]  = this->radius*sin(current_angle)+ this->height;
      current_angle+=angle;
    }
    float m = 0.5;
    GLfloat vertex_buffer_data2[18] ;
    int i = 0;
    vertex_buffer_data2[i++] = 0;
    vertex_buffer_data2[i++] = this->length/2; 
    vertex_buffer_data2[i++] = 2 + m;
    vertex_buffer_data2[i++] = -m*(1.732/2);
    vertex_buffer_data2[i++] = this->length/2;
    vertex_buffer_data2[i++] = 2 - m/2;
    vertex_buffer_data2[i++] = m*(1.732/2);
    vertex_buffer_data2[i++] = this->length/2;
    vertex_buffer_data2[i++] = 2 - m/2;
    
    vertex_buffer_data2[i++] = -m*(1.732/2);
    vertex_buffer_data2[i++] = this->length/2;
    vertex_buffer_data2[i++] = 2 + m/2;
    vertex_buffer_data2[i++] = m*(1.732/2);
    vertex_buffer_data2[i++] = this->length/2;
    vertex_buffer_data2[i++] = 2 + m/2;
    vertex_buffer_data2[i++] = 0;
    vertex_buffer_data2[i++] = this->length/2;
    vertex_buffer_data2[i++] = 2 - m;
    this->object = create3DObject(GL_TRIANGLES, parts*6, vertex_buffer_data, KHAKI, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, parts*6, vertex_buffer_data1, KHAKI, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, SEXYGREEN, GL_FILL);


}

void Barrel::draw(glm::mat4 VP) {
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

}

void Barrel::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Barrel::tick() {
    
    this->angle+=2;
    this->position.z = 0.05*sin(this->angle*M_PI/180) + 0.02;
}

