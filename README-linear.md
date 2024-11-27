# 线性表

## 已实现的函数，以双下划线开头的函数不应该被用户调用
``` c++
// 初始化线性表，使用 #define 简化
APLinear __a_linear_init(size_t total, size_t data_size, char *data_type);
#define a_linear_init(total, type) __a_linear_init(total, sizeof(type), #type)

// 释放线性表，使用 #define 简化
void __a_linear_free(APLinear *linear);
#define a_linear_free(linear) __a_linear_free(&(linear))

// 将数据存入指定下标。若原本有数据则覆盖
void a_linear_set(APLinear linear, const void *data, size_t index);

// 使用 ap_linear_get 函数返回的线性表中元素的地址，如果在外部修改了，会影响到线性表中的元素。
// 使用 a_linear_get   函数会将线性表中的元素复制一份返回，外部元素修改不会影响到线性表中的元素。
// 若存储的数据原本就是地址类型，通常使用 ap_linear_get 处理。
void *ap_linear_get(APLinear linear, size_t index);
#define a_linear_get(linear, index, type) (*((type *)ap_linear_get(linear, index)))

// 删除线性表中指定下标的元素
void a_linear_del(APLinear linear, size_t index);

// 线性表排序，使用回调函数定义排序规则
void a_linear_sort(APLinear linear, int (*operate)(const void *, const void *));

// 输出线性表的每个元素
void a_linear_print(APLinear linear, void (*operate)(void *), const char *end);

// 输出线性表的基本信息
void a_linear_print_info(APLinear linear);
// 返回线性表中数据的类型
const char *a_linear_get_type(APLinear linear);
// 返回线性表中已经存储的数据个数
size_t a_linear_get_count(APLinear linear);
// 返回线性表允许容纳的最大数据个数
size_t a_linear_get_total(APLinear linear);
```

## char 类型的使用案例
> [char 类型测试数据及相关函数](./README.md#char) 
```c++
void main() {
    // 初始化线性表
    APLinear linear = a_linear_init(5, char);

    // 将数据插入到线性表中
    a_linear_set(linear, &c0, 0);
    a_linear_set(linear, &c1, 1);
    a_linear_set(linear, &c2, 2);
    a_linear_set(linear, &c3, 3);
    a_linear_set(linear, &c4, 4);

    // 输出数据
    printf("初始化的数据：");
    a_linear_print(linear, operate_char_print, "\n");

    // 获取指定下标的数据, 指定的数据类型需要与初始化的类型匹配
    char get_c = a_linear_get(linear, 0, char);
    printf("获取到 0 号元素的数据：[%c]\n", get_c);
    printf("a_linear_get(linear, 0, char)：%c\n", get_c);
    get_c = 'A'; // 不会影响到线性表中的数据
    // // 该方法用于获取数据的地址，外部修改会影响到线性表内部对应的数据
    // char *get_cp = ap_linear_get(linear, 0);
    // printf("获取到 0 号元素的数据：[%c]\n", *get_cp);
    // *get_cp = 'A'; // 会影响到线性表中的数据

    // 排序
    a_linear_sort(linear, operate_char_sort);

    // 输出数据
    printf("排序后的数据：");
    a_linear_print(linear, operate_char_print, "\n");

    // 删除指定下标的数据
    a_linear_del(linear, 0);

    // 输出线性表的基本信息
    a_linear_print_info(linear);
    printf("a_linear_get_type  : %s\n", a_linear_get_type(linear));
    printf("a_linear_get_count : %zu\n", a_linear_get_count(linear));
    printf("a_linear_get_total : %zu\n", a_linear_get_total(linear));

    // 释放线性表内存
    a_linear_free(linear);
}
```

## string 类型的使用案例
> [string 类型测试数据及相关函数](./README.md#string)
```c++
void main() {
    // 初始化线性表
    APLinear linear = a_linear_init(5, char[16]);

    // 将数据插入到线性表中
    for (int i = 0; i < 3; i ++) {
        a_linear_set(linear, my_str[i], i);
    }
    a_linear_set(linear, str1, 3);
    a_linear_set(linear, str2, 4);

    // 输出数据
    printf("初始化的数据：");
    a_linear_print(linear, operate_string_print, "\n");

    // 获取指定下标的数据, 字符串本身是引用类型，因此使用ap_linear_get方法
    char * get_str = ap_linear_get(linear, 1);
    printf("ap_linear_get(linear, 1)：%s\n", get_str);

    // 排序
    a_linear_sort(linear, operate_string_sort);

    // 输出数据
    printf("排序后的数据：");
    a_linear_print(linear, operate_string_print, "\n");

    // 删除指定下标的数据
    a_linear_del(linear, 0);

    // 输出数据
    printf("删除后的数据：");
    a_linear_print(linear, operate_string_print, "\n");

    // 输出线性表的基本信息
    a_linear_print_info(linear);
    printf("a_linear_get_type  : %s\n", a_linear_get_type(linear));
    printf("a_linear_get_count : %zu\n", a_linear_get_count(linear));
    printf("a_linear_get_total : %zu\n", a_linear_get_total(linear));

    // 释放线性表内存
    a_linear_free(linear);
}
```

## complex structure 类型的使用案例
> [complex structure 类型测试数据及相关函数](./README.md#complex-structure)
> 
> AComplex结构体中包含了ASimple结构体类型，因此也需要复制以下内容
> 
> [simple structure 类型测试数据及相关函数](./README.md#simple-structure)
```c++
void main() {
    init_complex_test_data();
    // 初始化线性表
    APLinear linear = a_linear_init(6, AComplex);

    // 将数据插入到线性表中，注意值类型和引用类型插入数据的不同
    a_linear_set(linear, &complex1, 0);
    a_linear_set(linear, &complex2, 1);
    a_linear_set(linear, &complex3, 2);
    a_linear_set(linear, complex4, 3);
    a_linear_set(linear, complex5, 4);
    a_linear_set(linear, complex6, 5);

    // 输出数据
    printf("初始化的数据：");
    a_linear_print(linear, operate_complex_print, "\n");

    // 获取指定下标的数据
    AComplex get_complex = a_linear_get(linear, 0, AComplex);
    printf("a_linear_get(linear, 0, AComplex)：");
    operate_complex_print(&get_complex);
    printf("\n");

    // 排序
    a_linear_sort(linear, operate_complex_sort);

    // 输出数据
    printf("排序后的数据：");
    a_linear_print(linear, operate_complex_print, "\n");

    // 删除指定下标的数据
    a_linear_del(linear, 0);

    // 输出数据
    printf("删除后的数据：");
    a_linear_print(linear, operate_complex_print, "\n");

    // 输出线性表的基本信息
    a_linear_print_info(linear);
    printf("a_linear_get_type  : %s\n", a_linear_get_type(linear));
    printf("a_linear_get_count : %zu\n", a_linear_get_count(linear));
    printf("a_linear_get_total : %zu\n", a_linear_get_total(linear));

    // 释放线性表内存
    a_linear_free(linear);
}
```