echo off
echo params %*
echo 1 param %1
echo 2 param %2
echo 3 param %3

set /a res= %1 %3 %2
echo %res%