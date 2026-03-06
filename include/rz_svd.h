// SPDX-FileCopyrightText: 2020 Aswin C (officialcjunior) <realc@protonmail.com>, 2026 Muqeet Salam <muqeetsalam168@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef RZ_SVD_H
#define RZ_SVD_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__GNUC__) && __GNUC__ >= 4
#define SVD_LIB_EXPORT __attribute__((visibility("default")))
#elif defined(_WIN32)
#define SVD_LIB_EXPORT __declspec(dllexport)
#else
#define SVD_LIB_EXPORT
#endif

typedef struct svd_list_node_t {
	void *data;
	struct svd_list_node_t *next;
} SvdListNode;

typedef void (*SvdListFree)(void *);

typedef struct svd_list_t {
	SvdListNode *head;
	SvdListNode *tail;
	SvdListFree free_fn;
	size_t length;
} SvdList;

#define svd_list_foreach(list, node, val) \
	for (node = (list) ? (list)->head : NULL; \
		node && ((val) = (node)->data, 1); \
		node = (node)->next)

typedef struct rz_svd_interrupt_t {
	char *name;
	uint32_t value;
	char *description;
} RzSvdInterrupt;

typedef struct rz_svd_device_t {
	char *name;
	char *vendor;
	char *version;
	uint32_t address_width;
	uint32_t data_width;
	SvdList *interrupts;
} RzSvdDevice;

typedef struct rz_svd_context_t {
	char *file_path;
	SvdList *devices;
} RzSvdContext;

SVD_LIB_EXPORT RzSvdContext *rz_svd_new(const char *svd_path);
SVD_LIB_EXPORT void rz_svd_free(RzSvdContext *ctx);
SVD_LIB_EXPORT RzSvdDevice *rz_svd_get_device(RzSvdContext *ctx, const char *device_name);
SVD_LIB_EXPORT RzSvdInterrupt *rz_svd_device_get_interrupt(RzSvdDevice *device, uint32_t index);
SVD_LIB_EXPORT char *rz_svd_find_file(const char *base_path, const char *device_name);

#ifdef __cplusplus
}
#endif

#endif // RZ_SVD_H
