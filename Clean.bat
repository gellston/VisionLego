setlocal



set CURPATH=%~dp0



pause

echo progressing deleting output directory...

rmdir %CURPATH%\VisionLego\.vs /S /Q
rmdir %CURPATH%\VisionLego\VisionLego\x64 /S /Q
rmdir %CURPATH%\VisionLego\Common\x64 /S /Q
rmdir %CURPATH%\VisionLego\PrimitiveNode\x64 /S /Q
rmdir %CURPATH%\VisionLego\x64 /S /Q


endlocal