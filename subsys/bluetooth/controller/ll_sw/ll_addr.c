/*
 * Copyright (c) 2016-2018 Nordic Semiconductor ASA
 * Copyright (c) 2016 Vinayak Kariappa Chettimada
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stddef.h>
#include <string.h>

#include <zephyr/types.h>
#include <bluetooth/hci.h>
#include <bluetooth/controller.h>
#include <misc/slist.h>

#include "util/util.h"

#include "ll_sw/pdu.h"
#include "ll_sw/ctrl.h"

static u8_t pub_addr[BDADDR_SIZE];
static u8_t rnd_addr[BDADDR_SIZE];

u8_t *ll_addr_get(u8_t addr_type, u8_t *bdaddr)
{
	if (addr_type > 1) {
		return NULL;
	}

	if (addr_type) {
		if (bdaddr) {
			memcpy(bdaddr, rnd_addr, BDADDR_SIZE);
		}

		return rnd_addr;
	}

	if (bdaddr) {
		memcpy(bdaddr, pub_addr, BDADDR_SIZE);
	}

	return pub_addr;
}

u32_t ll_addr_set(u8_t addr_type, u8_t const *const bdaddr)
{
	if (ll_adv_is_enabled() ||
	    (ll_scan_is_enabled() & (BIT(1) | BIT(2)))) {
		return BT_HCI_ERR_CMD_DISALLOWED;
	}

	if (addr_type) {
		memcpy(rnd_addr, bdaddr, BDADDR_SIZE);
	} else {
		memcpy(pub_addr, bdaddr, BDADDR_SIZE);
	}

	return 0;
}

void bt_ctlr_set_public_addr(const u8_t *addr)
{
    (void)memcpy(pub_addr, addr, sizeof(pub_addr));
}
