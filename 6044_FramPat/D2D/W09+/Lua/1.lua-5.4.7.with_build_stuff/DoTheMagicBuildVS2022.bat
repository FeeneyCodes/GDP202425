cd src
cl /MD /O2 /c /DLUA_BUILD_AS_DLL *.c
ren lua.obj lua.o
ren luac.obj luac.o
link /DLL /IMPLIB:lua5.4.7.lib /OUT:lua5.4.7.dll *.obj 
link /OUT:lua.exe lua.o lua5.4.7.lib 
lib /OUT:lua5.4.7-static.lib *.obj
link /OUT:luac.exe luac.o lua5.4.7-static.lib
cd ..
mkdir bin
copy src\lua.exe bin/lua.exe /B
copy src\lua5.4.7.dll bin\lua5.4.7.dll /B
copy src\lua5.4.7.exp bin\lua5.4.7.exp /B
copy src\lua5.4.7.lib bin\lua5.4.7.lib /B
copy src\lua5.4.7-static.lib bin\lua5.4.7-static.lib /B
copy src\luac.exe bin\luac.exe /B
copy src\luac.lib bin\luac.lib /B
@echo All done.
pause
