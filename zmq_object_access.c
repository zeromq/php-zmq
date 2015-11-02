static inline php_zmq_context_object *php_zmq_context_fetch_object(zend_object *obj) {
	return (php_zmq_context_object *)((char *)obj - XtOffsetOf(php_zmq_context_object, zo));
}

static inline php_zmq_socket_object *php_zmq_socket_fetch_object(zend_object *obj) {
	return (php_zmq_socket_object *)((char *)obj - XtOffsetOf(php_zmq_socket_object, zo));
}

static inline php_zmq_poll_object *php_zmq_poll_fetch_object(zend_object *obj) {
	return (php_zmq_poll_object *)((char *)obj - XtOffsetOf(php_zmq_poll_object, zo));
}

static inline php_zmq_device_object *php_zmq_device_fetch_object(zend_object *obj) {
	return (php_zmq_device_object *)((char *)obj - XtOffsetOf(php_zmq_device_object, zo));
}

#define PHP_ZMQ_CONTEXT_OBJECT php_zmq_context_fetch_object(Z_OBJ_P(getThis()));
#define PHP_ZMQ_SOCKET_OBJECT  php_zmq_socket_fetch_object(Z_OBJ_P(getThis()));
#define PHP_ZMQ_POLL_OBJECT    php_zmq_poll_fetch_object(Z_OBJ_P(getThis()));
#define PHP_ZMQ_DEVICE_OBJECT  php_zmq_device_fetch_object(Z_OBJ_P(getThis()));