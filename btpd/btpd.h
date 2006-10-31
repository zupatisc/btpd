#ifndef BTPD_H
#define BTPD_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <assert.h>
#include <errno.h>
#include <event.h>
#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

#include "queue.h"

#include "benc.h"
#include "metainfo.h"
#include "subr.h"
#include "iobuf.h"
#include "hashtable.h"
#include "net_buf.h"
#include "net_types.h"
#include "net.h"
#include "peer.h"
#include "tlib.h"
#include "torrent.h"
#include "download.h"
#include "upload.h"
#include "content.h"
#include "opts.h"
#define DAEMON
#include "btpd_if.h"
#undef DAEMON

#define BTPD_VERSION PACKAGE_NAME "/" PACKAGE_VERSION

#define BTPD_L_ALL      0xffffffff
#define BTPD_L_ERROR    0x00000001
#define BTPD_L_TRACKER  0x00000002
#define BTPD_L_CONN     0x00000004
#define BTPD_L_MSG      0x00000008
#define BTPD_L_BTPD     0x00000010
#define BTPD_L_POL      0x00000020

extern long btpd_seconds;

void btpd_init(void);

__attribute__((format (printf, 2, 3)))
void btpd_log(uint32_t type, const char *fmt, ...);

__attribute__((format (printf, 1, 2), noreturn))
void btpd_err(const char *fmt, ...);

__attribute__((malloc))
void *btpd_malloc(size_t size);
__attribute__((malloc))
void *btpd_calloc(size_t nmemb, size_t size);

void btpd_ev_add(struct event *ev, struct timeval *tv);
void btpd_ev_del(struct event *ev);

void btpd_shutdown(int grace_seconds);
int btpd_is_stopping(void);

const uint8_t *btpd_get_peer_id(void);

void td_acquire_lock(void);
void td_release_lock(void);

#define td_post_begin td_acquire_lock
void td_post(void (*fun)(void *), void *arg);
void td_post_end(void);

void btpd_on_no_torrents(void);

#endif
