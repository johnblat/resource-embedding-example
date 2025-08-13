
if not exist obj mkdir obj

rc /fo windows_embedded_resources.res windows_embedded_resources.rc

cl.exe /DEBUG:FULL /Zi ^
/I "include" ^
/Fe:build\app_windows_res.exe ^
/Fo.\obj\ ^
app_windows_res.c ^
lib\SDL3.lib ^
windows_embedded_resources.res ^
