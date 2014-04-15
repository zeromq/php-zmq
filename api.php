<pre><code>
<?php

class ZMQContext {

    /**
     * Build a new ZMQContext. Persistent context is required for building
     * persistent sockets. 
     *
     *
     * @param integer $io_threads     Number of io threads
     * @param boolean $is_persistent  Whether the context is persistent
     * 
     * @return void
     */
    public function __construct($io_threads = 1, $is_persistent = true) {}

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
     * @param function   $on_new_socket     Called when a new socket is created     
     * @throws ZMQException
     * @return ZMQSocket
     */
    public function getSocket($type, $persistent_id = null, $on_new_socket = null) {}
    
    /**
     * Whether the context is persistent
     *
     * @return boolean
     */
    public function isPersistent() {}
}

class ZMQSocket {
    
    /**
     * Publish-subscribe 
     * Compatible sockets: SOCKET_SUB
     */
    const SOCKET_PAIR = 0;

    /**
     * Publish-subscribe 
     * Compatible sockets: SOCKET_SUB
     */
    const SOCKET_PUB = 1;

    /**
     * Publish-subscribe 
     * Compatible sockets: SOCKET_PUB
     */    
    const SOCKET_SUB = 2;

    /**
     * Request-reply
     * Compatible sockets: SOCKET_REP
     */
    const SOCKET_REQ = 3;

    /**
     * Request-reply
     * Compatible sockets: SOCKET_REQ
     */
    const SOCKET_REP = 4;

    /**
     * TODO
     */
    const SOCKET_XREQ = 5;

    /**
     * TODO
     */
    const SOCKET_XREP = 6;

    /**
     * Parallelized pipeline
     * Compatible sockets: SOCKET_DOWNSTREAM
     */
    const SOCKET_UPSTREAM = 7;

    /**
     * Parallelized pipeline
     * Compatible sockets: SOCKET_UPSTREAM
     */
    const SOCKET_DOWNSTREAM = 8;

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
     * Receive multipart message
     */
    const SOCKOPT_RCVMORE = 13;

    /**
     * Set on non-blocking mode
     */
    const MODE_NOBLOCK = 1;
     
    /**
     * Send multipart message
     */
    const MODE_SNDMORE = 2;
 
    /**
     * Track if the socket is readable
     */
    const POLL_IN = 1;

    /**
     * Track if the socket is writable
     */
    const POLL_OUT = 2;

    /**
     * Use the PLAIN authentication mechanism to authenticate clients.
     */
    const SOCKOPT_PLAIN_SERVER = 44;

    /**
     * The username to present when connecting to a server using the PLAIN
     * authentication mechanism.
     */
    const SOCKOPT_PLAIN_USERNAME = 45;

    /**
     * The password to present when connecting to a server using the PLAIN
     * authentication mechanism.
     */
    const SOCKOPT_PLAIN_PASSWORD = 46;

    /**
     * Use the CURVE authentication mechanism to authenticate clients.
     */
    const SOCKOPT_CURVE_SERVER = 47;

    /**
     * The public key to present when connecting to a server using the CURVE
     * authentication mechanism.
     */
    const SOCKOPT_CURVE_PUBLICKEY = 48;

    /**
     * The secret key to present when connecting to a server using the CURVE
     * authentication mechanism.
     */
    const SOCKOPT_CURVE_SECRETKEY = 49;

    /**
     * The public key of the server using the CURVE authentication mechanism.
     */
    const SOCKOPT_CURVE_SERVERKEY = 50;

    /**
     * The domain for ZAP authentication.
     */
    const SOCKOPT_ZAP_DOMAIN = 55;

    /**
     * When configuring a ZMQAuth to use the CURVE authentication mechanism
     * (see ZMQAuth#configure), specify ZMQ::CURVE_ALLOW_ANY as the location
     * parameter to allow all client keys without checking.
     */
    const CURVE_ALLOW_ANY = '*';
    
    /**
     * Construct a new ZMQ object. The extending class must call this method. 
     * The type is one of the ZMQ::SOCKET_* constants. 
     * Persistent id allows reusing the socket over multiple requests. 
     * If persistent_id parameter is specific the type parameter is ignored and the 
     * socket is of type that it was initially created with. Persistent context must 
     * be enabled for persistent_id to work. Setting incorrect socket type might 
     * cause failure later in connect/bind/setSockOpt.
     *
     * @param ZMQContext $context           ZMQContext to build this object
     * @param integer    $type              The type of the socket
     * @param string     $persistent_id     The persistent id. Can be used to create
     *                                      persistent connections
     * @param function   $on_new_socket     Called when a new socket is created
     * @throws ZMQException
     * @return void
     */
    public function __construct(ZMQContext $context, $type, $persistent_id = null, $on_new_socket = null) {}

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
     * @since 0MQ 2.0.7
     * @param integer $key The option key
     *
     * @throws ZMQException
     * @return mixed
     */
    public function getSockOpt($key) {}    

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
    
    /**
     * Whether the socket is persistent
     *
     * @return boolean
     */
    public function isPersistent() {}
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
     * @param array &$readable   array where to return the readable objects
     * @param array &$writable   array where to return the writable objects
     * @param integer $timeout   Timeout for poll in microseconds. -1 polls as long as one of the objects comes readable/writable
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
    
    /**
     * Removes an item from the poll object. The parameter can be ZMQ object, 
     * resource or the string id returned by 'add' method. Returns true if the
     * item was removed and false if item had not been added to the poll object.
     * 
     * @throws ZMQPollException if the poll object is empty
     * @throws ZMQPollException if $item parameter is object but not an instance of ZMQ
     *
     * @param mixed $item  The item to remove
     * @return boolean
     */
    public function remove($item) {}
    
    /**
     * Counts the items in the poll object
     *
     * @return integer
     */
    public function count() {}
    
    /**
     * Removes all items from the poll set
     *
     * @return ZMQPoll
     */
    public function clear() {}
}

/**
 * A security certificate for the ØMQ CURVE authentication mechanism.
 */
class ZMQCert {

    /**
     * Constructs a new instance of the ZMQCert class.
     *
     * If the filename parameter is given and is a readable file, then the
     * security certificate is initialised with the public and secret keys and
     * metadata in the file.
     *
     * Note well that if the file only contains a public key, then the secret
     * key won't be initialised but the security certificate can be applied to a
     * socket without error.
     *
     * If the filename parameter isn't given, then the security certificate is
     * initialised with randomly generated public and secret keys.
     *
     * @final
     *
     * @param string $filename
     * @throws ZMQCertException If the filename parameter isn't a string or
     *     can't be converted to a string
     * @throws ZMQCertException If the underlying zcert object can't be
     *     created, which is likely if libsodium isn't installed
     * @throws ZMQCertException If the file isn't readable or isn't in the
     *     {@link ZMQCert#save} format
     */
    public function __construct($filename = '') {}

    /**
     * Gets the public key as a 32-byte binary string.
     *
     * @return string
     */
    public function getPublicKey() {}

    /**
     * Gets the secret key as a 32-byte binary string.
     *
     * @return string
     */
    public function getSecretKey() {}

    /**
     * Gets the public key as a Z85 armoured string.
     *
     * @return string
     */
    public function getPublicTxt() {}

    /**
     * Gets the secret key as a Z85 armoured string.
     *
     * @return string
     */
    public function getSecretTxt() {}

    /**
     * Sets the metadata value.
     *
     * @param string $name The name of the metadata value
     * @param string $format The metadata value
     */
    public function setMeta($name, $format) {}

    /**
     * Gets the metadata value.
     *
     * @param string $name The name of the metadata value
     * @return string|null If the metadata value exists, then it is returned;
     *     otherwise null
     */
    public function getMeta($name) {}

    /**
     * Gets the names of all of the metadata values.
     *
     * Note well that the names of the metadata values are returned in the
     * opposite order that they are registered.
     *
     * <code>
     * $cert = new ZMQCert();
     * $cert->setMeta('one', '1');
     * $cert->setMeta('two', '2');
     * $cert->getMetaNames(); => ['two', 'one']
     * </code>
     *
     * @return array The names of all of the metadata values
     */
    public function getMetaKeys() {}

    /**
     * Saves the public key and metadata to the specified file.
     *
     * @param string $filename
     * @throws ZMQCertException If the file isn't writeable
     */
    public function savePublic($filename) {}

    /**
     * Saves the secret key and metadata to the specified file.
     *
     * @param string $filename
     * @throws ZMQCertException If the file isn't writeable
     */
    public function saveSecret($filename) {}

    /**
     * Saves the public and secret keys and metadata to the specified file.
     *
     * @param string $filename
     * @throws ZMQCertException If the file isn't writeable
     */
    public function save($filename) {}

    /**
     * Applies the security certificate to the socket by setting the
     * {@link ZMQ::CURVE_PUBLICKEY_BIN} and {@link ZMQ::CURVE_SECRETKEY_BIN}
     * socket options to the public and secret keys respectively.
     *
     * @param ZMQSocket $socket
     */
    public function apply(ZMQSocket $socket) {}

    /**
     * Clones the security certificate.
     *
     * @return ZMQCert
     */
    public function __clone() {}

    /**
     * Tests whether the security certificate is equal to another.
     *
     * Two security certificates are equal iff their public and secret keys are
     * equal.
     *
     * @param ZMQCert $certificate
     * @return boolean
     */
    public function equals(ZMQCert $certificate) {}
}

/**
 * A ØMQ authentication handler, which takes over authentication for all
 * incoming connections for a context.
 *
 * ØMQ has four authentication mechanisms: NULL, authenticated NULL, PLAIN,
 * and CURVE.
 *
 * The default authentication mechanism is NULL, which an
 * authentication handler doesn't receive authentication requests for.
 *
 * If a socket, that has a context with an authentication handler, has a ZAP
 * domain (the {@link ZMQ::SOCKOPT_ZAP_DOMAIN} socket option is set), then the
 * authentication handler receives authentication requests for incoming
 * connections to that socket, hence "authenticated NULL".
 *
 * In both the PLAIN and CURVE authentication mechanisms the authentication
 * handler tests the authentication credentials of the incoming connection.
 */
class ZMQAuth {

    /**
     * Configure the PLAIN authentication mechanism.
     *
     * @see ZMQAuth#configure
     */
    const AUTH_TYPE_PLAIN = 0;

    /**
     * Configure the CURVE authentication mechanism.
     *
     * @see ZMQAuth#configure
     */
    const AUTH_TYPE_CURVE = 1;

    /**
     * Constructs a new instance of the ZMQAuth class.
     *
     * @param ZMQContext $context
     * @throws ZMQAuthException If the underlying zauth object can't be
     *     created
     */
    public function __construct(ZMQContext $context) {}

    /**
     * Allow (whitelist) a single IP address.
     *
     * All incoming connections from the IP address will be accepted by the NULL
     * authentication mechanism and will be allowed to continue authenticating
     * in the PLAIN and CURVE authentication mechanisms.
     *
     * Note well that if you whitelist a single address, then any non-
     * whitelisted addresses are treated as if they were blacklisted.
     *
     * @param string $address
     */
    public function allow($address) {}

    /**
     * Deny (blacklist) a single IP address.
     *
     * All incoming connections from the IP address will be rejected by all
     * authentication mechanisms.
     *
     * Note well that if you define a whitelist and a blacklist then only the
     * whitelist will be used to authenticate incoming connections.
     *
     * @param string $address
     */
    public function deny($address) {}

    /**
     * Configure the PLAIN or CURVE authentication mechanism for the ZAP domain.
     *
     * When configuring the PLAIN authentication mechanism the filename
     * parameter should be the filename of a plain-text password file.
     *
     * @see examples/woodhouse.php
     *
     * When configuring the CURVE authentication mechanism the filename
     * parameter should be the path of the directory that contains valid public
     * keys.
     *
     * @param integer $type {@link ZMQAuth::PLAIN} to configure the PLAIN
     *     authentication mechanism or {@link ZMQAuth::CURVE} to configure the
     *     CURVE authentication mechanism
     * @param string $domain The ZAP domain. Use "*" to configure the PLAIN or
     *     CURVE authentication mechanism for all domains
     * @param string $filename
     */
    public function configure($type, $domain, $filename) {}
}
?>
</code></pre>
