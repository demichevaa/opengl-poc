#include "collision.h"

struct Collision {

};

bool collision_check_ABBB(struct Sprite *p_a, struct Sprite *p_b) {
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

float clamp(float value, float min, float max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
}


bool collision_check_circle_ABBB(struct Sprite *p_circle, struct Sprite *p_rectangle) {
        float radius = p_circle->width / 2;
        vec2 circle_center = {
                p_circle->X + radius,
                p_circle->Y + radius
        };

        vec2 closest = {
                clamp(circle_center[0], p_rectangle->X, p_rectangle->X + p_rectangle->width),
                clamp(circle_center[1], p_rectangle->Y, p_rectangle->Y + p_rectangle->height)
        };

        vec2 distance;
        glm_vec2_sub(circle_center, closest, distance);

        float distance_squared = distance[0] * distance[0] + distance[1] * distance[1];

        return distance_squared <= (radius * radius);
}

bool collision_check_x(struct Sprite *p_a, float min_x, float max_x) {
        return (p_a->X <= min_x) || (p_a->X + p_a->width) >= max_x;
}

bool collision_has_overlap_x(struct Sprite *p_a, struct Sprite *p_b) {
        return (p_a->X <= p_b->X) || (p_a->X + p_a->width) >= ;
}