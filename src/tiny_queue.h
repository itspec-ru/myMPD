/*
 SPDX-License-Identifier: GPL-2.0-or-later
 myMPD (c) 2018-2021 Juergen Mang <mail@jcgames.de>
 https://github.com/jcorporation/mympd
*/

#ifndef __TINY_QUEUE_H__
#define __TINY_QUEUE_H__

typedef struct tiny_msg_t {
    void *data;
    long id;
    time_t timestamp;
    struct tiny_msg_t *next;
} tiny_msg_t;

typedef struct tiny_queue_t {
    int length;
    struct tiny_msg_t *head;
    struct tiny_msg_t *tail;
    pthread_mutex_t mutex;
    pthread_cond_t wakeup;
} tiny_queue_t;

tiny_queue_t *tiny_queue_create(void);
void tiny_queue_free(tiny_queue_t *queue);
int tiny_queue_push(struct tiny_queue_t *queue, void *data, long id);
void *tiny_queue_shift(struct tiny_queue_t *queue, int timeout, long id);
void *tiny_queue_expire(tiny_queue_t *queue, time_t max_age);
unsigned tiny_queue_length(struct tiny_queue_t *queue, int timeout);
#endif
