gcc -DHAVE_CONFIG_H -I. -I. -I..  -I/usr/include -Iinclude -I. -DLOCALEDIR=\"/usr/share/locale\"   -pipe -Wall -O3 -Wno-unused -DNO_DEBUG -DPIC -fPIC             -ffast-math -fomit-frame-pointer -funroll-loops -c adenv_lvl.c
gcc -DHAVE_CONFIG_H -I. -I. -I..  -I/usr/include -Iinclude -I. -DLOCALEDIR=\"/usr/share/locale\"   -pipe -Wall -O3 -Wno-unused -DNO_DEBUG -DPIC -fPIC             -ffast-math -fomit-frame-pointer -funroll-loops -nostartfiles -shared -lc -o adenv_lvl.so  adenv_lvl.o

gcc -DHAVE_CONFIG_H -I. -I. -I..  -I/usr/include -Iinclude -I. -DLOCALEDIR=\"/usr/share/locale\"   -pipe -Wall -O3 -Wno-unused -DNO_DEBUG -DPIC -fPIC             -ffast-math -fomit-frame-pointer -funroll-loops -c adenv.c
gcc -DHAVE_CONFIG_H -I. -I. -I..  -I/usr/include -Iinclude -I. -DLOCALEDIR=\"/usr/share/locale\"   -pipe -Wall -O3 -Wno-unused -DNO_DEBUG -DPIC -fPIC             -ffast-math -fomit-frame-pointer -funroll-loops -nostartfiles -shared -lc -o adenv.so  adenv.o

gcc -DHAVE_CONFIG_H -I. -I. -I..  -I/usr/include -Iinclude -I. -DLOCALEDIR=\"/usr/share/locale\"   -pipe -Wall -O3 -Wno-unused -DNO_DEBUG -DPIC -fPIC             -ffast-math -fomit-frame-pointer -funroll-loops -c dahdsr_hexp.c
gcc -DHAVE_CONFIG_H -I. -I. -I..  -I/usr/include -Iinclude -I. -DLOCALEDIR=\"/usr/share/locale\"   -pipe -Wall -O3 -Wno-unused -DNO_DEBUG -DPIC -fPIC             -ffast-math -fomit-frame-pointer -funroll-loops -nostartfiles -shared -lc -o dahdsr_hexp.so  dahdsr_hexp.o

gcc -DHAVE_CONFIG_H -I. -I. -I..  -I/usr/include -Iinclude -I. -DLOCALEDIR=\"/usr/share/locale\"   -pipe -Wall -O3 -Wno-unused -DNO_DEBUG -DPIC -fPIC             -ffast-math -fomit-frame-pointer -funroll-loops -c dahdsr_fexp.c
gcc -DHAVE_CONFIG_H -I. -I. -I..  -I/usr/include -Iinclude -I. -DLOCALEDIR=\"/usr/share/locale\"   -pipe -Wall -O3 -Wno-unused -DNO_DEBUG -DPIC -fPIC             -ffast-math -fomit-frame-pointer -funroll-loops -nostartfiles -shared -lc -o dahdsr_fexp.so  dahdsr_fexp.o





