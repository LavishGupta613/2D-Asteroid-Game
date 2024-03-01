#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<cmath>
#include <stdio.h>
#include <string>
#define GUIDE_ARROW_SIZE 5.0f

float spaceshipX=0;
float spaceshipY=0;
int score = 0;
int health = 50;
int gameState = 0;
int lvl=1;
float s=1.0;
float playerSpeed = 1.0;  // Initial speed of the player
int numAsteroidsBelow = 0;
int socre=0;
int prevLevel=1;
struct Asteroid {
    float x, y;
    float size;
    float speed;
    float rotation;  // New property for rotation

   Asteroid(float _size, float _speed) : size(_size), speed(_speed), rotation(0.0f) {
    x = static_cast<float>(rand() % 200 - 100);
    y = 100.0f;
    size = static_cast<float>(rand() % 50 + 1) / 5.0f;
}


    void move() {
    y -= speed;

    if (y < -100.0f) {
        y = 100.0f;
        rotation += 2.0f;  // Adjust this value for the desired rotation speed
        if (rotation > 360.0f) {
            rotation -= 360.0f;
        }
        x = static_cast<float>(rand() % 200 - 100);
        size = static_cast<float>(rand() % 50 + 1) / 5.0f;
        speed = static_cast<float>(rand() % 15 + 1) / 100.0f;
        if (lvl > 4) speed = static_cast<float>(rand() % 30 + 10) / 100.0f;
        if (lvl > 7) speed = static_cast<float>(rand() % 50 + 10) / 100.0f;
    }
}

};

struct SpaceStation {
    float x, y;
    float size;

    SpaceStation(float _size) : size(_size) {
        x = static_cast<float>(rand() % 200 - 100) ;  // Random x position
        y = static_cast<float>(rand() % 100) ;    // Random y position in the upper half
    }
};
void drawSpaceship() {
    glColor3f(1.0, 0.0, 0.0);
    //Top of PLane of red color
    glBegin(GL_POLYGON);
    float radiusX = 2;
    float radiusY = 8;
    int numSegments = 100;

    for (int i = 0; i <= numSegments; ++i) {
        float theta = static_cast<float>(i) / static_cast<float>(numSegments) * (M_PI );
        float x = radiusX * cos(theta);
        float y = radiusY * sin(theta);
        glVertex2f(x-85+spaceshipX, y-70+spaceshipY);
    }
    glEnd();
    //
    glBegin(GL_QUADS);
     glColor3f(0.5, 0.5, 0.5);
    glVertex2f(-83+spaceshipX,-80+spaceshipY);
    glVertex2f(-87+spaceshipX,-80+spaceshipY);
    glVertex2f(-87+spaceshipX,-70+spaceshipY);
    glVertex2f(-83+spaceshipX,-70+spaceshipY);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
     glVertex2f(-83+spaceshipX,-80+spaceshipY);
    glVertex2f(-87+spaceshipX,-80+spaceshipY);
    glVertex2f(-86+spaceshipX,-82+spaceshipY);
    glVertex2f(-84+spaceshipX,-82+spaceshipY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.529, 0.808, 0.922);
    float radius = 1;

    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0 * M_PI * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x-85+spaceshipX, y-75+spaceshipY);
    }

    glEnd();
    glBegin(GL_POLYGON);
    //Circle at the centre of blue color
    glColor3f(1.0, 0.0, 0.0);
      glVertex2f(-80+spaceshipX,-95+spaceshipY);
    glVertex2f(-90+spaceshipX,-95+spaceshipY);
    glVertex2f(-90+spaceshipX,-90+spaceshipY);
     glVertex2f(-85+spaceshipX,-85+spaceshipY);
     glVertex2f(-80+spaceshipX,-90+spaceshipY);
    glVertex2f(-86+spaceshipX,-95+spaceshipY);
    glEnd();

    //
    glBegin(GL_QUADS);
     glColor3f(0.7, 0.7, 0.7);
    glVertex2f(-86+spaceshipX,-82+spaceshipY);
    glVertex2f(-84+spaceshipX,-82+spaceshipY);
     glVertex2f(-84+spaceshipX,-95+spaceshipY);
    glVertex2f(-86+spaceshipX,-95+spaceshipY);
    glEnd();
    //Left yellow line
    glBegin(GL_QUADS);
     glColor3f(1, 1, 0);
    glVertex2f(-90+spaceshipX,-98+spaceshipY);
    glVertex2f(-90+spaceshipX,-87+spaceshipY);
     glVertex2f(-91+spaceshipX,-87+spaceshipY);
    glVertex2f(-91+spaceshipX,-98+spaceshipY);
    glEnd();
    //Right Yellow Line
    glBegin(GL_QUADS);
     glColor3f(1, 1, 0);
    glVertex2f(-80+spaceshipX,-98+spaceshipY);
    glVertex2f(-80+spaceshipX,-87+spaceshipY);
     glVertex2f(-79+spaceshipX,-87+spaceshipY);
    glVertex2f(-79+spaceshipX,-98+spaceshipY);
    glEnd();
    //Base
     glBegin(GL_QUADS);
     glColor3f(0.2, 0.2, 0.2);
    glVertex2f(-86+spaceshipX,-95+spaceshipY);
    glVertex2f(-87+spaceshipX,-97+spaceshipY);
     glVertex2f(-84+spaceshipX,-95+spaceshipY);
    glVertex2f(-83+spaceshipX,-97+spaceshipY);
    glEnd();
}


void drawWelcomePage() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0, 0.5, 0.0);

    std::string welcomeText = "Welcome to Spaceship Game\n";
    std::string welcomeText1= "Navigate your spaceship using 'W', 'A', 'S', 'D'\n";
   std::string welcomeText2= "Avoid asteroids and reach the space station to advance\n";
    std::string welcomeText3= "Press 'O' or 'o' to start the game";

    glRasterPos2f(-60.0f, 50.0f);

    for (char c : welcomeText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(-60.0f, 40.0f);

    for (char c : welcomeText1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(-60.0f, 30.0f);

    for (char c : welcomeText2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(-60.0f, 20.0f);

    for (char c : welcomeText3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void drawGameOverPage() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0, 0.0, 0.0);  // Set color to red

    std::string gameOverText = "Game Over";
    std::string scoreText = "Final Score: " + std::to_string(score);
    std::string playAgainText = "Press 'R' to play again";

    glRasterPos2f(-25.0f, 20.0f);  // Adjust position as needed
    for (char c : gameOverText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2f(-30.0f, 10.0f);  // Adjust position as needed
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2f(-40.0f, 0.0f);  // Adjust position as needed
    for (char c : playAgainText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void drawnextlevelPage() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0, 0.5, 0.0);  // Set color to white
   int s=score;
    std::string welcomeText = "Congratulation you cleared the level : "+std::to_string(lvl-1);
     std::string scoreString = "Score: " + std::to_string(s);
     std::string s1 = "For next level press n or N";
    glRasterPos2f(-60.0f, 50.0f);  // Adjust position as needed

    for (char c : welcomeText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }glRasterPos2f(-60.0f, 60.0f);
    for (char c : scoreString) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }glRasterPos2f(-60.0f, 40.0f);
    for (char c : s1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}



std::vector<Asteroid> asteroids;
void Write(char *string){//Write string on the screen
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
        }


void drawScore() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.2, 0.9, 1.0);  // Set color to white

    std::string scoreString = "Score: " + std::to_string(score);

    glRasterPos2f(-70.0f, 90.0f);  // Adjust position as needed

    for (char c : scoreString) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
void drawHealth() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0, 0.0, 0.0);  // Set color to red

    std::string healthString = "Health: " + std::to_string(health);

    glRasterPos2f(-95.0f, 90.0f);

    for (char c : healthString) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(-80.0f, 90.0f);
    std::string level = "Level: " + std::to_string(lvl);
    for (char c : level) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void drawAsteroid(const Asteroid& asteroid) {
    glPushMatrix();
    glTranslatef(asteroid.x, asteroid.y, 0.0f);
    glRotatef(asteroid.rotation, 0.0f, 0.0f, 1.0f);  // Rotate the asteroid around its center

    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    int numSegments;
    if (asteroid.size < 2.0f) {
        numSegments = 3;
    } else if (asteroid.size < 4.0f) {
        numSegments = 4;
    } else if (asteroid.size < 7.0f) {
        numSegments = 5;
    } else  if(asteroid.size < 9.0f){
        numSegments = 6;
    }else numSegments = 7;
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0 * M_PI * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = asteroid.size * cos(theta);
        float y = (asteroid.size) * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();
}



SpaceStation spaceStation(5);
void drawSpaceStation() {
    glPushMatrix();
    glTranslatef(spaceStation.x, spaceStation.y, 0.0f);
    glRotatef(30.0f, 0.0f, 0.0f, 1.0f);  // Rotate by 30 degrees around the z-axis
    float y = 0;
    float x =0;

     if (lvl > prevLevel) {
        // Update the space station's position
        spaceStation.x = static_cast<float>(rand() % 200 - 100) / 2;
        spaceStation.y = static_cast<float>(rand() % 100) / 2;

        // Update the previous level
        prevLevel = lvl;
    }
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);  // Set color to red

    // Body of the space station
     glTranslatef(spaceStation.x, spaceStation.y, 0.0f);
    glVertex2f(-spaceStation.size+x, -spaceStation.size+y);  // bottom-left
    glVertex2f(spaceStation.size+x, -spaceStation.size+y);   // bottom-right
    glVertex2f(spaceStation.size+x, spaceStation.size+y);     // top-right
    glVertex2f(-spaceStation.size+x, spaceStation.size+y);    // top-left

    glEnd();

    // Solar Panel (Antenna)
    glBegin(GL_QUADS);
    glColor3f(0.529, 0.808, 0.922);  // Set color to sky blue

    // Bottom-left
    glVertex2f(-spaceStation.size / 2.0+x, spaceStation.size+y);
    // Bottom-right
    glVertex2f(spaceStation.size / 2.0+x, spaceStation.size+y);
    // Top-right
    glVertex2f(spaceStation.size / 2.0+x, spaceStation.size * 1.5+y);
    // Top-left
    glVertex2f(-spaceStation.size / 2.0+x, spaceStation.size * 1.5+y);
    // Bottom-left
    glVertex2f(-spaceStation.size / 2.0+x, -spaceStation.size+y);
    // Bottom-right
    glVertex2f(spaceStation.size / 2.0+x, -spaceStation.size+y);
    // Top-right
    glVertex2f(spaceStation.size / 2.0+x, -spaceStation.size * 1.5+y);
    // Top-left
    glVertex2f(-spaceStation.size / 2.0+x, -spaceStation.size * 1.5+y);

    glEnd();




    // Grid-like pattern on the solar panel
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);  // Set color to black

    float panelWidth = spaceStation.size;
    float panelHeight = spaceStation.size * 0.5;

    int numLines = 5;

    for (int i = 1; i < numLines; ++i) {
        // Vertical lines
        glVertex2f(-panelWidth / 2.0 + i * panelWidth / numLines+x, spaceStation.size+y);
        glVertex2f(-panelWidth / 2.0 + i * panelWidth / numLines, spaceStation.size * 1.5+y);

        // Horizontal lines
        glVertex2f(-panelWidth / 2.0+x, spaceStation.size + i * panelHeight / numLines+y);
        glVertex2f(panelWidth / 2.0+x, spaceStation.size + i * panelHeight / numLines+y);


        glVertex2f(-panelWidth / 2.0 + i * panelWidth / numLines+x, -spaceStation.size+y);
        glVertex2f(-panelWidth / 2.0 + i * panelWidth / numLines+x, -spaceStation.size * 1.5+y);

        // Horizontal lines
        glVertex2f(-panelWidth / 2.0+x, -(spaceStation.size + i * panelHeight / numLines+y));
        glVertex2f(panelWidth / 2.0+x, -(spaceStation.size + i * panelHeight / numLines+y));
    }

    glEnd();

    glPopMatrix();
}
void reset(){
    gameState=0;
    spaceshipX=0;
    spaceshipY=0;
    score=0;
     health = 3;
     for (auto& asteroid : asteroids) {
         asteroid.y=100;
         asteroid.x = static_cast<float>(rand() % 200 - 100);
     }

}
void checkCollisionWithAsteroids() {
    for (auto& asteroid : asteroids) {
        float distanceToAsteroid = sqrt(pow(-85 + spaceshipX - asteroid.x, 2) + pow(-62 + spaceshipY - asteroid.y, 2));
        float dis1 = sqrt(pow(-79 + spaceshipX - asteroid.x, 2) + pow(-92 + spaceshipY - asteroid.y, 2));
        float dis2 = sqrt(pow(-90 + spaceshipX - asteroid.x, 2) + pow(-92 + spaceshipY - asteroid.y, 2));
        float dis3 = sqrt(pow(-85 + spaceshipX - asteroid.x, 2) + pow(-75 + spaceshipY - asteroid.y, 2));

        if (asteroid.y < -95 + spaceshipY && health>0)
            score++;

        float p = (2.0f + asteroid.size);
        if (distanceToAsteroid < (2.0f + asteroid.size) || dis1 < p || dis2 < p || dis3 < p) {
            // Spaceship has collided with an asteroid
            health-=10;

            // Reset spaceship position
                // Reset spaceship position
            asteroid.x = 0;
            asteroid.y = 0;

            // Check if health is zero and handle game over logic
            std::string h = "Game over";

            if (health == 0) {
                gameState = 2;
                spaceshipX = 0;
            spaceshipY = 0;
            lvl=1;
            }
        }
        // Update numAsteroidsBelow for each asteroid
        numAsteroidsBelow = 0;
        for (const auto& a : asteroids) {
            if (a.y < spaceshipY) {
                numAsteroidsBelow++;
                socre+=100*numAsteroidsBelow+130*s;

            }
        }
    }
}
void updateScore() {
    // Check if the spaceship has reached the space station
    float distanceToSpaceStation = sqrt(pow(-85 + spaceshipX - spaceStation.x, 2) + pow(-62 + spaceshipY - spaceStation.y, 2));
    float dis1 = sqrt(pow(-79 + spaceshipX - spaceStation.x, 2) + pow(-92 + spaceshipY - spaceStation.y, 2));
    float dis2 = sqrt(pow(-90 + spaceshipX - spaceStation.x, 2) + pow(-92 + spaceshipY - spaceStation.y, 2));
    float dis3 = sqrt(pow(-85 + spaceshipX - spaceStation.x, 2) + pow(-75 + spaceshipY - spaceStation.y, 2));

    if (distanceToSpaceStation < (5.0f + spaceStation.size) || dis1 < (5.0f + spaceStation.size) ||
        dis2 < (5.0f + spaceStation.size) || dis3 < (6.0f + spaceStation.size)) {
        // Update the score based on level, player speed, and asteroids below for each asteroid
        for (const auto& asteroid : asteroids) {
            if (asteroid.y < spaceshipY) {
                score += static_cast<int>(lvl * playerSpeed);
            }
        }
    }
}
void drawDirectionalGuide() {
    glColor3f(0.0, 1.0, 0.0);  // Set color to green
    glLineWidth(2.0);

    float directionX = spaceStation.x - (spaceshipX - 85.0f);
    float directionY = spaceStation.y - (spaceshipY - 62.0f);

    // Normalize the direction vector
    float length = sqrt(directionX * directionX + directionY * directionY);
    directionX /= length;
    directionY /= length;

    // Extend the direction vector to have a magnitude of 10
    float extendedX = (spaceshipX - 85.0f) + 10.0f * directionX;
    float extendedY = (spaceshipY - 62.0f) + 10.0f * directionY;

    // Calculate the perpendicular direction vector
    float perpendicularX = -directionY;
    float perpendicularY = directionX;

    // Calculate arrowhead vertices
    float arrowBaseX1 = extendedX - 2.0f * (directionX + perpendicularX);
    float arrowBaseY1 = extendedY - 2.0f * (directionY + perpendicularY);
    float arrowBaseX2 = extendedX - 2.0f * (directionX - perpendicularX);
    float arrowBaseY2 = extendedY - 2.0f * (directionY - perpendicularY);

    // Draw the line
    glBegin(GL_LINES);
    glVertex2f(spaceshipX - 85.0f, spaceshipY - 62.0f);  // Starting point
    glVertex2f(extendedX, extendedY);  // End point with magnitude of 10
    glEnd();

    // Draw an arrowhead at the end of the line
    glBegin(GL_TRIANGLES);
    glVertex2f(extendedX, extendedY);  // Arrow tip
    glVertex2f(arrowBaseX1, arrowBaseY1);  // Arrow base
    glVertex2f(arrowBaseX2, arrowBaseY2);  // Arrow base
    glEnd();

    glLineWidth(1.0);
}





void update(int value) {
    for (auto& asteroid : asteroids) {
        asteroid.move();
         asteroid.rotation += 1.0f;
    }

    checkCollisionWithAsteroids();

    // Collision detection with space station
    float distanceToSpaceStation = sqrt(pow(-85 + spaceshipX - spaceStation.x, 2) + pow(-62 + spaceshipY - spaceStation.y, 2));
    float dis1 = sqrt(pow(-79 + spaceshipX - spaceStation.x, 2) + pow(-92 + spaceshipY - spaceStation.y, 2));
    float dis2 = sqrt(pow(-90 + spaceshipX - spaceStation.x, 2) + pow(-92 + spaceshipY - spaceStation.y, 2));
    float dis3 = sqrt(pow(-85 + spaceshipX - spaceStation.x, 2) + pow(-75 + spaceshipY - spaceStation.y, 2));

    if (distanceToSpaceStation < (5.0f + spaceStation.size) || dis1 < (5.0f + spaceStation.size) ||
        dis2 < (5.0f + spaceStation.size) || dis3 < (6.0f + spaceStation.size)) {
        // Spaceship has reached the space station
        lvl++;

        // Update player speed for the new level
        playerSpeed += 0.1;  // You can adjust the speed increment

        // Update the score
        updateScore();

        gameState = 3;

        // Reset spaceship position and asteroid positions for the new level
        spaceshipX = 0;
        spaceshipY = 0;

        for (auto& asteroid : asteroids) {
            asteroid.y = 100;
            asteroid.x = static_cast<float>(rand() % 200 - 100);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(8, update, 0);  // 60 FPS update rate
}
void drawMiniMap() {
    // Draw the mini-map
    glColor3f(0.2, 0.2, 0.2);  // Set color to dark gray
    glBegin(GL_QUADS);
    glVertex2f(80.0f, 80.0f);  // Top-right
    glVertex2f(100.0f, 80.0f);  // Top-left
    glVertex2f(100.0f, 100.0f);  // Bottom-left
    glVertex2f(80.0f, 100.0f);  // Bottom-right
    glEnd();

    // Draw the directional guide arrow
    glColor3f(0.0, 1.0, 0.0);  // Set color to green
    glBegin(GL_TRIANGLES);

    // Calculate the direction vector towards the space station
    float directionX = 85-spaceStation.x + spaceshipX;
    float directionY = 62-spaceStation.y + spaceshipY;

    // Normalize the direction vector
    float length = sqrt(directionX * directionX + directionY * directionY);
    directionX /= length;
    directionY /= length;

    // Calculate the arrow tip position
    float arrowTipX = 90.0f + directionX * GUIDE_ARROW_SIZE;
    float arrowTipY = 90.0f + directionY * GUIDE_ARROW_SIZE;

    // Draw the arrow
    glVertex2f(90.0f, 90.0f);  // Arrow base
    glVertex2f(arrowTipX + directionY * 2.0f, arrowTipY - directionX * 2.0f);  // Arrow tip
    glVertex2f(arrowTipX - directionY * 2.0f, arrowTipY + directionX * 2.0f);  // Arrow tip

    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (gameState) {
        case 0:  // WELCOME
            drawWelcomePage();

            break;
        case 1:
             // PLAYING

            for (const auto& asteroid : asteroids) {
                drawAsteroid(asteroid);
            }
            drawSpaceship();
            drawSpaceStation();
            drawScore();
            drawHealth();
            drawMiniMap();
            checkCollisionWithAsteroids();
            drawDirectionalGuide();
            break;
        case 2:

           drawGameOverPage();

            break;
        case 3:
            drawnextlevelPage();




    }

    glutSwapBuffers();  // Add this line
}




void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0,100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
void keyboard(unsigned char key, int x, int y) {
    switch (gameState) {
    case 3:
         if (key == 'n' || key == 'N') {
                gameState = 1;  // Switch to PLAYING
            }
            break;

        case 0:  // WELCOME
            if (key == 'o' || key == 'O') {
                gameState = 1;  // Switch to PLAYING
            }
            break;
        case 1:
            switch (key) {
                case 'w':
            spaceshipY += s;
            break;
        case 's':
            spaceshipY -= s;
            break;
        case 'a':
            spaceshipX -= s;
            break;
        case 'd':
            spaceshipX += s;
            break;
    } break;
        case 2:
              if (key == 'r' || key == 'R') {
                    reset();
                gameState = 1;  // Switch to PLAYING
            }
            break;

    glutPostRedisplay();
}
}

int main(int argc, char** argv) {
    srand(static_cast<unsigned>(time(nullptr)));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Moving Asteroids");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set clear color to black
    if(lvl<3)
{
 for (int i = 0; i < 15; ++i) {
        asteroids.emplace_back(static_cast<float>(rand() % 50 + 1) / 5.0f, static_cast<float>(rand() % 15 + 1) / 100.0f);
    }
}else if(lvl<5){
 for (int i = 0; i < 20; ++i) {
        asteroids.emplace_back(static_cast<float>(rand() % 50 + 1) / 5.0f, static_cast<float>(rand() %40  + 10) / 100.0f);
    }}
    else{
      for (int i = 0; i < 25; ++i) {
        asteroids.emplace_back(static_cast<float>(rand() % 50 + 1) / 5.0f, static_cast<float>(rand() % 60 + 10) / 100.0f);
    }}

 glutKeyboardFunc(keyboard);
    glutTimerFunc(25, update, 0);  // Initial call to update after 25 milliseconds

    glutMainLoop();

    return 0;
}
