CFLAGS =  -O2 -Zmts -s
HEAD = dink_sym.h dink_glb.h

# Don't add anymore files because the makefile with the Borland Ver. 2
#    Tlink will choke and die.

OBJECTS = dinkum.o describe.o longdsc.o objlook.o actor.o \
pusher.o monster.o opener.o parse.o taker.o
dinkum: $(OBJECTS)
	gcc $(CFLAGS) -o dinkum.exe $(OBJECTS)
dinkum.o: dinkum.c $(HEAD)
	gcc $(CFLAGS) -c dinkum.c
describe.o: describe.c $(HEAD)
	gcc $(CFLAGS) -c describe.c
longdsc.o: longdsc.c $(HEAD)
	gcc $(CFLAGS) -c longdsc.c
objlook.o: objlook.c $(HEAD)
	gcc $(CFLAGS) -c objlook.c
pusher.o: pusher.c $(HEAD)
	gcc $(CFLAGS) -c pusher.c
actor.o: actor.c $(HEAD)
	gcc $(CFLAGS) -c actor.c
monster.o: monster.c $(HEAD)
	gcc $(CFLAGS) -c monster.c
opener.o: opener.c $(HEAD)
	gcc $(CFLAGS) -c opener.c
taker.o: taker.c $(HEAD)
	gcc $(CFLAGS) -c taker.c

parse.o: parse.c $(HEAD)
# Replace with PROMPT if you want a prompt with every command entry.
# This modification was suggested by Chris Herborth.  Thanks, Chris!
#	cc $(CFLAGS) -DPROMPT parse.c
	gcc $(CFLAGS) -DPROMPT -c parse.c


