
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include <vector>

using namespace std;

const char *vertexShaderSource = "#version 410\n"
                                "layout (location=0) in vec3 vp;" 
                                "layout (location=1) in vec2 vt;" 
                                "out vec2 text_map;"
                                "void main () {"
                                "   text_map = vt;"                  
                                "	gl_Position = vec4 (vp, 1.0);" 
                                "}";

const char *fragmentShaderSource = "#version 410\n"
                                    "in vec2 text_map;"
                                    "uniform sampler2D basic_texture;"
                                   "out vec4 frag_color;"
                                   "void main () {"
                                   "	 frag_color = texture(basic_texture, text_map);"
                                   "}";


bool load_texture (const char* file_name, GLuint* tex, int index) {
    int x, y, n;
    int force_channels = 4;
    glEnable(GL_TEXTURE_2D);

    unsigned char* image_data = stbi_load (file_name, &x, &y, &n, force_channels);
    if (!image_data) {
        fprintf (stderr, "ERROR: could not load %s\n", file_name);
        return false;
    }

    if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
        fprintf (
                 stderr, "WARNING: texture %s is not power-of-2 dimensions\n", file_name
                 );
    }
    
    glGenTextures (index, tex); // talvez vai ter mais
    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_2D, *tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap (GL_TEXTURE_2D);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    GLfloat max_aniso = 0.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);
    return true;
}

struct Image {
    int id;
    GLuint VAO;
    GLuint texture;
};

vector<Image> model;
 int HEIGHT = 600;
 int WIDTH = 800;

float cursorX = 0;
float cursorY = 0;


void macOSInit() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
}

float generateRandomNumber() {
    float randomNum = rand() % 101;
    return randomNum / 100;
}

Image createBox(float x0, float y0, float x1, float y1, char * imageName, int index) {

    GLfloat vertices[] = {
        x0, y0, 0.0,
        x1, y1, 0.0,
        x0, y1, 0.0,

        x0, y0, 0.0,
        x1, y1, 0.0,
        x1, y0, 0.0,
    };

    GLfloat textureMap[] = {
        0.0, 1.0,
        1.0, 0.0,
       0.0, 0.0,
    
        0.0, 1.0,
        1.0, 0.0,
        1.0, 1.0,
 
 
        
    };

    GLuint VAO, VBO, VBOTexture;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &VBOTexture);
    glBindBuffer(GL_ARRAY_BUFFER, VBOTexture);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureMap), textureMap, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    GLuint tex;
    load_texture(imageName, &tex, index);

    Image model;
    model.id = index;
    model.VAO = VAO;
    model.texture = tex;
    return model;
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_KEY_UP && action == GLFW_PRESS)
    {
      
    }
}

void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
    float oldRangeX = (WIDTH - 0);
    float newRangeX = (1 - (-1));
    float newValueX = (((xPos - 0) * newRangeX) / oldRangeX) + (-1);

    float oldRangeY = (HEIGHT - 0);
    float newRangeY = (1 - (-1));
    float newValueY = ((((HEIGHT - yPos) - 0) * newRangeY) / oldRangeY) + (-1);

    if (newValueX < -1) {
        cursorX = -1; 
    } else if (newValueX > 1) {
        cursorX = 1;
    } else {
        cursorX = newValueX;
    }

        if (newValueY < -1) {
        cursorY = -1; 
    } else if (newValueY > 1) {
        cursorY = 1;
    } else {
        cursorY = newValueY;
    }
}

int main() {

    glfwInit();
    macOSInit();

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Triangulo 3 o inimigo agora são as cores", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "*** ERRO: não foi possível abrir janela com a GLFW\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);   
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); 
    glCompileShader(vertexShader);                            

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram(); 
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    Image image = createBox(-1.0, -1.0, 0.0, 0.0, "teste.jpeg", 0);
    Image image2 = createBox(0.0, 0.0, 1.0, 1.0, "teste2.jpeg", 1);
    model.push_back(image);
     model.push_back(image2);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwGetWindowSize(window, &WIDTH, &HEIGHT);
        glViewport(0, 0, WIDTH, HEIGHT);

        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        for (int i = 0; i < model.size(); i++) {

              glBindVertexArray( model[i].VAO );
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, model[i].texture);
        glUniform1i(glGetUniformLocation(shaderProgram, "basic_texture"), model[i].id);
        glDrawArrays( GL_TRIANGLES, 0, 6);
        glBindVertexArray( 0 );
            
        }
        glfwSwapBuffers(window);

    }
     glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
