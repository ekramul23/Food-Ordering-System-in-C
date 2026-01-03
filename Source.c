#include <stdio.h>
#include <string.h>
#include <conio.h>

#define MAX_ITEMS 20
#define MAX_ORDERS 50

typedef struct
{
    char name[50];
    float price;
} MenuItem;

// Structure for order
typedef struct
{
    MenuItem items[MAX_ITEMS];
    int quantities[MAX_ITEMS];
    float totalBill;

    char first_name[100];
    char last_name[100];
} Order;

// Global variables
MenuItem menu[MAX_ITEMS];

int itemCount = 4;

Order cart={0};
Order orderHistory[MAX_ORDERS]={0};
int orderCount = 0;

// Function prototypes
void displayMenu();
void addItem();
void deleteItem();
void replaceItem();
void addToCart();
float calculateTotalBill();
void displayOrderConfirmation();
void displayOrderHistory();

int main()
{
    strcpy(menu[0].name, "Burger");
    menu[0].price = 50.00;

    strcpy(menu[1].name, "Pizza");
    menu[1].price = 60.00;

    strcpy(menu[2].name, "Coffee");
    menu[2].price = 15.00;

    strcpy(menu[3].name, "Soup");
    menu[3].price = 65.00;
    // Order process loop
    int choice;
    do
    {
        system("cls");
        printf("\t==================================================\n");
        printf("\t\t Welcome to Food Ordering System\n");
        printf("\t==================================================\n\n");
        printf("\t\t1. Browse Menu\n");
        printf("\t\t2. Add item to  Menu\n");
        printf("\t\t3. Delete Item from Menu\n");
        printf("\t\t4. Replace Item in Menu\n");
        printf("\t__________________________________________________\n\n");
        printf("\t\t5. Add Items to Cart\n");
        printf("\t\t6. Checkout\n");
        printf("\t__________________________________________________\n\n");
        printf("\t\t7. Order History\n");
        printf("\t\t8. Exit\n");
        printf("\t__________________________________________________\n\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayMenu();
            break;
        case 2:

            addItem();
            break;
        case 3:
            deleteItem();
            break;
        case 4:
            replaceItem();
            break;
        case 5:
            addToCart();
            break;
        case 6:
            cart.totalBill = calculateTotalBill();
            displayOrderConfirmation();
            // Save order to history
            orderHistory[orderCount++] = cart;
            // Reset cart after order
            memset(&cart, 0, sizeof(cart));
            break;
        case 7:
            displayOrderHistory();
            break;
        case 8:
            system("cls");
            printf("Exiting food ordering system.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    while (choice != 8);

    return 0;
}
void displayMenu()
{
    system("cls");

    printf("\t\t=======================\n");
    printf("\t\t\t MENU\n");
    printf("\t\t=======================\n\n");

    printf("\tSerial no:\tIteam\t\tPrice\n\n");


    for (int i = 0; i < itemCount; ++i)
    {
        printf("\t  %d.\t\t%s\t\t%.2f//=\n", i + 1, menu[i].name, menu[i].price);
    }
    printf("\nPress any key to return--> ");
    getch();
}

void addItem()
{
    system("cls");
    int choice;
    do
    {
        if (itemCount == MAX_ITEMS)
        {
            printf("Menu is full!\n");
            printf("Press any key to return--> ");
            getch();
            return;
        }
        printf("Enter item name : ");
        scanf("%s", menu[itemCount].name);
        printf("Enter item price: ");
        scanf("%f", &menu[itemCount].price);
        itemCount++;

        printf("\nDo you want to add another item? (1 for Yes, 0 for No): ");
        scanf("%d", &choice);

    }
    while (choice == 1);
}

void deleteItem()
{
    system("cls");
    int itemToDelete;
    printf("Enter item number to delete: ");
    scanf("%d", &itemToDelete);

    if (itemToDelete >= 1 && itemToDelete <= itemCount)
    {
        // Shift the items in the array to remove the deleted item
        for (int i = itemToDelete - 1; i < itemCount - 1; ++i)
        {
            menu[i] = menu[i + 1];
        }
        itemCount--;
        printf("Item deleted successfully.\n");

    }
    else
    {
        printf("Invalid item number. Please try again.\n");
    }
    printf("Press any key to return--> ");
    getch();

}

void replaceItem()
{
    system("cls");
    int itemToReplace;
    printf("Enter item number to replace: ");
    scanf("%d", &itemToReplace);

    if (itemToReplace >= 1 && itemToReplace <= itemCount)
    {
        printf("Enter new item name: ");
        scanf("%s", menu[itemToReplace - 1].name);
        printf("Enter new item price: ");
        scanf("%f", &menu[itemToReplace - 1].price);
        printf("Item replaced successfully.\n");
    }
    else
    {
        printf("Invalid item number. Please try again.\n");
    }
    printf("\n\nPress any key to return--> ");
    getch();
}

void addToCart()
{
    system("cls");
    int item, quantity;
    int validItem;
    int choice;
    do
    {
        do
        {
            validItem = 0;
            printf("Enter item number to add to cart: ");
            scanf("%d", &item);

            if (item >= 1 && item <= itemCount)
            {
                validItem = 1;
            }
            else
            {
                printf("Invalid item number. Please try again.\n");

            }
        }
        while (!validItem);

        printf("Enter quantity: ");
        scanf("%d", &quantity);

        cart.items[item - 1]= menu[item - 1];
        cart.quantities[item - 1] += quantity;

        printf("Added %d %s to your cart.\n", quantity, menu[item - 1].name);

        // Update the total bill as items are added
        cart.totalBill += menu[item - 1].price * quantity;

        printf("\nDo you want to add another item? (1 for Yes, 0 for No): ");
        scanf("%d", &choice);

    }
    while(choice==1);

}
float calculateTotalBill()
{
    float totalBill = 0.0;
    for (int i = 0; i < itemCount; ++i)
    {
        totalBill += cart.items[i].price * cart.quantities[i];
    }

    return totalBill;
}

void displayOrderConfirmation()
{
    system("cls");

    printf("\n\n");
    printf("\t==========================================\n");
    printf("\t\t   Order Confirmation\n");
    printf("\t==========================================\n");

    printf("\tTotal bill is: %.2f\n\n", cart.totalBill);
    printf("\n\n\n");
    printf("\t===============================\n");
    printf("\t   Thank you for your order!\n");
    printf("\t===============================\n");
    printf("\n\nPress any key to return--> ");
    getch();
}


void displayOrderHistory()
{
    system("cls");
    if (orderCount == 0)
    {
        printf("No orders in history!\n");
        printf("\n\nPress any key to return--> ");
        getch();
        return;
    }

    printf("\n===== Order History =====\n\n");
    for (int i = 0; i < orderCount; ++i)
    {
        printf("Order %d:\n", i + 1);
        for (int j = 0; j < MAX_ITEMS; ++j)
        {
            if (orderHistory[i].quantities[j] > 0)
            {
                printf("%s - %.2f x %d\n", orderHistory[i].items[j].name,
                       orderHistory[i].items[j].price, orderHistory[i].quantities[j]);
            }
        }
        printf("Total Bill: %.2f\n", orderHistory[i].totalBill);
        printf("------------------------------\n");
    }
    printf("\n\nPress any key to return--> ");
    getch();
}
