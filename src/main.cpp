#include "main.h"
#include "timer.h"
#include "boat.h"
#include "lake.h"
#include "obstacle.h"
#include "barrel.h"
#include "monster.h"
#include "fireball.h"
#include "boss.h"
#include "sail.h"
#include "enemy.h"
// #include "audio.cpp"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
bool drag = false;
double cxpos, pxpos, cypos, pypos;
/**************************
* Customizable functions *
**************************/
glm::vec3 helcamEye = glm::vec3(0,-1.0, 9.0f);
glm::vec3 helcamTarget = glm::vec3(0, 1.0f, 0.0f);
Boat boat;
Lake lake;
Obstacle obstacle[50];
Barrel barrel[15];
Monster monster[15];
Fireball fireball;
Enemy enemy;
Boss boss;
Sail sail;

int flag2 = 0;
int flag1 = 1;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle =0;
int camera = 1;
int yes = 0;
int bossFlag = 1;
Timer t60(1.0 / 60);
bool detect_collision(Boat boat,Barrel barrel);
bool checkCollision(Boat boat,Obstacle obstacle);
bool fireCollision(Fireball fireball,Obstacle obstacle);
bool monsterCollision(Fireball fireball,Monster monster);
bool boatCollision(Boat boat,Monster monster);
bool bossCollision(Boat boat,Enemy enemy);
bool bossKill(Fireball fireball,Boss boss);
bool giftCollision(Boat boat,Monster monster);
void dispScore();
void endGame();
void draw() {
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   
    glUseProgram(programID);
    if(camera == 1)
    {
        glm::vec3 eye (boat.position.x + 4*sin(boat.rotation*M_PI/180),boat.position.y - 4*cos(boat.rotation*M_PI/180),boat.position.z + 0.9);
        glm::vec3 target (boat.position.x-0.5*sin(boat.rotation*M_PI/180),boat.position.y+ 2*cos(boat.rotation*M_PI/180),boat.position.z);
        glm::vec3 up (0, 0, 1);
        

        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    if(camera == 2)
    {
        glm::vec3 eye ( boat.position.x,boat.position.y,boat.position.z + 6.3);
        glm::vec3 target (boat.position.x,boat.position.y,boat.position.z);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    if(camera == 3)
    {
        glm::vec3 eye ( boat.position.x + 0.1*sin(boat.rotation*M_PI/180),boat.position.y - 0.1*cos(boat.rotation*M_PI/180),boat.position.z  + boat.height  );
        glm::vec3 target (boat.position.x - 0.1*sin(boat.rotation*M_PI/180),boat.position.y + 0.1*cos(boat.rotation*M_PI/180) ,boat.position.z + boat.height + 0.05);
        glm::vec3 up (0, 0, 1);
        Matrices.view = glm::lookAt( eye, target, up ); 
    }
    if(camera == 4)
    {
        glm::vec3 eye ( 0,0,7.3);
        glm::vec3 target (boat.position.x,boat.position.y,boat.position.z);
        glm::vec3 up (0, 0, 1);
        Matrices.view = glm::lookAt( eye, target, up ); 
    }
    if(camera == 5)
    {
        glm::vec3 eye = helcamEye;
        glm::vec3 target = helcamTarget;
        glm::vec3 up = glm::vec3(0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up ); 

    }
    glm::mat4 VP = Matrices.projection * Matrices.view;

    glm::mat4 MVP; 

    if(boss.flag && bossFlag >= 6)
    {    boss.draw(VP);
        enemy.draw(VP);
    }
    boat.draw(VP);
    for(int i = 0 ;i < 50;i++)
    {   
        if(obstacle[i].flag == 1)
        {
            obstacle[i].draw(VP);
        }
    }
    for(int i = 0 ;i < 15;i++)
    {   
        if(barrel[i].flag == 1)
        {
            barrel[i].draw(VP);
        }
    }
    for(int i = 0 ;i < 15;i++)
    {   
        if(monster[i].flag == 1)
        {
            monster[i].draw(VP);
        }
        if(monster[i].flag1 == 1)
        {
            monster[i].draw(VP);
        }
    }
    if(fireball.flag)
        fireball.draw(VP);
    sail.draw(VP);
    lake.draw(VP);

}

void tick_input(GLFWwindow *window) {
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int backView = glfwGetKey(window, GLFW_KEY_1);
    int topView = glfwGetKey(window,GLFW_KEY_2);
    int shipView = glfwGetKey(window,GLFW_KEY_3);
    int towerView = glfwGetKey(window,GLFW_KEY_4);
    int boost = glfwGetKey(window,GLFW_KEY_B);
    int fire = glfwGetKey(window,GLFW_KEY_F);
    int helicam = glfwGetKey(window,GLFW_KEY_5);
    
    if(backView)
    {
        camera = 1;
    }
    if(topView)
    {
        camera = 2;
    }
    if(shipView)
    {
        camera = 3;
    }
    if(towerView)
    {
        camera = 4;
    }
    if(helicam)
    {
        camera = 5;
    }
    double deltax, deltay;

    glfwGetCursorPos(window, &cxpos, &cypos);
    if (camera == 5 && drag) {
        float dragx = ((float)cxpos - (float)pxpos)/10;
        float dragy = ((float)cypos - (float)pypos)/10;

        glm::vec3 delta = helcamTarget - helcamEye;
        glm::vec3 l;
        l.x += delta.x/sqrt(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);
        l.y += delta.y/sqrt(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);
        l.z += delta.z/sqrt(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);

        float coss = l.z/sqrt(l.x*l.x + l.z*l.z);
        float sinn = l.x/sqrt(l.x*l.x + l.z*l.z);

        helcamTarget.x += dragy*sinn;
        helcamTarget.z += dragy*coss;

        helcamTarget.x += dragx*coss;
        helcamTarget.z -= dragx*sinn;
    }
    pxpos = cxpos;
    pypos = cypos;
    if (up) {

        if(boost && yes)
        {    
            boat.timer = 0;
            boat.boost = 1;
        }
        else
        {
            boat.position.x = boat.position.x - 0.1*sin(boat.rotation*M_PI/180);
            boat.position.y = boat.position.y + 0.1*cos(boat.rotation*M_PI/180);      
            sail.set_position(boat.position.x,boat.position.y,boat.position.z);
            fireball.set_position(boat.position.x + 0.08*sin(boat.rotation*M_PI/180),boat.position.y + 0.08*cos(boat.rotation*M_PI/180),boat.height);
            
        }
    }
    if (right)
    {
        boat.rotation -= 2;
        
        fireball.rotation -= 2;
        
    }
    
    if (left)
    {
        boat.rotation += 2;
        fireball.rotation += 2;
        
    }
    int flag = 0;
    if(jump)
    {   
        boat.speedY = 0.25;
        flag = 1;
        flag1 = 0;
        boat.speedY += boat.accY;
        boat.position.z += boat.speedY;
        sail.set_position(boat.position.x,boat.position.y,boat.position.z);
       
    }
    if(flag == 0 && !flag1)
    {
        boat.speedY += boat.accY;

        if(boat.position.z <= 0.1)
        {
            boat.position.z = 0.1;
            boat.speedY = 0;
            flag1 = 1;
        }
        if(boat.position.z > 0.2)
        {
            boat.position.z += boat.speedY;  
            sail.set_position(boat.position.x,boat.position.y,boat.position.z);

        }
       
    }
    if(flag1 == 1 && !jump)
    {
         boat.position.z = 0.06*sin(boat.angle1*M_PI/180) + 0.01 ;
    }

    if(fire && fireball.timer == 0)
    {
        fireball.flag = 1;
    }

}

void tick_elements() {

   
   enemy.tick();

   for(int i = 0 ; i < 15; i++)
   {
    barrel[i].tick();
   }
   sail.tick(boat.rotation,boat.timer1);
   boat.tick();
   sail.set_position(boat.position.x,boat.position.y,boat.position.z);

   fireball.rotation = boat.rotation;
   if(fireball.flag == 1)
   {   
      fireball.tick();
      if(fireball.timer == 60)
      {
        fireball.set_position(boat.position.x - 0.08*sin(boat.rotation*M_PI/180),boat.position.y + 0.08*cos(boat.rotation*M_PI/180),boat.height);
        fireball.flag = 0;
        fireball.timer = 0;
      }
   }
   for(int i = 0 ; i < 15 ; i++)
   {
    if(monster[i].flag == 1)
    {
        monster[i].tick();
    }
   }
   if(boat.timer != 60 && boat.boost == 1 )
   { 
       boat.position.x = boat.position.x - 0.4*sin(boat.rotation*M_PI/180);
       boat.position.y = boat.position.y + 0.4*cos(boat.rotation*M_PI/180);
       boat.timer++;
   }
   else{
    boat.timer = 0;
    boat.boost = 0;
   }
   for(int i = 0 ; i < 50 ; i++)
   {    
        obstacle[i].tick();
        if(obstacle[i].flag == 1)
        {   
            if(checkCollision(boat,obstacle[i]))
            {   
                obstacle[i].flag = 0;
                boat.health -= 20;
                dispScore();
                if(boat.health <= 0)
                {
                    endGame();
                }
            }    
        }
   }
   for(int i = 0 ; i < 15 ; i++)
   {
        if(barrel[i].flag == 1)
        {   
            if(detect_collision(boat,barrel[i]))
            {   
                barrel[i].flag = 0;
                boat.health += 20;
                dispScore();
            }    
        }
   }
   for(int i = 0 ; i < 15 ; i++)
   {
        if(monster[i].flag == 1)
        {   
            if(monsterCollision(fireball,monster[i]))
            {   
                monster[i].flag1 = 1;
                monster[i].flag = 0;
                boat.score += 100;
                bossFlag++;
                dispScore();

            }    
        }
        if(monster[i].flag1 == 1)
        {
            if(giftCollision(boat,monster[i]))
            {
                boat.score += 20;
                monster[i].flag1 = 0;
                dispScore();
            }
        }
   }
   for(int i = 0 ; i < 15 ; i++)
   {
        if(monster[i].flag == 1)
        {   
            if(boatCollision(boat,monster[i]))
            {   
                boat.health -= 0.5;
                dispScore(); 
                if(boat.health <= 0)
                {   

                     endGame();
                     exit(0);
                }               
            }    
        }
   }
   for(int i = 0 ; i < 50 ; i++)
   {
        if(obstacle[i].flag == 1 && fireball.flag == 1)
        {   
            if(fireCollision(fireball,obstacle[i]))
            {   
                obstacle[i].flag = 0;
                fireball.set_position(boat.position.x - 0.08*sin(boat.rotation*M_PI/180),boat.position.y + 0.08*cos(boat.rotation*M_PI/180),boat.height);
                boat.score += 100;
                dispScore();
                fireball.flag = 0;
                fireball.timer = 0;

            }    
        }
   }
   if(bossFlag >= 6)
   {
    yes = 1;
   }
   if(bossCollision(boat,enemy) && boss.flag == 1 && bossFlag >= 6)
   {    
        yes = 1;

        endGame();
        
   }
   if(bossKill(fireball,boss) && boss.flag == 1 && bossFlag >= 6)
   {
        boat.score += 100;
        boss.score -= 5;
        yes = 1;

        if(boss.score == 0)
        {
            yes = 1;
            boss.flag = 0;
        }
        dispScore();
   }
}

void initGL(GLFWwindow *window, int width, int height) {
   
    lake       = Lake(0,0,0);

    boat       = Boat(0,0,0.1,COLOR_RED);
    
    for(int i = 0; i < 50 ; i++)
    { 
        int HI1 = 70,HI2 = 70,LO1 = -20,LO2= -20;
        float x1 = LO1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI1-LO1)));
        float x2 = LO2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI2-LO2)));
        obstacle[i] = Obstacle(x1,x2,0,rand()%2);
    }
    for(int i = 0; i < 15;i++)
    { 
        int HI1 = 70,HI2 = 70,LO1 = -30,LO2=2;
        float x1 = LO1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI1-LO1)));
        float x2 = LO2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI2-LO2)));
        barrel[i] = Barrel(x1,x2,0);
     
    }
    for(int i = 0; i < 15;i++)
    { 
        int HI1 = 70,HI2 = 70,LO1 = -15,LO2=-15;
        float x1 = LO1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI1-LO1)));
        float x2 = LO2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI2-LO2)));
        monster[i] = Monster(x1,x2,0);
    }
    boss = Boss(0,8,1.6);
    enemy = Enemy(0,8,1);
    sail = Sail(boat.position.x,boat.position.y,boat.position.z);
    fireball = Fireball(boat.position.x,boat.position.y + 2*boat.length - 0.3,boat.height);
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices.Tr = glGetUniformLocation(programID, "T");
    reshapeWindow (window, width, height);

    
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); 
    glClearDepth (1.0f);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);
    while (!glfwWindowShouldClose(window)) {
        if (t60.processTick()) {
            draw();
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        glfwPollEvents();
    }
    quit(window);
}

bool detect_collision(Boat boat, Barrel barrel) {
   if(boat.position.x >= (barrel.position.x - barrel.radius) && boat.position.x <= (barrel.position.x + barrel.radius))
   {
    if(boat.position.y >= (barrel.position.y + barrel.length/2) && boat.position.y <= (barrel.position.y + 3/2*barrel.length))
    {
        if(boat.position.z >= (barrel.position.z + 2*barrel.height))
        {
            return true;
        }
    }
   }
   return false;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(1.0f, 1.0f,1.0f,500.0f);
}
bool checkCollision(Boat boat,Obstacle obstacle)
{
    if( abs(obstacle.position.x - boat.position.x) < obstacle.breadth/2)
    {   
        
        if(abs(obstacle.position.y - boat.position.y) < obstacle.length/2)
        {               
            if(abs((boat.position.z)) < (obstacle.height + 0.5))
            {   
                return true;
            }
           
        }
    }
    return false;

}

bool fireCollision(Fireball fireball,Obstacle obstacle)
{
    if( (obstacle.position.x - fireball.position.x) < obstacle.breadth/2)
    {   
        
        if(abs(obstacle.position.y - fireball.position.y) < obstacle.length/2)
        {               
            if(abs((fireball.position.z)) < (obstacle.height + 0.5))
            {   
                return true;
            }
           
        }
    }
    return false;
}
bool monsterCollision(Fireball fireball,Monster monster)
{
    if( abs(monster.position.x - fireball.position.x) < monster.breadth/2)
    {   
        
        if(abs(monster.position.y - fireball.position.y) < monster.length/2)
        {               
            if(abs((fireball.position.z)) < (monster.height + 0.5))
            {   
                return true;
            }
           
        }
    }
    return false;
}
bool boatCollision(Boat boat,Monster monster)
{
    if( abs(monster.position.x - boat.position.x) < monster.breadth/2 + .75*monster.radius)
    {   
        
        if(abs(monster.position.y - boat.position.y) < monster.length/2 + .75*monster.radius)
        {               
            if(abs((boat.position.z)) < (monster.height + 0.5))
            {   
                return true;
            }
           
        }
    }
    return false;
}

bool bossCollision(Boat boat,Enemy enemy)
{
    if( abs(enemy.position.x - boat.position.x) < enemy.radius)
    {   
        
        if(abs(enemy.position.y - boat.position.y) < enemy.radius)
        {               
            if(abs((boat.position.z)) < (enemy.radius + enemy.position.z))
            {   
                printf("Collided");
                return true;
            }
           
        }
    }
    return false;
}
bool bossKill(Fireball fireball,Boss boss)
{
    if( abs(boss.position.x - fireball.position.x) < boss.breadth/2)
    {   
        
        if(abs(boss.position.y - fireball.position.y) < boss.length/2)
        {               
            if(abs((fireball.position.z)) < (boss.position.z + boss.height))
            {   
                return true;
            }
           
        }
    }
    return false;
}
bool giftCollision(Boat boat,Monster monster)
{
    if( abs(monster.position.x - boat.position.x) < monster.breadth/2 - 0.2)
    {   
        
        if(abs(monster.position.y - boat.position.y) < monster.length/2 - 0.2)
        {               
            if(abs((boat.position.z)) < (monster.height + 0.5))
            {   
                return true;
            }
           
        }
    }
    return false;
}
void dispScore(){
//    cout << ball2.score << endl;
    string e = "Player Score: ";
    string s = to_string(boat.score);
    string p = "  Health: ";
    string l = to_string(boat.health);
    

    s = e+s + p + l ;
    glfwSetWindowTitle(window, const_cast<char*>(s.c_str()));
}
void dragS() {
    drag = true;
}

void dragE() {
    drag = false;
}
void scroll_call(double x_scroll, double y_scroll){
    glm::vec3 delta = helcamTarget - helcamEye;
    helcamEye.x += (y_scroll)*delta.x/sqrt(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);
    helcamEye.y += (y_scroll)*delta.y/sqrt(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);
    helcamEye.z += (y_scroll)*delta.z/sqrt(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);
}
int ind = 0;
void endGame(){
    string s = " Game Over ";
    string b = " Score : ";
    string e = to_string(boat.score);
    s = b+e+s;
    glfwSetWindowTitle(window, const_cast<char*>(s.c_str()));
    ind++;
    if(ind == 30)
    {
        exit(0);
    }

}   