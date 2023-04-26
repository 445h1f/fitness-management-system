#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


#define MAX 50
#define insert_num 1
#define del_num -1


void display_record();
void delete_record();
void insert_record();
void search_record();
void pack_details();
void print_slot();
void display_stats();
int check_slot(int);
void update(int, int);

typedef struct customer
{
    int registration_number;
    char name[50];
    float bmi;
    int package;
    long double phone_number;
    char city[50];
    int slot;
} customer;


typedef struct slot
{
    int slot_1;
    int slot_2;
    int slot_3;
    int slot_4;
} slot;



slot s, p;

customer c;
int i;
FILE *fp, *fs;



int main()
{
    fp = fopen("slot_timings.txt", "r");
    if(fp==NULL)
    {
        fs = fopen("slot_timings.txt", "wb");
        p.slot_1 = 0;
        p.slot_2 = 0;
        p.slot_2 = 0;
        p.slot_2 = 0;
        fwrite(&p, sizeof(slot), 1, fs);
    }
    fclose(fp);
    fclose(fs);
    int choice;
    while (1)
    {
        // getch();
        system("cls");
        printf("\n");
        printf("\t\t\t");
        for (i = 0; i < 70; i++)
            printf("*");
        printf("\n");
        printf("\t\t\t\t\t\tFITNESS MANAGEMENT\n");
        printf("\t\t\t");
        for (i = 0; i < 70; i++)
            printf("*");
        printf("\nSelect any of the following: \n");
        printf("1.Register\n");
        printf("2.Delete Record\n");
        printf("3.Search Record\n");
        printf("4.Display Records\n");
        printf("5.Stats\n");
        printf("6.Exit\n\n");
        printf(">>> Select Your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            insert_record();
            break;
        case 2:
            delete_record();
            break;
        case 3:
            search_record();
            break;
        case 4:
            display_record();
            break;
        case 5:
            display_stats();
            break;
        case 6:
            exit(0);
        default:
            printf("\t\t\t\t.........Select a valid option...........");
            getch();
        }
    }
}

void insert_record()
{
    FILE *fp, *fs;
    char temp_city[20];
    int resume = 1;
    int temp_package, choice;

    int temp_registration_number;
    fs = fopen("slot_timings.txt", "ab+");
    fread(&s, sizeof(slot), 1, fs);
    if ((s.slot_1 >= MAX) && (s.slot_2 >= MAX) && (s.slot_3 >= MAX) && (s.slot_4 >= MAX))
    {
        printf("\nAll Slots are filled");
        printf("\n\t\t No More Bookings!");
    }
    else
    {
        printf(">>> Enter customer registration number: ");
        scanf("%d", &temp_registration_number);
        fp = fopen("details.txt", "ab+");
        int flag = 0;
        while (fread(&c, sizeof(customer), 1, fp))
        {
            if (temp_registration_number == c.registration_number)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            c.registration_number = temp_registration_number;
            char name[50];
            printf(">>> Enter customer name: ");
            scanf(" %[^\n]s", name);
            strcpy(c.name, name);

            printf(">>> Enter customer Phone number: ");
            scanf("%lf", &c.phone_number);

            printf(">>> Enter your BMI: ");
            scanf("%f", &c.bmi);

            char city[50];
            printf(">>> Enter City: ");
            scanf(" %[^\n]s", city);
            strcpy(c.city, city);

            pack_details();
            while (1)
            {
                printf("\n>>> Select Package: ");
                scanf("%d", &temp_package);

                if (temp_package == 1 || temp_package == 2)
                {
                    printf("\n\t\t\t\t.........Package selected..........");
                    break;

                } else{
                    printf("\n\t\t\t\t.......select a valid package..........\n\n");
                }

            }
            c.package = temp_package;
            while (1)
            {
                print_slot();
                printf("\n>>> Select slot: ");
                scanf("%d", &choice);
                if (choice == 1 || choice == 2 || choice == 3 || choice == 4)

                {
                    if (check_slot(choice) == 0)
                    {
                        printf("\n\t\t\t\t.......Slots are Full.........");
                        printf("\n\n>>> Press \"1\" to book another slot / select any other number to discard registration: ");
                        scanf("%d", &resume);
                        if (resume != 1)
                            break;
                    }
                    else
                    {
                        printf("\t\t\t\t.........Slots are available...........");
                        break;
                    }
                }
                else
                {
                    printf("\t\t\t\t.........Select a valid slot............. ");
                }
            }
            if (resume == 1)
            {
                c.slot = choice;
                printf("\n\t\t\t\t........You are registerd succesfully...........");
                update(choice, insert_num);
                fwrite(&c, sizeof(customer), 1, fp);
                getch();
            }
        }
        else
        {
            printf("\n\tCustomer already registered with this registration id");
            printf("\n\n \t\t \t\t.........Press Any Key to Continue.........");
            getch();
        }
    }
    fclose(fp);
}


void delete_record()
{
    FILE *fp, *fs;
    int temp_registration_number;
    int flag = 0;
    int temp_slot;
    fp = fopen("details.txt", "rb");
    fs = fopen("new_details.txt", "wb");
    printf("\n>>> Enter registration number : ");
    scanf("%d", &temp_registration_number);
    while (fread(&c, sizeof(customer), 1, fp))
    {
        if (c.registration_number != temp_registration_number)
        {
            fwrite(&c, sizeof(customer), 1, fs);
        }
        else
        {
            flag = 1;
        }
    }
    fclose(fp);
    fclose(fs);
    if (flag == 0)
        printf("\n\t\t\t.........Record not found..............");
    else
    {
        printf("\n\t\t\t........Record deleted succesfully...........");
        update(c.slot, del_num);
        remove("details.txt");
        rename("new_details.txt", "details.txt");
        printf("\n New records are: \n");
        display_record();
    }
    getch();
}


void search_record()
{
    FILE *fp, *fs;
    int flag = 0;
    int temp_registration;
    fp = fopen("details.txt", "rb");
    printf("\n>>> Enter Registration Number: ");
    scanf("%d", &temp_registration);
    while (fread(&c, sizeof(customer), 1, fp))
    {
        if (temp_registration == c.registration_number)
        {
            printf("\n \t\t\t......Search record found.......\n\n");
            printf("\n \t Registration Number: %d", c.registration_number);
            printf("\n \t\t\t Name: %s", c.name);
            printf("\n \t\t Phone Number: %0.Lf", c.phone_number);
            printf("\n\t\t\t City: %s", c.city);
            printf("\n\t\t Slot Timings: ");
            if (c.slot == 1)
                printf("06AM-07AM");
            else if (c.slot == 2)
                printf("07AM-08AM");
            else if (c.slot == 3)
                printf("04PM-05PM");
            else if (c.slot == 4)
                printf("05PM-06PM");
            flag = 1;
            printf("\n\t\t      Package: %d", c.package);
            getch();
        }
    }
    fclose(fp);
    if (flag == 0)
    {
        printf("\n \t\t\t.........No Record found...............");
        getch();
    }


}
void display_record()
{
    FILE *fp, *fs;
    fp = fopen("details.txt", "rb");
    fs = fopen("slot_timings.txt", "rb");
    fread(&s, sizeof(slot), 1, fs);
    if (s.slot_1 == 0 && s.slot_2 == 0 && s.slot_3 == 0 && s.slot_4 == 0)
    {
        printf("\n\t\t\t\t......No Records to Display..........");
    }
    else{
        for (int i=0; i<120; i++){
            printf("_");
        }
        printf("\n");
        printf("\nNumber \t\t    Name \t\tPhone Number \t\t   City \t\t\t    Slot\n");

        while (fread(&c, sizeof(customer), 1, fp))
        {
            // printf("\n%d \t\t %s \t\t %0.Lf \t\t %s \t\t %d", c.registration_number, c.name, c.phone_number, c.city, c.package);
            for (int i=0; i<120; i++){
                printf("_");
            }
            printf("\n");
            printf("\n%d", c.registration_number);
            printf("\t\t%s", c.name);
            printf("\t\t%0.lf", c.phone_number);
            printf("\t\t%s\t\t", c.city);
            if(c.slot==1)
                printf("\t06AM-07AM\n");
            else if(c.slot==2)
                printf("\t07AM-08AM\n");
            else if (c.slot == 3)
                printf("\t04PM-05PM\n");
            else if (c.slot == 4)
                printf("\t05PM-06PM\n");
        }
        for (int i=0; i<120; i++){
            printf("_");
        }
    }
    fclose(fp);
    fclose(fs);
    getch();
}


void display_stats()
{
    FILE *fp, *fs;
    fp = fopen("details.txt", "rb");
    fs = fopen("slot_timings.txt", "rb");
    fread(&s, sizeof(slot), 1, fs);
    if (s.slot_1 == 0 && s.slot_2 == 0 && s.slot_3 == 0 && s.slot_4 == 0)
    {
        printf("\n\t\t\t\t..........No Stats Found..........");
    }
    else{
        printf("\n\t\t\t\t\t\t..........Stats..........\n");
        for (int i=0; i<120; i++){
            printf("_");
        }
        long sales = 0;
        int customers = 0;
        int packageSales[] = {0, 0};
        while (fread(&c, sizeof(customer), 1, fp))
        {
            customers++;
            int package = c.package;
            if (package == 1){
                sales += 400;
                packageSales[0]++;
            } else if (package == 2){
                sales += 1000;
                packageSales[1]++;
            }
        }
        printf("Number of Customers: %d\n", customers);
        printf("Total Sales: %ld INR\n", sales);
        for (int i=0; i<2; i++){
            printf("Package %d Sold: %d\n", i+1, packageSales[i]);
        }
        printf("Slot 1 Booking [06AM-07AM]: %d\n", s.slot_1);
        printf("Slot 2 Booking [07AM-08AM]: %d\n", s.slot_2);
        printf("Slot 3 Booking [04PM-05PM]: %d\n", s.slot_3);
        printf("Slot 4 Booking [05PM-06PM]: %d\n", s.slot_4);
        printf("Slots Remaining: %d\n", MAX-customers);
        for (int i=0; i<120; i++){
            printf("_");
        }
    }
    fclose(fp);
    fclose(fs);

    getch();
}

void pack_details()
{
    printf("\n\n");
    printf("\t\t");
    for (i = 0; i < 70; i++)
        printf("*");
    printf("\n\n");
    printf("\t\t\tPackage: 1\t\t\t Package: 2\n");
    printf("\t\t\tTime: 1 month \t\t\t Time: 3 months\n");
    printf("\t\t\tCost: 400 \t\t\t Cost: 1000\n");
    printf("\t\t\tTrainer Name: Mahesh \t\t Trainer Name: Anil");

    printf("\n\n");
    printf("\t\t");
    for (i = 0; i < 70; i++)
        printf("*");
    printf("\n\n");
}


void print_slot()
{

    printf("\n\n");
    printf("\n Slot 1:\t\tTimings: 06AM-07AM");
    printf("\n Slot 2:\t\tTimings: 07AM-08AM");
    printf("\n Slot 3:\t\tTimings: 04PM-05PM");
    printf("\n Slot 4:\t\tTimings: 05PM-06PM");
    printf("\n\n");
}


int check_slot(int sl)
{
    FILE *fp, *fs;
    fp = fopen("slot_timings.txt", "rb");
    fread(&s, sizeof(slot), 1, fp);
    if (sl == 1)
    {

        if (s.slot_1 < MAX)
            return 1;
        return 0;
    }
    else if (sl == 2)
    {
        if (s.slot_2 < MAX)
            return 1;
        return 0;
    }
    else if (sl == 3)
    {
        if (s.slot_3 < MAX)
            return 1;
        return 0;
    }
    else if (sl == 4)
    {
        if (s.slot_4 < MAX)
            return 1;
        return 0;
    }
    fclose(fp);
}


void update(int choice, int update_num)
{
    slot p;
    FILE *fp, *fs;
    fp = fopen("slot_timings.txt", "rb");

    fread(&s, sizeof(slot), 1, fp);
    fclose(fp);
    fp = fopen("slot_timings.txt", "wb");

    if (choice == 1)
    {
        p.slot_1 = s.slot_1 + update_num;
        p.slot_2 = s.slot_2;
        p.slot_3 = s.slot_3;
        p.slot_4 = s.slot_4;
    }
    else if (choice == 2)
    {
        p.slot_1 = s.slot_1;
        p.slot_2 = s.slot_2 + update_num;
        p.slot_3 = s.slot_3;
        p.slot_4 = s.slot_4;
    }
    if (choice == 3)
    {
        p.slot_1 = s.slot_1;
        p.slot_2 = s.slot_2;
        p.slot_3 = s.slot_3 + update_num;
        p.slot_4 = s.slot_4;
    }
    if (choice == 4)
    {
        p.slot_1 = s.slot_1;
        p.slot_2 = s.slot_2;
        p.slot_3 = s.slot_3;
        p.slot_4 = s.slot_4 + update_num;
    }
    fwrite(&p, sizeof(slot), 1, fp);
    fclose(fp);
    // remove("slot_timings.txt");
    fp = fopen("slot_timings.txt", "rb");
    // while (fread(&s, sizeof(slot), 1, fp))
    // {
    // printf("\n%d %d %d %d", s.slot_1, s.slot_2, s.slot_3, s.slot_4);
    // }
    fclose(fp);
}
