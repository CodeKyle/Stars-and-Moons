#include "slot.h"

#include <stdio.h>

void initialize_slot(struct slot *slot, int value, float x_pos, float y_pos, float width, float height)
{
    set_slot_value(slot, value);
    set_slot_area(slot, x_pos, y_pos, width, height);
}

void set_slot_value(struct slot *slot, int value)
{
    slot->value = value;
}

void set_slot_area(struct slot *slot, float x_pos, float y_pos, float width, float height)
{
    //*slot = (struct slot){x_pos, y_pos, width, height};
    
    
    slot->x_pos = x_pos;
    slot->y_pos = y_pos;
    slot->width = width;
    slot->height = height; 
    
    //printf("set_slot_area: %f, %f, %f, %f\n", slot->x_pos, slot->y_pos, slot->width, slot->height);
}

void draw_slot(const struct slot *slot, SDL_Window *window, SDL_Surface *image)
{
    //printf("draw slot %f, %f, %f, %f\n", slot->x_pos, slot->y_pos, slot->width, slot->height);
    
    SDL_Rect area;
    area.x = slot->x_pos;
    area.y = slot->y_pos;
    area.w = slot->width;
    area.h = slot->height;

    draw_surface(window, image, area);
}



void initialize_slot_cluster(struct slot cluster[], int rows, int cols, int value,
                             float cluster_x_pos, float cluster_y_pos, float cluster_width, float cluster_height)
{
    set_slot_cluster_value(cluster, rows * cols, value);
    set_slot_cluster_area(cluster, rows, cols, cluster_x_pos, cluster_y_pos, cluster_width, cluster_height);
}

void set_slot_cluster_value(struct slot cluster[], size_t cluster_size, int value)
{
    size_t i;
    for (i = 0; i < cluster_size; ++i)
    {
        set_slot_value(&cluster[i], value);
    }
}

void set_slot_cluster_area(struct slot cluster[], int rows, int cols,
                           float cluster_x_pos, float cluster_y_pos, float cluster_width, float cluster_height)
{
    float slot_width = cluster_width / cols;
    float slot_height = cluster_height / rows;
    
    float slot_x_pos = cluster_x_pos;
    float slot_y_pos = cluster_y_pos;
    
    //printf("%f, %f, %f, %f\n", slot_x_pos, slot_y_pos, slot_width, slot_height);
    
    size_t i, j, counter = 0;
    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < cols; ++j)
        {
            //printf("s_s_c_a %f, %f, %f, %f\n", slot_x_pos, slot_y_pos, slot_width, slot_height);
            set_slot_area(&cluster[counter], slot_x_pos, slot_y_pos, slot_width, slot_height);
            
            slot_x_pos += slot_width;
            ++counter;
        }
        
        slot_x_pos = cluster_x_pos;
        slot_y_pos += slot_height;
    }
}

void draw_slot_cluster(const struct slot cluster[], size_t cluster_size, SDL_Surface *image_array[], SDL_Window *window)
{
    size_t i;
    for (i = 0; i < cluster_size; ++i)
    {
        draw_slot(&cluster[i], window, image_array[cluster[i].value]);
    }
}

struct slot* get_slot_at_pos(struct slot cluster[], size_t cluster_size, int x, int y)
{
    size_t i;
    for (i = 0; i < cluster_size; ++i)
    {
        int slot_x = cluster[i].x_pos;
        int slot_y = cluster[i].y_pos;
        int slot_w = cluster[i].width;
        int slot_h = cluster[i].height;
        
        if (mouse_over_area(x, y, slot_x, slot_y, slot_w, slot_h))
        {
            return &cluster[i];
        }
    }
    
    return NULL;
}
