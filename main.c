#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>

void title();
void main_menu();
void room_list();
void monthly_rent_update();
void room_edit();
void room_add();
void room_delete();
void usr_login();
void usrlog();
void admin_panel();
char current_user[10]="";


struct renter
{
    int no;
    int room_no;
    int level;
    char name[10];
    char status[4];
    int rent;

} ren;

int main()
{
    title();
    usr_login();
}



void title()
{
    printf("\n\t==========================\n");
    printf("\t  HOME MANAGEMENT SYSTEM\n");
    printf("\t==========================\n");
    printf("\t\t\t Created by RAIYAN CHOUDHURY        CURRENT-USER: %s\n",current_user);
}


void main_menu()
{

    title();
    printf("\t...Main Menu...\n");
    printf("01. List of Rooms.\n");
    printf("02. Monthly Rent update.\n");
    printf("03. Renter Details.\n");
    printf("04. Renters Due month.\n");
    printf("08. logout.\n");
    printf("00. Exit.\n\n");
    printf("Select Option (0-5) : ");
    int opt1;
    scanf("%d",&opt1);
    switch(opt1)
    {
    case 1:
        room_list();
        int op_rl;
        printf("\n\n 1.Edit.\n 2.Add.\n 3.Delete.\n 0.Return.\n");
        printf("Select Option : ");
        scanf("%d",&op_rl);
        switch(op_rl)
        {
        case 1:
            room_edit();
            break;
        case 2:
            room_add();
            break;
        case 3:
            room_delete();
            break;

        case 0:
            system("cls");
            main_menu();
        default:
            system("cls");
            room_list();
        }


        system("cls");
        main();
        break;
    case 2:
        monthly_rent_update();
        break;
    case 8:
            system("cls");
            strcpy(current_user,"LOGIN REQURED");
            printf("\n***LOGGED OUT SUCCESSFULLY \n ");
            main();
            break;
    case 0:
        exit(0);
    default:
        system("cls");
        printf("\n***Enter Correct Option !!!\n\n\n");
        main();
    }
}


void room_list()
{
    FILE* fptr;
    fptr=fopen("roomlist.csv","r");
    if (fptr==0)
    {
        system("cls");
        printf("\n***File Not Found!\n");

        main();
    }
    else
    {

        char buffer;
        system("cls");
        title();
        printf("\n\t\t...ROOM LIST...\n");
        printf("\n NO  ||LEVEL||ROOM NO||     NAME     ||Avail|| RENT \n");
        printf("----------------------------------------------------\n");
        while(fscanf(fptr,"%d,%d,%d,%[^,],%[^,],%d",&ren.no,&ren.level,&ren.room_no,ren.name,ren.status,&ren.rent)==6)
        {


            printf(" %-3d || %-4d|| %-6d|| %-12s || %-4s|| %d\n",ren.no,ren.level,ren.room_no,ren.name,ren.status,ren.rent);

        };


        fclose(fptr);


    }

}

void monthly_rent_update()
{

    room_list();
    FILE*ft;
    FILE*fptr;
    ft=fopen("monthlyrent.csv","a");
    fptr=fopen("roomlist.csv","r");

    int op;
    int amount;
    printf("Enter number :");
    scanf("%d",&op);
    printf("Enter Amount: ");
    scanf("%d",&amount);
    char line[200];


    while(fgets(line,sizeof(line),fptr))
    {

        if (sscanf(line,"%d,%d,%d,%[^,],%[^,],%d",
                   &ren.no,&ren.level,&ren.room_no,ren.name,ren.status,&ren.rent)==6)
        {
            if (ren.no == op)
            {

                fprintf(ft,"%d,%s,%d\n",ren.room_no,ren.name,amount);
                break;
            }
        }
    }
    fclose(ft);
    fclose(fptr);
    system("cls");
    printf("***Monthly Rent Updated Successfully...\n");
    main();
}

void room_edit()
{
    FILE *fptr, *fp;
    char line1[200];
    int op, amount;
    char avail_new[4];
    char new_name[10];

    printf("Enter renter number to edit: ");
    scanf("%d", &op);

    printf("Enter Room NAME to edit: ");
    scanf("%s", &new_name);


    printf("Enter Room Status to edit: ");
    scanf("%s", &avail_new);

    printf("Enter new rent amount: ");
    scanf("%d", &amount);

    fptr = fopen("roomlist.csv", "r");
    fp = fopen("temp.csv", "w");

    if (fptr == NULL || fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    while (fgets(line1, sizeof(line1), fptr))
    {
        if (sscanf(line1, "%d,%d,%d,%[^,],%[^,],%d",
                   &ren.no, &ren.level, &ren.room_no,
                   ren.name, ren.status, &ren.rent) == 6)
        {
//THIS PROGRAM IS MADE BY RAIYAN CHOUDHURY AND COPYRIGHT 2025
            if (ren.no == op)
            {
                fprintf(fp, "%d,%d,%d,%s,%s,%d\n",
                        ren.no, ren.level, ren.room_no,
                        strupr(new_name), strupr(avail_new), amount);
            }
            else
            {
                fputs(line1, fp);
            }
        }
    }

    fclose(fptr);
    fclose(fp);

    remove("roomlist.csv");
    rename("temp.csv", "roomlist.csv");
    system("cls");
    printf("Record updated successfully.\n");
    main_menu();
}


void usr_login()
{
    char user[13];
    char pw[8];
    char buff[100];
//THIS PROGRAM IS MADE BY RAIYAN CHOUDHURY AND COPYRIGHT 2025
    struct usr
    {
        char usrn[13];
        char pass[8];
    } logn;

    FILE *lo_s = fopen("login.txt", "r");
    if (lo_s == NULL)
    {
        fopen("login.txt","a");
        printf("No user database found!Program has created login.txt. \nRe-enter into program.\n");
        return;
    }

    printf("Enter Username: ");
    scanf("%12s", user);
    printf("Enter Password: ");

    int i = 0;
    char ch;
    while (1)
    {
        ch = _getch();  // read without printing
        if (ch == 13)   // Enter key
        {
            pw[i] = '\0';
            break;
        }
        else if (ch == 8 && i > 0)     // Backspace
        {
            i--;
            printf("\b \b");
        }
        else if (i < 7 && ch != 8)
        {
            pw[i++] = ch;
            printf("*");
        }
    }
    printf("\n");


//THIS PROGRAM IS MADE BY RAIYAN CHOUDHURY AND COPYRIGHT 2025
// Admin user=admin and password=admin42


    if (strcmp(user, "admin") == 0 && strcmp(pw, "admin42") == 0)
    {
        fclose(lo_s);
        system("cls");
        strcpy(current_user,"ADMIN");
        title();
        printf("\n\n...Welcome, ADMIN...\n");
        admin_panel();
        return;
    }

    int found = 0;
    while (fgets(buff, sizeof(buff), lo_s))
    {
        if (sscanf(buff, "%12[^|]|%7s", logn.usrn, logn.pass) == 2)
        {
            if (strcmp(logn.usrn, user) == 0)
            {
                found = 1;
                if (strcmp(logn.pass, pw) == 0)
                {
                    fclose(lo_s);
                    system("cls");
                    strcpy(current_user, strupr(user));
                    printf("\n\n\tLogin successful! Welcome, %s\n\n", current_user);
                    main_menu();
                    return;
                }
                else
                {
                    fclose(lo_s);
                    system("cls");
                    printf("\n*** X Wrong password! X ***\n");
                    main();
                    return;
                }
            }
        }
    }

    fclose(lo_s);
    if (!found){
        system("cls");
        printf("\n***Username not found!***\n");
//THIS PROGRAM IS MADE BY RAIYAN CHOUDHURY AND COPYRIGHT 2025
        main();}
}


void room_add()
{

    char buff[200];
    int count=0;

    FILE*fptr;
    fptr=fopen("roomlist.csv","r");
    if (fptr !=NULL)
    {
        while(fgets(buff,sizeof(buff),fptr))
        {
            if (sscanf(buff,"%d,%d,%d,%[^,],%[^,],%d",&ren.no,&ren.level,&ren.room_no,ren.name,ren.status,&ren.rent)==6)
            {
                count=count+1;
            }

        }

        fclose(fptr);
    }
//THIS PROGRAM IS MADE BY RAIYAN CHOUDHURY AND COPYRIGHT 2025
    fptr=fopen("roomlist.csv","a+");
    ren.no=count+1;
    printf("\t...Add Room...\n");
    printf("Floor No: ");
    scanf("%d",&ren.level);
    printf("Room No: ");
    scanf("%d",&ren.room_no);
    printf("Room Name: ");
    scanf(" %s",ren.name);
    printf("Available Status: ");
    scanf(" %s",&ren.status);
    printf("Rent Amount(Bdt): ");
    scanf(" %d",&ren.rent);

    fprintf(fptr,"%d,%d,%d,%s,%s,%d\n",ren.no,ren.level,ren.room_no,strupr(ren.name),strupr(ren.status),ren.rent);

    fclose(fptr);
    system("cls");
    printf("*Room added Successfully!!!\n");
    main_menu();

}



void room_delete()
{
    char line[100];
    int op;
    printf("Enter Serial No to Delete Room: ");
    scanf("%d",&op);
//THIS PROGRAM IS MADE BY RAIYAN CHOUDHURY AND COPYRIGHT 2025

    FILE*fptr,*fr;
    fptr=fopen("roomlist.csv","r");
    fr=fopen("temp.csv","w");
    while(fgets(line,sizeof(line),fptr))
    {
        if (sscanf(line,"%d,%d,%d,%[^,],%[^,],%d",&ren.no,&ren.level,&ren.room_no,ren.name,ren.status,&ren.rent)==6)
        {
            if (op!=ren.no)
            {
                fprintf(fr,"%d,%d,%d,%s,%s,%d\n",ren.no,ren.level,ren.room_no,ren.name,ren.status,ren.rent);
            }

        }

    }

    fclose(fptr);
    fclose(fr);
    remove("roomlist.csv");
    rename("temp.csv","roomlist.csv");

    system("cls");
    printf("***Room Deleted Successfully");
    main_menu();


}


void usrlog()
{

    FILE *fptr;
    fptr=fopen("log.csv","a");
    char log[20];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char t_buffer[100];

    strftime(t_buffer, sizeof(t_buffer), "%d-%m-%Y||%H:%M:%S", t);

    fprintf(fptr,"%s,%s\n",current_user,t_buffer);


    fclose(fptr);
}


void admin_panel()
{
    int op;
    printf("\n\t...Admin Panel..");

    printf("\n\n 1.Create user.\n 2.Delete user.\n 3.View Login Logs\n 0.Return to Login Page \n");
    printf(" Select Option: ");
    scanf("%d",&op);

switch(op){

    case 1:
//THIS PROGRAM IS MADE BY RAIYAN CHOUDHURY AND COPYRIGHT 2025
        system("cls");
        strcmp(current_user,"ADMIN");
        title();
        struct usercheck{
            char usern[13];
            char upass[8];

        }user_data;


        FILE*fr,*fa;
        fr=fopen("login.txt","r");
        fa=fopen("login.txt","a");
        char newuser[13];
        char newpass[8];
        char line[100];
        int founduser=0;
        printf("\n...NEW USER Maker...\n");
        printf("Enter New USERNAME: ");
        scanf("%12s",&newuser);
        printf("Enter New PASSWORD: ");
        scanf("%s",&newpass);

        if (fr!= NULL){
        while(fgets(line,sizeof(line),fr)){
            if(sscanf(line,"%[^|]|%s",user_data.usern,user_data.upass)==2){
                if (strcmp(user_data.usern,newuser)==0){
                    printf("User Already Exists\n");
                    admin_panel();
                    founduser=1;
                    fclose(fr);
                    break;
                    }}} fclose(fr);
}
if (founduser==0){
        fprintf(fa,"\n%s|%s",newuser,newpass);
        fclose(fa);
        system("cls");
        title();
        printf("\n*User Created Successfully...\n");
        strcmp(current_user,"ADMIN");
        title();

        admin_panel();
        break;}



    case 2:

        FILE *fptr, *fn;
        fptr=fopen("login.txt","r");
        fn=fopen("logintemp.txt","w");

        char temp_user[13];
        char temp_pass[8];
        char del_user[13];
        while(fgets(line,sizeof(line),fptr))
        {
            if(sscanf(line,"%[^|]|%s",temp_user,temp_pass)==2)
            {
                printf("%-10s || %s\n",temp_user,temp_pass);
            }
        }

        printf("\nEnter username to Delete: ");
        scanf("%12s",del_user);
        rewind(fptr);
        while(fgets(line,sizeof(line),fptr))
        {
            if(sscanf(line,"%[^|]|%s",temp_user,temp_pass)==2)
            {
                if(strcmp(temp_user,del_user)!=0)
                {
                    fprintf(fn,"%s|%s\n",temp_user,temp_pass);
                }

            }
        }
        fclose(fn);
        fclose(fptr);

        remove("login.txt");
        remove("login.txt");
        rename("logintemp.txt","login.txt");
        admin_panel();
        break;
    case 0:
        system("cls");
        strcpy(current_user,"LOGIN REQURED");
        main();
        break;
//THIS PROGRAM IS MADE BY RAIYAN CHOUDHURY AND COPYRIGHT 2025

    default:
        system("cls");
        printf("Select Correct Option!!!\n\n");
        main();

}}

//THIS PROGRAM IS MADE BY RAIYAN CHOUDHURY AND COPYRIGHT 2025
