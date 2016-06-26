#include "SDL.h"

struct slot
{
    float x_pos, y_pos, width, height;
    int value;
};

void initialize_slot(struct slot *slot, int value, float x_pos, float y_pos, float width, float height);
void set_slot_area(struct slot *slot, float x_pos, float y_pos, float width, float height);
void set_slot_value(struct slot *slot, int value);
void draw_slot(const struct slot *slot, SDL_Window *window, SDL_Surface *image);


void initialize_slot_cluster(struct slot cluster[], int rows, int cols, int value,
                             float cluster_x_pos, float cluster_y_pos, float cluster_width, float cluster_height);
void set_slot_cluster_value(struct slot cluster[], size_t cluster_size, int value);
void set_slot_cluster_area(struct slot cluster[], int rows, int cols,
                           float cluster_x_pos, float cluster_y_pos, float cluster_width, float cluster_height);
void draw_slot_cluster(const struct slot cluster[], size_t cluster_size, SDL_Surface *image_array[], SDL_Window *window);



struct slot* get_slot_at_pos(struct slot cluster[], size_t cluster_size, int x, int y);