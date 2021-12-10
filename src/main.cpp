//#include <GL/glew.h>
#include "../include/GL/glew.h"
#include "../include/freeglut-3.2.1/include/GL/freeglut.h"

#include "../include/glm/glm.hpp"
#include "../include/glm/gtx/string_cast.hpp"
#include "../include/importOBJ.h"
#include "../include/datatypes/generic_class.h"

#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


void display() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);


  // build and compile our shader program
  // ------------------------------------
  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // link shaders
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);



  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------

  float firstTriangle[] = {
      -0.9f, -0.5f, 0.0f,  // left 
      -0.0f, -0.5f, 0.0f,  // right
      -0.45f, 0.5f, 0.0f,  // top 
  };
  float secondTriangle[] = {
      0.0f, -0.5f, 0.0f,  // left
      0.9f, -0.5f, 0.0f,  // right
      0.45f, 0.5f, 0.0f   // top 
  };

  mesh* cube = new mesh;
  import( (char*)"OBJs/cube.obj", cube );

  unsigned int VBOs[1], VAOs[1], IBOs[1];
  glGenVertexArrays(1, VAOs); // we can also generate multiple VAOs or buffers at the same time
  glGenBuffers(1, VBOs);
  glGenBuffers(1, IBOs);

  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  
  /*
  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, cube->vertices.size() * sizeof(glm::vec3), &cube->vertices[0].position, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
  glEnableVertexAttribArray(0);
  

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOs[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube->indices.size() * sizeof(unsigned int), &cube->indices[0], GL_STATIC_DRAW); 
  */

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    // draw first triangle using the data from the first VAO
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    //glBindVertexArray(VAOs[0]);
    //glDrawArrays(GL_TRIANGLES, 0, cube->indices.size());
    //glBindVertexArray(0);

    //glDrawElements(GL_TRIANGLES, cube->indices.size(), sizeof(unsigned int),0 );
    



  /*
  mesh* suzanne = new mesh;
  import((char*)"OBJs/suzanne.obj", cube);

  generic_container* obj1 = new generic_container{"obj1", cube, NULL};
  generic_container* obj2 = new generic_container {"obj2", suzanne, obj1};

  std::cout<<obj2->parent_ptr->name;*/
  //glfwTerminate();

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
    
  // ready GLUT window:
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutInitContextVersion(3,3);
  
  // 16:9 ratio
  glutInitWindowSize(512, 576/2);
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

// OpenGL bufferdata setup: 
//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);