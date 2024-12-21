#include <GL/freeglut.h>
#include <iostream>

// Screen dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int mouse_x, mouse_y;
int x_1 = 200, y_1 = 400, x_3 = 500, y_3 = 550, x_4 = 400, y_4 = 250;

void init()
{
    glClearColor(0, 0, 0, 1.0);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT); // Ensure the coordinates are within screen bounds
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float maxSize;
    glGetFloatv(GL_POINT_SIZE_MAX, &maxSize);
    std::cout << "Max point size: " << maxSize << std::endl;
}

// This function will be called to update the mouse coordinates
void mouseMotion(int x, int y)
{
    mouse_x = x;                 // x-coordinate of the mouse
    mouse_y = SCREEN_HEIGHT - y; // Convert from window space to OpenGL space (Y is flipped in OpenGL)
    glutPostRedisplay();         // Request to redraw the window
}

bool checkIntersection(int *px, int *py)
{
    // Ray origin and direction
    int rayOriginX = x_1, rayOriginY = y_1;
    int rayDirX = mouse_x - x_1, rayDirY = mouse_y - y_1;

    // Line segment endpoints
    int lineStartX = x_3, lineStartY = y_3;
    int lineEndX = x_4, lineEndY = y_4;

    // Line segment direction
    int lineDirX = lineEndX - lineStartX;
    int lineDirY = lineEndY - lineStartY;

    // Compute determinant
    float det = rayDirX * lineDirY - rayDirY * lineDirX;
    if (fabs(det) < 1e-6)
    {
        // Ray and line are parallel
        return false;
    }

    // Compute intersection parameters
    float t = ((lineStartX - rayOriginX) * lineDirY - (lineStartY - rayOriginY) * lineDirX) / det;
    float u = ((lineStartX - rayOriginX) * rayDirY - (lineStartY - rayOriginY) * rayDirX) / det;

    // Check if the intersection is valid
    if (t >= 0 && u >= 0 && u <= 1)
    {
        // Intersection occurs
        *px = rayOriginX + t * rayDirX; // Intersection point X
        *py = rayOriginY + t * rayDirY; // Intersection point Y
        return true;
    }

    return false; // No intersection
}
void display()
{
    int px, py;
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Set up the color for the lines (White)
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw the lines
    glBegin(GL_LINES);

    // Define the first line (from x_1, y_1 to mouse_x, mouse_y)
    glVertex2f(x_1, y_1);         // Starting point of the ray
    glVertex2f(mouse_x, mouse_y); // Ray direction (mouse position)

    // Define the second line (from x_3, y_3 to x_4, y_4)
    glVertex2f(x_3, y_3); // Line segment start
    glVertex2f(x_4, y_4); // Line segment end

    glEnd();

    // Check for intersection
    if (checkIntersection(&px, &py))
    {
        // Set color to green for the intersection point
        glEnable(GL_POINT_SMOOTH);
        glColor3f(0.0f, 1.0f, 0.0f);
        // Set the size of the point
        glPointSize(64.0f); // Size in pixels

        // Render the intersection point
        glPointSize(5.0f); // Increase point size for visibility
        glBegin(GL_POINTS);
        std::cout << "Intersection at: " << px << ", " << py << std::endl;
        glVertex2f(static_cast<float>(px), static_cast<float>(py)); // Specify intersection point
        glEnd();
    }

    glFlush(); // Ensure all OpenGL commands are executed
}

// Main function to set up OpenGL window
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Line Intersection");

    init();

    // Register the mouse motion callback
    glutPassiveMotionFunc(mouseMotion); // Called when the mouse is moved
    glutDisplayFunc(display);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}