# [Very Dirty] raylib 5.5 port for ps vita

raylib vita using pvr driver

everything should work.
supports wav ogg and mp3 playback

requires sdl2 with pvr support

i recommend using [vita-packages-extra](https://github.com/isage/vita-packages-extra/) to install sdl2 with pvr_psp2

# building/installing

Run `make clean && make -j$(nproc) && make install` in `/src`
