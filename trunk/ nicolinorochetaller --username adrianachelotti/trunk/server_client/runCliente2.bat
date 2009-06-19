set Y = %CD%
cd %Y%
del .\clientedeprueba\imagenesTransferidas\*.bmp
del .\clientedeprueba2\imagenesTransferidas\*.bmp
call .\clientedeprueba2\testClient\Debug\Cliente04.exe localhost 5001