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
			insert(x,aTree-> right);
		} else {
			tree *temp = malloc(sizeof(tree));
			temp-> key = x;
			temp-> parent = aTree;
			temp-> left = 0;
			temp-> right = 0;
			aTree-> right = temp;
		}
	} else {
		if (aTree-> left){
			insert(x,aTree-> left);
		} else {
			tree *temp = malloc(sizeof(tree));
			temp-> key = x;
			temp-> parent = aTree;
			temp-> left = 0;
			temp-> right = 0;
			aTree-> left = temp;
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
tree *parent(int x, tree *pointer) {
	tree *temp;
	if (temp = search(x,pointer)) {
		return temp-> parent;
	} else return 0;
}
tree *lchild(int x, tree *pointer) {
	tree *temp;
	if (temp = search(x,pointer)) {
		return temp-> left;
	} else return 0;
}
tree *rchild(int x, tree *pointer){
	tree *temp;
	if (temp = search(x,pointer)) {
		return temp-> right;
	} else return 0;
}
int delete(int x, tree *aTree) {
	tree *temp;
	if (temp = search(x, aTree)) {
		if (temp == aTree) { // если это корень
			tree *z = aTree-> right;
			aTree-> right-> parent = 0;
			while ( z-> left) z = z-> left;
			z-> left = aTree-> left;
			derevo = aTree-> right;
			free(aTree);
		} else if (aTree-> left && aTree-> right) { // оба дочерних узла
			tree *z;
			tree *temp = aTree-> parent;
			temp-> right = aTree-> right;
			aTree-> right-> parent = temp;
			z = temp-> right;
			while( z-> left) z = z-> left;
			z-> left = aTree-> left;
			free(aTree);
		} else if (aTree-> left && !aTree-> right) { // имеет только левый узел
			tree *temp = aTree-> parent;
			temp-> left = aTree-> left;
			aTree-> left-> parent = temp;
			free(aTree);
		} else if (!aTree-> left && aTree-> right) { // имеет только правый узел
			tree *temp = aTree-> parent;
			temp-> right = aTree-> right;
			aTree-> right-> parent = temp;
			free(aTree);
		} else { // без потомков (листва или как там)
			tree *temp = aTree-> parent;
			int temporaryKey = temp->key;
			if (temporaryKey < x) temp-> right = 0;
			else temp-> left = 0;
			free(aTree);
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

/// Красиво распечатать дерево
void prettyPrint() {
	// Гуглим 'print binary search tree'
	// Реализация на C++
	// https://stackoverflow.com/a/51730733
	// Можно адаптировать под C
}

#pragma mark - Меню

void displayMenu() {
//	clock_t timeBefore = clock(); // берём текущее время

	printf("Выберите действие:\n");
	
	const char *menu[] = {"Вставить", "Удалить", "Поиск", "Распечатать"};
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
	return choise >= 1 && choise <= 4;
}

// Поиск
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
			displayMenu(); // снова показываем меню, чтобы программа не завершалась
		} else {
			printf("Такого значения ключа в дереве нет. Попробуйте поискать другое значение\n\n");
			interactiveSearch();
		}
	}
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
		insert(100, derevo);
	} else if (choise == 2) { // удаление
		delete(100, derevo);
	} else if (choise == 3) { // поиск
		interactiveSearch();
	} else if (choise == 4) { // распечатать
		printInPreorder(derevo);
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
