<pre><code>
<?php

class ZMQ {

    /**
     * Peer to peer socket
     * Compatible sockets: SOCKET_P2P
     */
    const SOCKET_P2P = 1;

    /**
     * Publish-subscribe 
     * Compatible sockets: SOCKET_SUB
     */
    const SOCKET_PUB = 2;

    /**
     * Publish-subscribe 
     * Compatible sockets: SOCKET_PUB
     */    
    const SOCKET_SUB = 3;

    /**
     * Request-reply
     * Compatible sockets: SOCKET_REP
     */
    const SOCKET_REQ = 4;

    /**
     * Request-reply
     * Compatible sockets: SOCKET_REQ
     */
    const SOCKET_REP = 5;

    /**
     * TODO
     */
    const SOCKET_XREQ = 6;

    /**
     * TODO
     */
    const SOCKET_XREP = 7;

    /**
     * Parallelized pipeline
     * Compatible sockets: SOCKET_DOWNSTREAM
     */
    const SOCKET_UPSTREAM = 8;

    /**
     * Parallelized pipeline
     * Compatible sockets: SOCKET_UPSTREAM
     */
    const SOCKET_DOWNSTREAM = 9;

    /**
     * Set high water mark
     * Valuetype: integer
     */
    const SOCKOPT_HWM = 1;

    /**
     * Set low water mark
     * Valuetype: integer
     */
    const SOCKOPT_LWM = 2;

    /**
     * Set disk offload size
     * Valuetype: integer
     */
    const SOCKOPT_SWAP = 3;

    /**
     * Set I/O thread affinity 
     * Valuetype: integer
     */
    const SOCKOPT_AFFINITY = 4;

    /**
     * Set socket identity
     * Valuetype: string
     */
    const SOCKOPT_IDENTITY = 5;

    /**
     * Establish message filter
     * Valuetype: string
     */
    const SOCKOPT_SUBSCRIBE = 6;

    /**
     * Remove message filter
     * Valuetype: string
     */
    const SOCKOPT_UNSUBSCRIBE = 7;

    /**
     * Set multicast data rate
     * Valuetype: integer >= 0
     */
    const SOCKOPT_RATE = 8;

    /**
     * Set multicast recovery interval
     * Valuetype: integer >= 0
     */
    const SOCKOPT_RECOVERY_IVL = 9;

    /**
     * Control multicast loopback
     * Valuetype: integer >= 0
     */
    const SOCKOPT_MCAST_LOOP = 10;

    /**
     * Set kernel transmit buffer size
     * Valuetype: integer >= 0
     */
    const SOCKOPT_SNDBUF = 11;

    /**
     * Set kernel receive buffer size
     * Valuetype: integer >= 0
     */
    const SOCKOPT_RCVBUF = 12;
    
    /**
     * Send a multipart message
     * @since 0MQ 2.0.7
     */
     const SOCKOPT_SNDMORE = 13;

     /**
      * Receive a multipart message
      * @since 0MQ 2.0.7
      */
     const SOCKOPT_RECVMORE = 14;    

    /**
     * Set on non-blocking mode
     */
     const MODE_NOBLOCK = 1;
 
    /**
     * Track if the socket is readable
     */
     const POLL_IN = 1;

    /**
     * Track if the socket is writable
     */
     const POLL_OUT = 2;
    
    /**
     * Construct a new ZMQ object. The extending class must call this method. 
     * The type is one of the ZMQ::SOCKET_* constants. 
     * Persistent id allows reusing the socket over multiple requests. 
     * If persistent_id parameter is specific the type parameter is ignored and the 
     * socket is of type that it was initially created with. Persistent context must 
     * be enabled for persistent_id to work. Setting incorrect socket type might 
     * cause failure later in connect/bind/setSockOpt.
     *
     * @param integer $type              The type of the socket
     * @param string  $persistent_id     The persistent id. Can be used to create
     *                                   persistent connections
     * @throws ZMQException
     * @return void
     */
    public function __construct($type, $persistent_id = null) {}

    /**
     * Sends a message to the queue. 
     *
     * @param string  $message  The message to send
     * @param integer $flags    self::MODE_NOBLOCK or 0
     * @throws ZMQException if sending message fails
     *
     * @return ZMQ
     */
    public function send($message, $flags = 0) {}

    /**
     * Receives a message from the queue.
     * 
     * @param integer $flags self::MODE_NOBLOCK or 0
     * @throws ZMQException if receiving fails.
     *
     * @return string
     */
    public function recv($flags = 0) {}

    /**
     * Connect the socket to a remote endpoint. For more information about the dsn 
     * see http://api.zeromq.org/zmq_connect.html. By default the method does not 
     * try to connect if it has been already connected to the address specified by $dsn.
     *
     * @param string  $dsn   The connect dsn
     * @param boolean $force Tries to connect to end-point even if the object is already connected to the $dsn
     *
     * @throws ZMQException If connection fails
     * @return ZMQ
     */
    public function connect($dsn, $force = false) {}

    /**
     *
     * Binds the socket to an end-point. For more information about the dsn see 
     * http://api.zeromq.org/zmq_connect.html. By default the method does not 
     * try to bind if it has been already bound to the address specified by $dsn.
     *
     * @param string  $dsn   The bind dsn
     * @param boolean $force Tries to bind to end-point even if the object is already bound to the $dsn
     *
     * @throws ZMQException if binding fails
     * @return ZMQ
     */
    public function bind($dsn, $force = false) {}

    /**
     * Sets a socket option. For more information about socket options see 
     * http://api.zeromq.org/zmq_setsockopt.html
     *
     * @param integer $key   The option key
     * @param mixed   $value The option value
     *
     * @throws ZMQException
     * @return ZMQ
     */
    public function setSockOpt($key, $value) {}

    /**
     * Gets a socket option. This method is available if ZMQ extension
     * has been compiled against ZMQ version 2.0.7 or higher
     *
     * @param integer $key The option key
     *
     * @throws ZMQException
     * @return mixed
     */
    public function getSockOpt($key) {}    

    /**
     * Set the amount of threads and whether to poll in the internal context. Must be 
     * set before connect / bind / setSockOpt is called. For persistent objects
     * it is on the first instanciation.
     *
     * $poll must be true if the object is going to be added into ZMQPoll.
     * 
     *
     * @param integer $app_threads  How many application threads
     * @param integer $io_threads   How many io threads
     * @param boolean $poll         Whether to support polling
     *
     * @throws ZMQException if the socket has been initialized already
     * @return ZMQ
     */
    public function setContextOptions($app_threads, $io_threads, $poll = false) {}    

    /**
     * Get the options for the internal context. The returned
     * array contains keys 'app_threads', 'io_threads' and 'poll'
     *
     * @return array
     */
    public function getContextOptions() {}

    /**
     * Get endpoints where the socket is connected to. The return array
     * contains two sub-arrays: 'connect' and 'bind'
     *
     * @throws ZMQException
     * @return array 
     */
    public function getEndpoints() {}

    /**
     * Return the socket type. Returns one of ZMQ::SOCKET_* constants
     *
     * @throws ZMQException
     * @return integer 
     */
    public function getSocketType() {}
}


class ZMQPoll {
 
    /**
     * Add a new object into the poll set. Returns the id for the object
     * in the pollset.
     * 
     * @param ZMQ $object Object to add to set
     * @param integer $type Bit-mask of ZMQ::POLL_* constants
     *
     * @throws ZMQPollException if the object has not been initialized with polling
     * @return integer
     */
    public function add(ZMQ $object, $type) {}
    
    /**
     * Execute the poll. Readable and writable sockets are returned
     * in the arrays passed by reference. If either of the given arrays
     * is null the events of that type are not returned. Returns an integer
     * indicated the amount of objects with events pending.
     *
     * @param array &$readable  array where to return the readable objects
     * @param array &$writable  array where to return the writable objects
     * @param integer $timeout   Timeout for poll in milliseconds. -1 polls as long as one of the objects comes readable/writable
     *
     * @throws ZMQPollException if polling fails
     * @return integer
     */
    public function poll(array &$readable, array &$writable, $timeout = -1) {}
    
    /**
     * Returns the ids of the objects that had ZMQ_POLLERR flag set on the last 
     * poll call. This method does not clear the last errors and the errors are
     * cleared on next call to poll()
     * 
     * @return array
     */
    public function getLastErrors() {}    
}
?>
</code></pre>

h3. INI settings

<pre><code>
zeromq.persist_context   Boolean   PHP_INI_ALL  (Default: On)
</code></pre>
Whether or not persistent contexts are allowed. Each unique combination of application and io threads creates a new context which is persisted if this setting is on. This setting must be set On for persistent connections to work.

