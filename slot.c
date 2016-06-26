#include <stdio.h>

#include "constants.c"
#include "functions.h"
#include "slot.h"

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
    slot->x_pos = x_pos;
    slot->y_pos = y_pos;
    slot->width = width;
    slot->height = height; 
}

void initialize_slot_cluster(struct slot cluster[], int rows, int cols, int value,
                             float cluster_x_pos, float cluster_y_pos,
                             float cluster_width, float cluster_height)
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
    //printf("slot_width = %f, slot_height = %f\n", slot_width, slot_height);
    
    float slot_x_pos = cluster_x_pos; // Starting position of each row.
    float slot_y_pos = cluster_y_pos; // Starting position of each column.
    
    size_t i, j, counter = 0;
    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < cols; ++j)
        {
            set_slot_area(&cluster[counter], slot_x_pos, slot_y_pos, slot_width, slot_height);            
            slot_x_pos += slot_width;
            ++counter;
        }
        
        slot_x_pos = cluster_x_pos;
        slot_y_pos += slot_height;
    }
}

struct slot* get_slot_at_pos(struct slot cluster[], size_t cluster_size, int x, int y)
{
    size_t i;
    for (i = 0; i < cluster_size; ++i)
    {       
        if (mouse_over_area(x, y, cluster[i].x_pos, cluster[i].y_pos, cluster[i].width, cluster[i].height))
        {
            return &cluster[i];
        }
    }
    
    return NULL; // If not found, NULL will be returned.
}

int get_slot_coordinate(enum coord coord_type, struct slot* slot, struct slot cluster[], int rows, int cols)
{
    size_t i, j, counter = 0;
    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < cols; ++j)
        {
            if (&cluster[counter] == slot)
            {
                if (coord_type == X_AXIS)
                    return i;
                else if (coord_type == Y_AXIS)
                    return j;
                else
                    return -1;
            }
            
            ++counter;
        }
    }
}