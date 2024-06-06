#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN32
	#include "List.h"
	#include <io.h>
#else
	#include "libraries/List.h"
	#include <unistd.h>
#endif

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

void clear_screen()
{
#ifdef _WIN32
    std::system("cls");
#else
    // Assume POSIX
    std::system ("clear");
#endif
}

//Part1_B
void AddToList(List** head) {
	clear_screen();
	WashingMachine* wm = (WashingMachine*)malloc(sizeof(WashingMachine));
	float price, mss;
	char* model = (char*)malloc(N), * firm = (char*)malloc(N);
	
#ifdef __linux__
	printf("Enter price: ");
	scanf("%f", &price);
	printf("Enter motor spin speed: ");
	scanf("%f", &mss);
	printf("Enter model: ");
	scanf("%s", model);
	printf("Enter firm: ");
	scanf("%s", firm);
#else
	printf("Enter price: ");
	scanf_s("%f", &price);
	printf("Enter motor spin speed: ");
	scanf_s("%f", &mss);
	getchar();
	printf("Enter model: ");
	gets_s(model, N);
	printf("Enter firm: ");
	gets_s(firm, N);
#endif
	printf("\n");
	Init(wm, price, mss, model, firm);
	Push_back(wm, head);
}
//Part1_B
void PrintList(List* head) {
	if(head == NULL)
		return;
	clear_screen();
	for (int i = 0; i < Size(head); i++)
	{
		printf("PC %d\n", i);
		Print(GetElementByPos(head, i));
		printf("\n");
	}
}
//Part1_B
void DeleteFromList(List** head) {
	clear_screen();
	if(*head == NULL){
		return;
	}
	printf("Enter index of wm you want to delete: ");
	int pos;
#ifdef __linux__
	scanf("%d", &pos);
#else
	scanf_s("%d", &pos);
#endif
	if (DeleteByPos(head, pos) == 0) {
		printf("Deleting complete!\n");
	}
	else {
		printf("Error: index is wrong!\n");
	}
	printf("\n");
}

//Part1_C
void WriteToFile(List* head) {
	char pathname[] = "file.bin";
#ifdef __linux__
	int fd = open(pathname, O_CREAT | O_WRONLY, S_IRWXU);
	if (fd == -1) {
		printf("The file was not opened!\n");
		return;
	}
	while (head != NULL) {
		int cnt = write(fd, &head->wm->price, sizeof(head->wm->price));
		cnt = write(fd, &head->wm->mss, sizeof(head->wm->mss));
		cnt = write(fd, &head->wm->model, sizeof(head->wm->model));
		cnt = write(fd, &head->wm->firm, sizeof(head->wm->firm));
		head = head->next;
	}
	
#else
	int fd = _open(pathname, O_CREAT | O_WRONLY, S_IWRITE);
	if (fd == -1) {
		printf("The file was not opened!");
		return;
	}
	while (head != NULL) {
		int cnt = _write(fd, &head->wm->price, sizeof(head->wm->price));
		cnt = _write(fd, &head->wm->mss, sizeof(head->wm->mss));
		cnt = _write(fd, &head->wm->model, sizeof(head->wm->model));
		cnt = _write(fd, &head->wm->firm, sizeof(head->wm->firm));
		head = head->next;
	}
#endif
	close(fd);
}

List* ReadFromFile() {
	char pathname[] = "file.bin";
#ifdef __linux__
	int fd = open(pathname, O_RDONLY, S_IRWXU);
	if (fd == -1) {
		printf("The file was not opened!\n");
		return NULL;
	}
	List* head = NULL;
	while (true) {
		WashingMachine* wm = (WashingMachine*)malloc(sizeof(WashingMachine));
		float price, mss;	
		int cnt = read(fd, &price, sizeof(price));
		if (cnt == 0) {
			return head;
		}
		cnt = read(fd, &mss, sizeof(mss));
		char model[N], firm[N];
		cnt = read(fd, &model, N);
		cnt = read(fd, &firm, N);
		
		Init(wm, price, mss, model, firm);
		Push_back(wm, &head);
	}
#else
	int fd = _open(pathname, O_RDONLY, S_IREAD);
	if (fd == -1) {
		printf("The file was not opened!");
		return NULL;
	}
	List* head = NULL;
	while (true) {
		WashingMachine* wm = (WashingMachine*)malloc(sizeof(WashingMachine));
		float price, mss;	
		int cnt = _read(fd, &price, sizeof(price));
		cnt = _read(fd, &mss, sizeof(mss));
		char model[20], firm[20];
		cnt = _read(fd, &model, 20);
		cnt = _read(fd, &firm, 20);
		if (cnt == 0) {
			return head;
		}
		Init(wm, price, mss, model, firm);
		Push_back(wm, &head);
	}
#endif
	close(fd);
	return head;
}

void Part1_A() {
	WashingMachine wm1, wm2, wm3, wm4;
	Init(&wm1, 20, 8, "AMD", "Linux");
	Init(&wm2, 16, 4, "AMD", "MacOS");
	Init(&wm3, 24, 16, "Intel", "Windows");
	Init(&wm4, 20, 8, "AMD", "Linux");

	Print(&wm1);
	Print(&wm2);
	Print(&wm3);
	Print(&wm4);

	if (Equals(&wm1, &wm4)) {
		printf("Equals!\n");
	}

	if (Less(&wm2, &wm3)) {
		printf("Less!\n");
	}

	List* head = NULL;
	Push_back(&wm1, &head);
	Push_back(&wm2, &head);
	Push_back(&wm3, &head);
	// Push_back(&wm4, &head);

	printf("%d\n", Size(head));
	DeleteByPos(&head, 1);
	Print(GetElementByPos(head, 1));
}

void Part1_B() {
	List* head = NULL;
	while (true) {
		//clear_screen();
		printf("1)Add washing machine to list\n2)Print list\n3)Delete from list by index\n0)Exit\nEnter your choiсe -> ");
		int choice;
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			AddToList(&head);
			break;
		case 2:
			PrintList(head);
			break;
		case 3:
			DeleteFromList(&head);
			break;
		case 0:
			return;
		default:
			break;
		}
#ifdef _WIN32
		system("pause");
#endif
	}
}


void Part1_C() {
	List* head = ReadFromFile();
	while (true) {
		//clear_screen();
		printf("1)Add washing machine to list\n2)Print list\n3)Delete from list by index\n0)Exit\nEnter your choiсe -> ");
		int choice;
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			AddToList(&head);
			break;
		case 2:
			PrintList(head);
			break;
		case 3:
			DeleteFromList(&head);
			break;
		case 0:
			WriteToFile(head);
			return;
		default:
			break;
		}
#ifdef _WIN32
		system("pause");
#endif
	}
}

int main(int, char**) {
	//Part1_A();
	//Part1_B();
	Part1_C();
}