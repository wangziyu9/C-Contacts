#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    char ID[10];     	//学号
    char name[20];    	//姓名
    char sex[4];          	//性别
    double score[5];    	//五门课的成绩
    double total;       	//总成绩
    double avg;         	//平均成绩

	struct node *next;
};

typedef struct node Node, *LinkList;


void display(void);							/*显示主菜单*/
void load(LinkList H);				/*把文件信息加载到内存*/
void save(LinkList H);					/*将数据保存到磁盘*/
//void sort(LinkList H);					/*排序*/
//void find(LinkList H, int x);					/*查找*/
//int  del(LinkList H, int x);					/*删除*/
void add(LinkList H);					/*添加*/
void output(LinkList H);

void InputRecord(LinkList p);					/*输入一个学生 信息*/
void PrnRecord(LinkList p);
void SaveRecord(FILE *fp, LinkList p);


int main()
{
   

	int select;
	LinkList H = (LinkList)malloc(sizeof(Node));
	H->next = NULL;

	load(H);

	while(1)
	{
		
		display();
		scanf("%d",&select);

		switch(select)
		{
			case 1: 						/*添加*/
				add(H);	break;
			case 2: 						/*修改*/
				//edit(stu, n);	break;
			case 3:							/*排序*/
			//	sort(stu, n);	break;
			case 4:							/*查找*/
			//	find(stu, n);	break;
			case 5:							/*删除*/
			//	del(stu, &n);	break;
			case 6:							/*输出*/
				output(H);	break;
			case 7:							/*退出*/ 
				return 0;	 
		}
	}
}


/*显示主菜单*/
void display(void)
{
    system("cls");
    printf("欢迎使用本系统\n");
    printf("说明：在本系统中欲执行某功能请输入相应数字\n");
    printf("1 添加\n");
    printf("2 修改\n");
    printf("3 排序\n");
    printf("4 查找\n");
    printf("5 删除\n");
    printf("6 输出\n");
    printf("7 退出\n");
    
 }

void add(LinkList H)
{
	char ch = 'y';

	//可以进行多次添加
	while( ch == 'y')
	{
		//生成新节点
		LinkList s;
		s = (LinkList)malloc(sizeof(Node));

		InputRecord(s);

		//链表头部插入新结点s
		s->next = H->next; // 让原来的首元结点作为s的后继
		H->next = s;  // 让s做首元结点，即H的的后继
		
		printf("是否继续添加(y/n):\n");
		scanf(" %c", &ch);
	}

	save(H);
}

void InputRecord(LinkList p)
{
	double sum = 0;
	printf("请输入一个学生的学号、姓名、性别、五门课成绩\n");
	scanf("%s%s%s", p->ID, p->name, p->sex);

	for(int i = 0; i < 5; i++)
	{
		scanf("%lf", &p->score[i]);
		sum += p->score[i];
	}

	p->total  = sum;
	p->avg = sum/5;

	p->next = NULL;
}



void output(LinkList H)
{
	LinkList p;

	p = H->next; //p指向首元结点

	while(p) //当p非空，即所指结点存在
	{
		PrnRecord(p);
		p = p->next;//指向后继结点
	}
	printf("\n");
	getchar();
	getchar();

}

void PrnRecord(LinkList p)
{
	int i;
	printf("%8s%8s%8s", p->ID, p->name, p->sex);
	for(i = 0; i < 5; i++)
		printf("%6.1f", p->score[i]);
	printf("%6.1f", p->total, p->avg);
	printf("\n");
}

void save(LinkList H)
{
	FILE *fp;
	LinkList p = H->next; //p指向首元结点

	fp = fopen("d:\\f1.txt", "w");

	while(p) //当p非空，即所指结点存在
	{
		SaveRecord(fp, p);
		p = p->next; //指向后继结点
	}
	printf("\n");

	fclose(fp);
}

void SaveRecord(FILE *fp, LinkList p)
{
	int i;
	fprintf(fp, "%8s%8s%8s", p->ID, p->name, p->sex);
	for(i = 0; i < 5; i++)
		fprintf(fp, "%6.1f", p->score[i]);
	fprintf(fp,"%6.1f", p->total, p->avg);
	fprintf(fp, "\n");
}

void load(LinkList H)
{
	FILE *fp;
	char ID[16];

	if( fp = fopen("d:\\f1.txt", "r"), fp == NULL) //若文件不存在
		return ;

	while(fscanf(fp, "%s", ID) != EOF)//当成功读入一个整数
	{
		//为当前整数建立结点s
		LinkList s; 
		s = (LinkList)malloc(sizeof(Node));


		strcpy(s->ID, ID);
		fscanf(fp, "%s%s",  s->name, s->sex);

		for(int i = 0; i < 5; i++)
		{
			fscanf(fp, "%lf", &s->score[i]);		
		}

		fscanf(fp, "%lf%lf", &s->total, &s->avg);

		s->next = H->next; //让首元结点H->next作为s的后继
		H->next = s;  //让s作为首元结点，即作为H的后继
	}
}





