
@echo OFF

RMDIR /S /Q build\
MKDIR build\

cl /O0 /Zi /I lib /D IS_SERVER=0 src\windows.cpp /Febuild\game.exe user32.lib gdi32.lib ole32.lib lib\glew32s.lib lib\assimp-vc143-mtd.lib opengl32.lib  /link ws2_32.lib /incremental:no

if "%1" == "run"  start build\game.exe exit
