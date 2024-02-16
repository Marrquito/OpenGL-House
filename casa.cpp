/**
 * Copyright 2024 <Marco Antonio Cunha Cossetin 20200011020>
 * g++ atv2.cpp -lGL -lGLU -lglut -o gl_app
 * */

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#define WIDTH           800
#define HEIGHT          600

#define INITIAL_WIDTH   600
#define INITIAL_HEIGHT  250

int SCREEN_WIDTH        = 0;
int SCREEN_HEIGHT       = 0;
bool DRAW_CLOUDS        = true;
bool DRAW_RAIN_CLOUDS   = false;

struct Raindrop {
    float x;
    float y;
    float speed;

    Raindrop(float x, float y, float speed) : x(x), y(y), speed(speed) {}
};

vector<Raindrop> raindrops;

void initGLUT(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(WIDTH, HEIGHT);
    
    SCREEN_WIDTH    = glutGet(GLUT_SCREEN_WIDTH); 
    SCREEN_HEIGHT   = glutGet(GLUT_SCREEN_HEIGHT); 
    
    glutInitWindowPosition(INITIAL_WIDTH, INITIAL_HEIGHT);

    glutCreateWindow("Casinha com OpenGL");
}

void setup()
{
    glClearColor(0.98f, 0.0117f, 0.925f, 1.0f); 
    
    glClear(GL_COLOR_BUFFER_BIT);

    gluOrtho2D(0, WIDTH, HEIGHT, 0);
}

void draw_circle(GLfloat cx, GLfloat cy, float radius, int segments)
{
    glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i <= segments; ++i)
        {
            float theta = (2.0f * M_PI * static_cast<float>(i)) / static_cast<float>(segments);
            
            float x = radius * cos(theta);
            float y = radius * sin(theta);

            glVertex2f(x + cx, y + cy);
        }
    glEnd();
}

void draw_cloud(GLfloat xStart, GLfloat yStart)
{
    int xIncremente = 30;

    draw_circle(xStart+=xIncremente, yStart, 30.0f, 100);
    draw_circle(xStart+=xIncremente, yStart, 40.0f, 100);
    draw_circle(xStart+=xIncremente, yStart, 35.0f, 100);
    draw_circle(xStart+=xIncremente, yStart, 25.0f, 100);
    draw_circle(xStart+=xIncremente, yStart, 35.0f, 100);
}

void draw_point(GLint x, GLint y)
{
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

void draw_square(GLint xi, GLint yi, GLint xf, GLint yf, GLboolean setColor)
{
    if  (setColor)
    {
        if (!DRAW_CLOUDS)   glColor3f(0.75f, 0.8f, 0.09f);
        else                glColor3f(1.0f, 1.0f, 1.0f);
    }

    glBegin(GL_QUADS);

        glVertex2i(xi, yi);
        glVertex2i(xf, yi);
        glVertex2i(xf, yf);
        glVertex2i(xi, yf);
    glEnd();
}

void draw_line(GLfloat xi, GLfloat yi, GLfloat xf, GLfloat yf)
{
    glBegin(GL_LINES | GL_LINE_STRIP | GL_LINE_LOOP);
        glVertex2f(xi, yi);
        glVertex2f(xf, yf);

    glEnd();
}

void draw_house()
{
    // telhado pt1 
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(400.0f, 150.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(500.0f, 300.0f);
        
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(300.0f, 300.0f);
    glEnd();

    // base da casa
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(300.0f, 300.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(700.0f, 300.0f);

        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex2f(700.0f, 450.0f);
        
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(300.0f, 450.0f);
    glEnd();

    // telhado pt2
    glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(400.0f, 150.0f);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(600.0f, 150.0f);

        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex2f(700.0f, 300.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(500.0f, 300.0f);
    glEnd();

    // porta
    glColor3f(0.54f, 0.27f, 0.07f);
    draw_square(330.0f, 365.0f, 390.0f, 465.0f, false);
    
    // maçaneta da porta
    glColor3f(0.41f, 0.41f, 0.41f);
    draw_point(340.0f, 420.0f);

    // janelinha 1
    draw_square(540.0f, 335.0f, 590.0f, 375.0f, true);

    // janelinha 2
    draw_square(630.0f, 335.0f, 680.0f, 375.0f, true);

    // linha vertical janela1
    glColor3f(0.0f, 0.0f, 0.0f);
    draw_line(565.0f, 335.0f, 565.0f, 375.0f);
    draw_line(540.0f, 355.0f, 590.0f, 355.0f);
    
    // linhas janela2
    draw_line(655.0f, 335.0f, 655.0f, 375.0f);
    draw_line(630.0f, 355.0f, 680.0f, 355.0f);

    glColor3f(0.0f, 0.0f, 0.0f);

    // telhas e contornos da casa
    GLfloat xiv = 400.0f, xfv = 500.0f;
    GLfloat xih = 400.0f, yih = 150.0f, xfh = 600.0f, yfh = 300.0f;

    while ((xiv != 600.0f && xfv != 700) || (yih <= yfh))
    {
        if (xiv != 600.0f && xfv != 700)
        {
            draw_line(xiv, 150.0f, xfv, 300.0f);

            xiv += 10.0f;
            xfv += 10.0f;
        }

        if (yih <= yfh) 
        {
            draw_line(xih, yih, xfh, yih);

            yih += 10.0f;
            xih += 6.5f;
            xfh += 6.5f;
        }
    }

    // contorno triangulo
    draw_line(300.0f, 300.0f, 700.0f, 300.0f);
    draw_line(300.0f, 300.0f, 400.0f, 150.0f);

    // 1° linha base da casa
    draw_line(300.0f, 300.0f, 300.0f, 450.0f);
    
    // linha meio casa
    draw_line(500.0f, 300.0f, 500.0f, 450.0f);

    // ultima linha base da casa
    draw_line(700.0f, 300.0f, 700.0f, 450.0f);

    // chao da casa
    draw_line(300.0f, 450.0f, 700.0f, 450.0f);

    // final 2 telhado
    draw_line(600.0f, 150.0f, 700.0f, 300.0f);

    // janela teto principal
    if (!DRAW_CLOUDS)   glColor3f(0.75f, 0.8f, 0.09f);
    else                glColor3f(1.0f, 1.0f, 1.0f);
    draw_circle(400.0f, 250.0f, 25.0f, 100);
    
    glColor3f(0.0f, 0.0f, 0.0f);

    draw_line(400.0f, 225.0f, 400.0f, 275.0f);
    draw_line(375.0f, 250.0f, 425.0f, 250.0f);
}

void draw_star(GLfloat x, GLfloat y)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);
        glVertex2f(x, y + 5.0f);
        glVertex2f(x - 1.0f, y);
        glVertex2f(x + 1.0f, y);

        glVertex2f(x, y - 5.0f);
        glVertex2f(x - 1.0f, y);
        glVertex2f(x + 1.0f, y);
    glEnd();
}

void updateRain()
{
    if (DRAW_RAIN_CLOUDS) 
    {
        for (auto& raindrop : raindrops)
        {
            raindrop.y += raindrop.speed;
            if (raindrop.y >= HEIGHT) raindrop.y = 75;
        }
    }
}

void draw_raindrop(GLfloat x, GLfloat y)
{
    glColor3f(0.0f, 0.5f, 1.0f);

    glBegin(GL_LINES);
        glVertex2f(x+7, y+7);
        glVertex2f(x, y - 5.0f); 
    glEnd();
}

void draw_rainScene()
{
    for (const auto& raindrop : raindrops)
    {
        draw_raindrop(raindrop.x, raindrop.y);
    }
}

void draw_nightScene()
{
    srand(0);
    for (int i = 0; i < 100; ++i)
    {
        float x = rand() % WIDTH; 
        float y = rand() % HEIGHT;

        draw_star(x, y);
    }
}

void update(int value)
{
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void draw_tree()
{
    // tronco
    glColor3f(0.5, 0.35, 0.05); 
    glBegin(GL_POLYGON);
        glVertex2f(190, 350);
        glVertex2f(210, 350);
        glVertex2f(210, 450);
        glVertex2f(190, 450);
    glEnd();

    // folhas
    glColor3f(0.0, 0.5, 0.0); 
    glBegin(GL_TRIANGLES);
        glVertex2f(200, 300);
        glVertex2f(180, 395);
        glVertex2f(220, 395);
    glEnd();
}

void draw_bird(GLfloat x, GLfloat y)
{
    // corpo
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + 10, y - 10);
        glVertex2f(x + 20, y);
        glVertex2f(x + 10, y + 10);
    glEnd();

    // cabeça
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x + 20, y);
        for (int i = 0; i <= 360; i += 10) glVertex2f(x + 20 + 5 * cos(i * 3.14 / 180), y + 5 * sin(i * 3.14 / 180));
        
    glEnd();
}

void draw() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(10);

    if (DRAW_CLOUDS)
    {   
        if (DRAW_RAIN_CLOUDS)   
        {
            glColor3f(0.41f, 0.41f, 0.41f);
            draw_rainScene();
            updateRain();
        }
        else glColor3f(0.7f, 1.0f, 1.0f);

        draw_cloud(100, 75);
        draw_cloud(250, 75);
        draw_cloud(550, 90);
    }
    else draw_nightScene();

    draw_house();
    
    // grama
    if (DRAW_RAIN_CLOUDS && DRAW_CLOUDS)    glColor3f(0.33f, 0.419f, 0.18f);
    else                                    glColor3f(0.13f, 0.54f, 0.13f);
    draw_square(0.0f, 450.0f, WIDTH, HEIGHT, false);

    // Desenha o caminho
    glColor3f(0.5f, 0.5f, 0.5f);
    draw_square(330.0f, 450.0f, 390.0f, HEIGHT, false);
    
    draw_tree();

    if (DRAW_CLOUDS && !DRAW_RAIN_CLOUDS)
    {
        draw_bird(100.0, 150.0);
        draw_bird(200.0, 200.0);
        draw_bird(300.0, 50.0);
    }
    
    glFlush();
}

void keyboard_handle(GLubyte key, GLint x, GLint y)
{
    if ((glutGetModifiers() == GLUT_ACTIVE_CTRL) && key == 0)
    {
        cout << "Mudando para noite... " << endl;

        DRAW_CLOUDS = false;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glutPostRedisplay();
    }
    else 
    {
        cout << "Mudando para dia claro... " << endl;
        DRAW_CLOUDS         = true;
        DRAW_RAIN_CLOUDS    = false;

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glutPostRedisplay();
    }
}

void mouse_handle(GLint button, GLint action, GLint x, GLint y)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        printf("Clicou com o botao esquerdo!\n");
    } 
    else if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
    {
        printf("Clicou com o botao direito!\n");
    }
}

void especialKey_handle(int key, int x, int y)
{   
    cout << "Tecla especial precionada. Mudando fundo para cor cinza!" << endl;
    
    DRAW_CLOUDS      = true;
    DRAW_RAIN_CLOUDS = true;
    
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glutPostRedisplay();
}

void initRain()
{
    for (int i = 0; i < 750; ++i)
    {
        float x = rand() % WIDTH; 
        float y = rand() % HEIGHT;

        float speed = static_cast<float>(rand() % 5 + 1);

        raindrops.emplace_back(x, y, speed);
    }
}

int main(int argc, char** argv)
{
    cout << "Iniciando GLUT" << endl;

    initGLUT(argc, argv);
    setup();

    initRain();

    glutDisplayFunc(draw);

    glutSpecialFunc(especialKey_handle);
    glutKeyboardFunc(keyboard_handle);
    glutMouseFunc(mouse_handle);

    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}