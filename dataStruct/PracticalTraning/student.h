#pragma once

#include <stdio.h>

#include <stdlib.h>

#include<string.h>

//学生结构体
//包含姓名，年龄，学号，班级号等信息
typedef struct stdu{

	char name[25];

	int age;

    char gender[5];

    int score;

    int classNo;//班级号

	int StdNo;//学号 

}student;

//整个学校的结构体
typedef struct {
    student* std;//学生数组

    int cnt;//学生人数

}school;



school* initSys();



void menuMain() ;



void addsStd(school* sc);



void saveStd(school* sc);



void loadStd(school* sc);



int cntStu(school* sc);


void delStu(school* sc);



int serachStd(school* sc);

void modifyStd(school* sc);

void PrintStd(school* sc);



