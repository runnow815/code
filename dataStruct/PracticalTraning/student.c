#include"student.h"

#include <stdio.h>

#include <stdlib.h>

#include<string.h>

#define maxx 1000+5
//第0个不存 最多存1000个学生

//初始化学生管理系统，分配内存并设置默认值
school* initSys(){

	school* sc=malloc(sizeof(school));
	if(sc==NULL)

	{

		printf("动态内存分配错误\n");

		return NULL;

	}
	student* std=malloc(sizeof(student)*maxx);//分配足够大的数组

	if(std==NULL)

	{

		printf("动态内存分配错误\n");
		free(sc);
		return NULL;

	}

	sc->std=std;
	sc->cnt=0;

	
	   // 不需要循环初始化所有元素，因为只使用 1..cnt
	return sc;


};

void menuMain(){

	char str[25]="学生信息" ;

	printf("\t1.录入%s\n",str);

	printf("\t2.打印%s\n",str);

	printf("\t3.保存%s\n",str);

	printf("\t4.读取%s\n",str);

	printf("\t5.统计所有学生人数\n");

	printf("\t6.查找%s\n",str);

	printf("\t7.修改%s\n",str);

	printf("\t8.删除%s\n",str);

	printf("\t9.退出系统\n");

}

static int StuNoValid(school* sc, int stdNo){

	for(int i=1;i<=sc->cnt;i++){

		if(sc->std[i].StdNo==stdNo){

			return 0;//学号已存在，不合法

		}

	}

	return 1;//学号合法

}


//输入各种信息创建学生
static student* createStd(school* sc){

	student* s=malloc(sizeof(student));
	if(s==NULL){
		printf("\t动态内存分配错误\n");
		return NULL;
	}

	printf("\t请输入学生姓名：(长度不超过10)\n");

	scanf("%s",s->name);

	printf("\t请输入学生年龄：\n");

	scanf("%d",&s->age);

	printf("\t请输入学生班级号：\n");

	scanf("%d",&s->classNo);

	while(1)
	{
		printf("\t请输入学生学号：\n");//需要保证唯一,学号合法
		int stdNo1;
		scanf("%d",&stdNo1);

		int vaild=StuNoValid(sc, stdNo1);

		if(!vaild){
			printf("\t学号已存在，无法创建学生信息,请重新输入\n");
			
		}else{
			s->StdNo=stdNo1;
			break;
		}

	}

	
	
	while(1)
	{
		printf("\t请输入学生性别：\n");
		char gender[15];
		scanf("%s",gender);

		if(strcmp(gender,"男")==0 || strcmp(gender,"女")==0){
			strcpy(s->gender,gender);
			break;
		}else{
			printf("\t性别不合法,重新输入\n");
		}

	}


	printf("\t请输入学生成绩：\n");
	scanf("%d",&s->score);



	return s;

} 




//添加学生信息到学生数组里面,先检查是否满
void addsStd(school* sc){
	

	printf("\t======================\n");
	printf("\t选择了录入学生信息\n");

	
	student* s=createStd(sc);

	if(s){
		printf("\t学生创建成功\n");
	}else{
		printf("\t学生创建失败\n");
		free(s);
		return;
	}

	if(sc->cnt>=maxx-1){
		printf("\t学生人数已满，无法添加更多学生\n");
		free(s);
		return;
	}
	++sc->cnt;//学生人数加1,0号不存储学生信息

	sc->std[sc->cnt]=*s;//添加到学生数组中
	free(s);


};



void PrintStd(school* sc){

	
	printf("\t======================\n");
	printf("\t选择了打印学生信息\n");

	for(int i=1;i<=sc->cnt;i++)

	{
		printf("\t第%d名学生:\n",i);
		printf("\t学生名字为：%s\n",sc->std[i].name);
		printf("\t学生性别为：%s\n",sc->std[i].gender);
		printf("\t学生年龄为：%d\n",sc->std[i].age);
		printf("\t学生成绩为：%d\n",sc->std[i].score);
		printf("\t学生学号为：%d\n",sc->std[i].StdNo);
		printf("\t学生班级号为：%d\n",sc->std[i].classNo);

	}

	

};



void saveStd(school* sc) {
    printf("\t======================\n");
    printf("\t选择了保存学生信息\n");

    FILE* fp = fopen("student.txt", "w");
    if (fp == NULL) {
        printf("\t打开文件失败，无法保存学生信息\n");
        return;
    }
    printf("\t文件打开成功，准备写入...\n");   // ← 探针1

    for (int i = 1; i <= sc->cnt; i++) {
        printf("\t正在写入第 %d 条记录...\n", i); // ← 探针2
        student st = sc->std[i];
        fprintf(fp, "%d %d %d %d %s %s\n", st.classNo, st.StdNo, st.age, st.score, st.name, st.gender);
    }
    printf("\t写入循环结束，准备关闭文件...\n");   // ← 探针3

    fclose(fp);
    printf("\t保存了%d条学生信息\n", sc->cnt);
}


//需要先清空原来的学生信息
//再从文件中读取学生信息并添加到学生数组中
void loadStd(school* sc){

	
	printf("\t======================\n");
	printf("\t选择了读取学生信息\n");

	FILE* fp=fopen("student.txt","r");//打开文件
	if(fp==NULL)return;

	sc->cnt=0;//清空原来的学生信息
	
	while(fscanf(fp,"%d %d %d %d %s %s\n",&sc->std[sc->cnt+1].classNo,&sc->std[sc->cnt+1].StdNo,&sc->std[sc->cnt+1].age,&sc->std[sc->cnt+1].score,sc->std[sc->cnt+1].name,sc->std[sc->cnt+1].gender)==6){
		sc->cnt++;//学生人数加1
	}

	fclose(fp);
	printf("\t读取了%d条学生信息\n",sc->cnt);
	

};



int cntStu(school* sc){
	printf("\t======================\n");
	printf("\t选择了统计学生人数\n");
	

	return sc->cnt;

}



//找到与否返回i/0 
//通过学号顺序查找学生信息
int serachStd(school* sc){

	printf("\t======================\n");
	printf("\t选择了查找学生信息\n");

	printf("\t请输入要查找的学生学号：\n");

	int stdNo;

	scanf("%d", &stdNo);

	
	for(int i=1;i<=sc->cnt;i++){

		if(sc->std[i].StdNo==stdNo){
			printf("\t找到了学生信息！\n");
			printf("\t学生名字为：%s\n",sc->std[i].name);
			printf("\t学生性别为：%s\n",sc->std[i].gender);
			printf("\t学生年龄为：%d\n",sc->std[i].age);
			printf("\t学生成绩为：%d\n",sc->std[i].score);
			printf("\t学生学号为：%d\n",sc->std[i].StdNo);
			printf("\t学生班级号为：%d\n",sc->std[i].classNo);

			
			return i;

		}

	}

	return 0;//没找到

}


static int ToolSer(school* sc,int id){
	for(int i=1;i<=sc->cnt;i++){

		if(sc->std[i].StdNo==id){
			return i;//找到了学生信息，返回索引

		}

	}

	return 0;//没找到
}

//输入学号修改学生信息
void modifyStd(school* sc){

	printf("\t======================\n");

	printf("\t选择了修改学生信息\n");

	printf("\t请输入要修改的学生学号：\n");
	int stdNo;
	scanf("%d", &stdNo);

	int idx=ToolSer(sc,stdNo);//找


	if(idx){

		printf("\t请输入新的学生信息：\n");

		student* s=createStd(sc);

		sc->std[idx]=*s;//修改学生信息

	} else printf("\t没有找到学生信息，无法修改\n");



}



//输入姓名删除 (学号唯一更好删除)
//输入学号删除
void delStu(school* sc){

	printf("\t======================\n");

	

	printf("\t选择了删除学生信息\n");

	printf("\t请输入要删除的学生学号：\n");
	int stdNo;
	scanf("%d", &stdNo);

	int idx=ToolSer(sc,stdNo);//找第几个
	if(idx){
		
		//数组删除(前移动覆盖)
		for(int i=idx;i < sc->cnt;i++){
			sc->std[i]=sc->std[i+1];
		}
		sc->cnt--;//学生人数减1
		

	}else printf("\t没有找到学生信息，无法删除\n");

	

};