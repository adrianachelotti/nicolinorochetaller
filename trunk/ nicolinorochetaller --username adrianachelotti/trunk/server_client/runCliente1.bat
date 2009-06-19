set Y = %CD%
cd %Y%
del .\clientedeprueba\imagenesTransferidas\*.bmp
rem call .\clientedeprueba\testClient\Debug\Cliente04.exe 169.254.113.36 5001
call .\clientedeprueba\testClient\Debug\Cliente04.exe localhost 5000
