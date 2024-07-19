#include "raylib.h"
#include <conio.h>
#include <dir.h>
#include <process.h>
#include <ctime>
#include <vector>
#define SCREEN_H 450
#define SCREEN_W 560
using namespace std;

const int canvas_side = 420;
const int grid_x = 10;
const int grid_y = 10;
const int colorPalette_x = 440; 
const int colorPalette_y = 120;

int NO_PIXEL=32;
int img_no = 0;
int pencil_size = 1;
int pixel_size_in_palette = 8;
int switch_palette = 1;
int currentFrameEditing = 0;
int currentFrame = 0;
int framesCounter = 0;
int framesSpeed = 2;
int count = 1;


double pixel_size=canvas_side/NO_PIXEL;

short m_x,m_y;

char *status = "";

// ATTENTION TO THIS IS NEEDED
FilePathList droppedFiles = { 0 };


bool mirror = false;
bool grid_lines = false;
bool show_centre = false;
bool playAnim = false;
bool chosen = false;

vector< vector<Color> > grid;
vector<vector< vector<Color> >> frames;

Color present_color;
Color* color_list1;
Color* color_list2;
Color* color_list3;
Color* img_col;
Image color_palette_img1;
Image color_palette_img2;
Image color_palette_img3;

void keyStrokes(void);
void drawGrid(void);
void printData(void);
void drawColors(int,int);
void drawAnimation(int);
void showChoices(void);
void file(void);

int main(void)
{

    // DO NOT TOUCH THESE
    color_palette_img1 = LoadImage("res/palette1.png"); 
    color_list1 = LoadImageColors(color_palette_img1);
    UnloadImage(color_palette_img1);
    color_palette_img2 = LoadImage("res/palette2.png"); 
    color_list2 = LoadImageColors(color_palette_img2);
    UnloadImage(color_palette_img2);
    color_palette_img3 = LoadImage("res/palette3.png"); 
    color_list3 = LoadImageColors(color_palette_img3);
    UnloadImage(color_palette_img3);
    present_color = color_list1[0];


    for(int row=0;row<=NO_PIXEL;row++)
    {
        vector<Color> i_grid;
        for (int column = 0; column <= NO_PIXEL; column++)
            i_grid.push_back((Color){0,0,0,0});
        grid.push_back(i_grid);
    }
    frames.push_back(grid);


    InitWindow(SCREEN_W, SCREEN_H, "minpx");
    SetTargetFPS(60);
    

    Texture2D checked = LoadTexture("res/checked.png");
    Texture2D checked2 = LoadTexture("res/checked2.png");

    while (!WindowShouldClose())
    {
        if (IsFileDropped())
        {
            // Unload previously dropped files
            if (droppedFiles.count > 0) UnloadDroppedFiles(droppedFiles);

            // Load new dropped files
            droppedFiles = LoadDroppedFiles();
            count = 1; // Mark that new files are ready for processing
        }
        
        BeginDrawing();
            if (chosen)
            {
                ClearBackground((Color){13,17,27});
                DrawTexture(checked,grid_x,grid_y,WHITE);
                DrawTexture(checked2,grid_x+canvas_side+10,grid_y,WHITE);
                drawGrid();
                drawColors(5,20);
                printData();
                file(); // STUPID FUNCTION
            }
            else 
                showChoices();
        EndDrawing();
        framesCounter++;
        keyStrokes(); 

        if (IsKeyPressed(KEY_F))
            {
                    UnloadDroppedFiles(droppedFiles);
                    count = 0;
            } 
    }
    UnloadTexture(checked);
    UnloadTexture(checked2);
    UnloadImageColors(color_list1);
    UnloadImageColors(color_list2);
    UnloadImageColors(color_list3);
    UnloadImageColors(img_col);

    //ClearDroppedFiles();
    // THIS ONE TOO
    if (img_col != NULL) UnloadImageColors(img_col);

    if (droppedFiles.count > 0) UnloadDroppedFiles(droppedFiles);


    CloseWindow();    
}



// THIS ONE NOT WORKING AAARGhhh
void file()
{
    if (droppedFiles.count > 0 && count == 1)
    {
        // Load and process the dropped image
        Image img = LoadImage(droppedFiles.paths[0]);
        ImageResizeNN(&img, NO_PIXEL, NO_PIXEL);
        img_col = LoadImageColors(img);
        UnloadImage(img);

        // Assign the colors to the grid frame
        for (int row = 0; row < NO_PIXEL; row++)
        {
            for (int column = 0; column < NO_PIXEL; column++)
            {
                frames[currentFrameEditing][row][column] = img_col[row + column * NO_PIXEL];
            }
        }

        // Mark count to prevent re-processing
        count = 0;
    }

    // Display some text for debugging purposes
    if (count == 0)
    {
        DrawText("F", canvas_side + grid_x - 54, 435, 12, (Color){255, 255, 255, 255});
    }
}




// THESE ARE OK, DONT TOUCH 


void keyStrokes()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if ((GetMouseX()<=canvas_side+grid_x) && (GetMouseY()<=canvas_side+grid_y) && (GetMouseX()>=grid_x) && (GetMouseY()>=grid_y))
            {
                for (int i = -pencil_size/2; i <= pencil_size/2; i++)
                    for (int y = -pencil_size/2; y <= pencil_size/2; y++)
                        if (((
                            (int)((GetMouseX()-grid_x)/pixel_size)+i)>-1 && 
                            ((int)((GetMouseX()-grid_x)/pixel_size)+i)<NO_PIXEL) && 
                            (((int)((GetMouseY()-grid_y)/pixel_size)+y)>-1 && 
                            ((int)((GetMouseY()-grid_y)/pixel_size)+y)<NO_PIXEL))
                        {

                            if (mirror)
                            {
                                frames[currentFrameEditing][((int)((GetMouseX()-grid_x)/pixel_size)+i)][((int)((GetMouseY()-grid_y)/pixel_size)+y)] = present_color;
                                frames[currentFrameEditing][(NO_PIXEL - 1 - ((int)((GetMouseX()-grid_x)/pixel_size)+i))][((int)((GetMouseY()-grid_y)/pixel_size)+y)] = present_color;
                            }
                            else
                                frames[currentFrameEditing][((int)((GetMouseX()-grid_x)/pixel_size)+i)][((int)((GetMouseY()-grid_y)/pixel_size)+y)] = present_color;
                        }
                status = "Pencil";
            }
        }    
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
        if ((GetMouseX()<=canvas_side+grid_x) && (GetMouseY()<=canvas_side+grid_y) && (GetMouseX()>=grid_x) && (GetMouseY()>=grid_y))
        {
            for (int i = -pencil_size/2; i <= pencil_size/2; i++)
                    for (int y = -pencil_size/2; y <= pencil_size/2; y++)
                        if ((((int)((GetMouseX()-grid_x)/pixel_size)+i)>-1 && ((int)((GetMouseX()-grid_x)/pixel_size)+i)<NO_PIXEL) && (((int)((GetMouseY()-grid_y)/pixel_size)+y)>-1 && ((int)((GetMouseY()-grid_y)/pixel_size)+y)<NO_PIXEL))
                        {
                            if (mirror)
                            {
                                frames[currentFrameEditing][((int)((GetMouseX()-grid_x)/pixel_size)+i)][((int)((GetMouseY()-grid_y)/pixel_size)+y)] = (Color){0,0,0,0};
                                frames[currentFrameEditing][(NO_PIXEL - 1 - ((int)((GetMouseX()-grid_x)/pixel_size)+i))][((int)((GetMouseY()-grid_y)/pixel_size)+y)] = (Color){0,0,0,0};
                            }
                            else
                                frames[currentFrameEditing][((int)((GetMouseX()-grid_x)/pixel_size)+i)][((int)((GetMouseY()-grid_y)/pixel_size)+y)] = (Color){0,0,0,0};
                        }
        }
        status = "Eraser";
        }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if ((GetMouseX()<=colorPalette_x+5*20) && (GetMouseY()<=colorPalette_y+7*20) && (GetMouseX()>=colorPalette_x) && (GetMouseY()>=colorPalette_y))
            {
                if (switch_palette == 1)
                    present_color = color_list1[(((GetMouseX()-colorPalette_x)/20)+((GetMouseY()-colorPalette_y)/20)*5)*pixel_size_in_palette];
                if (switch_palette == 2)
                    present_color = color_list2[(((GetMouseX()-colorPalette_x)/20)+((GetMouseY()-colorPalette_y)/20)*5)*pixel_size_in_palette];
                if (switch_palette == 3)
                    present_color = color_list3[(((GetMouseX()-colorPalette_x)/20)+((GetMouseY()-colorPalette_y)/20)*5)*pixel_size_in_palette];
                status = "New Color Picked";
            }}
    if (IsKeyPressed(KEY_G))
    {
        status = "Grid";
        grid_lines = !grid_lines;
    }
    if (IsKeyPressed(KEY_X))
    {
        status = "Centre";
        show_centre = !show_centre;
    }
    if (IsKeyPressed(KEY_M))
        mirror = !mirror;
    if (IsKeyPressed(KEY_LEFT_BRACKET))
        if (pencil_size>2)pencil_size-=2;
    if (IsKeyPressed(KEY_RIGHT_BRACKET))
        pencil_size+=2;
    if (IsKeyPressed(KEY_C))
    {
        for(int row=0; row<NO_PIXEL; row++)
            for(int column=0; column<NO_PIXEL; column++)
                frames[currentFrameEditing][row][column]= {0,0,0,0};
    }
     if((IsKeyDown(KEY_LEFT_CONTROL)) && (IsKeyPressed(KEY_N)))
    {
        frames.push_back(frames[currentFrameEditing]);
        currentFrameEditing++;
        status = "New Frame";
    }
    if (IsKeyPressed(KEY_P))
    {
       if (switch_palette >2)switch_palette=0;
        switch_palette++; 
    }
    if (IsKeyPressed(KEY_RIGHT))
        if (currentFrameEditing<frames.size()-1)currentFrameEditing++;
    if (IsKeyPressed(KEY_LEFT))
        if (currentFrameEditing>0)currentFrameEditing--;
    if (IsKeyPressed(KEY_UP))
        framesSpeed++;
    if (IsKeyPressed(KEY_DOWN))
        if (framesSpeed>1)framesSpeed--;
    if (IsKeyPressed(KEY_SPACE))
        playAnim = !playAnim;
    if ((IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) && ((GetMouseX()<=canvas_side+grid_x) && (GetMouseY()<=canvas_side+grid_y) && (GetMouseX()>=grid_x) && (GetMouseY()>=grid_y)))
        present_color = frames[currentFrameEditing][((int)((GetMouseX()-grid_x)/pixel_size))][((int)((GetMouseY()-grid_y)/pixel_size))];
    


    if((IsKeyDown(KEY_LEFT_CONTROL)) && (IsKeyPressed(KEY_E)))
    {
        // THIS IS ALSO NOT WORKING
        time_t now = time(0); // get current dat/time with respect to system  
  
        char* dt = ctime(&now); // convert it into string  
        mkdir(TextFormat("session_%i",dt));
        for (int imgs=0;imgs<frames.size();imgs++)
        {
            Image p_img = GenImageColor(NO_PIXEL, NO_PIXEL, ((Color){0,0,0,0}));
                for(int row=0; row<NO_PIXEL; row++)
                    for(int column=0; column<NO_PIXEL; column++)
                        ImageDrawPixel(&p_img, row, column, frames[imgs][row][column]);
                
                ExportImage(p_img, TextFormat("session_%i/%03i.png",dt,img_no));
                img_no++;
                UnloadImage(p_img);
        }     
        status = "Image Exported";
    }       
}
void drawGrid()
{
    for(int row=0; row<NO_PIXEL; row++)
        for(int column=0; column<NO_PIXEL; column++)
        {
            DrawRectangle((row*pixel_size)+grid_x, (column*pixel_size)+grid_y, pixel_size, pixel_size, frames[currentFrameEditing][row][column]); 
        }        
    DrawRectangleLines(grid_x, grid_y, canvas_side-3, canvas_side-3, (Color){50,50,50,255});    
    DrawRectangleLines(grid_x+canvas_side+10, grid_y, canvas_side/4-8, canvas_side/4-8, (Color){80,80,80,255});   
    if (grid_lines)
    {
        for(int i=1; i<NO_PIXEL; i++)
            DrawLine(grid_x, (i*pixel_size)+grid_y, grid_x+canvas_side-3, ((i*pixel_size)+grid_y), (Color){50,50,50,255});
        for(int i=1; i<NO_PIXEL; i++)
            DrawLine((i*pixel_size)+grid_x, grid_y, (i*pixel_size)+grid_x, grid_y+canvas_side-3, (Color){50,50,50,255});
    }
    if (show_centre)
    {
        DrawLine((grid_x+canvas_side/2)-1.5, grid_y, (grid_x+canvas_side/2)-1.5, grid_y+canvas_side-2, (Color){255,100,100,255});
        DrawLine(grid_x, (grid_y+canvas_side/2)-2, grid_x+canvas_side-1.5, (grid_y+canvas_side/2)-2, (Color){255,100,100,255});
    }
    if (framesCounter >= 60/framesSpeed)
        {
            framesCounter = 0;
            if (frames.size()>=1)
                {
                    currentFrame++;
                    if (currentFrame==frames.size())
                        currentFrame = 0;
                }
        }
    if (!(playAnim))currentFrame=currentFrameEditing;
    if (frames.size()>0)
        drawAnimation(currentFrame);
}
void drawAnimation(int da_frame)
{
    for(int row=0; row<NO_PIXEL; row++)
                for(int column=0; column<NO_PIXEL; column++)
                        DrawRectangle(
                            (row*(int)(pixel_size/4))+440,
                             (column*(int)(pixel_size/4))+grid_y,
                              (int)(pixel_size/4),
                               (int)(pixel_size/4),
                                frames[da_frame][row][column]); 
}
void drawColors(int no_rows, int size)
{
    for(int row=0;row<32;row++)
    {
        if (switch_palette == 1)
            DrawRectangle(colorPalette_x+size*(row>=no_rows?row-no_rows*(row/no_rows):row),colorPalette_y+size*(row/no_rows), size, size, color_list1[row*pixel_size_in_palette]);
        if (switch_palette == 2)
            DrawRectangle(colorPalette_x+size*(row>=no_rows?row-no_rows*(row/no_rows):row),colorPalette_y+size*(row/no_rows), size, size, color_list2[row*pixel_size_in_palette]);
        if (switch_palette == 3)
            DrawRectangle(colorPalette_x+size*(row>=no_rows?row-no_rows*(row/no_rows):row),colorPalette_y+size*(row/no_rows), size, size, color_list3[row*pixel_size_in_palette]);
    }
}
void printData()
{
    if ((GetMouseX()<=canvas_side+grid_x) && (GetMouseY()<=canvas_side+grid_y) && (GetMouseX()>=grid_x) && (GetMouseY()>=grid_y))
    {
        m_x = (int)((GetMouseX()-grid_x)/pixel_size)+1;
        m_y = (int)((GetMouseY()-grid_y)/pixel_size)+1;
    }
    DrawText(
        TextFormat("%03i,%03i",m_x,m_y),10,435, 12,(Color){255,255,255,255});
    DrawText(
        status,70,435, 12,(Color){255,255,255,255});
    if (mirror)
        DrawText(
        "M",canvas_side+grid_x-42,435,12,(Color){255,255,255,255});
    DrawText(
        TextFormat("%0i",pencil_size),canvas_side+grid_x-30,435,12,(Color){255,255,255,255});
    DrawRectangle(
        canvas_side+grid_x-16,435,15,10,present_color);
    DrawText(TextFormat("Paused: %0s",(playAnim?"No":"Yes")),grid_x+canvas_side+10,270,12,(Color){255,255,255,255});
    DrawText(TextFormat("Editing Frame: %0i",currentFrameEditing+1),grid_x+canvas_side+10,290,12,(Color){255,255,255,255});
    DrawText(TextFormat("FPS: %0i",framesSpeed),grid_x+canvas_side+10,330,12,(Color){255,255,255,255});
    DrawText(TextFormat("Frames: %0i",frames.size()),grid_x+canvas_side+10,310,12,(Color){255,255,255,255});
}
void showChoices()
{
    ClearBackground((Color){13,17,27,180});
    DrawRectangleRoundedLines((Rectangle){SCREEN_W/2-90,75,180,80}, 50, 50, 3, (Color){50,50,50,255});
    DrawRectangleRoundedLines((Rectangle){SCREEN_W/2-90,175,180,80}, 50, 50, 3, (Color){50,50,50,255});
    DrawRectangleRoundedLines((Rectangle){SCREEN_W/2-90,275,180,80}, 50, 50, 3, (Color){50,50,50,255});
    DrawText("8 x 8",SCREEN_W/2-30,106,24,(Color){255,255,255,255});
    DrawText("16 x 16",SCREEN_W/2-36,206,24,(Color){255,255,255,255});
    DrawText("32 x 32",SCREEN_W/2-45,306,24,(Color){255,255,255,255});
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if ((GetMouseX()<=SCREEN_W/2-90+180) && (GetMouseY()<=75+80) && (GetMouseX()>=SCREEN_W/2-90) && (GetMouseY()>=75))
            {
               NO_PIXEL=8;
               pixel_size=canvas_side/NO_PIXEL;
               chosen = true;
            }
            if ((GetMouseX()<=SCREEN_W/2-90+180) && (GetMouseY()<=175+80) && (GetMouseX()>=SCREEN_W/2-90) && (GetMouseY()>=175))
            {
               NO_PIXEL=16;
               pixel_size=canvas_side/NO_PIXEL;
               chosen = true;
            }
            if ((GetMouseX()<=SCREEN_W/2-90+180) && (GetMouseY()<=275+80) && (GetMouseX()>=SCREEN_W/2-90) && (GetMouseY()>=275))
            {
               NO_PIXEL=32;
               pixel_size=canvas_side/NO_PIXEL;
               chosen = true;
            }
        }
}
