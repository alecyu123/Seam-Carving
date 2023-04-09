#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "seamcarving.h"
#include "c_img.h"

void calc_energy(struct rgb_img *im, struct rgb_img **grad)
{
    *grad = (struct rgb_img*)malloc(sizeof(struct rgb_img));
    (*grad)->raster = (uint8_t*)malloc(3*(im->height)*(im->width)*sizeof(uint8_t)); // change : need to add sizeof(uint8t?)
    (*grad)->height = im->height;
    (*grad)->width = im->width;
    if(im->height == 1 && im->width == 1) // need to change (consider 1 x 99 or 99 x 1)
    {
        set_pixel(*grad, 0, 0, 0, 0, 0);
        return;
    }
    else if (im->height == 1)
    {
        for (int x = 0; x < im->width; x++)
        {
            int Rx, Gx, Bx;
            int tot_energy = 0;

            if(x == 0) 
            {
                Rx = get_pixel(im, 0, x + 1, 0) - get_pixel(im, 0, im->width - 1 , 0);
                Gx = get_pixel(im, 0, x + 1, 1) - get_pixel(im, 0, im->width - 1 , 1);
                Bx = get_pixel(im, 0, x + 1, 2) - get_pixel(im, 0, im->width - 1 , 2);
            }
            else if(x == (im->width - 1))
            {
                Rx = get_pixel(im, 0, 0, 0) - get_pixel(im, 0, x - 1 , 0);
                Gx = get_pixel(im, 0, 0, 1) - get_pixel(im, 0, x - 1 , 1);
                Bx = get_pixel(im, 0, 0, 2) - get_pixel(im, 0, x - 1 , 2);
            }
            else
            {
                Rx = get_pixel(im, 0, x + 1, 0) - get_pixel(im, 0, x - 1 , 0);
                Gx = get_pixel(im, 0, x + 1, 1) - get_pixel(im, 0, x - 1 , 1);
                Bx = get_pixel(im, 0, x + 1, 2) - get_pixel(im, 0, x - 1 , 2);
            }
            tot_energy = sqrt(Rx*Rx + Gx*Gx + Bx*Bx)/10;
            uint8_t total = (uint8_t) tot_energy; // is this how we recast
            set_pixel(*grad, 0, x, total, total, total);
        }
        return;
    }
    else if (im->width == 1)
    {
        for (int y = 0; y < im->height; y++)
        {
            int Ry, Gy, By;
            int tot_energy = 0;

            if(y == 0)
            {
                Ry = get_pixel(im, y + 1, 0, 0) - get_pixel(im, im->height - 1, 0, 0);
                Gy = get_pixel(im, y + 1, 0, 1) - get_pixel(im, im->height - 1, 0, 1);
                By = get_pixel(im, y + 1, 0, 2) - get_pixel(im, im->height - 1, 0, 2);
            }

            else if(y == (im->height - 1))
            {
                Ry = get_pixel(im, 0, 0, 0) - get_pixel(im, y - 1, 0, 0);
                Gy = get_pixel(im, 0, 0, 1) - get_pixel(im, y - 1, 0, 1);
                By = get_pixel(im, 0, 0, 2) - get_pixel(im, y - 1, 0, 2);
            }
            else
            {
                Ry = get_pixel(im, y + 1, 0, 0) - get_pixel(im, y - 1, 0, 0);
                Gy = get_pixel(im, y + 1, 0, 1) - get_pixel(im, y - 1, 0, 1);
                By = get_pixel(im, y + 1, 0, 2) - get_pixel(im, y - 1, 0, 2);
            }

            tot_energy = sqrt(Ry*Ry + Gy*Gy + By*By)/10;
            uint8_t total = (uint8_t) tot_energy;
            set_pixel(*grad, y, 0, total, total, total);
        }
        return;
    }
    
    for(int y = 0; y < im->height; y++)
    {
        for(int x = 0; x < im->width; x++)
        {
            int tot_energy = 0;
            int Rx, Ry, Gx, Gy, Bx, By;

            if(x == 0) 
            {
                Rx = get_pixel(im, y, x + 1, 0) - get_pixel(im, y, im->width - 1 , 0);
                Gx = get_pixel(im, y, x + 1, 1) - get_pixel(im, y, im->width - 1 , 1);
                Bx = get_pixel(im, y, x + 1, 2) - get_pixel(im, y, im->width - 1 , 2);
            }
            else if(x == (im->width - 1))
            {
                Rx = get_pixel(im, y, 0, 0) - get_pixel(im, y, x - 1 , 0);
                Gx = get_pixel(im, y, 0, 1) - get_pixel(im, y, x - 1 , 1);
                Bx = get_pixel(im, y, 0, 2) - get_pixel(im, y, x - 1 , 2);
            }
            else
            {
                Rx = get_pixel(im, y, x + 1, 0) - get_pixel(im, y, x - 1 , 0);
                Gx = get_pixel(im, y, x + 1, 1) - get_pixel(im, y, x - 1 , 1);
                Bx = get_pixel(im, y, x + 1, 2) - get_pixel(im, y, x - 1 , 2);
            }

            if(y == 0)
            {
                Ry = get_pixel(im, y + 1, x, 0) - get_pixel(im, im->height - 1, x, 0);
                Gy = get_pixel(im, y + 1, x, 1) - get_pixel(im, im->height - 1, x, 1);
                By = get_pixel(im, y + 1, x, 2) - get_pixel(im, im->height - 1, x, 2);
            }

            else if(y == (im->height - 1))
            {
                Ry = get_pixel(im, 0, x, 0) - get_pixel(im, y - 1, x, 0);
                Gy = get_pixel(im, 0, x, 1) - get_pixel(im, y - 1, x, 1);
                By = get_pixel(im, 0, x, 2) - get_pixel(im, y - 1, x, 2);
            }
            else
            {
                Ry = get_pixel(im, y + 1, x, 0) - get_pixel(im, y - 1, x, 0);
                Gy = get_pixel(im, y + 1, x, 1) - get_pixel(im, y - 1, x, 1);
                By = get_pixel(im, y + 1, x, 2) - get_pixel(im, y - 1, x, 2);
            }

            tot_energy = sqrt(Rx*Rx + Ry*Ry + Gx*Gx + Gy*Gy + Bx*Bx + By*By)/10;
            uint8_t total = (uint8_t) tot_energy; // is this how we recast
            set_pixel(*grad, y, x, total, total, total);
        }
    }
}

void dynamic_seam(struct rgb_img *grad, double **best_arr)
{
    *best_arr = (double*)malloc(grad->height * grad->width * sizeof(double)); // necessary to add sizeof?
    for (int j = 0; j < grad->width; j++)
    {
        (*best_arr)[j] = get_pixel(grad, 0, j, 0);
    }
    for (int i = 1; i < grad->height; i++)
    {
        for (int j = 0; j < grad->width; j++)
        {
            int min1, min2, min3;
            if (j == 0 || j == (grad->width - 1))
            {
                
                if (j == 0)
                {
                    min1 = (*best_arr)[(i-1)*grad->width + j];  
                    min2 = (*best_arr)[(i-1)*grad->width + j + 1];
                }
                else
                {
                    min1 = (*best_arr)[(i-1)*grad->width + j];
                    min2 = (*best_arr)[(i-1)*grad->width + j - 1];
                }
                (*best_arr)[i*grad->width + j] = get_pixel(grad, i, j, 0) + fmin(min1, min2);
            }
            else
            {
                min1 = (*best_arr)[(i-1)*grad->width + j];
                min2 = (*best_arr)[(i-1)*grad->width + j + 1];
                min3 = (*best_arr)[(i-1)*grad->width + j - 1];
                (*best_arr)[i*grad->width + j] = get_pixel(grad, i, j, 0) + fmin(min3, fmin(min1, min2)); //am i allowed to use fmin
            }
        }
    }
}

void recover_path(double *best, int height, int width, int **path)
{
    *path = (int*)malloc(height * sizeof(int));
    int min_h = best[(height - 1)*width];
    int width_h = 0;
    for (int i = 1; i < width; i++)
    {
        if (best[(height - 1)*width + i] < min_h) // what happens if they are equal
        {
            min_h = best[(height - 1)*width + i];
            width_h = i;
        }
    }
    (*path)[height - 1] = width_h;
    for (int j = (height - 2); j >= 0; j--)
    {
        int width_1, width_2, width_3;
        double min1, min2, min3;
        if (width_h == 0 || width_h == (width - 1))
        {
            if (width_h == 0)
            {
                min1 = (best)[(j-1)*width];
                width_1 = width_h;
                min2 = (best)[(j-1)*width + 1];
                width_2 = width_h + 1;
            }
            else
            {
                min1 = (best)[(j-1)*width + width_h];
                width_1 = width_h;
                min2 = (best)[(j-1)*width + width_h - 1];
                width_2 = width_h - 1;
            }

            if (min1 <= min2)
            {
                width_h = width_1;
            }
            else
            {
                width_h = width_2;
            }
        }
        else
        {
            min1 = (best)[(j)*width + width_h];
            width_1 = width_h;
            min2 = (best)[(j)*width + width_h + 1];
            width_2 = width_h + 1;
            min3 = (best)[(j)*width + width_h - 1];
            width_3 = width_h - 1;
            if (min1 <= min2 && min1 <= min3)
            {
                width_h = width_1;
            }
            else if(min2 <= min3)
            {
                width_h = width_2;
            }
            else
            {
                width_h = width_3;
            }
        }
        (*path)[j] = width_h;
    }

}



void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path) // Do I need to worry about edge cases like for calc_energy
{
    *dest = (struct rgb_img*)malloc(sizeof(struct rgb_img));
    (*dest)->height = src->height;
    (*dest)->width = src->width - 1;
    (*dest)->raster = (uint8_t*)malloc(3*(src->height)*(src->width - 1)*sizeof(uint8_t));
    int j = 0;
    for (int y = 0; y < (*dest)->height; y++)
    {
        int x = 0;
        int n = 0;
        while (n < src->width)
        {
            if (path[j] != n)
            {
                set_pixel(*dest, y, x, get_pixel(src, y, n, 0), get_pixel(src, y, n, 1), get_pixel(src, y, n, 2));
                x++;

            }
            n++;
        }
        j++;
    }
}


