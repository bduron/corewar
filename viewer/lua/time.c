// time.c

#include "lua.h"
#include "lauxlib.h"
#include <libc.h>

int new_table(lua_State *L)
{
	lua_newtable(L);
	lua_pushstring(L, "world");
	lua_setfield(L, -2, "hello");
	return (1);
}

int get_time(lua_State *L)
{
	lua_pushnumber(L, 32);
	return (1);
}

int luaopen_time(lua_State *L)
{
	luaL_Reg fns[] = {
		{"get_time", get_time},
		{"new_table", new_table},
		{NULL, NULL}
	};
	luaL_newlib(L, fns);
	return (1);
}
