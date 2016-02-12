#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
//#include <lualib.h>
//#include <lauxlib.h>

#define WINVER 0x0500
#include <windows.h>

//__declspec(dllexport) int cfunctest_dll(lua_State* L) {
//
//	INPUT ip;
//
//	int num = lua_tointeger(L, 1);
//	printf("Got %c from lua in dll\n", (char) num);
// 
//    // Set up a generic keyboard event.
//    ip.type = INPUT_KEYBOARD;
//    ip.ki.wScan = 0; // hardware scan code for key
//    ip.ki.time = 0;
//    ip.ki.dwExtraInfo = 0;
// 
//    // Press the key
//    ip.ki.wVk = num; // ascii code for key
//    ip.ki.dwFlags = 0; // 0 for key press
//    SendInput(1, &ip, sizeof(INPUT));
// 
//    // Release the "A" key
//    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
//    SendInput(1, &ip, sizeof(INPUT));
//
//	return 0;
//}
//
//static const struct luaL_Reg mylib[] = {
//    {"cfunctest_dll", cfunctest_dll},
//    {NULL, NULL}  /* sentinel */
//};

//#define LUA_5_3_2

struct my_state {
  unsigned int *next;
  unsigned char tt;
  unsigned char marked;

#ifdef LUA_5_3_2
  unsigned short nci;  /* number of items in 'ci' list */
  unsigned char status;
#endif

  unsigned int *top;  /* first free slot in the stack */

#ifndef LUA_5_3_2
  unsigned int *base;  /* first free slot in the stack */
#endif 

  unsigned int *l_G;
  unsigned int *ci;  /* call info for current function */

#ifdef LUA_5_3_2
  const unsigned int *oldpc;  /* last pc traced */
#endif

  unsigned int *stack_last;  /* last free slot in the stack */
  unsigned int *stack;  /* stack base */
};

__declspec(dllexport) int init(lua_State *L) {

	INPUT ip;

	struct my_state *state = (struct my_state*) L;
	unsigned int *data = (unsigned int*) state->base;
	unsigned int arg1 = (unsigned int)(*((double*)(&data[2])));
	unsigned int arg2 = (unsigned int)(*((double*)(&data[6])));
	unsigned char shift = (arg2 & 0x01);
	unsigned char ctrl = (arg2 & 0x02);

#ifdef LUA_5_3_2
	printf("argument = 0x%x\n", arg2);
	printf("Size of pointer %d\n", (int) sizeof(int*));

	for (i = 0; i < 32; i++) printf("Stack word %d: 0x%x\n", i, data[i]);
#endif

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    ip.ki.dwFlags = 0; // 0 for key press down

	if (shift > 0)
	{
		ip.ki.wVk = 0x10; // code for shift key
		SendInput(1, &ip, sizeof(INPUT));
	}

	if (ctrl > 0)
	{
		ip.ki.wVk = 0x11; // code for Ctrl key
		SendInput(1, &ip, sizeof(INPUT));
	}

    // Press the key
    ip.ki.wVk = arg1; // code for key
    SendInput(1, &ip, sizeof(INPUT));
 
	// Release the key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	if (shift > 0)
	{
		ip.ki.wVk = 0x10; // code for shift key
		SendInput(1, &ip, sizeof(INPUT));
	}

	if (ctrl > 0)
	{
		ip.ki.wVk = 0x11; // code for Ctrl key
		SendInput(1, &ip, sizeof(INPUT));
	}

	return 0;
}
