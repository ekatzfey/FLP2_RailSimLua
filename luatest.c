
#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define WINVER 0x0500
#include <windows.h>

static int cfunctest(lua_State* L) {

	INPUT ip;

	int num = lua_tointeger(L, 1);
	printf("Got %c from lua\n", (char) num);
 
    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
 
    // Press the key
    ip.ki.wVk = num; // ascii code for key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
 
    // Release the "A" key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));

	return 0;
}

int main(void)
{
	int status, result;

    //create a Lua state
    lua_State *L = luaL_newstate();

	printf("Lua test application\n");

    //load and execute a string
    if (luaL_dostring(L, "function foo (x,y) return x+y end")) {
        lua_close(L);
        return -1;
    }

    //push value of global "foo" (the function defined above)
    //to the stack, followed by integers 5 and 3
    lua_getglobal(L, "foo");
    lua_pushinteger(L, 5);
    lua_pushinteger(L, 3);
    lua_call(L, 2, 1); //call a function with two arguments and one return value
    printf("Result: %d\n", lua_tointeger(L, -1)); //print integer value of item at stack top

    lua_close(L); //close Lua state

	// Slightly more interesting test. Load a script and execute it.
	L = luaL_newstate();

    luaL_openlibs(L); /* Load Lua libraries */

	lua_pushcfunction(L, cfunctest);
    lua_setglobal(L, "mycfunc");

    /* Load the file containing the script we are going to run */
    status = luaL_loadfile(L, "C:\\Lua\\lua-5.3.2\\test\\script.lua");
    if (status != 0) {
        /* If something went wrong, error message is at the top of */
        /* the stack */
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
    }
	else {
		result = lua_pcall(L, 0, 0, 0); // Priming run?
		if (result != 0) printf("Doh!\n");

		lua_getglobal(L, "foo");
		result = lua_pcall(L, 0, 1, 0);
		if (result != 0) printf("Doh!\n");
		printf("foo returned %d\n", lua_tointeger(L, -1));

		lua_getglobal(L, "foobar");
		result = lua_pcall(L, 0, 0, 0);
		if (result != 0) printf("Doh!\n");
		printf("foobar returned\n");
		result = getchar();
		printf("Keyboard returned %c\n", (char) result);

		lua_getglobal(L, "dlltest");
		result = lua_pcall(L, 0, 0, 0);
		if (result != 0) printf("Doh!\n");
		printf("dlltest returned\n");
		result = getchar();
		result = getchar();
		printf("Keyboard returned %c\n", (char) result);
	}

	lua_close(L);

	return 0;
}