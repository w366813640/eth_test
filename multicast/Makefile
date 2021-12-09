all: mcastserver mcastclient

mcastserver: mcastserver.c
	gcc mcastserver.c -o mcastserver

mcastclient: mcastclient.c
	gcc mcastclient.c -o mcastclient

clean:
	rm mcastserver mcastclient
