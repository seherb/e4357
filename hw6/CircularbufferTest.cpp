#include "CircularBuffer.h"
int main(void)
{
	CircularBuffer *pQue;
	CircularBufferInit(&pQue, 16);
	KeyType data = 50;
	int completed = 0;
	for (int i = 0; i < 15; i++)
	{
		completed=CircularBufferEnque(pQue, data + i);
		if (completed == 0)
			printf("Buffer is full\n");
	}
	CircularBufferPrint(pQue);
	for (int i = 0; i < 5; i++)
	{
		CircularBufferDeque(pQue,&data);
		printf("Dequed data: %d\n",data);
	}
	data = 100;
	for (int i = 0; i < 6; i++)
	{
		completed = CircularBufferEnque(pQue, data + i);
		if (completed == 0)
			printf("Buffer is full\n");
	}

	CircularBufferPrint(pQue);
	CircularBufferFree(pQue);
	return 0;
}