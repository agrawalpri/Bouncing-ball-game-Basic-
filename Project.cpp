#include <GL/glut.h>
#include <iostream>
#include<bits/stdc++.h>

float ballX = 0.0f, ballY = 0.0f; // Ball position
float ballDX = 0.02f, ballDY = 0.02f; // Ball speed
float paddleX = 0.0f; // Paddle position
const float paddleWidth = 0.4f, paddleHeight = 0.05f;
int score = 0;

// Function to draw the ball
void drawBall() {
    glColor3f(1.0f, 0.0f, 0.0f); // Red ball
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float theta = i * 3.14159f / 180;
        glVertex2f(0.05f * cos(theta) + ballX, 0.05f * sin(theta) + ballY);
    }
    glEnd();
}

// Function to draw the paddle
void drawPaddle() {
    glColor3f(0.0f, 0.0f, 1.0f); // Blue paddle
    glBegin(GL_QUADS);
    glVertex2f(paddleX - paddleWidth / 2, -0.9f);
    glVertex2f(paddleX + paddleWidth / 2, -0.9f);
    glVertex2f(paddleX + paddleWidth / 2, -0.85f);
    glVertex2f(paddleX - paddleWidth / 2, -0.85f);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBall();
    drawPaddle();

    glutSwapBuffers();
}

// Update function
void update(int value) {
    // Move the ball
    ballX += ballDX;
    ballY += ballDY;

    // Ball collision with walls
    if (ballX > 1.0f || ballX < -1.0f) ballDX = -ballDX;
    if (ballY > 1.0f) ballDY = -ballDY;

    // Ball collision with paddle
    if (ballY < -0.85f && ballX > paddleX - paddleWidth / 2 && ballX < paddleX + paddleWidth / 2) {
        ballDY = -ballDY; // Bounce
        score++;
        std::cout << "Score: " << score << std::endl;
    }

    // Ball falls below the paddle (Game Over)
    if (ballY < -1.0f) {
        std::cout << "Game Over! Final Score: " << score << std::endl;
        ballX = 0.0f; ballY = 0.0f; // Reset ball
        ballDX = 0.02f; ballDY = 0.02f; // Reset speed
        score = 0; // Reset score
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 60 FPS
}

// Function to control the paddle
void keyboard(int key, int, int) {
    if (key == GLUT_KEY_LEFT && paddleX > -0.8f) paddleX -= 0.1f;
    if (key == GLUT_KEY_RIGHT && paddleX < 0.8f) paddleX += 0.1f;
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bouncing Ball Game");

    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);

    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
