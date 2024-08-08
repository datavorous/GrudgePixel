#include "input.h"
#include <sys/stat.h>
#include <string>
#include <filesystem>

// Function to check if a directory exists
bool dirExists(const std::string& dirName_in)
{
    struct stat info;
    if(stat(dirName_in.c_str(), &info) != 0)
        return false;
    else if(info.st_mode & S_IFDIR)
        return true;
    else
        return false;
}


// KEY STROKES MANAGEMENT

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
                                frames[currentFrameEditing][((int)((GetMouseX()-grid_x)/pixel_size)+i)][((int)((GetMouseY()-grid_y)/pixel_size)+y)] = Color{0,0,0,0};
                                frames[currentFrameEditing][(NO_PIXEL - 1 - ((int)((GetMouseX()-grid_x)/pixel_size)+i))][((int)((GetMouseY()-grid_y)/pixel_size)+y)] = Color{0,0,0,0};
                            }
                            else
                                frames[currentFrameEditing][((int)((GetMouseX()-grid_x)/pixel_size)+i)][((int)((GetMouseY()-grid_y)/pixel_size)+y)] = Color{0,0,0,0};
                        }
        }
        status = "Eraser";

        }

    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if ((GetMouseX()<=colorPalette_x+5*20) && (GetMouseY()<=colorPalette_y+7*20) && (GetMouseX()>=colorPalette_x) && (GetMouseY()>=colorPalette_y))
            {
                if (switch_palette == 1)
                    present_color = color_list1[(((GetMouseX()-colorPalette_x)/20)+((GetMouseY()-colorPalette_y)/20)*5)*pixel_size_in_palette];
                if (switch_palette == 2)
                    present_color = color_list2[(((GetMouseX()-colorPalette_x)/20)+((GetMouseY()-colorPalette_y)/20)*5)*pixel_size_in_palette];
                if (switch_palette == 3)
                    present_color = color_list3[(((GetMouseX()-colorPalette_x)/20)+((GetMouseY()-colorPalette_y)/20)*5)*pixel_size_in_palette];
                status = "New Color Picked";
            }
    }

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



    if (IsKeyPressed(KEY_F))
    {
        //ClearDroppedFiles();
        count = 0;
    }  



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
        std::string dirName = "session_";
        
        // Check if directory exists, if not, create it
        if (!dirExists(dirName))
        {
            #ifdef _WIN32
                mkdir(dirName.c_str());
            #else
                mkdir(dirName.c_str(), 0777);
            #endif
        }

        for (size_t imgs = 0; imgs < frames.size(); imgs++)
        {
            Image p_img = GenImageColor(NO_PIXEL, NO_PIXEL, (Color{0,0,0,0}));
            for(int row=0; row<NO_PIXEL; row++)
                for(int column=0; column<NO_PIXEL; column++)
                    ImageDrawPixel(&p_img, row, column, frames[imgs][row][column]);
            
            ExportImage(p_img, TextFormat("%s/%03i.png", dirName.c_str(), img_no));
            img_no++;
            UnloadImage(p_img);
        }     
        status = "Image Exported";
    }




        
}