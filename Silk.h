/* 
 * File:   Silk.h
 * Author: mschwartz
 *
 * Created on July 22, 2010, 11:17 AM
 */

#ifndef SILK_H
#define	SILK_H

#define GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/file.h>

// SpiderMonkey
#define XP_UNIX
#include <js/jsapi.h>

#include "Util.h"

#include "TSocket.h"
#include "TServerSocket.h"

#include "TInterpreter.h"
#include "THeader.h"
#include "THttpRequest.h"
#include "THttpResponse.h"


#include "THttpChild.h"

#endif	/* SILK_H */

