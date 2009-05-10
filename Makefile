### Makefile --- 

## Author: sebastianarcila@gmail.com
## Version: 1: Makefile,v 1.0 2009/05/10 16:50:45 sebastian Exp $
## Keywords: ray tracer, c++
## X-URL: 

CFLAGS =  -O3
OBJS = raytracer
all = main
CC = g++
SRC = src/*.cpp
raytracer: 
	$(CC) $(SRC)  -o  $(OBJS) $(CFLAGS)

clean:
	-$(RM) raytracer

### Makefile ends here
