set Y = %CD%
cd %Y%
del .\clientedeprueba\imagenesTransferidas\*.bmp
call .\clientedeprueba\testClient\Debug\Cliente04.exe localhost 5001
