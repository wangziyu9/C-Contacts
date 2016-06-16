 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100
typedef struct student
{
    char ID[20];
    char name[20];
    char sex;
    double score[5];
    double total;
    double avg;
}STU;
void display();                       /*显示主菜单*/
void load(STU s[], int *nptr);        /*把学生信息加载到内存*/
void save(STU s[], int n);            /*将数据保存到磁盘*/
void sort(STU s[], int n);            /*排序*/
void InputRecord(STU s[], int i);
void find(STU s[], int n);             /*查找*/
void del(STU s[], int *nptr);           /*删除*/
void add(STU s[], int *nptr);           /*添加一条记录*/
void edit(STU s[], int n);              /*修改一条记录*/
void DeleteAll(STU s[], int *nptr);
void DeleteRecord(STU s[], int *nptr);
int FindByNum(STU s[], int n, char *str);
void output(STU s[], int n);              /*输出所有信息*/
void PintRecord(STU *sptr);
int main()
{
    STU s[N];
    int n, select;
    load(s, &n);
    while(1)
    {
        display();
        scanf("%d", &select);
        switch(select)
        {
        case 1:
            add(s, &n); break;
         case 2:
            edit(s, n); break;
         case 3:
            sort(s, n); break;
         case 4:
           find(s, n); break;
         case 5:
            del(s, &n); break;
         case 6:
            output(s, n); break;
         case 7:
            return 0;
        }
    }
}
void display()
{
    system("cls");
    printf("欢迎使用本学f生成绩管理系统\n");
    printf("说明：在本系统中欲执行某项功能请输入相应数字\n");
    printf("1 添加\n");
    printf("2 修改\n");
    printf("3 排序\n");
    printf("4 查找\n");
    printf("5 删除\n");
    printf("6 输出\n");
    printf("7 退出\n");

}
void load(STU s[], int *nptr)
{
    FILE *fp;
    int i;
    fp=fopen("d:\\student.dat", "r");
    for(i=0; fread(&s[i], sizeof(STU), 1, fp)!=0; i++);
    *nptr=i;
    fclose(fp);
}
void save(STU s[], int n)
{
    FILE *fp;
    fp=fopen("d:\\student.dat", "w");
    fwrite(s, n*sizeof(s[0]), 1, fp);
    fclose(fp);
}
void sort(STU s[], int n)
{
    int select, i, j;
    int (*cmp)(STU a, STU b);
    int ScoreAsc(STU a, STU b);
    int ScoreDes(STU a, STU b);
    int NameAsc(STU a, STU b);
    printf("1 按总分升序排列\n");
    printf("2 按总分降序排列\n");
    printf("3 按姓名排列\n");
    printf("请输入选择：\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1: cmp=ScoreAsc; break;
        case 2: cmp=ScoreDes; break;
        case 3: cmp=NameAsc; break;
        default: return;
    }
    for(i=0; i<n-1; i++)
    {
       for(j=i+1; j<n; j++)
        if((*cmp)(s[i], s[j])>0)
       {
           STU temp;
           temp=s[i];
           s[i]=s[j];
           s[j]=temp;
       }
    }
    output(s, n);
}
    int ScoreAsc(STU a, STU b)
    {
        return a.total>b.total?1:-1;
    }
    int ScoreDes(STU a, STU b)
    {
        return a.total<b.total?1:-1;
    }
    int NameAsc(STU a, STU b)
    {
        return strcmp(a.name, b.name);
    }

void find(STU s[], int n)
{
    int index;
    char str[20];
    printf("请输入学号:\n");
    scanf("%s", str);
    index=FindByNum(s, n, str);
    if(index>=0)
        PintRecord(&s[index]);
    else
        printf("该学生信息不存在\n");
    system("pause");
}
void del(STU s[], int *nptr)
{
    int i, index;
    char str[20];
    printf("请输入学号:\n");
    scanf("%s", str);
    index=FindByNum(s, *nptr, str);
    if(index<0)
    {
        printf("该学生信息不存在\n");

    return ;
}
    for(i=index; i<*nptr-1; i++)

    s[i]=s[i+1];
    (*nptr)--;
    printf("删除成功\n");

    save(s, *nptr);
}
void add(STU s[], int *nptr)
{
    char sel='y';
    while(sel=='y')
    {
        InputRecord(s, (*nptr)++);
        printf("是否继续添加(yes--y, no--others)\n");
        scanf(" %c", &sel);
    }
    save(s, *nptr);
}
void edit(STU s[], int n)
{
    int i, index;
    char sel;
    char str[20];
    printf("请输入学号:\n");
    scanf("%s", str);
    index=FindByNum(s, n, str);
    if(index<0)
    {
        printf("该学生信息不存在\n");
        return;
    }
    printf("修改前的原纪录如下: \n");
    PintRecord(&s[index]);
    printf("是否修改姓名?请输入 y or n:\n");
    scanf(" %c", &sel);
    if(sel=='y')
    {
        printf("请输入姓名:\n");
        scanf("%s", s[index].name);
    }
    printf("是否修改性别?请输入 y or n:\n");
    scanf(" %c", &sel);
    if(sel=='y')
    {
        printf("请输入 f or m:\n");
        scanf(" %c", &s[index].sex);
    }
    printf("是否修改成绩?input y or n:\n");
    scanf(" %c", &sel);
    if(sel=='y')
    {
        s[index].total=0;
        printf("输5门学科成绩:\n");
        for(i=0; i<5; i++)
        {
            scanf("%lf", &s[index].score[i]);
            s[index].total=s[index].total+s[index].score[i];
        }
        s[index].avg=s[index].total/5;
    }
    save(s, n);
}
void output(STU s[], int n)
{
    int i;
    for(i=0; i<n; i++)
        PintRecord(&s[i]);
    system("pause");
}
void PintRecord(STU *sptr)
{
    int i;
    printf("%12s%8s%4c", sptr->ID, sptr->name, sptr->sex);
    for(i=0; i<5; i++)
        printf("%8.2f", sptr->score[i]);
    printf("%8.2f%8.2f", sptr->total, sptr->avg);
    printf("\n");
}
int FindByNum(STU s[], int n, char *str)
{
    int i;
    for(i=0; i<n; i++)
       if(strcmp(s[i].ID, str)==0)
          return i;
     return -1;
}
void InputRecord(STU s[], int i)
{
    int j;
    printf("请输入第%d个学生信息\n", i+1);
    printf("请输入学生学号（学号小于9位数字组成）\n");
    scanf("%s", s[i].ID);
    printf("请输入学生姓名\n");
    scanf("%s", s[i].name);
    printf("请输入学生性别（f或m f 代表女性 m 代表男性\n");
    scanf(" %c", &s[i].sex);
    printf("请输入五门课成绩(0-100)\n");
    s[i].total=0;
    for(j=0; j<5; j++)
    {
        scanf("%lf", &s[i].score[j]);
        s[i].total+=s[i].score[j];
    }
    s[i].avg=s[i].total/5;
}
