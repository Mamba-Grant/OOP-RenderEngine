#include <GL/glew.h>
#include "../include/freeglut-3.2.1/include/GL/freeglut.h"

#include "../include/glm/glm.hpp"
#include "../include/glm/gtx/string_cast.hpp"
#include "../include/importOBJ.h"
#include "../include/datatypes/generic_class.h"

#include <iostream>

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);

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
  
  // 16:9 ratio
  glutInitWindowSize(512, 576/2);
  glutCreateWindow("Geometry Testing");

  // initialize GLEW
  glewInit();
  
  mesh* cube = new mesh;
  import((char*)"OBJs/cube.obj", cube);

  float vertices[] = {
     0.0f,  0.5f, // Vertex 1 (X, Y)
     0.5f, -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f  // Vertex 3 (X, Y)
  };

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  //glDrawArrays( GL_TRIANGLES, 0, suzanne->vertices.size() );

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  
  //glBufferData(GL_ARRAY_BUFFER, suzanne->vertices.size() * sizeof(glm::vec3), &suzanne->vertices[0].position, GL_STATIC_DRAW);

  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  
  //std::cout<<sizeof(glm::vec3)<<std::endl;
  //std::cout<<glm::to_string(cube->vertices[0].position)<<std::endl
/*
  mesh* suzanne = new mesh;
  import((char*)"OBJs/suzanne.obj", cube);

  generic_container* obj1 = new generic_container{"obj1", cube, NULL};
  generic_container* obj2 = new generic_container {"obj2", suzanne, obj1};

  std::cout<<obj2->parent_ptr->name;*/
  //glfwTerminate();
  return 0;
}

// OpenGL thingy: 
//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);