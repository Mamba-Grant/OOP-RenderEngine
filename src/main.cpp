#include "../include/freeglut-3.2.1/include/GL/freeglut.h"

#include "../include/glm/glm.hpp"
#include "../include/glm/gtx/string_cast.hpp"
#include "../include/importOBJ.h"
#include "../include/datatypes/generic_class.h"

#include <iostream>

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // Rotate the scene so we can see the tops of the shapes.
  glRotatef(-20.0, 1.0, 0.0, 0.0);

  glBegin(GL_TRIANGLE_STRIP);
    mesh* cube = new mesh;


  std::vector< glm::vec3 > vertices;
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);



  glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
    glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
    glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
    glColor3f(0, 1, 0); glVertex3f(1, 0, 1);
    glColor3f(0, 0, 1); glVertex3f(0, 0, -1.4);
    glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
    glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
  glEnd();

  glPopMatrix();
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

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  
  // 16:9 ratio
  glutInitWindowSize(512, 576/2);
  glutCreateWindow("Geometry Testing");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
/*
  mesh* suzanne = new mesh;
  import((char*)"OBJs/suzanne.obj", cube);

  generic_container* obj1 = new generic_container{"obj1", cube, NULL};
  generic_container* obj2 = new generic_container {"obj2", suzanne, obj1};

  std::cout<<obj2->parent_ptr->name;*/
  
  return 0;
}

// OpenGL thingy: 
//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);