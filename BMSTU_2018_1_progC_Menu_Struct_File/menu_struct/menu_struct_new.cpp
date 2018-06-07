// slover_v_menu.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <Windows.h>
#include "menu_lib.h"
#include <string.h>


#pragma warning(disable:4996)

const int MASHROOMS_COUNT=18;
const char FILE_WAY[] = "C:\\123\\1.txt";
//int wordsCount=0;
//const char* mashrooms[MASHROOMS_COUNT]={"�����", "�������", "�����������", "������������", "�������", "�������" ,"�������_�������", "�������", "������", "�����", "��������", "�������", "�������", "������", "��������", "��������_����", "��������", "�����", "����������", "�������"};

const int STR_MAX_LEN=16;
const int NO_EATABLE_CATEGORY=-1;

//MashroomDictionary myDict[MASHROOMS_COUNT];

MashroomDictionary dictConst[]={
	{"�����", true, 1},
	{"�������", false, NO_EATABLE_CATEGORY},
	{"��������", true, 4},
	{"�������", true, 1},
	{"�����������", true, 2},
	{"������� �������", false, NO_EATABLE_CATEGORY},
	{"������������", true, 3},
	{"��������", true, 3},
	{"�������", true, 3},
	{"������", true, 1},
	{"�������", true, 3},
	{"�������", true, 2},
	{"�����", true, 1},
	{"�������", true, 3},
	{"�������", true, 4},
	{"�������� ����", true, 3},
	{"������� ����", false, NO_EATABLE_CATEGORY},
	{"�����", true, 3},
};



int _tmain(int argc, _TCHAR* argv[])
{
	SetRussian();

	printf("----������� 2.0----");

	//MashroomDictionary **dictActive = (MashroomDictionary**)calloc(MASHROOMS_COUNT, sizeof(MashroomDictionary*));
	//MashroomDictionary *dictActive = NULL;//new MashroomDictionary[MASHROOMS_COUNT];
	MashroomDictionary *dictActive = (MashroomDictionary*)calloc(MASHROOMS_COUNT + 1, sizeof(MashroomDictionary));
	bool work=true;
	char menuNumber;
	int mashroomsCount = 0;

	while (work)
	{
		printf("\n0 - �����, 1 - �������, 2 - �������, 3 - ������, 4 - ����������, 5 - ���������, 6 - �������� ����\n");
		scanf("%c", &menuNumber);

		switch (menuNumber)
		{
			case '0'://exit
			{
				work=false;
				break;
			}
			case '1'://create
			{
				CreateDictionary(dictActive, &mashroomsCount);
				break;
			}
			case '2'://destroy
			{
				DestroyDictionary(dictActive);
				work = false;
				break;
			}

			case '3'://print
			{
				PrintDictionary(dictActive);
				break;
			}

			case '4'://sort
			{
				SortDictionary(dictActive, mashroomsCount);
				break;
			}

			case '5':
			{
				SaveDictionary(dictActive);
				break;
			}

			case '6':
			{
				printTxt();
				break;
			}

		default:
			printf("�������� �������");
			break;
		}
	}
	return 0;
}

void SetRussian()
{
	const UINT CODE_PAGE_ID=1251;
	SetConsoleCP(CODE_PAGE_ID);
	SetConsoleOutputCP(CODE_PAGE_ID);
	setlocale(LC_ALL,"rus");
	//setlocale(LC_ALL, "");
}

void CreateDictionary(MashroomDictionary *md, int *mCount)
{
	*mCount = 0;
	while ((*mCount<3)||(*mCount>MASHROOMS_COUNT)){
		printf("\n������� ���������� ���� � ������� �� 2 �� %d: \n", MASHROOMS_COUNT);
		scanf("%d", mCount);
	}
	
	for (int i = 0; i < *mCount; i++){		
		md[i] = dictConst[i];
	}
	md[*mCount].name[0] = '\0';
	
	printf("������� ������!\n");
}

void DestroyDictionary(MashroomDictionary *md)
{
	free((void*)md);
	md=NULL;
	printf("������� ������!\n");
}

void PrintDictionary(const MashroomDictionary *md)
{
	if (md[0].name[0] == '\0') {
		return;
	}

	printf("����� ������� �� �����:\n");
	for (int i = 0; md[i].name[0]!='\0'; i++)
	{
		printf("%-18s  %-12s   %-2d  \n", md[i].name, IsEatebleText(md[i].eatable), md[i].category);
	}
}


void SortDictionary(MashroomDictionary * md, const int mCount) {
	if (md[0].name[0] == '\0') {
		return;
	}
	  
	MashroomDictionary temp;

	for (int i = 0; i < mCount -1; i++)
	{
		for (int j = i; j < mCount; j++)
		{
			if (strcoll(md[i].name, md[j].name)>0)
			{
				temp=md[i];
				md[i]=md[j];
				md[j]=temp;
			}
		}
	}
	printf("������� ������������!\n");
}

void SaveDictionary(const MashroomDictionary * md) {
	FILE *fp;
	fp = fopen(FILE_WAY, "w");
	int a = 0;

	while (md[a].name[0]!='\0') {
		fprintf(fp, "%0s %s %d\n", md[a].name, IsEatebleText(md[a].eatable), md[a].category);
		a++;
	}

	fclose(fp);
}

void printTxt() {
	FILE *fp;
	fp = fopen(FILE_WAY, "r");
	int c;

	while ((c = getc(fp)) != EOF) {
		putc(c, stdout);
	}

	//char *name;
	//int isEateble, category;

	//while (!feof(fp)) {
	//	fscanf(fp, "%0s %s %d\n");
	//}

	fclose(fp);
}

char* IsEatebleText(const bool isEatable){
	return (isEatable) ? "���������" : "�����������";
}