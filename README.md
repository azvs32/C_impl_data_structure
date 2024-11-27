# C_impl_data_structure

+ [线性表的使用](./README-linear.md)

---

# 日志模块

## 修改日志级别

```c++
// 将输出所有高于指定级别的日志，日志级别由低到高排列如下：
//    LOG_LEVEL_DEBUG
//    LOG_LEVEL_INFO
//    LOG_LEVEL_WARN
//    LOG_LEVEL_ERROR  默认
set_log_level(LogLevel level);
// 提供给外部输出日志的方法
LOG_MSG(LogLevel level, char *format, ...)
```

---

# 准备测试数据

## char

```c++
// 用于测试的数据
char c0 = 'd', c1 = 'b', c2 = 'a', c3 = 'e', c4 = 'c';

// 自定义输出的规则
void operate_char_print(void *data) {
    if (data == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "内部错误");
        return;
    }
    char c = *(char*)data;
    printf("[%c]   ", c);
}

// 自定义排序规则
int operate_char_sort(const void *a, const void *b) {
    return *(char*)a - *(char*)b;
}
```

## int

```c++
// 用于测试的数据
int a = 1, b = 6, c = 3, d = 8, e = 9;

// 自定义输出的规则
void operate_int_print(void *data) {
    if (data == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "内部错误");
        return;
    }
    int i = *(int*)data;
    printf("[%d]   ", i);
}

// 自定义排序规则
int operate_int_sort(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}
```

## double

```c++
// 用于测试的数据
double a = 1.4, b = 4.2, c = 2.4, d = 8.3, e = 3.5;

// 自定义输出的规则
void operate_double_print(void *data) {
    if (data == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "内部错误");
        return;
    }
    double i = *(double*)data;
    printf("[%.2lf]   ", i);
}

// 自定义排序规则
int operate_double_sort(const void *a, const void *b) {
    double d1 = *(double*)a;
    double d2 = *(double*)b;
    return d1 ? d2 ? -1 : 1;
}
```

## string

```c++
// 用于测试的数据
char *my_str[16] = { "linear", "linked", "tree" };
char *str1 = "graph";
char *str2 = "struct";

// 自定义输出的规则
void operate_string_print(void *data) {
    if (data == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "内部错误");
        return;
    }
    char *str = data;
    printf("%16s", str);
}

// 自定义排序规则
int operate_string_sort(const void *a, const void *b) {
    char *str1 = a;
    char *str2 = b;
    return strcmp(str1, str2);
}
```

## simple structure

```c++
// 定义简单结构体
typedef struct azvs_simple {
    int x;
    int y;
} ASimple, *APSimple;

// 初始化 APSimple 数据
APSimple init_simple(const int x, const int y) {
    APSimple simple = NEW(ASimple);
    simple->x = x;
    simple->y = y;
    return simple;
}

// 用于测试的数据
ASimple simple1 = {6, 5};
ASimple simple2 = {2, 9};
ASimple simple3 = {4, 3};
APSimple simple4, simple5, simple6;
void init_simple_test_data() {
    simple4 = init_simple(1, 5);
    simple5 = init_simple(1, 8);
    simple6 = init_simple(3, 4);
}

// 自定义输出的规则
void operate_simple_print(void *data) {
    if (data == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "内部错误");
        return;
    }
    APSimple simple = (APSimple) data;
    printf("[x:%d,y:%d]   ", simple->x, simple->y);
}

// 自定义排序规则
int operate_simple_sort(const void *a, const void *b) {
    ASimple s1 = *(ASimple *) a;
    ASimple s2 = *(ASimple *) b;
    if (s1.x != s2.x) {
        return s1.x < s2.x ? -1 : 1;
    }
    return s1.y < s2.y ? -1 : 1;
}
```

## complex structure

```c++
// 定义复杂结构体
typedef struct azvs_complex {
    char c;
    int i;
    double d;
    ASimple s;
} AComplex, *APComplex;

// 初始化 APSimple 数据
APComplex init_complex(const char c, const int i, const double d, const int x, const int y) {
    APComplex complex = NEW(AComplex);
    complex->c = c;
    complex->i = i;
    complex->d = d;
    complex->s.x = x;
    complex->s.y = y;
    return complex;
}

// 用于测试的数据
AComplex complex1 = {.c = 'A', .i = 10, .d = 3.14, .s = {.x = 1, .y = 2}};
AComplex complex2 = {.c = 'D', .i = 20, .d = 1.23, .s = {.x = 2, .y = 4}};
AComplex complex3 = {.c = 'H', .i = 50, .d = 8.22, .s = {.x = 1, .y = 8}};
APComplex complex4, complex5, complex6;
void init_complex_test_data() {
    complex4 = init_complex('Z', 30, 2.64, 4, 2);
    complex5 = init_complex('Q', 12, 1.54, 3, 1);
    complex6 = init_complex('L', 18, 0.98, 5, 2);
}

// 自定义输出的规则
void operate_complex_print(void *data) {
    if (data == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "内部错误");
        return;
    }
    APComplex complex = (APComplex) data;
    printf("[{'%c',%d,%.2lf,{%d,%d}}]   ", complex->c, complex->i, complex->d, complex->s.x, complex->s.y);
}

// 自定义排序规则
int operate_complex_sort(const void *a, const void *b) {
    AComplex c1 = *(AComplex *) a;
    AComplex c2 = *(AComplex *) b;
    if (c1.c != c2.c) {
        return c1.c < c2.c ? -1 : 1;
    }
    if (c1.i != c2.i) {
        return c1.c < c2.c ? -1 : 1;
    }
    if (c1.d != c2.d) {
        return c1.d < c2.d ? -1 : 1;
    }
    if (c1.s.x != c2.s.x) {
        return c1.s.x < c2.s.x ? -1 : 1;
    }
    return c1.s.y < c2.s.y ? -1 : 1;
}
```