#pragma once
#include <stdlib.h>
#include <string.h>

typedef struct voidVector {
	void** arr;
	int size;
} voidVector;

/* Initiates a voidVector pointer. 
 * A voidVector object must be a pointer to use the freeVector and initVector methods. Otherwise, 
 * user must allocate memory by themselves for the voidVector. Vectors instantiated without using 
 * this method and without being pointers are not supported by the following voidVector methods. 
 * Use pointers.
 *
 * Initializes the voidVector's array to NULL and the size to 0. 
 * Allocates memory using malloc, and as such, memory that has been instantiated without being 
 * filled should not be relied on to hold any certain value, such as 0, unless memset has been 
 * explicitly called.
 *
 * Usage:
 * 	voidVector *my_voidVector = initVoidVector();
 */
voidVector* initVoidVector()
{
	voidVector *v = (voidVector*)malloc(sizeof(void**) + sizeof(int));
	v->arr = NULL;
	v->size = 0;
	return v;
}

/* Frees any voidVector instantiated using the initVector() method.
 * Frees both voidVector array and the struct itself.
 * Do not call if voidVector was not instantiated with initVector because the behavior
 * will be undefined.
 */
void freeVoidVector(voidVector *v)
{
	free(v->arr);
	free(v);
}

/* Adds an integer to the last position of the voidVector, adding a position there for said integer.
 * Increases the size value of the voidVector as well.
 */
void pushBackVoidVector(voidVector *v, void* value)
{
	void** temp = (void**)malloc(sizeof(void*)*v->size);
	memcpy(temp, v->arr, sizeof(void*)*v->size);
	free(v->arr);
	v->size++;
	v->arr = (void**)malloc(sizeof(void*)*v->size);
	memcpy(v->arr, temp, sizeof(void*)*(v->size - 1));
	v->arr[v->size - 1] = value;
	free(temp);
}

/* Inserts an integer to the specified index, shifting all values after it back one space. Increases
 * the size of the voidVector object. 
 *
 * Example: 
 * Vector1: [1, 2, 3, 4, 5] Before insertion
 * 
 * insertVoidVector(Vector1, 2, 6);
 *
 * Vector1: [1, 2, 6, 3, 4, 5] After insertion
 */
void insertVoidVector(voidVector *v, int index, void* value)
{
	void** temp = (void**)malloc(sizeof(void*)*(v->size));
	memcpy(temp, v->arr, sizeof(void*)*(v->size));
	free(v->arr);
	v->size++;
	v->arr = (void**)malloc(sizeof(void*)*v->size);
	memcpy(v->arr, temp, sizeof(void*)*(v->size - 1));
	for(int i = v->size - 1; i > index; i--)
	{
		v->arr[i] = temp[i-1];
	}
	v->arr[index] = value;
	free(temp);
}

/* Sets a specific index in the voidVector to a specific value
 */
void assignVoidVector(voidVector *v, int index, void* value)
{
	if(index < v->size && index >= 0)
		v->arr[index] = value;
}

/* Removes an index from the voidVector. Shifts all value after it left one space
 * and decreases the size;
 */
void eraseVoidVector(voidVector *v, int index)
{
	// Error Checking
	if(index >= v->size || index < 0)
		return;
	
	// Temporary Arrays
	void** temp = (void**)malloc(sizeof(void*)*v->size);
	memcpy(temp, v->arr, sizeof(void*)*v->size);

	// Update Actual Array
	free(v->arr);
	v->size--;
	v->arr = (void**)malloc(sizeof(void*)*v->size);

	// Move Information
	memcpy(v->arr, temp, sizeof(void*)*index);
	memcpy(v->arr+index, temp+index+1, sizeof(void*)*(v->size - index));

	// Free Temp
	free(temp);
}

/* Given an amount of elements to be copied from a source voidVector to a destination voidVector,
 * if the amount of elements is larger than what is in the source voidVector, the amount of
 * elemenents transferred is the size of the source voidVector. Otherwise, the amount
 * transferred is equal to the given size. The destination voidVector is always cleared, and 
 * reallocated before being filled, so that the two voidVectors given are exactly the same, save
 * for their memory address.
 */
void copyVoidVector(voidVector *src, voidVector *dst, size_t size)
{
	if(size > 0 && size <= src->size && size)
	{
		free(dst->arr);
		dst->arr = (void**)malloc(sizeof(void*)*size);
		dst->size = size;
		memcpy(dst, src, size);
	}
	else if(size > 0 && size > src->size)
	{
		free(dst->arr);
		dst->arr = (void**)malloc(sizeof(void*)*src->size);
		dst->size = src->size;
		memcpy(dst, src, src->size);
	}
}

/* Same as deleteVector() methods, except it only works on the last element of the voidVector.
 */
void* popBackVoidVector(voidVector *v)
{
	void* temp = (v->size > 0) ? v->arr[v->size-1] : 0;
	eraseVoidVector(v, v->size-1);
	return temp;
}

/* Swaps the memory address of two given voidVectors. Doesn't affect any information stored by voidVectors.
 */
void swapVoidVector(voidVector *v1, voidVector *v2)
{
	void** tmp = v1->arr;
	v1->arr = v2->arr;
	v2->arr = tmp;
}

/* Gets the value of element at given index. Returns 0 if the index is invalid.
 */
void* atVoidVector(voidVector *v, int index)
{
	return (v->size > index && index >= 0) ? v->arr[index] : 0;
}

/* Gets the value of the first element in the voidVector. Returns 0 if the voidVector is of size 0.
 */
void* frontVoidVector(voidVector *v)
{
	return (v->size > 0) ? v->arr[0] : 0;
}

/* Gets the value of the last  element in the voidVector. Returns 0 if the voidVector is of size 0.
 */
void* backVoidVector(voidVector *v)
{
	return (v->size > 0) ? v->arr[v->size-1] : 0; 
}

/* Sets all elements in a voidVector to 0, then frees the memory.
 */
void clearVoidVector(voidVector *v)
{
	memset(v->arr, 0, sizeof(void*)*v->size);
	free(v->arr);
	v->arr = NULL;
	v->size = 0;
}

/* Returns the pointer to the voidVector's data array.
 */
void** dataVoidVector(voidVector *v)
{
	return v->arr;
}
