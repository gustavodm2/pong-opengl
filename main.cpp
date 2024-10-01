#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const int Width = 800;
const int Height = 600;

float paddleWidth = 5.0f;
float paddleHeight = 25.0f;
float ballSize = 10.0f;
float obstacleWidth = 20.0f;
float obstacleHeight = 60.0f;

float leftPaddleY = Height / 2 - paddleHeight / 2;
float rightPaddleY = Height / 2 - paddleHeight / 2;
float ballX = Width / 2 - ballSize / 2;
float ballY = Height / 2 - ballSize / 2;
float obstacleX = Width / 2 - obstacleWidth / 2;
float obstacleY[] = { 150.0f, 300.0f, 450.0f }; 

float ballSpeedX = 5.0f;
float ballSpeedY = 5.0f;
float paddleSpeed = 10.0f;

void drawPaddle(float x, float y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + paddleWidth, y);
    glVertex2f(x + paddleWidth, y + paddleHeight);
    glVertex2f(x, y + paddleHeight);
    glEnd();
}

void drawBall(float x, float y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + ballSize, y);
    glVertex2f(x + ballSize, y + ballSize);
    glVertex2f(x, y + ballSize);
    glEnd();
}

void drawObstacle(float x, float y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + obstacleWidth, y);
    glVertex2f(x + obstacleWidth, y + obstacleHeight);
    glVertex2f(x, y + obstacleHeight);
    glEnd();
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && leftPaddleY + paddleHeight < Height) {
        leftPaddleY += paddleSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && leftPaddleY > 0) {
        leftPaddleY -= paddleSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && rightPaddleY + paddleHeight < Height) {
        rightPaddleY += paddleSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && rightPaddleY > 0) {
        rightPaddleY -= paddleSpeed;
    }
}

int main() {
  
    if (!glfwInit()) {
        std::cout << "Erro ao inicializar o GLFW" << std::endl;
        return 1;
    }

    
    GLFWwindow* Window = glfwCreateWindow(Width, Height, "Pong Game com Obstáculos", nullptr, nullptr);
    if (!Window) {
        std::cout << "Erro ao criar janela" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1); 
    glewInit();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, Width, 0.0f, Height, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(Window)) {
       
        glClear(GL_COLOR_BUFFER_BIT);

      
        processInput(Window);

        glColor3f(0.0f, 0.7f, 0.7f); 
        drawPaddle(20.0f, leftPaddleY);

        glColor3f(0.7f, 0.0f, 0.7f);
        drawPaddle(Width - 30.0f, rightPaddleY);

        glColor3f(1.0f, 1.0f, 0.0f); 
        drawBall(ballX, ballY);

        glColor3f(0.5f, 0.5f, 0.5f);
        for (int i = 0; i < 3; ++i) {
            drawObstacle(obstacleX, obstacleY[i]);
        }

        ballX += ballSpeedX;
        ballY += ballSpeedY;

        if (ballY <= 0 || ballY >= Height - ballSize) {
            ballSpeedY = -ballSpeedY;
        }

        if ((ballX <= 30.0f && ballY + ballSize >= leftPaddleY && ballY <= leftPaddleY + paddleHeight) ||
            (ballX + ballSize >= Width - 30.0f && ballY + ballSize >= rightPaddleY && ballY <= rightPaddleY + paddleHeight)) {
            ballSpeedX = -ballSpeedX;
        }

        for (int i = 0; i < 3; ++i) {
            if (ballX + ballSize >= obstacleX && ballX <= obstacleX + obstacleWidth &&
                ballY + ballSize >= obstacleY[i] && ballY <= obstacleY[i] + obstacleHeight) {
                ballSpeedX = -ballSpeedX; 
                break;  
            }
        }

        if (ballX < 0 || ballX > Width) {
         
            ballX = Width / 2 - ballSize / 2;
            ballY = Height / 2 - ballSize / 2;
            ballSpeedX = 5.0f * (ballSpeedX > 0 ? 1 : -1); 
        }

     
        glfwPollEvents();
        glfwSwapBuffers(Window);
    }

   
    glfwTerminate();
    return 0;
}
