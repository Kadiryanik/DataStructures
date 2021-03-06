/*
 * Simple Logging Macros
 *
 * Copyright (C) Kadir Yanık - <kdrynkk@gmail.com>, 2019
 */
#ifndef LOG_H_
#define LOG_H_

/* Log Levels */
#define LOG_LEVEL_NONE         0 /* No log */
#define LOG_LEVEL_ERR          1 /* Errors */
#define LOG_LEVEL_WARN         2 /* Warnings */
#define LOG_LEVEL_INFO         3 /* Basic info */
#define LOG_LEVEL_DBG          4 /* Detailled debug */

/*------------------------------------------------------------------------------*/
#include "project-conf.h" // make sure the LOG_LEVELS defined

#include <stdio.h>
/*------------------------------------------------------------------------------*/
#ifndef PRINT_WITH_FUNC_LINE
#define PRINT_WITH_FUNC_LINE 0
#endif /* PRINT_WITH_FUNC_LINE */

#define LOG(with_level_str, level, level_str, ...) do {  \
                            if(level <= (LOG_LEVEL)) { \
                              if(with_level_str){ \
                                if(PRINT_WITH_FUNC_LINE){ \
                                  printf("%s[%s %d]: ", level_str, __FUNCTION__, __LINE__); \
                                } else{ \
                                  printf("%s", level_str); \
                                } \
                              } \
                              printf(__VA_ARGS__); \
                            } \
                          } while (0)

/*------------------------------------------------------------------------------*/
#define LOG_PRINT(...)          LOG(1, LOG_LEVEL_NONE, "PRI : ", __VA_ARGS__)
#define LOG_ERR(...)            LOG(1, LOG_LEVEL_ERR, "ERR : ", __VA_ARGS__)
#define LOG_WARN(...)           LOG(1, LOG_LEVEL_WARN, "WARN: ", __VA_ARGS__)
#define LOG_INFO(...)           LOG(1, LOG_LEVEL_INFO, "INFO: ", __VA_ARGS__)
#define LOG_DBG(...)            LOG(1, LOG_LEVEL_DBG, "DBG : ", __VA_ARGS__)

/*------------------------------------------------------------------------------*/
#define LOG_PRINT_(...)         LOG(0, LOG_LEVEL_NONE, "PRI : ", __VA_ARGS__)
#define LOG_ERR_(...)           LOG(0, LOG_LEVEL_ERR, "ERR : ", __VA_ARGS__)
#define LOG_WARN_(...)          LOG(0, LOG_LEVEL_WARN, "WARN: ", __VA_ARGS__)
#define LOG_INFO_(...)          LOG(0, LOG_LEVEL_INFO, "INFO: ", __VA_ARGS__)
#define LOG_DBG_(...)           LOG(0, LOG_LEVEL_DBG, "DBG : ", __VA_ARGS__)

#endif /* LOG_H_ */