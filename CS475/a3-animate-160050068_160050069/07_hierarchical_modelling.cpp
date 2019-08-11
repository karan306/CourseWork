/*
  CSX75 Tutorial 3

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by - 
               Harshavardhan Kode
*/

#include "07_hierarchical_modelling.hpp"
// #include "hierarchy_node.hpp"

extern GLfloat c_xpos,c_ypos,c_zpos;

#include <fstream>
#include <sstream>
#include <string>

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;
const int num_vertices = 36;
double PI=3.14159265;


// int canvas_t::save(void)
//   {
//     int num_bytes_written = 0;
//     if (!drw_file_present)
//     {
//       drwfilename="default.tga"; drw_file_present=true;
//     }

    
//     unsigned char* ustore = new unsigned char[width*height*4];
//     for(unsigned int x=0; x<width; x++)
//       for(unsigned int y=0;y<height; y++)
//       {
//         unsigned int index=0, uindex=0;
//         index=(4*width*y) + (4*x);
//         uindex=(4*width*(height-1-y)) + (4*x);
//         ustore[uindex] = (unsigned char)(255.0f*store[index]);
//         ustore[uindex+1]=(unsigned char)(255.0f*store[index+1]);
//         ustore[uindex+2]=(unsigned char)(255.0f*store[index+2]);
//         ustore[uindex+3]=(unsigned char)(255.0f*store[index+3]);
//       }
  
//     num_bytes_written = stbi_write_tga( drwfilename.c_str(), width, height, 4, (void*)ustore );

//     if (ustore != NULL)
//       delete[] ustore;
    
//     return num_bytes_written;
//   }
  
void saveframe() {
  std::ofstream frame;
  frame.open("keyframes.txt", std::ios::app);

  frame<<abdomen->dfs();
  frame<<stomach->dfs();
  frame<<node1->dfs();

  frame << "\n";

  frame.close();
}

std::vector<double> parse(std::string s) {
  std::string t;
  std::vector<double> f;
  std::istringstream i(s);
  while(getline(i, t, ' ')) {
    f.push_back(std::stod(t));
  }
  return f;
}

std::vector<std::vector<double>> interpolate_two_frames(int t){
  std::vector<std::vector<double>> frames;

  for(int i=0;i<24;i++)
  {
    std::vector<double> frame;
    for(int j=0;j<keyframes[t].size();j++){
      frame.push_back((keyframes[t][j]*(24-i)+keyframes[t+1][j]*i)/24);
    }
    frames.push_back(frame);
  }
  return frames;
}

void interpolate(){
  for(int i=0;i<keyframes.size()-1;i++){
    std::vector<std::vector<double>> frames = interpolate_two_frames(i);
    allframes.insert(allframes.end(),frames.begin(),frames.end());
  }
  allframes.push_back(keyframes[keyframes.size()-1]);
}

void getframes() {
  std::string s;
  std::ifstream frames("keyframes.txt");
  while(getline(frames, s)) {
    keyframes.push_back(parse(s));
  }
  frames.close();
  interpolate();
}


void setframe(int i)
{
  std::vector<double> frame=allframes[i];
  int j=0;
  abdomen->dfs2(frame,j);
  stomach->dfs2(frame,j);
  node1->dfs2(frame,j);
}
//-----------------------------------------------------------------

//Eight vertices in homogenous coordinates
//elongated cuboid , basic arm in the hierarchy;

//RGBA colors
glm::vec4 colors[8] = {
  glm::vec4(0.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(0.0, 1.0, 1.0, 1.0)
};

glm::vec4 box[8] = {
  glm::vec4(-1.0, -1.0, 1.0, 1.0),
  glm::vec4(-1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, -1.0, 1.0, 1.0),
  glm::vec4(-1.0, -1.0, -1.0, 1.0),
  glm::vec4(-1.0, 1.0, -1.0, 1.0),
  glm::vec4(1.0, 1.0, -1.0, 1.0),
  glm::vec4(1.0, -1.0, -1.0, 1.0)
};

int tri_idx=0;
glm::vec4 v_positions[num_vertices];
glm::vec4 v_colors[num_vertices];
glm::vec4 frustum_ps[4320];
glm::vec4 frustum_cs[4320];
double ang;

glm::vec4 ellipsoid_ps[15552];
glm::vec4 ellipsoid_cs[15552];

void ellipsoid(double a,double b,double c,glm::vec4 white)
{
  double lats, longs;
  tri_idx=0;
  double slices=PI/36.0;
  double sectors=PI/36.0;

  double l;

  for (lats = 0.0; lats <= PI; lats+=sectors)  
  {
      for(longs = 0.0; longs <= 2.0*(PI)&& tri_idx<15552; longs+=slices)
    {
      double x = a * sin(lats) * cos(longs);
      double y = b * sin(lats) * sin(longs);
      double z = c * cos(lats);
      glm::vec4 pt(x, y, z, 1.0);

      ellipsoid_cs[tri_idx] = white; ellipsoid_ps[tri_idx] = pt; 
      // v_normals[tri_idx] = pt; 

      
     l=lats+sectors;
      x = a * sin(l) * cos(longs);
      y = b * sin(l) * sin(longs);
      z = c * cos(l);
      pt =glm::vec4(x, y, z, 1.0);
      ellipsoid_cs[tri_idx+1] = white; ellipsoid_ps[tri_idx+1] = pt; 
      double l1=longs+slices;
      x = a * sin(lats) * cos(l1);
      y = b * sin(lats) * sin(l1);
      z = c * cos(lats);
      pt =glm::vec4(x, y, z, 1.0);
      ellipsoid_cs[tri_idx+2] = white; ellipsoid_ps[tri_idx+2] = pt; 
      x = a * sin(l) * cos(l1);
      y = b * sin(l) * sin(l1);
      z = c * cos(l);
      pt =glm::vec4(x, y, z, 1.0);
      ellipsoid_cs[tri_idx+3] = white; ellipsoid_ps[tri_idx+3] = pt; 
      ellipsoid_cs[tri_idx+4] = white; ellipsoid_ps[tri_idx+4] = ellipsoid_ps[tri_idx+1]; 
      ellipsoid_cs[tri_idx+5] = white; ellipsoid_ps[tri_idx+5] = ellipsoid_ps[tri_idx+2]; 
      
      tri_idx+=6;   
    }
  }
}

void ellip_frustum(double a,double b,double h,double f,glm::vec4 cl)
{ 
  double x=0.0,y=a,z=0.0;
  glm::vec4 axis0(0.0,0.0,0.0,1.0);
  // glm::vec4 axis1(h,0.0,0.0,1.0);
  
  tri_idx=0;
  int count=0;
  for(ang=0;ang<2.0*PI-(PI/180.0);ang+=(PI/180.0)){
    count++;
    for(int i=0;i<12;i++)
      frustum_cs[tri_idx+i]=cl;

    frustum_ps[tri_idx]=axis0;

    glm::vec4 pt2(x, y, z, 1.0);
    frustum_ps[tri_idx+1]=pt2;

    y=a*cos(ang+PI/180.0);
    z=b*sin(ang+PI/180.0);
    glm::vec4 pt3(x, y, z, 1.0);
    frustum_ps[tri_idx+2]=pt3;

    for(int i=0;i<3;i++)
    {
       glm::vec4 pt=frustum_ps[tri_idx+i];
      // std::cout<<"Hello\n";
      pt[0]=h;
      pt[1]=f*pt[1];
      pt[2]=f*pt[2];
      // std::cout<<"Hello Hi\n"<<tri_idx<<" "<<ang<<std::endl;
      frustum_ps[tri_idx+3+i]=pt;
    }
    frustum_ps[tri_idx+6]=frustum_ps[tri_idx+4];
    for(int i=0;i<2;i++)
    {
      frustum_ps[tri_idx+7+i]=frustum_ps[tri_idx+i+1];
    }
    frustum_ps[tri_idx+9]=frustum_ps[tri_idx+2];
    for(int i=0;i<2;i++)
    {
      frustum_ps[tri_idx+10+i]=frustum_ps[tri_idx+i+4];
    }
    tri_idx+=12;
    // std::cout<<"Hello \n"<<tri_idx<<" "<<ang<<" "<<count<<std::endl;
  }
  tri_idx=0;
}


// quad generates two triangles for each face and assigns colors to the vertices
void quad(int a, int b, int c, int d, glm::vec4 positions[])
{
  v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors[b]; v_positions[tri_idx] = positions[b]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
  v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
  v_colors[tri_idx] = colors[d]; v_positions[tri_idx] = positions[d]; tri_idx++;
 }

// generate 12 triangles: 36 vertices and 36 colors
void colorcube(glm::vec4 positions[])
{
    quad( 1, 0, 3, 2 ,positions);
    quad( 2, 3, 7, 6 ,positions);
    quad( 3, 0, 4, 7 ,positions);
    quad( 6, 5, 1, 2 ,positions);
    quad( 4, 5, 6, 7 ,positions);
    quad( 5, 4, 0, 1 ,positions);
    tri_idx=0;
}

void change_cube(double fx,double fy,double fz,glm::vec4 color)
{
  for(int i=0;i<num_vertices;i++)
  {
    v_positions[i][0]=v_positions[i][0]*fx;
    v_positions[i][1]=v_positions[i][1]*fy;
    v_positions[i][2]=v_positions[i][2]*fz;
    v_colors[i]=color;
  }
}

void boxcube(glm::vec4 positions[]){
    quad( 1, 0, 3, 2 ,positions);
    quad( 2, 3, 7, 6 ,positions);
    quad( 3, 0, 4, 7 ,positions);
    // quad( 6, 5, 1, 2 ,positions);
    quad( 4, 5, 6, 7 ,positions);
    quad( 5, 4, 0, 1 ,positions);
    tri_idx=0;
}


//-----------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("07_vshader.glsl");
  std::string fragment_shader_file("07_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

  glm::vec4 white(1.0,1.0,1.0,1.0);
  glm::vec4 red(1.0,0.0,0.0,1.0);
  glm::vec4 green(0.0,1.0,0.0,1.0);
  glm::vec4 blue(0.0,0.0,1.0,1.0);
  glm::vec4 black(0.0,0.0,0.0,1.0);
  glm::vec4 brown(0.4,0.3,0.2,1.0);
  glm::vec4 yellow(0.9,0.9,0.2,1.0);
  glm::vec4 skin(0.9,0.7,0.4,1.0);
  glm::vec4 skin2(0.9,0.5,0.3,1.0);
  glm::vec4 tshirt(0.7,1.0,0.0,1.0);
  glm::vec4 capcolor(0.9,1.0,0.2,1.0); 

  //   Table

  colorcube(box);
  change_cube(4.5,0.25,4.5,brown);
  table=new csX75::HNode(NULL,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  table->change_parameters(0.0,1.0,0.0,0.0,15.0,0.0);

  colorcube(box);
  change_cube(0.25,2.5,0.25,brown);
  leg1=new csX75::HNode(table,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  leg1->change_parameters(-4.0,-2.5,-4.0,0.0,0.0,0.0);

  leg2=new csX75::HNode(table,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  leg2->change_parameters(-4.0,-2.5,4.0,0.0,0.0,0.0);

  leg3=new csX75::HNode(table,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  leg3->change_parameters(4.0,-2.5,4.0,0.0,0.0,0.0);

  leg4=new csX75::HNode(table,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  leg4->change_parameters(4.0,-2.5,-4.0,0.0,0.0,0.0);


  //-------------box

  boxcube(box);
  change_cube(3,3,3,brown);
  
  node1=new csX75::HNode(table,30,v_positions,v_colors,480,480);
  node1->change_parameters(0.0,3.25,0,0.0,0,0);

  v_colors[tri_idx] =brown; v_positions[tri_idx] = glm::vec4(-3.0,0.0,0.0,1.0); tri_idx++;
  v_colors[tri_idx] =brown; v_positions[tri_idx] = glm::vec4(3.0,0.0,0.0,1.0); tri_idx++;
  v_colors[tri_idx] =brown; v_positions[tri_idx] = glm::vec4(-3.0,0.0,6.0,1.0); tri_idx++;
  v_colors[tri_idx] =brown; v_positions[tri_idx] = glm::vec4(3.0,0.0,0.0,1.0); tri_idx++;
  v_colors[tri_idx] =brown; v_positions[tri_idx] = glm::vec4(-3.0,0.0,6.0,1.0); tri_idx++;
  v_colors[tri_idx] =brown; v_positions[tri_idx] = glm::vec4(3.0,0.0,6.0,1.0); tri_idx++;
  tri_idx=0;
  node2=new csX75::HNode(node1,6,v_positions,v_colors,96,96);
  node2->change_parameters(0.0,3.0,-3.0,0.0,0.0,0.0);

  node3=new csX75::HNode(node1,6,v_positions,v_colors,96,96);
  node3->change_parameters(0.0,-3.0,-3.0,0.0,0.0,0.0);

  //-------------humanoid
  ellip_frustum(0.5,0.3,0.4,1.0,green);
  abdomen=new csX75::HNode(node3,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  abdomen->change_parameters(1.0,3.0,2.5,0.0,0.0,-90.0);

  ellip_frustum(0.625,0.375,1.0,0.8,tshirt);
  chest=new csX75::HNode(abdomen,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  chest->change_parameters(-1.0,0.0,0.0,0.0,0.0,0.0);

  ellip_frustum(0.625,0.375,0.6,0.8,blue);
  hip=new csX75::HNode(abdomen,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  hip->change_parameters(1.0,0.0,0.0,0.0,0.0,180.0);

  ellip_frustum(0.2,0.2,0.3,1.0,skin);
  neck=new csX75::HNode(chest,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  neck->change_parameters(-0.3,0.0,0.0,0.0,0.0,0.0);

  ellipsoid(0.5,0.4,0.4,skin);
  head=new csX75::HNode(neck,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  head->change_parameters(-0.45,0.0,0.0,0.0,0.0,0.0);

  ellip_frustum(0.6,0.6,0.4,0.0,capcolor);
  cap=new csX75::HNode(head,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  cap->change_parameters(-0.25,0.0,0.0,0.0,0.0,180.0);

  ellipsoid(0.07,0.07,0.07,black);
  hlefteye=new csX75::HNode(head,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  hlefteye->change_parameters(-0.15,0.15,0.4*cos(PI/6.0),0.0,0.0,0.0);

  hrighteye=new csX75::HNode(head,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  hrighteye->change_parameters(-0.15,-0.15,0.4*cos(PI/6.0),0.0,0.0,0.0);

  ellip_frustum(0.03,0.03,0.3,1.0,white);
  hmouth=new csX75::HNode(head,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  hmouth->change_parameters(0.25,-0.15,0.4*cos(PI/10.0),0.0,0.0,90.0);

  ellip_frustum(0.03,0.03,0.2,1.0,black);
  hnose=new csX75::HNode(head,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  hnose->change_parameters(-0.05,0.0,0.4*cos(PI/10.0),0.0,0.0,0.0);


  ellipsoid(0.2,0.2,0.2,tshirt);
  ballhandL1=new csX75::HNode(chest,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  ballhandL1->change_parameters(0.15,-0.75,0.0,0.0,0.0,90.0);

  ballhandR1=new csX75::HNode(chest,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  ballhandR1->change_parameters(0.15,0.75,0.0,0.0,0.0,-90.0);

  ellip_frustum(0.1,0.1,0.8,1.0,skin);
  handL1=new csX75::HNode(ballhandL1,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  handL1->change_parameters(0.0,0.0,0.0,0.0,0.0,-90.0);

  handR1=new csX75::HNode(ballhandR1,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  handR1->change_parameters(0.0,0.0,0.0,0.0,0.0,90.0);

  ellipsoid(0.2,0.2,0.2,skin2);
  ballhandL2= new csX75::HNode(handL1,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  ballhandL2->change_parameters(1.0,0.0,0.0,0.0,0.0,0.0);

  ballhandR2= new csX75::HNode(handR1,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  ballhandR2->change_parameters(1.0,0.0,0.0,0.0,0.0,0.0);

  handL2=new csX75::HNode(ballhandL2,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  handL2->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);

  handR2=new csX75::HNode(ballhandR2,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  handR2->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);

  ellip_frustum(0.125,0.125,1.0,1.0,skin);
  legL1=new csX75::HNode(hip,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  legL1->change_parameters(0.0,-0.4,0.0,0.0,0.0,180.0);

  legR1=new csX75::HNode(hip,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  legR1->change_parameters(0.0,0.4,0.0,0.0,0.0,180.0);

  balllegL2= new csX75::HNode(legL1,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  balllegL2->change_parameters(1.1,0.0,0.0,0.0,0.0,0.0);

  balllegR2= new csX75::HNode(legR1,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  balllegR2->change_parameters(1.1,0.0,0.0,0.0,0.0,0.0);

  legL2=new csX75::HNode(balllegL2,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  legL2->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);

  legR2=new csX75::HNode(balllegR2,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  legR2->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);



  //---------------tedddy bear

  ellipsoid(0.9,0.9,0.9,brown);
  stomach=new csX75::HNode(node3,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  stomach->change_parameters(-1.0,1.5,2.5,0.0,0.0,0.0);

  ellipsoid(0.6,0.6,0.6,yellow);
  tedhead=new csX75::HNode(stomach,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  tedhead->change_parameters(0.0,1.125,0.0,0.0,0.0,0.0);

  ellipsoid(0.1,0.1,0.1,black);
  lefteye=new csX75::HNode(tedhead,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  lefteye->change_parameters(0.3*cos(PI/6.0),0.15,0.6*cos(PI/6.0),0.0,0.0,0.0);

  righteye=new csX75::HNode(tedhead,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  righteye->change_parameters(-0.3*cos(PI/6.0),0.15,0.6*cos(PI/6.0),0.0,0.0,0.0);

  ellipsoid(0.05,0.05,0.05,black);
  nose=new csX75::HNode(tedhead,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  nose->change_parameters(0.0,0.02,0.6*cos(PI/15.0),0.0,0.0,0.0);


  ellip_frustum(0.03,0.03,0.3,1.0,white);
  mouth=new csX75::HNode(tedhead,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  mouth->change_parameters(-0.15,-0.1,0.6*cos(PI/15.0),0.0,0.0,0.0);

  ellipsoid(0.225,0.225,0.225,brown);
  leftear=new csX75::HNode(tedhead,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  leftear->change_parameters(-0.6*cos(PI/4.0),0.6*sin(PI/4.0),0.0,0.0,0.0,0.0);

  rightear=new csX75::HNode(tedhead,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  rightear->change_parameters(0.6*cos(PI/4.0),0.6*sin(PI/4.0),0.0,0.0,0.0,0.0);

  
  ellip_frustum(0.2,0.2,0.6,1.0,yellow);
  leftarm=new csX75::HNode(stomach,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  leftarm->change_parameters(-0.6*cos(PI/6.0),0.6*sin(PI/6.0),0.0,0.0,0.0,150.0);

  leftarmball=new csX75::HNode(leftarm,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  leftarmball->change_parameters(0.7,0.0,0.0,0.0,0.0,0.0);

  rightarm=new csX75::HNode(stomach,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  rightarm->change_parameters(0.6*cos(PI/6.0),0.6*sin(PI/6.0),0.0,0.0,0.0,30.0);

  rightarmball=new csX75::HNode(rightarm,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  rightarmball->change_parameters(0.7,0.0,0.0,0.0,0.0,0.0);

  ellip_frustum(0.225,0.225,0.6,1.0,yellow);
  leftleg=new csX75::HNode(stomach,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  leftleg->change_parameters(-0.6*cos(-1.0*PI/3.0),0.6*sin(-1.0*PI/3.0),0.0,0.0,0.0,-120.0);

  leftlegball=new csX75::HNode(leftleg,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  leftlegball->change_parameters(0.7,0.0,0.0,0.0,0.0,0.0);

  rightleg=new csX75::HNode(stomach,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  rightleg->change_parameters(0.6*cos(-1.0*PI/3.0),0.6*sin(-1.0*PI/3.0),0.0,0.0,0.0,-60.0);

  rightlegball=new csX75::HNode(rightleg,15552,ellipsoid_ps,ellipsoid_cs,sizeof(ellipsoid_ps),sizeof(ellipsoid_cs));
  rightlegball->change_parameters(0.7,0.0,0.0,0.0,0.0,0.0);

  // Chair

  colorcube(box);
  change_cube(2.25,0.25,2.25,brown);
  Chair=new csX75::HNode(NULL,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  Chair->change_parameters(4.0,0.0,0.0,0.0,15.0,0.0);

  colorcube(box);
  change_cube(0.20,2.0,0.20,brown);
  Cleg1=new csX75::HNode(Chair,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  Cleg1->change_parameters(2.0,-2.0,2.0,0.0,0.0,0.0);

  Cleg2=new csX75::HNode(Chair,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  Cleg2->change_parameters(2,-2.0,-2,0.0,0.0,0.0);

  Cleg3=new csX75::HNode(Chair,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  Cleg3->change_parameters(-2,-2.0,2,0.0,0.0,0.0);

  Cleg4=new csX75::HNode(Chair,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  Cleg4->change_parameters(-2,-2.0,-2,0.0,0.0,0.0);

  colorcube(box);
  change_cube(0.25,2.25,2.25,brown);
  Chead=new csX75::HNode(Chair,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  Chead->change_parameters(2,2.25,0.0,0.0,0.0,0.0);



  // Chair

  colorcube(box);
  change_cube(2.25,0.25,2.25,brown);
  Chair1=new csX75::HNode(NULL,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  Chair1->change_parameters(-9.0,0.0,0.0,0.0,-165.0,0.0);

  colorcube(box);
  change_cube(0.20,2.0,0.20,brown);
  cleg1=new csX75::HNode(Chair1,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  cleg1->change_parameters(2,-2.0,2,0.0,0.0,0.0);

  cleg2=new csX75::HNode(Chair1,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  cleg2->change_parameters(2,-2.0,-2,0.0,0.0,0.0);

  cleg3=new csX75::HNode(Chair1,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  cleg3->change_parameters(-2,-2.0,2,0.0,0.0,0.0);

  cleg4=new csX75::HNode(Chair1,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  cleg4->change_parameters(-2,-2.0,-2,0.0,0.0,0.0);

  colorcube(box);
  change_cube(0.25,2.25,2.25,brown);
  chead=new csX75::HNode(Chair1,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  chead->change_parameters(2,2.25,0.0,0.0,0.0,0.0);

  // Lamp Table

  colorcube(box);
  change_cube(2.75,0.15,2.75,brown);
  Ttable=new csX75::HNode(NULL,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  Ttable->change_parameters(10.0,-1.0,-7.0,0.0,45.0,0.0);

  colorcube(box);
  change_cube(0.15,2.0,0.15,brown);
  Tleg1=new csX75::HNode(Ttable,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  Tleg1->change_parameters(1.414,-1.414,0.0,45.0,45.0,0.0);

  Tleg2=new csX75::HNode(Ttable,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  Tleg2->change_parameters(1.414,-1.414,0.0,-45.0,45.0,0.0);

  Tleg3=new csX75::HNode(Ttable,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  Tleg3->change_parameters(-1.414,-1.414,0.0,45.0,-45.0,0.0);

  Tleg4=new csX75::HNode(Ttable,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  Tleg4->change_parameters(-1.414,-1.414,0.0,-45.0,-45.0,0.0);

  // Table Lamp

  ellip_frustum(1,1,2.0,2.0,white);
  lamp=new csX75::HNode(Ttable,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  lamp->change_parameters(0.0,4.0,0,0.0,0.0,-90.0);

  ellip_frustum(0.15,0.15,2.0,1.0,red);
  stand=new csX75::HNode(lamp,4320,frustum_ps,frustum_cs,sizeof(frustum_ps),sizeof(frustum_cs));
  stand->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);
  
//  room

  colorcube(box);
  change_cube(15,15,12,yellow);
  room=new csX75::HNode(NULL,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  room->change_parameters(0.0,10.0,0.0,0.0,0.0,0.0);

  root_node = curr_node = table;

  colorcube(box);
  change_cube(2,3,0.1,blue);
  window1=new csX75::HNode(room,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  window1->change_parameters(5.0,2.0,-12.0,0.0,0.0,0.0);

  window2=new csX75::HNode(room,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  window2->change_parameters(-5.0,2.0,-12.0,0.0,0.0,0.0);

  colorcube(box);
  change_cube(3,5,0.1,green);
  door=new csX75::HNode(room,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  door->change_parameters(0.0,-9.0,12.0,0.0,0.0,0.0);


}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    // projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
    projection_matrix = glm::perspective(glm::radians(90.0),3.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-20.0, 20.0, -20.0, 20.0, -5.0,20.0);

  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);
    // node3->render_tree();
    // abdomen->render_tree();
    // stomach->render_tree();
    // node1->render_tree();
    table->render_tree();
    Chair->render_tree();
    Chair1->render_tree();
    Ttable->render_tree();
    // lamp->render_tree();
    room->render_tree();

}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
      if(dekhega && glfwGetTime()>framenum*1.0/24){
        setframe(framenum);
        framenum++;
        if(framenum == allframes.size())
          dekhega = 0;
      }
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

