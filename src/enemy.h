#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    float length;
    float height;
    float radius;
    float rad;
    int timer;
    int flag;
    float speed;

private:
    VAO *object;
    VAO *object1;
  
};

#endif // ENEMY_H



Enemy::Enemy(float x, float y, float z) {
    
    this->position = glm::vec3(x, y, z );
    float a,b,c,k;
    float r = 1;
    int idx = 0;
    this->rad = r;
    this->timer = 0;
    this->flag = 0;
    this->speed = 0.1;
    this->radius = 1.5;
    int i = 0;
    GLfloat vertex_buffer_data6[18*181*361 + 100];
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
    int j;
    int parts = 15;
    float angle=(2*M_PI/parts);
    float current_angle = 0;
    GLfloat vertex_buffer_data1[parts*9] ;
    
    current_angle = 0;
    for(j=0;j<parts;j++){
      

      vertex_buffer_data1[j*9]    = 0;
      vertex_buffer_data1[j*9+1]  = 0;
      vertex_buffer_data1[j*9+2]  = 0;
      vertex_buffer_data1[j*9+3]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data1[j*9+4]  = this->radius*sin(current_angle + angle);
      vertex_buffer_data1[j*9+5]  = 0;
      vertex_buffer_data1[j*9+6]  = this->radius*cos(current_angle);
      vertex_buffer_data1[j*9+7]  = this->radius*sin(current_angle);
      vertex_buffer_data1[j*9+8]  = 0;

      current_angle+=angle;
    }
    this->object = create3DObject(GL_TRIANGLES,idx/3, vertex_buffer_data6,BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES,parts*3, vertex_buffer_data1,SILVER, GL_FILL);
    
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0 ,0,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object);
    draw3DObject(this->object1);
    

}

void Enemy::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Enemy::tick() {
    
    this->rotation += 2;
    if(this->flag == 0)
    {
        if(this->timer == 120)
        {
            this->set_position(0,8,1.0);
            this->timer = 0;
            this->flag = rand()%4;
        }
        else
        {
            this->position.y -= this->speed;
            this->timer++;
        }
    }
    if(this->flag == 1)
    {
        if(this->timer == 120)
        {
            this->set_position(0,8,1.0);
            this->timer = 0;
            this->flag = rand()%4;

        }
        else
        {
            this->position.y += this->speed;
            this->timer++;
        }
    }
    if(this->flag == 2)
    {
        if(this->timer == 120)
        {
            this->set_position(0,8,1.0);
            this->timer = 0;
            this->flag = rand()%4;
            
        }
        else
        {
            this->position.x += this->speed;
            this->timer++;
        }
    }
    if(this->flag == 3)
    {   
        if(this->timer == 120 )
        {
            this->set_position(0,8,1.0);
            this->timer = 0;
            this->flag = rand()%4;
            
        }
        else
        {
            this->position.x -= this->speed;
            this->timer++;
        }
    }

}
