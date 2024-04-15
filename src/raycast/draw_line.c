#include "cub3d.h"

void draw_line_on_image(int *addr, int width, int height, int start_x, int start_y, int end_x, int end_y, int color)
{
    int delta_x = abs(end_x - start_x), step_x = start_x < end_x ? 1 : -1;
    int delta_y = -abs(end_y - start_y), step_y = start_y < end_y ? 1 : -1; 
    int error = delta_x + delta_y, error2; // error value e_xy
    
    while (1) {  // The loop will run until break is called
        if (start_x >= 0 && start_x < width && start_y >= 0 && start_y < height) {
            addr[start_y * width + start_x] = color; // Draw pixel
        }
        
        if (start_x == end_x && start_y == end_y) break; // Line has been drawn
        
        error2 = 2 * error;
        if (error2 >= delta_y) { // e_xy+e_x > 0
            if (start_x == end_x) break;
            error += delta_y;
            start_x += step_x;
        }
        if (error2 <= delta_x) { // e_xy+e_y < 0
            if (start_y == end_y) break;
            error += delta_x;
            start_y += step_y;
        }
    }
}