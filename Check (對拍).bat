:loop
data_maker.exe>data.in
p1.exe<data.in>p1.out
p2.exe<data.in>p2.out
pause
fc p1.out 2.out
if errorlevel 1 goto end
goto loop
:end