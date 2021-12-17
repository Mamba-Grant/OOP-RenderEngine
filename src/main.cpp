// OpenGL related libraries
  #include "../include/GL/glew.h"
  #include "../include/freeglut-3.2.1/include/GL/freeglut.h"
  #include "../include/glm/gtx/string_cast.hpp"
  #include "../include/glm/gtc/type_ptr.hpp"

// these are essentially just the base of the OpenGL rendering things
// had trouble getting OpenGL to not be super buggy so I had to switch to using some pre-made classes to sort it out
  #include "../include/tutorial/shaderClass.h"
  #include "../include/tutorial/VAO.h"
  #include "../include/tutorial/VBO.h"
  #include "../include/tutorial/EBO.h"
  #include "../include/tutorial/Camera.h"
// for some reason replit is not having a good time with just the header files, so cpp files to make sure they're included
  #include "../include/tutorial/shaderClass.cpp"
  #include "../include/tutorial/VAO.cpp"
  #include "../include/tutorial/VBO.cpp"
  #include "../include/tutorial/EBO.cpp"
  #include "../include/tutorial/Camera.cpp"

// my own files once again
  #include "../include/importOBJ.h"
  #include "../include/datatypes/mesh.h"
  #include "../include/datatypes/generic_class.h"
  #include "../include/datatypes/scene.h"

// the chosen one
  #include <iostream>
  
unsigned int width = 720/2;
unsigned int height = 480/2;
scene* MAIN_SCENE = new scene;

void initmesh(std::vector <vertex> vertices, std::vector <GLuint>& indices, VAO VAO) {
  VAO.Bind();
  // Generates Vertex Buffer Object and links it to vertices
  VBO VBO(vertices);
  // Generates Element Buffer Object and links it to indices
  EBO EBO(indices);
  // Links VBO attributes such as coordinates and colors to VAO
  VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);
  VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(glm::vec3), (void*)(3 * sizeof(float)));
  VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(glm::vec3), (void*)(6 * sizeof(float)));
  VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(glm::vec3), (void*)(9 * sizeof(float)));
  // Unbind all to prevent accidentally modifying them
  VAO.Unbind();
  VBO.Unbind();
  EBO.Unbind();
}

// draw mesh (oh boy thats a lof of parameters)
void draw(Shader& shader, 
  Camera& camera,
  VAO VAO,
  std::vector<GLuint> vertexIndices,
  glm::mat4 matrix = glm::mat4(1.0f),
  glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
  glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
  glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
  ) {
  // Bind shader to be able to access uniforms
  shader.Activate();
  VAO.Bind();

  // Take care of the camera Matrix
  glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
  camera.Matrix(shader, "camMatrix");

  // Initialize matrices
  glm::mat4 trans = glm::mat4(1.0f);
  glm::mat4 rot = glm::mat4(1.0f);
  glm::mat4 sca = glm::mat4(1.0f);

  // Transform the matrices to their correct form
  trans = glm::translate(trans, translation);
  rot = glm::mat4_cast(rotation);
  sca = glm::scale(sca, scale);

  // Push the matrices to the vertex shader
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

  // Draw the actual mesh
  glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, 0);
}


void display() {

  Shader shaderProgram("../include/tutorial/default.vert", "../include/tutorial/default.frag");

  Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// lighting things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

  // set up the shader program
	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Enables the Depth Buffer - this is important so OpenGL knows how to draw geometry which is occluded
	glEnable(GL_DEPTH_TEST);

  // background
  glClearColor(0.77f, 0.83f, 0.87f, 1.0f);
  // clear buffers (we start rendering things in the window here)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // export camera data to shader (tell the shader that there is a camera)
  camera.updateMatrix(45.0f, 0.1f, 100.0f);

  // 
	// ACTUALLY DISPLAY THE MODEL
  // 

  // create a VAO for the first mesh (cube)
  VAO VAO1;
  // initialize buffers/bufferdata
  initmesh(MAIN_SCENE->SCENE_CHILDREN[0]->skinned_mesh_ptr->vertices, MAIN_SCENE->SCENE_CHILDREN[0]->skinned_mesh_ptr->vertexIndices, VAO1);
  // if I remember correctly:
  // the first vec3 is position, the quaternion is rotation, and the last vec3 is scale for the function below
  // formatted as (x,y,z) or (w,x,y,z) for quaternion
  // x is the horizontal, y is up, z is out
  // draw the program
  draw(shaderProgram, camera, VAO1, MAIN_SCENE->SCENE_CHILDREN[0]->skinned_mesh_ptr->vertexIndices, glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) );

  // same thing as above with 2nd mesh (suzanne monkey)
  VAO VAO2;
  initmesh(MAIN_SCENE->SCENE_CHILDREN[0]->parent_ptr->skinned_mesh_ptr->vertices, MAIN_SCENE->SCENE_CHILDREN[0]->parent_ptr->skinned_mesh_ptr->vertexIndices, VAO2);
  draw(shaderProgram, camera, VAO1, MAIN_SCENE->SCENE_CHILDREN[0]->parent_ptr->skinned_mesh_ptr->vertexIndices, glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::quat(1.0f, 0.3f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) );

  glutSwapBuffers();
  //glFlush();
}

void precompile_demo_files() {
  // thanks to the file structure it is possible to create objects to be rendered outside of the display loop- allows for organizing and pre-compiling of necessary things before running the function
  // all resources used in the program are compiled here and made relative to the scene

  // the camera object (woo)
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
  MAIN_SCENE->MAIN_SCENE_CAMERA = &camera;

  mesh* suzanne = new mesh;
  generic_container* suzanne_container = new generic_container;
  suzanne_container->skinned_mesh_ptr = suzanne;
  import( (char*)"OBJs/suzanne.obj", suzanne );
  // fairly sure there is a problem with how data is imported and prepped for displaying
  // seems to be improperly indexed...
  // either way it displays something, even if it is scrambled

  mesh* cube = new mesh;
  generic_container* cube_container = new generic_container;
  cube_container->skinned_mesh_ptr = cube;
  cube_container->parent_ptr = suzanne_container;
  import( (char*)"OBJs/cube.obj", cube);

  
  // end of branch so:
  // previously not reserving caused a segfault, although that has seemingly been fixed - leaving it in just in case
  MAIN_SCENE->SCENE_CHILDREN.reserve(1);
  MAIN_SCENE->SCENE_CHILDREN.push_back(cube_container);
  return;
}

int main(int argc, char** argv) {

  precompile_demo_files();

  // ready GLUT window:
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutInitContextVersion(3,3);
    
  glutInitWindowSize(width, height);
  glutCreateWindow("This is a Monkey and Cube (if you could not tell)");

  // initialize GLEW
  glewInit();

  // display things
  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}