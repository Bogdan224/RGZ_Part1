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
	PersonalComputer* pc = (PersonalComputer*)malloc(sizeof(PersonalComputer));
	float displaySize, ram;
	char* cpu = (char*)malloc(N), * os = (char*)malloc(N);
	
#ifdef __linux__
	printf("Enter display size(inch): ");
	scanf("%f", &displaySize);
	printf("Enter size of RAM(gb): ");
	scanf("%f", &ram);
	printf("Enter name of CPU: ");
	scanf("%s", cpu);
	printf("Enter name of OS: ");
	scanf("%s", os);
#else
	printf("Enter display size(inch): ");
	scanf_s("%f", &displaySize);
	printf("Enter size of RAM(gb): ");
	scanf_s("%f", &ram);
	getchar();
	printf("Enter name of CPU: ");
	gets_s(cpu, N);
	printf("Enter name of OS: ");
	gets_s(os, N);
#endif
	printf("\n");
	Init(pc, displaySize, ram, cpu, os);
	Push_back(pc, head);
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
	printf("Enter index of pc you want to delete: ");
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
		int cnt = write(fd, &head->pc->displaySize, sizeof(head->pc->displaySize));
		cnt = write(fd, &head->pc->ram, sizeof(head->pc->ram));
		cnt = write(fd, &head->pc->cpu, sizeof(head->pc->cpu));
		cnt = write(fd, &head->pc->os, sizeof(head->pc->os));
		head = head->next;
	}
	
#else
	int fd = _open(pathname, O_CREAT | O_WRONLY, S_IWRITE);
	if (fd == -1) {
		printf("The file was not opened!");
		return;
	}
	while (head != NULL) {
		int cnt = _write(fd, &head->pc->displaySize, sizeof(head->pc->displaySize));
		cnt = _write(fd, &head->pc->ram, sizeof(head->pc->ram));
		cnt = _write(fd, &head->pc->cpu, sizeof(head->pc->cpu));
		cnt = _write(fd, &head->pc->os, sizeof(head->pc->os));
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
		PersonalComputer* pc = (PersonalComputer*)malloc(sizeof(PersonalComputer));
		float displaySize, ram;	
		int cnt = read(fd, &displaySize, sizeof(displaySize));
		if (cnt == 0) {
			return head;
		}
		cnt = read(fd, &ram, sizeof(ram));
		char cpu[N], os[N];
		cnt = read(fd, &cpu, N);
		cnt = read(fd, &os, N);
		
		Init(pc, displaySize, ram, cpu, os);
		Push_back(pc, &head);
	}
#else
	int fd = _open(pathname, O_RDONLY, S_IREAD);
	if (fd == -1) {
		printf("The file was not opened!");
		return NULL;
	}
	List* head = NULL;
	while (true) {
		PersonalComputer* pc = (PersonalComputer*)malloc(sizeof(PersonalComputer));
		float displaySize, ram;	
		int cnt = _read(fd, &displaySize, sizeof(displaySize));
		cnt = _read(fd, &ram, sizeof(ram));
		char cpu[20], os[20];
		cnt = _read(fd, &cpu, 20);
		cnt = _read(fd, &os, 20);
		if (cnt == 0) {
			return head;
		}
		Init(pc, displaySize, ram, cpu, os);
		Push_back(pc, &head);
	}
#endif
	close(fd);
	return head;
}

void Part1_A() {
	PersonalComputer pc1, pc2, pc3, pc4;
	Init(&pc1, 20, 8, "AMD", "Linux");
	Init(&pc2, 16, 4, "AMD", "MacOS");
	Init(&pc3, 24, 16, "Intel", "Windows");
	Init(&pc4, 20, 8, "AMD", "Linux");

	Print(&pc1);
	Print(&pc2);
	Print(&pc3);
	Print(&pc4);

	if (Equals(&pc1, &pc4)) {
		printf("Equals!\n");
	}

	if (Less(&pc2, &pc3)) {
		printf("Less!\n");
	}

	List* head = NULL;
	Push_back(&pc1, &head);
	Push_back(&pc2, &head);
	Push_back(&pc3, &head);
	//Push_back(&pc3, &head);

	printf("%d\n", Size(head));
	DeleteByPos(&head, 1);
	Print(GetElementByPos(head, 1));
}

void Part1_B() {
	List* head = ReadFromFile();
	while (true) {
		//clear_screen();
		printf("1)Add pc to list\n2)Print list\n3)Delete from list by index\n0)Exit\nEnter your choiсe -> ");
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
#else
		getc(stdin);
#endif
	}
}

int main(int, char**) {
	
	//Part1_A();
	Part1_B();
}