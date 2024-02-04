
set /P yes=Do you want to clean all temporal files? (y/n)
IF %yes%==y (
IF EXIST "./.vs" (RD /S /Q "./.vs") ELSE (ECHO .VS already clean)
IF EXIST "./Binaries" (RD /S /Q "./Binaries") ELSE (ECHO BINARIES already clean)
IF EXIST "./Build" (RD /S /Q "./Build") ELSE (ECHO BUILD already clean)
REM uncomment this line to clear shaders as well
REM IF EXIST "./DerivedDataCache" (RD /S /Q "./DerivedDataCache") ELSE (ECHO DERIVEDDATACACHE already clean)
IF EXIST "./Intermediate" (RD /S /Q "./Intermediate") ELSE (ECHO INTERMEDIATE already clean)
IF EXIST "./Saved" (RD /S /Q "./Saved") ELSE (ECHO SAVED already clean)
del "%~dp0\*.sln"
)
