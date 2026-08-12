#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STU 100
#define FILE_NAME "student_data.txt"

typedef struct {
    int id;
    char name[24];
    float score;
}Student;

Student stu[MAX_STU];
int count = 0;

// 将全部数据保存到本地文件
void saveToFile(void)
{
    FILE *fp = fopen(FILE_NAME,"w");
    if(fp == NULL){
        printf("保存文件失败！\n");
        return;
    }
    for(int i = 0; i < count; i++)
    {
        fprintf(fp,"%d %s %.2f\n",stu[i].id,stu[i].name,stu[i].score);
    }
    fclose(fp);
    printf("?数据已保存到文件\n");
}

// 程序启动，从文件读取历史数据
void loadFromFile(void)
{
    FILE *fp = fopen(FILE_NAME,"r");
    if(fp == NULL){
        return;
    }
    count = 0;
    while(fscanf(fp,"%d %s %f",&stu[count].id,stu[count].name,&stu[count].score)!=EOF)
    {
        count++;
    }
    fclose(fp);
}

// 添加学生
void addStudent(void)
{
    if(count >= MAX_STU){
        printf("学生数量已经达到上限！\n");
        return;
    }
    printf("请输入学号：");
    scanf("%d",&stu[count].id);
    printf("请输入姓名：");
    scanf("%s",stu[count].name);
    printf("请输入分数：");
    scanf("%f",&stu[count].score);
    count++;
    printf("?学生添加成功\n");
    saveToFile();
}

// 展示全部学生
void showAll(void)
{
    if(count == 0){
        printf("暂无学生记录\n");
        return;
    }
    printf("\n========学生信息列表========\n");
    printf("学号\t姓名\t分数\n");
    for(int i = 0; i < count; i++)
    {
        printf("%d\t%s\t%.2f\n",stu[i].id,stu[i].name,stu[i].score);
    }
}

// 按学号查找
void searchById(void)
{
    int id;
    printf("输入要查询的学号：");
    scanf("%d",&id);
    for(int i = 0; i < count; i++)
    {
        if(stu[i].id == id)
        {
            printf("?找到：学号:%d  姓名:%s  分数:%.2f\n",stu[i].id,stu[i].name,stu[i].score);
            return;
        }
    }
    printf("?未找到该学号\n");
}

// 删除学生
void delStudent(void)
{
    int id,i,j;
    printf("输入要删除学生学号：");
    scanf("%d",&id);
    for(i=0;i<count;i++)
    {
        if(stu[i].id == id)
        {
            for(j=i;j<count-1;j++)
            {
                stu[j]=stu[j+1];
            }
            count--;
            printf("?删除完成\n");
            saveToFile();
            return;
        }
    }
    printf("?没有找到该学生\n");
}

// 修改学生分数
void modifyScore(void)
{
    int id;
    float newScore;
    printf("输入要修改的学号：");
    scanf("%d",&id);
    for(int i=0;i<count;i++)
    {
        if(stu[i].id == id)
        {
            printf("请输入新分数：");
            scanf("%f",&newScore);
            stu[i].score = newScore;
            printf("?分数修改完毕\n");
            saveToFile();
            return;
        }
    }
    printf("?未找到学生\n");
}

// 按分数从高到低排序
void sortByScore(void)
{
    for(int i=0;i<count-1;i++)
    {
        for(int j=0;j<count-i-1;j++)
        {
            if(stu[j].score < stu[j+1].score)
            {
                Student temp = stu[j];
                stu[j] = stu[j+1];
                stu[j+1] = temp;
            }
        }
    }
    printf("\n=====按分数降序排列=====\n");
    printf("学号\t姓名\t分数\n");
    for(int i=0;i<count;i++)
    {
        printf("%d\t%s\t%.2f\n",stu[i].id,stu[i].name,stu[i].score);
    }
}

int main(void)
{
    loadFromFile(); //启动读取本地保存的数据
    int select;
    while(1)
    {
        printf("\n====学生成绩管理系统====\n");
        printf("1.新增学生\n");
        printf("2.全部学生信息\n");
        printf("3.学号查询学生\n");
        printf("4.删除学生记录\n");
        printf("5.修改学生分数\n");
        printf("6.按分数降序排序\n");
        printf("0.退出程序\n");
        printf("请输入功能选择：");
        scanf("%d",&select);
        switch(select)
        {
            case 1: addStudent();break;
            case 2: showAll();break;
            case 3: searchById();break;
            case 4: delStudent();break;
            case 5: modifyScore();break;
            case 6: sortByScore();break;
            case 0: printf("程序退出\n");exit(0);
            default: printf("输入无效，请重新选择！\n");
        }
    }
    return 0;
}