@ECHO off
SETLOCAL EnableDelayedExpansion
SET objectFiles=SpaceRTS.cpp
SET engineFiles=
SET oFile=unit unitTarget point planet partition triangulation regionMapping nationGenerator
SET eFile=game.cpp game.h rnd.cpp rnd.h utils.cpp utils.h input.cpp input.h win.cpp win.h entity.cpp entity.h entityHandler.cpp particle.cpp particle.h particleSystem.h entityHandler.h textureTable.cpp textureTable.h animator.cpp animator.h 
SET oPref=o/
SET ePref=e/
SET srcSuf=.cpp
SET headSuf=.h
FOR %%i IN (%oFile%) DO SET objectFiles=!objectFiles! %oPref%%%i%srcSuf% %oPref%%%i%headSuf%
FOR %%k IN (%eFile%) DO SET engineFiles=!engineFiles! %ePref%%%k
SET cmpParams=-o run -IC:\codeProjects\nationGenerator\SFML-2.5.1\include -LC:\codeProjects\nationGenerator\SFML-2.5.1\lib -DSFML_STATIC -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32
SET stdTarget=-std=c++17
ECHO ERRORS/WARNINGS:
g++ %stdTarget% %objectFiles% %engineFiles% %cmpParams%
if errorlevel 0 (
	cls
	color 0A
	ECHO COMPILE TERMINATED WITH EXIT STATUS 0
	ECHO.	
	ECHO GENERATION OF "run.exe" WAS SUCCESSFUL
	timeout /t 5 > nul
)
color
