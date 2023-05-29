#include<stdio.h>
#include<windows.h>
#include<stdlib.h>  
#include<string.h>
#include<math.h>
#include<conio.h>
#define N 100

typedef struct administrator
{
	char id[N];								// �û���
	char password[N];						// ����

	struct administrator* next;				// ָ����
}ADMIN;

typedef struct user
{
	char id[N];								// �û���
	char password[N];						// ����

	struct user* next;						// ָ����
}USER;

typedef struct node
{
	char name[N];				// ����
	char type[N];				// ����
	int time;					// ʱ��
	char day[N];				// ����
	char start[N];				// ��ʼʱ��
	char site[N];				// �ص�
	int price;					// �۸�
	int num;					// ����
	int id;						// ���
	int sum;                    // Ʊ�� 
	int seat[N][N];				// ��λ

	struct node* next;			// ָ����
}NODE;

typedef struct ticket
{
	char name[N];				// ����
	char type[N];				// ����
	int time;					// ʱ��
	char day[N];				// ����
	char start[N];				// ��ʼʱ��
	char site[N];				// �ص�
	int price;					// �۸�
	int id;						// ���

	char username[N];			// �û���
	int x;						// ��
	int y;						// ��
	int istake;					// �Ƿ�ȡƱ

	struct ticket* next;		// ָ����
}TICKET;

ADMIN a;									// ����Ա��Ϣ
USER b;										// �û���Ϣ
NODE list;									// ӰƬ��Ϣ
TICKET c;									// ��Ʊ

char fusername[N], fpassword[N];			// �û���/���루�ļ���
char username[N], password[N];				// �û���/���루���룩
int flag = 0;								// �ж��Ƿ��¼�ɹ�

// ����Ա��¼
void menu_Login_admin();					// ����
void fun_Login_admin();						// ����
void admin_login();							// ��¼
int Read_admin_login();						// �ļ���ȡ

// �û���¼
void menu_Login_user();						// ����
void fun_Login_user();						// ����
void user_login(USER* L);					// ��¼
int Read_user(USER* L);						// �û���¼�ļ���ȡ
int Read_user_login(USER* L);				// �ж�
int user_logon(USER* L);					// ע��
void Add1(USER* L, USER e);					// ����

// ��ȡ�ļ�
int Read_FILE(NODE* L);

// �����ļ�
int Save_FILE(NODE* L);

// �˵�
void welcome();								// ���˵�
void fun_welcome();							// ���˵�����
void menu_administrator();					// ����Ա����
void fun_administrator();					// ����Ա����
void menu_user();							// �û�����
void fun_user();							// �û�����

// ����ӰƬ
void Add(NODE* L, NODE e);					// ����
void Add_Printf();							// ����

// ��ѯӰƬ
void Search_Printf(NODE* L);					// ����
int Search_allname(char name[], NODE* L);		// �����ƽ��в���
NODE* Search_name(char name[], NODE* L);		// �����ƽ��в��ҵ�һ��
int Search_type(char type[], NODE* L);			// �����ͽ��в���
NODE* Search_id(int id, NODE* L);				// ����Ž��в���

// ɾ��ӰƬ
void Delete_Printf(NODE* L);				// ����
void Delete(NODE* s);						// ����

// �޸�ӰƬ
void Fix(NODE* L);

// ��ʾӰƬ
void Print(NODE* L);						// ����
void Print_Printf();						// ����Ա����
void Print_Printf2();                       // �û����� 

// ����ӰƬ
void Sort(NODE* L);

int cmp_big_sum(NODE e1, NODE e2);			// Ʊ���Ӵ�С
int cmp_small_sum(NODE e1, NODE e2);		// Ʊ����С���� 

// ��Ʊ
void Buy_ticket();							// ����
int Buy_ticket_Printf();					// ����
void Add2(TICKET* L, TICKET e);				// ����Ԥ����Ϣ
int Save_TICKET(TICKET* L);					// �ļ�������Ʊ��Ϣ
int Read_TICKET(TICKET* L);					// ��ȡ��Ʊ��Ϣ

// ȡƱ
void Collect_ticket();
// ��ӡƱ����Ϣ
void Print_ticket(TICKET* L);
void Print_ticket_Printf();

// ��Ʊ
void Return_ticket();
void Print_ticket1(TICKET* L);						// ��ӡ��Ϣ
TICKET* Find_ticket(TICKET* L, char username[]);	// ����ǰ���ڵ�
void Delete_ticket(TICKET* s);						// ɾ��

// �˳�ϵͳ
void goodbye();

int main()
{
	Read_FILE(&list);
	Read_TICKET(&c);
	Read_user(&b);

	while (1)
	{
		fun_welcome();
	}
	
	return 0;
}

// ���˵�
void welcome()
{
	system("cls");
	printf("****************************************************************\n");
	printf("***********               ӰԺ����ϵͳ               ***********\n");
	printf("***********             1 ----  ����Ա               ***********\n");
	printf("***********             2 ----  �û�                 ***********\n");
	printf("***********             0 ----  �˳�                 ***********\n");
	printf("****************************************************************\n");

	printf("��ϵͳ����ѡ�������ݣ����֣���");
}

// ���˵�����
void fun_welcome()
{
	int choice = 0;
	welcome();
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:// ����Ա
		fun_administrator();
		break;
	case 2:// �û�
		fun_user();
		break;
	case 0:// �˳�
		goodbye();
		break;
	}
}

// ����Ա����
void menu_administrator()
{
	system("cls");
	printf("��ϵͳ����ӭ%s������\n", username);
	printf("****************************************************************\n");
	printf("***********               ��ӭ������                 ***********\n");
	printf("***********             1 ----  ����ӰƬ             ***********\n");
	printf("***********             2 ----  ��ʾӰƬ             ***********\n");
	printf("***********             3 ----  �޸�ӰƬ             ***********\n");
	printf("***********             4 ----  ɾ��ӰƬ             ***********\n");
	printf("***********             5 ----  ����ӰƬ             ***********\n");
	printf("***********             0 ----  �˳�                 ***********\n");
	printf("****************************************************************\n");

	printf("��ϵͳ����ѡ����Ҫʵ�ֵĹ��ܣ����֣���");
}

// ����Ա����
void fun_administrator()
{
	fun_Login_admin();

	if (flag == 1)
	{
		int choice = 0;
		while (1)
		{
			menu_administrator();
			scanf("%d", &choice);
			switch (choice)
			{
			case 1:// ����ӰƬ
				Add_Printf();
				break;
			case 2:// ��ʾӰƬ
				Print(&list);
				break;
			case 3:// �޸�ӰƬ
				Fix(&list);
				break;
			case 4:// ɾ��ӰƬ
				Delete_Printf(&list);
				break;
			case 5:// ����ӰƬ
				Sort(&list);
				break;
			case 0:// �˳�
				return;
			}

			printf("�Ƿ���Ҫ������������Yes��1 / No��0)��");
			scanf("%d", &choice);

			if (choice != 1)
			{
				if (choice != 0)
					printf("������󣡣���\n");
				system("pause");
				break;
			}
		}
	}
}

// �û�����
void menu_user()
{
	system("cls");
	printf("��ϵͳ����ӭ%s������\n", username);
	printf("****************************************************************\n");
	printf("***********              ��ӭ���٣���                ***********\n");
	printf("***********             1 ----  ��Ʊ                 ***********\n");
	printf("***********             2 ----  ȡƱ                 ***********\n");
	printf("***********             3 ----  ��Ʊ                 ***********\n");
//	printf("***********             4 ----  ����ӰƬ             ***********\n");
	printf("***********             0 ----  �˳�                 ***********\n");
	printf("****************************************************************\n");

	printf("��ϵͳ����ѡ����Ҫʵ�ֵĹ��ܣ����֣���");
}

// �û�����
void fun_user()
{
	fun_Login_user();

	if (flag == 1)
	{
		int choice = 0;
		while (1)
		{
			menu_user();
			scanf("%d", &choice);
			switch (choice)
			{
			case 1:// ��Ʊ
				Buy_ticket();
				break;
			case 2:// ȡƱ
				Collect_ticket();
				break;
			case 3:// ��Ʊ
				Return_ticket();
				break;
//			case 4:// ����ӰƬ
//				Search_Printf(&list);
//				break;
			case 0:// �˳�
				return;
			}

			system("cls");

			printf("��ϵͳ���Ƿ���Ҫ������������Yes��1 / No��0)��");
			scanf("%d", &choice);

			if (choice != 1)
			{
				if (choice != 0)
					printf("��ϵͳ��������󣡣���\n");
				system("pause");
				break;
			}
		}
	}
}

// ����Ա��¼����
void menu_Login_admin()
{
	system("cls");
	printf("****************************************************************\n");
	printf("***********               ����Ա��¼                 ***********\n");
	printf("***********             1 ----  ��¼                 ***********\n");
	printf("***********             0 ----  �˳�                 ***********\n");
	printf("****************************************************************\n");

	printf("��ϵͳ����ѡ����Ҫʵ�ֵĹ��ܣ����֣���");
}

// ����Ա��¼����
void fun_Login_admin()
{
	int choice = 0;
	menu_Login_admin();
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:// ��¼
		admin_login();
		break;
	case 0:// �˳�
		flag = 0;
		return;
	}
}

// ����Ա��¼
void admin_login()
{
	int cnt = 0;
	do {
		printf("��ϵͳ���������û�����");
		scanf("%s", username);
		getchar();

		printf("��ϵͳ�����������룺");
		char c;
		int i = 0;
		while ((c = getch()) != '\r')
		{
			password[i] = c;
			i++;
			putchar('*');

		}
		printf("\n");
		password[i] = '\0';

		cnt++;
	} while (Read_admin_login() == 0 && cnt < 3);
}


// ����Ա��¼�ļ���ȡ
int Read_admin_login()
{

FILE*fp;
fp=fopen("admin.txt","r");
fprintf(fp,"%s",fusername);
fprintf(fp,"%s",fpassword);
fclose(fp);	
	fp = fopen("admin.txt", "r+");

	if (fp == NULL)
	{
		return 0;
	}

	while (fscanf(fp, "%s %s", fusername, fpassword) != EOF)
	{
		fscanf(fp, "\n");
		if ((strcmp(fusername, username) == 0) && (strcmp(fpassword, password)) == 0)
		{
			printf("��ϵͳ����½�ɹ�\n");
			getch();
			system("cls");
			flag = 1;
			return 1;
		}
	}
	printf("��ϵͳ���û����������������������\n");
	getch();
	system("pause");

	return 0;
}

// �û���¼����
void menu_Login_user()
{
	system("cls");
	printf("****************************************************************\n");
	printf("***********               �û���¼                   ***********\n");
	printf("***********             1 ----  ע��                 ***********\n");
	printf("***********             2 ----  ��¼                 ***********\n");
	printf("***********             0 ----  �˳�                 ***********\n");
	printf("****************************************************************\n");

	printf("��ѡ����Ҫʵ�ֵĹ��ܣ����֣���");
}

// �û���¼����
void fun_Login_user()
{
	int choice = 0;
	menu_Login_user();
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		user_logon(&b);
	case 2:
		user_login(&b);
		break;
	case 0:
		flag = 0;
		return;
	}
}

// �û���¼
void user_login(USER* L)
{
	int cnt = 0;
	do {
		printf("��ϵͳ���������û�����");
		scanf("%s", username);
		getchar();

		printf("��ϵͳ�����������룺");
		char c;
		int i = 0;
		while ((c = getch()) != '\r')
		{
			password[i] = c;
			i++;
			putchar('*');

		}
		printf("\n");
		password[i] = '\0';

		cnt++;
	} while (Read_user_login(L) == 0 && cnt < 3);
}

int Read_user(USER* L)
{
	FILE* fp = fopen("user.txt", "r");

	if (fp == NULL)
	{
		return 0;
	}

	USER st;
	USER* s = NULL;
	USER* t = L;

	while (fscanf(fp, "%s %s", st.id, st.password) != EOF)
	{
		s = (USER*)malloc(sizeof(USER));
		*s = st;

		// β�巨
		t->next = s;
		t = s;
		t->next = NULL;
	}

	fclose(fp);	// ���ļ���ǵùر�

	return 1;
}

// �û���¼�ļ���ȡ
int Read_user_login(USER* L)
{
	USER* q = L->next;
	while (q != NULL)
	{
		if ((strcmp(q->id, username) == 0) && (strcmp(q->password, password)) == 0)
		{
			printf("��½�ɹ�\n");
			getch();
			system("cls");
			flag = 1;
			return 1;
		}
		q = q->next;
	}
	printf("��ϵͳ���û����������������������\n");
	getch();
	system("pause");

	return 0;
}

// �û�ע��
int user_logon(USER* L)
{
	FILE* pf = fopen("user.txt", "w");

	if (pf == NULL)
	{
		return 0;
	}

	USER st;

	printf("�������û�����");
	scanf("%s", st.id);
	printf("���������룺");
	scanf("%s", st.password);

	Add1(&b, st);

	USER* p = L->next;

	while (p != NULL)
	{
		fprintf(pf, "%s %s\n", p->id, p->password);
		p = p->next;
	}

	fclose(pf);

	system("cls");
	printf("ע��ɹ���\n");
}

// ����
void Add1(USER* L, USER e)
{
	// ͷ�巨
	USER* p = L;
	USER* s = (USER*)malloc(sizeof(USER));
	*s = e;

	s->next = p->next;
	p->next = s;
}

// ��ȡ�ļ�
int Read_FILE(NODE* L)
{
	FILE* pfRead = fopen("ticket.txt", "r");
	NODE st;
	NODE* s = NULL;
	NODE* t = L;

	if (pfRead == NULL)
	{
		return 0;
	}

	while (fscanf(pfRead, "%s %s %d %s %s %s %d %d %d", st.name, st.type, &st.time, st.day, st.start, st.site, &st.price, &st.num, &st.id) != EOF)
	{
		// ��ȡ��λ��
		for (int i = 1; i <= 10; i++)
		{
			for (int j = 1; j <= 10; j++)
			{
				fscanf(pfRead, "%d ", &st.seat[i][j]);
			}
			fscanf(pfRead, "\n");
		}

		s = (NODE*)malloc(sizeof(NODE));
		*s = st;

		// β�巨
		t->next = s;
		t = s;
		t->next = NULL;
	}

	fclose(pfRead);	// ���ļ���ǵùر�

	return 1;
}

// �����ļ�
int Save_FILE(NODE* L)
{
	FILE* pfWrite = fopen("ticket.txt", "w");
	if (pfWrite == NULL)
	{
		return 0;
	}

	NODE* p = L->next;

	while (p != NULL)
	{
		fprintf(pfWrite, "%s %s %d %s %s %s %d %d %d\n", p->name, p->type, p->time, p->day, p->start, p->site, p->price, p->num, p->id);
		// ������λ��
		for (int i = 1; i <= 10; i++)
		{
			for (int j = 1; j <= 10; j++)
			{
				fprintf(pfWrite, "%d ", p->seat[i][j]);
			}
			fprintf(pfWrite, "\n");
		}

		p = p->next;
	}

	// ���ļ���ǵùر�
	fclose(pfWrite);

	return 1;
}

// ����ӰƬ
void Add_Printf()
{
	system("cls");

	NODE st;
	printf("��ϵͳ������������ӰƬ�������Ϣ��\n");

	printf("���ƣ�");
	scanf("%s", st.name);
	printf("���ͣ�");
	scanf("%s", st.type);
	printf("ʱ����");
	scanf("%d", &st.time);
	printf("���ڣ�");
	scanf("%s", st.day);
	printf("��ʼʱ�䣺");
	scanf("%s", st.start);
	printf("�ص㣺");
	scanf("%s", st.site);
	printf("�۸�");
	scanf("%d", &st.price);
	printf("������");
	scanf("%d", &st.num);
	printf("��ţ�");
	scanf("%d", &st.id);

	
	
	
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			st.seat[i][j] = 0;
		}
	}

	Add(&list, st);
}

void Add(NODE* L, NODE e)
{
	// ͷ�巨
	NODE* p = L;
	NODE* s = (NODE*)malloc(sizeof(NODE));
	*s = e;

	s->next = p->next;
	p->next = s;

	Save_FILE(L);
}

// ɾ��ӰƬ
void Delete_Printf(NODE* L)
{
	system("cls");

	int id;
	node* p;

	printf("��ϵͳ��������Ҫɾ����ӰƬ�ı�ţ�");
	scanf("%d", &id);
	NODE* st = Search_id(id, L); 
	p = st;

	if (st == NULL)
	{
		printf("�Ҳ�����ӰƬ��\n");
		return;
	}

	st = st->next;
	printf("_________________________________________________________________________________________________________\n");
	printf("|\t����\t\t|����\t|ʱ��\t|����\t|��ʼʱ��\t|�ص�\t|�۸�\t|����\t|���\t |\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t|%s\t|%d\t|%d\t|%d\t |\n", st->name, st->type, st->time, st->day, st->start, st->site, st->price, st->num, st->id);
	printf("_________________________________________________________________________________________________________\n");

	Delete(p);

	// ������Ϣ
	Save_FILE(L);
}

void Delete(NODE* s)
{
	NODE* t = s->next;

	s->next = t->next;
	t->next = NULL;

	free(t);
}

// �޸�ӰƬ
void Fix(NODE* L)
{
	system("cls");

	int id;
	printf("��ϵͳ��������Ҫ�޸ĵ�ӰƬ�ı�ţ�");
	scanf("%d", &id);

	NODE* st = Search_id(id, L);

	if (st == NULL)
	{
		printf("�޷��ҵ���ӰƬ��\n");
		return;
	}

	st = st->next;

	int choice = 0;
	while (1)
	{
		system("cls");

		// ���һ����Ҫ�޸ĵ�ӰƬ��Ϣ
		printf("_________________________________________________________________________________________________________\n");
		printf("|\t����\t\t|����\t|ʱ��\t|����\t|��ʼʱ��\t|�ص�\t|�۸�\t|����\t|���\t|\n");
		printf("_________________________________________________________________________________________________________\n");
		printf("_________________________________________________________________________________________________________\n");
		printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", st->name, st->type, st->time, st->day, st->start, st->site, st->price, st->num, st->id);
		printf("_________________________________________________________________________________________________________\n");
		printf("_________________________________________________________________________________________________________\n");
		
		printf("|\t�޸�����     ---- 1\t|\n");
		printf("|\t�޸�����     ---- 2\t|\n");
		printf("|\t�޸�ʱ��     ---- 3\t|\n");
		printf("|\t�޸�����     ---- 4\t|\n");
		printf("|\t�޸���ʼʱ�� ---- 5\t|\n");
		printf("|\t�޸ĵص�     ---- 6\t|\n");
		printf("|\t�޸ļ۸�     ---- 7\t|\n");
		printf("|\t�޸�����     ---- 8\t|\n");
		printf("|\t�޸ı��     ---- 9\t|\n");
		printf("|\t�˳�         ---- 0\t|\n");
		printf("________________________________\n");

		printf("��ϵͳ��������Ҫ�޸ĵ���Ϣ��");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("��ϵͳ�����������ƣ�");
			scanf("%s", st->name);
			break;
		case 2:
			printf("��ϵͳ�����������ͣ�");
			scanf("%s", st->type);
			break;
		case 3:
			printf("��ϵͳ��������ʱ����");
			scanf("%d", &st->time);
			break;
		case 4:
			printf("��ϵͳ�����������ڣ�");
			scanf("%s", st->day);
			break;
		case 5:
			printf("��ϵͳ����������ʼʱ�䣺");
			scanf("%s", st->start);
			break;
		case 6:
			printf("��ϵͳ��������ص㣺");
			scanf("%s", st->site);
			break;
		case 7:
			printf("��ϵͳ��������۸�");
			scanf("%d", &st->price);
			break;
		case 8:
			printf("��ϵͳ��������������");
			scanf("%d", &st->num);
			break;
		case 9:
			printf("��ϵͳ���������ţ�");
			scanf("%d", &st->id);
			break;
		case 0:
			break;
		}
		printf("�Ƿ�����޸ĸ�ӰƬ��Ϣ����Yes��1 / No��0����");
		scanf("%d", &choice);
		if (choice == 0)
		{
			break;
		}
	}

	// �޸���ɺ��ӰƬ����Ϣ
	printf("_________________________________________________________________________________________________________\n");
	printf("|\t����\t\t|����\t|ʱ��\t|����\t\t|��ʼʱ��\t|�ص�\t|�۸�\t|����\t|���\t|\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", st->name, st->type, st->time, st->day, st->start, st->site, st->price, st->num, st->id);
	printf("_________________________________________________________________________________________________________\n");

	// ������Ϣ
	Save_FILE(L);
}

// ��ѯӰƬ
void Search_Printf(NODE* L)
{
	system("cls");

	int choice = 0;
	printf("�������Ʋ�ѯ ---- 1\n");
	printf("�������Ͳ�ѯ ---- 2\n");
	printf("���ձ�Ų�ѯ ---- 3\n");
	printf("��ϵͳ���������ѯ��ʽ��");
	scanf("%d", &choice);

	node* st;

	if (choice == 1)
	{
		char name[N];
		int cnt = 0;

		printf("��ϵͳ��������Ҫ��ѯ��ӰƬ���ƣ�");
		scanf("%s", name);

		cnt = Search_allname(name, L);

		if (cnt == 0)
		{
			printf("�޷��ҵ���ӰƬ��\n");
		}
	}
	else if (choice == 2)
	{
		char type[N];
		int cnt = 0;

		printf("��ϵͳ��������Ҫ��ѯ��ӰƬ���ͣ�");
		scanf("%s", type);

		cnt = Search_type(type, L);

		if (cnt == 0)
		{
			printf("�޷��ҵ������͵�ӰƬ��\n");
		}
	}
	else if (choice == 3)
	{
		int id;

		printf("��ϵͳ��������Ҫ��ѯ��ӰƬ��ţ�");
		scanf("%d", &id);

		st = Search_id(id, L);

		if (st == NULL)
		{
			printf("���޴�Ƭ��\n");
		}
		else
		{
			st = st->next;

			printf("_________________________________________________________________________________________________________\n");
			printf("|\t����\t\t|����\t|ʱ��\t|����\t\t|��ʼʱ��\t|�ص�\t|�۸�\t|����\t|���\t |\n");
			printf("_________________________________________________________________________________________________________\n");
			printf("_________________________________________________________________________________________________________\n");
			printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", st->name, st->type, st->time, st->day, st->start, st->site, st->price, st->num, st->id);
			printf("_________________________________________________________________________________________________________\n");
		}
	}
}

// �����ƽ��в���
int Search_allname(char name[], NODE* L)
{
	int cnt = 0;

	node* p = L;

	while (p->next != NULL)
	{
		p = p->next;

		if (strcmp(name, p->name) == 0)
		{
			cnt++;

			if (cnt == 1)
			{
				printf("_________________________________________________________________________________________________________\n");
				printf("|\t����\t\t|����\t|ʱ��\t|����\t\t|��ʼʱ��\t|�ص�\t|�۸�\t|����\t|���\t |\n");
				printf("_________________________________________________________________________________________________________\n");
			}
			printf("_________________________________________________________________________________________________________\n");
			printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", p->name, p->type, p->time, p->day, p->start, p->site, p->price, p->num, p->id);
			printf("_________________________________________________________________________________________________________\n");
		}

	}
	return cnt;
}

// �����ƽ��в��ҵ�һ��
NODE* Search_name(char name[], NODE* L)
{
	NODE* p = L;

	while (p->next != NULL)
	{
		if (strcmp(name, p->next->name) == 0)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

// ����Ž��в���
NODE* Search_id(int id, NODE* L)
{
	NODE* p = L;

	while (p->next != NULL)
	{
		if (p->next->id == id)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

// �����ͽ��в���
int Search_type(char type[], NODE* L)
{
	int cnt = 0;

	node* p = L;

	while (p->next != NULL)
	{
		p = p->next;

		if (strcmp(type, p->type) == 0)
		{
			cnt++;

			if (cnt == 1)
			{
				printf("_________________________________________________________________________________________________________\n");
				printf("|\t����\t\t|����\t|ʱ��\t|����\t\t|��ʼʱ��\t|�ص�\t|�۸�\t|����\t|���\t |\n");
				printf("_________________________________________________________________________________________________________\n");
			}
			printf("_________________________________________________________________________________________________________\n");
			printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", p->name, p->type, p->time, p->day, p->start, p->site, p->price, p->num, p->id);
			printf("_________________________________________________________________________________________________________\n");
		}
		
	}

	return cnt;
}

// ����Ա��ʾӰƬ
void Print(NODE* L)
{
	system("cls");

	node* p = L->next;
	Print_Printf();
	p->sum=(N-p->num)*p->price;                   //��ѭ��ǰ�ȼ���һ��Ʊ�� 
	if (p != NULL)
	{
		while (p != NULL)
		{
			p->sum=(N-p->num)*p->price;           //Ʊ��=����*����Ʊ��-��Ʊ�� 
			printf("_________________________________________________________________________________________________________\n");
			printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t|%d\t |\n", p->name, p->type, p->time, p->day, p->start, p->site, p->price, p->num, p->id,p->sum);
			printf("_________________________________________________________________________________________________________\n");
			p = p->next;
		}
	}
}

// �û���ʾӰƬ
void Print2(NODE* L)
{
	system("cls");

	node* p = L->next;
	Print_Printf2();

	if (p != NULL)
	{
		while (p != NULL)
		{

			printf("__________________________________________________________________________________________________\n");
			printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", p->name, p->type, p->time, p->day, p->start, p->site, p->price, p->num, p->id);
			printf("__________________________________________________________________________________________________\n");
			p = p->next;
		}
	}
}

void Print_Printf()
{
	printf("_________________________________________________________________________________________________________\n");
	printf("|\t����\t\t|����\t|ʱ��\t|����\t|��ʼʱ��\t|�ص�\t|�۸�\t|����\t|���\t|Ʊ��\t |\n");
	printf("_________________________________________________________________________________________________________\n");
}

void Print_Printf2()
{
	printf("__________________________________________________________________________________________________\n");
	printf("|\t����\t\t|����\t|ʱ��\t|����\t|��ʼʱ��\t|�ص�\t|�۸�\t|����\t|���\t |\n");
	printf("__________________________________________________________________________________________________\n");
}

// ����ӰƬ
void Sort(NODE* L)
{
	system("cls");

	int choice = 0;
	printf("����Ʊ���Ӵ�С���� ---- 1\n");
	printf("����Ʊ����С�������� ---- 2\n\n");
	printf("��ϵͳ����ѡ������ʽ��");
	scanf("%d", &choice);

	int flag = 0;
	for (node* p = L->next; p != NULL; p = p->next)
	{
		for (node* q = p; q != NULL; q = q->next)
		{
			switch (choice)
			{
	
				case 1:
				if (!cmp_big_sum(*p, *q))
				{
					flag = 1;
				}
				break;
				case 2:
				if (!cmp_small_sum(*p, *q))
				{
					flag = 1;
				}
				break;
				
			}
			if (flag == 1)
			{
				// ����������
				node t = *p;
				*p = *q;
				*q = t;
				// ����ָ����
				t.next = p->next;
				p->next = q->next;
				q->next = t.next;
				flag = 0;
			}
		}
	}
	printf("��ϵͳ������ɹ���\n");
}

// Ʊ���Ӵ�С
int cmp_big_sum(NODE e1, NODE e2)
{
	return e1.sum > e2.sum;
}

// Ʊ����С���� 
int cmp_small_sum(NODE e1, NODE e2)
{
	return e1.sum < e2.sum;
}


// �ļ�������Ʊ��Ϣ
int Save_TICKET(TICKET* L)
{
	FILE* pfWrite = fopen("ticket1.txt", "w");
	if (pfWrite == NULL)
	{
		return 0;
	}

	TICKET* p = L->next;

	while (p != NULL)
	{
		fprintf(pfWrite, "%s %s %d %s %s %s %d %d %s %d %d %d\n", p->name, p->type, p->time, p->day, p->start, p->site, p->price, p->id, p->username, p->x, p->y, p->istake);
		p = p->next;
	}

	// ���ļ���ǵùر�
	fclose(pfWrite);

	return 1;
}

// ��ȡ��Ʊ��Ϣ
int Read_TICKET(TICKET* L)
{
	FILE* pfRead = fopen("ticket1.txt", "r");
	TICKET st;
	TICKET* s = NULL;
	TICKET* t = L;

	if (pfRead == NULL)
	{
		return 0;
	}

	while (fscanf(pfRead, "%s %s %d %s %s %s %d %d %s %d %d %d\n", st.name, st.type, &st.time, st.day, st.start, st.site, &st.price, &st.id, st.username, &st.x, &st.y, &st.istake) != EOF)
	{
		s = (TICKET*)malloc(sizeof(TICKET));
		*s = st;

		// β�巨
		t->next = s;
		t = s;
		t->next = NULL;
	}

	fclose(pfRead);	// ���ļ���ǵùر�

	return 1;
}

// ��Ʊ
void Buy_ticket()
{
	do {
		system("pause");
		Print2(&list);
	} while (Buy_ticket_Printf() == 0);
}

int Buy_ticket_Printf()
{
	TICKET s;   // ��¼Ʊ����Ϣ

	int id;
	printf("��ϵͳ����������Ҫ�����ӰƬ�ı�ţ�");
	scanf("%d", &id);

	system("cls");

	node* st = Search_id(id, &list);

	if (st == NULL)
	{
		printf("��ϵͳ���޷��ҵ���ӰƬ��\n");

		int choice;
		printf("��ϵͳ����ѡ���Ƿ�Ҫ������Ʊ����Yes��1 / No��0)��");
		scanf("%d", &choice);
		
		if (choice == 1)
			return 0;
		else if (choice == 0)
			return 1;
		else
		{
			printf("�������\n");
			system("pause");
			return 1;
		}
	}

	st = st->next;
	printf("��ϵͳ����ӰƬ����Ϣ���£�\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("|\t����\t\t|����\t|ʱ��\t|����\t|��ʼʱ��\t|�ص�\t|�۸�\t|����\t|���\t |\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", st->name, st->type, st->time, st->day, st->start, st->site, st->price, st->num, st->id);
	printf("_________________________________________________________________________________________________________\n");

	printf("��ϵͳ����λʾ��ͼ���£�(����ʾ��Ԥ��������ʾδԤ����\n");

	printf("    ");
	for (int i = 1; i <= 10; i++)
	{
		printf("%3d", i);
	}
	printf("\n");

	for (int i = 1; i <= 10; i++)
	{
		printf("%4d", i);
		for (int j = 1; j <= 10; j++)
		{
			if (st->seat[i][j] == 0)
				printf(" ��");
			else
				printf(" ��");
		}
		printf("\n");
	}

	int a;
	printf("��ϵͳ����ѡ����Ҫ�����������");
	scanf("%d", &a);

	for (int i = 0; i < a; i++)
	{
		printf("��ϵͳ����ѡ����Ҫ�������λ�ţ�\n");
		int x, y;
		printf("�У�1-10����");
		scanf("%d", &x);
		printf("�У�1-10����");
		scanf("%d", &y);

		if (st->seat[x][y] == 0)
		{
			st->seat[x][y] = 1;
			st->num = st->num - 1;
		}
		else
		{
			printf("��ϵͳ��Ԥ��ʧ�ܣ�����λ�ѱ�Ԥ��\n");

			int choice;
			printf("��ϵͳ����ѡ���Ƿ�Ҫ������Ʊ����Yes��1 / No��0)��");
			scanf("%d", &choice);

			if (choice == 1)
				return 0;
			else if (choice == 0)
				return 1;
			else
			{
				printf("�������\n");
				system("pause");
				return 1;
			}
		}

		// ��¼������Ϣ
		strcpy(s.name, st->name);
		strcpy(s.type, st->type);
		s.time = st->time;
		strcpy(s.day, st->day);
		strcpy(s.start, st->start);
		strcpy(s.site, st->site);
		s.price = st->price;
		s.id = st->id;

		strcpy(s.username, username);
		s.x = x;
		s.y = y;
		s.istake = 0;

		Add2(&c, s);

		printf("��ϵͳ��Ԥ���ɹ�\n");
	}

	system("pause");
	system("cls");

	printf("��ϵͳ�����Ķ�����Ϣ���£�\n");
	printf("_________________________________________________________________________________________________\n");
	printf("|\t����\t\t|����\t|ʱ��\t|����\t|��ʼʱ��\t|�ص�\t|�۸�\t|����\t|\n");
	printf("_________________________________________________________________________________________________\n");
	printf("_________________________________________________________________________________________________\n");
	printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|\n", st->name, st->type, st->time, st->day, st->start, st->site, st->price * a, a);
	printf("_________________________________________________________________________________________________\n");

	system("pause");

	Save_FILE(&list);
	return 1;
}

// ����Ԥ����Ϣ
void Add2(TICKET* L, TICKET e)
{
	// ͷ�巨
	TICKET* p = L;
	TICKET* s = (TICKET*)malloc(sizeof(TICKET));
	*s = e;

	s->next = p->next;
	p->next = s;

	Save_TICKET(L);
}

// ȡƱ
void Collect_ticket()
{
	system("cls");
	
	Print_ticket(&c);

	Save_TICKET(&c);
}

void Print_ticket(TICKET* L)
{
	TICKET* p = L->next;
	int cnt = 0, choice = 0;
	
	if (p != NULL)
	{
		while (p != NULL && strcmp(p->username, username) == 0 && p->istake==0)
		{
			printf("��ϵͳ�����Ķ������£�\n");
			Print_ticket_Printf();
			printf("______________________________________________________________________________________________________________________\n");
			printf("|%-15s\t|%s\t|%d\t|%s\t\t|%s\t\t|%s\t|%d\t|%d\t |%-10s|%d\t|%-5d|\n", p->name, p->type, p->time, p->day, p->start, p->site, p->price, p->id, p->username, p->x, p->y);
			printf("______________________________________________________________________________________________________________________\n");

			printf("��ϵͳ���Ƿ�ȡƱ����Yes��1 / No��0)��");
			scanf("%d", &choice);

			if (choice != 1)
			{
				if (choice != 0)
					printf("��ϵͳ��������󣡣���\n");
			}
			else
			{
				p->istake = 1;
				printf("��ϵͳ��ȡƱ�ɹ�������\n");
			}
			system("pause");

			p = p->next;

			cnt++;
		}
	}

	if (cnt == 0)
		printf("��ϵͳ����Ǹ������ǰ��Ʊ��ȡ��\n");
}

void Print_ticket_Printf()
{
	system("cls");
	printf("______________________________________________________________________________________________________________________\n");
	printf("|\t����\t\t|����\t|ʱ��\t|����\t\t|��ʼʱ��\t|�ص�\t|�۸�\t|���\t |��Ʊ��    |��\t|��   |\n");
	printf("______________________________________________________________________________________________________________________\n");
}

// ��Ʊ
void Return_ticket()
{
	system("cls");

	printf("��ϵͳ�����Ķ������£�\n");
	system("pause");
	Print_ticket1(&c);

	Save_TICKET(&c);
}

// ��ӡ��Ϣ
void Print_ticket1(TICKET* L)
{
	TICKET* s = L;
	TICKET* p = NULL, * q = NULL;
	int cnt = 0, choice = 0;

	while (1)
	{
		q = Find_ticket(s, username);
		if (q == NULL)
			break;

		p = q;
		Print_ticket_Printf();
		printf("______________________________________________________________________________________________________________________\n");
		printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t |%-10s|%d\t|%-5d|\n", q->next->name, q->next->type, q->next->time, q->next->day, q->next->start, q->next->site, q->next->price, q->next->id, q->next->username, q->next->x, q->next->y);
		printf("______________________________________________________________________________________________________________________\n");

		printf("��ϵͳ���Ƿ���Ʊ����Yes��1 / No��0)��");
		scanf("%d", &choice);

		if (choice != 1)
		{
			if (choice != 0)
				printf("��ϵͳ��������󣡣���\n");
			q = q->next;
		}
		else if(choice == 1)
		{
			NODE* r = Search_id(q->next->id, &list);
			r->next->num = r->next->num + 1;
			r->next->seat[q->next->x][q->next->y] = 0;
			printf("%d,%d\n", r->next->num, r->next->seat[p->next->x][p->next->y]);


			Save_FILE(&list);
			Delete_ticket(p);
		}
		system("pause");
		s = q;
		cnt++;
	}

	if (cnt == 0)
		printf("��ϵͳ����Ǹ������ǰ��Ʊ���ˡ�\n");
}

// ����ǰ���ڵ�
TICKET* Find_ticket(TICKET* L, char username[])
{
	TICKET* p = L;

	while (p->next != NULL)
	{
		if (strcmp(username, p->next->username) == 0)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

// ɾ��
void Delete_ticket(TICKET* s)
{
	TICKET* t = s->next;

	s->next = t->next;
	t->next = NULL;

	free(t);
}

// �˳�ϵͳ
void goodbye()
{
	system("cls");
	printf("��ӭ�´�ʹ��ӰԺ��Ʊ����ϵͳ��");
	exit(0);
}
