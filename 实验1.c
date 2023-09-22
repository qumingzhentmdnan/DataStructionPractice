#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct emp {
	char name[20];
	double score;
	int no;
	struct emp*next;
}emp;


void CreatList(emp* head) {
	FILE* file = fopen("D:\\shuju1.txt", "r");
	if (file == NULL) {
		printf("文件打开失败");
		return;
	}
	while (1) {
		emp* temp = (emp*)malloc(sizeof(emp));
		temp->next = NULL;
		int res = fscanf(file, "%d %s %lf\n", &temp->no, &temp->name, &temp->score);
		if (res == -1) {
			return;
		}
		else {
			head->next = temp;
			head = head->next;
		}
	}
	fclose(file);
}

void SaveList(emp* head, FILE* file) {
	while (head != NULL) {
		int res = fprintf(file, "%d %s %f\n", head->no, head->name, head->score);
		head = head->next;
	}

	fclose(file);
}

void display(emp* temp1, emp* temp2) {
	printf("%d  %s  %.2lf\n", temp1->no, temp1->name, temp1->score);
	printf("%d  %s  %.2lf\n", temp2->no, temp2->name, temp2->score);
	puts("");
}
void BubbleSortByScore(emp* head) {
	emp*temp = head;
	int size = 0;

	while (temp != NULL) {
		size++;
		temp = temp->next;
	}
	for (int i = 0; i < size - 1; i++) {
		temp = head;
		for (int j = 0; j < size - i - 1; j++) {
			if (temp->score < temp->next->score) {

				double a = temp->score;
				temp->score = temp->next->score;
				temp->next->score = a;

				int no = temp->no;
				temp->no = temp->next->no;
				temp->next->no = no;

				char name[20];
				strcpy(name, temp->name);
				strcpy(temp->name, temp->next->name);
				strcpy(temp->next->name, name);
			}
			temp = temp->next;
		}
	}
	FILE* file = fopen("D:\\shuju2.txt", "w");
	if (file == NULL) {
		printf("文件创建失败");
		return;
	}
	SaveList(head, file);
}


void BubbleSortByName(emp* head) {
	emp*temp = head;
	int size = 0;
	while (temp != NULL) {
		size++;
		temp = temp->next;
	}

	for (int i = 0; i < size - 1; i++) {
		temp = head;
		for (int j = 0; j < size - i - 1; j++) {
			if (strcmp(temp->name, temp->next->name) > 0) {
				double a = temp->score;
				temp->score = temp->next->score;
				temp->next->score = a;

				int no = temp->no;
				temp->no = temp->next->no;
				temp->next->no = no;

				char name[20];
				strcpy(name, temp->name);
				strcpy(temp->name, temp->next->name);
				strcpy(temp->next->name, name);
			}
			temp = temp->next;
		}
	}
	FILE* file = fopen("D:\\shuju3.txt", "w");
	if (file == NULL) {
		printf("文件创建失败");
		return;
	}
	SaveList(head, file);
}





void GetMaxAndAverage(emp* head) {
	double max = 0.0;
	double all = 0.0;
	int size = 0;
	while (head != NULL) {
		if (head->score > max) {
			max = head->score;
		}
		all += head->score;
		size++;
		head = head->next;
	}

	double average = all / size;
	printf("平均分：%f\n最高分：%f\n", average, max);

	FILE* file = fopen("D:\\shuju4.txt", "w");
	if (file == NULL) {
		printf("文件打开失败");
		return;
	}
	fprintf(file, "平均分：%f 最高分：%f\n", average, max);
	fclose(file);
}


void FilterByScore(emp* head) {
	double min = 0.0;
	double max = 0.0;
	printf("请依次输入最小值和最大值:\n");
	scanf("%lf%lf", &min, &max);

	FILE* file = fopen("D:\\shuju6.txt", "w");
	if (file == NULL) {
		printf("文件创建失败");
		return;
	}

	while (head != NULL) {
		if (head->score >= min && head->score <= max) {
			int res = fprintf(file, "%d %s %f\n", head->no, head->name, head->score);
		}
		head = head->next;
	}
	fclose(file);
}

void GetGroupInfo(emp* head) {
	int first = 0;
	int second = 0;
	int third = 0;
	int fourth = 0;
	int fifth = 0;
	while (head != NULL) {
		if (head->score >= 0 && head->score <= 59) {
			first++;
		}
		else if (head->score >= 60 && head->score <= 69) {
			second++;
		}
		else if (head->score >= 70 && head->score <= 79) {
			third++;
		}
		else if (head->score >= 80 && head->score <= 89) {
			fourth++;
		}
		else {
			fifth++;
		}
		head = head->next;
	}

	FILE* file = fopen("D:\\shuju5.txt", "w");
	if (file == NULL) {
		printf("文件创建失败");
		return;
	}
	fprintf(file, "0-59:%d\n60-69:%d\n70-79:%d\n80-89:%d\n90-100:%d\n", first, second, third, fourth, fifth);
	fclose(file);
}


int main() {
	emp* head = (emp*)malloc(sizeof(emp));
	head->next = NULL;
	CreatList(head);
	BubbleSortByScore(head->next);
	BubbleSortByName(head->next);
	GetMaxAndAverage(head->next);
	FilterByScore(head->next);
	GetGroupInfo(head->next);
	return 0;
}
