#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//首先定义一个链表节点结构来表示每个购物清单项：
struct ShoppingItem {
	char name[50]; // 商品名称
	int quantity; // 商品数量
	struct ShoppingItem* next;//指向下一个节点指针
};

// 创建一个链表头指针，表示购物清单的起始点：
struct ShoppingItem* shoppingList = NULL; // 初始化购物清单为空
struct ShoppingItem* shoppingList1 = NULL; // 初始化购物清单为空


// 添加商品到购物清单：
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

// 从购物清单中移除商品：
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

// 查看购物清单：
void displayList() {
	struct ShoppingItem* current = shoppingList;
	printf("购物清单:\n");
	while (current != NULL) {
		printf("%s - 数量：%d\n", current->name, current->quantity);
		current = current->next;
	}
}

//  修改购物清单中商品的数量：
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

// 清空购物清单：
void clearList() {
	struct ShoppingItem* temp;
	while (shoppingList != NULL) {
		temp = shoppingList;
		shoppingList = shoppingList->next;
		free(temp);
		temp = NULL;
	}
}

// 计算购物清单中商品的总数量：
int totalQuantity() {
	struct ShoppingItem* current = shoppingList;
	int total = 0;
	while (current != NULL) {
		total += (current->quantity);
		current = current->next;
	}
	return total;
}

// 查找购物清单中的商品：
void findItem(char itemName[]) {
	struct ShoppingItem* current = shoppingList;
	printf("查找商品 \"%s\" ：\n", itemName);
	while (current != NULL) {
		if (strcmp(current->name, itemName) == 0) {
			printf("%s - 数量：%d\n", current->name, current->quantity);
			return;
		}
		current = current->next;
	}
	printf("未找到商品 \"%s\"。\n", itemName);
}

// 排序购物清单：
void sortList() {
	struct ShoppingItem* current = shoppingList;
	struct ShoppingItem* nextItem = NULL;
	char tempName[50];
	int tempQuantity;
	while (current != NULL) {
		nextItem = current->next;
		while (nextItem != NULL) {
			if (strcmp(current->name, nextItem->name) > 0) {
				// 交换商品信息
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

// 合并购物清单：假设你有两个不同的购物清单，你希望将它们合并成一个。
void mergeLists(struct ShoppingItem** list1, struct ShoppingItem** list2) {
	struct ShoppingItem* current = *list1;
		// 遍历到第一个购物清单的末尾
	while (current->next != NULL) {
		current = current->next;
	}
		// 将第二个购物清单连接到第一个清单的末尾
	current->next = *list2;
	*list2 = NULL; // 清空第二个购物清单的头指针，防止误用
}

//删除购物清单中的商品：
//实现一个函数，可以根据商品名称删除购物清单中的商品项。如果有多个相同名称的商品，
//可以选择删除其中一个或全部。
void deleteItem(char itemName[], int deleteAll) {
	struct ShoppingItem*current = shoppingList;
	struct ShoppingItem*prev = NULL;
	while (current != NULL) {
		if (strcmp(current->name, itemName) == 0) {
			if (prev == NULL) {
				// 如果要删除的是第一个节点
				struct ShoppingItem*temp = current;
				current = current->next;
				shoppingList = current;
				free(temp);
				temp = NULL;
				if (!deleteAll) break;
			}
			else {
				// 如果要删除的不是第一个节点
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
	addItem("C语言程序设计", 12);
	addItem("数据结构", 14);
	addItem("大学物理", 45);
	addItem("高等数学", 23);
	displayList();//展示数据
	/*购物清单:
	高等数学 - 数量：23
	大学物理 - 数量：45
	数据结构 - 数量：14
	C语言程序设计 - 数量：12*/


	sortList();//按照书名进行排序
	displayList();
	/*
	购物清单:
	C语言程序设计 - 数量：12
	大学物理 - 数量：45
	高等数学 - 数量：23
	数据结构 - 数量：14
	*/


	removeItem("大学物理上");//对于不存在的书籍，删除失败
	displayList();
	/*
	购物清单:
	C语言程序设计 - 数量：12
	大学物理 - 数量：45
	高等数学 - 数量：23
	数据结构 - 数量：14
	*/


	addItem("大学物理", 45);
	removeItem("大学物理");//对于存在的书籍，删除成功,但是只能删除一本
	displayList();
	/*
	购物清单:
	C语言程序设计 - 数量：12
	大学物理 - 数量：45
	高等数学 - 数量：23
	数据结构 - 数量：14
	*/


	addItem("大学物理", 45);
	deleteItem("大学物理",0);//删除第一本符合条件的书籍
	displayList();
	/*
	购物清单:
	C语言程序设计 - 数量：12
	大学物理 - 数量：45
	高等数学 - 数量：23
	数据结构 - 数量：14
	*/


	addItem("大学物理", 45);
	deleteItem("大学物理",1);//删除全部符合条件的书籍
	displayList();
	/*
	购物清单:
	C语言程序设计 - 数量：12
	高等数学 - 数量：23
	数据结构 - 数量：14
	*/


	printf("%d\n", totalQuantity());//计算总数，数量为49


	updateQuantity("高等数学", 100);//修改高等数学的数量
	printf("%d\n", totalQuantity());//计算总数，数量为126

	findItem("高等数学");//查找高等数学的信息
	/*
	查找商品 "高等数学" ：
	高等数学 - 数量：100
	*/

	addItem1("java程序设计", 1);
	addItem1("线性代数", 1);
	addItem1("概率论", 1);
	addItem1("电路基础", 1);
	mergeLists(&shoppingList, &shoppingList1);//拼接
	displayList();
	/*
	购物清单:
	C语言程序设计 - 数量：12
	高等数学 - 数量：100
	数据结构 - 数量：14
	电路基础 - 数量：1
	概率论 - 数量：1
	线性代数 - 数量：1
	java程序设计 - 数量：1
	*/

	clearList();//	清空链表
	displayList();//输出为空：购物清单:

	
}












