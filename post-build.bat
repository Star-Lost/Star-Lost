@echo off
set buildTarget=%1
set outputPath=%2
set sfmlBinPath=..\Third Party\SFML-2.3.2\bin

if %buildTarget% == "Debug" (
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