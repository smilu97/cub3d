#include "util.h"

void ensure_string_capacity(t_string *s, int dst_capacity);
void ensure_arraylist_capacity(t_arraylist *array, int dst_capacity);

t_ivec2 make_ivec2(int x, int y) {
    t_ivec2 r;
    r.x = x;
    r.y = y;
    return r;
}

t_fvec2 make_fvec2(float x, float y) {
    t_fvec2 r;
    r.x = x;
    r.y = y;
    return r;
}

t_fvec4 color_to_fvec4(int color) {
    t_fvec4 r;
    r.x = ((float) ((color >> 24) & 0xFF)) / 255.0f;
    r.y = ((float) ((color >> 16) & 0xFF)) / 255.0f;
    r.z = ((float) ((color >>  8) & 0xFF)) / 255.0f;
    r.w = ((float) ((color >>  0) & 0xFF)) / 255.0f;
    return r;
}

t_fvec4 add_fvec4(t_fvec4 v1, t_fvec4 v2) {
    t_fvec4 r;
    r.x = v1.x + v2.x;
    r.y = v1.y + v2.y;
    r.z = v1.z + v2.z;
    r.w = v1.w + v2.w;
    return r;
}

t_fvec2 sub_fvec2(t_fvec2 v1, t_fvec2 v2) {
    t_fvec2 r;
    r.x = v1.x - v2.x;
    r.y = v1.y - v2.y;
    return r;
}

t_fvec4 mul_fvec4_f(t_fvec4 v, float f) {
    t_fvec4 r;
    r.x = v.x * f;
    r.y = v.y * f;
    r.z = v.z * f;
    r.w = v.w * f;
    return r;
}

t_fvec4 interpolate_fvec4(t_fvec4 v1, t_fvec4 v2, float w) {
    // v1 * (1-w) + v2 * w;
    return add_fvec4(mul_fvec4_f(v1, 1-w), mul_fvec4_f(v2, w));
}

float distance_fvec2(t_fvec2 v) {
    return sqrtf(v.x*v.x + v.y*v.y);
}

float rev_interpolate_fvec2(t_fvec2 t, t_fvec2 p1, t_fvec2 p2) {
    t  = sub_fvec2(t , p1);
    p2 = sub_fvec2(p2, p1);
    if (fabsf(p2.x) > 0.0001f)
        return t.x / p2.x;
    return t.y / p2.y;
}

int fvec4_to_color(t_fvec4 v) {
    int t = (((int) (v.x * 255.0f)) & 0xFF) << 24;
    int r = (((int) (v.y * 255.0f)) & 0xFF) << 16;
    int g = (((int) (v.z * 255.0f)) & 0xFF) <<  8;
    int b = (((int) (v.w * 255.0f)) & 0xFF) <<  0;
    return t | r | g | b;
}

void swap_fvec2(t_fvec2 *p1, t_fvec2 *p2) {
    float tmp;
    tmp = p1->x;
    p1->x = p2->x;
    p2->x = tmp;
    tmp = p1->y;
    p1->y = p2->y;
    p2->y = tmp;
}

int max2i(int a, int b) {
    return a - ((a-b) & (a-b)>>31);
}

int min2i(int a, int b) {
    return b + ((a-b) & (a-b)>>31);
}

int parse_int(const char *s, int len) {
    int res = 0;
    while (len && '0' <= *s && *s <= '9') {
        res = (res * 10) + (*s - '0');
        s++;
        len--;
    }
    return res;
}

/**
 * 
 * @brief on failure, return.buf is null
 * 
 * @return t_string 
 */
t_string make_string() {
    t_string res;
    res.capacity = 32;
    res.length = 0;
    res.buf = (char*) malloc(sizeof(char) * res.capacity);
    return res;
}

/**
 * @brief reference string
 * 
 * @param src 
 * @return t_string 
 */
t_string ref_string(t_string *src) {
    t_string res;
    memcpy(&res, src, sizeof(t_string));
    return res;
}

/**
 * @brief
 * 
 * @param src 
 * @param from 
 * @param length 
 * @return t_string 
 */
t_string sub_string(t_string *src, int from, int length) {
    t_string res = ref_string(src);
    res.buf += from;
    res.capacity -= from;
    res.length = min2i(res.length - from, length);
    return res;
}

void clean_string(t_string *s) {
    s->buf = 0;
    s->capacity = 0;
    s->length = 0;
}

void destroy_string(t_string *s) {
    free(s->buf);
    clean_string(s);
}

/**
 * @brief on failure, line is destroyed
 * 
 * @return t_string 
 */
void readline(t_string *line, int fd) {
    line->length = 0;
    int length = 0;
    char ch = 0;
    while (ch != '\n' && read(fd, &ch, 1)) {
        append_string(line, ch);
        if (line->length == length++) {
            destroy_string(line);
            return;
        }
    }
}

void readall(t_string *s, int fd) {
    s->length = 0;
    int length = 0;
    char ch = 0;
    while (read(fd, &ch, 1)) {
        append_string(s, ch);
        if (s->length == length++) {
            destroy_string(s);
            return;
        }
    }
}

/**
 * @brief on failure, length is not modified
 * 
 * @param s 
 * @param ch 
 */
void append_string(t_string *s, char ch) {
    if (s->capacity < s->length + 1) {
        ensure_string_capacity(s, s->capacity * 2);
        if (s->capacity < s->length + 1)
            return;
    }
    s->buf[s->length++] = ch;
}

/**
 * @brief on failure, capacity is not modified
 * 
 * @param s 
 * @param dst_capacity 
 */
void ensure_string_capacity(t_string *s, int dst_capacity) {
    if (s->capacity >= dst_capacity)
        return;
    
    char *new_buf = (char*) malloc(sizeof(char) * dst_capacity);
    if (!new_buf)
        return;

    memcpy(new_buf, s->buf, sizeof(char) * s->length);
    free(s->buf);
    s->buf = new_buf;
    s->capacity = dst_capacity;
}

t_string trim_left(t_string *src, char *blacklist) {
    t_string res = ref_string(src);
    while (res.length && strchr(blacklist, res.buf[0])) {
        res.buf++;
        res.capacity--;
        res.length--;
    }
    return res;
}

t_string trim_right(t_string *src, char *blacklist) {
    t_string res = ref_string(src);
    while (res.length && strchr(blacklist, res.buf[res.length - 1])) {
        res.capacity--;
        res.length--;
    }
    return res;
}

t_string trim(t_string *src, char *blacklist) {
    t_string res = trim_left(src, blacklist);
    return trim_right(&res, blacklist);
}

t_arraylist make_arraylist() {
    t_arraylist res;
    res.capacity = 32;
    res.length = 0;
    res.buf = (void**) malloc(sizeof(void*) * res.capacity);
    return res;
}

void clean_arraylist(t_arraylist *array) {
    array->capacity = 0;
    array->length = 0;
    array->buf = 0;
}

void destroy_arraylist(t_arraylist *array) {
    free(array->buf);
    clean_arraylist(array);
}

void ensure_arraylist_capacity(t_arraylist *array, int dst_capacity) {
    if (array->capacity >= dst_capacity)
        return;
    
    void *new_buf = (void**) malloc(sizeof(void*) * dst_capacity);
    if (!new_buf)
        return;

    memcpy(new_buf, array->buf, sizeof(void*) * array->length);
    free(array->buf);
    array->buf = new_buf;
    array->capacity = dst_capacity;
}

void append_arraylist(t_arraylist *array, void *el) {
    if (array->capacity < array->length + 1) {
        ensure_arraylist_capacity(array, array->capacity * 2);
        if (array->capacity < array->length + 1)
            return;
    }
    array->buf[array->length++] = el;
}
