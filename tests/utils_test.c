#include <criterion/criterion.h>
#include "gl_utils.h"

Test(utils, s) {
    createShaderProgram(NULL);
}

Test(utils, b) {
    cr_assert(0, "trash 111");
}