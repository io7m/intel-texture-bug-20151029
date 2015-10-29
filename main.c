#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
  GLFWwindow* context0;
  GLFWwindow* context1;
  int clear = 0;

  if (argc > 1) {
    clear = strcmp(argv[1], "clear") == 0;
    fprintf(stderr, "Periodically clearing\n");
  } else {
    fprintf(stderr, "Not periodically clearing\n");
  }

  if (!glfwInit()) {
    fprintf(stderr, "Unable to initialize\n");
    return -1;
  }

  glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  context0 = glfwCreateWindow(320, 240, "Main", NULL, NULL);
  if (!context0) {
    fprintf(stderr, "Unable to create context0\n");
    glfwTerminate();
    return -1;
  }

  fprintf(stderr, "Created context0\n");

  context1 = glfwCreateWindow(320, 240, "Main", NULL, context0);
  if (!context1) {
    fprintf(stderr, "Unable to create context1\n");
    glfwTerminate();
    return -1;
  }

  fprintf(stderr, "Created context1\n");

  for (;;) {
    GLuint tex_id;

    // Allocate a texture
    glfwMakeContextCurrent(context1);
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *) 0L);
    glBindTexture(GL_TEXTURE_2D, 0);
    glfwMakeContextCurrent(NULL);

    // Reference the texture
    glfwMakeContextCurrent(context0);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (clear) glClear(GL_COLOR_BUFFER_BIT);
    glfwMakeContextCurrent(NULL);

    // Deallocate the texture
    glfwMakeContextCurrent(context1);
    glDeleteTextures(1, &tex_id);
    glfwMakeContextCurrent(NULL);
  }

  glfwTerminate();
  return 0;
}
