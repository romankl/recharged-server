#include <stdio.h>

#include "error.h"
#include "uv.h"

void checkForError(int code) {
    if (code != 0) {
        fprintf(stderr, "Error: %s - %s", uv_strerror(code), uv_err_name(code));
    }
}
