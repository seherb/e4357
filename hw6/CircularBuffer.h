#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __CIRCULAR_BUFFER
#define __CIRCULAR_BUFFER

/* Implement a circularbuffer library with the following API interface */

/**< Circular Buffer Types */
typedef unsigned char INT8U;
typedef INT8U KeyType;
typedef struct {
	INT8U writePointer; /**< write pointer */
	INT8U readPointer;  /**< read pointer */
	INT8U size;         /**< size of circular buffer */
	INT8U mask;         /**< bit Mask of circular buffer size*/
	KeyType keys[0];    /**< Element of ciruclar buffer */
} CircularBuffer;

/**< Init Ciruclar Buffer */ 
CircularBuffer* CircularBufferInit(CircularBuffer** pQue, int size)
{
	int sz = size*sizeof(KeyType) + sizeof(CircularBuffer);
	*pQue = (CircularBuffer*)malloc(sz);
	if (*pQue)
	{
		printf("Init CircularBuffer: keys[%d] (%d)\n", size, sz); 
		if (!(size & (size - 1)))
		{
			(*pQue)->size = size;
			(*pQue)->mask = size - 1;
			(*pQue)->writePointer = 0;
			(*pQue)->readPointer = 0; 
		}
		else
		{
			printf("Error Size:%d is not power of TWO!\n", size);
		} 
	}
	return *pQue;
}
void CircularBufferFree(CircularBuffer*pQue)
{
	memset((void *)pQue, 0, sizeof(CircularBuffer));
	free((void *)pQue);
}
inline int CircularBufferIsFull(CircularBuffer* que)
{
	return (que->readPointer == ((que->writePointer + 1)&que->mask));
}
inline int CircularBufferIsEmpty(CircularBuffer* que)
{
	return (que->writePointer == que->readPointer );
}
inline int CircularBufferEnque(CircularBuffer* que, KeyType k)
{ 	
	if (CircularBufferIsFull(que))
	{
		return 0;
	}
	que->keys[que->writePointer] = k;
	que->writePointer++;
	que->writePointer &= que->mask;
	return 1;
}
inline int CircularBufferDeque(CircularBuffer* que, KeyType* pK)
{ 
	if (CircularBufferIsEmpty(que))
	{
		return 0;
	}
	*pK = que->keys[que->readPointer++];
	que->readPointer &= que->mask;
	return 1;
}
inline int CircularBufferPrint(CircularBuffer* que)
{ 
	int size = 0;
	for (int i = que->readPointer; i != que->writePointer; i = (i + 1)&que->mask)
	{
		printf("%d ", que->keys[i]);
		size++;
	}
	printf("\n");
	return size;
}

#endif
