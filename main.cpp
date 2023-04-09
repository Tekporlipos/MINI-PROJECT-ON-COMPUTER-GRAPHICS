#include <GL/glut.h> // Include the GLUT library to create a window
#include <stdio.h>
    // Define the initial position and size of the train
    GLfloat trainPos = 0.0f;
    GLfloat signalColor = 0.0f; // red signal
    GLfloat cometX = -10.0f;
    GLfloat cometY = 10.0f;
    GLfloat cometVelX = 0.1f;
    GLfloat cometVelY = -0.05f;
    bool isNightMode = false;
    bool signalState = false;
    const BOOL GREEN = true;
    const BOOL RED = true;
    const float PI = 3.14159265358979323846;
    const int NUM_SEGMENTS = 50;
    const GLfloat TRAIN_LENGTH = 20.0f;
    const GLfloat TRAIN_WIDTH = 5.0f;
    const GLfloat TRAIN_HEIGHT = 5.0f;
    const GLfloat WHEEL_RADIUS = 1.5f;
    const GLfloat WHEEL_WIDTH = 2.0f;
    GLuint skyboxTextures[5];
    const float STATION_SIZE = 50.0f;
    float trainX = 0.0f;
void initGL() {
    // Set the clear color to light blue
    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable lighting and set the light source properties
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = { 0.0, 10.0, 10.0, 1.0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Set the material properties for the ground
    GLfloat mat_ambient_ground[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse_ground[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_specular_ground[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_shininess_ground[] = { 10.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_ground);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_ground);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_ground);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_ground);
}

void drawWheel(float wheel_radius, float wheel_width) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidTorus(0.2f * wheel_radius, 0.5f * wheel_radius, 10, 20);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidTorus(0.1f * wheel_radius, 0.4f * wheel_radius, 10, 20);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidSphere(0.2f * wheel_radius, 10, 10);
}

void drawTrain() {
    // Set the material properties for the train
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Draw the main body of the train
    glPushMatrix();
    glTranslatef(0.0, 0.0, -TRAIN_LENGTH / 2);
    glScalef(TRAIN_WIDTH, TRAIN_HEIGHT, TRAIN_LENGTH);
    glutSolidCube(1.0);
    glPopMatrix();

    // Draw the wheels of the train
    GLfloat wheel_radius = TRAIN_HEIGHT / 2;
    GLfloat wheel_width = wheel_radius / 2;
    glPushMatrix();
    glTranslatef(-TRAIN_WIDTH / 2 + wheel_width, -TRAIN_HEIGHT / 2, -TRAIN_LENGTH / 2);
    drawWheel(wheel_radius, wheel_width);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(TRAIN_WIDTH / 2 - wheel_width, -TRAIN_HEIGHT / 2, -TRAIN_LENGTH / 2);
    drawWheel(wheel_radius, wheel_width);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-TRAIN_WIDTH / 2 + wheel_width, -TRAIN_HEIGHT / 2, TRAIN_LENGTH / 2);
    drawWheel(wheel_radius, wheel_width);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(TRAIN_WIDTH / 2 - wheel_width, -TRAIN_HEIGHT / 2, TRAIN_LENGTH / 2);
    drawWheel(wheel_radius, wheel_width);
    glPopMatrix();

    // Draw the chimney of the train
    GLfloat chimney_width = TRAIN_WIDTH / 4;
    GLfloat chimney_height = TRAIN_HEIGHT / 2;
    glPushMatrix();
    glTranslatef(TRAIN_WIDTH / 2 - chimney_width / 2, chimney_height / 2, 0.0);
    glScalef(chimney_width, chimney_height, chimney_width);
    glutSolidCube(1.0);
    glPopMatrix();

    // Draw the cabin of the train
    glPushMatrix();
    glTranslatef(0.0, 0.0, TRAIN_LENGTH / 2 - TRAIN_LENGTH / 3);
    glScalef(TRAIN_WIDTH / 2, TRAIN_HEIGHT, TRAIN_LENGTH / 3);
    glutSolidCube(1.0);
    glPopMatrix();
}


void drawSignal() {
    // Set the signal pole color to gray
    glColor3f(0.5f, 0.5f, 0.5f);

    // Draw the signal pole
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 2.0f);
    glScalef(0.1f, 0.1f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Set the signal light color to black
    glColor3f(0.0f, 0.0f, 0.0f);

    // Draw the signal light holder
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3.0f);
    glScalef(0.2f, 0.2f, 0.2f);
    glutSolidSphere(1.0f, 20, 20);
    glPopMatrix();

    // Set the signal light color according to the current signal state
    if (signalState == GREEN) {
        glColor3f(0.0f, 1.0f, 0.0f);
    } else {
        glColor3f(1.0f, 0.0f, 0.0f);
    }

    // Draw the signal light
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3.0f);
    glScalef(0.8f, 0.8f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void drawStation() {
    // Draw the platform
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.0f);
    glScalef(STATION_SIZE, STATION_SIZE / 10.0f, STATION_SIZE);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw the roof
    glColor3f(0.5f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f + STATION_SIZE / 20.0f, 0.0f);
    glScalef(STATION_SIZE, STATION_SIZE / 10.0f, STATION_SIZE);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw the front entrance
    glColor3f(0.0f, 0.0f, 0.5f);
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, STATION_SIZE / 2.0f);
    glScalef(STATION_SIZE / 4.0f, STATION_SIZE / 5.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw the back entrance
    glColor3f(0.0f, 0.0f, 0.5f);
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, -STATION_SIZE / 2.0f);
    glScalef(STATION_SIZE / 4.0f, STATION_SIZE / 5.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
}
    #define COMET_SIZE 1.0f
void drawComet() {
    // Set the material properties of the comet
    GLfloat materialAmbient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat materialDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat materialSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat materialShininess[] = { 100.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);

    // Draw the comet
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);  // Set the color of the comet
    glTranslatef(0.0, 0.0, -COMET_SIZE / 2.0);  // Center the comet
    glutSolidSphere(COMET_SIZE / 2.0, 20, 20);  // Draw a sphere for the comet
    glPopMatrix();
}

void display() {
    // Clear the color buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1.0f, 1.0f, 100.0f);

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat eyeX = 0.0f;
    GLfloat eyeY = 0.0f;
    GLfloat eyeZ = 100.0f;
    GLfloat centerX = 0.0f;
    GLfloat centerY = 0.0f;
    GLfloat centerZ = 0.0f;
    GLfloat upX = 0.0f;
    GLfloat upY = 1.0f;
    GLfloat upZ = 0.0f;
    // Set the camera position and orientation
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    // Draw the train
    drawTrain();

    // Draw the railway signal
    drawSignal();

    // Draw the railway station
    drawStation();

    // If night mode is enabled, draw the comet
    if (isNightMode) {
        drawComet();
    }

    // Swap the buffers
    glutSwapBuffers();
}




void reshape(int width, int height) {
    // Set the viewport size
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the perspective projection
    gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.0f);

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    // If the 'q' key is pressed, exit the program
    if (key == 'q') {
        exit(0);
    }

    // If the 'd' key is pressed, toggle day/night mode
    if (key == 'd') {
        isNightMode = !isNightMode;
    }

    // If the 'r' key is pressed, reset the train position and signal lights
    if (key == 'r') {
        trainX = -20.0f;
        signalColor = RED;
    }

    // Redraw the scene
    glutPostRedisplay();
}
void menuSelect(int value) {
    switch (value) {
        case 1:
            printf("Menu item 1 selected\n");
            break;
        case 2:
            printf("Menu item 2 selected\n");
            break;
        case 3:
            printf("Menu item 3 selected\n");
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    // If the left mouse button is pressed, exit the program
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        exit(0);
    }

    // If the right mouse button is pressed, show the menu
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Create the menu
        int menu = glutCreateMenu(menuSelect);

        // Add options to the menu
        glutAddMenuEntry("Day Mode", 1);
        glutAddMenuEntry("Night Mode", 2);
        glutAddMenuEntry("Reset", 3);

        // Attach the menu to the right mouse button
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}



void idle() {
    // Increment the comet's position
    cometX += cometVelX;
    cometY += cometVelY;

    // Reverse comet direction if it reaches screen edge
    if (cometX > 30.0f || cometX < -30.0f) {
        cometVelX = -cometVelX;
    }
    if (cometY > 20.0f || cometY < -20.0f) {
        cometVelY = -cometVelY;
    }

    // Redraw the scene
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    // Initialize GLUT and create window
    int windowWidth = 800;
    int windowHeight = 600;
    GLuint textureID;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Train Simulation");
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutIdleFunc(idle); // Register idle function

    #define DAY_NIGHT_TOGGLE 3
    #define QUIT 3

    // Set up menu
    int menu = glutCreateMenu(menuSelect);
    glutAddMenuEntry("Toggle Day/Night Mode", DAY_NIGHT_TOGGLE);
    glutAddMenuEntry("Quit", QUIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button

    // Initialize OpenGL
    initGL();

    // Start main event loop
    glutMainLoop();

    return 0;
}



// 1. State the technology you will use for this project.

/*
        For this project, I used the OpenGL graphics library along with the GLUT (OpenGL Utility Toolkit) toolkit.
        OpenGL is a cross-platform graphics API that allows us to render 3D graphics on a variety of platforms, including Windows, macOS, and Linux.
        GLUT provides a simple framework for creating OpenGL applications and handling user input events such as keyboard and mouse input.

        I used C++ as the programming language to implement the project.
        C++ is a powerful language with excellent support for object-oriented programming and system-level programming,
        making it an excellent choice for developing complex applications like computer graphics simulations.
*/

//2. Provide reasons for this choice of technology as compared to other technologies on the market.

/*
        1. OpenGL is a cross-platform graphics API, which means that the same code can run on multiple operating systems,
            including Windows, macOS, and Linux. This makes it an ideal choice for developing cross-platform applications.

        2.  OpenGL provides access to hardware acceleration, which can significantly improve the
            performance of graphics applications. This is especially important for real-time simulations like the one we are developing.

        3.  OpenGL has a large and active community of developers who provide support and resources for developing
            graphics applications. This means that we can easily find resources, tutorials, and sample code online to help us develop our project.

        4.  OpenGL is widely used in the computer graphics industry, including video game development,
            virtual reality, and scientific visualization. This means that learning OpenGL can be beneficial for future career prospects.

        5.  GLUT provides a simple and lightweight framework for developing OpenGL applications,
            making it easy to get started with graphics programming without worrying too much about low-level details.
            This allows us to focus on the simulation itself, rather than the implementation details.
*/
