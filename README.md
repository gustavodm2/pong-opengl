Pong Game com Obstáculos
Este projeto implementa um jogo de Pong simples com obstáculos, utilizando a biblioteca OpenGL para renderização e GLFW para gerenciamento de janelas e entrada do usuário. O objetivo é criar uma variante de Pong com obstáculos fixos no meio da tela.

Pré-requisitos
GLFW
GLEW
Instalação
Instale as dependências necessárias (GLFW e GLEW).

Compile o código utilizando um compilador compatível com OpenGL (como g++):

bash
Copy code
g++ main.cpp -o pong -lglfw -lGLEW -lGL
Execute o programa:

bash
Copy code
./pong
Controles
Jogador 1 (esquerda):

W: Mover para cima
S: Mover para baixo
Jogador 2 (direita):

Seta para cima: Mover para cima
Seta para baixo: Mover para baixo
Funcionalidades
Dois paddles controlados por jogadores.
Bola que se move pela tela e rebate nos paddles, nas bordas da tela e nos obstáculos.
Três obstáculos fixos no meio da tela que alteram a trajetória da bola ao colidir.
Licença
Este projeto é de código aberto e está sob a licença MIT.
