#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// For items
struct items
{
    char item_one[50];
    float price;
    int quantity;
};
//For order details
struct orders
{
    char customer[50];
    char date[40];
    int itemNum;
    struct items item[50];
};
// This is for showing the bill details
void showBillDetails(char name[100], char date[50])
{
    printf("\n\n");
    printf("\t\t Restaurant X.");
    printf("\n\t    -----------------------");
    printf("\nDate: %s", date);
    printf("\nInvoice for : %s", name);
    printf("\n");
    printf("------------------------------------------------\n");
    printf("Items \t\t");
    printf("Qantity\t\t");
    printf("Total\t\t");
    printf("\n------------------------------------------------\n");
    printf("\n\n");
}
// Bill Body
void showBillBody(char item[50], int quantity, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", quantity);
    printf("%.2f\t\t", quantity * price);
    printf("\n");
}
//End body of the bill
void endBillDetails(float total)
{
    printf("\n");
    float discount = 0.1 * total;
    float netTotal = total - discount;
    printf("Sub Total = \t\t\t%.2f", total);
    printf("\nDiscount 10%s\t\t\t%.2f", "%", discount);
    printf("\n\t\t\t\t----------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
}
int main()
{

    int option, numberOfItems;
    float total, total_2 = 0;
    char saveBill = 'y', continue_again = 'y';
    FILE *file;
    char name[50];
    struct orders order;
    struct orders order_b;
    //This is Dashboard
    while (continue_again == 'y')
    {
        float total = 0;
        int invoceFound = 0;
//        printf("\t============  Resturant X. =============");
        printf("\n");
        printf(" __   __  __  ___              __               ___        \\.\\  /./\n");
        printf("|  | |   |     |   /\\   |   | |  |   /\\   |\\  |  |          \\ \\/ /\n");
        printf("|__| |-- |--|  |  /__\\  |   | |__|  /__\\  | \\ |  |          / /\\ \\\n");
        printf("|  \\ |__  __|  | /    \\ |___| |  \\ /    \\ |  \\|  |         /./  \\.\\\n\n\n");

        printf("Select Your prefered operation : ");

        printf("\n1. Generate Invoices");
        printf("\n2. Show all invoices");
        printf("\n3. Search Invoices");
        printf("\n4. Exit\n\n");
        printf(" Choose : ");
        scanf("%d", &option);
        fgetc(stdin);
        switch (option)
        {
        // This is for option one
        case 1:
            system("cls");
            printf("\nPlease Enter the name of the customer : ");
            fgets(order.customer, 50, stdin);
            order.customer[strlen(order.customer) - 1] = 0;
            strcpy(order.date, __DATE__);
            printf("\nPlease Enter the number of items : ");
            scanf("%d", &numberOfItems);
            order.itemNum = numberOfItems;
            for (int i = 0; i < numberOfItems; i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the item %d name :\t ", i + 1);
                fgets(order.item[i].item_one, 50, stdin);
                order.item[i].item_one[strlen(order.item[i].item_one) - 1] = 0;
                printf("Please Enter the quantity : \t");
                scanf("%d", &order.item[i].quantity);
                printf("Please Enter the unit price : \t");
                scanf("%f", &order.item[i].price);
                total += order.item[i].quantity * order.item[i].price;
            }

            showBillDetails(order.customer, order.date);
            for (int i = 0; i < order.itemNum; i++)
            {
                showBillBody(order.item[i].item_one, order.item[i].quantity, order.item[i].price);
            }
            endBillDetails(total);
            printf("\nDo You want to save the invoice?y/n] :  \t");
            scanf("%s", &saveBill);
            if (saveBill == 'y')
            {
                file = fopen("RestaurantBill.dat", "a+");
                fwrite(&order, sizeof(struct orders), 1, file);
                if (&fwrite != 0)
                {
                    printf("\nSuccesfully Saved");
                }
                else
                {
                    printf("\nError in saving");
                }
                fclose(file);
            }

            break;
        // This is for option two
        case 2:
            system("clear");
            file = fopen("RestaurantBill.dat", "r");
            printf("\t-----------Your invoices are :-------------\n");
            while (fread(&order_b, sizeof(struct orders), 1, file))
            {
                showBillDetails(order_b.customer, order_b.date);
                for (int i = 0; i < order_b.itemNum; i++)
                {
                    showBillBody(order_b.item[i].item_one, order_b.item[i].quantity, order_b.item[i].price);
                    total_2 += order_b.item[i].quantity * order_b.item[i].price;
                }
                endBillDetails(total_2);
            }
            fclose(file);
            break;
        // This is for option three
        case 3:

            printf("\nEnter the name of the customer: \t");
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
            system("clear");
            file = fopen("RestaurantBill.dat", "r");
            printf("\t-----------Your invoice of %s-------------\n", name);
            while (fread(&order_b, sizeof(struct orders), 1, file))
            {
                if (!strcmp(order_b.customer, name))
                {

                    showBillDetails(order_b.customer, order_b.date);
                    for (int i = 0; i < order_b.itemNum; i++)
                    {
                        showBillBody(order_b.item[i].item_one, order_b.item[i].quantity, order_b.item[i].price);
                        total_2 += order_b.item[i].quantity * order_b.item[i].price;
                    }
                    endBillDetails(total_2);
                    invoceFound = 1;
                }
            }
            if (!invoceFound)
            {
                printf("\nSorry customer %s is not here", name);
            }
            fclose(file);
            break;
        case 4:
            printf("\t\t Bye ");
            exit(0);
            break;
        default:
            printf("Invaild option");
            break;
        }
        printf("\nDo you want to check again?[y/n] : \t");
        scanf("%s", &continue_again);
    }
    printf("\t\t Bye ");
    printf("\n\n");

    return 0;
}
