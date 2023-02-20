nasm -fobj main.asm
nasm -fobj modul.asm

alink main.obj modul.obj -oPE -subsys console -entry start
