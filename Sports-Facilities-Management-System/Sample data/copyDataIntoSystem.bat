@echo off
CHOICE /M "Copying the sample data into system will overwrite current data. Proceed "
IF %ERRORLEVEL% EQU 1 (
IF NOT EXIST %appdata%\SFMS mkdir %appdata%\SFMS 
copy booking.txt %appdata%\SFMS\
copy facility.dat %appdata%\SFMS\
copy facilityusage.txt %appdata%\SFMS\
copy staffNameList.bin %appdata%\SFMS\
copy userinfo.dat %appdata%\SFMS\
)
pause