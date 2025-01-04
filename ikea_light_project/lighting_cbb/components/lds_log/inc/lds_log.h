/*
 * @Author: xiehuawei xiehuawei@leedarson.com
 * @Date: 2024-05-24 16:07:31
 * @LastEditors: xiehuawei xiehuawei@leedarson.com
 * @LastEditTime: 2024-06-20 19:27:18
 * @FilePath: /X_matter_zigbee_concurrent_lighting/esp-matter/examples/light/light_app/lds_log.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#ifndef _LDS_LOG_H_
#define _LDS_LOG_H_
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus


#define LDS_LOG_OFF      0
#define LDS_LOG_ERROR    1
#define LDS_LOG_WARNING  2
#define LDS_LOG_INFO     3
#define LDS_LOG_DEBUG    4

#ifndef LDS_LOG_LVL
#define LDS_LOG_LVL 	LDS_LOG_INFO
#endif

void LDS_LOG(int level, const char *format, ...);

#if (LDS_LOG_LVL >= LDS_LOG_DEBUG)
    #define LDS_LOG_D(...)       LDS_LOG(LDS_LOG_DEBUG, __VA_ARGS__)
#else
    #define LDS_LOG_D(...)       ((void)0)
#endif
#if (LDS_LOG_LVL >= LDS_LOG_INFO)
    #define LDS_LOG_I(...)       LDS_LOG(LDS_LOG_INFO, __VA_ARGS__)
#else
    #define LDS_LOG_I(...)       ((void)0)
#endif
#if (LDS_LOG_LVL >= LDS_LOG_WARNING)
    #define LDS_LOG_W(...)       LDS_LOG(LDS_LOG_WARNING, __VA_ARGS__)
#else
    #define LDS_LOG_W(...)       ((void)0)
#endif
#if (LDS_LOG_LVL >= LDS_LOG_ERROR)
    #define LDS_LOG_E(...)       LDS_LOG(LDS_LOG_ERROR, __VA_ARGS__)
#else
    #define LDS_LOG_E(...)       ((void)0)
#endif


#ifdef __cplusplus
}
#endif  // __cplusplus
#endif  // _LDS_LOG_H_

