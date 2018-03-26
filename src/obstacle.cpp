#include "obstacle.h"
#include "main.h"
// const color_t BROWN = {165, 42, 42};
const color_t BLACK = {0,0,0 };
const color_t PINK = {  255, 0, 255};

Obstacle::Obstacle(float x, float y, float z,int a) {
    this->rotation = 0;
    this->breadth =0.7;
    this->length = 0.7;
    this->height = 0.5;
    this->flag = 1;
    this->position = glm::vec3(x , y , z);
    this->radius = 0.5;

    
    
    if(a == 1)
    { 
      GLfloat vertex_buffer_data[] =  {
      0 - this->breadth/2,0 - this->length/2,0, //1
      0 - this->breadth/2 + 0.2,0 - this->length/2 + 0.25,0 + this->height, //2
      0 - this->breadth/2,0 + this->length/2,0, //3
      0 - this->breadth/2 + 0.2,0 - this->length/2 + 0.25,0 + this->height, //3
      0 - this->breadth/2,0 + this->length/2,0 ,//3
      0 - this->breadth/2 + 0.2,0 + this->length/2 - 0.25,0 + this->height, //4

      0 - this->breadth/2 ,0 + this->length/2 ,0 , //3
      0 - this->breadth/2 + 0.2,0 + this->length/2 - 0.25,0 + this->height, //4
      0 + this->breadth/2 - 0.2,0 + this->length/2 - 0.25,0 + this->height, //5
      0 - this->breadth/2 ,0 + this->length/2 ,0 , //3
      0 + this->breadth/2 - 0.2,0 + this->length/2 - 0.25,0 + this->height, //5
      0 + this->breadth/2,0 + this->length/2,0, //6

      0 + this->breadth/2 - 0.2,0 + this->length/2 - 0.25,0 + this->height, //5
      0 + this->breadth/2,0 + this->length/2,0, //6
      0 + this->breadth/2,0 - this->length/2 ,0, //7
      0 + this->breadth/2 - 0.2,0 + this->length/2 - 0.25,0 + this->height, //5
      0 + this->breadth/2,0 - this->length/2 ,0, //7
      0 + this->breadth/2 - 0.2,0 - this->length/2 + 0.25,0 + this->height, //8

      0 - this->breadth/2,0 - this->length/2,0, //1
      0 - this->breadth/2 + 0.2,0 - this->length/2 + 0.25,0 + this->height, //2
      0 + this->breadth/2,0 - this->length/2 ,0, //7
      0 - this->breadth/2 + 0.2,0 - this->length/2 + 0.25,0 + this->height, //2
      0 + this->breadth/2,0 - this->length/2 ,0, //7
      0 + this->breadth/2 - 0.2,0 - this->length/2 + 0.25,0 + this->height, //8

    };
    GLfloat vertex_buffer_data1[] = {
      0 - this->breadth/2 + 0.2,0 - this->length/2 + 0.25,0 + this->height, //2
      0 - this->breadth/2 + 0.2,0 + this->length/2 - 0.25,0 + this->height, //4
      0,0,0 + this->height + 0.5, // 9

      0 - this->breadth/2 + 0.2,0 + this->length/2 - 0.25,0 + this->height, //4
      0,0,0 + this->height + 0.5, // 9
      0 + this->breadth/2 - 0.2,0 + this->length/2 - 0.25,0 + this->height, //5

      0 + this->breadth/2 - 0.2,0 + this->length/2 - 0.25,0 + this->height, //5
      0,0,0 + this->height + 0.5, // 9
      0 + this->breadth/2 - 0.2,0 - this->length/2 + 0.25,0 + this->height, //8

      0 + this->breadth/2 - 0.2,0 - this->length/2 + 0.25,0 + this->height, //8
      0,0,0 + this->height + 0.5, // 9
      0 - this->breadth/2 + 0.2,0 - this->length/2 + 0.25,0 + this->height, //2

    };
      this->object1 = create3DObject(GL_TRIANGLES,12, vertex_buffer_data1, PINK, GL_FILL);
      this->object = create3DObject(GL_TRIANGLES,24, vertex_buffer_data, BLACK, GL_FILL);
      this->ab = 1;
    }
    else
    {
      int parts = 15;

    GLfloat vertex_buffer_data2[parts*18] ;
    int j;
    float angle=(2*M_PI/parts);
    float current_angle = 0;
    
    for(j=0;j<parts;j++){
      

      vertex_buffer_data2[j*18]    = this->radius*cos(current_angle);
      vertex_buffer_data2[j*18+1]  = this->radius*sin(current_angle) + this->height;
      vertex_buffer_data2[j*18+2]  = 0;
      vertex_buffer_data2[j*18+3]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data2[j*18+4]  = this->radius*sin(current_angle + angle) + this->height;
      vertex_buffer_data2[j*18+5]  = 0;
      vertex_buffer_data2[j*18+6]  = this->radius*cos(current_angle);
      vertex_buffer_data2[j*18+7]  = this->radius*sin(current_angle) + this->height;
      vertex_buffer_data2[j*18+8]  = 2*this->height;

      vertex_buffer_data2[j*18+9]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data2[j*18+10] = this->radius*sin(current_angle + angle) + this->height;
      vertex_buffer_data2[j*18+11] = 0;
      vertex_buffer_data2[j*18+12] = this->radius*cos(current_angle + angle);
      vertex_buffer_data2[j*18+13] = this->radius*sin(current_angle + angle) + this->height;
      vertex_buffer_data2[j*18+14] = 2*this->height;
      vertex_buffer_data2[j*18+15] = this->radius*cos(current_angle);
      vertex_buffer_data2[j*18+16] = this->radius*sin(current_angle) + this->height;
      vertex_buffer_data2[j*18+17] = 2*this->height;

      current_angle+=angle;
    }
      this->object1 = create3DObject(GL_TRIANGLES,parts*6, vertex_buffer_data2,{238, 130, 238}, GL_FILL);
      this->ab = 0;
    }
}

void Obstacle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0,1 ));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->ab == 1)
    {
      draw3DObject(this->object);
      draw3DObject(this->object1);
    }
    else if(!this->ab)
    {
      draw3DObject(this->object1);

    }

}

void Obstacle::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Obstacle::tick() {
    this->rotation += 2;
    this->position.z = 0.05*sin(this->rotation*M_PI/180) - 0.01;
    
    // this->position.x -= speed;
    // this->position.y -= speed;
}

