#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//���ȶ���һ������ڵ�ṹ����ʾÿ�������嵥�
struct ShoppingItem {
	char name[50]; // ��Ʒ����
	int quantity; // ��Ʒ����
	struct ShoppingItem* next;//ָ����һ���ڵ�ָ��
};

// ����һ������ͷָ�룬��ʾ�����嵥����ʼ�㣺
struct ShoppingItem* shoppingList = NULL; // ��ʼ�������嵥Ϊ��
struct ShoppingItem* shoppingList1 = NULL; // ��ʼ�������嵥Ϊ��


// �����Ʒ�������嵥��
void addItem(char itemName[], int itemQuantity) {
	struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
	strcpy(newItem->name, itemName);
	newItem->quantity = itemQuantity;
	newItem->next = NULL;
	if (shoppingList == NULL) {
		shoppingList = newItem;
	}
	else {
		newItem->next = shoppingList;
		shoppingList = newItem;
	}
}


void addItem1(char itemName[], int itemQuantity) {
	struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
	strcpy(newItem->name, itemName);
	newItem->quantity = itemQuantity;
	newItem->next = NULL;
	if (shoppingList1 == NULL) {
		shoppingList1 = newItem;
	}
	else {
		newItem->next = shoppingList1;
		shoppingList1 = newItem;
	}
}

// �ӹ����嵥���Ƴ���Ʒ��
void removeItem(char itemName[]) {
	struct ShoppingItem* current = shoppingList;
	struct ShoppingItem* previous = NULL;
	while (current != NULL) {
		if (strcmp(current->name, itemName) == 0) {
			if (previous != NULL) {
				previous->next = current->next;
			}
			else {
				shoppingList = current->next;
			}
			free(current);
			break;
		}
		previous = current;
		current = current->next;
	}
}

// �鿴�����嵥��
void displayList() {
	struct ShoppingItem* current = shoppingList;
	printf("�����嵥:\n");
	while (current != NULL) {
		printf("%s - ������%d\n", current->name, current->quantity);
		current = current->next;
	}
}

//  �޸Ĺ����嵥����Ʒ��������
void updateQuantity(char itemName[], int newItemQuantity) {
	struct ShoppingItem* current = shoppingList;
	while (current != NULL) {
		if (strcmp(current->name, itemName) == 0) {
			current->quantity = newItemQuantity;
			break;
		}
		current = current->next;
	}
}

// ��չ����嵥��
void clearList() {
	struct ShoppingItem* temp;
	while (shoppingList != NULL) {
		temp = shoppingList;
		shoppingList = shoppingList->next;
		free(temp);
		temp = NULL;
	}
}

// ���㹺���嵥����Ʒ����������
int totalQuantity() {
	struct ShoppingItem* current = shoppingList;
	int total = 0;
	while (current != NULL) {
		total += (current->quantity);
		current = current->next;
	}
	return total;
}

// ���ҹ����嵥�е���Ʒ��
void findItem(char itemName[]) {
	struct ShoppingItem* current = shoppingList;
	printf("������Ʒ \"%s\" ��\n", itemName);
	while (current != NULL) {
		if (strcmp(current->name, itemName) == 0) {
			printf("%s - ������%d\n", current->name, current->quantity);
			return;
		}
		current = current->next;
	}
	printf("δ�ҵ���Ʒ \"%s\"��\n", itemName);
}

// �������嵥��
void sortList() {
	struct ShoppingItem* current = shoppingList;
	struct ShoppingItem* nextItem = NULL;
	char tempName[50];
	int tempQuantity;
	while (current != NULL) {
		nextItem = current->next;
		while (nextItem != NULL) {
			if (strcmp(current->name, nextItem->name) > 0) {
				// ������Ʒ��Ϣ
				strcpy(tempName, current->name);
				strcpy(current->name, nextItem->name);
				strcpy(nextItem->name, tempName);

				tempQuantity = current->quantity;
				current->quantity = nextItem->quantity;
				nextItem->quantity = tempQuantity;
			}
			nextItem = nextItem->next;
		}
		current = current->next;
	}
}

// �ϲ������嵥����������������ͬ�Ĺ����嵥����ϣ�������Ǻϲ���һ����
void mergeLists(struct ShoppingItem** list1, struct ShoppingItem** list2) {
	struct ShoppingItem* current = *list1;
		// ��������һ�������嵥��ĩβ
	while (current->next != NULL) {
		current = current->next;
	}
		// ���ڶ��������嵥���ӵ���һ���嵥��ĩβ
	current->next = *list2;
	*list2 = NULL; // ��յڶ��������嵥��ͷָ�룬��ֹ����
}

//ɾ�������嵥�е���Ʒ��
//ʵ��һ�����������Ը�����Ʒ����ɾ�������嵥�е���Ʒ�����ж����ͬ���Ƶ���Ʒ��
//����ѡ��ɾ������һ����ȫ����
void deleteItem(char itemName[], int deleteAll) {
	struct ShoppingItem*current = shoppingList;
	struct ShoppingItem*prev = NULL;
	while (current != NULL) {
		if (strcmp(current->name, itemName) == 0) {
			if (prev == NULL) {
				// ���Ҫɾ�����ǵ�һ���ڵ�
				struct ShoppingItem*temp = current;
				current = current->next;
				shoppingList = current;
				free(temp);
				temp = NULL;
				if (!deleteAll) break;
			}
			else {
				// ���Ҫɾ���Ĳ��ǵ�һ���ڵ�
				prev->next = current->next;
				free(current);
				current = prev->next;
				if (!deleteAll) break;
			}
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}


int main() {
	addItem("C���Գ������", 12);
	addItem("���ݽṹ", 14);
	addItem("��ѧ����", 45);
	addItem("�ߵ���ѧ", 23);
	displayList();//չʾ����
	/*�����嵥:
	�ߵ���ѧ - ������23
	��ѧ���� - ������45
	���ݽṹ - ������14
	C���Գ������ - ������12*/


	sortList();//����������������
	displayList();
	/*
	�����嵥:
	C���Գ������ - ������12
	��ѧ���� - ������45
	�ߵ���ѧ - ������23
	���ݽṹ - ������14
	*/


	removeItem("��ѧ������");//���ڲ����ڵ��鼮��ɾ��ʧ��
	displayList();
	/*
	�����嵥:
	C���Գ������ - ������12
	��ѧ���� - ������45
	�ߵ���ѧ - ������23
	���ݽṹ - ������14
	*/


	addItem("��ѧ����", 45);
	removeItem("��ѧ����");//���ڴ��ڵ��鼮��ɾ���ɹ�,����ֻ��ɾ��һ��
	displayList();
	/*
	�����嵥:
	C���Գ������ - ������12
	��ѧ���� - ������45
	�ߵ���ѧ - ������23
	���ݽṹ - ������14
	*/


	addItem("��ѧ����", 45);
	deleteItem("��ѧ����",0);//ɾ����һ�������������鼮
	displayList();
	/*
	�����嵥:
	C���Գ������ - ������12
	��ѧ���� - ������45
	�ߵ���ѧ - ������23
	���ݽṹ - ������14
	*/


	addItem("��ѧ����", 45);
	deleteItem("��ѧ����",1);//ɾ��ȫ�������������鼮
	displayList();
	/*
	�����嵥:
	C���Գ������ - ������12
	�ߵ���ѧ - ������23
	���ݽṹ - ������14
	*/


	printf("%d\n", totalQuantity());//��������������Ϊ49


	updateQuantity("�ߵ���ѧ", 100);//�޸ĸߵ���ѧ������
	printf("%d\n", totalQuantity());//��������������Ϊ126

	findItem("�ߵ���ѧ");//���Ҹߵ���ѧ����Ϣ
	/*
	������Ʒ "�ߵ���ѧ" ��
	�ߵ���ѧ - ������100
	*/

	addItem1("java�������", 1);
	addItem1("���Դ���", 1);
	addItem1("������", 1);
	addItem1("��·����", 1);
	mergeLists(&shoppingList, &shoppingList1);//ƴ��
	displayList();
	/*
	�����嵥:
	C���Գ������ - ������12
	�ߵ���ѧ - ������100
	���ݽṹ - ������14
	��·���� - ������1
	������ - ������1
	���Դ��� - ������1
	java������� - ������1
	*/

	clearList();//	�������
	displayList();//���Ϊ�գ������嵥:

	
}












