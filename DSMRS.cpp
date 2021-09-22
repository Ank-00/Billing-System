#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
struct memory{
    char ID[15];
    char product[20];
    char name[20];
    char quan[20];
    char price[20];
	char total[20];
};
struct stock{
    char ID[15];
    char product[20];
    char name[20];
    char quan[20];
    char price[20];
};
void employee();
void adminuser();
void user();
void out();
struct stock st;
struct memory mem;
int quantity;
int pricetemp;
void SetColor(int ForgC)
{
     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD coord = {0, 0};
     DWORD count;
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

COORD coord = {0,0}; 
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearWindow(){
    int i,j;
    for(i = 0; i < 78; i++){
        for(j = 6; j < 25; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}
void clearWindowfull(){
    int i,j;
    for(i = 0; i < 90; i++){
        for(j = 26; j < 40; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}

void generate(){
	clearWindow();
	SetColor(28);
	gotoxy(5,6);
	printf("Generate a Bill");
	gotoxy(5,7);
	printf("----------------");
    FILE *fp;
    fp = fopen("record.txt","ab+");
    SetColor(0);
    if(fp == NULL){
        MessageBox(0,"Error in Opening file\nMake sure your file is not write protected","Warning",0);

    } 
	else{
        fflush(stdin);
        
        gotoxy(2,10);printf("ID: ");gets(mem.ID);
        gotoxy(2,12);printf("Customer Name: ");gets(mem.name);
        gotoxy(2,14);printf("Product Name: ");gets(mem.product);
        gotoxy(2,16);printf("Quantity: ");scanf("%d",&quantity);
        gotoxy(2,18);printf("Price: ");scanf("%d",&pricetemp);
        int total = quantity * pricetemp;
       	itoa(total,mem.total,10);
       	itoa(quantity,mem.quan,10);
       	itoa(pricetemp,mem.price,10);
        gotoxy(50,5);SetColor(45);printf("Total Price: ");printf("%s",mem.total);
        SetColor(0);
        fwrite(&mem, sizeof(mem), 1, fp);
    	FILE * fo;
    	fo=fopen("stock.txt","rb+");
    	while(fread(&st, sizeof(st),1,fo) == 1){
        if(strcmp(mem.product, st.product) == 0){
            fflush(stdin);
            int val = atoi(st.quan);
            int as= val-quantity;
            itoa(as,st.quan,10);
            fseek(fo,-sizeof(st), SEEK_CUR);
            fwrite(&st,sizeof(st), 1, fo);
            break;
        }
    }
    fclose(fo);
    }
    fclose(fp);
    char man;
    SetColor(0);
    gotoxy(2,18);printf("Are you want to add more? (Y/N)");scanf("%c",&man);
    if(man == 'y' || man == 'y'){
    	generate();
	}
	else{
		employee();
	}
}
void search(){
    clearWindow();
	SetColor(28);
	gotoxy(5,6);
	printf("Search a Bill");
	gotoxy(5,7);
	printf("----------------");
	SetColor(00);
    char s_id[15];
    int isFound = 0;
    gotoxy(2,8);printf("Enter ID to Search: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("record.txt","rb");
    while(fread(&mem,sizeof(mem),1,fp) == 1){
        if(strcmp(s_id,mem.ID) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
    	SetColor(28);
        gotoxy(15,10);printf("The record is Found");
        SetColor(00);
        gotoxy(2,12);printf("ID: %s",mem.ID);
        gotoxy(2,14);printf("Customer Name: %s",mem.name);
        gotoxy(2,16);printf("Product: %s",mem.product);
        gotoxy(2,18);printf("Quantity: %s",mem.quan);
        gotoxy(2,20);printf("Price: %s",mem.price);
        gotoxy(2,22);printf("Total: %s",mem.total);
    }else{
        gotoxy(2,12);printf("Sorry, No record found in the database");
    }
    fclose(fp);
    gotoxy(2,23);printf("Press any key to go back... ");
    getch();
    adminuser();
}
void modify(){
    clearWindow();
	SetColor(28);
	gotoxy(5,6);
	printf("Modify a Bill");
	gotoxy(5,7);
	printf("----------------");
	SetColor(00);
    char s_id[15];
    int isFound = 0, print = 37;
    gotoxy(2,8);printf("Enter ID to Modify: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("record.txt","rb+");
    while(fread(&mem, sizeof(mem),1,fp) == 1){
        if(strcmp(s_id, mem.ID) == 0){
            fflush(stdin);
        gotoxy(2,10);printf("ID: %s",mem.ID);
        gotoxy(2,12);printf("Customer Name: %s",mem.name);
        gotoxy(2,14);printf("Product Name: ");gets(mem.product);
        gotoxy(2,16);printf("Quantity: ");scanf("%d",&quantity);
        gotoxy(2,18);printf("Price: ");scanf("%d",&pricetemp);
        int total = quantity * pricetemp;
       	itoa(total,mem.total,10);
       	itoa(quantity,mem.quan,10);
       	itoa(pricetemp,mem.price,10);
        gotoxy(2,20);printf("Total Price: ");printf("%c",mem.total);
            fseek(fp,-sizeof(mem), SEEK_CUR);
            fwrite(&mem,sizeof(mem), 1, fp);
            isFound = 1;
            break;
        }
    }
    if(!isFound){
        gotoxy(print, 12);printf("No Record Found");
    }
    fclose(fp);
    gotoxy(2,23);printf("Press any key to go back... ");
    getch();
    adminuser();
}
void search2(){
    clearWindow();
	SetColor(28);
	gotoxy(5,6);
	printf("Search a Bill");
	gotoxy(5,7);
	printf("----------------");
	SetColor(00);
    char s_id[15];
    int isFound = 0;
    gotoxy(2,8);printf("Enter ID to Search: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("record.txt","rb");
    while(fread(&mem,sizeof(mem),1,fp) == 1){
        if(strcmp(s_id,mem.ID) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
    	SetColor(28);
        gotoxy(15,10);printf("The record is Found");
        SetColor(00);
        gotoxy(2,12);printf("ID: %s",mem.ID);
        gotoxy(2,14);printf("Customer Name: %s",mem.name);
        gotoxy(2,16);printf("Product: %s",mem.product);
        gotoxy(2,18);printf("Quantity: %s",mem.quan);
        gotoxy(2,20);printf("Price: %s",mem.price);
        gotoxy(2,22);printf("Total: %s",mem.total);
    }else{
        gotoxy(2,12);printf("Sorry, No record found in the database");
    }
    fclose(fp);
    gotoxy(2,23);printf("Press any key to go back... ");
    getch();
    employee();
}
void modify2(){
    clearWindow();
	SetColor(28);
	gotoxy(5,6);
	printf("Modify a Bill");
	gotoxy(5,7);
	printf("----------------");
	SetColor(00);
    char s_id[15];
    int isFound = 0, print = 37;
    gotoxy(2,8);printf("Enter ID to Modify: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("record.txt","rb+");
    while(fread(&mem, sizeof(mem),1,fp) == 1){
        if(strcmp(s_id, mem.ID) == 0){
            fflush(stdin);
        gotoxy(2,10);printf("ID: %s",mem.ID);
        gotoxy(2,12);printf("Customer Name: %s",mem.name);
        gotoxy(2,14);printf("Product Name: ");gets(mem.product);
        gotoxy(2,16);printf("Quantity: ");scanf("%d",&quantity);
        gotoxy(2,18);printf("Price: ");scanf("%d",&pricetemp);
        int total = quantity * pricetemp;
       	itoa(total,mem.total,10);
       	itoa(quantity,mem.quan,10);
       	itoa(pricetemp,mem.price,10);
        gotoxy(2,20);printf("Total Price: ");printf("%c",mem.total);
            fseek(fp,-sizeof(mem), SEEK_CUR);
            fwrite(&mem,sizeof(mem), 1, fp);
            isFound = 1;
            break;
        }
    }
    if(!isFound){
        gotoxy(print, 12);printf("No Record Found");
    }
    fclose(fp);
    gotoxy(2,23);printf("Press any key to go back... ");
    getch();
    employee();
}

void out(){
clearWindow();
	SetColor(28);
	gotoxy(5,6);
	printf("Display all Stock Record");
	gotoxy(5,7);
	printf("---------------------------");
	gotoxy(4,10);printf("ID");
    gotoxy(20,10);printf("Product");
    gotoxy(35,10);printf("Quantity");
    gotoxy(2,11);printf("----------------------------------------------");
	int idc=12;
    fflush(stdin);
    FILE *fo;
    fo = fopen("stock.txt","rb");
    int size= sizeof(st);
    for(int i=1;i<=size;i++){
    	while(fread(&st,size,1,fo)==1){
        SetColor(00);
        gotoxy(4,idc);printf("%s",st.ID);
        gotoxy(20,idc);printf("%s",st.product);
        gotoxy(35,idc);printf("%s",st.quan);
        idc=idc+2;
        
	}
}
    fclose(fo);
    SetColor(28);
    gotoxy(2,idc);printf("Press any key to go back... ");
    SetColor(0);
    getch();
    clearWindowfull();
    adminuser();
}
void display(){
clearWindow();
	SetColor(28);
	gotoxy(5,6);
	printf("Display all Billing Record");
	gotoxy(5,7);
	printf("---------------------------");
	SetColor(00);
		gotoxy(2,9);printf("ID");
        gotoxy(8,9);printf("Customer Name");
        gotoxy(25,9);printf("Product Name");
        gotoxy(40,9);printf("Quantity");
        gotoxy(50,9);printf("Price");
        gotoxy(58,9);printf("Total");
        gotoxy(2,10);SetColor(00);printf("-----------------------------------------------------------------------");
	int idc=11;
    fflush(stdin);
    FILE *fp;
    fp = fopen("record.txt","rb");
    int size= sizeof(mem);
    for(int i=1;i<=size;i++){
    	while(fread(&mem,size,1,fp) == 1){
        SetColor(00);
        gotoxy(2,idc);printf("%s",mem.ID);
        gotoxy(8,idc);printf("%s",mem.name);
        gotoxy(25,idc);printf("%s",mem.product);
        gotoxy(40,idc);printf("%s",mem.quan);
        gotoxy(50,idc);printf("%s",mem.price);
        gotoxy(58,idc);printf("%s",mem.total);
        idc=idc+2;
        
	}
}
    fclose(fp);
    SetColor(28);
    gotoxy(2,idc);printf("Press any key to go back... ");
    SetColor(0);
    getch();
    clearWindowfull();
    adminuser();
}
void del(){
    clearWindow();
	SetColor(28);
	gotoxy(5,6);
	printf("Delete a Bill");
	gotoxy(5,7);
	printf("----------------");
	SetColor(00);
    char s_id[15];
    int isFound = 0;
    gotoxy(2,10);printf("Enter ID to Modify: ");fflush(stdin);
    gets(s_id);
    FILE *fp, *temp;
    fp = fopen("record.txt","rb");
    temp = fopen("temp.txt", "wb");
    while(fread(&mem, sizeof(mem),1,fp) == 1){
        if(strcmp(s_id, mem.ID) == 0){
            fwrite(&mem,sizeof(mem),1,temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("record.txt");
    rename("temp.txt","record.txt");
    gotoxy(28,20);
	SetColor(28);
	printf("Record Deleted Successfully");
	SetColor(0);
	getch();
    adminuser();
}

void employee(){
	clearWindow();
	int choice;
    int x = 2;
    while(1){
    	gotoxy(5,6);
		printf("Select a option");
		gotoxy(5,7);
		printf("----------------");
        gotoxy(x,8);printf("1. Generate a Bill");
        gotoxy(x,10);printf("2. Search a Record");
        gotoxy(x,12);printf("3. Modify a Record");
        SetColor(28);
        gotoxy(x,16);printf("4. Logout from Employee Panel");
        gotoxy(x,18);printf("5. Exit");
        gotoxy(x,23);printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
		case 1:
		generate();
		break;
		case 2:
		search2();
		break;
		case 3:
		modify2();
		break;
		case 4:
		user();
		break;
		case 5:
		exit(0);
		break;
		default:
			gotoxy(2,5);
			SetColor(28);
			printf("Invalid Input ! Enter your choice from 1 to 5 only....... Restart the Application");
			user();
    }
}
}
void stock(){
	clearWindow();
	SetColor(28);
	gotoxy(5,6);
	printf("Generate a stock");
	gotoxy(5,7);
	printf("----------------");
    FILE *fo;
    fo = fopen("stock.txt","ab+");
    SetColor(0);
    if(fo == NULL){
        MessageBox(0,"Error in Opening file\nMake sure your file is not write protected","Warning",0);

    } 
	else{
		int quantity,pricetemp,total;
        fflush(stdin);
        gotoxy(2,10);printf("ID: ");gets(st.ID);
        gotoxy(2,12);printf("Product Name: ");gets(st.product);
        gotoxy(2,14);printf("Quantity: ");scanf("%d",&quantity);
        gotoxy(2,16);printf("Price: ");scanf("%d",&pricetemp);
       	itoa(quantity,st.quan,10);
       	itoa(pricetemp,st.price,10);
        fwrite(&st, sizeof(st), 1, fo);
        SetColor(28);
        gotoxy(25,6); printf("The record is sucessfully added");
        
    }
    fclose(fo);
    char man;
    SetColor(0);
    gotoxy(2,18);printf("Are you want to add more? (Y/N)");
	scanf("%s",&man);
    if(man == 'Y' || man == 'y'){
    	clearWindow();
    	stock();
	}
	else{
		adminuser();
	}
}
void adminuser(){
	clearWindow();
	int choice;
    int x = 2;
    while(1){
    	gotoxy(5,6);
		printf("Select a option");
		gotoxy(5,7);
		printf("----------------");
        gotoxy(x,8);printf("1. Search a Record");
        gotoxy(x,10);printf("2. Modify a Record");
        gotoxy(x,12);printf("3. Delete a Record");
        gotoxy(x,14);printf("4. Update a Record");
        gotoxy(x,16);printf("5. Display all Record");
        gotoxy(x,18);printf("6. Add Store Stock");
        gotoxy(x,20);printf("7. Dislay Stock Record");
        SetColor(28);
        gotoxy(48,8);printf("8. Logout from Admin Panel");
        gotoxy(48,10);printf("9. Exit");
        SetColor(00);
        gotoxy(x,23);printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
		case 1:
		search();
		break;
		case 2:
		modify();
		break;
		case 3:
		del();
		break;
		case 4:
		modify();
		break;
		case 5:
		display();
		break;
		case 6:
		stock();
		break;
		case 7:
		out();
		break;
		case 8:
		clearWindow();
		user();
		break;
		case 9:
		clearWindow();
		exit(0);
		default:
			gotoxy(2,5);
			SetColor(28);
			printf("Invalid Input ! Enter your choice from 1 to 9 only....... Restart the Application");
			user();
    }
}
}
void user(){
	clearWindow();
	int tempuser;
	SetColor(00);
	gotoxy(18,8);
	printf("Select User Type");
	gotoxy(18,9);
	printf("----------------");
	gotoxy(18,11);
    printf("1. Admin");
    gotoxy(35,11);
    printf("2. Store Employee");
    gotoxy(18,15);
    printf("Enter the number to select the user : ");
    scanf("%d",&tempuser);
    switch(tempuser){
	case 2:
	employee();
	break;
	case 1:
    		int password = 9205;
    		int password2;
    		clearWindow();
    		gotoxy(18,8);
			printf("Enter the 4 digit Numeric Pin for Admin Login");
			gotoxy(28,12);
			printf("Your Passkey : ");
			scanf("%d",&password2);
			if(password == password2){
				adminuser();
			}
			else {
				clearWindow();
				gotoxy(28,6);
				SetColor(28);
				printf("Incorrect Pin !");
				user();}
		break;
	}
}

void window(){
    gotoxy(23,2);
    SetColor(35);
    printf("Departmental Store Management System");
    gotoxy(18,3);
    printf("Air Force vocational college, New Delhi, India");
    gotoxy(18,4);
    printf("==============================================");
	user();
}
int main(){
	ClearConsoleToColors(17,15);
	SetConsoleTitle("Departmental Store Record System > > > By - Shweta Gupta");
    window();
    return 0;
}
