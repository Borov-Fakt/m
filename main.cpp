#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>

const double PI = 3.14159265358979323846;

// Настройка области видимости с сохранением пропорций
void setupOrtho(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double aspect = (double)width / (double)height;
    double xRange = 20.0; // от -20 до 20 по X (хватает для 6pi)
    double yRange = 5.0;  // от -5 до 5 по Y

    if (width >= height)
        glOrtho(-xRange * aspect, xRange * aspect, -yRange, yRange, -1, 1);
    else
        glOrtho(-xRange, xRange, -yRange / aspect, yRange / aspect, -1, 1);

    glMatrixMode(GL_MODELVIEW);
}

void drawAxes() {
    glColor3f(0.5f, 0.5f, 0.5f); // Серый цвет для осей
    glBegin(GL_LINES);
    // Ось X
    glVertex2f(-20, 0); glVertex2f(20, 0);
    // Стрелочка X
    glVertex2f(20, 0); glVertex2f(19.5, 0.2);
    glVertex2f(20, 0); glVertex2f(19.5, -0.2);

    // Ось Y
    glVertex2f(0, -10); glVertex2f(0, 10);
    // Стрелочка Y
    glVertex2f(0, 5); glVertex2f(0.2, 4.5);
    glVertex2f(0, 5); glVertex2f(-0.2, 4.5);
    glEnd();

    // Деления (засечки)
    glBegin(GL_LINES);
    for (float i = -19; i < 19; i++) {
        glVertex2f(i, -0.1); glVertex2f(i, 0.1); // по X
    }
    for (float i = -5; i < 5; i++) {
        glVertex2f(-0.1, i); glVertex2f(0.1, i); // по Y
    }
    glEnd();
}

void drawGraph() {
    glColor3f(0.0f, 1.0f, 0.0f); // Зеленый график
    glBegin(GL_LINE_STRIP);
    for (double x = -6 * PI; x <= 6 * PI; x += 0.05) {
        double y = sin(3 * x) + cos(2 * x + 12);
        glVertex2d(x, y);
    }
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "Graph: sin(3x) + cos(2x+12)", NULL, NULL);
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        setupOrtho(w, h);

        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        drawAxes();
        drawGraph();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}