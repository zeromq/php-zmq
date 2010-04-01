#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <zmq.h>

/*
	Adapted from ZMQ examples. Compile with 
	gcc test.c -lzmq -o test
*/
 
int main (int argc, char *argv[]) 
{
    int rc;
    void *ctx, *s;
    zmq_msg_t query, resultset;
    const char *query_string, *resultset_string;
 
    /* Initialise 0MQ context, requesting a single application thread
       and a single I/O thread */
    ctx = zmq_init (1, 1, 0);
    assert (ctx);
    /* Create a ZMQ_REP socket to receive requests and send replies */
    s = zmq_socket (ctx, ZMQ_REP);
    assert (s);

	if (argc > 1) {
		rc = zmq_bind (s, argv[1]);
	} else {
		rc = zmq_bind (s, "tcp://127.0.0.1:5555");
	}

    assert (rc == 0);
 
    while (1) {
        /* Allocate an empty message to receive a query into */
        rc = zmq_msg_init (&query);
        assert (rc == 0);
 
        /* Receive a message, blocks until one is available */
        rc = zmq_recv (s, &query, 0);
        assert (rc == 0);

		printf("Size: %d\n", zmq_msg_size(&query));

        /* Send back our canned response */
	    rc = zmq_msg_init_size (&resultset, zmq_msg_size(&query));
		assert (rc == 0);
		memcpy (zmq_msg_data (&resultset), zmq_msg_data (&query), zmq_msg_size(&query));


        rc = zmq_send (s, &resultset, 0);
        assert (rc == 0);

		zmq_msg_close (&query);
		zmq_msg_close (&resultset);
    }
}