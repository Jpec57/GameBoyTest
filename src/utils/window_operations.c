#include "../../includes/main.h"

void wait_frames(INT8 count) {
    while (count) {
        count -= SILVER;
        wait_vbl_done();
    }
}
