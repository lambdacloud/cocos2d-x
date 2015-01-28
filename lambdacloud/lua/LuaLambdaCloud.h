#ifndef __LUALAMBDACLOUD_H_
#define __LUALAMBDACLOUD_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

TOLUA_API int tolua_LambdaCloud_open(lua_State* tolua_S);

#endif // __LUALAMBDACLOUD_H_