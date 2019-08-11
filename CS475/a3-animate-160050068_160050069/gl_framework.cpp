#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
// #include "07_hierarchical_modelling.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot,c_xpos,c_ypos,c_zpos;
extern bool enable_perspective;
extern csX75::HNode* node1, *node2, *node3,*curr_node,*abdomen,*chest,*hip,*handL1,*handL2,
*handR1,*handR2,*legL1,*legL2,*legR1,*legR2,*head,*neck,*balllegL1,*balllegL2,*balllegR1,*balllegR2,
*ballhandL1,*ballhandL2,*ballhandR1,*ballhandR2,*stomach,*leftarm,*rightarm,*leftleg,*rightleg,*tedhead;
extern void saveframe();
extern void getframes();
// extern void cambeiz();
// extern std::vector<std::vector<double> > campoints;
extern std::vector<std::vector<double>> keyframes,allframes;
extern bool dekhega;
//extern bool cam;
extern int framenum;

namespace csX75
{
  //! Initialize GL State
  int cur_obj=0;
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
    {  cur_obj = 0; curr_node = abdomen;}
    else if (key == GLFW_KEY_Y && action == GLFW_PRESS)
    {  cur_obj = 1; curr_node = stomach;} 
    else if (key == GLFW_KEY_X && action == GLFW_PRESS)
    {  cur_obj = 2; curr_node = node1;}
    else if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
      cur_obj=3;curr_node=node3;
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS)
      saveframe();
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
      dekhega=!dekhega;
      if(dekhega)
      {
        keyframes.clear();
        allframes.clear();
        getframes();
        glfwSetTime(0.0);
        framenum=0;
      }
    }
    // else if (key == GLFW_KEY_L && action == GLFW_PRESS)
    // {
    //   cam=!cam;
    //   if(!cam)
    //   {
    //     cambeiz();
    //   }
    // }
    else if (cur_obj==0 && key == GLFW_KEY_1 && action == GLFW_PRESS)
      curr_node = ballhandL2;  
    else if (cur_obj==0 && key == GLFW_KEY_2 && action == GLFW_PRESS)
      curr_node = ballhandL1;
    else if (cur_obj==0 && key == GLFW_KEY_3 && action == GLFW_PRESS)
      curr_node = ballhandR1;  
    else if (cur_obj==0 && key == GLFW_KEY_4 && action == GLFW_PRESS)
      curr_node = ballhandR2;

    else if (cur_obj==0 && key == GLFW_KEY_0 && action == GLFW_PRESS)
      curr_node = neck;  
    else if (cur_obj==0 && key == GLFW_KEY_5 && action == GLFW_PRESS)
      curr_node = abdomen;
    else if (cur_obj==0 && key == GLFW_KEY_L && action == GLFW_PRESS)
      curr_node = hip;

    else if (cur_obj==0 && key == GLFW_KEY_6 && action == GLFW_PRESS)
      curr_node = legL1;  
    else if (cur_obj==0 && key == GLFW_KEY_7 && action == GLFW_PRESS)
      curr_node = balllegL2; 
    else if (cur_obj==0 && key == GLFW_KEY_8 && action == GLFW_PRESS)
      curr_node = legR1;  
    else if (cur_obj==0 && key == GLFW_KEY_9 && action == GLFW_PRESS)
      curr_node = balllegR2;

    else if (cur_obj==1 && key == GLFW_KEY_0 && action == GLFW_PRESS)
      curr_node = stomach;
    else if (cur_obj==1 && key == GLFW_KEY_1 && action == GLFW_PRESS)
      curr_node = leftarm;  
    else if (cur_obj==1 && key == GLFW_KEY_2 && action == GLFW_PRESS)
      curr_node = rightarm;
    else if (cur_obj==1 && key == GLFW_KEY_3 && action == GLFW_PRESS)
      curr_node = leftleg;  
    else if (cur_obj==1 && key == GLFW_KEY_4 && action == GLFW_PRESS)
      curr_node = rightleg;
    else if (cur_obj==1 && key == GLFW_KEY_5 && action == GLFW_PRESS)
      curr_node = tedhead;

    else if (cur_obj==2 && key == GLFW_KEY_0 && action == GLFW_PRESS)
      curr_node = node1;
    else if (cur_obj==2 && key == GLFW_KEY_1 && action == GLFW_PRESS)
      curr_node = node2;  
    

    else if (key == GLFW_KEY_LEFT )
      curr_node->dec_ry();
    else if (key == GLFW_KEY_RIGHT )
      curr_node->inc_ry();
    else if (key == GLFW_KEY_UP )
      curr_node->dec_rx();
    else if (key == GLFW_KEY_DOWN )
      curr_node->inc_rx();
    else if (key == GLFW_KEY_PAGE_UP )
      curr_node->dec_rz();
    else if (key == GLFW_KEY_PAGE_DOWN )
      curr_node->inc_rz();
    else if (key == GLFW_KEY_F )
      curr_node->dec_tx();
    else if (key == GLFW_KEY_U )
      curr_node->dec_ty();
    else if (key == GLFW_KEY_I )
      curr_node->dec_tz();
    else if (key == GLFW_KEY_G )
      curr_node->inc_tx();
    else if (key == GLFW_KEY_H )
      curr_node->inc_ty();
    else if (key == GLFW_KEY_J )
      curr_node->inc_tz();

    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A )
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D )
      c_yrot += 1.0;
    else if (key == GLFW_KEY_W  )
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_S )
      c_xrot += 1.0;        
    else if (key == GLFW_KEY_Q )
      c_zrot -= 1.0;
    else if (key == GLFW_KEY_E  )
      c_zrot += 1.0; 
    else if (key == GLFW_KEY_C )
      c_ypos -= 0.1;
    else if (key == GLFW_KEY_V )
      c_ypos += 0.1;
    else if (key == GLFW_KEY_B  )
      c_xpos -= 0.1;
    else if (key == GLFW_KEY_N )
      c_xpos += 0.1;        
    else if (key == GLFW_KEY_T )
      c_zpos -= 0.1;
    else if (key == GLFW_KEY_O  )
      c_zpos += 0.1;      
  }
};  
  


