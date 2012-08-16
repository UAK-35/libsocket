# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include "../headers/libunixsocket.h"

/*
 * This example is part of libsocket/libunixsocket
 * It may be used with the other part, unix_stream_server.c
 * This example simply sends a string to the echo server
 * and tries to receive the answer and print it.
*/

int main(void)
{
	int sfd, bytes = 1;
	const char* string = "abcdefghijklmnopqrstuvwxyz";
	char buf[16];

	memset(buf,0,sizeof(buf));

	if ( -1 == (sfd = create_unix_stream_socket("/tmp/echosock",0)) )
		return -1;

	write(sfd,string,26);

	shutdown_unix_stream_socket(sfd,WRITE); // Send EOF

	while ( bytes > 0 )
	{
		bytes = read(sfd,buf,15);
		write(1,buf,bytes);
	}

	destroy_unix_socket(sfd);

	return 0;
}
