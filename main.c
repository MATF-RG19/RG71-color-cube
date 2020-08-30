#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define TIMER_INTERVAL 20
#define TIMER_ID 0
#define TIMER_ID_2 1
#define PI 3.14159265359

float animation_parameter = 0;
int animation_ongoing = 0;

static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
//static void on_timer(int id);

int generate_random();
void draw_cube();
void draw_path();

static void game_info_initialization();

int main(int argc, char** argv) {
    
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije */
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);

    /* Obavlja se OpenGL inicijalizacija. */
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    
    float light_position[] = {-1, 1, 1, 0};
    float light_ambient[] = {.3f, .3f, .3f, 1};
    float light_diffuse[] = {.7f, .7f, .7f, 1};
    float light_specular[] = {.7f, .7f, .7f, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glClearColor(.5f, .5f, .5f, 1);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    
    glutMainLoop();
    
    return 0;
    
 }

static void game_info_initialization(){
    
}

void on_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(30, (float) width/height, 1, 1000);
}

static void on_timer(int id) {}
static void on_keyboard(unsigned char key, int x, int y) {
    
}

/*void on_timer(int id) {
    
}
*/
void draw_cube() {
    
    glPushMatrix();
    
        glutSolidCube(0.5);
    
    glPopMatrix();
    
}

void draw_path() {
    
    glPushMatrix();
    glTranslatef(-animation_parameter, 0.0, 0.0);
    glScalef(1.5,0.5,1);
    
    
    glTranslatef(-0.6, 0.0, 0.0);
    draw_cube();
    
    glTranslatef(0.0, 0.0, 0.0);
    draw_cube();
    
    glTranslatef(0.6, 0.0, 0.0);
    draw_cube();
        
    glTranslatef(0.6, 0.0, 0.0);
    draw_cube();
    
    glTranslatef(0.6, 0.0, 0.0);
    draw_cube();
    
    glPopMatrix();
    
}

void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    gluLookAt(0, 10 + 5*sin(PI*animation_parameter/180), 10,
              0, 0, 0,
              0, 1, 0);



    GLfloat ambient[] = {0.3,0.3,0.3,0};
    GLfloat diffuse[] = {0,0.7,0,0};
    GLfloat specular[] = {0.6,0.6,0.6,0};
    GLfloat shininess = 80;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glPushMatrix();

    GLfloat ambient1[] = {0.3,0.3,0.3,0};
    GLfloat green[] = {0.0,0.7f,0,0};
    GLfloat red[] = {0.7f, 0.0, 0.0};
    GLfloat blue[] = {0.0, 0.0, 0.7f};
    GLfloat b[] = {0.0, 0.5f, 0.5f};
    GLfloat specular1[] = {0.6,0.6,0.6,0};
    GLfloat shininess1 = 80;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular1);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess1);
    
        glTranslatef(-animation_parameter, 0.0, 0.0);
        glScalef(1.5,0.9,1);
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
        glTranslatef(-0.6, 0.0, 0.0);
        draw_cube();
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
        glTranslatef(0.0, 0.0, 0.0);
        draw_cube();
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(0.6, 0.0, 0.0);
        draw_cube();
        
        for(int i = 0; i < 5; i++) {
	
            int nu = generate_random();
            if (nu == 1)
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
            else if (nu == 2)
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
            else
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
            glTranslatef(0.6, 0.0, 0.0);
            
            draw_cube();
	
        }
    
        
        
    glPopMatrix();    
    glutSwapBuffers();
}


int generate_random() { //this will generate random number in range l and r
   int lower = 1, upper = 3;
   srand(time(0)); //current time as seed of random number generator
   int rand_num = (rand() % (upper - lower + 1)) + lower;
   return rand_num;
}
