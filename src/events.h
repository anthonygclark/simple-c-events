/* Simple Events in C */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef void (*EventCallback)(void *userdata);

typedef struct EventQueue {
  unsigned int max_signal;
  unsigned int max_handlers;
  EventCallback* signal_pool;
} EventQueue_t;

EventQueue_t* createEventQueue(unsigned int max_signals, unsigned int max_handlers);

int addEvent(EventQueue_t* queue, unsigned int signal, EventCallback callback);
int removeEvent(EventQueue_t* queue, unsigned int signal, EventCallback callback);
int triggerEvent(EventQueue_t* queue, unsigned int signal, void *userdata);
void freeEventQueue(EventQueue_t* queue);


