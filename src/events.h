/* Simple Events in C */
// vim: ts=2
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef void (*EventCallback)(void *userdata);
/**< Event Callback Function signature */

/** @brief Event Queue Structure */
typedef struct EventQueue {
  unsigned int max_signal;
  /**< The Maximum signals for each listener */  
  unsigned int max_handlers;
  /**< The Maximum amount of listeners */  
  EventCallback* signal_pool;
  /**< Callback list */  
} EventQueue_t;

/**
 * @brief Creates an Event Queue
 * @details Initializes the required memory for the event queue
 * @returns A valid event queue or NULL
 * @param max_signals The Maximum signals for each listener
 * @param max_handlers The Maximum listeners
 */ 
EventQueue_t* createEventQueue(unsigned int max_signals, unsigned int max_handlers);

/**
 * @brief Adds an Event to the Event Queue
 * @param queue The Event queue to add an event to
 * @param signal The signal number to add
 * @param callback The callback function to call on trigger
 * @returns -1 if event cant be added or valid added slot
 */
int addEvent(EventQueue_t* queue, unsigned int signal, EventCallback callback);

/**
 * @brief Removes an Event from the Event Queue
 * @param queue The Event queue to remove an event from
 * @param signal The signal number to remove
 * @param callback The callback function to identify against
 * @returns -1 if event isnt present in the queue, or valid removed slot
 */
int removeEvent(EventQueue_t* queue, unsigned int signal, EventCallback callback);

/**
 * @brief Triggers an Event
 * @param queue The Event queue to search
 * @param signal The signal to call
 * @param userdata Pointer to data to pass to this signal's callback
 * @returns Total events triggered
 */ 
int triggerEvent(EventQueue_t* queue, unsigned int signal, void *userdata);

/**
 * @brief Frees memory associated with the Event Queue
 * @param queue The Queue to free
 */ 
void freeEventQueue(EventQueue_t* queue);
