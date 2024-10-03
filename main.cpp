#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// defini��o de constantes de largura e altura da janela
const int Width = 800;
const int Height = 600;

// dimens�es do paddle, bola e obst�culos
float paddleWidth = 5.0f;
float paddleHeight = 25.0f;
float ballSize = 10.0f;
float obstacleWidth = 20.0f;
float obstacleHeight = 60.0f;

// posi��es iniciais dos elementos
float leftPaddleY = Height / 2 - paddleHeight / 2;
float rightPaddleY = Height / 2 - paddleHeight / 2;
float ballX = Width / 2 - ballSize / 2;
float ballY = Height / 2 - ballSize / 2;
float obstacleX = Width / 2 - obstacleWidth / 2;
float obstacleY[] = { 150.0f, 300.0f, 450.0f }; // Posi��es dos obst�culos

// velocidade da bola e do paddle
float ballSpeedX = 2.0f;
float ballSpeedY = 2.0f;
float paddleSpeed = 5.0f;

// fun��o para renderizar um paddle na tela
void drawPaddle(float x, float y) {
    glBegin(GL_QUADS); // cria quadrado (paddle)
    glVertex2f(x, y);
    glVertex2f(x + paddleWidth, y);
    glVertex2f(x + paddleWidth, y + paddleHeight);
    glVertex2f(x, y + paddleHeight); 
    glEnd(); 
}

// fun��o para renderizar a bola na tela
void drawBall(float x, float y) {
    glBegin(GL_QUADS); // cria quadrado (bola)
    glVertex2f(x, y); 
    glVertex2f(x + ballSize, y); 
    glVertex2f(x + ballSize, y + ballSize); 
    glVertex2f(x, y + ballSize); 
    glEnd();
}

// fun��o para renderizar obst�culos na tela
void drawObstacle(float x, float y) {
    glBegin(GL_QUADS); // cria quadrado (obst�culo)
    glVertex2f(x, y); 
    glVertex2f(x + obstacleWidth, y); 
    glVertex2f(x + obstacleWidth, y + obstacleHeight);
    glVertex2f(x, y + obstacleHeight); 
    glEnd();
}

// fun��o para processar entradas do usu�rio
void processInput(GLFWwindow* window) {
    // paddle esquerdo (W e S)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && leftPaddleY + paddleHeight < Height) {
        leftPaddleY += paddleSpeed; //  cima
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && leftPaddleY > 0) {
        leftPaddleY -= paddleSpeed; //  baixo
    }

    // paddle direito (seta pra cima e pra baixo)
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && rightPaddleY + paddleHeight < Height) {
        rightPaddleY += paddleSpeed; //  cima
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && rightPaddleY > 0) {
        rightPaddleY -= paddleSpeed; //  baixo
    }
}

int main() {
  
    if (!glfwInit()) {
        std::cout << "Erro ao inicializar o GLFW" << std::endl;
        return 1;
    }

    // cria uma janela 
    GLFWwindow* Window = glfwCreateWindow(Width, Height, "Pong Game com Obst�culos", nullptr, nullptr);
    if (!Window) {
        std::cout << "Erro ao criar janela" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Configura o contexto e ativa a sincroniza��o vertical
    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1);
    glewInit();

    // cor de fundo da janela
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // proje��o ortogr�fica
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, Width, 0.0f, Height, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(Window)) {
        glClear(GL_COLOR_BUFFER_BIT); 

        processInput(Window); // processa entradas do usu�rio

        // Renderiza os paddles
        glColor3f(0.0f, 0.7f, 0.7f); 
        drawPaddle(20.0f, leftPaddleY);

        glColor3f(0.7f, 0.0f, 0.7f); 
        drawPaddle(Width - 30.0f, rightPaddleY);

        // bola
        glColor3f(1.0f, 1.0f, 0.0f);
        drawBall(ballX, ballY);

        // obst�culos
        glColor3f(0.5f, 0.5f, 0.5f);
        for (int i = 0; i < 3; ++i) {
            drawObstacle(obstacleX, obstacleY[i]);
        }

        // posi��o da bola
        ballX += ballSpeedX;
        ballY += ballSpeedY;

        // colis�es da bola com as bordas superiores e inferiores
        if (ballY <= 0 || ballY >= Height - ballSize) {
            ballSpeedY = -ballSpeedY; // inverte a dire��o vertical da bola
        }

        // colis�es da bola com os paddles
        if ((ballX <= 30.0f && ballY + ballSize >= leftPaddleY && ballY <= leftPaddleY + paddleHeight) ||
            (ballX + ballSize >= Width - 30.0f && ballY + ballSize >= rightPaddleY && ballY <= rightPaddleY + paddleHeight)) {
            ballSpeedX = -ballSpeedX; // inverte a dire��o horizontal da bola
        }

        // Detecta colis�es da bola com os obst�culos
        for (int i = 0; i < 3; ++i) {
            if (ballX + ballSize >= obstacleX && ballX <= obstacleX + obstacleWidth &&
                ballY + ballSize >= obstacleY[i] && ballY <= obstacleY[i] + obstacleHeight) {
                ballSpeedX = -ballSpeedX; // inverte a dire��o horizontal da bola ao colidir com obst�culo
                break;
            }
        }

        // restarta a bola se ela sair da tela
        if (ballX < 0 || ballX > Width) {
            ballX = Width / 2 - ballSize / 2;
            ballY = Height / 2 - ballSize / 2;
            ballSpeedX = 2.0f * (ballSpeedX > 0 ? 1 : -1); // reseta a velocidade da bola
        }

        glfwPollEvents();
        glfwSwapBuffers(Window);
    }


    glfwTerminate();
    return 0;
}
