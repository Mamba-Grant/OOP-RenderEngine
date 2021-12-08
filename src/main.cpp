#include "../freeglut-3.2.1/include/GL/freeglut.h"

#include "../linker/glm/glm.hpp"
#include "../linker/glm/gtx/string_cast.hpp"
#include "../linker/importOBJ.h"
#include "../linker/datatypes/generic_class.h"

#include <iostream>

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // Rotate the scene so we can see the tops of the shapes.
  glRotatef(-20.0, 1.0, 0.0, 0.0);

  // add a torus
  glPushMatrix();
  glTranslatef(-0.75, 0.5, 0.0);
  //glRotatef(90.0, 1.0, 0.0, 0.0);
  glutSolidTorus(0.275, 0.85, 16, 40);
  glPopMatrix();

  // add a cone
  glPushMatrix();
  glTranslatef(-0.75, -0.5, 0.0);
  //glRotatef(270.0, 1.0, 0.0, 0.0);
  glutSolidCone(1.0, 2.0, 70, 12);
  glPopMatrix();

  // Add a sphere
  glPushMatrix();
  //glTranslatef(0.75, 0.0, -1.0);
  glutSolidSphere(1.0, 30, 30);
  glPopMatrix();

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
  GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
  GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat direction[] = { 1.0, 1.0, 1.0, 0.0 };

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
  glMaterialfv(GL_FRONT, GL_SPECULAR, white);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);

  glLightfv(GL_LIGHT0, GL_AMBIENT, black);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  glLightfv(GL_LIGHT0, GL_POSITION, direction);

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
  glutCreateWindow("Cyan Shapes in Yellow Light");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  init();
  glutMainLoop();

  mesh* cube = new mesh;
  import((char*)"OBJs/cube.obj", cube);
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