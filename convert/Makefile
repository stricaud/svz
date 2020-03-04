all: svzconvert

svzconvert: svzconvert.c
	gcc svzconvert.c -o svzconvert -lgd -lpng -lz -ljpeg -lfreetype -lm -I../libsvz/src/include/ -L../libsvz/build/src/ -lsvz

