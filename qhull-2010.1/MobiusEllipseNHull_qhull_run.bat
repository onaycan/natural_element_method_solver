@echo off
echo
echo ========= qhull_run.bat voronoits your population ===========
echo.
cd E:\meshless\fromDesktop\NEM3DCAN\NEM3DCAN\NEM3DCAN\qhull-2010.1
if exist %qvoronoi.exe goto spring
echo There is nothing like qvoronoi.exe under this directory says CAN
REM This file reads the group of points in meshless_input.txt,
REM calls the programm qhull to calculate the voronoi diagramm freaky fast, 
REM writes the result in voronoi_input.txt and delaunayinput.txt
REM The order line by line 
REM (1),(2),(3)comments
REM (5) check the existance of the executable (qvoronoi.exe)
REM (8) spring to the existance condition statement (you can replace spring statement with something else) 
REM (9) show in the command prompt that you are alright till now...
REM (10) syntax-in the voronoi think. 
REM (10) you first enter the executable, then the input file (the point cloud), and output file. 
REM (10)For better understanding of this sytax refer to the qhull documentation
REM (11) Remarks: copy the written file, into the input directiory of your meshless program. was done before
REM (11) /Y overwrites the file(voronoi_input.txt) without asking you for further replacement
goto ENDE
:spring
echo The current qvoronoi.exe is under this directory of yours
qvoronoi<MobiusEllipseNHullmeshless_input.txt Qt s o Fv TO MobiusEllipseNHullvoronoi_input.txt
qdelaunay<MobiusEllipseNHullmeshless_input.txt Qt i Fa TO MobiusEllipseNHulldelaunay_input.txt
REM xcopy E:meshlessromDesktopmeshless3D1meshless3D1qhull-2010.1Nvoronoi_input.txt  E:meshlessromDesktopmeshless3D1meshless3D1inputsN_inputs /Y 
REM xcopy E:meshlessromDesktopmeshless3D1meshless3D1qhull-2010.1Ndelaunay_input.txt  E:meshlessromDesktopmeshless3D1meshless3D1inputsN_inputs /Y 
cd .
:ENDE 
echo.
echo ========= qhull_run.bat finished with or withhout errors ===========
