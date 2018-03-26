#include "main.h"

#ifndef FIREBALL_H
#define FIREBALL_H

class Fireball {
public:
    Fireball() {}
    Fireball(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    float length;
    float height;
    float radius;
    int timer;
    int flag;
    int gift;
    float speedY;
    float accY;
private:
    VAO *object;
  
};

#endif // FIREBALL_H



Fireball::Fireball(float x, float y, float z) {
    
    this->position = glm::vec3(x, y, z );
    float a,b,c,k;
    float r = 0.05;
    int idx = 0;
    this->timer = 0;
    this->flag = 0;
    this->speedY = 0.07;
    this->accY = -0.003;
    GLfloat vertex_buffer_data6[18*181*361 + 90];
    int i = 0;
    while(i<=360)
    {   
        int j = 0;
        do
        {   
            k = j;
            float angle = M_PI*j/180;
            c=r*cos(angle);
            a=r*sin(angle)*cos(M_PI*i/180);
            b=r*sin(angle)*sin(M_PI*i/180);
            vertex_buffer_data6[idx++]=r*sin(angle)*cos(M_PI*(i+1)/180);
            vertex_buffer_data6[idx++]=r*sin(angle)*sin(M_PI*(i+1)/180);
            vertex_buffer_data6[idx++]=r*cos(angle);
            vertex_buffer_data6[idx]=a;
            vertex_buffer_data6[idx+1]=b;
            vertex_buffer_data6[idx+2]=c;
            idx += 3;
            k=j+1;
            angle = M_PI*k/180;
            c=r*cos(angle);
            a=r*sin(angle)*cos(M_PI*i/180);
            b=r*sin(angle)*sin(M_PI*i/180);
            vertex_buffer_data6[idx]=a;
            vertex_buffer_data6[idx+1]=b;
            vertex_buffer_data6[idx+2]=c;
            j++;
            idx += 3;
        }while(j<=180);
        i++;
    }

    i = 0;
    while(i<=360)
    {
        for(int j=0;j<=180;j++)
        {   
            float angle = M_PI*(j+1)/180;
            float angle1 = M_PI*j/180;
            c=r*cos(angle);
            a=r*sin(angle)*cos(M_PI*(i+1)/180);
            b=r*sin(angle)*sin(M_PI*(i+1)/180);
            vertex_buffer_data6[idx++]=r*sin(angle1)*cos(M_PI*(i+1)/180);
            vertex_buffer_data6[idx++]=r*sin(angle1)*sin(M_PI*(i+1)/180);
            vertex_buffer_data6[idx++]=r*cos(angle1);
            vertex_buffer_data6[idx]=a;
            vertex_buffer_data6[idx+1]=b;
            vertex_buffer_data6[idx+2]=c;
            idx += 3;
            k=j+1;
            c=r*cos(angle);
            a=r*sin(angle)*cos(M_PI*i/180);
            b=r*sin(angle)*sin(M_PI*i/180);
            vertex_buffer_data6[idx]=a;
            vertex_buffer_data6[idx+1]=b;
            vertex_buffer_data6[idx+2]=c;
            idx += 3;
        }
        i++;
    }

    this->object = create3DObject(GL_TRIANGLES,idx/3, vertex_buffer_data6,BLACK, GL_FILL);
    // printf("Created fireball\n");
}

void Fireball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0 ,0,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object);
  

}

void Fireball::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Fireball::tick() {
    
    this->timer++;
    this->position.x = this->position.x - 0.1*sin(this->rotation*M_PI/180);
    this->position.y = this->position.y + 0.1*cos(this->rotation*M_PI/180);
    if(this->position.z > 0.1)
    {
      this->speedY += this->accY;
      this->position.z += this->speedY;
    }
    else
    {
      this->speedY = 0.07;
    }

}
