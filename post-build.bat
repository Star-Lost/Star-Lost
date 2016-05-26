@echo off
set configuration=%1
set platform=%2
set outputPath=%3
set sfmlBinPath=..\Third Party\%platform%\SFML-2.3.2\bin

if %configuration% == "Debug" (
	xcopy /D "%sfmlBinPath%\sfml-audio-d-2.dll" %outputPath%
	xcopy /D "%sfmlBinPath%\sfml-graphics-d-2.dll" %outputPath%
	xcopy /D "%sfmlBinPath%\sfml-network-d-2.dll" %outputPath%
	xcopy /D "%sfmlBinPath%\sfml-system-d-2.dll" %outputPath%
	xcopy /D "%sfmlBinPath%\sfml-window-d-2.dll" %outputPath%
) else (
	xcopy /D "%sfmlBinPath%\sfml-audio-2.dll" %outputPath%
	xcopy /D "%sfmlBinPath%\sfml-graphics-2.dll" %outputPath%
	xcopy /D "%sfmlBinPath%\sfml-network-2.dll" %outputPath%
	xcopy /D "%sfmlBinPath%\sfml-system-2.dll" %outputPath%
	xcopy /D "%sfmlBinPath%\sfml-window-2.dll" %outputPath%
)

xcopy /D "%sfmlBinPath%\openal32.dll" %outputPath%
exit 0