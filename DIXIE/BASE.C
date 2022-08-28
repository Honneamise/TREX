/* HEADERS */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "DIXIE/BASE.H"

/* DEFINES */
#define BIG_ENDIAN        0
#define LITTLE_ENDIAN     1

#define ARRAY_DEFAULT_SIZE 32

/**************/
/* ENDIANNESS */
/**************/
static unsigned int Endianness()
{
    unsigned int i = 0x01234567;

    return (*((byte *)(&i))) == 0x67;
}

/********/
/* MATH */
/********/
void Swap(int *a, int *b)
{
	int t = *a;
    *a = *b;
    *b = t;
}

/**********/
void Swapf(float *a, float *b)
{
	float t = *a;
    *a = *b;
    *b = t;
}

/**********/
int Min(int a, int b)
{
	return a <= b ? a : b;
}

/**********/
float Minf(float a, float b)
{
	return a <= b ? a : b;
}

/**********/
int Max(int a, int b)
{
	return a >= b ? a : b;
}

/**********/
float Maxf(float a, float b)
{
	return a >= b ? a : b;
}

/**********/
int Rand(int min, int max)
{
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

/**********/
float Randf(float min, float max)
{
	float f = rand() / ((float)(RAND_MAX)+1);

	if (min > max)
		return f * (min - max) + max;
	else
		return f * (max - min) + min;
}

/**********/
int Map(int x, int in_min, int in_max, int out_min, int out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**********/
float Mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**********/
int Clamp(int x, int min, int max)
{
	int t = x < min ? min : x;
	return t > max ? max : t;
}

/**********/
float Clampf(float x, float min, float max)
{
	float t = x < min ? min : x;
	return t > max ? max : t;
}

/**********/
float Radiansf(float degrees)
{
	return (float)(degrees * (float)M_PI / 180.0f);
}

/**********/
float Degreesf(float radians)
{
	return (float)(radians * 180.0f / (float)M_PI);
}

/*********/
/* ARRAY */
/*********/
void ArrayInit(Array *array)
{
	array->size = ARRAY_DEFAULT_SIZE;
	array->elems_count = 0;
	array->elems = calloc(array->size,sizeof(void*));
}

/**********/
void ArrayClose(Array *array, Performer func )
{
	int i = 0;

	if(func!=NULL)
	{
		for(i=0;i<array->elems_count;i++)
		{
			func(array->elems[i]);
		}
	}

	array->size = 0;
	array->elems_count = 0;
	free(array->elems);
	array->elems = NULL;
}

/***********/
void ArrayAdd(Array *array, void *el)
{
	if(array->elems_count== array->size)
	{
		array->size *= 2;
		array->elems = realloc(array->elems,array->size*sizeof(void*));
	}

	array->elems[array->elems_count] = el;

	array->elems_count++;
}

/*********/
void *ArrayRemove(Array* array, int index)
{
	int i = 0;
	void *item = array->elems[index];

	for(i = index; i < array->elems_count-1; i++)
	{
		array->elems[i] = array->elems[i + 1];
	}

	array->elems_count--;

	return item;
}

/***********/
void *ArrayGet(Array *array, int index)
{
	if(index<0 || index>=array->elems_count) { return NULL; }
	
	return array->elems[index];
}

/**********/
void ArrayPerform(Array *array, Performer func)
{
	int i = 0;

	if(func!=NULL)
	{
		for(i=0;i<array->elems_count;i++)
		{
			func(array->elems[i]);
		}
	}
}

/***********/
void ArraySort(Array *array, Sorter func)
{
	qsort(array->elems, array->elems_count, sizeof(void*), (int (*)(const void *, const void *))func);
}

/*********/
/* STACK */
/*********/
void StackInit(Stack *stack)
{
	ArrayInit(stack);
}

/**********/
void StackClose(Stack *stack, void(*func)(void *elem) )
{
	ArrayClose(stack,func);
}

/**********/
void StackPush(Stack *stack, void *elem)
{
	ArrayAdd(stack, elem);
}

/**********/
void *StackPop(Stack *stack)
{
	return ArrayRemove(stack, stack->elems_count-1);
}

/**********/
void *StackPeek(Stack *stack)
{
	return ArrayGet(stack, stack->elems_count-1);
}

/*********/
/* QUEUE */
/*********/
void QueueInit(Queue *queue)
{
	ArrayInit(queue);
}

/**********/
void QueueClose(Queue *queue, void(*func)(void *elem) )
{
	ArrayClose(queue,func);
}

/**********/
void QueueEnq(Queue *queue, void *elem)
{
	ArrayAdd(queue, elem);
}

/**********/
void *QueueDeq(Queue *queue)
{
	return ArrayRemove(queue,0);
}

/**********/
void *QueuePeek(Queue *queue)
{
	return ArrayGet(queue, 0);
}

/***********/
/* BUFFERS */
/***********/
void BufferLoad(char *file, byte **buffer, int *size)
{
	size_t _size = 0;

	FILE *fp = fopen(file, "rb");

	if (fp != NULL)
	{
		fseek(fp, 0, SEEK_END);

		_size = ftell(fp);

		*buffer = malloc( _size * sizeof(byte));

		fseek(fp, 0, SEEK_SET);

		fread(*buffer, _size, 1, fp);

		fclose(fp);
	}

	if(size!=NULL){ *size = (int)_size; }
}

/**********/
byte BufferReadByte(byte **buffer)
{
	byte *buf = &(**buffer);

    byte val = buf[0];

    *buffer += 1;

    return val;
} 

/**********/
short BufferReadShort(byte **buffer)
{
	byte *buf = &(**buffer);

    short val = 0x00;

    if(Endianness()==BIG_ENDIAN)
    {
        val = (buf[0]<<8) | buf[1];
    }
    else
    {
        val = (buf[1]<<8) | buf[0];
    }

    *buffer += 2;

    return val;
} 

/**********/
int BufferReadInt(byte **buffer)
{
	byte *buf = &(**buffer);

    int val = 0x00;
    
    if(Endianness()==BIG_ENDIAN)
    {
        val = (buf[0]<<24) | (buf[1]<<16) | (buf[2]<<8) | buf[3];
        
    }
    else
    {
        val = (buf[3]<<24) | (buf[2]<<16) | (buf[1]<<8) | buf[0];
    }

    *buffer += 4;

    return val;
}

/**********/
float BufferReadFloat(byte **buffer)
{
	byte *buf = &(**buffer);

    float output = 0.0f;

	if(Endianness()==BIG_ENDIAN)
    {
		*((byte*)(&output) + 3) = buf[0];
		*((byte*)(&output) + 2) = buf[1];
		*((byte*)(&output) + 1) = buf[2];
		*((byte*)(&output) + 0) = buf[3];
	}
	else
	{
		*((byte*)(&output) + 3) = buf[3];
		*((byte*)(&output) + 2) = buf[2];
		*((byte*)(&output) + 1) = buf[1];
		*((byte*)(&output) + 0) = buf[0];
	}

    *buffer += 4;

    return output;
}
