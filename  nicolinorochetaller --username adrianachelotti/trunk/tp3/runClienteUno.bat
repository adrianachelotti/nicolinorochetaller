set Y = %CD%
cd %Y%
del .\ClienteUno\Cliente\Debug\archivos\*.bmp
del .\ClienteUno\Cliente\Debug\errores\*.bmp
cd .\ClienteUno\Cliente\Debug
rem call .\Cliente04.exe localhost 5000
call .\Cliente04.exe localhost 5000
