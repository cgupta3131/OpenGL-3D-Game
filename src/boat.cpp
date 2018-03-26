
#include "boat.h"
#include "main.h"
const color_t BROWN = {165, 42, 42};
const color_t BLACK = {0,0,0};
const color_t AQUA = {0, 206, 209};
const color_t AQUAM = {0, 100, 0};

Boat::Boat(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->breadth = 0.2;
    this->length = 0.6;
    this->height = 0.2;
    this->speed = 0;
    this->accY = -0.025;
    this->speedY = 0;
    this->radius =0.048;
    this->length1 = 0.8;
    this->timer = 0;
    this->timer1 = 0;
    this->boost = 0;
    this->angle = 0;
    this->score = 0.0;
    this->health = 100.0;
    
    this->cannon_rotx = 0.0f;
    this->cannon_rotz = 0.0f;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_color_data[36];
    
    static const GLfloat vertex_buffer_data1[] = {
        0 - this->breadth/2,0 + this->length/2,0 ,
        0 + this->breadth/2,0 + this->length/2,0 ,
        0 - this->breadth/2,0 - this->length/2,0 ,
        0 - this->breadth/2,0 - this->length/2,0 ,
        0 + this->breadth/2,0 + this->length/2,0 ,
        0 + this->breadth/2,0 - this->length/2,0 ,

    };
    static const GLfloat vertex_buffer_data2[] = {
        0 - this->breadth/2,0+ this->length/2,0 ,
        0 - this->breadth/2,0- this->length/2,0 ,
        0 - this->breadth/2 - 0.07,0 + this->length/2  ,0 + this->height,
        0 - this->breadth/2,0 - this->length/2,0 ,
        0 - this->breadth/2 - 0.07,0  + this->length/2,0 + this->height,
        0 - this->breadth/2 - 0.07,0  - this->length/2 - 0.09,0 + this->height,

    };
    for(int i = 0 ;i <= 15 ;i+=3)
    {
        vertex_color_data[i] = 0.000 ;
        vertex_color_data[i+1] = 0.392;
        vertex_color_data[i+2] = 0.000;

    }
    for(int i = 18; i <=27 ;i+=3)
    {
        vertex_color_data[i] = 1.000;
        vertex_color_data[i+1] = 0.843;
        vertex_color_data[i+2] = 0.000;
    }
    static const GLfloat vertex_buffer_data3[] = {
        0 + this->breadth/2,0+ this->length/2,0 ,
        0 + this->breadth/2,0- this->length/2,0 ,
        0 + this->breadth/2 + 0.07,0 + this->length/2 ,0 + this->height,
        0 + this->breadth/2,0 - this->length/2,0 ,
        0 + this->breadth/2 + 0.07,0  + this->length/2,0 + this->height,
        0 + this->breadth/2 + 0.07,0  - this->length/2 - 0.09,0 + this->height,

    };
    static const GLfloat vertex_buffer_data4[] = {
        0 - this->breadth/2,0 + this->length/2,0 ,
        0 + this->breadth/2,0 + this->length/2,0 ,
        0, 0 + this->length/2 + 0.18, 0 + this->height ,
    };
    static const GLfloat vertex_buffer_data5[] = {
        0, 0 + this->length/2 + 0.18,  0  + this->height  ,
        0 - this->breadth/2,0 + this->length/2,0 ,
        0 - this->breadth/2 - 0.07,0  + this->length/2,0 + this->height,
        0, 0 + this->length/2 + 0.18, 0 + this->height,
        0 + this->breadth/2,0 + this->length/2,0,
        0 + this->breadth/2 + 0.07,0 + this->length/2 ,0 + this->height,
        0 - this->breadth/2,0 - this->length/2,0,
        0 - this->breadth/2 - 0.07,0 - this->length/2 - 0.09,0 + this->height,
        0 + this->breadth/2,0 - this->length/2,0,
        0 - this->breadth/2 - 0.07,0 - this->length/2 - 0.09,0  + this->height,
        0 + this->breadth/2,0 - this->length/2,0 ,
        0 + this->breadth/2 + 0.07,0 - this->length/2 - 0.09 ,0 + this->height ,
                
    };
     static const GLfloat vertex_buffer_data6[] = {
       0 - 0.01, 0, 0,
       0 + 0.01, 0, 0,
       0 + 0.01, 0 , 0 + 0.55,
       0 + 0.01, 0, 0 + 0.55,
       0 - 0.01, 0, 0,
       0 - 0.01, 0, 0 + 0.55,
      

    };
    

    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data2,vertex_color_data, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3, AQUAM, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data4, BROWN, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data5, BROWN, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data6, BLACK, GL_FILL);
    int parts = 10;

    GLfloat vertex_buffer_data7[parts*18] ;
    int j;
    float angle=(2*M_PI/parts);
    float current_angle = 0;
    
    for(j=0;j<parts;j++){
      

      vertex_buffer_data7[j*18]    = this->radius*cos(current_angle);
      vertex_buffer_data7[j*18+1]  = 0.15;
      vertex_buffer_data7[j*18+2]  = this->radius*sin(current_angle) + this->height;
      vertex_buffer_data7[j*18+3]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data7[j*18+4]  = 0.15;
      vertex_buffer_data7[j*18+5]  = this->radius*sin(current_angle + angle) + this->height ;
      vertex_buffer_data7[j*18+6]  = this->radius*cos(current_angle);
      vertex_buffer_data7[j*18+7]  = this->length + 0.15;
      vertex_buffer_data7[j*18+8]  = this->radius*sin(current_angle) + this->height;

      vertex_buffer_data7[j*18+9]  = this->radius*cos(current_angle + angle);
      vertex_buffer_data7[j*18+10] = 0.15;
      vertex_buffer_data7[j*18+11] = this->radius*sin(current_angle + angle) + this->height;
      vertex_buffer_data7[j*18+12] = this->radius*cos(current_angle + angle);
      vertex_buffer_data7[j*18+13] = this->length + 0.15;
      vertex_buffer_data7[j*18+14] = this->radius*sin(current_angle + angle) + this->height;
      vertex_buffer_data7[j*18+15] = this->radius*cos(current_angle);
      vertex_buffer_data7[j*18+16] = this->length + 0.15;
      vertex_buffer_data7[j*18+17] = this->radius*sin(current_angle) + this->height;

      current_angle+=angle;
    }
    GLfloat vertex_color_data1[parts*6];

    for(j=0;j<parts;j++){
      

      vertex_color_data1[j*18]    = 1.000;
      vertex_color_data1[j*18+1]  = 0.271;
      vertex_color_data1[j*18+2]  = 0.000;
      vertex_color_data1[j*18+3]  = 1.000;
      vertex_color_data1[j*18+4]  = 0.271;
      vertex_color_data1[j*18+5]  = 0.000;
      vertex_color_data1[j*18+6]  = 1.000;
      vertex_color_data1[j*18+7]  = 0.271;
      vertex_color_data1[j*18+8]  = 0.000;

      vertex_color_data1[j*18+9]  = 0;
      vertex_color_data1[j*18+10] = 0;
      vertex_color_data1[j*18+11] = 0;
      vertex_color_data1[j*18+12] = 0;
      vertex_color_data1[j*18+13] = 0; 
      vertex_color_data1[j*18+14] = 0;
      vertex_color_data1[j*18+15] = 0;
      vertex_color_data1[j*18+16] = 0;
      vertex_color_data1[j*18+17] = 0;

    }
    this->object7 = create3DObject(GL_TRIANGLES, parts*6, vertex_buffer_data7, vertex_color_data1, GL_FILL);


}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,0 ,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate(this->position);
    rotate = glm::rotate((float) ((this->rotation - this->cannon_rotx) * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate *= glm::rotate((float) ((this->cannon_rotz) * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object7);

}

void Boat::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
    this->angle1+=10;
    this->timer1++;
    if(this->timer1 >= 480 && this->timer1 < 540)
    {
      if(this->timer1 == 480)
      {
        this->angle = 90 - this->rotation;
      }
      if(this->angle!= 90)
      {     
            this->position.x = this->position.x - 0.08*sin(this->angle*M_PI/180);
            this->position.y = this->position.y - 0.08*cos(this->angle*M_PI/180);
      
            this->angle += 0.05;
            if(this->rotation > 90)
              this->rotation -= 0.51*sin(M_PI/2);
            else
              this->rotation += 0.51*sin(M_PI/2);}
    }
    if(this->timer1 == 600)
    {
      this->timer1 = 0;
    }
   
}
