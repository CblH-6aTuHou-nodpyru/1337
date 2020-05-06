#include <stdio.h>

int displayMenu() {
	printf("Выберите действие:\n");
	
	const char *menu[] = {"One", "Two", "Three"};
	size_t menuItemsCount = sizeof(menu)/sizeof(menu[0]);
	for (int i = 0; i < menuItemsCount; i++) {
		printf("%d. %s\n", i + 1, menu[i]);
	}
	printf("\nВаш выбор: ");
	
	int userChoise;
	scanf("%d", &userChoise);
	return userChoise;
}

int main(int argc, const char * argv[]) {
	displayMenu();
	return 0;
}
