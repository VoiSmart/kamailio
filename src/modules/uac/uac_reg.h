/**
 * Copyright (C) 2010 Daniel-Constantin Mierla (asipto.com)
 *
 * This file is part of Kamailio, a free SIP server.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Kamailio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * Kamailio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _UAC_REG_H_
#define _UAC_REG_H_

#include "../../core/pvar.h"

#define UACREG_TABLE_VERSION 5

#define UACREG_REQTO_MASK_USER 1
#define UACREG_REQTO_MASK_AUTH 2

typedef struct _reg_uac
{
	unsigned int h_uuid;
	unsigned int h_user;
	str l_uuid;
	str l_username;
	str l_domain;
	str r_username;
	str r_domain;
	str realm;
	str auth_proxy;
	str auth_username;
	str auth_password;
	str auth_ha1;
	str callid;
	str contact_addr;
	str socket;
	unsigned int cseq;
	unsigned int flags;
	unsigned int expires;
	time_t timer_expires;
	unsigned int reg_delay;
	time_t reg_init;
	gen_lock_t *lock;
} reg_uac_t;

typedef struct _reg_item
{
	reg_uac_t *r;
	struct _reg_item *next;
} reg_item_t;


typedef struct _reg_entry
{
	unsigned int isize;
	unsigned int usize;
	reg_item_t *byuser;
	reg_item_t *byuuid;
	gen_lock_t lock;
} reg_entry_t;

typedef struct _reg_ht
{
	unsigned int htsize;
	time_t stime;
	reg_entry_t *entries;
} reg_ht_t;

extern int reg_timer_interval;
extern int reg_retry_interval;
extern int reg_htable_size;
extern int reg_fetch_rows;
extern int reg_keep_callid;
extern int reg_random_delay;
extern str reg_contact_addr;
extern str reg_db_url;
extern str reg_db_table;
extern str uac_default_socket;
/* just to check for non-local sockets for now */
extern struct socket_info *uac_default_sockinfo;

extern str l_uuid_column;
extern str l_username_column;
extern str l_domain_column;
extern str r_username_column;
extern str r_domain_column;
extern str realm_column;
extern str auth_username_column;
extern str auth_password_column;
extern str auth_proxy_column;
extern str expires_column;
extern str socket_column;

int uac_reg_load_db(void);
int uac_reg_init_ht(unsigned int sz);
int uac_reg_free_ht(void);

void uac_reg_timer(unsigned int ticks);
int uac_reg_init_rpc(void);

int uac_reg_send(reg_uac_t *reg, time_t tn);
int uac_reg_lookup(struct sip_msg *msg, str *src, pv_spec_t *dst, int mode);
int uac_reg_status(struct sip_msg *msg, str *src, int mode);
int uac_reg_request_to(struct sip_msg *msg, str *src, unsigned int mode);

int uac_reg_enable(sip_msg_t *msg, str *attr, str *val);
int uac_reg_disable(sip_msg_t *msg, str *attr, str *val);
int uac_reg_refresh(sip_msg_t *msg, str *l_uuid);

int reg_active_init(int mode);
int reg_ht_get_byfilter(reg_uac_t **reg, str *attr, str *val);

#endif
