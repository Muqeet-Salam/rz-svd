// SPDX-FileCopyrightText: 2007-2019 pancake <pancake@nopcode.org>
// SPDX-FileCopyrightText: 2007-2019 alvarofe <alvaro.felipe91@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#include "svd_util.h"

#include <sys/stat.h>

#ifdef _WIN32
#include <io.h>
#define access _access
#define F_OK   0
#else
#include <unistd.h>
#endif

// --- Simple linked list implementation ---

SvdList *svd_list_newf(SvdListFree fn) {
	SvdList *list = RZ_NEW0(SvdList);
	if (!list) {
		return NULL;
	}
	list->free_fn = fn;
	return list;
}

void svd_list_free(SvdList *list) {
	if (!list) {
		return;
	}
	SvdListNode *node = list->head;
	while (node) {
		SvdListNode *next = node->next;
		if (list->free_fn && node->data) {
			list->free_fn(node->data);
		}
		free(node);
		node = next;
	}
	free(list);
}

bool svd_list_append(SvdList *list, void *data) {
	if (!list) {
		return false;
	}
	SvdListNode *node = RZ_NEW0(SvdListNode);
	if (!node) {
		return false;
	}
	node->data = data;
	if (list->tail) {
		list->tail->next = node;
	} else {
		list->head = node;
	}
	list->tail = node;
	list->length++;
	return true;
}

// --- File utilities ---

char *svd_file_slurp(const char *path, size_t *size_out) {
	if (!path) {
		return NULL;
	}
	FILE *f = fopen(path, "rb");
	if (!f) {
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	if (fsize < 0) {
		fclose(f);
		return NULL;
	}
	fseek(f, 0, SEEK_SET);

	char *buf = (char *)malloc((size_t)fsize + 1);
	if (!buf) {
		fclose(f);
		return NULL;
	}
	size_t nread = fread(buf, 1, (size_t)fsize, f);
	fclose(f);

	buf[nread] = '\0';
	if (size_out) {
		*size_out = nread;
	}
	return buf;
}

bool svd_file_exists(const char *path) {
	if (!path) {
		return false;
	}
	return access(path, F_OK) == 0;
}

// --- String utilities ---

char *svd_str_newf(const char *fmt, ...) {
	if (!fmt) {
		return NULL;
	}
	va_list ap;

	va_start(ap, fmt);
	int len = vsnprintf(NULL, 0, fmt, ap);
	va_end(ap);

	if (len < 0) {
		return NULL;
	}

	char *buf = (char *)malloc((size_t)len + 1);
	if (!buf) {
		return NULL;
	}

	va_start(ap, fmt);
	vsnprintf(buf, (size_t)len + 1, fmt, ap);
	va_end(ap);

	return buf;
}
