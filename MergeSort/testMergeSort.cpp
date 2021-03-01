
/* Basic Mergesort implementation
 * Written by Isaiah Knorr
 * 28 Feb 2021
 * 
 * This mergesort test program will generate an int array containing a random
 * number of elements and random values. The array is then sorted using mergesort
 * and the sorted array is displayed. There is a REPEAT flag that can also be set
 * in order to run the test in an infinite loop.
 * 
 * This implementation was based on the tutorial found at
 * https://www.geeksforgeeks.org/merge-sort/
 *

*/

#include <iostream>
#include <limits>
#include <time.h>

using namespace std;

void merge(int thisArray[], int startIndex, int middleIndex, int endIndex) {

	// First, find the size of each array
	int leftSize = middleIndex - startIndex + 1;
	int rightSize = endIndex - middleIndex;

	// Next, crate a copy of the left and right side (uses heap memory because the size is not known at compile time)
	int* leftArray = new int[leftSize] { 0 };
	int* rightArray = new int[rightSize] { 0 };

	// Copy elements into leftArray
	int currentIndex = 0;
	while (currentIndex < leftSize) {
		leftArray[currentIndex] = thisArray[startIndex + currentIndex];
		currentIndex++;
	}

	// Copy elements  into right array
	currentIndex = 0;
	while (currentIndex < rightSize) {
		rightArray[currentIndex] = thisArray[currentIndex + middleIndex + 1];
		currentIndex++;
	}

	// The left and right sides are assumed to be sorted from previous recursions, so can be merged this way

	// Create index for each side, indicates lowest value not already sorted
	int leftIndex = 0;
	int rightIndex = 0;

	for (currentIndex = startIndex; currentIndex <= endIndex; currentIndex++) {
		// Create storage for left and right sides
		int currentLeftValue = INT_MAX;
		int currentRightValue = INT_MAX;

		// Check to see if there are any unsorted elements for each side
		if (leftIndex < leftSize) {
			currentLeftValue = leftArray[leftIndex]; 
		}

		if (rightIndex < rightSize) {
			currentRightValue = rightArray[rightIndex];
		}

		// Now insert lowest of two values and increment appropriate index
		if (currentLeftValue <= currentRightValue) {
			thisArray[currentIndex] = currentLeftValue;
			leftIndex++;
		}
		else {
			thisArray[currentIndex] = currentRightValue;
			rightIndex++;
		}

	}

	// Free up the memory used on the heap
	delete[] leftArray;
	delete[] rightArray;
}

void mergeSort(int thisArray[], int startIndex, int endIndex) {

	// Recursive breaking condition
	if (startIndex >= endIndex) {
		return; // This is what stops the recursion from causing a stack overflow
	}

	// Find the middle index
	int middleIndex = startIndex + (endIndex - startIndex) / 2;

	/* Now split into two pieces where index is: [startIndex:middleIndex] [middleIndex+1:endIndex]
	   and call mergeSort recursively on the two pieces
	*/

	mergeSort(thisArray, startIndex, middleIndex);
	mergeSort(thisArray, middleIndex + 1, endIndex);

	// Now the two pieces have to be put back together in the right order (that is the tricky part)
	merge(thisArray, startIndex, middleIndex, endIndex);

	// Merged and sorted

}

void displayArray(int* thisArray, int arraySize) {
	cout << "[";
	for (int i = 0; i < arraySize; i++) {
		cout << thisArray[i];
		if (i < (arraySize - 1)) {
			cout << ",";
		}
	}
	cout << "]" << endl;
}


int main()
{
	const bool REPEAT = false; // Set to true if you want to run program in an infinite loop

	

	// Repeater loop
	do {
		/* Generate a random number for the size of the array to generate, between 1 - 30
		 * NOTE: This method does not generate a secure pseudorandom number and if you run
		 * this program in a loop you can clearly see how the 'random' numbers only change
		 * every second as the time changes.
		 */
		srand(time(NULL)); 
		int arraySize = (rand() % 30) + 1;
		// Allocate memory for the array (Not known at compile time, so needs dynamic memory)
		int* myArray = new int[arraySize] { 0 };

		// Fill the array with random numbers from -100 - 100
		for (int i = 0; i < arraySize; i++) {
			myArray[i] = (rand() % 201) - 100;
		}

		// Display unsorted element
		cout << "Unsorted array: ";
		displayArray(myArray, arraySize);

		// Mergesort needs to know the index of the beginning and end of the array
		int startIndex = 0;
		int endIndex = arraySize - 1;

		// Now call Mergesort

		mergeSort(myArray, startIndex, endIndex);

		// Display sorted array
		cout << "Sorted Array: ";
		displayArray(myArray, arraySize);
		cout << endl;

		// Free up the heap memory
		delete[] myArray;
	} while (REPEAT);
}
