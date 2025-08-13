
if not exist obj mkdir obj

objcopy -I binary -O pe-x86-64 -B i386:x86-64 waving-person.png waving-person.o

cl.exe /DEBUG:FULL /Zi ^
/I "include" ^
/Fe:build\app_objcopy.exe ^
/Fo.\obj\ ^
app_objcopy_embedded_resource.c ^
lib\SDL3.lib ^
waving-person.o ^
