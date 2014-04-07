#include <string.h>
#include <stdio.h>
#include "events.h"

void myEventHandler(void* userdata)
{
  printf("I got called: %s\n", (char*) userdata);
}


typedef enum EVENTSTATES {
  EVENT_OPEN = 0,
  EVENT_READ,
  EVENT_CLOSE
} EVENTSTATE_T;


int main(int argc, char** argv){

  EventQueue_t* queue = createEventQueue(3, 15);
 
  // Register an event to the "READ" (second phase) event stack
  addEvent(queue, EVENT_OPEN, myEventHandler);
  addEvent(queue, EVENT_READ, myEventHandler);
  addEvent(queue, EVENT_CLOSE, myEventHandler);

  triggerEvent(queue, EVENT_OPEN, "first");
  triggerEvent(queue, EVENT_READ, "second");
  triggerEvent(queue, EVENT_CLOSE, "third");

  freeEventQueue(queue);   


  return 0;
}


