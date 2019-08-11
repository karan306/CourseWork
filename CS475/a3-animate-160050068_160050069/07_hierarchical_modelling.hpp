/*
  A program which opens a window and draws three arms in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Written by - 
               Harshavardhan Kode
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"

/*// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;*/
// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 6.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=false;
//Shader program attribs
GLuint vPosition,vColor;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;
csX75::HNode* node1;
csX75::HNode* node2;
csX75::HNode* node3;
csX75::HNode* root_node;
csX75::HNode* curr_node;
csX75::HNode* abdomen;
csX75::HNode* chest;
csX75::HNode* hip;
csX75::HNode* handL1;
csX75::HNode* handL2;
csX75::HNode* handR1;
csX75::HNode* handR2;
csX75::HNode* legL1;
csX75::HNode* legL2;
csX75::HNode* legR1;
csX75::HNode* legR2;
csX75::HNode* head;
csX75::HNode* neck;
csX75::HNode* balllegL1;
csX75::HNode* balllegL2;
csX75::HNode* balllegR1;
csX75::HNode* balllegR2;
csX75::HNode* ballhandL1;
csX75::HNode* ballhandL2;
csX75::HNode* ballhandR1;
csX75::HNode* ballhandR2;
csX75::HNode* stomach;
csX75::HNode* tedhead;
csX75::HNode* leftear;
csX75::HNode* leftarm;
csX75::HNode* rightarm;
csX75::HNode* rightear;
csX75::HNode* leftleg;
csX75::HNode* rightleg;
csX75::HNode* leftarmball;
csX75::HNode* rightarmball;
csX75::HNode* leftlegball;
csX75::HNode* rightlegball;
csX75::HNode* lefteye;
csX75::HNode* righteye;
csX75::HNode* mouth;
csX75::HNode* nose;
csX75::HNode* hlefteye;
csX75::HNode* hrighteye;
csX75::HNode* hmouth;
csX75::HNode* hnose;
csX75::HNode* cap;
csX75::HNode* room;
csX75::HNode* table;
csX75::HNode* leg1;
csX75::HNode* leg2;
csX75::HNode* leg3;
csX75::HNode* leg4;

csX75::HNode* Ttable;
csX75::HNode* Tleg1;
csX75::HNode* Tleg2;
csX75::HNode* Tleg3;
csX75::HNode* Tleg4;

csX75::HNode* Chair;
csX75::HNode* Cleg1;
csX75::HNode* Cleg2;
csX75::HNode* Cleg3;
csX75::HNode* Cleg4;
csX75::HNode* Chead;

csX75::HNode* Chair1;
csX75::HNode* cleg1;
csX75::HNode* cleg2;
csX75::HNode* cleg3;
csX75::HNode* cleg4;
csX75::HNode* chead;

csX75::HNode* lamp;
csX75::HNode* stand;

csX75::HNode* door;
csX75::HNode* window1;
csX75::HNode* window2;

void saveframe();
void getframes();

bool dekhega=0;
std::vector<std::vector<double>> keyframes;
std::vector<std::vector<double>> allframes;
int framenum=0;



//-------------------------------------------------------------------------

#endif
