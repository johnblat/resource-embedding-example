
if not exist obj mkdir obj


cl.exe /DEBUG:FULL /Zi ^
/I "include" ^
/Fe:build\app_from_file.exe ^
/Fo.\obj\ ^
app_from_file.c ^
lib\SDL3.lib ^
