#ifndef MINPX_H
#define MINPX_H

#include "raylib.h"
#include <vector>
#include <string>

// Constants
extern const int SCREEN_H;
extern const int SCREEN_W;
extern const int canvas_side;
extern const int grid_x;
extern const int grid_y;
extern const int colorPalette_x;
extern const int colorPalette_y;

// Global variables
extern int NO_PIXEL;
extern int img_no;
extern int pencil_size;
extern int pixel_size_in_palette;
extern int switch_palette;
extern int currentFrameEditing;
extern int currentFrame;
extern int framesCounter;
extern int framesSpeed;
extern int count;
extern int session;
extern double pixel_size;
extern short m_x, m_y;
extern const char* status;
extern bool mirror;
extern bool grid_lines;
extern bool show_centre;
extern bool playAnim;
extern bool chosen;

extern std::vector<std::vector<Color>> grid;
extern std::vector<std::vector<std::vector<Color>>> frames;

extern Color present_color;
extern Color* color_list1;
extern Color* color_list2;
extern Color* color_list3;
extern Color* img_col;

//extern Font customFont;

// Added these lines:
extern Image color_palette_img1;
extern Image color_palette_img2;
extern Image color_palette_img3;

// Function declarations
void keyStrokes(void);
void drawGrid(void);
void printData(void);
void drawColors(int, int);
void drawAnimation(int);
void showChoices(void);
void file(void);

#endif // MINPX_H