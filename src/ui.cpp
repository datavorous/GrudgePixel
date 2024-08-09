#include "ui.h"

// PRINTING INFO 

void printData()
{
    if ((GetMouseX()<=canvas_side+grid_x) && (GetMouseY()<=canvas_side+grid_y) && (GetMouseX()>=grid_x) && (GetMouseY()>=grid_y))
    {
        m_x = (int)((GetMouseX()-grid_x)/pixel_size)+1;
        m_y = (int)((GetMouseY()-grid_y)/pixel_size)+1;
    }
    
    DrawText(
        TextFormat("%03i,%03i",m_x,m_y),10,435, 12,Color{255,255,255,255});
     DrawText(status, 70, 435, 12, Color{255,255,255,255});
    if (mirror)
        DrawText(
        "M",canvas_side+grid_x-42,435,12,Color{255,255,255,255});
    DrawText(
        TextFormat("%0i",pencil_size),canvas_side+grid_x-30,435,12,Color{255,255,255,255});
    DrawRectangle(
        canvas_side+grid_x-16,435,15,10,present_color);
    DrawText(TextFormat("Paused: %0s",(playAnim?"No":"Yes")),grid_x+canvas_side+10,270,12,Color{255,255,255,255});
    DrawText(TextFormat("Editing Frame: %0i",currentFrameEditing+1),grid_x+canvas_side+10,290,12,Color{255,255,255,255});
    DrawText(TextFormat("FPS: %0i",framesSpeed),grid_x+canvas_side+10,330,12,Color{255,255,255,255});
    DrawText(TextFormat("Frames: %0i",frames.size()),grid_x+canvas_side+10,310,12,Color{255,255,255,255});
}

// INTRO CHOICES

void showChoices()
{
    ClearBackground(Color{20,20,20,255});
    
    // Cast to float to avoid narrowing conversion warnings
    float centerX = (float)(SCREEN_W/2 - 90);
    
    DrawRectangleRoundedLines(Rectangle{centerX, 75.0f, 180.0f, 80.0f}, 50.0f, 50.0f, 3, Color{50,50,50,255});
    DrawRectangleRoundedLines(Rectangle{centerX, 175.0f, 180.0f, 80.0f}, 50.0f, 50.0f, 3, Color{50,50,50,255});
    DrawRectangleRoundedLines(Rectangle{centerX, 275.0f, 180.0f, 80.0f}, 50.0f, 50.0f, 3, Color{50,50,50,255});
    


    
    DrawText("8 x 8",SCREEN_W/2-30,106,24,Color{255,255,255,255});
    DrawText("16 x 16",SCREEN_W/2-36,206,24,Color{255,255,255,255});
    DrawText("32 x 32",SCREEN_W/2-45,306,24,Color{255,255,255,255});
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
