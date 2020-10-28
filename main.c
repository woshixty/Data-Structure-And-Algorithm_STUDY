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
            printf("��⵽���ĵ����ϴ���stu.txt�ĵ����Ƿ��ȡ���ݣ�\n");
            printf("1.��  2.��\n");
            int k;
            do{
                scanf("%d",&k);
                if(k!=1&&k!=2)
                    printf("������������������>_<\n");
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

    printf("������ѧ��\n");
    do{
        scanf("%s",p->stu.num);
        s=strlen(p->stu.num);
        if(s!=8)
            printf("ѧ�ų���Ϊ8λ��������������������*_*\n");
    }while(s!=8);
    printf("����������\n");
    scanf("%s",p->stu.name);
    printf("��������ѧ����Ӣ�����ƿ��Գɼ�(����Ϊ100)\n");
    do{
        scanf("%d%d%d",&p->stu.score[0],&p->stu.score[1],&p->stu.score[2]);
        k=judge(p->stu.score[0],p->stu.score[1],p->stu.score[2]);
        if(k!=1)
            printf("������������������^_^\n");
    }while(k!=1);

    p->stu.sum=p->stu.score[0]+p->stu.score[1]+p->stu.score[2];
    if(g_pHead==NULL)
        g_pHead=p;
    else{
        p->next=g_pHead;
        g_pHead=p;
    }
    printf("¼��ɹ���\n");
    system("pause");
}

void print(void)
{
    printf("*******************************************************\n");
    printf("*             1. ����ѧ����Ϣ                         *\n");
    printf("*             2. ��ӡѧ����Ϣ                         *\n");
    printf("*             3. ����ѧ����Ϣ                         *\n");
    printf("*             4. ��ȡѧ����Ϣ                         *\n");
    printf("*             5. ͳ��ѧ������                         *\n");
    printf("*             6. ����ѧ����Ϣ                         *\n");
    printf("*             7. �޸�ѧ����Ϣ                         *\n");
    printf("*             8. ɾ��ѧ����Ϣ                         *\n");
    printf("*             9. ѧ���ֽܷ���                         *\n");
    printf("*             0. �˳�ϵͳ                             *\n");
    printf("*******************************************************\n");
    printf("����������ѡ�񣬲����»س��� \n");
}

void output(void)
{
    if(g_pHead==NULL){
        printf("û�����ݣ���������߶�ȡѧ�����ݺ��ٲ���\n");
        system("pause");
        return;
    }
    printf("************************************************************\n");
    printf("*ѧ��*\t \t *����*\t*��ѧ*\t*����*\t*Ӣ��*\t*�ܷ�*\t   *\n");
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
        printf("д���ļ�ʧ��\n");
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

    printf("���ݱ���ɹ�\n");
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
        printf("���ļ�ʧ��,c�������ĵ������ĵ�Ϊ��\n");
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
    printf("���ݶ���ɹ�\n");
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
    printf("����%d��ѧ������ͳ��\n",n);
    system("pause");
}

void srchadchange(int key)
{
    if(g_pHead==NULL){
        printf("û�����ݣ���������߶�ȡѧ�����ݺ��ٲ���\n");
        system("pause");
        return;
    }
    int flag=0,s;
    if(key)
        printf("���ڿ�ʼ������Ҫ�޸ĵ�ѧ����Ϣ\n");
    printf("��Ҫͨ�����ַ�ʽ����ѧ����\n");
    printf("1.ѧ��  2.����\n");
    int k;
    do{
        scanf("%d",&k);
        if(k!=1&&k!=2)
            printf("������������������>_<\n");
    }while(k!=1&&k!=2);
    Node* p=g_pHead;

    if(k==1){
        char a[100];
        printf("��������Ҫ����ѧ����ѧ��\n");
        do{
            scanf("%s",a);
            s=strlen(a);
            if(s!=8)
                printf("ѧ�ų���Ϊ8λ��������������������*_*\n");
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
        printf("��������Ҫ����ѧ��������\n");
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
                printf("��Ҫ���ҵ�ѧ����Ϣ���ҵ�^_^\n");
                printf("***********************************************************\n");
                printf("*ѧ��*\t \t *����*\t*��ѧ*\t*����*\t*Ӣ��*\t*�ܷ�*\t  *\n");
                printf("*%s\t *%s*\t *%d*\t *%d*\t *%d*\t *%d*\t  *\n",p->stu.num,p->stu.name,p->stu.score[0],p->stu.score[1],p->stu.score[2],p->stu.sum);
                printf("***********************************************************\n");
            }
            else
                printf("��Ҫ���ҵ�ѧ����Ϣδ�ҵ�~_~\n");

    if(key&&flag){
        printf("��ȷ��Ҫ�޸���\n");
        printf("1.��  2.��\n");

        do{
        scanf("%d",&k);
        if(k!=1&&k!=2)
            printf("������������������>_<\n");
            }while(k!=1&&k!=2);

        if(k==1){
            printf("�������µ�ѧ��\n");
            do{
            scanf("%s",p->stu.num);
            s=strlen(p->stu.num);
            if(s!=8)
                printf("ѧ�ų���Ϊ8λ��������������������*_*\n");
            }while(s!=8);

            printf("�������µ�����\n");
            scanf("%s",p->stu.name);
            printf("�������µ����ſ��Գɼ�\n");
            scanf("%d%d%d",&p->stu.score[0],&p->stu.score[1],&p->stu.score[2]);
            p->stu.sum=p->stu.score[0]+p->stu.score[1]+p->stu.score[2];
            printf("\nѧ����Ϣ�����^_^\n");
            printf("***********************************************************\n");
            printf("*ѧ��*\t \t *����*\t*��ѧ*\t*����*\t*Ӣ��*\t*�ܷ�*\t  *\n");
            printf("*%s\t *%s*\t *%d*\t *%d*\t *%d*\t *%d*\t  *\n",p->stu.num,p->stu.name,p->stu.score[0],p->stu.score[1],p->stu.score[2],p->stu.sum);
            printf("***********************************************************\n");
        }
    }
    system("pause");
}

void Delete(void)
{
    if(g_pHead==NULL){
        printf("û�����ݣ���������߶�ȡѧ�����ݺ��ٲ���\n");
        system("pause");
        return;
    }
    int flag=0,s;
    printf("���ڿ�ʼ������Ҫɾ����ѧ����Ϣ\n");
    printf("��Ҫͨ�����ַ�ʽ����ѧ����\n");
    printf("1.ѧ��  2.����\n");
    int k;
    do{
        scanf("%d",&k);
        if(k!=1&&k!=2)
            printf("������������������>_<\n");
    }while(k!=1&&k!=2);
    Node* p=g_pHead;
    Node* p2=NULL;
    Node* p3=NULL;

    if(k==1){
        char a[100];
        printf("��������Ҫɾ��ѧ����ѧ��\n");
        do{
            scanf("%s",a);
            s=strlen(a);
            if(s!=8)
                printf("ѧ�ų���Ϊ8λ��������������������*_*\n");
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
        printf("��������Ҫɾ��ѧ��������\n");
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
                printf("��Ҫɾ����ѧ����Ϣ���ҵ�^_^\n");
                printf("***********************************************************\n");
                printf("*ѧ��*\t \t *����*\t*��ѧ*\t*����*\t*Ӣ��*\t*�ܷ�*\t      *\n");
                printf("*%s\t *%s*\t *%d*\t *%d*\t *%d*\t *%d*\t       *\n",p->stu.num,p->stu.name,p->stu.score[0],p->stu.score[1],p->stu.score[2],p->stu.sum);
                printf("***********************************************************\n");
                printf("��ȷ��Ҫɾ����\n");
                printf("1.��  2.��\n");

                do{
                    scanf("%d",&k);
                    if(k!=1&&k!=2)
                        printf("������������������>_<\n");
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
                        printf("��ɾ��\n");
                    }
            }
            else
                printf("��Ҫɾ����ѧ����Ϣδ�ҵ�~_~\n");
            system("pause");

}

void sort(void)
{
    if(g_pHead==NULL){
        printf("û�����ݣ���������߶�ȡѧ�����ݺ��ٲ���\n");
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
    printf("���ֽܷ�������������\n");
    system("pause");


}

void quit(void)
{
    int k;
    printf("�Ƿ���Ϣ������stu.txt�У�\n");
    printf("1.��  2.��\n");
    do{
        scanf("%d",&k);
        if(k!=1&&k!=2)
            printf("������������������>_<\n");
        }while(k!=1&&k!=2);
    if(k==1)
        save();
    printf("��ӭ�´ι���^_^\n");
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












