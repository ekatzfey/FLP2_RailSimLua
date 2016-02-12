
CDLL.dll

This is the dll that is loaded by the lua script to send keystrokes to the game.

Sample_EngineScript.lua

This is the original lua script that has been modified to load the dll and initiate keystrokes. The DLL must be in C:\Temp for it to be found properly. Of course, you can modify the script to load it from some other location. The keypress function takes a value that represents the desired key and makes it appear to the game as if that key was pressed. The key values come from:

https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

You must use the value from that page and represent it in decimal, not hexidecimal. The example sends key code 52 (0x34) which represents the 4 key. In the game this causes the camera position to move outside of the cab. You can simply hit 1 again to go back into the cab.

Enjoy!
