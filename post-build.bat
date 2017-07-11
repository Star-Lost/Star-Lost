@echo off
set configuration=%1
set platform=%2
set outputPath=%3
set sfmlBinPath=..\Third Party\%platform%\SFML-2.4.2\bin

if %configuration% == "Debug" (
	xcopy /d /y "%sfmlBinPath%\sfml-audio-d-2.dll" %outputPath%
	xcopy /d /y "%sfmlBinPath%\sfml-graphics-d-2.dll" %outputPath%
	xcopy /d /y "%sfmlBinPath%\sfml-network-d-2.dll" %outputPath%
	xcopy /d /y "%sfmlBinPath%\sfml-system-d-2.dll" %outputPath%
	xcopy /d /y "%sfmlBinPath%\sfml-window-d-2.dll" %outputPath%
) else (
	xcopy /d /y "%sfmlBinPath%\sfml-audio-2.dll" %outputPath%
	xcopy /d /y "%sfmlBinPath%\sfml-graphics-2.dll" %outputPath%
	xcopy /d /y "%sfmlBinPath%\sfml-network-2.dll" %outputPath%
	xcopy /d /y "%sfmlBinPath%\sfml-system-2.dll" %outputPath%
	xcopy /d /y "%sfmlBinPath%\sfml-window-2.dll" %outputPath%
)

xcopy /d /y "%sfmlBinPath%\openal32.dll" %outputPath%
exit 0