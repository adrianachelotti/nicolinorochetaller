set Y = %CD%
cd %Y%
del .\ClienteDos\Cliente\Debug\imagenes\*.bmp
del .\ClienteDos\Cliente\Debug\niveles\*.bmp
del .\ClienteDos\Cliente\Debug\errores\*.bmp
cd .\ClienteDos\Cliente\Debug
call .\Cliente04.exe localhost 5001
