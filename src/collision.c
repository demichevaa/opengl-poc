#include "collision.h"

int collision_check_ABBB(Sprite *p_a, Sprite *p_b) {
        float a_x_right = p_a->X + p_a->width;
        float a_x_left = p_a->X;
        float a_y_top = p_a->Y + p_a->height;
        float a_y_bottom = p_a->Y;

        float b_x_right = p_b->X + p_b->width;
        float b_x_left = p_b->X;
        float b_y_top = p_b->Y + p_b->width;
        float b_y_bottom = p_b->Y;


        bool has_x_collision = a_x_right >= b_x_left && a_x_left <= b_x_right;
        bool has_y_collision = a_y_top >= b_y_bottom && a_y_bottom <= b_y_top;

        return has_x_collision && has_y_collision;
}