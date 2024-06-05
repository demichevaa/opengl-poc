#include <criterion/criterion.h>

Test(misc, failing) {
    cr_assert(0, "hell");
}

Test(misc, passing) {
    cr_assert(1);
}
