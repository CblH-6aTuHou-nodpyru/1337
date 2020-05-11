#include <stdio.h>
#include <stdlib.h> // для использования функции atoi
#include <time.h> // для использования функции clock
#include <string.h> // для использования функции strstr

#pragma mark - Бинарное дерево поиска, мама дорогая

struct tree{
	int key; // значение, которое хранится в узле
	struct tree *left; // левый потомок
	struct tree *right; // правый потомок
};

typedef struct tree tree; // псевдоним 'tree' для 'struct tree' чтобы не писать 2 слова каждый раз
tree *derevo;

// Инициализатор дерева
tree *initialize(int value) {
	tree *tree = malloc(sizeof(tree));
	tree-> key = value;
	tree-> left = NULL;
	tree-> right = NULL;
	return tree;
}

tree *search(tree *root, int x)
{
    if (root == NULL || root->key == x) // if root->key is x then the element is found
        return root;
    else if (x > root->key) // x is greater, so we will search the right subtree
        return search(root->right, x);
    else //x is smaller than the key, so we will search the left subtree
        return search(root->left,x);
}

/// Находит минимум в дереве
/// @param root дерево
tree *findMinimum(tree *root)
{
	if (root == NULL) {
        return NULL;
	}
	else if (root->left != NULL) { // node with minimum value will have no left child
        return findMinimum(root->left); // left most element will be minimum
	}
    return root;
}

tree *insert(tree *root, int x)
{
	// Из задания: если информация с заданным ключом уже есть, то выводится сообщение об ошибке
	// Поэтому ищем значение, если есть, то дасвиданья
	tree *searchResult = search(root, x);
	if (searchResult) {
		printf("Это значение уже есть в дереве. ДАСВИДАНЬЯ\n\n");
		return root;
	}
	// Ищем куда вставить
	if (root == NULL) {
		printf("Введенное значение ключа вставлено в дерево\n\n");
        return initialize(x);
	} else if (x > root->key) { // x is greater. Should be inserted to right
        root->right = insert(root->right, x);
	} else { // x is smaller should be inserted to left
        root->left = insert(root->left, x);
	}
    return root;
}

tree *delete(tree *root, int x)
{
	// Ищем узел для удаления
    if (root == NULL)
        return NULL;
    if (x > root->key)
        root->right = delete(root->right, x);
    else if (x < root->key)
        root->left = delete(root->left, x);
    else {
		if (root->left == NULL && root->right == NULL) { // // Без поддеревьев
            free(root);
            return NULL;
		} else if (root->left == NULL || root->right == NULL) { // Одно поддерево
            tree *temp;
            if (root->left == NULL)
                temp = root->right;
            else
                temp = root->left;
            free(root);
            return temp;
        } else { // Оба поддерева
            tree *temp = findMinimum(root->right);
            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
    }
    return root;
}

void inorder(tree *root)
{
    if (root != NULL) // может быть нил, если дерево не проинициализировано
    {
        inorder(root->left); // visiting left child
        printf(" %d ", root->key); // printing key at root
        inorder(root->right);// visiting right child
    }
}

// Задание:
// вывод всего содержимого таблицы в прямом порядке следования ключей, превышающих заданное значение ключа;
// если ключ не указан,  то всей таблицы;

// Сейчас оно выводится не в прямом порядке
// Сейчас выводится всё дерево
// TODO:
// 1) прокинуть ещё один параметр key, чтобы доделать задание
// 2) переделать на прямой порядок
void printInInorder(tree *root) {
	inorder(root);
}

// TODO: Реализовать
/// Красиво распечатать дерево
void prettyPrint(tree *aTree) {
	// Гуглим 'print binary search tree'
	// Реализация на C++
	// https://stackoverflow.com/a/51730733
	// Можно адаптировать под C
}

#pragma mark - Меню

void displayMenu() {

//  Провести таймирование (или профилирование) программы:
//  Это, как я понял, заюзать как раз этот закомменченный код в нужных местах: засечь clock до и после
//	clock_t timeBefore = clock(); // берём текущее время

	printf("Выберите действие:\n");
	
	const char *menu[] = {"Вставить", "Удалить", "Поиск", "Распечатать в прямом порядке", "Распечатать красиво", "Загрузить из файла", "Поиск содержащегося числа"};
	size_t menuItemsCount = sizeof(menu)/sizeof(menu[0]);
	for (int i = 0; i < menuItemsCount; i++) {
		printf("%d. %s\n", i + 1, menu[i]);
	}
	
//	clock_t timeAfter = clock(); // берём опять текущее время
//	// вычитаем из новой даты предыдущую - получаем разницу: столько выполнялся этот кусок кода
//	printf("\nОтрисовка меню заняла: %.10f\n\n", (double)(timeAfter - timeBefore)/CLOCKS_PER_SEC);

	printf("\nВаш выбор: ");
}

/// Функция валидирует пользовательский выбор
/// @param choise выбор пользователя
_Bool isMenuChoiseValid(int choise) {
	return choise >= 1 && choise <= 7;
}

// объявляем прототип функции, чтобы в методе interactiveSearch была видна функция offerChoise,
// которая реализована ниже по коду, чем методы interactiveInsert, interactiveDeletion, interactiveSearch.
// Этим мы как бы заставляем компилятор поверить нам наслово, что этот метод существует при выполнении программы.
void offerChoise(void);

// Интерактивная(через взаимодействие с юзером) вставка
void interactiveInsert() {
	char input[100];
	printf("Введите, пожалуйста, значение ключа, которое хотите вставить: \n\n");
	scanf("%s", input);

	int value = atoi(input);
	if (value == '\0') {
		printf("Нужно ввести именно число. Попробуйте снова\n\n");
		interactiveInsert();
	} else {
		derevo = insert(derevo, value);
		offerChoise(); // снова показываем меню, чтобы программа не завершалась
	}
}

// Интерактивное удаление
void interactiveDeletion() {
	char input[100];
	printf("Введите, пожалуйста, значение ключа, которое хотите удалить: \n\n");
	scanf("%s", input);

	int value = atoi(input);
	if (value == '\0') {
		printf("Нужно ввести именно число. Попробуйте снова\n\n");
		interactiveDeletion();
	} else {
		derevo = delete(derevo, value);
		printf("Введенное значение ключа удалено из дерева\n\n");
		offerChoise(); // снова показываем меню, чтобы программа не завершалась
	}
}
	
// Интерактивный поиск
void interactiveSearch() {
	char input[100];
	printf("Введите, пожалуйста, значение ключа, которое хотите найти: \n\n");
	scanf("%s", input);
	
	int value = atoi(input);
	if (value == '\0') {
		printf("Нужно ввести именно число. Попробуйте снова\n\n");
		interactiveSearch();
	} else {
		tree *searchResult = search(derevo, value);
		if (searchResult != NULL) {
			printf ("Введенное значение ключа найдено\n\n" );
			offerChoise(); // снова показываем меню, чтобы программа не завершалась
		} else {
			printf("Такого значения ключа в дереве нет. Попробуйте поискать другое значение\n\n");
			interactiveSearch();
		}
	}
}

_Bool stringContainsString(char *a, char *b) {
	return (strstr(a, b) != NULL);
}

// Задание:
// поиск элемента, соответствующего значению ключа,
// совпадающего с заданным по первым N символам (выводятся все элементы, удовлетворяющие условию).
void printContainedValues(tree *root, int x) {
    if (root != NULL) // может быть нил, если дерево не проинициализировано
    {
		// Перевод числа в строку (http://kulibaba.net/programming/cpp/int-to-char)
		// Конвертируем x и ключ в строку
		// И проверяем, содержится ли икс в ключе. И так по кругу по всем ключам
		char xAsString[20];
		sprintf(xAsString, "%d", x);

		char keyAsString[20];
		sprintf(keyAsString, "%d", root->key);

		if (stringContainsString(keyAsString, xAsString)) {
			printf("%d\n", root->key);
		}

		printContainedValues(root->left, x);
		printContainedValues(root->right, x);
    }
}

void interactiveSearchContainedValues() {
	printf("\nКакое число хотите найти?\nВаш выбор: ");
	char input[100];
	scanf("%s", input);

	int value = atoi(input);
	if (value == '\0') {
		printf("Нужно ввести именно число. Попробуйте снова\n\n");
		interactiveSearchContainedValues();
	} else {
		printContainedValues(derevo, value);
	}
}

void interactiveLoadFromFile() {
//	char filename[100];
//	printf("\nУкажите файл, из которого хотите загрузить дерево:\n");
//	scanf("%s", filename);
	char filename[] = "/path/to/file.txt";

	int bufferLength = 255;
	char buffer[bufferLength];
	FILE *filePointer = fopen(filename, "r");

	if (filePointer == NULL) {
		printf("Неверный файл.");
		return;
	}
	while(fgets(buffer, bufferLength, filePointer)) {
		int x = atoi(buffer);
		if (x != '\0') {
			insert(derevo, x);
		}
	}
	fclose(filePointer);
}

#pragma mark - Main

/// Предложить пользователю выбор
void offerChoise() {
	int choise = -1;
	// до тех пор пока нам не введут адекватное значение, будем делать это:
	while (!isMenuChoiseValid(choise)) {
		// отображаем меню
		displayMenu();
		
		// считываем пользовательский ввод
		char input[100];
		scanf("%s", input);

		// валидируем
		int value = atoi(input); // atoi конвертирует строку в int
		// если ввели какую-то муть
		if (value == '\0') {
			printf("Ты вводишь какую-то муть. Давай ещё раз\n\n");
		} else {
			// если ввели не муть, то смотрим чтоб это значение было в диапазоне существующих
			if (!isMenuChoiseValid(value)) {
				// не прошли валидацию
				printf("Такого значения в меню нет. Давай ещё раз\n\n");
			} else {
				// прошли валидацию. значит присваиваем корректный choise, что приведёт к выходу из цикла while
				choise = value;
			}
		}
	}
	
	printf("Выбрали. Какие мы молодцы! %d\n\n", choise);
	
	if (choise == 1) { // вставка
		interactiveInsert();
		offerChoise(); // снова показываем меню, чтобы программа не завершалась
	} else if (choise == 2) { // удаление
		interactiveDeletion();
		offerChoise();
	} else if (choise == 3) { // поиск
		interactiveSearch();
	} else if (choise == 4) { // распечатать в прямом порядке
		printInInorder(derevo);
		offerChoise();
	} else if (choise == 5) { // распечатать красиво
		prettyPrint(derevo);
		offerChoise();
	} else if (choise == 6) { // загрузить из файла
		interactiveLoadFromFile();
		offerChoise();
	} else if (choise == 7) { // поиск содержащегося числа
		interactiveSearchContainedValues();
		printf("\n");
		offerChoise();
	}
}

int main(int argc, const char * argv[]) {
	derevo = initialize(50);
	offerChoise();
	return 0;
}

// TODO:
// Задание
// Оценить сложность реализованных алгоритмов.
// Ответ здесь: https://www.geeksforgeeks.org/complexity-different-operations-binary-tree-binary-search-tree-avl-tree/
/**
 Searching: For searching element 1, we have to traverse all elements (in order 3, 2, 1). Therefore, searching in binary search tree has worst case complexity of O(n). In general, time complexity is O(h) where h is height of BST.
 Insertion: For inserting element 0, it must be inserted as left child of 1. Therefore, we need to traverse all elements (in order 3, 2, 1) to insert 0 which has worst case complexity of O(n). In general, time complexity is O(h).
 Deletion: For deletion of element 1, we have to traverse all elements to find 1 (in order 3, 2, 1). Therefore, deletion in binary tree has worst case complexity of O(n). In general, time complexity is O(h).
 */
// А ещё здесь, справа:
// https://en.wikipedia.org/wiki/Binary_search_tree
// Algorithm		Average		Worst case
// Space			O(n)		O(n)
// Search			O(log n)	O(n)
// Insert			O(log n)	O(n)
// Delete			O(log n)	O(n)
