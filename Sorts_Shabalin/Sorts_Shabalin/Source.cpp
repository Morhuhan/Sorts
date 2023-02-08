#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#define SIZE 100000

// Для сорировки подсчетом
#define BORDER 200000

// rand() % BORDER вызов в ПОЛЬЗОВАТЕЛЬСКОМ диапазона от 0 до BORDER

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

	// Кол-во перестановок
	double count = 0;

	// Двигаемся по массиву
	for (; j < array_size; j++) {

		// Элемент перед j
		i = j - 1;

		// Если нарушается порядок
		if (rand_arr[i] > rand_arr[j]) {

			// Записываем в буфер элемент, который нарушил порядок
			buffer = rand_arr[j];

			// Ищем куда вставить элемент из буфера, попутно сдвигая вправо все элементы из левой отсортированной части
			while (i >= 0 && rand_arr[i] > buffer) {

				count++;

				// Сдвиг элемента вправо
				rand_arr[i + 1] = rand_arr[i];

				// Проверка следующего элемента
				i--;
			}

			// Если цикл прекртаился, значит найдено место, куда вставить элемент из буфера
			rand_arr[i + 1] = buffer;
		}
	}

	return count;
}

int Shell_sort(int* rand_arr, int array_size) {

	int step = array_size;
	int buffer;

	// Кол-во перестановок
	double count = 0;

	// Последний проход с шагом 1
	while (step != 1) { 

		// Шаг каждый раз уменьшается в 2 раза
		step = step / 2;
		
		// Возвращаем указатели на исходные позиции
		int i = 0;
		int j = i + step;

		while (j != array_size) {

			// Свапаем элементы если они не на своем месте и пытаемся еще раз свапнуть пока не упремся в левую границу
			for (; i >= 0 && rand_arr[i] > rand_arr[i + step]; i = i - step) {

				// Меняем местами при необходимости
				buffer = rand_arr[i];
				rand_arr[i] = rand_arr[i + step];
				rand_arr[i + step] = buffer;
				count++;
			}

			// Возвращаем указатель i на позицию где было найдено несоответствие
			i = j - step;

			i++;
			j++;

		}
	}
	
	return count;
}

void countingSort(int* rand_arr, int array_size, int k) {

	// Вводим вспомогательный массив размером k+1
	int* c = (int*)calloc((k+1), sizeof(int));
	 
	// Заполняем вспомогательный массив (номер ячейки = числу, колличество которых она хранит)
	for (int i = 0; i < array_size; ++i) {	
		++c[rand_arr[i]];
	}

	// Указатель на текущую ячейку массива rand_arr
	int ptr = 0;

	// Для каждой ячейки запускается цикл, который записывает в исходный массив соответствующее число столько раз, сколько оно встречалось
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

	// Для всех элементов
	for (int i = 0; i < array_size - 1; i++) {
	
		for (int j = (array_size - 1); j > i; j--) { // Начинаем с конца
		
			if (rand_arr[j - 1] > rand_arr[j]) { // Постепенно увеличиваем область сравнения
	
				buffer = rand_arr[j - 1]; // Свапаем элемента (они "всплывают")
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

	int left = 0, right = array_size - 1; // левая и правая границы сортируемой области массива
	int flag = 1;  // флаг наличия перемещений

	// Выполнение цикла пока левая граница не сомкнётся с правой
	// и пока в массиве имеются перемещения
	while ((left < right) && flag > 0) {

		flag = 0;
		for (int i = left; i < right; i++) {  //двигаемся слева направо

			if (rand_arr[i] > rand_arr[i + 1]) {  // если следующий элемент меньше текущего,
			            // меняем их местами
				double t = rand_arr[i];
				rand_arr[i] = rand_arr[i + 1];
				rand_arr[i + 1] = t;
				flag = 1;      // перемещения в этом цикле были
				count++;
			}
		}
		right--; // сдвигаем правую границу на предыдущий элемент
		for (int i = right; i > left; i--) { //двигаемся справа налево
		
			if (rand_arr[i - 1] > rand_arr[i]) { // если предыдущий элемент больше текущего,
			           // меняем их местами
				double t = rand_arr[i];
				rand_arr[i] = rand_arr[i - 1];
				rand_arr[i - 1] = t;
				flag = 1;    // перемещения в этом цикле были
				count++;
			}
		}
		left++; // сдвигаем левую границу на следующий элемент
	}

	return count;
}

void quickSort(int* rand_arr, int left, int right) {

	int pivot; // разрешающий элемент

	int l_hold = left; //левая граница
	int r_hold = right; // правая граница

	pivot = rand_arr[left];

	while (left < right) { // пока границы не сомкнулись

		while ((rand_arr[right] >= pivot) && (left < right))
			right--; // сдвигаем правую границу пока элемент [right] больше [pivot]

		if (left != right) { // если границы не сомкнулись 
			rand_arr[left] = rand_arr[right]; // перемещаем элемент [right] на место разрешающего
			left++; // сдвигаем левую границу вправо
		}

		while ((rand_arr[left] <= pivot) && (left < right))
			left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]

		if (left != right) { // если границы не сомкнулись
			rand_arr[right] = rand_arr[left]; // перемещаем элемент [left] на место [right]
			right--; // сдвигаем правую границу влево
		}
	}

	rand_arr[left] = pivot; // Ставим разрешающий элемент на нужное место

	pivot = left; // Выбираем новый разрешающий элемент

	left = l_hold;	// Возвращаем указатели на исходные позиции
	right = r_hold;

	if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
		quickSort(rand_arr, left, pivot - 1);
	if (right > pivot)
		quickSort(rand_arr, pivot + 1, right);
}

void selection_sort(int* rand_arr, int array_size) {

	int buffer;

	for (int i = 0; i < array_size - 1; i++) {
	
		int min_index = i; // Выбираем текущий минимальный элемент

		for (int j = i + 1; j < array_size; j++) { // Начиная со следующего элемента пробегаем массив
		
			if (rand_arr[j] < rand_arr[min_index]) { // Если находим элемент меньше ранее выбранного - теперь он минимальный
			
				min_index = j;
			}
		}

		if (min_index != i) { // Если минимальный элемент обновился 
		
			// Меняем его местами с текущим элементом
			buffer = rand_arr[i]; 
			rand_arr[i] = rand_arr[min_index];
			rand_arr[min_index] = buffer;
		}
	}
}

// Вспомогательная функция для сортировки кучей
void heapify(int* rand_arr, int array_size, int i) {

	int buffer;

	// Инициализируем родительский элемент как корень
	int largest = i;

	int l = 2 * i + 1; // левый = 2*i + 1
	int r = 2 * i + 2; // правый = 2*i + 2

	// Если левый дочерний элемент больше корня
	if (l < array_size && rand_arr[l] > rand_arr[largest])
		largest = l;

	// Если правый дочерний элемент больше корня
	if (r < array_size && rand_arr[r] > rand_arr[largest])
		largest = r;

	// Если нашелся элемент больше корня - теперь он корень
	if (largest != i) {
	
		buffer = rand_arr[i];
		rand_arr[i] = rand_arr[largest];
		rand_arr[largest] = buffer;

		// Рекурсивно углубляемся, на случай если у дочрених элементов тоже были дочерние
		heapify(rand_arr, array_size, largest);
	}
}

void heapSort(int* rand_arr, int array_size) {

	int buffer;

	// Построение max-кучи
	for (int i = array_size / 2 - 1; i >= 0; i--)
		heapify(rand_arr, array_size, i);

	// Сортировка max-кучи
	for (int i = array_size - 1; i >= 0; i--) {
	
		// Перемещаем текущий корень в конец
		buffer = rand_arr[i];
		rand_arr[i] = rand_arr[0];
		rand_arr[0] = buffer;

		// Перегруппировываем кучу на измененном массиве
		heapify(rand_arr, i, 0);
	}
}

void merge_sort(int* rand_arr, int* aux, int left, int right) {

	// Подмассив rand_arr[left .. right]содержит либо 1 элемент (который сортируется), либо нет элементов (которые также сортируются)
	if (right <= left) {
		return;    
	}

	// Разбиваем массив на 2 подмассива почти одинаковой длины rand_arr[left ..mid] и rand_arr[mid + 1 ..right]
	int mid = (left + right) / 2;


	// Рекурсивно сортируем rand_arr[left ..mid] и rand_arr[mid + 1 ..right]
	merge_sort(rand_arr, aux, left, mid);
	merge_sort(rand_arr, aux, mid + 1, right);

	// Остальная часть кода объединяет 2 отсортированных подмассива:

	// Указатель на начало левого подмассива
	int pointer_left = left;       

	// Указатель на начало правого подмассива
	int pointer_right = mid + 1;        
	int k;
	
	// Заполняем вспомогательный массив
	for (k = left; k <= right; k++) {

		// В этом случае левый подмассив завершен, и все его элементы уже использованны (дописываем правый)
		if (pointer_left == mid + 1) {      
			aux[k] = rand_arr[pointer_right];
			pointer_right++;
		}

		// В этом случае правый подмассив завершен, и все его элементы уже использованны (дописываем левый)
		else if (pointer_right == right + 1) {        
			aux[k] = rand_arr[pointer_left];
			pointer_left++;
		}

		// Элемент из левого подмассива меньше элемента из правого -> записываем его в вспомогательный массив
		else if (rand_arr[pointer_left] < rand_arr[pointer_right]) {        
			aux[k] = rand_arr[pointer_left];
			pointer_left++;
		}

		// Элемент из правого подмассива меньше элемента из левого -> записываем его во вспомогательный массив
		else {        
			aux[k] = rand_arr[pointer_right];
			pointer_right++;
		}
	}

	// Переносим элементы из вспомогательного массива в основной
	for (k = left; k <= right; k++) {     
		rand_arr[k] = aux[k];
	}
}

void netural_merge_sort(int* rand_arr, int* aux, int left, int right) {

	int numElements = right;

	int* tmp = (int*)malloc(numElements * sizeof(int));
	int* starts = (int*)malloc(numElements * sizeof(int) + 1);

	// Колличетсво получившихся сегемнетов (стартов)
	int runCount = 0;

	// В массив стартов записываем 0 в первую ячейку
	starts[0] = 0;

	// Начиная со второго элемента бежим по массиву и определяем сегменты
	for (int i = 1; i <= numElements; i++) {

		// Если нарушется порядок элементов (или массив закончился) - в этом месте заканчивается сегмент
		if (i == numElements || rand_arr[i] < rand_arr[i - 1]) {

			// В массиве стартов хранится информация с какого места начинается новый сегмент
			starts[++runCount] = i;
		}
	}

	// Step 2: merge runs, until only 1 run is left
	int from = elements;
	int to = tmp;

	// Пока сегментов больше одного
	while (runCount > 1) {

		// Вводим новый счетчик сегментов(стартов)
		int newRunCount = 0;

		// Merge two runs each
		for (int i = 0; i < runCount - 1; i += 2) {

			// Рекурсивно вызывем функцию для каждых двух сегментов
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

	// Объявление случайной генерации
	srand((unsigned)time(NULL));

	clock_t start;
	clock_t finish;

	int count = 0;

	int key = 1;
	int rand_arr[SIZE];

	// Вспомогательный массив для сортировки слиянием
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