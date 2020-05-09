#include <stdio.h>
#include <stdlib.h> // для использования функции atoi
#include <time.h> // для использования функции clock

#pragma mark - Бинарное дерево поиска, мама дорогая

struct uzel{
	int key; // значение, которое хранится в узле
	struct uzel *parent; // родительский узел
	struct uzel *left; // левый потомок
	struct uzel *right; // правый потомок
};
typedef struct uzel tree; // псевдоним 'tree' для 'struct uzel' чтобы не писать 2 слова каждый раз
tree *derevo;

// Инициализатор дерева
tree *initialize(int value) {
	tree *tree = malloc(sizeof(tree));
	tree-> key = value;
	tree-> parent = 0;
	tree-> left = 0;
	tree-> right = 0;
	return tree;
}

void insert(int x, tree *aTree) {
	if (x > aTree->key) {
		if (aTree-> right) {
			insert(x, aTree-> right);
		} else {
			tree *newChild = malloc(sizeof(tree));
			newChild-> key = x;
			newChild-> parent = aTree;
			newChild-> left = 0;
			newChild-> right = 0;
			aTree-> right = newChild;
		}
	} else {
		if (aTree-> left){
			insert(x, aTree-> left);
		} else {
			tree *newChild = malloc(sizeof(tree));
			newChild-> key = x;
			newChild-> parent = aTree;
			newChild-> left = 0;
			newChild-> right = 0;
			aTree-> left = newChild;
		}
	}
}

/// Поиск
/// @param x искомое значение
/// @param aTree дерево, в котором ищем
tree *search(int x, tree *aTree) {
	if (aTree) {
		int y = aTree-> key;
		if (y == x) return aTree;
		else if (y < x) return search(x, aTree->right);
		else return search(x,aTree->left);
	} else {
		return 0;
	}
}

int delete(int x, tree *aTree) {
	tree *searchResult = search(x, aTree);
	if (searchResult) {
		if (searchResult == aTree) { // если это корень
			// надо сделать [!!!!!!!!!]
		} else if (searchResult-> left && searchResult-> right) { // есть есть оба дочерних узла
			// надо сделать [!!!!!!!!!]
		} else if (searchResult-> left && !searchResult-> right) { // имеет только левый узел
			tree *tempParent = searchResult-> parent; // сохраняем ссылку на родителя
			tree *parentlessLeft = searchResult-> left; // сохраняем ссылку на потомка, у которого теперь нет родителя
			parentlessLeft-> parent = tempParent; // присваеваем потомку нового родителя
			tempParent-> left = parentlessLeft; // присваиваем родителю нового потомка
			free(searchResult); // удаляем найденное значение
		} else if (!searchResult-> left && searchResult-> right) { // имеет только правый узел
			tree *tempParent = searchResult-> parent; // сохраняем ссылку на родителя
			tree *parentlessRight = searchResult-> right; // сохраняем ссылку на потомка, у которого теперь нет родителя
			parentlessRight-> parent = tempParent; // присваеваем потомку нового родителя
			// тут у нас остался родитель, которому нужно указать нового наследника
			if (parentlessRight->key < tempParent->key) { // если он должен быть слева
				tempParent-> left = parentlessRight; // присваиваем родителю нового потомка
			} else {
				tempParent-> right = parentlessRight; // присваиваем родителю нового потомка
			}
			free(searchResult); // удаляем найденное значение
		} else { // без потомков (листва или как там)
			tree *parent = aTree-> parent;
			if (parent->key < x) parent-> right = 0;
			else parent-> left = 0;
			free(searchResult);
		}
		return(x);
	} else {
		printf("Не найдено\n");
		return 0;
	}
}

int height(tree *aTree, int count) {
	if (aTree) {
		int x = height(aTree-> left, count + 1);
		int y = height(aTree-> right, count + 1);
		return x > y ? x : y;
	}
	return count;
}

// Задание:
// вывод всего содержимого таблицы в прямом порядке следования ключей, превышающих заданное значение ключа;
// если ключ не указан,  то всей таблицы;

// Сейчас выводится всё дерево.
// TODO: прокинуть ещё один параметр key, чтобы доделать задание
// void printInPreorder(tree *aTree, int key)
void printInPreorder(tree *aTree) {
	if (aTree) {
		printf("%d\n", aTree-> key );
		printInPreorder(aTree-> left);
		printInPreorder(aTree-> right);
	}
}

void printInPostorder(tree *aTree) {
	if (aTree) {
		printInPostorder(aTree-> left);
		printInPostorder(aTree-> right);
		printf("%d\n", aTree-> key);
	}
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
//	clock_t timeBefore = clock(); // берём текущее время

	printf("Выберите действие:\n");
	
	const char *menu[] = {"Вставить", "Удалить", "Поиск", "Распечатать в прямом порядке", "Распечатать красиво", "Загрузить из файла"};
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
	return choise >= 1 && choise <= 6;
}

// объявляем прототип функции, чтобы в методе interactiveSearch была видна функция offerChoise,
// которая реализована ниже по коду, чем методы interactiveInsert, interactiveDeletion, interactiveSearch.
// Этим мы как бы заставляем компилятор поверить нам наслово, что этот метод существует при выполнении программы.
void offerChoise(void);

// Интерактивная(через взаимодействие с юзером) вставка
void interactiveInsert() {
	// TODO: сделать вставку не цифры 100, а значения которое ввёл юзер
	insert(100, derevo);
}

// Интерактивное удаление
void interactiveDeletion() {
	// TODO: сделать удаление не цифры 100, а значения которое ввёл юзер
	delete(100, derevo);
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
		tree *searchResult = search(value, derevo);
		if (searchResult != NULL) {
			printf ("Введенное значение ключа найдено\n\n" );
			offerChoise(); // снова показываем меню, чтобы программа не завершалась
		} else {
			printf("Такого значения ключа в дереве нет. Попробуйте поискать другое значение\n\n");
			interactiveSearch();
		}
	}
}

// TODO:
// Задание:
// поиск элемента, соответствующего значению ключа,
// совпадающего с заданным по первым N символам (выводятся все элементы, удовлетворяющие условию).
void interactiveSearchСочныйМощный() {
	// не очень понял чё значит совпадающий с заданным
	// типа если есть дерево со значениями 100, 10, 90, 85. Юзер вводит 10, а программа должна выдать 100, 10 ?
	// потому что они содержатся в этих цифрах. Или как?
	
	// Если именно так, как я понял, то можно отконвертить ключ в строку и проверить, содержится ли строка в строке
	// Или как-то математически попробовать
	
	// Если не так, как я понял, то обсудим
}

// TODO: Реализовать
// Задание
// Для целей отладки реализовать загрузку таблицы из файла в формате
// Ключ1
// Информация1
// Ключ2
// …
void interactiveLoadFromFile() {
	// предложить юзеру указать имя файла (файл предварительно лежит на диске с инфой в нужном формате)
	// легко гуглится, например 'c read from file'
	// ну и каждому прочтённому узлу делать insert, полагаю
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
		printInPreorder(derevo);
		offerChoise();
	} else if (choise == 5) { // распечатать красиво
		prettyPrint(derevo);
		offerChoise();
	} else if (choise == 6) { // загрузить из файла
		interactiveLoadFromFile();
		offerChoise();
	}
}

int main(int argc, const char * argv[]) {
	derevo = initialize(100);
	insert(90, derevo);
	insert(50, derevo);
	insert(60, derevo);
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
