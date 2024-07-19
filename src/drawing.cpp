#include "drawing.h"

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


// MINIMAP ANIMATION AND DRAWING PALLETE COLORS

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