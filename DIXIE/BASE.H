#ifndef _BASE
#define _BASE

/* TYPEDEFS */
typedef unsigned char byte;

/********/
/* MATH */
/********/
void 		Swap(int *a, int *b);
void 		Swapf(float *a, float *b);
int 	    Min(int a, int b);
float 		Minf(float a, float b);
int 	    Max(int a, int b);
float 		Maxf(float a, float b);
int 	    Rand(int min, int max);
float 		Randf(float min, float max);
int 	    Map(int x, int in_min, int in_max, int out_min, int out_max);
float 		Mapf(float x, float in_min, float in_max, float out_min, float out_max);
int 	    Clamp(int x, int min, int max);
float 	    Clampf(float x, float min, float max);
float 		Radiansf(float degrees);
float 		Degreesf(float radians);

/*********/
/* ARRAY */
/*********/
/*Example function for Array Sorter prototype :

    int32_t FUNC(void *elem_a, void *elem_b);
    {
		TYPE *a = *(TYPE **)elem_a;
  	    TYPE *b = *(TYPE **)elem_b;
		
		if (a->field < b->field) return -1;
  	    if (a->field > b->field) return +1;

   	    return 0;
	}
*/

typedef struct Array
{
	int 	size;
	int 	elems_count;
	void 	**elems;

} Array;

typedef void (*Performer)(void *elem);
typedef int (*Sorter)(void *elem_a, void *elem_b);

void ArrayInit(Array *array);
void ArrayClose(Array *array, void(*func)(void *elem) );
void ArrayAdd(Array *array, void *elem);
void *ArrayRemove(Array *array, int index);
void *ArrayGet(Array *array, int index);
void ArrayPerform(Array *array, Performer func );
void ArraySort(Array *array, Sorter func);

/*********/
/* STACK */
/*********/
typedef Array Stack;

void StackInit(Stack *stack);
void StackClose(Stack *stack, void(*func)(void *elem) );
void StackPush(Stack *stack, void *elem);
void *StackPop(Stack *stack);
void *StackPeek(Stack *stack);

/*********/
/* QUEUE */
/*********/
typedef Array Queue;

void QueueInit(Queue *queue);
void QueueClose(Queue *queue, void(*func)(void *elem) );
void QueueEnq(Queue *queue, void *elem);
void *QueueDeq(Queue *queue);
void *QueuePeek(Queue *queue);

/***********/
/* BUFFERS */
/***********/
void BufferLoad(char *file, byte **buffer, int *size);
byte BufferReadByte(byte **buffer);
short BufferReadShort(byte **buffer);
int BufferReadInt(byte **buffer);
float BufferReadFloat(byte **buffer);

#endif