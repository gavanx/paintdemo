#gcc -o demo $(pkg-config --cflags --libs cairo) demo.c -lcairo
#gcc -o demo demo.c -I../../ -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/json-c -L/usr/local/lib -ljson-c -lgobject-2.0 -lglib-2.0


#-I/usr/local/include/libmypaint -I/usr/include/json-c -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -L/usr/local/lib -lmypaint -ljson-c -lgobject-2.0 -lglib-2.0

#-fpermissive -m32
gcc -o  demo \
 -I../../ \
 -I/usr/include/json-c -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -L/usr/local/lib -ljson-c -lgobject-2.0 -lglib-2.0 \
 $(pkg-config --cflags --libs cairo) \
 demo_main.c demo.c canvas.c -DMYPAINT_CONFIG_USE_GLIB -lm -ljson-c -lgobject-2.0 -lglib-2.0 -lcairo