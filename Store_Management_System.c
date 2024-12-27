#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
// Username: admin
// Password: 1

//--------------------------Definition date------------------------
typedef struct Date
{
	int day;
	int month;
	int year;
} ImportDate;

//------------------Definition structure of Product----------------------
struct Product
{
	char id[10];
	char name[50];
	ImportDate Date;
	char brand[50];
	int price;
	int quantity;
};
typedef struct Product Product;

//-----------------------------Definition function----------------------
void printLine(int x);
int checkId(char id[]);
int login();
void menu();
void add();
void display();
void deleteID();
void updateById();
void searchProductByName();
void sortByPrice();

//----------------------------Set position-----------------------------
COORD coord;
void gotoxy(int x, int y)
{
	coord.X = x;
	coord.Y = y; /// X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// GOTOXY to set position
//---------------------MAIN-----------------------------------
int main()
{
	system("color e4"); // set color
	int l = login();	// check login
	if (l == 0)
		return 0;
	else
	{
		system("cls"); // Clear display
		gotoxy(20, 8);
		printf("WELCOME TO THE PROGRAM");
		menu();
	}
	return 0;
}

//-----------------------------Print "-"-----------------------------------------
void printLine(int x)
{
	for (int i = 0; i < x; i++)
	{
		if (i == 0 || i == x - 1)
			printf("+");
		else
			printf("-");
	}
}

//--------------------------------------ID must unique-----------------------------
int checkId(char id[])
{
	FILE *fp;
	Product p;
	fp = fopen("Database.txt", "rb+");
	if (fp == NULL)
	{
		printf("\nNo data in DB!");
		exit(1);
	}
	else
	{
		while (fread(&p, sizeof(p), 1, fp) == 1)
		{
			if (strcmp(id, p.id) == 0)
			{
				return 1;
			}
		}
	}
	fclose(fp);
	return 0;
}

//--------------------------------------Check login---------------------------
int login()
{
	char c;
	int count = 3;
	while (count > 0)
	{
		char userName[9];
		char password[9];
		int num = 0;
		gotoxy(5, 5);
		printf("SIGN IN");
		gotoxy(5, 6);
		printf("User name: ");
		fflush(stdin);
		gets(userName);
		gotoxy(5, 7);
		printf("Password: ");
		do
		{
			if (kbhit())
			{ // ham kbhit dung de phat hien co su kien phim nhan (trong thu vien conio.h)
				c = getch();
				if (c != 13)
				{
					password[num] = c;
					num++;
					printf("*");
				}
				else
					break;
			}
		} while (1);
		if (strcmp(userName, "admin") == 0 && strcmp(password, "1") == 0)
			return 1;
		else
		{
			gotoxy(5, 10);
			printf("Incorrect user name or password!");
			count--;
			getch();
			system("cls");
		}
	}
	return 0;
}

//-------------------------------Menu---------------------------------------
void menu()
{
	int choice;
	gotoxy(10, 10);
	printf("+========================================+");
	gotoxy(10, 11);
	printf("|| 		   TripleT		  ||");
	gotoxy(10, 12);
	printf("||   Fashion Store Management System 	  ||");
	gotoxy(10, 13);
	printf("||		     Menu 		  ||");
	gotoxy(10, 14);
	printf("+========================================+");
	gotoxy(10, 15);
	printf("||1. Add Product		  	  ||");
	gotoxy(10, 16);
	printf("||2. Update Product		  	  ||");
	gotoxy(10, 17);
	printf("||3. Delete Product		  	  ||");
	gotoxy(10, 18);
	printf("||4. List Product		  	  ||");
	gotoxy(10, 19);
	printf("||5. Search Product by Name   	  ||");
	gotoxy(10, 20);
	printf("||6. Sort by Price			  ||");
	gotoxy(10, 21);
	printf("||0. Exit			  	  ||");
	gotoxy(10, 22);
	printf("+========================================+");
	gotoxy(10, 23);
	printf("||Your choice: ");
	gotoxy(50, 23);
	printf("||");
	gotoxy(10, 24);
	printf("+========================================+");
	gotoxy(26, 23);
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		add();
		break;
	case 2:
		updateById();
		break;
	case 3:
		deleteID();
		break;
	case 4:
		display();
		break;
	case 5:
		searchProductByName();
		break;
	case 6:
		sortByPrice();
		break;
	case 0:
		exit(0);
		break;
	default:
		system("cls");
		gotoxy(10, 8);
		printf("Enter 0 to 6 only! Please input again!");
		menu();
	}
}

//------------------------------------Add product-----------------------------------
void add()
{
	system("cls");
	FILE *fp;
	struct Product p;
	fp = fopen("Database.txt", "ab+");
	char another = 'y';
	while (another == 'y' || another == 'Y')
	{
		gotoxy(25, 1);
		printf("Add product: ");
		gotoxy(5, 2);
		printLine(52);
		gotoxy(5, 3);
		printf("|Field			|Information		|");
		gotoxy(5, 4);
		printLine(52);
		fflush(stdin);
		gotoxy(5, 5);
		printf("|Enter id: ");
		gotoxy(32, 5);
		printf("|");
		gotoxy(56, 5);
		printf("|");
		gotoxy(33, 5);
		gets(p.id);
		if (checkId(p.id) == 1)
		{
			system("cls");
			gotoxy(5, 5);
			printf("The id is duplicated! Please input again!");
			gotoxy(5, 6);
			printf("Press 0.Menu | 1.Input again:");
			gotoxy(35, 6);
			if (getch() == '0')
			{
				fclose(fp);
				system("cls");
				menu();
			}
			else
			{
				add();
			}
		}
		else
		{
			gotoxy(5, 6);
			printf("|Enter name: ");
			gotoxy(32, 6);
			printf("|");
			gotoxy(56, 6);
			printf("|");
			gotoxy(33, 6);
			gets(p.name);
			gotoxy(5, 7);
			printf("|Enter importday: ");
			gotoxy(32, 7);
			printf("|");
			gotoxy(56, 7);
			printf("|");
			gotoxy(33, 7);
			scanf("%d%d%d", &p.Date.day, &p.Date.month, &p.Date.year);
			fflush(stdin);
			gotoxy(5, 8);
			printf("|Enter brand: ");
			gotoxy(32, 8);
			printf("|");
			gotoxy(56, 8);
			printf("|");
			gotoxy(33, 8);
			gets(p.brand);
			gotoxy(5, 9);
			printf("|Enter price: ");
			gotoxy(32, 9);
			printf("|");
			gotoxy(56, 9);
			printf("|");
			gotoxy(33, 9);
			scanf("%d", &p.price);
			gotoxy(5, 10);
			printf("|Enter quantity: ");
			gotoxy(32, 10);
			printf("|");
			gotoxy(56, 10);
			printf("|");
			gotoxy(33, 10);
			scanf("%d", &p.quantity);

			gotoxy(5, 11);
			printLine(52);
			fwrite(&p, sizeof(p), 1, fp);

			fflush(stdin);
			gotoxy(5, 19);
			printf("\nRecord saved");
			gotoxy(5, 20);
			printf("\nAdd another product? (Y/N)? ");
			fflush(stdin); // fflush dung de loai bo nhung ky tu thua
			another = getchar();
			system("cls");
		}
	}
	fclose(fp);
	if (another == 'n' || another == 'N')
	{
		fclose(fp);
		system("cls");
		menu();
	}
}

//-----------------------------------------Display product-------------------------------------------------------
void display()
{
	system("cls");
	fflush(stdin);
	struct Product p;
	FILE *fp;
	int i = 10;
	fp = fopen("Database.txt", "rb");
	if (fp == NULL)
	{
		printf("\nFile opening error");
		exit(1);
	}
	gotoxy(5, 5);
	printLine(94);
	gotoxy(5, 6);
	printf("|\t\t\t\t\t  LIST OF PRODUCTS\t\t\t\t\t  |");
	gotoxy(5, 7);
	printLine(94);
	gotoxy(5, 8);
	printf("|%-10s|%-20s|%-22s|%-15s|%-10s|%-10s|",
		   "ID", "Name", "Import Day", "Brand", "Price", "Quantity");
	gotoxy(5, 9);
	printLine(94);
	while (fread(&p, sizeof(p), 1, fp) == 1)
	{
		gotoxy(5, i);
		printf("|%-10s|%-20s|%-2d - %-2d - %-12d|%-15s|%-10d|%-10d|",
			   p.id, p.name, p.Date.day, p.Date.month, p.Date.year, p.brand, p.price, p.quantity);
		i++;
	}
	gotoxy(5, i);
	printLine(94);

	fclose(fp);
	gotoxy(5, i + 2);
	printf("Enter any key to back to menu!");
	getch();
	system("cls");
	menu();
}

//----------------------------------------Delete Product by ID---------------------------------
void deleteID()
{
	struct Product p;
	FILE *fp, *temp;
	int flag;
	char id[10];
	fp = fopen("Database.txt", "rb");
	if (fp == NULL)
	{
		gotoxy(5, 5);
		printf("No Data in DB");
		gotoxy(5, 6);
		printf("Press any key...");
		getch();
		system("cls");
		menu();
	}
	else
	{
		temp = fopen("temp.txt", "wb+");
		if (temp == NULL)
		{
			gotoxy(5, 5);
			printf("Opening database error");
			gotoxy(5, 6);
			printf("Press any key...");
			getch();
			system("cls");
			menu();
		}
		else
		{
			system("cls");
			gotoxy(6, 6);
			printf("Enter the product's id: ");
			fflush(stdin);
			gotoxy(30, 6);
			gets(id);
			while (fread(&p, sizeof(p), 1, fp) == 1)
			{
				if (strcmp(id, p.id) != 0)
					fwrite(&p, sizeof(p), 1, temp);
				if (strcmp(id, p.id) == 0)
					flag = 1;
			}
			fclose(temp);
			fclose(fp);
			if (flag != 1)
			{
				gotoxy(8, 8);
				printf("Cannot delete!");
				remove("temp.txt");
				gotoxy(8, 9);
				printf("Press any key...");
				getchar();
				system("cls");
				menu();
			}
			else
			{
				remove("Database.txt");
				rename("temp.txt", "Database.txt");
				gotoxy(8, 8);
				printf("Deleted Successfully");
				gotoxy(8, 9);
				printf("Press any key...");
				getchar();
				system("cls");
				menu();
			}
		}
	}
}

//---------------------------------------Update information-------------------------------
void updateById()
{
	FILE *fp;
	int flag = 0;
	int choice = 'y';
	struct Product p;
	char id[10];
	fp = fopen("Database.txt", "rb+");
	if (fp == NULL)
	{
		printf("\nNo Data in DB!");
		exit(1);
	}
	else
	{
		system("cls");
		while (choice == 'y' || choice == 'Y')
		{
			gotoxy(5, 3);
			printf("Modify product");
			fflush(stdin);
			gotoxy(5, 5);
			printf("Enter the product's id to modify: ");
			gotoxy(40, 5);
			gets(id);
			while (fread(&p, sizeof(p), 1, fp) == 1)
			{
				if (strcmp(id, p.id) == 0)
				{
					fflush(stdin);

					gotoxy(5, 7);
					printf("Product found!");

					do
					{
						gotoxy(5, 9);
						printLine(35);
						gotoxy(5, 10);
						printf("|Choose what you want to update   |");
						gotoxy(5, 11);
						printLine(35);
						gotoxy(5, 12);
						printf("|1.Name");
						gotoxy(39, 12);
						printf("|");
						gotoxy(5, 13);
						printf("|2.Import Day");
						gotoxy(39, 13);
						printf("|");
						gotoxy(5, 14);
						printf("|3.Brand");
						gotoxy(39, 14);
						printf("|");
						gotoxy(5, 15);
						printf("|4.Price");
						gotoxy(39, 15);
						printf("|");
						gotoxy(5, 16);
						printf("|5.Quantity");
						gotoxy(39, 16);
						printf("|");
						gotoxy(5, 17);
						printf("|6.Update all");
						gotoxy(39, 17);
						printf("|");
						gotoxy(5, 18);
						printf("|0.Exit");
						gotoxy(39, 18);
						printf("|");
						gotoxy(5, 19);
						printLine(35);
						gotoxy(5, 20);
						printf("|Your choice:");
						gotoxy(39, 20);
						printf("|");
						gotoxy(5, 21);
						printLine(35);
						gotoxy(20, 20);
						scanf("%d", &choice);
						switch (choice)
						{
						case 1:
							gotoxy(50, 9);
							printf("Modify %s's name", p.id);
							fflush(stdin);
							gotoxy(50, 10);
							printf("Enter name: ");
							gotoxy(64, 10);
							gets(p.name);
							gotoxy(50, 11);
							printf("Name is modified");
							fseek(fp, -(long)sizeof(p), SEEK_CUR); // ham nay dung de tro dung vi tri minh dang dung, tro vao cai id minh dang can sua
							fwrite(&p, sizeof(p), 1, fp);
							flag = 1; // dat flag = 1 o day de khi xong het minh xu ly o phia duoi; cac ham duoi tuong tu
							break;
						case 2:
							gotoxy(50, 13);
							printf("Modify %s's import day", p.id);
							gotoxy(50, 14);
							printf("Enter import day: ");
							gotoxy(70, 14);
							scanf("%d%d%d", &p.Date.day, &p.Date.month, &p.Date.year);
							gotoxy(50, 15);
							printf("Import day is modified");
							fseek(fp, -(long)sizeof(p), SEEK_CUR);
							fwrite(&p, sizeof(p), 1, fp);
							flag = 1;
							break;
						case 3:
							gotoxy(50, 17);
							printf("Modify %s's brand", p.id);
							fflush(stdin);
							gotoxy(50, 18);
							printf("Enter brand: ");
							gotoxy(65, 18);
							gets(p.brand);
							gotoxy(50, 19);
							printf("Brand is modified");
							fseek(fp, -(long)sizeof(p), SEEK_CUR);
							fwrite(&p, sizeof(p), 1, fp);
							flag = 1;
							break;
						case 4:
							gotoxy(50, 21);
							printf("Modify %s's price", p.id);
							fflush(stdin);
							gotoxy(50, 22);
							printf("Enter price: ");
							gotoxy(65, 22);
							scanf("%d", &p.price);
							gotoxy(50, 23);
							printf("price is modified");
							fseek(fp, -(long)sizeof(p), SEEK_CUR);
							fwrite(&p, sizeof(p), 1, fp);
							flag = 1;
							break;
						case 5:
							gotoxy(50, 25);
							printf("Modify %s's quantity", p.id);
							gotoxy(50, 26);
							printf("Enter quantity: ");
							gotoxy(65, 26);
							scanf("%d", &p.quantity);
							gotoxy(50, 27);
							printf("Quantity is modified");
							fseek(fp, -(long)sizeof(p), SEEK_CUR);
							fwrite(&p, sizeof(p), 1, fp);
							flag = 1;
							break;
						case 6:
							gotoxy(80, 9);
							printf("Modify all field");
							fflush(stdin);
							gotoxy(80, 10);
							printf("Enter name: ");
							gotoxy(95, 10);
							gets(p.name);
							gotoxy(80, 11);
							printf("Enter import day: ");
							gotoxy(100, 11);
							scanf("%d%d%d", &p.Date.day, &p.Date.month, &p.Date.year);
							fflush(stdin);
							gotoxy(80, 12);
							printf("Enter brand: ");
							gotoxy(96, 12);
							gets(p.brand);
							gotoxy(80, 13);
							printf("Enter price: ");
							gotoxy(96, 13);
							scanf("%d", &p.price);
							gotoxy(80, 14);
							printf("Enter quantity: ");
							gotoxy(95, 14);
							scanf("%d", &p.quantity);
							fflush(stdin);
							gotoxy(80, 15);
							printf("Modify successfully!");
							fseek(fp, -(long)sizeof(p), SEEK_CUR);
							fwrite(&p, sizeof(p), 1, fp);
							flag = 1;
							break;
						case 0:
							flag = 1;
							break;
						default:
							printf("\nPlease input from 1 to 6 to update!");
							break;
						}
					} while (choice != 0);
					break;
				}
				fflush(stdin);
			}
			if (flag == 1)
			{
				gotoxy(5, 30);
				printf("Do you want to modify another product? (Y/N)?");
				fflush(stdin);
				choice = getchar();
				system("cls");
			}
			else
			{
				gotoxy(5, 7);
				printf("No record Found in database");
				fclose(fp);
				gotoxy(5, 8);
				printf("Press any key...");
				fflush(stdin);
				getch();
				system("cls");
				menu();
			}
		}
		if (choice == 'n' || choice == 'N')
		{
			fclose(fp);
			system("cls");
			menu();
		}
	}
}
//-------------------------Search product by Name-------------------------
void separateName(char fullName[], char firstName[], char lastName[])
{
	int i, j, n = strlen(fullName);
	for (i = n - 1; i > 0; i--)
	{
		if (fullName[i] == ' ')
			break;
	}
	for (j = 0; j < i; j++)
	{
		lastName[j] = fullName[j];
		lastName[i] = '\0';
	}
	for (j = i + 1; j < n; j++)
		firstName[j - i - 1] = fullName[j];
	firstName[n - i - 1] = '\0';
}

int checkName(char x[])
{
	int length = strlen(x);
	for (int i = 0; i < length; i++)
		if (x[i] == ' ')
			return 1;
	return 0;
}

void searchProductByName()
{
	struct Product s;
	FILE *fp;
	char name[50], firstName[20], lastName[20];
	char choice = 'y';
	fp = fopen("Database.txt", "rb");
	if (fp == NULL)
	{
		printf("\nERROR");
		exit(1);
	}

	while (choice == 'y' || choice == 'Y')
	{
		system("cls");
		int count = 0, i = 10;
		int isFound = 0;
		gotoxy(5, 5);
		printf("Enter the name of the product want to search: ");
		fflush(stdin);
		gotoxy(52, 5);
		gets(name);
		gotoxy(8, 7);
		printLine(94);
		gotoxy(8, 8);
		printf("|%-10s|%-20s|%-22s|%-15s|%-10s|%-10s|",
			   "ID", "Name", "Import Day", "Brand", "Price", "Quantity");
		gotoxy(8, 9);
		printLine(94);
		fseek(fp, SEEK_SET, 0);
		while (fread(&s, sizeof(s), 1, fp) == 1)
		{
			if (checkName(s.name) == 1)
			{
				separateName(s.name, firstName, lastName);
				if (strcmp(firstName, name) == 0 || strcmp(lastName, name) == 0 || strcmp(s.name, name) == 0)
				{
					gotoxy(8, i);
					printf("|%-10s|%-20s|%-2d - %-2d - %-12d|%-15s|%-10d|%-10d|",
						   s.id, s.name, s.Date.day, s.Date.month, s.Date.year, s.brand, s.price, s.quantity);
					isFound = 1;
					i++;
					count++;
				}
			}
		}
		if (isFound == 0)
		{
			gotoxy(8, i);
			printLine(94);
			gotoxy(8, i + 2);
			printf("Sorry, no record FOUND in the database");
			gotoxy(8, i + 3);
			printf("Do you want to search other names? (Y/N)?");
			fflush(stdin);
			choice = getchar();
		}
		else
		{
			printf("\n");
			isFound = 0;
			gotoxy(8, i);
			printLine(94);
			gotoxy(8, i + 2);
			printf("FOUND %d record(s) in the database", count);
			gotoxy(8, i + 3);
			printf("Do you want to search other names? (Y/N)?");
			fflush(stdin);
			choice = getchar();
		}
	}
	fclose(fp);
	if (choice == 'n' || choice == 'N')
	{
		system("cls");
		fclose(fp);
		menu();
	}
	//	fclose(fp);
}

//-------------------------Sort product by price (Asending)--------------------------
void sortByPrice()
{
	Product *s, s1;
	FILE *fp;
	int i;
	fp = fopen("Database.txt", "rb");
	fseek(fp, 0, SEEK_END);
	int n = ftell(fp) / sizeof(Product);
	s = (Product *)calloc(n, sizeof(Product));

	rewind(fp);
	if (fp == NULL)
	{
		printf("\nERROR");
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			fread(&s[i], sizeof(Product), 1, fp);
		}
		fclose(fp);
		char choice;
		system("cls");
		gotoxy(5, 5);
		printf("Choose A(Ascending) or D(Descending): ");
		scanf("%c", &choice);
		switch (choice)
		{
		case 'A':
			for (int i = 0; i < n; i++)
			{
				for (int j = i + 1; j < n; j++)
				{
					if (s[i].price > s[j].price)
					{
						s1 = s[i];
						s[i] = s[j];
						s[j] = s1;
					}
				}
			}
			break;
		case 'D':
			for (int i = 0; i < n; i++)
			{
				for (int j = i + 1; j < n; j++)
				{
					if (s[i].price < s[j].price)
					{
						s1 = s[i];
						s[i] = s[j];
						s[j] = s1;
					}
				}
			}
			break;
		default:
			system("cls");
			sortByPrice();
		}

		system("cls");
		gotoxy(5, 5);
		printLine(94);
		gotoxy(5, 6);
		printf("|\t\t\t\t\tLIST OF PRODUCTS AFTER SORTING\t\t\t\t  |");
		gotoxy(5, 7);
		printLine(94);
		gotoxy(5, 8);
		printf("|%-10s|%-20s|%-22s|%-15s|%-10s|%-10s|",
			   "ID", "Name", "Import Day", "Brand", "Price", "Quantity");
		gotoxy(5, 9);
		printLine(94);
		for (i = 0; i < n; i++)
		{
			gotoxy(5, 10 + i);
			printf("|%-10s|%-20s|%-2d - %-2d - %-12d|%-15s|%-10d|%-10d|",
				   s[i].id, s[i].name, s[i].Date.day, s[i].Date.month, s[i].Date.year, s[i].brand, s[i].price, s[i].quantity);
		}
		gotoxy(5, i + 10);
		printLine(94);
		free(s);
		gotoxy(5, i + 12);
		printf("Press any key...");
		getch();
		system("cls");
		menu();
	}
}