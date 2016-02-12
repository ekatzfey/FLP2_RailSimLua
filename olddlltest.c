#include <stdio.h>
#include <stdlib.h>

#include <lua.h>

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

__declspec(dllexport) int init(lua_State *L) {

	INPUT ip;

	int i = 0;
	struct my_state *state = (struct my_state*) L;
	unsigned int *data = (unsigned int*) state->stack;
	int arg1idx = -1;
	unsigned int arg2 = 0x32;
	int arg3idx = -1;

	for (i = 0; i < 64; i++) {
		if (data[i] == 0x12344321) {
			arg1idx = i;
			arg2 = 0x34;
			break;
		}
	}

	if (arg1idx > 0) {
		for (i = 0; i < 64; i++) {
			if (data[i] == 0xdeadbeef) {
				arg3idx = i;
				arg2 = 0x36;
				break;
			}
		}
	}

	if ((arg1idx >= 0) &&
		(arg3idx >= 0) &&
		(arg3idx > arg1idx))
	{
		arg2 = data[arg1idx + ((arg3idx - arg1idx) / 2)];
	}

#ifdef TEST_BUILD
	printf("argument = 0x%x\n", arg2);
	printf("Size of pointer %d\n", (int) sizeof(int*));

	for (i = 0; i < 32; i++) printf("Stack word %d: 0x%x\n", i, data[i]);
#endif

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
 
    // Press the key
    ip.ki.wVk = arg2; // code for key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
 
	if (arg2 < 0x40) {
		// Release the key
		ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
		SendInput(1, &ip, sizeof(INPUT));
	}

#ifdef TEST_BUILD
    // Press the key
    ip.ki.wVk = 0x0d; // ascii code for enter key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
 
    // Release the key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
#endif

	return 0;
}
