# FLP2_RailSimLua
Freelancer project #2: Creating lua code and library module to enable keystrokes

The actual dll is created from the file cdlltest.c. That is the end product.

The other files are for various tests that were run during the development process.

It should be noted that the dll is specific to Lua 5.0.2 which is what is built into
Rail Simulator 2016. The big problem is that Rail Simulator statically links in Lua and
does not bring in a DLL for it. That made things much more difficult since I couldn't
bring in the same DLL and use the Lua functions. Instead I had to reverse engineer
the Lua stack and build in explicit support for the Lua 5.0.2 stack to get access to the
arguments that we being sent in to my C code.

Enjoy!

