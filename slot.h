#ifndef SLOT_H
#define SLOT_H

#include <stddef.h>

#include "functions.h"

/*  A slot is an object that is intended to be used for user interaction or
    drawing images. 'x_pos', 'y_pos', 'width', and 'height' are intuitively
    used to represent the area of the screen where the object exists. 'value'
    provides a somewhat arbitrary way to allow individual slot objects to act
    differently.
    
    An array of slots is referred to as a "slot cluster" or "cluster". This
    allows for easy grouping of related slot objects and also allows them to
    be drawn together in specified row/column patterns.
    
    Drawing functions are placed in "slot_draw.h" to allow for easy use with a
    different graphics library. */
struct slot
{
    float x_pos, y_pos, width, height;
    int value;
};

/*  Initializes all members of 'slot' using the provided values. This should
    always be called first to avoid accidentally attempting to use any
    uninitialized variables. */
void initialize_slot(struct slot *slot, int value,
                     float x_pos, float y_pos, float width, float height);

/*  Sets the "value" member of 'slot'. */
void set_slot_value(struct slot *slot, int value);

/*  Sets the coordinate variables of 'slot'. */
void set_slot_area(struct slot *slot,
                   float x_pos, float y_pos, float width, float height);

/*  Initializes all members of all slot objects in 'cluster'. Each slot
    object's "value" member is set to 'value'. The 'rows' and 'cols'
    arguments are used to evenly divide the space specified by the
    'cluster_x_pos' through 'cluster_height' arguments, so that each slot
    occupies roughly the same amount of space when drawn. */
void initialize_slot_cluster(struct slot cluster[], int rows, int cols, int value,
                             float cluster_x_pos, float cluster_y_pos,
                             float cluster_width, float cluster_height);

/*  Sets all "value" members for slots  within 'cluster' to 'value'. Likewise,
    'cluster_size' refers to the amount of elements in 'cluster'. */
void set_slot_cluster_value(struct slot cluster[], size_t cluster_size, int value);

/*  Sets the area of the entire 'cluster', equally dividing the space between
    'rows' and 'cols'. */
void set_slot_cluster_area(struct slot cluster[], int rows, int cols,
                           float cluster_x_pos, float cluster_y_pos,
                           float cluster_width, float cluster_height);

/*  Searches'cluster' for a slot object existing at ('x', 'y'). Likewise,
    'cluster_size' refers to the amount of elements 'cluster'. If found,
    returns a pointer to the slot object at ('x', 'y'), otherwise returns
    a NULL pointer.
    
    Note: ('x', 'y') refer to actual coordinates on the screen, and not the
    row/column pair of an array. */
struct slot* get_slot_at_pos(struct slot cluster[], size_t cluster_size, int x, int y);

/*  Returns the row or column index of the 'slot' in 'cluster', depending
    on whether 'coord_type' is X_AXIS or Y_AXIS. Returns the index value of
    said coordinate if successful, otherwise -1. 'rows' and 'cols'
    refer to 'cluster'. */
int get_slot_coordinate(enum coord coord_type, struct slot* slot, struct slot cluster[], int rows, int cols);

#endif