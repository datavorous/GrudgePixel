#include "main.h"
#include <conio.h>
#include <dir.h>
#include <process.h>

// Constants definition
const int SCREEN_H = 450;
const int SCREEN_W = 560;
const int canvas_side = 420;
const int grid_x = 10;
const int grid_y = 10;
const int colorPalette_x = 440;
const int colorPalette_y = 120;

// Global variables definition
int NO_PIXEL = 32;
int img_no = 0;
int pencil_size = 1;
int pixel_size_in_palette = 8;
int switch_palette = 1;
int currentFrameEditing = 0;
int currentFrame = 0;
int framesCounter = 0;
int framesSpeed = 2;
int count = 0;
int session = 0;
double pixel_size = canvas_side / NO_PIXEL;
short m_x, m_y;
const char* status = "";
bool mirror = false;
bool grid_lines = false;
bool show_centre = false;
bool playAnim = false;
bool chosen = false;

// Define global variables
std::vector<std::vector<Color>> grid;
std::vector<std::vector<std::vector<Color>>> frames;

Color present_color;
Color* color_list1 = nullptr;
Color* color_list2 = nullptr;
Color* color_list3 = nullptr;
Color* img_col = nullptr;

//Font customFont;

Image color_palette_img1;
Image color_palette_img2;
Image color_palette_img3;

int main(void)
{
    //customFont = LoadFont("res/custom_font.ttf");

    color_palette_img1 = LoadImage("res/palette1.png");
    color_palette_img2 = LoadImage("res/palette2.png");
    color_palette_img3 = LoadImage("res/palette3.png");

    color_list1 = LoadImageColors(color_palette_img1);
    color_list2 = LoadImageColors(color_palette_img2);
    color_list3 = LoadImageColors(color_palette_img3);

    UnloadImage(color_palette_img1);
    UnloadImage(color_palette_img2);
    UnloadImage(color_palette_img3);

    present_color = color_list1[0];

    for(int row=0; row<=NO_PIXEL; row++)
    {
        std::vector<Color> i_grid;
        for (int column = 0; column <= NO_PIXEL; column++)
            i_grid.push_back((Color){0,0,0,0});
        grid.push_back(i_grid);
    }
    frames.push_back(grid);

    InitWindow(SCREEN_W, SCREEN_H, "minpx");
    SetTargetFPS(60);
    
    ///session = LoadStorageValue(0) + 1;
    //SaveStorageValue(0, session);
    //mkdir(TextFormat("session_%i",session));
    //mkdir(TextFormat("session_"));

    Texture2D checked = LoadTexture("res/checked.png");
    Texture2D checked2 = LoadTexture("res/checked2.png");
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
         
            if (chosen)
            {
                ClearBackground((Color){13,17,27});
                DrawTexture(checked,grid_x,grid_y,WHITE);
                DrawTexture(checked2,grid_x+canvas_side+10,grid_y,WHITE);
                drawGrid();
                drawColors(5,20);
                printData();
                file();
            }
            else 
                showChoices();
        
        EndDrawing();
        framesCounter++;
        keyStrokes(); 
    }
    UnloadTexture(checked);
    UnloadTexture(checked2);
    //UnloadFont(customFont); 
    UnloadImageColors(color_list1);
    UnloadImageColors(color_list2);
    UnloadImageColors(color_list3);
    UnloadImageColors(img_col);

    //ClearDroppedFiles();


    CloseWindow();    
}