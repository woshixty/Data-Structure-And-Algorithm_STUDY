#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


typedef struct _Studet{
    char num[20];
    char name[20];
    int score[4];
    int sum;
}Student;

typedef struct _Node{
    Student stu;
    struct _Node* next;
}Node;
Node* g_pHead=NULL;

void search(void);
void print(void);
void input(void);
void output(void);
void save(void);
void read(void);
void stastics(void);
void srchadchange(int key);
void Delete(void);
void sort(void);
void quit(void);
int judge(int a,int b,int c);

int main()
{
    int a=1;
    while(1){
        if(a)
            search();
        a=0;
        system("cls");
        print();
        char ch=getchar();
        switch(ch)
        {
            case'1':
                input();
                break;

            case'2':
                output();
                break;

            case'3':
                save();
                break;

            case'4':
                read();
                break;

            case'5':
                stastics();
                break;

            case'6':
                srchadchange(0);
                break;

            case'7':
                srchadchange(1);
                break;

            case'8':
                Delete();
                break;

            case'9':
                sort();
                break;

            case'0':
                quit();
                return 0;
        }
    }
    return 0;
}

void search(void)
{
    char ch;
    FILE* pFile=fopen("C:\\stu.txt","r");
    if(pFile!=NULL)
    {
        ch=fgetc(pFile);
        fclose(pFile);
        if(ch!=EOF){
            printf("检测到您的电脑上存在stu.txt文档，是否读取数据？\n");
            printf("1.是  2.否\n");
            int k;
            do{
                scanf("%d",&k);
                if(k!=1&&k!=2)
                    printf("输入有误，请重新输入>_<\n");
            }while(k!=1&&k!=2);
            if(k==1)
                read();
        }
        return;
    }
    return;
}

void input(void)
{
    int k,s;
    Node* p=(Node*)malloc(sizeof(Node));
    p->next=NULL;

    printf("请输入学号\n");
    do{
        scanf("%s",p->stu.num);
        s=strlen(p->stu.num);
        if(s!=8)
            printf("学号长度为8位，输入有误，请重新输入*_*\n");
    }while(s!=8);
    printf("请输入姓名\n");
    scanf("%s",p->stu.name);
    printf("请输入数学语文英语三科考试成绩(满分为100)\n");
    do{
        scanf("%d%d%d",&p->stu.score[0],&p->stu.score[1],&p->stu.score[2]);
        k=judge(p->stu.score[0],p->stu.score[1],p->stu.score[2]);
        if(k!=1)
            printf("输入有误，请重新输入^_^\n");
    }while(k!=1);

    p->stu.sum=p->stu.score[0]+p->stu.score[1]+p->stu.score[2];
    if(g_pHead==NULL)
        g_pHead=p;
    else{
        p->next=g_pHead;
        g_pHead=p;
    }
    printf("录入成功！\n");
    system("pause");
}

void print(void)
{
    printf("*******************************************************\n");
    printf("*             1. 输入学生信息                         *\n");
    printf("*             2. 打印学生信息                         *\n");
    printf("*             3. 保存学生信息                         *\n");
    printf("*             4. 读取学生信息                         *\n");
    printf("*             5. 统计学生人数                         *\n");
    printf("*             6. 查找学生信息                         *\n");
    printf("*             7. 修改学生信息                         *\n");
    printf("*             8. 删除学生信息                         *\n");
    printf("*             9. 学生总分降序                         *\n");
    printf("*             0. 退出系统                             *\n");
    printf("*******************************************************\n");
    printf("请输入您的选择，并按下回车键 \n");
}

void output(void)
{
    if(g_pHead==NULL){
        printf("没有数据，请输入或者读取学生数据后再操作\n");
        system("pause");
        return;
    }
    printf("************************************************************\n");
    printf("*学号*\t \t *姓名*\t*数学*\t*语文*\t*英语*\t*总分*\t   *\n");
    printf("************************************************************\n");
    Node* p=g_pHead;
    while(p!=NULL)
    {
        printf("*%s*\t *%s*\t *%d*\t *%d*\t *%d*\t *%d*\t   *\n",p->stu.num,p->stu.name,p->stu.score[0],p->stu.score[1],p->stu.score[2],p->stu.sum);
        printf("************************************************************\n");
        p=p->next;
    }
    system("pause");
}

void save(void)
{
    FILE* fp=fopen("C:\\stu.txt","w+");
    if(fp==NULL)
    {
        printf("写入文件失败\n");
        return;
    }

    Node* p=g_pHead;
    while(p!=NULL)
    {
        fprintf(fp,"%s %s %d %d %d %d\n",
        //fwrite(&p->stu,1,sizeof(Student),fp);
                p->stu.num,
                p->stu.name,
                p->stu.score[0],
                p->stu.score[1],
                p->stu.score[2],
                p->stu.sum
                );
        p=p->next;

    }

    fclose(fp);

    printf("数据保存成功\n");
    system("pause");
}

void read(void)
{
    Node* p;
    p=g_pHead;
    FILE* pFile=fopen("C:\\stu.txt","a+");
    char ch=fgetc(pFile);
    if(pFile==NULL||ch==EOF)
    {
        printf("打开文件失败,c盘中无文档或者文档为空\n");
        system("pause");
        return;
    }
    /*
    if(g_pHead!=NULL)
        while(p->next!=NULL)
            p=p->next;
            */
    while(!feof(pFile)){
        Node* ptemp=(Node*)malloc(sizeof(Node));
        fscanf(pFile,"%s %s %d %d %d %d\n",
                ptemp->stu.num,
                ptemp->stu.name,
                &ptemp->stu.score[0],
                &ptemp->stu.score[1],
                &ptemp->stu.score[2],
                &ptemp->stu.sum
                );
                /*
        if(g_pHead==NULL){
            g_pHead=ptemp;
            p=g_pHead;
        }
        else{
            p->next=ptemp;
            p=p->next;
            p->next=NULL;
        }
        */
        ptemp->next=g_pHead;
        g_pHead=ptemp;
    }
    fclose(pFile);
    printf("数据读入成功\n");
    system("pause");
}

void stastics(void)
{
    int n=0;
    Node* p=g_pHead;
    while(p!=NULL){
        n++;
        p=p->next;
    }
    printf("共有%d名学生参与统计\n",n);
    system("pause");
}

void srchadchange(int key)
{
    if(g_pHead==NULL){
        printf("没有数据，请输入或者读取学生数据后再操作\n");
        system("pause");
        return;
    }
    int flag=0,s;
    if(key)
        printf("现在开始查找您要修改的学生信息\n");
    printf("您要通过哪种方式查找学生？\n");
    printf("1.学号  2.姓名\n");
    int k;
    do{
        scanf("%d",&k);
        if(k!=1&&k!=2)
            printf("输入有误，请重新输入>_<\n");
    }while(k!=1&&k!=2);
    Node* p=g_pHead;

    if(k==1){
        char a[100];
        printf("请输入您要查找学生的学号\n");
        do{
            scanf("%s",a);
            s=strlen(a);
            if(s!=8)
                printf("学号长度为8位，输入有误，请重新输入*_*\n");
        }while(s!=8);
        while(p!=NULL){
            if(strcmp(p->stu.num,a)==0){
                flag=1;
                break;
            }
            p=p->next;
        }
    }

    if(k==2){
        char a[100];
        printf("请输入您要查找学生的姓名\n");
        scanf("%s",a);
        while(p!=NULL){
            if(strcmp(p->stu.name,a)==0){
                flag=1;
                break;
            }
            p=p->next;
        }
    }

    if(flag){
                printf("您要查找的学生信息已找到^_^\n");
                printf("***********************************************************\n");
                printf("*学号*\t \t *姓名*\t*数学*\t*语文*\t*英语*\t*总分*\t  *\n");
                printf("*%s\t *%s*\t *%d*\t *%d*\t *%d*\t *%d*\t  *\n",p->stu.num,p->stu.name,p->stu.score[0],p->stu.score[1],p->stu.score[2],p->stu.sum);
                printf("***********************************************************\n");
            }
            else
                printf("您要查找的学生信息未找到~_~\n");

    if(key&&flag){
        printf("您确定要修改吗\n");
        printf("1.是  2.否\n");

        do{
        scanf("%d",&k);
        if(k!=1&&k!=2)
            printf("输入有误，请重新输入>_<\n");
            }while(k!=1&&k!=2);

        if(k==1){
            printf("请输入新的学号\n");
            do{
            scanf("%s",p->stu.num);
            s=strlen(p->stu.num);
            if(s!=8)
                printf("学号长度为8位，输入有误，请重新输入*_*\n");
            }while(s!=8);

            printf("请输入新的姓名\n");
            scanf("%s",p->stu.name);
            printf("请输入新的三门考试成绩\n");
            scanf("%d%d%d",&p->stu.score[0],&p->stu.score[1],&p->stu.score[2]);
            p->stu.sum=p->stu.score[0]+p->stu.score[1]+p->stu.score[2];
            printf("\n学生信息已完成^_^\n");
            printf("***********************************************************\n");
            printf("*学号*\t \t *姓名*\t*数学*\t*语文*\t*英语*\t*总分*\t  *\n");
            printf("*%s\t *%s*\t *%d*\t *%d*\t *%d*\t *%d*\t  *\n",p->stu.num,p->stu.name,p->stu.score[0],p->stu.score[1],p->stu.score[2],p->stu.sum);
            printf("***********************************************************\n");
        }
    }
    system("pause");
}

void Delete(void)
{
    if(g_pHead==NULL){
        printf("没有数据，请输入或者读取学生数据后再操作\n");
        system("pause");
        return;
    }
    int flag=0,s;
    printf("现在开始查找您要删除的学生信息\n");
    printf("您要通过哪种方式查找学生？\n");
    printf("1.学号  2.姓名\n");
    int k;
    do{
        scanf("%d",&k);
        if(k!=1&&k!=2)
            printf("输入有误，请重新输入>_<\n");
    }while(k!=1&&k!=2);
    Node* p=g_pHead;
    Node* p2=NULL;
    Node* p3=NULL;

    if(k==1){
        char a[100];
        printf("请输入您要删除学生的学号\n");
        do{
            scanf("%s",a);
            s=strlen(a);
            if(s!=8)
                printf("学号长度为8位，输入有误，请重新输入*_*\n");
        }while(s!=8);
        while(p!=NULL){
            if(strcmp(p->stu.num,a)==0){
                flag=1;
                break;
            }
            p=p->next;
        }
    }

    if(k==2){
        char a[100];
        printf("请输入您要删除学生的姓名\n");
        scanf("%s",a);
        while(p!=NULL){
            if(strcmp(p->stu.name,a)==0){
                flag=1;
                break;
            }
            p=p->next;
        }
    }

    if(flag){
                printf("您要删除的学生信息已找到^_^\n");
                printf("***********************************************************\n");
                printf("*学号*\t \t *姓名*\t*数学*\t*语文*\t*英语*\t*总分*\t      *\n");
                printf("*%s\t *%s*\t *%d*\t *%d*\t *%d*\t *%d*\t       *\n",p->stu.num,p->stu.name,p->stu.score[0],p->stu.score[1],p->stu.score[2],p->stu.sum);
                printf("***********************************************************\n");
                printf("您确定要删除吗\n");
                printf("1.是  2.否\n");

                do{
                    scanf("%d",&k);
                    if(k!=1&&k!=2)
                        printf("输入有误，请重新输入>_<\n");
                    }while(k!=1&&k!=2);

                    if(k==1){
                        if(p==g_pHead){
                            p2=g_pHead;
                            p=g_pHead->next;
                            g_pHead=p;
                            free(p2);
                        }
                        else{
                            p3=g_pHead;
                            p2=g_pHead->next;
                            while(1){
                                if(p==p2){
                                    p3->next=p2->next;
                                    free(p2);
                                    break;
                                }
                                p3=p2;
                                p2=p2->next;
                            }
                        }
                        printf("已删除\n");
                    }
            }
            else
                printf("您要删除的学生信息未找到~_~\n");
            system("pause");

}

void sort(void)
{
    if(g_pHead==NULL){
        printf("没有数据，请输入或者读取学生数据后再操作\n");
        system("pause");
        return;
    }

    Node* NewHead=NULL;
    Node* p1=NULL;
    Node* p2=g_pHead;
    Node* t=NULL;

    while(p2!=NULL){
        p1=p2;
        p2=p2->next;
        if(NewHead==NULL){
            p1->next=NULL;
            NewHead=p1;
            continue;
        }

        if(p1->stu.sum>NewHead->stu.sum){
            p1->next=NewHead;
            NewHead=p1;
            continue;
        }

        Node* q1=NewHead->next;
        Node* q2=NewHead;
        while(q1!=NULL&&p1->stu.sum<q1->stu.sum){
            q1=q1->next;
            q2=q2->next;
        }
        if(q1==NULL){
            q2->next=p1;
            p1->next=NULL;
        }
        else{
            p1->next=q1;
            q2->next=p1;

        }
    }
    g_pHead=NewHead;
    printf("按总分降序的排序已完成\n");
    system("pause");


}

void quit(void)
{
    int k;
    printf("是否将信息储存至stu.txt中？\n");
    printf("1.是  2.否\n");
    do{
        scanf("%d",&k);
        if(k!=1&&k!=2)
            printf("输入有误，请重新输入>_<\n");
        }while(k!=1&&k!=2);
    if(k==1)
        save();
    printf("欢迎下次光临^_^\n");
}

int judge(int a,int b,int c)
{
    int x=1,y=1,z=1;
    if(a<0||a>100)
        x=0;
    if(b<0||b>100)
        y=0;
    if(c<0||c>100)
        z=0;
    return x*y*z;
}












