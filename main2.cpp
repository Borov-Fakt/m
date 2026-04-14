#define _CRT_SECURE_NO_WARNINGS
#include <GLFW/glfw3.h>
#include <cmath>
#include <ctime>
// ... остальной код

const double PI = 3.1415926535;

void drawCircle(float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * float(i) / float(segments);
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
}

void drawHand(float angle, float length, float width, float r, float g, float b) {
    glLineWidth(width);
    glColor3f(r, g, b);
    glPushMatrix();
    glRotatef(-angle, 0, 0, 1); // Поворот по часовой стрелке
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, length);
    glEnd();
    glPopMatrix();
}

// Рисование цифр примитивами (упрощенно палочками)
void drawNumber12() {
    glLineWidth(2);
    // Единица
    glBegin(GL_LINES);
    glVertex2f(-0.05, 0.85); glVertex2f(-0.05, 0.95);
    // Двойка
    glVertex2f(0.02, 0.95); glVertex2f(0.08, 0.95);
    glVertex2f(0.08, 0.95); glVertex2f(0.08, 0.90);
    glVertex2f(0.08, 0.90); glVertex2f(0.02, 0.90);
    glVertex2f(0.02, 0.90); glVertex2f(0.02, 0.85);
    glVertex2f(0.02, 0.85); glVertex2f(0.08, 0.85);
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(600, 600, "Analog Clock", NULL, NULL);
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        // Циферблат
        glColor3f(1, 1, 1);
        drawCircle(0.9f, 100);
        drawNumber12();

        // Получаем время
        time_t t = time(0);
        struct tm* now = localtime(&t);

        float s_angle = now->tm_sec * 6.0f;
        float m_angle = now->tm_min * 6.0f + now->tm_sec * 0.1f;
        float h_angle = (now->tm_hour % 12) * 30.0f + now->tm_min * 0.5f;

        // Рисуем стрелки
        drawHand(s_angle, 0.8f, 1.0f, 1.0f, 0.0f, 0.0f); // Секундная (красная)
        drawHand(m_angle, 0.7f, 3.0f, 1.0f, 1.0f, 1.0f); // Минутная (белая)
        drawHand(h_angle, 0.5f, 5.0f, 0.0f, 0.7f, 1.0f); // Часовая (синяя)

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}