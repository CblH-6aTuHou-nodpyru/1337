#include <stdio.h>
#include <stdlib.h> // для использования функции atoi
#include <time.h> // для использования функции clock

#pragma mark - Бинарное дерево поиска, мама дорогая

struct uzel{
	int data;
	struct uzel *father;
	struct uzel *left;
	struct uzel *right;
};
typedef struct uzel tree;
tree *derevo;

// Инициализатор дерева
tree *root(int value) {
	tree *tree = malloc(sizeof(tree));
	tree-> data = value;
	tree-> father = 0;
	tree-> left = 0;
	tree-> right = 0;
	return tree;
}
void insert(int x, tree *ptr){
	if (x > ptr->data){
		if (ptr-> right){
			insert(x,ptr-> right);
		} else {
			tree *temp = malloc(sizeof(tree));
			temp-> data = x;
			temp-> father = ptr;
			temp-> left = 0;
			temp-> right = 0;
			ptr-> right = temp;
		}
	} else {
		if (ptr-> left){
			insert(x,ptr-> left);
		} else{
			tree *temp = malloc(sizeof(tree));
			temp-> data = x;
			temp-> father = ptr;
			temp-> left = 0;
			temp-> right = 0;
			ptr-> left = temp;
		}
	}
}

tree *search(int x, tree *ptr){
	if(ptr){
		int y = ptr-> data;
		if(y == x) return ptr;
		else if( y < x ) return search(x,ptr->right);
		else return search(x,ptr->left);
	}else return 0;
}
tree *parent(int x, tree *ptr) {
	tree *temp;
	if (temp = search(x,ptr)) {
		return temp-> father;
	}else return 0;
}
tree *lchild(int x, tree *ptr) {
	tree *temp;
	if (temp = search(x,ptr)) {
		return temp-> left;
	}else return 0;
}
tree *rchild(int x, tree *ptr){
	tree *temp;
	if (temp = search(x,ptr)) {
		return temp-> right;
	}else return 0;
}
int delete(int x, tree *ptr) {
	tree *temp;
	if (temp = search(x,ptr)) {
		if (temp == ptr){						   /// ROOT
			tree *z = ptr-> right;
			ptr-> right-> father = 0;
			while ( z-> left) z = z-> left;
			z-> left = ptr-> left;
			derevo = ptr-> right;
			free(ptr);
		}else if (ptr-> left && ptr-> right){		   /// Both child
			tree *z,*temp = ptr-> father;
			temp-> right = ptr-> right;
			ptr-> right-> father = temp;
			z = temp-> right;
			while( z-> left) z = z-> left;
			z-> left = ptr-> left;
			free(ptr);
		} else if (ptr-> left && !ptr-> right){       /// Left child only
			tree *temp = ptr-> father;
			temp-> left = ptr-> left;
			ptr-> left-> father = temp;
			free(ptr);
		} else if (!ptr-> left && ptr-> right){	   /// Right child only
			tree *temp = ptr-> father;
			temp-> right = ptr-> right;
			ptr-> right-> father = temp;
			free(ptr);
		} else {                                     /// No child
			tree *temp = ptr-> father;
			int k = temp->data;
			if(k < x) temp-> right = 0;
			else temp-> left = 0;
			free(ptr);
		}
		return(x);
	} else{
		printf("Не найдено\n");
		return 0;
	}
}

int height(tree *ptr,int count) {
	if(ptr){
		int x = height(ptr-> left,count+1),y = height(ptr-> right,count+1);
		return ( x > y ? x : y);
	}
	return count;
}

#pragma mark - Меню

void displayMenu() {
//	clock_t timeBefore = clock(); // берём текущее время

	printf("Выберите действие:\n");
	
	const char *menu[] = {"Вставить", "Удалить", "Поиск"};
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
	return choise >= 1 && choise <= 3;
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
	}
}

int main(int argc, const char * argv[]) {
	derevo = root(100);
	offerChoise();
	return 0;
}
