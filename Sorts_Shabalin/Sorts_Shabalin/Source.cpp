#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#define SIZE 100000

// ��� ��������� ���������
#define BORDER 200000

// rand() % BORDER ����� � ���������������� ��������� �� 0 �� BORDER

void menu() {

	printf("\n 1 - insertsSort\n");
	printf("\n 2 - Shell_sort\n");
	printf("\n 3 - countingSort\n");
	printf("\n 4 - bubbleSort\n");
	printf("\n 5 - shekerSort\n");
	printf("\n 6 - quickSort\n");
	printf("\n 7 - selection_sort\n");
	printf("\n 8 - heapSort\n");
	printf("\n 9 - merge_sort\n");
	printf("\n 0 - exit\n");

}

void create_rand_array(int* rand_arr, int array_size) {

	for (int i = 0; i < array_size; i++) {
		rand_arr[i] = rand() % BORDER;
	}
}

void print_array(int* rand_arr, int array_size) {

	int key;

	printf("\nDo you want to print array?\n1 - Yes\n2 - No\n");
	scanf("%d", &key);

	if (key == 1) {
		for (int i = 0; i < array_size; i++) {
			printf("%d ", rand_arr[i]);
		}
	}
}

int sorting_by_inserts(int* rand_arr, int array_size) {

	int i = 0;
	int j = 1;
	int buffer;

	// ���-�� ������������
	double count = 0;

	// ��������� �� �������
	for (; j < array_size; j++) {

		// ������� ����� j
		i = j - 1;

		// ���� ���������� �������
		if (rand_arr[i] > rand_arr[j]) {

			// ���������� � ����� �������, ������� ������� �������
			buffer = rand_arr[j];

			// ���� ���� �������� ������� �� ������, ������� ������� ������ ��� �������� �� ����� ��������������� �����
			while (i >= 0 && rand_arr[i] > buffer) {

				count++;

				// ����� �������� ������
				rand_arr[i + 1] = rand_arr[i];

				// �������� ���������� ��������
				i--;
			}

			// ���� ���� �����������, ������ ������� �����, ���� �������� ������� �� ������
			rand_arr[i + 1] = buffer;
		}
	}

	return count;
}

int Shell_sort(int* rand_arr, int array_size) {

	int step = array_size;
	int buffer;

	// ���-�� ������������
	double count = 0;

	// ��������� ������ � ����� 1
	while (step != 1) { 

		// ��� ������ ��� ����������� � 2 ����
		step = step / 2;
		
		// ���������� ��������� �� �������� �������
		int i = 0;
		int j = i + step;

		while (j != array_size) {

			// ������� �������� ���� ��� �� �� ����� ����� � �������� ��� ��� �������� ���� �� ������� � ����� �������
			for (; i >= 0 && rand_arr[i] > rand_arr[i + step]; i = i - step) {

				// ������ ������� ��� �������������
				buffer = rand_arr[i];
				rand_arr[i] = rand_arr[i + step];
				rand_arr[i + step] = buffer;
				count++;
			}

			// ���������� ��������� i �� ������� ��� ���� ������� ��������������
			i = j - step;

			i++;
			j++;

		}
	}
	
	return count;
}

void countingSort(int* rand_arr, int array_size, int k) {

	// ������ ��������������� ������ �������� k+1
	int* c = (int*)calloc((k+1), sizeof(int));
	 
	// ��������� ��������������� ������ (����� ������ = �����, ����������� ������� ��� ������)
	for (int i = 0; i < array_size; ++i) {	
		++c[rand_arr[i]];
	}

	// ��������� �� ������� ������ ������� rand_arr
	int ptr = 0;

	// ��� ������ ������ ����������� ����, ������� ���������� � �������� ������ ��������������� ����� ������� ���, ������� ��� �����������
	for (int i = 0; i < k + 1; ++i) {
		for (int j = 0; j < c[i]; ++j) {
			rand_arr[ptr++] = i;
		}
	}

	free(c);
}

int bubbleSort(int* rand_arr, int array_size) {

	int buffer;
	double count = 0;

	// ��� ���� ���������
	for (int i = 0; i < array_size - 1; i++) {
	
		for (int j = (array_size - 1); j > i; j--) { // �������� � �����
		
			if (rand_arr[j - 1] > rand_arr[j]) { // ���������� ����������� ������� ���������
	
				buffer = rand_arr[j - 1]; // ������� �������� (��� "���������")
				rand_arr[j - 1] = rand_arr[j];
				rand_arr[j] = buffer;
				count++;
			}
		}
	}

	return count;

}

int shekerSort(int* rand_arr, int array_size) {

	double count = 0;

	int left = 0, right = array_size - 1; // ����� � ������ ������� ����������� ������� �������
	int flag = 1;  // ���� ������� �����������

	// ���������� ����� ���� ����� ������� �� �������� � ������
	// � ���� � ������� ������� �����������
	while ((left < right) && flag > 0) {

		flag = 0;
		for (int i = left; i < right; i++) {  //��������� ����� �������

			if (rand_arr[i] > rand_arr[i + 1]) {  // ���� ��������� ������� ������ ��������,
			            // ������ �� �������
				double t = rand_arr[i];
				rand_arr[i] = rand_arr[i + 1];
				rand_arr[i + 1] = t;
				flag = 1;      // ����������� � ���� ����� ����
				count++;
			}
		}
		right--; // �������� ������ ������� �� ���������� �������
		for (int i = right; i > left; i--) { //��������� ������ ������
		
			if (rand_arr[i - 1] > rand_arr[i]) { // ���� ���������� ������� ������ ��������,
			           // ������ �� �������
				double t = rand_arr[i];
				rand_arr[i] = rand_arr[i - 1];
				rand_arr[i - 1] = t;
				flag = 1;    // ����������� � ���� ����� ����
				count++;
			}
		}
		left++; // �������� ����� ������� �� ��������� �������
	}

	return count;
}

void quickSort(int* rand_arr, int left, int right) {

	int pivot; // ����������� �������

	int l_hold = left; //����� �������
	int r_hold = right; // ������ �������

	pivot = rand_arr[left];

	while (left < right) { // ���� ������� �� ����������

		while ((rand_arr[right] >= pivot) && (left < right))
			right--; // �������� ������ ������� ���� ������� [right] ������ [pivot]

		if (left != right) { // ���� ������� �� ���������� 
			rand_arr[left] = rand_arr[right]; // ���������� ������� [right] �� ����� ������������
			left++; // �������� ����� ������� ������
		}

		while ((rand_arr[left] <= pivot) && (left < right))
			left++; // �������� ����� ������� ���� ������� [left] ������ [pivot]

		if (left != right) { // ���� ������� �� ����������
			rand_arr[right] = rand_arr[left]; // ���������� ������� [left] �� ����� [right]
			right--; // �������� ������ ������� �����
		}
	}

	rand_arr[left] = pivot; // ������ ����������� ������� �� ������ �����

	pivot = left; // �������� ����� ����������� �������

	left = l_hold;	// ���������� ��������� �� �������� �������
	right = r_hold;

	if (left < pivot) // ���������� �������� ���������� ��� ����� � ������ ����� �������
		quickSort(rand_arr, left, pivot - 1);
	if (right > pivot)
		quickSort(rand_arr, pivot + 1, right);
}

void selection_sort(int* rand_arr, int array_size) {

	int buffer;

	for (int i = 0; i < array_size - 1; i++) {
	
		int min_index = i; // �������� ������� ����������� �������

		for (int j = i + 1; j < array_size; j++) { // ������� �� ���������� �������� ��������� ������
		
			if (rand_arr[j] < rand_arr[min_index]) { // ���� ������� ������� ������ ����� ���������� - ������ �� �����������
			
				min_index = j;
			}
		}

		if (min_index != i) { // ���� ����������� ������� ��������� 
		
			// ������ ��� ������� � ������� ���������
			buffer = rand_arr[i]; 
			rand_arr[i] = rand_arr[min_index];
			rand_arr[min_index] = buffer;
		}
	}
}

// ��������������� ������� ��� ���������� �����
void heapify(int* rand_arr, int array_size, int i) {

	int buffer;

	// �������������� ������������ ������� ��� ������
	int largest = i;

	int l = 2 * i + 1; // ����� = 2*i + 1
	int r = 2 * i + 2; // ������ = 2*i + 2

	// ���� ����� �������� ������� ������ �����
	if (l < array_size && rand_arr[l] > rand_arr[largest])
		largest = l;

	// ���� ������ �������� ������� ������ �����
	if (r < array_size && rand_arr[r] > rand_arr[largest])
		largest = r;

	// ���� ������� ������� ������ ����� - ������ �� ������
	if (largest != i) {
	
		buffer = rand_arr[i];
		rand_arr[i] = rand_arr[largest];
		rand_arr[largest] = buffer;

		// ���������� �����������, �� ������ ���� � �������� ��������� ���� ���� ��������
		heapify(rand_arr, array_size, largest);
	}
}

void heapSort(int* rand_arr, int array_size) {

	int buffer;

	// ���������� max-����
	for (int i = array_size / 2 - 1; i >= 0; i--)
		heapify(rand_arr, array_size, i);

	// ���������� max-����
	for (int i = array_size - 1; i >= 0; i--) {
	
		// ���������� ������� ������ � �����
		buffer = rand_arr[i];
		rand_arr[i] = rand_arr[0];
		rand_arr[0] = buffer;

		// ������������������ ���� �� ���������� �������
		heapify(rand_arr, i, 0);
	}
}

void merge_sort(int* rand_arr, int* aux, int left, int right) {

	// ��������� rand_arr[left .. right]�������� ���� 1 ������� (������� �����������), ���� ��� ��������� (������� ����� �����������)
	if (right <= left) {
		return;    
	}

	// ��������� ������ �� 2 ���������� ����� ���������� ����� rand_arr[left ..mid] � rand_arr[mid + 1 ..right]
	int mid = (left + right) / 2;


	// ���������� ��������� rand_arr[left ..mid] � rand_arr[mid + 1 ..right]
	merge_sort(rand_arr, aux, left, mid);
	merge_sort(rand_arr, aux, mid + 1, right);

	// ��������� ����� ���� ���������� 2 ��������������� ����������:

	// ��������� �� ������ ������ ����������
	int pointer_left = left;       

	// ��������� �� ������ ������� ����������
	int pointer_right = mid + 1;        
	int k;
	
	// ��������� ��������������� ������
	for (k = left; k <= right; k++) {

		// � ���� ������ ����� ��������� ��������, � ��� ��� �������� ��� ������������� (���������� ������)
		if (pointer_left == mid + 1) {      
			aux[k] = rand_arr[pointer_right];
			pointer_right++;
		}

		// � ���� ������ ������ ��������� ��������, � ��� ��� �������� ��� ������������� (���������� �����)
		else if (pointer_right == right + 1) {        
			aux[k] = rand_arr[pointer_left];
			pointer_left++;
		}

		// ������� �� ������ ���������� ������ �������� �� ������� -> ���������� ��� � ��������������� ������
		else if (rand_arr[pointer_left] < rand_arr[pointer_right]) {        
			aux[k] = rand_arr[pointer_left];
			pointer_left++;
		}

		// ������� �� ������� ���������� ������ �������� �� ������ -> ���������� ��� �� ��������������� ������
		else {        
			aux[k] = rand_arr[pointer_right];
			pointer_right++;
		}
	}

	// ��������� �������� �� ���������������� ������� � ��������
	for (k = left; k <= right; k++) {     
		rand_arr[k] = aux[k];
	}
}

void netural_merge_sort(int* rand_arr, int* aux, int left, int right) {

	int numElements = right;

	int* tmp = (int*)malloc(numElements * sizeof(int));
	int* starts = (int*)malloc(numElements * sizeof(int) + 1);

	// ����������� ������������ ���������� (�������)
	int runCount = 0;

	// � ������ ������� ���������� 0 � ������ ������
	starts[0] = 0;

	// ������� �� ������� �������� ����� �� ������� � ���������� ��������
	for (int i = 1; i <= numElements; i++) {

		// ���� ��������� ������� ��������� (��� ������ ����������) - � ���� ����� ������������� �������
		if (i == numElements || rand_arr[i] < rand_arr[i - 1]) {

			// � ������� ������� �������� ���������� � ������ ����� ���������� ����� �������
			starts[++runCount] = i;
		}
	}

	// Step 2: merge runs, until only 1 run is left
	int from = elements;
	int to = tmp;

	// ���� ��������� ������ ������
	while (runCount > 1) {

		// ������ ����� ������� ���������(�������)
		int newRunCount = 0;

		// Merge two runs each
		for (int i = 0; i < runCount - 1; i += 2) {

			// ���������� ������� ������� ��� ������ ���� ���������
			netural_merge_sort(from, to, starts[i], starts[i + 1], starts[i + 2]);
			starts[newRunCount++] = starts[i];
		}

		// Odd number of runs? Copy the last one
		if (runCount % 2 == 1) {
			int lastStart = starts[runCount - 1];
			System.arraycopy(from, lastStart, to, lastStart,
				numElements - lastStart);
			starts[newRunCount++] = lastStart;
		}

		// Prepare for next round...
		starts[newRunCount] = numElements;
		runCount = newRunCount;

		// Swap "from" and "to" arrays
		int[] help = from;
		from = to;
		to = help;
	}

	// If final run is not in "elements", copy it there
	if (from != elements) {
		System.arraycopy(from, 0, elements, 0, numElements);
	}
}

int main() {

	// ���������� ��������� ���������
	srand((unsigned)time(NULL));

	clock_t start;
	clock_t finish;

	int count = 0;

	int key = 1;
	int rand_arr[SIZE];

	// ��������������� ������ ��� ���������� ��������
	int aux[SIZE];

	while (key != 0) {

		menu();
		scanf("%d", &key);

		switch (key) {

		case 1:
			create_rand_array(rand_arr, SIZE);
			start = clock();
			count = sorting_by_inserts(rand_arr, SIZE);
			finish = clock();
			print_array(rand_arr, SIZE);
			printf("\nTime = %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
			printf("\nCount = %d\n", count);
			break;

		case 2:
			create_rand_array(rand_arr, SIZE);
			start = clock();
			count = Shell_sort(rand_arr, SIZE);
			finish = clock();
			print_array(rand_arr, SIZE);
			printf("\nTime = %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
			printf("\nCount = %d\n", count);
			break;

		case 3:
			create_rand_array(rand_arr, SIZE);
			start = clock();
			countingSort(rand_arr, SIZE, BORDER);
			finish = clock();
			print_array(rand_arr, SIZE);
			printf("\nTime = %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
			break;

		case 4:
			create_rand_array(rand_arr, SIZE);
			start = clock();
			count = bubbleSort(rand_arr, SIZE);
			finish = clock();
			print_array(rand_arr, SIZE);
			printf("\nTime = %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
			printf("\nCount = %d\n", count);
			break;

		case 5:
			create_rand_array(rand_arr, SIZE);
			start = clock();
			count = shekerSort(rand_arr, SIZE);
			finish = clock();
			print_array(rand_arr, SIZE);
			printf("\nTime = %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
			printf("\nCount = %d\n", count);
			break;

		case 6:
			create_rand_array(rand_arr, SIZE);
			start = clock();
			quickSort(rand_arr, 0, SIZE - 1);
			finish = clock();
			print_array(rand_arr, SIZE);
			printf("\nTime = %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
			break;

		case 7:
			create_rand_array(rand_arr, SIZE);
			start = clock();
			selection_sort(rand_arr, SIZE);
			finish = clock();
			print_array(rand_arr, SIZE);
			printf("\nTime = %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
			break;

		case 8:
			create_rand_array(rand_arr, SIZE);
			start = clock();
			heapSort(rand_arr, SIZE);
			finish = clock();
			print_array(rand_arr, SIZE);
			printf("\nTime = %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
			break;

		case 9:
			create_rand_array(rand_arr, SIZE);
			start = clock();
			merge_sort(rand_arr, aux, 0, SIZE - 1);
			finish = clock();
			print_array(rand_arr, SIZE);
			printf("\nTime = %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
			break;

		default:
			break;
		}
	}






}