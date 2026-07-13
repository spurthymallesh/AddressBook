#include <stdio.h>
#include "contact.h"
//colours//
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define MAGENTA "\033[1;35m"


/* Structure declaration */

int main()
{
    /* Variable and structre defintion */
    int option;
    AddressBook addressbook;
    addressbook.contact_count = 0;
    load_contacts(&addressbook);

    printf(CYAN "\n=================================\n" RESET);
    printf(CYAN "      ADDRESS BOOK SYSTEM\n" RESET);
    printf(CYAN "=================================\n" RESET);
    while (1)
    {
        printf(YELLOW"\nAddress book menu\n"RESET); /* Give a prompt message for a user */
        printf(YELLOW "1.Add contact\n2.search contact\n3.Edit contact\n4.Delete contact\n5.Display contact\n6.Save contact\n7.Exit\n"RESET);
        printf("Enter the option : ");
        scanf("%d", &option);

        switch (option) /* Based on choosed option */
        {
        case 1:
        {
            char choice;

            do
            {
                create_contact(&addressbook);

                printf(YELLOW"Do you want to add another contact? (y/n): "RESET);
                scanf(" %c", &choice);

            } while (choice == 'y' || choice == 'Y');

                break;
        }

        case 2:
        {
            //printf("Search Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4. Exit\nEnter the option : "); /* Providing menu */
            search_contacts(&addressbook);
            break;
        }
        case 3:
            //printf("Edit Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */

            edit_contact(&addressbook);
            break;

        case 4:
        {
            //printf("Delete Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */

            delete_contact(&addressbook);
            break;
        }
        case 5:
        {
            printf("List Contacts:");
            list_contacts(&addressbook);
            break;
        }

        case 6:
        {
            if (save_contacts(&addressbook) == Success)
            printf(GREEN "Contacts saved successfully!\n" RESET);
            else
            printf(RED "Error saving contacts!\n" RESET);
            break;
        }

        case 7:
        {
            if (save_contacts(&addressbook) == Success)
            printf(GREEN "Contacts saved successfully and Exiting\n" RESET);
            else
            printf(RED "Error saving contacts!\n" RESET);

            return 0;
        }

        default:
            printf(RED"Invalid option \n"RESET);
            break;
        }
    }
    return 0;
}
