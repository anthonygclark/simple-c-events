
#include "events.h"

#ifndef NULL
#define NULL 0x0
#endif



void cleanEventQueue(EventQueue_t* queue, unsigned int max_signals, unsigned int max_handlers){
  memset(queue->signal_pool, 0, max_signals * max_handlers * sizeof(EventCallback));
  queue->max_signal = max_signals;
  queue->max_handlers = max_handlers;
}



EventQueue_t* createEventQueue(unsigned int max_signals, unsigned int max_handlers){
  EventQueue_t* queue = malloc(sizeof(EventQueue_t));
  queue->signal_pool = malloc(max_signals * max_handlers * sizeof(EventCallback));
  cleanEventQueue(queue, max_signals, max_handlers);
  return queue;
}


void freeEventQueue(EventQueue_t* queue){
  cleanEventQueue(queue, queue->max_signal, queue->max_handlers);
  free(queue->signal_pool);
  free(queue);
}



int addEvent(EventQueue_t* queue, unsigned int signal, EventCallback* callback){
  int i;
  int base = (signal * (queue->max_handlers));

  for(i = 0; i < queue->max_handlers; i++){
    if(queue->signal_pool[base + i] == NULL){
      queue->signal_pool[base + i] = callback;
      return i;
    }
  }

  return -1;
}


int removeEvent(EventQueue_t* queue, unsigned int signal, EventCallback* callback){
  int i;
  int base = (signal * (queue->max_handlers));

  for(i = 0; i < queue->max_handlers; i++){
    if(queue->signal_pool[base + i] == callback){
      queue->signal_pool[base + i] = NULL;
      return i;
    }
  }

  return -1;
}

int triggerEvent(EventQueue_t* queue, unsigned int signal, void *userdata){
  int i, total = 0;
  int base = (signal * (queue->max_handlers));

  for(i = 0; i < queue->max_handlers; i++){
    if(NULL != queue->signal_pool[base + i]){
      total++;
      (*(queue->signal_pool[base + i]))(userdata);
    }
  }

  return total;
}



