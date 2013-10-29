<xsl:stylesheet
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	version="1.0">
	<xsl:output indent="no" method="text"/>
	<xsl:template match="/">
		<xsl:call-template name="file-header"/>
		
		<xsl:for-each select="/options/version">
#if <xsl:value-of select="@comparison" />

			<!-- start ZMQSocket::getSockOpt -->
			<xsl:call-template name="getsockopt-header"/>
			<xsl:for-each select="option">
				
				<xsl:variable name="raw-name">
					<xsl:call-template name="convert-to-uppercase">
						<xsl:with-param name="input-string" select="@name"/>
					</xsl:call-template>
				</xsl:variable>
				<xsl:variable name="const-name" select="concat('ZMQ_', $raw-name)"/>

				<xsl:variable name="max-length">
					<xsl:choose>
    					<xsl:when test="@max-length">
							<xsl:value-of select="@max-length"/>
						</xsl:when>
    					<xsl:otherwise>255</xsl:otherwise>
					</xsl:choose>
				</xsl:variable>

				<xsl:if test="@name != 'fd'">	
					<xsl:choose>
						<xsl:when test="@mode = 'rw' or @mode = 'r'">
							<xsl:call-template name="get-option">
								<xsl:with-param name="const-name" select="$const-name"/>
								<xsl:with-param name="raw-name" select="$raw-name"/>
								<xsl:with-param name="type" select="@type"/>
								<xsl:with-param name="max-length" select="$max-length"/>
							</xsl:call-template>
						</xsl:when>
						<xsl:otherwise>
							<xsl:call-template name="unsupported-operation">
								<xsl:with-param name="operation" select="'Getting'"/>
								<xsl:with-param name="const-name" select="$const-name"/>
								<xsl:with-param name="raw-name" select="$raw-name"/>
							</xsl:call-template>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:if>
			</xsl:for-each>
			<xsl:call-template name="getsockopt-footer" />
			<!-- end ZMQSocket::getSockOpt -->

			<!-- start ZMQSocket::setSockOpt -->
			<xsl:call-template name="setsockopt-header"/>

			<xsl:for-each select="option">
				<xsl:variable name="raw-name">
					<xsl:call-template name="convert-to-uppercase">
						<xsl:with-param name="input-string" select="@name"/>
					</xsl:call-template>
				</xsl:variable>
				<xsl:variable name="const-name" select="concat('ZMQ_', $raw-name)"/>
				<xsl:if test="@name != 'fd' and @name != 'events'">
					<xsl:choose>
						<xsl:when test="@mode = 'rw' or @mode = 'w'">
							<xsl:call-template name="set-option">
								<xsl:with-param name="const-name" select="$const-name"/>
								<xsl:with-param name="type" select="@type"/>
								<xsl:with-param name="raw-name" select="$raw-name"/>
							</xsl:call-template>
						</xsl:when>
						<xsl:otherwise>
							<xsl:call-template name="unsupported-operation">
								<xsl:with-param name="operation" select="'Setting'"/>
								<xsl:with-param name="const-name" select="$const-name"/>
								<xsl:with-param name="raw-name" select="$raw-name"/>
							</xsl:call-template>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:if>
			</xsl:for-each>
			
			<xsl:if test="@major = 3 or @major = 4">
				<xsl:call-template name="set-hwm-bwc"/>
			</xsl:if>
	
			<xsl:call-template name="setsockopt-footer" />

void php_zmq_register_sockopt_constants (zend_class_entry *php_zmq_sc_entry TSRMLS_DC)
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
	zend_declare_class_constant_long(php_zmq_sc_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);
			<xsl:if test="@major = 3 or @major = 4">
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HWM", ZMQ_HWM);
			</xsl:if>
			<xsl:for-each select="option">
				<xsl:variable name="raw-name">
					<xsl:call-template name="convert-to-uppercase">
						<xsl:with-param name="input-string" select="@name"/>
					</xsl:call-template>
				</xsl:variable>
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_<xsl:value-of select="$raw-name"/>", ZMQ_<xsl:value-of select="$raw-name"/>);
			</xsl:for-each>
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
			<!-- end ZMQSocket::setSockOpt -->
#endif
</xsl:for-each>
	</xsl:template>
	
	
	<xsl:template name="getsockopt-header">

/* {{{ proto mixed ZMQSocket::getSockOpt()
	Get a socket option
*/
PHP_METHOD(zmqsocket, getsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	size_t value_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &amp;key) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

	</xsl:template>
	<xsl:template name="getsockopt-footer">

		case ZMQ_FD:
		{
			php_stream *stm = php_zmq_create_zmq_fd(getThis() TSRMLS_CC);
			if (stm) {
				php_stream_to_zval(stm, return_value);
				return;
			}
			RETURN_FALSE;
		}
		break;

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
	}
}

	</xsl:template>

	<xsl:template name="unsupported-operation">
		<xsl:param name="operation"/>
		<xsl:param name="const-name"/>
		<xsl:param name="raw-name"/>
		case <xsl:value-of select="$const-name"/>:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "<xsl:value-of select="$operation"/> ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	</xsl:template>

	<xsl:template name="get-numeric-option">
		<xsl:param name="const-name"/>
		<xsl:param name="raw-name"/>
		<xsl:param name="type"/>	
		case <xsl:value-of select="$const-name"/>:
		{
			<xsl:value-of select="$type"/> value;

			value_len = sizeof(<xsl:value-of select="$type"/>);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &amp;value, &amp;value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	</xsl:template>

	<xsl:template name="get-blob-option">
		<xsl:param name="const-name"/>
		<xsl:param name="raw-name"/>
		<xsl:param name="max-length"/>
		case <xsl:value-of select="$const-name"/>:
		{
			char value[<xsl:value-of select="$max-length"/>];

			value_len = <xsl:value-of select="$max-length"/>;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &amp;value, &amp;value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
	</xsl:template>

	<xsl:template name="get-string-option">
		<xsl:param name="const-name"/>
		<xsl:param name="raw-name"/>
		<xsl:param name="max-length"/>
		case <xsl:value-of select="$const-name"/>:
		{
			char value[<xsl:value-of select="$max-length"/>];

			value_len = <xsl:value-of select="$max-length"/>;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &amp;value, &amp;value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len - 1, 1);
		}
		break;
	</xsl:template>
	
	<xsl:template name="get-option">
		<xsl:param name="const-name"/>
		<xsl:param name="raw-name"/>
		<xsl:param name="type"/>
		<xsl:param name="max-length" select="'xyz'"/>
		
		<xsl:choose>
			<xsl:when test="$type = 'blob'">
				<xsl:call-template name="get-blob-option">
					<xsl:with-param name="const-name" select="$const-name"/>
					<xsl:with-param name="raw-name" select="$raw-name"/>
					<xsl:with-param name="max-length" select="$max-length"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:when test="$type = 'string'">
				<xsl:call-template name="get-string-option">
					<xsl:with-param name="const-name" select="$const-name"/>
					<xsl:with-param name="raw-name" select="$raw-name"/>
					<xsl:with-param name="max-length" select="$max-length"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="get-numeric-option">
					<xsl:with-param name="const-name" select="$const-name"/>
					<xsl:with-param name="type" select="$type"/>
					<xsl:with-param name="raw-name" select="$raw-name"/>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	
	<xsl:template name="setsockopt-header">

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
	Set a socket option
*/
PHP_METHOD(zmqsocket, setsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	zval *pz_value;
	int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz/", &amp;key, &amp;pz_value) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

	</xsl:template>

	<xsl:template name="setsockopt-footer">

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	}
	ZMQ_RETURN_THIS;
}

	</xsl:template>
	
	<xsl:template name="set-string-option">
		<xsl:param name="const-name"/>
		<xsl:param name="raw-name"/>

		case <xsl:value-of select="$const-name"/>:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	</xsl:template>
	
	<xsl:template name="set-numeric-option">
		<xsl:param name="const-name"/>
		<xsl:param name="raw-name"/>
		<xsl:param name="type"/>

		case <xsl:value-of select="$const-name"/>:
		{
			<xsl:value-of select="$type"/> value;
			convert_to_long(pz_value);
			<xsl:if test="type = 'uint64_t'">
			if (Z_LVAL_P(pz_value) &lt; 0) {
				zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The option ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
				return;
			}
			</xsl:if>
			value  = (<xsl:value-of select="$type"/>) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &amp;value, sizeof(<xsl:value-of select="$type"/>));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_<xsl:value-of select="$raw-name"/> option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	</xsl:template>

	<xsl:template name="set-option">
		<xsl:param name="const-name"/>
		<xsl:param name="raw-name"/>
		<xsl:param name="type"/>
		
		<xsl:choose>
			<xsl:when test="$type = 'blob'">
				<xsl:call-template name="set-string-option">
					<xsl:with-param name="const-name" select="$const-name"/>
					<xsl:with-param name="raw-name" select="$raw-name"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="set-numeric-option">
					<xsl:with-param name="const-name" select="$const-name"/>
					<xsl:with-param name="type" select="$type"/>
					<xsl:with-param name="raw-name" select="$raw-name"/>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	
	<xsl:template name="set-hwm-bwc">
		
		case ZMQ_HWM:
		{
			int value;
			convert_to_long(pz_value);

			if (Z_LVAL_P(pz_value) &lt; 0) {
				zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The option value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
				return;
			}
			value = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &amp;value, sizeof(int));

			if (status == 0) {
				status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &amp;value, sizeof(int));
			}
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_HWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;
	</xsl:template>
	
	<xsl:template name="convert-to-uppercase">
		<xsl:param name="input-string"/>
	
		<xsl:variable name="lower" select="'abcdefghijklmnopqrstuvwxyz'" />
		<xsl:variable name="upper" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'" />

	  	<xsl:value-of select="translate($input-string, $lower, $upper)" />
	</xsl:template>
	
	<xsl:template name="file-header">
/*
+-----------------------------------------------------------------------------------+
|  ZMQ extension for PHP                                                            |
|  Copyright (c) 2010, Mikko Koppanen &lt;mkoppanen@php.net&gt;                           |
|  All rights reserved.                                                             |
+-----------------------------------------------------------------------------------+
|  Redistribution and use in source and binary forms, with or without               |
|  modification, are permitted provided that the following conditions are met:      |
|     * Redistributions of source code must retain the above copyright              |
|       notice, this list of conditions and the following disclaimer.               |
|     * Redistributions in binary form must reproduce the above copyright           |
|       notice, this list of conditions and the following disclaimer in the         |
|       documentation and/or other materials provided with the distribution.        |
|     * Neither the name of the copyright holder nor the                            |
|       names of its contributors may be used to endorse or promote products        |
|       derived from this software without specific prior written permission.       |
+-----------------------------------------------------------------------------------+
|  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND  |
|  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED    |
|  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           |
|  DISCLAIMED. IN NO EVENT SHALL MIKKO KOPPANEN BE LIABLE FOR ANY                   |
|  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES       |
|  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;     |
|  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND      |
|  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       |
|  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS    |
|  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                     |
+-----------------------------------------------------------------------------------+
*/

#include "php_zmq.h"
#include "php_zmq_private.h"
	</xsl:template>
	
</xsl:stylesheet>
