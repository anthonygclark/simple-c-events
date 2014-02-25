#include "events.h"
#include <string.h>
#include <stdio.h>


void myEventHandler(void* userdata){
  printf("I got called\n");
}


int main(int argc, char** argv){

  EventQueue_t* queue = createEventQueue(3, 15);
 
  EventCallback callback = myEventHandler;

  addEvent(queue, 2, & callback);

  triggerEvent(queue, 0, NULL);
  triggerEvent(queue, 1, NULL);
  triggerEvent(queue, 2, NULL);

  freeEventQueue(queue);   


  return 0;
}


