#include "cubparse.h"

void get_width_height(t_cubfile *cub, t_string rest);
void copy_map_data(char *dst, t_string src, int width);
int apply_line(t_cubfile *cub, t_string line, int flag);
int parse_color(t_string s);

t_cubfile* read_cubfile(int fd) {
    t_cubfile *res = (t_cubfile*) malloc(sizeof(t_cubfile));
    if (!res) {
        return 0;
    }

    t_string line = make_string();
    unsigned int flag = 0;
    while (flag != 63) {
        readline(&line, fd);
        if (!line.buf) {
            free(res);
            return 0;
        }
        if (line.length == 0) {
            destroy_string(&line);
            free(res);
            return 0;
        }
        flag = apply_line(res, trim(&line, " \r\n\t"), flag);
    }
    destroy_string(&line);

    t_string rest = make_string();
    readall(&rest, fd);
    if (!rest.buf) {
        free(res);
        return 0;
    }
    close(fd);

    get_width_height(res, rest);
    const int sz_data = res->map_width * res->map_height;
    res->map_data = (char*) malloc(sizeof(char) * sz_data);
    if (!res->map_data) {
        free(res);
        return 0;
    }

    copy_map_data(res->map_data, rest, res->map_width);

    return res;
}

void destroy_cubfile(t_cubfile **cub) {
    free((*cub)->map_data);
    free(*cub);
}

void get_width_height(t_cubfile *cub, t_string rest) {
    int width = 0, height = 0;
    int begin = 0, end = 0;
    while (end <= rest.length) {
        if (end >= rest.length || rest.buf[end] == '\n') {
            width = max2i(width, end - begin);
            height++;
            begin = end + 1;
        }
        end++;
    }
    cub->map_width = width;
    cub->map_height = height;
}

void copy_map_data(char *dst, t_string src, int width) {
    int i = 0;
    int begin = 0, end = 0;
    while (end <= src.length) {
        if (end >= src.length || src.buf[end] == '\n') {
            int len = end - begin;
            memcpy(dst + (i * width), src.buf + begin, len);
            memset(dst + (i * width) + len, ' ', width - len);
            i++;
            begin = end + 1;
        }
        end++;
    }
}

int apply_line(t_cubfile *cub, t_string line, int flag) {
    if (line.length >= 2 && !memcmp(line.buf, "NO", 2)) {
        line = sub_string(&line, 2, line.length - 2);
        line = trim(&line, " \r\n\t");
        memcpy(cub->no_texture_path, line.buf, line.length);
        cub->no_texture_path[line.length] = 0;
        return flag | 1;
    }
    if (line.length >= 2 && !memcmp(line.buf, "SO", 2)) {
        line = sub_string(&line, 2, line.length - 2);
        line = trim(&line, " \r\n\t");
        memcpy(cub->so_texture_path, line.buf, line.length);
        cub->so_texture_path[line.length] = 0;
        return flag | 2;
    }
    if (line.length >= 2 && !memcmp(line.buf, "WE", 2)) {
        line = sub_string(&line, 2, line.length - 2);
        line = trim(&line, " \r\n\t");
        memcpy(cub->we_texture_path, line.buf, line.length);
        cub->we_texture_path[line.length] = 0;
        return flag | 4;
    }
    if (line.length >= 2 && !memcmp(line.buf, "EA", 2)) {
        line = sub_string(&line, 2, line.length - 2);
        line = trim(&line, " \r\n\t");
        memcpy(cub->ea_texture_path, line.buf, line.length);
        cub->ea_texture_path[line.length] = 0;
        return flag | 8;
    }
    if (line.length >= 1 && !memcmp(line.buf, "F", 1)) {
        line = sub_string(&line, 1, line.length - 1);
        line = trim_left(&line, " \r\n\t");
        cub->color_floor = parse_color(line);
        return flag | 16;
    }
    if (line.length >= 1 && !memcmp(line.buf, "C", 1)) {
        line = sub_string(&line, 1, line.length - 1);
        line = trim_left(&line, " \r\n\t");
        cub->color_ceil = parse_color(line);
        return flag | 32;
    }
    return flag;
}

int parse_color(t_string s) {
    char* comma1 = strchr(s.buf, ',');
    if (!comma1)
        return -1;
    char* comma2 = strchr(comma1 + 1, ',');
    if (!comma2)
        return -1;
    int r = parse_int(s.buf, comma1 - s.buf) << 16;
    int g = parse_int(comma1 + 1, comma2 - comma1 - 1) << 8;
    int b = parse_int(comma2 + 1, s.length - (comma2 - s.buf + 1));
    return 0xff000000 | r | g | b;
}

void debug_print_cubfile(t_cubfile *cub) {
    printf("NO texture path: %s\n", cub->no_texture_path);
    printf("SO texture path: %s\n", cub->so_texture_path);
    printf("WE texture path: %s\n", cub->we_texture_path);
    printf("EA texture path: %s\n", cub->ea_texture_path);
    printf("ceil color: %6x\n", cub->color_ceil);
    printf("floor color: %6x\n", cub->color_floor);
    for (int i = 0; i < cub->map_height; i++) {
        for (int j = 0; j < cub->map_width; j++) {
            putchar(cub->map_data[i*cub->map_width + j]);
        }
        puts("");
    }
}
