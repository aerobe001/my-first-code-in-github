#include<stdio.h>
#include<windows.h>
#include<stdlib.h>  
#include<string.h>
#include<math.h>
#include<conio.h>
#define N 100

typedef struct administrator
{
	char id[N];								// 用户名
	char password[N];						// 密码

	struct administrator* next;				// 指针域
}ADMIN;

typedef struct user
{
	char id[N];								// 用户名
	char password[N];						// 密码

	struct user* next;						// 指针域
}USER;

typedef struct node
{
	char name[N];				// 名称
	char type[N];				// 类型
	int time;					// 时长
	char day[N];				// 日期
	char start[N];				// 起始时间
	char site[N];				// 地点
	int price;					// 价格
	int num;					// 数量
	int id;						// 编号
	int sum;                    // 票房 
	int seat[N][N];				// 座位

	struct node* next;			// 指针域
}NODE;

typedef struct ticket
{
	char name[N];				// 名称
	char type[N];				// 类型
	int time;					// 时长
	char day[N];				// 日期
	char start[N];				// 起始时间
	char site[N];				// 地点
	int price;					// 价格
	int id;						// 编号

	char username[N];			// 用户名
	int x;						// 行
	int y;						// 列
	int istake;					// 是否取票

	struct ticket* next;		// 指针域
}TICKET;

ADMIN a;									// 管理员信息
USER b;										// 用户信息
NODE list;									// 影片信息
TICKET c;									// 购票

char fusername[N], fpassword[N];			// 用户名/密码（文件）
char username[N], password[N];				// 用户名/密码（输入）
int flag = 0;								// 判断是否登录成功

// 管理员登录
void menu_Login_admin();					// 界面
void fun_Login_admin();						// 功能
void admin_login();							// 登录
int Read_admin_login();						// 文件读取

// 用户登录
void menu_Login_user();						// 界面
void fun_Login_user();						// 功能
void user_login(USER* L);					// 登录
int Read_user(USER* L);						// 用户登录文件读取
int Read_user_login(USER* L);				// 判断
int user_logon(USER* L);					// 注册
void Add1(USER* L, USER e);					// 插入

// 读取文件
int Read_FILE(NODE* L);

// 保存文件
int Save_FILE(NODE* L);

// 菜单
void welcome();								// 主菜单
void fun_welcome();							// 主菜单功能
void menu_administrator();					// 管理员界面
void fun_administrator();					// 管理员功能
void menu_user();							// 用户界面
void fun_user();							// 用户功能

// 增加影片
void Add(NODE* L, NODE e);					// 功能
void Add_Printf();							// 界面

// 查询影片
void Search_Printf(NODE* L);					// 界面
int Search_allname(char name[], NODE* L);		// 按名称进行查找
NODE* Search_name(char name[], NODE* L);		// 按名称进行查找第一个
int Search_type(char type[], NODE* L);			// 按类型进行查找
NODE* Search_id(int id, NODE* L);				// 按编号进行查找

// 删除影片
void Delete_Printf(NODE* L);				// 界面
void Delete(NODE* s);						// 功能

// 修改影片
void Fix(NODE* L);

// 显示影片
void Print(NODE* L);						// 功能
void Print_Printf();						// 管理员界面
void Print_Printf2();                       // 用户界面 

// 排序影片
void Sort(NODE* L);

int cmp_big_sum(NODE e1, NODE e2);			// 票房从大到小
int cmp_small_sum(NODE e1, NODE e2);		// 票房从小到大 

// 购票
void Buy_ticket();							// 功能
int Buy_ticket_Printf();					// 界面
void Add2(TICKET* L, TICKET e);				// 保存预定信息
int Save_TICKET(TICKET* L);					// 文件保存售票信息
int Read_TICKET(TICKET* L);					// 读取售票信息

// 取票
void Collect_ticket();
// 打印票务信息
void Print_ticket(TICKET* L);
void Print_ticket_Printf();

// 退票
void Return_ticket();
void Print_ticket1(TICKET* L);						// 打印信息
TICKET* Find_ticket(TICKET* L, char username[]);	// 查找前驱节点
void Delete_ticket(TICKET* s);						// 删除

// 退出系统
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

// 主菜单
void welcome()
{
	system("cls");
	printf("****************************************************************\n");
	printf("***********               影院管理系统               ***********\n");
	printf("***********             1 ----  管理员               ***********\n");
	printf("***********             2 ----  用户                 ***********\n");
	printf("***********             0 ----  退出                 ***********\n");
	printf("****************************************************************\n");

	printf("【系统】请选择你的身份（数字）：");
}

// 主菜单功能
void fun_welcome()
{
	int choice = 0;
	welcome();
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:// 管理员
		fun_administrator();
		break;
	case 2:// 用户
		fun_user();
		break;
	case 0:// 退出
		goodbye();
		break;
	}
}

// 管理员界面
void menu_administrator()
{
	system("cls");
	printf("【系统】欢迎%s！！！\n", username);
	printf("****************************************************************\n");
	printf("***********               欢迎！！！                 ***********\n");
	printf("***********             1 ----  增加影片             ***********\n");
	printf("***********             2 ----  显示影片             ***********\n");
	printf("***********             3 ----  修改影片             ***********\n");
	printf("***********             4 ----  删除影片             ***********\n");
	printf("***********             5 ----  排序影片             ***********\n");
	printf("***********             0 ----  退出                 ***********\n");
	printf("****************************************************************\n");

	printf("【系统】请选择你要实现的功能（数字）：");
}

// 管理员功能
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
			case 1:// 增加影片
				Add_Printf();
				break;
			case 2:// 显示影片
				Print(&list);
				break;
			case 3:// 修改影片
				Fix(&list);
				break;
			case 4:// 删除影片
				Delete_Printf(&list);
				break;
			case 5:// 排序影片
				Sort(&list);
				break;
			case 0:// 退出
				return;
			}

			printf("是否需要继续操作？（Yes：1 / No：0)：");
			scanf("%d", &choice);

			if (choice != 1)
			{
				if (choice != 0)
					printf("输入错误！！！\n");
				system("pause");
				break;
			}
		}
	}
}

// 用户界面
void menu_user()
{
	system("cls");
	printf("【系统】欢迎%s！！！\n", username);
	printf("****************************************************************\n");
	printf("***********              欢迎光临！！                ***********\n");
	printf("***********             1 ----  购票                 ***********\n");
	printf("***********             2 ----  取票                 ***********\n");
	printf("***********             3 ----  退票                 ***********\n");
//	printf("***********             4 ----  查找影片             ***********\n");
	printf("***********             0 ----  退出                 ***********\n");
	printf("****************************************************************\n");

	printf("【系统】请选择您要实现的功能（数字）：");
}

// 用户功能
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
			case 1:// 购票
				Buy_ticket();
				break;
			case 2:// 取票
				Collect_ticket();
				break;
			case 3:// 退票
				Return_ticket();
				break;
//			case 4:// 查找影片
//				Search_Printf(&list);
//				break;
			case 0:// 退出
				return;
			}

			system("cls");

			printf("【系统】是否需要继续操作？（Yes：1 / No：0)：");
			scanf("%d", &choice);

			if (choice != 1)
			{
				if (choice != 0)
					printf("【系统】输入错误！！！\n");
				system("pause");
				break;
			}
		}
	}
}

// 管理员登录界面
void menu_Login_admin()
{
	system("cls");
	printf("****************************************************************\n");
	printf("***********               管理员登录                 ***********\n");
	printf("***********             1 ----  登录                 ***********\n");
	printf("***********             0 ----  退出                 ***********\n");
	printf("****************************************************************\n");

	printf("【系统】请选择你要实现的功能（数字）：");
}

// 管理员登录功能
void fun_Login_admin()
{
	int choice = 0;
	menu_Login_admin();
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:// 登录
		admin_login();
		break;
	case 0:// 退出
		flag = 0;
		return;
	}
}

// 管理员登录
void admin_login()
{
	int cnt = 0;
	do {
		printf("【系统】请输入用户名：");
		scanf("%s", username);
		getchar();

		printf("【系统】请输入密码：");
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


// 管理员登录文件读取
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
			printf("【系统】登陆成功\n");
			getch();
			system("cls");
			flag = 1;
			return 1;
		}
	}
	printf("【系统】用户名或密码错误，请重新输入\n");
	getch();
	system("pause");

	return 0;
}

// 用户登录界面
void menu_Login_user()
{
	system("cls");
	printf("****************************************************************\n");
	printf("***********               用户登录                   ***********\n");
	printf("***********             1 ----  注册                 ***********\n");
	printf("***********             2 ----  登录                 ***********\n");
	printf("***********             0 ----  退出                 ***********\n");
	printf("****************************************************************\n");

	printf("请选择你要实现的功能（数字）：");
}

// 用户登录功能
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

// 用户登录
void user_login(USER* L)
{
	int cnt = 0;
	do {
		printf("【系统】请输入用户名：");
		scanf("%s", username);
		getchar();

		printf("【系统】请输入密码：");
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

		// 尾插法
		t->next = s;
		t = s;
		t->next = NULL;
	}

	fclose(fp);	// 打开文件后记得关闭

	return 1;
}

// 用户登录文件读取
int Read_user_login(USER* L)
{
	USER* q = L->next;
	while (q != NULL)
	{
		if ((strcmp(q->id, username) == 0) && (strcmp(q->password, password)) == 0)
		{
			printf("登陆成功\n");
			getch();
			system("cls");
			flag = 1;
			return 1;
		}
		q = q->next;
	}
	printf("【系统】用户名或密码错误，请重新输入\n");
	getch();
	system("pause");

	return 0;
}

// 用户注册
int user_logon(USER* L)
{
	FILE* pf = fopen("user.txt", "w");

	if (pf == NULL)
	{
		return 0;
	}

	USER st;

	printf("请输入用户名：");
	scanf("%s", st.id);
	printf("请输入密码：");
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
	printf("注册成功！\n");
}

// 插入
void Add1(USER* L, USER e)
{
	// 头插法
	USER* p = L;
	USER* s = (USER*)malloc(sizeof(USER));
	*s = e;

	s->next = p->next;
	p->next = s;
}

// 读取文件
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
		// 读取座位表
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

		// 尾插法
		t->next = s;
		t = s;
		t->next = NULL;
	}

	fclose(pfRead);	// 打开文件后记得关闭

	return 1;
}

// 保存文件
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
		// 保存座位表
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

	// 打开文件后记得关闭
	fclose(pfWrite);

	return 1;
}

// 增加影片
void Add_Printf()
{
	system("cls");

	NODE st;
	printf("【系统】请输入新增影片的相关信息：\n");

	printf("名称：");
	scanf("%s", st.name);
	printf("类型：");
	scanf("%s", st.type);
	printf("时长：");
	scanf("%d", &st.time);
	printf("日期：");
	scanf("%s", st.day);
	printf("起始时间：");
	scanf("%s", st.start);
	printf("地点：");
	scanf("%s", st.site);
	printf("价格：");
	scanf("%d", &st.price);
	printf("数量：");
	scanf("%d", &st.num);
	printf("编号：");
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
	// 头插法
	NODE* p = L;
	NODE* s = (NODE*)malloc(sizeof(NODE));
	*s = e;

	s->next = p->next;
	p->next = s;

	Save_FILE(L);
}

// 删除影片
void Delete_Printf(NODE* L)
{
	system("cls");

	int id;
	node* p;

	printf("【系统】请输入要删除的影片的编号：");
	scanf("%d", &id);
	NODE* st = Search_id(id, L); 
	p = st;

	if (st == NULL)
	{
		printf("找不到该影片！\n");
		return;
	}

	st = st->next;
	printf("_________________________________________________________________________________________________________\n");
	printf("|\t名称\t\t|类型\t|时长\t|日期\t|起始时间\t|地点\t|价格\t|数量\t|编号\t |\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t|%s\t|%d\t|%d\t|%d\t |\n", st->name, st->type, st->time, st->day, st->start, st->site, st->price, st->num, st->id);
	printf("_________________________________________________________________________________________________________\n");

	Delete(p);

	// 保存信息
	Save_FILE(L);
}

void Delete(NODE* s)
{
	NODE* t = s->next;

	s->next = t->next;
	t->next = NULL;

	free(t);
}

// 修改影片
void Fix(NODE* L)
{
	system("cls");

	int id;
	printf("【系统】请输入要修改的影片的编号：");
	scanf("%d", &id);

	NODE* st = Search_id(id, L);

	if (st == NULL)
	{
		printf("无法找到该影片！\n");
		return;
	}

	st = st->next;

	int choice = 0;
	while (1)
	{
		system("cls");

		// 输出一次所要修改的影片信息
		printf("_________________________________________________________________________________________________________\n");
		printf("|\t名称\t\t|类型\t|时长\t|日期\t|起始时间\t|地点\t|价格\t|数量\t|编号\t|\n");
		printf("_________________________________________________________________________________________________________\n");
		printf("_________________________________________________________________________________________________________\n");
		printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", st->name, st->type, st->time, st->day, st->start, st->site, st->price, st->num, st->id);
		printf("_________________________________________________________________________________________________________\n");
		printf("_________________________________________________________________________________________________________\n");
		
		printf("|\t修改名称     ---- 1\t|\n");
		printf("|\t修改类型     ---- 2\t|\n");
		printf("|\t修改时长     ---- 3\t|\n");
		printf("|\t修改日期     ---- 4\t|\n");
		printf("|\t修改起始时间 ---- 5\t|\n");
		printf("|\t修改地点     ---- 6\t|\n");
		printf("|\t修改价格     ---- 7\t|\n");
		printf("|\t修改数量     ---- 8\t|\n");
		printf("|\t修改编号     ---- 9\t|\n");
		printf("|\t退出         ---- 0\t|\n");
		printf("________________________________\n");

		printf("【系统】请输入要修改的信息：");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("【系统】请输入名称：");
			scanf("%s", st->name);
			break;
		case 2:
			printf("【系统】请输入类型：");
			scanf("%s", st->type);
			break;
		case 3:
			printf("【系统】请输入时长：");
			scanf("%d", &st->time);
			break;
		case 4:
			printf("【系统】请输入日期：");
			scanf("%s", st->day);
			break;
		case 5:
			printf("【系统】请输入起始时间：");
			scanf("%s", st->start);
			break;
		case 6:
			printf("【系统】请输入地点：");
			scanf("%s", st->site);
			break;
		case 7:
			printf("【系统】请输入价格：");
			scanf("%d", &st->price);
			break;
		case 8:
			printf("【系统】请输入数量：");
			scanf("%d", &st->num);
			break;
		case 9:
			printf("【系统】请输入编号：");
			scanf("%d", &st->id);
			break;
		case 0:
			break;
		}
		printf("是否继续修改该影片信息？（Yes：1 / No：0）：");
		scanf("%d", &choice);
		if (choice == 0)
		{
			break;
		}
	}

	// 修改完成后该影片的信息
	printf("_________________________________________________________________________________________________________\n");
	printf("|\t名称\t\t|类型\t|时长\t|日期\t\t|起始时间\t|地点\t|价格\t|数量\t|编号\t|\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", st->name, st->type, st->time, st->day, st->start, st->site, st->price, st->num, st->id);
	printf("_________________________________________________________________________________________________________\n");

	// 保存信息
	Save_FILE(L);
}

// 查询影片
void Search_Printf(NODE* L)
{
	system("cls");

	int choice = 0;
	printf("按照名称查询 ---- 1\n");
	printf("按照类型查询 ---- 2\n");
	printf("按照编号查询 ---- 3\n");
	printf("【系统】请输入查询方式：");
	scanf("%d", &choice);

	node* st;

	if (choice == 1)
	{
		char name[N];
		int cnt = 0;

		printf("【系统】请输入要查询的影片名称：");
		scanf("%s", name);

		cnt = Search_allname(name, L);

		if (cnt == 0)
		{
			printf("无法找到该影片！\n");
		}
	}
	else if (choice == 2)
	{
		char type[N];
		int cnt = 0;

		printf("【系统】请输入要查询的影片类型：");
		scanf("%s", type);

		cnt = Search_type(type, L);

		if (cnt == 0)
		{
			printf("无法找到该类型的影片！\n");
		}
	}
	else if (choice == 3)
	{
		int id;

		printf("【系统】请输入要查询的影片编号：");
		scanf("%d", &id);

		st = Search_id(id, L);

		if (st == NULL)
		{
			printf("查无此片！\n");
		}
		else
		{
			st = st->next;

			printf("_________________________________________________________________________________________________________\n");
			printf("|\t名称\t\t|类型\t|时长\t|日期\t\t|起始时间\t|地点\t|价格\t|数量\t|编号\t |\n");
			printf("_________________________________________________________________________________________________________\n");
			printf("_________________________________________________________________________________________________________\n");
			printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", st->name, st->type, st->time, st->day, st->start, st->site, st->price, st->num, st->id);
			printf("_________________________________________________________________________________________________________\n");
		}
	}
}

// 按名称进行查找
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
				printf("|\t名称\t\t|类型\t|时长\t|日期\t\t|起始时间\t|地点\t|价格\t|数量\t|编号\t |\n");
				printf("_________________________________________________________________________________________________________\n");
			}
			printf("_________________________________________________________________________________________________________\n");
			printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", p->name, p->type, p->time, p->day, p->start, p->site, p->price, p->num, p->id);
			printf("_________________________________________________________________________________________________________\n");
		}

	}
	return cnt;
}

// 按名称进行查找第一个
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

// 按编号进行查找
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

// 按类型进行查找
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
				printf("|\t名称\t\t|类型\t|时长\t|日期\t\t|起始时间\t|地点\t|价格\t|数量\t|编号\t |\n");
				printf("_________________________________________________________________________________________________________\n");
			}
			printf("_________________________________________________________________________________________________________\n");
			printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", p->name, p->type, p->time, p->day, p->start, p->site, p->price, p->num, p->id);
			printf("_________________________________________________________________________________________________________\n");
		}
		
	}

	return cnt;
}

// 管理员显示影片
void Print(NODE* L)
{
	system("cls");

	node* p = L->next;
	Print_Printf();
	p->sum=(N-p->num)*p->price;                   //进循环前先计算一次票房 
	if (p != NULL)
	{
		while (p != NULL)
		{
			p->sum=(N-p->num)*p->price;           //票房=单价*（总票数-余票） 
			printf("_________________________________________________________________________________________________________\n");
			printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t|%d\t |\n", p->name, p->type, p->time, p->day, p->start, p->site, p->price, p->num, p->id,p->sum);
			printf("_________________________________________________________________________________________________________\n");
			p = p->next;
		}
	}
}

// 用户显示影片
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
	printf("|\t名称\t\t|类型\t|时长\t|日期\t|起始时间\t|地点\t|价格\t|数量\t|编号\t|票房\t |\n");
	printf("_________________________________________________________________________________________________________\n");
}

void Print_Printf2()
{
	printf("__________________________________________________________________________________________________\n");
	printf("|\t名称\t\t|类型\t|时长\t|日期\t|起始时间\t|地点\t|价格\t|数量\t|编号\t |\n");
	printf("__________________________________________________________________________________________________\n");
}

// 排序影片
void Sort(NODE* L)
{
	system("cls");

	int choice = 0;
	printf("按照票房从大到小排序 ---- 1\n");
	printf("按照票房从小到大排序 ---- 2\n\n");
	printf("【系统】请选择排序方式：");
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
				// 交换数据域
				node t = *p;
				*p = *q;
				*q = t;
				// 处理指针域
				t.next = p->next;
				p->next = q->next;
				q->next = t.next;
				flag = 0;
			}
		}
	}
	printf("【系统】排序成功！\n");
}

// 票房从大到小
int cmp_big_sum(NODE e1, NODE e2)
{
	return e1.sum > e2.sum;
}

// 票房从小到大 
int cmp_small_sum(NODE e1, NODE e2)
{
	return e1.sum < e2.sum;
}


// 文件保存售票信息
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

	// 打开文件后记得关闭
	fclose(pfWrite);

	return 1;
}

// 读取售票信息
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

		// 尾插法
		t->next = s;
		t = s;
		t->next = NULL;
	}

	fclose(pfRead);	// 打开文件后记得关闭

	return 1;
}

// 购票
void Buy_ticket()
{
	do {
		system("pause");
		Print2(&list);
	} while (Buy_ticket_Printf() == 0);
}

int Buy_ticket_Printf()
{
	TICKET s;   // 记录票务信息

	int id;
	printf("【系统】请输入您要购买的影片的编号：");
	scanf("%d", &id);

	system("cls");

	node* st = Search_id(id, &list);

	if (st == NULL)
	{
		printf("【系统】无法找到该影片！\n");

		int choice;
		printf("【系统】请选择是否要继续购票？（Yes：1 / No：0)：");
		scanf("%d", &choice);
		
		if (choice == 1)
			return 0;
		else if (choice == 0)
			return 1;
		else
		{
			printf("输入错误\n");
			system("pause");
			return 1;
		}
	}

	st = st->next;
	printf("【系统】该影片的信息如下：\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("|\t名称\t\t|类型\t|时长\t|日期\t|起始时间\t|地点\t|价格\t|数量\t|编号\t |\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("_________________________________________________________________________________________________________\n");
	printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|%d\t |\n", st->name, st->type, st->time, st->day, st->start, st->site, st->price, st->num, st->id);
	printf("_________________________________________________________________________________________________________\n");

	printf("【系统】座位示意图如下：(■表示已预定，□表示未预定）\n");

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
				printf(" □");
			else
				printf(" ■");
		}
		printf("\n");
	}

	int a;
	printf("【系统】请选择您要购买的数量：");
	scanf("%d", &a);

	for (int i = 0; i < a; i++)
	{
		printf("【系统】请选择您要购买的座位号：\n");
		int x, y;
		printf("行（1-10）：");
		scanf("%d", &x);
		printf("列（1-10）：");
		scanf("%d", &y);

		if (st->seat[x][y] == 0)
		{
			st->seat[x][y] = 1;
			st->num = st->num - 1;
		}
		else
		{
			printf("【系统】预定失败，该座位已被预定\n");

			int choice;
			printf("【系统】请选择是否要继续购票？（Yes：1 / No：0)：");
			scanf("%d", &choice);

			if (choice == 1)
				return 0;
			else if (choice == 0)
				return 1;
			else
			{
				printf("输入错误\n");
				system("pause");
				return 1;
			}
		}

		// 记录订单信息
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

		printf("【系统】预定成功\n");
	}

	system("pause");
	system("cls");

	printf("【系统】您的订单信息如下：\n");
	printf("_________________________________________________________________________________________________\n");
	printf("|\t名称\t\t|类型\t|时长\t|日期\t|起始时间\t|地点\t|价格\t|数量\t|\n");
	printf("_________________________________________________________________________________________________\n");
	printf("_________________________________________________________________________________________________\n");
	printf("|%-15s\t|%s\t|%d\t|%s\t|%s\t\t|%s\t|%d\t|%d\t|\n", st->name, st->type, st->time, st->day, st->start, st->site, st->price * a, a);
	printf("_________________________________________________________________________________________________\n");

	system("pause");

	Save_FILE(&list);
	return 1;
}

// 保存预定信息
void Add2(TICKET* L, TICKET e)
{
	// 头插法
	TICKET* p = L;
	TICKET* s = (TICKET*)malloc(sizeof(TICKET));
	*s = e;

	s->next = p->next;
	p->next = s;

	Save_TICKET(L);
}

// 取票
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
			printf("【系统】您的订单如下：\n");
			Print_ticket_Printf();
			printf("______________________________________________________________________________________________________________________\n");
			printf("|%-15s\t|%s\t|%d\t|%s\t\t|%s\t\t|%s\t|%d\t|%d\t |%-10s|%d\t|%-5d|\n", p->name, p->type, p->time, p->day, p->start, p->site, p->price, p->id, p->username, p->x, p->y);
			printf("______________________________________________________________________________________________________________________\n");

			printf("【系统】是否取票？（Yes：1 / No：0)：");
			scanf("%d", &choice);

			if (choice != 1)
			{
				if (choice != 0)
					printf("【系统】输入错误！！！\n");
			}
			else
			{
				p->istake = 1;
				printf("【系统】取票成功！！！\n");
			}
			system("pause");

			p = p->next;

			cnt++;
		}
	}

	if (cnt == 0)
		printf("【系统】抱歉，您当前无票可取。\n");
}

void Print_ticket_Printf()
{
	system("cls");
	printf("______________________________________________________________________________________________________________________\n");
	printf("|\t名称\t\t|类型\t|时长\t|日期\t\t|起始时间\t|地点\t|价格\t|编号\t |购票人    |行\t|列   |\n");
	printf("______________________________________________________________________________________________________________________\n");
}

// 退票
void Return_ticket()
{
	system("cls");

	printf("【系统】您的订单如下：\n");
	system("pause");
	Print_ticket1(&c);

	Save_TICKET(&c);
}

// 打印信息
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

		printf("【系统】是否退票？（Yes：1 / No：0)：");
		scanf("%d", &choice);

		if (choice != 1)
		{
			if (choice != 0)
				printf("【系统】输入错误！！！\n");
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
		printf("【系统】抱歉，您当前无票可退。\n");
}

// 查找前驱节点
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

// 删除
void Delete_ticket(TICKET* s)
{
	TICKET* t = s->next;

	s->next = t->next;
	t->next = NULL;

	free(t);
}

// 退出系统
void goodbye()
{
	system("cls");
	printf("欢迎下次使用影院售票管理系统！");
	exit(0);
}
