#include <stdio.h>
#include <stdlib.h> // для использования функции atoi
#include <time.h> // для использования функции clock

#pragma mark - Бинарное дерево поиска, мама дорогая

struct tree{
	int data;
	struct tree *father;
	struct tree *lptr;
	struct tree *rptr;
};
typedef struct tree node;
node *derevo;
node *new(){
	return (node *)malloc(sizeof(node));
}
node *root(int value){            //call at the time of initilisation
	node *ptr = new();
	ptr-> data = value;
	ptr-> father = 0;
	ptr-> lptr = 0;
	ptr-> lptr = 0;
	return ptr;
}
void insert(int x, node *ptr){
	if (x > ptr->data){
		if (ptr-> rptr){
			insert(x,ptr-> rptr);
		} else{
			node *temp = new();
			temp-> data = x;
			temp-> father = ptr;
			temp-> lptr = 0;
			temp-> rptr = 0;
			ptr-> rptr = temp;
		}
	} else{
		if (ptr-> lptr){
			insert(x,ptr-> lptr);
		} else{
			node *temp = new();
			temp-> data = x;
			temp-> father = ptr;
			temp-> lptr = 0;
			temp-> rptr = 0;
			ptr-> lptr = temp;
		}
	}
}

node *search(int x, node *ptr){
	if(ptr){
		int y = ptr-> data;
		if(y == x) return ptr;
		else if( y < x ) return search(x,ptr->rptr);
		else return search(x,ptr->lptr);
	}else return 0;
}
node *parent(int x, node *ptr) {
	node *temp;
	if (temp = search(x,ptr)) {
		return temp-> father;
	}else return 0;
}
node *lchild(int x, node *ptr) {
	node *temp;
	if (temp = search(x,ptr)) {
		return temp-> lptr;
	}else return 0;
}
node *rchild(int x, node *ptr){
	node *temp;
	if (temp = search(x,ptr)) {
		return temp-> rptr;
	}else return 0;
}
int delete(int x, node *ptr) {
	node *temp;
	if (temp = search(x,ptr)) {
		if (temp == ptr){						   /// ROOT
			node *z = ptr-> rptr;
			ptr-> rptr-> father = 0;
			while ( z-> lptr) z = z-> lptr;
			z-> lptr = ptr-> lptr;
			derevo = ptr-> rptr;
			free(ptr);
		}else if (ptr-> lptr && ptr-> rptr){		   /// Both child
			node *z,*temp = ptr-> father;
			temp-> rptr = ptr-> rptr;
			ptr-> rptr-> father = temp;
			z = temp-> rptr;
			while( z-> lptr) z = z-> lptr;
			z-> lptr = ptr-> lptr;
			free(ptr);
		} else if (ptr-> lptr && !ptr-> rptr){       /// Left child only
			node *temp = ptr-> father;
			temp-> lptr = ptr-> lptr;
			ptr-> lptr-> father = temp;
			free(ptr);
		} else if (!ptr-> lptr && ptr-> rptr){	   /// Right child only
			node *temp = ptr-> father;
			temp-> rptr = ptr-> rptr;
			ptr-> rptr-> father = temp;
			free(ptr);
		} else {                                     /// No child
			node *temp = ptr-> father;
			int k = temp->data;
			if(k < x) temp-> rptr = 0;
			else temp-> lptr = 0;
			free(ptr);
		}
		return(x);
	} else{
		printf("Не найдено\n");
		return 0;
	}
}

int height(node *ptr,int count) {
	if(ptr){
		int x = height(ptr-> lptr,count+1),y = height(ptr-> rptr,count+1);
		return ( x > y ? x : y);
	}
	return count;
}

#pragma mark - Меню

void displayMenu() {
//	clock_t timeBefore = clock(); // берём текущее время

	printf("Выберите действие:\n");
	
	const char *menu[] = {"Вставить", "Удалить"};
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
	
	if (choise == 1) {
		insert(100, derevo);
	} else if (choise == 2) {
		delete(100, derevo);
	}
}

int main(int argc, const char * argv[]) {
	derevo = root(100);
	offerChoise();
	return 0;
}
