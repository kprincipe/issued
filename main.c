#include <stdio.h>

#define UTILS_IMPLEMENTATION
#include "utils.h"

int main(void) {
    char *filepath = "main.c";

    String_Builder sb = {0};
    if (!util_read_file(&sb, filepath)) {
        fprintf(stderr, "error: coud not open file: %s\n", filepath);
    }

    String_View buffer = util_svn_from_sb(&sb, sb.count);

    // TODO: foo
    int line = 1;
    for (size_t i = 0; i < buffer.count; ++i) {
        if (buffer.items[i] == '/' && buffer.items[i + 1] == '/') {
            i += 3;
            char *start = buffer.items + i;

            int len = 0;
            while (buffer.items[i] != '\n') {
                len++;
                i++;
            }

            String_View comment = util_svn(start, len);
            printf("%s:%d: %.*s\n", filepath, line, comment.count, comment.items);
        }

        if (buffer.items[i] == '\n') line++;
    }
    // TODO: bar

    return 0;
    // TODO: baz
}
