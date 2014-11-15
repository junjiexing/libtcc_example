cd /d %~dp0

echo generating crt...

@set target=-DTCC_TARGET_PE -DTCC_TARGET_I386

.\tcc %target% -c lib/libtcc1.c
.\tcc %target% -c lib/crt1.c
.\tcc %target% -c lib/wincrt1.c
.\tcc %target% -c lib/dllcrt1.c
.\tcc %target% -c lib/dllmain.c
.\tcc %target% -c lib/chkstk.S
.\tcc %target% -c lib/alloca86.S
.\tcc %target% -c lib/alloca86-bt.S
.\tcc %target% -c lib/bcheck.c
tiny_libmaker lib/libtcc1.a libtcc1.o alloca86.o alloca86-bt.o crt1.o wincrt1.o dllcrt1.o dllmain.o chkstk.o bcheck.o