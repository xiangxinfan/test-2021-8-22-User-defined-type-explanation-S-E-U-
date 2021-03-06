#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

//自定义类型（结构体 + 枚举 + 联合）

//本章重点
//结构体
       // 结构体类型的声明
       // 结构的自引用
       // 结构体变量的定义和初始化
       // 结构体内存对齐
       // 结构体传参
       // 结构体实现位段（位段的填充&可移植性）
//枚举 
       // 枚举类型的定义 
       // 枚举的优点
       // 枚举的使用
//联合
       // 联合类型的定义
       // 联合的特点
       // 联合大小的计算
 


//结构体

//结构体的声明
  //结构的基础知识
    //结构是一些值的集合，这些值称为成员变量/结构的每个成员可以是不同类型的变量

//struct Stu
//{
//    char name[20];//名字
//    char tele[20];//电话
//    char sex[10];//性别
//    int age;
//}s4,s5;
//struct Stu s3;
////这里的s3,s4,s5是全局变量
//int main()
//{
//    //创建的结构体变量
//    struct Stu s1;
//    struct Stu s2;//这里的s1,s2是局部变量
//    return 0;
//}

////上面的例子中，假如是下面这种样子：
//struct
//{
//    char name[20];//名字
//    char tele[20];//电话
//    char sex[10];//性别
//    int age;
//}x;
////这种就称为匿名结构体变量
////但最后的x是必不可少的
//上面的两个结构在声明的时候省略掉了结构体标签，也就是结构体名字（tag）

//那么：
//在上面的代码的基础上，p=&x;是合法的吗？

//警告：编译器会把上面的两个声明当成完全不同的两个类型。所以是非法的



//结构的自引用

//typedef struct Node//假如没有这一行的Node,就是错误的
//{
//    int data;//4个字节
//    struct Node* next;// 4/8
//}Node;
//int main()
//{
//    struct Node n1;
//    Node n2;//假如没有typedef，这里n2就会出现问题
//    //加上之后，上面这两种都是正确的
//
//    return 0;
//}


////结构体变量的定义和初始化
//struct T
//{
//    double weight;
//    short age;
//};
//struct S
//{
//    char c;
//    struct T st;//结构体嵌套
//    int a;
//    double d;
//    char arr[20];
//};
//int main()
//{
//    struct S s = { 'c',{55.6,30},100,3.14,"hello bit" };
//    //{55.6,30}是结构体嵌套
//    printf("%c %d %lf %s\n", s.c, s.a, s.d, s.arr);
//    printf("%lf\n", s.st.weight );
//    return 0;
//}


//结构体内存对齐
//这是一个深入谈论的一个问题：计算结构体大小。
//这也是一个特别热门的考点：结构体内存对齐

//struct S1
//{
//    char c1;
//    int a;
//    char c2;
//};
//struct S2
//{
//    char c1;
//    char c2;
//    int a;
//};
//int main()
//{
//    struct S1 s1 = { 0 };
//    printf("%d\n", sizeof(s1));//8
//    struct S2 s2 = { 0 };
//    printf("%d\n", sizeof(s2));//12
//    return 0;
//}

//计算规则：
//1、第一个成员在与结构体变量偏移量为0的地址处
//2、其他成员变量要对齐到某个数字（对齐数）的整数倍的地址处

//对齐数 == 编译器默认的一个对齐数 与 该成员大小的较小值
//VS编译器中的默认值为8

//3、结构体总大小为最大对齐数（每个成员变量都有一个对齐数）的整数倍
//4、如果嵌套了结构体的情况，嵌套的结构体对齐到自己的最大对齐数的整数倍处，结构体的整体大小
//就是所有最大对齐数（含嵌套结构体的对齐数）的整数倍.

//struct S1
//{
//    char c1;
//    //这个char位于偏移量为0的地方，就拿数组看，这个在位置为0下面的内存中
//    int a;//这个对齐数为4，但是编译器是8，所以4和8之间的最小对齐数
//    //所以char和int之间的就有3的字节的内存被浪费了
//    char c2;//这个对齐数是1，编译器是8，最小的就是1，所以在8的下面，9处内存
//    //又因为结构体总大小为最大对齐数（每个成员变量都有一个对齐数）的整数倍
//    //这对大的对齐数是int，为4
//    //所以9下面的3个又被浪费，
//    //所以这个结构体内存为12
//};
//
//int main()
//{
//    struct S1 s1 = { 0 };
//    printf("%d\n", sizeof(s1));//12
//    return 0;
//}

//
//struct S2
//{
//    char c1;
//    //这里对齐数是1，所以就放在0下面的内存中
//    char c2;//这里的对齐数是1，编译器对齐数是8，最小为1
//    //所以这里放在1的下面的位置上
//    int a;////这里的对齐数是4，编译器对齐数是8，最小为4
//    //就放在4的位置处，中间的2，3内存都是被浪费的
//    //加起来就是8 = 1+1+2+4，8正好是上面三个元素的最大对齐数的倍数，
//    //所以这个结构体的内存就是8
//
//};
//int main()
//{
//    struct S2 s2 = { 0 };
//    printf("%d\n", sizeof(s2));//8
//    return 0;
//}

////练习
//struct S3
//{
//    double d;
//    //这个对齐数是8，放在0下面的位置
//    char c;//这对齐数是1，VS是8，所以选择1，
//    //这个就放在了8下面的位置上了
//    int i;//这的对齐数是4，VS是8，所以选择4
//    //但是上面的位置是9，不是4的倍数，所以中间会浪费几个空间
//    //在12下面放int的内存，放4个，就是对齐数为16
//    //double char int 中的对齐数最大是8，16又是8的倍数，所以这个结构体内存就是16
//};
//printf("%d\n", sizeof(struct S3));


//struct S4
//{
//    char C1;//这个对齐数是1，所以在0的下面的位置上放1个
//    
//    struct S3 s3;//这个是一个嵌套结构体，这个结构体的对齐数是16，VS对齐数是8，所以选择8
//    //所以在8的位置下面放结构体的内存，放16个
//    
//    //1+7+16=24
//    double i;//这的对齐数是8，VS是8，所以选择8
//    //24是8的倍数，所以在24下面直接放即可
//    
//    //24+8=32，32是上面三个元素中最大对齐数的倍数，
//    //所以这个结构体所占的内存为32
//};
//printf("%d\n", sizeof(struct S4));



//为什么存在内存对齐？

//大部分的参考资料都这样说：
//1、平台原因（移植原因）：
//不是所有的硬件平台都能访问任意地址上的任意数据的；某些硬件平台
//只能在某些地址处取某些特定类型的数据，否则抛出硬件异常。
//2、性能原因：
//数据结构（尤其是栈）应该尽可能地在自然边界上对齐。原因在于：为了访问未对齐的内存，处理器
//需要作两次内存访问；而对齐的内存访问仅需要一次访问

//总体来说：
//结构体的内存对齐是拿空间来换取时间的做法

//那在设计结构体的时候，我们既要满足对齐，又要节省空间，如何做到让空间减到最小：  
//让占用空间小的成员尽量集中在一起。




//修改默认对齐数
//#pragma 这个预处理指令，我们可以改变默认对齐数


////设置默认对齐数为4
//#pragma pack(4)
//struct S
//{
//    char C1;// 1
//    // 7 
//    double d;
//};
////取消设置的默认对齐数
//int main()
//{
//    struct S s;
//    printf("%d\n", sizeof(s));
//    return 0;
//}


//结论：
//结构在对齐方向不合适的时候，我们可以自己更改默认对齐数



//offsetof (Retrieves the offset of a member from the beginning of its parent structure.)
//检测各成员的偏移量

//size_t offsetof( structName, memberName );

//这是一个宏，后面会学到

//#include <stddef.h>
//struct S
//{
//    char c;
//    int i;
//    double d;
//};
//int main()
//{
//    printf("%d\n", offsetof(struct S, c));
//    printf("%d\n", offsetof(struct S, i));
//    printf("%d\n", offsetof(struct S, d));
//    return 0;
//}



//结构体传参

//直接上代码：

//struct S
//{
//    int a;
//    char c;
//    double d;
//};
//void Init(struct S tmp)
//{
//    tmp.a = 100;
//    tmp.c = 'w';
//    tmp.d = 3.14159;
//}
//int main()
//{
//    struct S s = { 0 };
//    //Init(s);//这里不能用s，要用取地址s
//    //因此就是下面的代码出现：
//
//    /*s.a = 100;
//    s.c = 'w';
//    s.d = 3.14159;
//    printf("%d\n", s.a);*/
//    return 0;
//}



//struct S
//{
//    int a;
//    char c;
//    double d;
//};
//void Init(struct S* ps)
//{
//    ps->a = 100;
//    ps->c = 'w';
//    ps->d = 3.14159;
//}
////这里传的是数值
//void Print1(struct S tmp)
//{
//    printf("%d %c %lf\n", tmp.a, tmp.c, tmp.d);
//}
////这里传的是地址
//void Print2(struct S* ps)//在这里，前面加个const会更好，这样就会避免ps中的值被改变
//{
//    printf("%d %c %lf\n", ps->a, ps->c, ps->d);
//}
//int main()
//{
//    struct S s = { 0 };
//    Init(&s);//这里函数内部要保留函数外部的数据，就一定要传地址，这样才能找到变量的数值
//    //打印一下：
//    Print1(s);
//    //或者这样打印：
//    Print2(&s);
//    return 0;
//}

//上面这两种，传值中，若s的值过大，所占内存空间过大，就会导致系统开销过大，系统就会反应过慢

//上面的Print1好还是Print2好？
//肯定是Print2好，因为
//函数传参的时候，参数是需要压栈的，会有时间和空间上的系统开销
//如果传递一个结构体对象的是时候，结构体过大，参数压栈的系统开销比较大，所以会导致性能的下降

//结论：结构体传参的时候，要传结构体的地址



//补充一下，当结构体变量是一般的时候，用 .
//          当结构体变量是指针的时候，用 ->


//位段

//什么是位段
//位段的声明和结构是类型的，有两个不同：
//1、位段的成员必须是int 、unsigned int 或signed int 
//2、位段的成员名后要有一个冒号和一个数字



//位段的内存分配

//1、位段的成员是int unsigned， int signed ，int 或char（属于整型家族）类型
//2、位段的空间上是按照需要以4个字节（int）或者1个字节（char）的方式来开辟的
//3、位段涉及很多不确定因素，位段是不跨平台的，注重可移植的程序应该避免使用位段

//冒号后面的表示比特（bit），不是数值或其他
//例如：
//struct S
//{
//    int a : 2;
//    int b : 5;
//    int c : 10;
//    int d : 30;
//};
////这里是int 4个字节，也就是32个比特位，2+5+10=17个比特位，剩下的15个比特位放不下30个比特位
////所以要开辟一段新的字节空间，来放下剩下的30个字节
////第一个剩下的15个比特位和第二个剩下的2个比特位都将被浪费
////而两个int类型的空间，就需要8个字节的空间，所以打印出来的就是8
////int 类型的位段，冒号后面的数值不能超过32，因为4个字节，32个比特位
//int main()
//{
//    struct S s;
//    printf("%d\n", sizeof(s));//这打印出来的是8，这里的8代表的是单位字节
//    return 0;
//}

//位段的作用   就是    用来节省字节空间的
//不然上面的代码就会出现 int a,int b,int c,int d各开辟一个空间，比较浪费空间内存
//char的话就是8个比特位

//下面的代码就关于是内存中的问题：

//struct S
//{
//    char a : 3;
//    char b : 4;
//    char c : 5;
//    char d : 4;
//};
//int main()
//{
//    struct S s = { 0 };
//    //这里的数值都需进行二进制码转换
//    s.a = 10;
//    //1010  //对应上面结构体中的比特位数，上面比特位只有3个，所以只能取010放在一个char字节中
//    s.b = 20;
//    //10100 //对应上面4个比特位，所以可以放下0100，而8个比特位中只占了3个，还有5个，所以还能
//    //放下这4个比特位   
//    //所以这8个比特位就成为  0 0 1 0 0 0 1 0 
//    s.c = 3;
//    //11   //对应上面5个比特位，但这只有2个，所以在前面要补3个0称为00011，放在一个新开辟的空间中
//    //就是这样的 0 0 0 0 0 0 1 1
//    s.d = 4;
//    //100   //上面剩下的又放不下这里的4个比特位，所以要开辟一段新的空间
//    //这里对应上面4个比特位，二进制码补成0 1 0 0
//    //就是这样的 0 0 0 0 0 1 0 0
//    return 0;
//}
//因此上面的就是3*8=24个比特位的，为：
// 0 0 1 0 0 0 1 0 0 0 0 0 0 0 1 1 0 0 0 0 0 1 0 0
//这就是放在内存中的码，但内存放的是十六进制码，所以4个4个为一位，改成是十六进制码
// 0 0 1 0 - 2，0 0 1 0 - 2， 0 0 0 0 - 0，0 0 1 1 - 3，0 0 0 0 - 0 ， 0 1 0 0 - 4

//所以内存就会出现 22 03 04，


//在课件中会有这个图



//位段的跨平台问题
//1、int 位段被当成有符号数还是无符号数是不确定的
//2、位段中最大位的数目不能确定（16位机器最大16，32位机器最大32，写成27，16位机器就会出现问题）
//3、位段中的成员在内存中从左向右分配，还是从右向左分配的标准尚未定义
//4、当一个结构包含两个位段，第二个位段成员比较大，无法容纳于第一个位段剩余的位时，是舍弃
//还是利用，这是不确定的

//总结：
//跟结构相比，位段可以达到同样的效果，但是可以很好的节省空间，但是有跨平台的问题存在

//位段的应用

//在课间中是有图的




//枚举

//枚举顾名思义就是 一一列举
//把可能的取值一一列举

//枚举类型的定义

    //枚举类型
//enum Sex
//{
//    //枚举的可能取值 - 枚举常量
//    MALE,
//    FEMALE,
//    SECRET
//};
//enum Color
//{
//    RED = 2,
//    YELLOW = 4,
//    BLUE = 8
//};
////上面枚举常量的值都别对应0，1，2
////下一个是上一个+1得到的
////也可以进行赋值，例如第二个
//int main()
//{
//    
//    enum Sex s = MALE;
//    enum Color c = BLUE;
//
//    //enum Color c = 2;//如果是这种，则是编译不出来的，因为左右两边的类型不同，右边是int类型的
//    //左边是enum Color类型的
//    //这里不会报错，但是编译出来没数字
//    //这里C++就会报错
//    printf("%d %d %d \n", RED, YELLOW, BLUE);
//    printf("%d %d %d \n", MALE, FEMALE, SECRET);
//    return 0;
//}




//上面定义的enum Day,enum Sex,enum Color都是枚举类型，{}中的内容是枚举类型的可能取值
//也叫枚举常量
//这些可能取值都是有值的，默认从0开始，一次递增1，当然在定义的时候也可以赋初值


//也可以用下来这个来表示：
// 
// //C语言的源代码 --> 可执行程序
//#define RED 0
//#define YELLOW 0
//#define BLUE 0
//int main()
//{
//    int Color = RED;//这里RED全部会被改成0，程序编译中编译的不是RED，而是0 
// //在优点中的4，便于调试
//    return 0;
//}

//但为什么不会用上面的这个，而会用枚举呢？
//因为枚举的优点：
//我们可以使用#define定义常量，
//1、增加代码的可读性和可维护性
//2、和#define定义的标识符比较枚举有类型检查，更加严谨。
//3、防止了命名污染（封装）
//4、便于调试
//5、使用方便，一次可以定义多个变量


//C语言的源代码 --> 预编译（预处理） --> 编译 --> 链接 --> 可执行程序


//联合（共用体）
//联合类型的定义
//联合也是一种特殊的自定义类型这种类型定义的变量也包含一系列的成员，特征是这些成员公用同一块
//空间（所以联合也叫联合共用体）。比如：

//union Un
//{
//    char c;
//    int i;
//};
//int main()
//{
//    union Un u;
//    printf("%d\n", sizeof(u));//打印出来是4
//    //原因是char c是1个字节，int i 是4个字节
//    //char 放在了一个字节的第一个比特位上
//    //int 还是放在了这个同样的字节上，放了4个比特位
//    //再看地址
//    printf("%p\n", &u);
//    printf("%p\n", &(u.c ));
//    printf("%p\n", &(u.i ));
//    //地址是相同的，所以首元素地址是相同的
//    //所以char c和int i是公用同一块空间
//
//    return 0;
//}


//union Un
//{
//    char c;
//    int i;
//};
//int main()
//{
//    //联合变量的定义
//    union Un un;
//    //计算连个变量的大小
//    printf("%d\n", sizeof(un));
//    return 0;
//}


//联合的特点

//联合的成员是共用同一块内存空间的，这样一个联合变量的大小，至少是最大成员的大小（因为
//联合至少得有能力保存最大的那个成员）

//这个有缺点：就是在同一时刻，i和c不能同时使用，若同时使用，则改c就会把i改了
//改i就会把c改了




//复习一下大小端存储

//int a = 0x11223344;//这是从高字节到低字节

//大端存储是：
//将高字节存储在低地址处，低字节存储在高地址处
//小端存储是：
//高字节存储在高地址处，低字节存储在低地址处


//int check_sys()
//{
//    int a = 1;
//    //返回1，表示小端
//    //返回0，表示大端
//    return *(char*)&a;
//}

//int check_sys()
//{
//    union Un//可以将Un删除掉，这就成为匿名结构体，是可以的，但必须要有后面的u
//    {
//        char c;
//        int i;
//    }u;
//    u.i = 1;
//    //返回1，表示小端
//    //返回0，表示大端
//    return u.c;
//    //用结构体来检验大小端
//}
//int main()
//{
//
//    int a = 1;
//    check_sys();//进行封装一些函数
//    if (1 == *(char*)&a)
//    {
//        printf("小端\n");
//    }
//    else
//    {
//        printf("小端\n");
//    }
//    return 0;
//}


//共用体和结构体仅在内存存储不一样，这是对的
//这是地址相同，但是值不一定相同

//计算enum的值：
//enum Sex
//{
//    MALE,
//    FEMALE,
//    SECRET
//};
//int main()
//{
//    enum Sex s = MALE;
//    printf("%d\n", sizeof(s));
//    return 0;
//}


//联合大小的计算

//联合的大小至少是最大成员的大小。
//当最大成员大小不是最大对齐数的整数倍的时候，就要对齐到最大对齐数的整数倍
//例如：

//union Un
//{
//    int a;//这个的字节数是4，编译器默认为8，取最小的为4
//    char arr[5];//这个字节数为5，char类型是1，默认为8，取最小为1
//};
//int main()
//{
//    union Un u;
//    printf("%d\n", sizeof(u));//上面先放4，再放1，加起来是8，不是4的倍数，
//    //所以会浪费3个字节的空间，就成了8
//    return 0;
//}