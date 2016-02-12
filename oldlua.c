#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define TEST_BUILD

struct my_state {
  unsigned int *next;
  unsigned char tt;
  unsigned char marked;
  unsigned int *top;  /* first free slot in the stack */
  unsigned int *base;  /* first free slot in the stack */
  unsigned int *l_G;
  unsigned int *ci;  /* call info for current function */
  unsigned int *stack_last;  /* last free slot in the stack */
  unsigned int *stack;  /* stack base */
};

static int cfunctest(lua_State* L) {

	//int n = 0; 

	//double num = lua_tonumber(L, 1);

	struct my_state* state = (struct my_state*) L;
	unsigned int *data = (unsigned int*) state->base;

	printf("%f\n", *((double*)(&data[2])));

	//int argc = lua_gettop(L);

	//printf("-- my_function() called with %d arguments:\n", argc);

	//for ( n=1; n<=argc; ++n ) {
	//	int val = atoi(lua_tostring(L, n));
	//	printf("-- argument %d: 0x%x\n", n, val);
	//}

	return 0;
}

int main()
{
	int status, result;

    //create a Lua state
    lua_State *L = lua_open();

	printf("Lua test application\n");

    luaopen_io(L); // provides io.*
    luaopen_base(L);
    luaopen_table(L);
    luaopen_string(L);
    luaopen_math(L);
    luaopen_loadlib(L);

	lua_register(L, "my_func", cfunctest);

	/* Load the file containing the script we are going to run */
    status = luaL_loadfile(L, "C:\\Lua\\lua-5.0.2\\test\\test\\script.lua");
    if (status != 0) {
        /* If something went wrong, error message is at the top of */
        /* the stack */
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
    }
	else {
		result = lua_pcall(L, 0, 0, 0); // Priming run?
		if (result != 0) printf("Doh!\n");

		lua_getglobal(L, "dlltest");
		result = lua_pcall(L, 0, 0, 0);
		if (result != 0) printf("Doh!\n");
		printf("dlltest returned\n");
	}

	lua_close(L);

	return 0;
}