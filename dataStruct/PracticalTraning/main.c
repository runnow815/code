#include <stdio.h>

#include <stdlib.h>

#include "student.h"


int main() {

	system("chcp 65001 >nul");

	
	printf("\t欢迎使用学生管理系统\n"); 
	school* sc=initSys();

	


	while(1)
	{ 

	
		printf("\t===================\n");
		menuMain();



		printf("\t===================\n");
		printf("\t请选择操作\n"); 


		int choice;
		scanf("%d",&choice);


		switch(choice){

		

			case 1:

				addsStd(sc);

				break;

			case 2:

				PrintStd(sc);

				break;

			case 3:

				saveStd(sc);

				break;

			case 4:

				loadStd(sc);

				break;

			case 5:

				

				printf("学生人数为%d\n",cntStu(sc));

				break;

			case 6:

				serachStd(sc);

				break;

			case 7:

				modifyStd(sc);

				break;

			case 8:

				delStu(sc);

				break;

			case 9:
				printf("\t是否需要保存0否1是\n");
				int c;
				scanf("%d",&c);
				if(c)saveStd(sc);

				printf("\t退出系统\n");
				exit(0);

			default:

				printf("\t请输入正确的数字\n");

				break;	


		}

	

	} 

	

	

	return 0;

}