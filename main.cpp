/**
 * @Author: 软件19-2 高瑞泽 1914010205
 * @Date: 2021-04-25
 */
#include <cstdio>
#include <cstdlib>

/* 声明调用c的函数库 */
#ifdef __cplusplus
extern "C"
{
#endif
#include <winsock2.h>
#include "cJSON.h"
#include "utf8togbk.h"
#ifdef __cplusplus
}
#endif

using namespace std;

/* 心知天气IP */
#define WEATHER_IP_ADDR "116.62.93.248"

/* 心知天气端口 */
#define WEATHER_PORT 80

/* 心知天气密钥 */
#define KEY "SV9IRl3DkDBUyCsZF"

/* GET请求包 */
#define GET_REQUEST_PACKAGE "GET https://api.seniverse.com/v3/weather/%s.json?key=%s&location=%s&language=zh-Hans&unit=c\r\n\r\n"

/* JSON数据包 */
#define NOW_JSON "now"
#define DAILY_JSON "daily"

/* 天气数据结构体 */
typedef struct
{
    /* 实时的天气数据 */
    char id[35];                //id
    char name[35];                //地名
    char country[35];            //国家
    char path[35];                //完整地名路径
    char timezone[35];            //时区
    char timezone_offset[35];   //时差
    char text[35];                //天气预报文字
    char code[35];                //天气预报代码
    char temperature[35];    //气温
    char last_update[35];        //最后一次更新时间

    /* 今天、明天、后天天气数据 */
    char date[3][35];            //日期
    char text_day[3][70];        //白天天气现象文字
    char code_day[3][35];        //白天天气现象代码
    char code_night[3][70];    //晚间天气现象代码
    char high[3][35];            //最高温
    char low[3][35];            //最低温
    char wind_direction[3][70]; //风向
    char wind_speed[3][35];    //风速，单位km/h（当unit=c时）
    char wind_scale[3][35];    //风力等级
} Weather;

/* cmd窗口设置 */
struct cmd_windows_config
{
    int width;
    int high;
    int color;
};

/* cmd窗口默认配置 */
struct cmd_windows_config cmd_default_config = {60, 40, 0xf0};

// 函数声明
static void GetWeather(char *weather_json, char *location, Weather *result);

static int cJSON_NowWeatherParse(char *JSON, Weather *result);

static int cJSON_DailyWeatherParse(char *JSON, Weather *result);

static void DisplayWeather(Weather *weather_data);

static void cmd_window_set(struct cmd_windows_config *config);

static void printf_topic();

/**
 * @fuction: main
 * @Parameter: void
 * @return: void
 */
int main()
{
    Weather weather_data = {0};
    char location[35] = {0};
    cmd_window_set(&cmd_default_config);
    printf_topic();

    while ((1 == scanf("%s", location))) // 读入地名拼音
    {
        system("cls");    // 清屏
        memset(&weather_data, 0, sizeof(weather_data));  // weather_data清零
        GetWeather(NOW_JSON, location, &weather_data);   // GET 并解析实况天气数据
        GetWeather(DAILY_JSON, location, &weather_data); // GET 并解析近三天天气数据
        DisplayWeather(&weather_data);                     // 显示天气结果
        printf("\n请输入要查询天气的城市名称的拼音（如：beijing）：");
    }

    return 0;
}

/**
 * @fuction: GetWeather 获取天气数据并解析
 * @Parameter: weather_json：需要解析的json包   location：地名   result：数据解析的结果
 * @return: void
 */
static void GetWeather(char *weather_json, char *location, Weather *result)
{
    SOCKET ClientSock;
    WSADATA wd;
    char GetRequestBuf[256] = {0};
    char WeatherRecvBuf[2 * 1024] = {0};
    char GbkRecvBuf[2 * 1024] = {0};
    int gbk_recv_len = 0;
    int connect_status = 0;

    /* 初始化操作sock需要的DLL */
    WSAStartup(MAKEWORD(2, 2), &wd);

    /* 设置要访问的服务器的信息 */
    SOCKADDR_IN ServerSockAddr;
    memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));          // 每个字节都用0填充
    ServerSockAddr.sin_family = PF_INET;                          // IPv4
    ServerSockAddr.sin_addr.s_addr = inet_addr(WEATHER_IP_ADDR);  // 心知天气服务器IP
    ServerSockAddr.sin_port = htons(WEATHER_PORT);              // 端口

    /* 创建客户端socket */
    if (-1 == (ClientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)))
    {
        printf("socket error!\n");
        exit(1);
    }

    /* 连接服务端 */
    if (-1 == (connect_status = connect(ClientSock, (SOCKADDR *) &ServerSockAddr, sizeof(SOCKADDR))))
    {
        printf("connect error!\n");
        exit(1);
    }

    /* 组合GET请求包 */
    sprintf(GetRequestBuf, GET_REQUEST_PACKAGE, weather_json, KEY, location);

    /* 发送数据到服务端 */
    send(ClientSock, GetRequestBuf, strlen(GetRequestBuf), 0);

    /* 接受服务端的返回数据 */
    recv(ClientSock, WeatherRecvBuf, 2 * 1024, 0);

    /* utf-8转为gbk */
    SwitchToGbk((const unsigned char *) WeatherRecvBuf, strlen((const char *) WeatherRecvBuf),
                (unsigned char *) GbkRecvBuf, &gbk_recv_len);

    /* 解析天气数据并保存到结构体变量weather_data中 */
    if (0 == strcmp(weather_json, NOW_JSON))        // 天气实况
    {
        cJSON_NowWeatherParse(GbkRecvBuf, result);
    } else if (0 == strcmp(weather_json, DAILY_JSON)) // 未来三天天气
    {
        cJSON_DailyWeatherParse(GbkRecvBuf, result);
    }

    /* 清空缓冲区 */
    memset(GetRequestBuf, 0, 256);
    memset(WeatherRecvBuf, 0, 2 * 1024);
    memset(GbkRecvBuf, 0, 2 * 1024);

    /* 关闭套接字 */
    closesocket(ClientSock);

    /* 终止使用 DLL */
    WSACleanup();
}

/**
 * @fuction: cJSON_NowWeatherParse 解析天气实况数据
 * @Parameter: JSON：天气数据包   result：数据解析的结果
 * @return: void
 */
static int cJSON_NowWeatherParse(char *JSON, Weather *result)
{
    cJSON *json, *arrayItem, *object, *subobject, *item;

    json = cJSON_Parse(JSON); //解析JSON数据包
    if (json == NULL)          //检测JSON数据包是否存在语法上的错误，返回NULL表示数据包无效
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr()); //打印数据包语法错误的位置
        return 1;
    } else
    {
        if ((arrayItem = cJSON_GetObjectItem(json, "results")) != NULL); //匹配字符串"results",获取数组内容
        {
            int size = cJSON_GetArraySize(arrayItem);     //获取数组中对象个数
            if ((object = cJSON_GetArrayItem(arrayItem, 0)) != NULL)//获取父对象内容
            {
                /* 匹配子对象1：城市地区相关 */
                if ((subobject = cJSON_GetObjectItem(object, "location")) != NULL)
                {
                    // 匹配id
                    if ((item = cJSON_GetObjectItem(subobject, "id")) != NULL)
                    {
                        memcpy(result->id, item->valuestring, strlen(item->valuestring));        // 保存数据供外部调用
                    }
                    // 匹配城市名
                    if ((item = cJSON_GetObjectItem(subobject, "name")) != NULL)
                    {
                        memcpy(result->name, item->valuestring, strlen(item->valuestring));        // 保存数据供外部调用
                    }
                    // 匹配城市所在的国家
                    if ((item = cJSON_GetObjectItem(subobject, "country")) != NULL)
                    {
                        memcpy(result->country, item->valuestring, strlen(item->valuestring));    // 保存数据供外部调用
                    }
                    // 匹配完整地名路径
                    if ((item = cJSON_GetObjectItem(subobject, "path")) != NULL)
                    {
                        memcpy(result->path, item->valuestring, strlen(item->valuestring));        // 保存数据供外部调用
                    }
                    // 匹配时区
                    if ((item = cJSON_GetObjectItem(subobject, "timezone")) != NULL)
                    {
                        memcpy(result->timezone, item->valuestring, strlen(item->valuestring));    // 保存数据供外部调用
                    }
                    // 匹配时差
                    if ((item = cJSON_GetObjectItem(subobject, "timezone_offset")) != NULL)
                    {
                        memcpy(result->timezone_offset, item->valuestring, strlen(item->valuestring));    // 保存数据供外部调用
                    }
                }
                /* 匹配子对象2：今天的天气情况 */
                if ((subobject = cJSON_GetObjectItem(object, "now")) != NULL)
                {
                    // 匹配天气现象文字
                    if ((item = cJSON_GetObjectItem(subobject, "text")) != NULL)
                    {
                        memcpy(result->text, item->valuestring, strlen(item->valuestring));  // 保存数据供外部调用
                    }
                    // 匹配天气现象代码
                    if ((item = cJSON_GetObjectItem(subobject, "code")) != NULL)
                    {
                        memcpy(result->code, item->valuestring, strlen(item->valuestring));  // 保存数据供外部调用
                    }
                    // 匹配气温
                    if ((item = cJSON_GetObjectItem(subobject, "temperature")) != NULL)
                    {
                        memcpy(result->temperature, item->valuestring, strlen(item->valuestring));   // 保存数据供外部调用
                    }
                }
                /* 匹配子对象3：数据更新时间（该城市的本地时间） */
                if ((subobject = cJSON_GetObjectItem(object, "last_update")) != NULL)
                {
                    memcpy(result->last_update, subobject->valuestring, strlen(subobject->valuestring));   // 保存数据供外部调用
                }
            }
        }
    }

    cJSON_Delete(json); //释放cJSON_Parse()分配出来的内存空间

    return 0;
}

/**
 * @fuction: cJSON_DailyWeatherParse，解析近三天天气数据
 * @Parameter: JSON：天气数据包   result：数据解析的结果
 * @return: void
 */
static int cJSON_DailyWeatherParse(char *JSON, Weather *result)
{
    cJSON *json, *arrayItem, *object, *subobject, *item, *sub_child_object, *child_Item;

    json = cJSON_Parse(JSON); //解析JSON数据包
    if (json == NULL)          //检测JSON数据包是否存在语法上的错误，返回NULL表示数据包无效
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr()); //打印数据包语法错误的位置
        return 1;
    } else
    {
        if ((arrayItem = cJSON_GetObjectItem(json, "results")) != NULL); //匹配字符串"results",获取数组内容
        {
            int size = cJSON_GetArraySize(arrayItem);     //获取数组中对象个数
            if ((object = cJSON_GetArrayItem(arrayItem, 0)) != NULL)//获取父对象内容
            {
                /* 匹配子对象1------结构体location */
                if ((subobject = cJSON_GetObjectItem(object, "location")) != NULL)
                {
                    if ((item = cJSON_GetObjectItem(subobject, "name")) != NULL) //匹配子对象1成员"name"
                    {
                        memcpy(result->name, item->valuestring, strlen(item->valuestring));        // 保存数据供外部调用
                    }
                }
                /* 匹配子对象2------数组daily */
                if ((subobject = cJSON_GetObjectItem(object, "daily")) != NULL)
                {
                    int sub_array_size = cJSON_GetArraySize(subobject);
                    for (int i = 0; i < sub_array_size; i++)
                    {
                        if ((sub_child_object = cJSON_GetArrayItem(subobject, i)) != NULL)
                        {
                            // 匹配日期
                            if ((child_Item = cJSON_GetObjectItem(sub_child_object, "date")) != NULL)
                            {
                                memcpy(result->date[i], child_Item->valuestring,
                                       strlen(child_Item->valuestring));        // 保存数据
                            }
                            // 匹配白天天气现象文字
                            if ((child_Item = cJSON_GetObjectItem(sub_child_object, "text_day")) != NULL)
                            {
                                memcpy(result->text_day[i], child_Item->valuestring,
                                       strlen(child_Item->valuestring));    // 保存数据
                            }
                            // 匹配白天天气现象代码
                            if ((child_Item = cJSON_GetObjectItem(sub_child_object, "code_day")) != NULL)
                            {
                                memcpy(result->code_day[i], child_Item->valuestring,
                                       strlen(child_Item->valuestring));    // 保存数据
                            }
                            // 匹配夜间天气现象代码
                            if ((child_Item = cJSON_GetObjectItem(sub_child_object, "code_night")) != NULL)
                            {
                                memcpy(result->code_night[i], child_Item->valuestring,
                                       strlen(child_Item->valuestring)); // 保存数据
                            }
                            // 匹配最高温度
                            if ((child_Item = cJSON_GetObjectItem(sub_child_object, "high")) != NULL)
                            {
                                memcpy(result->high[i], child_Item->valuestring,
                                       strlen(child_Item->valuestring));        //保存数据
                            }
                            // 匹配最低温度
                            if ((child_Item = cJSON_GetObjectItem(sub_child_object, "low")) != NULL)
                            {
                                memcpy(result->low[i], child_Item->valuestring,
                                       strlen(child_Item->valuestring));        // 保存数据
                            }
                            // 匹配风向
                            if ((child_Item = cJSON_GetObjectItem(sub_child_object, "wind_direction")) != NULL)
                            {
                                memcpy(result->wind_direction[i], child_Item->valuestring,
                                       strlen(child_Item->valuestring)); //保存数据
                            }
                            // 匹配风速，单位km/h（当unit=c时）
                            if ((child_Item = cJSON_GetObjectItem(sub_child_object, "wind_speed")) != NULL)
                            {
                                memcpy(result->wind_speed[i], child_Item->valuestring,
                                       strlen(child_Item->valuestring)); // 保存数据
                            }
                            // 匹配风力等级
                            if ((child_Item = cJSON_GetObjectItem(sub_child_object, "wind_scale")) != NULL)
                            {
                                memcpy(result->wind_scale[i], child_Item->valuestring,
                                       strlen(child_Item->valuestring)); // 保存数据
                            }
                        }
                    }
                }
                /* 匹配子对象3------最后一次更新的时间 */
                if ((subobject = cJSON_GetObjectItem(object, "last_update")) != NULL)
                {
                    //printf("%s:%s\n",subobject->string,subobject->valuestring);
                }
            }
        }
    }

    cJSON_Delete(json); //释放cJSON_Parse()分配出来的内存空间

    return 0;
}

/**
 * @fuction: DisplayWeather 显示天气数据
 * @Parameter: weather_data：天气数据
 * @return: void
 */
static void DisplayWeather(Weather *weather_data)
{
    printf("===========%s此时的天气情况如下===========\n", weather_data->name);
    printf("天气：%s\n", weather_data->text);
    printf("气温：%s℃\n", weather_data->temperature);
    printf("时区：%s\n", weather_data->timezone);
    printf("时差：%s\n", weather_data->timezone_offset);
    printf("天气更新时间：%s\n", weather_data->last_update);
    printf("===========%s近三天的天气情况如下===========\n", weather_data->name);
    printf("【%s】\n", weather_data->date[0]);
    printf("天气：%s\n", weather_data->text_day[0]);
    printf("最高温：%s℃\n", weather_data->high[0]);
    printf("最低温：%s℃\n", weather_data->low[0]);
    printf("风向：%s\n", weather_data->wind_direction[0]);
    printf("风速：%skm/h\n", weather_data->wind_speed[0]);
    printf("风力等级：%s\n", weather_data->wind_scale[0]);
    printf("\n");
    printf("【%s】\n", weather_data->date[1]);
    printf("天气：%s\n", weather_data->text_day[1]);
    printf("最高温：%s℃\n", weather_data->high[1]);
    printf("最低温：%s℃\n", weather_data->low[1]);
    printf("风向：%s\n", weather_data->wind_direction[1]);
    printf("风速：%skm/h\n", weather_data->wind_speed[1]);
    printf("风力等级：%s\n", weather_data->wind_scale[1]);
    printf("\n");
    printf("【%s】\n", weather_data->date[2]);
    printf("天气：%s\n", weather_data->text_day[2]);
    printf("最高温：%s℃\n", weather_data->high[2]);
    printf("最低温：%s℃\n", weather_data->low[2]);
    printf("风向：%s\n", weather_data->wind_direction[2]);
    printf("风速：%skm/h\n", weather_data->wind_speed[2]);
    printf("风力等级：%s\n", weather_data->wind_scale[2]);
}

/**
 * @fuction: cmd_window_set 设置cmd窗口
 * @Parameter: weather_data：天气数据
 * @return: void
 */
static void cmd_window_set(struct cmd_windows_config *config)
{
    char cmd[50];
    sprintf((char *) cmd, "mode con cols=%d lines=%d", config->width, config->high);
    system(cmd);
    memset(cmd, 0, 50);
    sprintf((char *) cmd, "color %x", config->color);
    system(cmd);
    memset(cmd, 0, 50);
}

/**
 * @fuction:  printf_topic, 打印标题
 * @Parameter: void
 * @return: void
 */
static void printf_topic()
{
    system("date /T");    // 输出日期
    system("time /T");    // 输出时间

    printf("=================HTTP天气客户端==================\n");
    printf("请输入要查询天气的城市名称");
}