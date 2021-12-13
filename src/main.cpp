//#include <GL/glew.h>
#include "../include/GL/glew.h"
#include "../include/freeglut-3.2.1/include/GL/freeglut.h"

#include "../include/glm/glm.hpp"
#include "../include/glm/gtx/string_cast.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include "../include/importOBJ.h"
#include "../include/datatypes/generic_class.h"
#include "../include/datatypes/scene.h"

#include <iostream>

unsigned int height = 576/2;
unsigned int width = 512;

const char* dev_vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char* dev_fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

// builds and compiles shaders given sources
unsigned int prepShaders(const char* vertexShaderSource, const char* fragmentShaderSource) {
  
  // vertex shader
  // create and compile
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  
  // error checking
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  
  // fragment shader
  // create and compile
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  
  // error checking
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  
  // link shaders
  // create program
  unsigned int ID = glCreateProgram();
  // attach shaders and link
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);
  // check for linking errors
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  // since they have been linked, we can delete the shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return ID;
}

void display() {

  unsigned int shaderProgram = prepShaders(dev_vertexShaderSource, dev_fragmentShaderSource);

  camera SCENE_MAIN_CAMERA{width, height, glm::vec3(0.0f, 0.0f, -2.0f) };

  SCENE_MAIN_CAMERA.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
  
// kept for debugging
  float firstTriangle[] = {
      -0.9f, -0.5f, 0.0f,  // left 
      -0.0f, -0.5f, 0.0f,  // right
      -0.45f, 0.5f, 0.0f,  // top 
  };

  // import mesh
  mesh* cube = new mesh;
  import( (char*)"OBJs/cube.obj", cube );

  
  std::cout<<"test";
  std::cout<<cube->vertices.size();

  // init buffers
  GLuint VBOs[1], VAOs[1], IBOs[1];
  
  
  // - VAO - 
  glGenVertexArrays(1, VAOs);
  glBindVertexArray(VAOs[0]);
  
  // - VBO - 
  glGenBuffers(1, VBOs);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  //glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), &firstTriangle[0], GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, cube->vertices.size() * sizeof(glm::vec3), &cube->vertices[0].position, GL_STATIC_DRAW);
  // something around here is not setup properly, and polygons draw strangely (or sometimes not on screen)
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
  
/*
  // - IBO - 
  glGenBuffers(1, IBOs);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOs[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube->indices.size() * sizeof(unsigned int), &cube->indices[0], GL_STATIC_DRAW); 
*/
  
  // - render -
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  
  glUseProgram(shaderProgram);
  
  glBindVertexArray(VAOs[0]);
  //glDrawArrays( GL_TRIANGLES, 0, 3);
  glDrawArrays( GL_TRIANGLES, 0, cube->vertices.size() );

  //glDrawElements( GL_TRIANGLES, cube->indices.size(), sizeof(unsigned int), 0 )
  
  glFlush();
}

void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  GLfloat aspect = GLfloat(w) / GLfloat(h);
  glLoadIdentity();
  if (w <= h) {
    // width is smaller, so stretch out the height
    glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, -10.0, 10.0);
  } else {
    // height is smaller, so stretch out the width
    glOrtho(-2.5*aspect, 2.5*aspect, -2.5, 2.5, -10.0, 10.0);
  }
}

void init() {
  glEnable(GL_LIGHTING); // so the renderer considers light
  glEnable(GL_LIGHT0); // turn LIGHT0 on
  glEnable(GL_DEPTH_TEST); // so the renderer considers depth
}

int main(int argc, char** argv) {
  //glEnable(GL_DEBUG_OUTPUT);
  // ready GLUT window:
  glutInit(&argc, argv);
  glutInitContextFlags(GLUT_DEBUG);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutInitContextVersion(3,3);


  //camera.Matrix();
    
  // 16:9 ratio
  glutInitWindowSize(width, height);
  glutCreateWindow("This is a Monkey (if you could not tell)");

  // initialize GLEW
  glewInit();

  // display things
  //glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  //init();
  glutMainLoop();

  return 0;
}