/*
 * @Author: chenkunlin chenkunlin@leedarson.com
 * @Date: 2024-05-20 11:06:36
 * @LastEditors: linwanyi linwanyi@leedarson.com
 * @LastEditTime: 2024-06-20 18:54:23
 * @FilePath: /chenkl/lighting_cbb/components/lds_simple/inc/lds_simple.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef COMPONENTS_LDS_POWER_ON_COUNT_H_
#define COMPONENTS_LDS_POWER_ON_COUNT_H_

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <stdlib.h>

//计数类型
#define POWER_ON_COUNT_TIMEOUT  0
#define POWER_ON_COUNT_SHORT    1
#define POWER_ON_COUNT_LONG     2   
#define POWER_ON_COUNT_SHORT_START  0
#define POWER_ON_COUNT_SHORT_END    2500
#define POWER_ON_COUNT_LONG_START   3000
#define POWER_ON_COUNT_LONG_END     4000
#define MAX_NUM 6

typedef enum{
    POWER_ON_COUNT_MATCH_SUCCESS = 0,  //匹配成功
    POWER_ON_COUNT_MATCH_FAIL
}match_status_e;

typedef enum{
    RESET,
    EXIT_FTM,
    MAX_TYPE
}power_on_count_type_e;

//
typedef struct
{
    unsigned char enable;
    unsigned char is_update;
}power_on_count_data_t;
//计数存储 使用字符串数组
typedef struct
{
    uint8_t index; //用于指示当前需要写入的位置 初始值为0
    char count_value[MAX_NUM];//记录每次上电的类型 无效: 0 短: 1 长:2
}power_on_count_data_save_t;

typedef struct 
{
    size_t length;
    char match_sequence[MAX_NUM];
}power_on_match_type_t;

void ldsPowerOnCountInitTest();
void ldsPowerOnCountMatch(power_on_count_data_save_t *count_data,unsigned char flag,uint8_t cur_index);
void ldsPowerOnCountUpdate(unsigned int cur_tick,power_on_count_data_save_t *count_data_save,uint8_t cur_index,power_on_count_data_t *count_data);
void ldsPowerOnCountClear(power_on_count_data_save_t *count_data);
#ifdef __cplusplus
}
#endif

#endif

