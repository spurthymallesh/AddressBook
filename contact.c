#include <stdio.h>
#include "contact.h"
#include<ctype.h>
#include<string.h>
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define MAGENTA "\033[1;35m"

// Function Definitions
Status create_contact(AddressBook *addressbook)
{

    Contacts *new_contact = &addressbook->contact_details[addressbook->contact_count];

    do
    {
        printf(BLUE"Enter Name: "RESET);
        scanf(" %[^\n]", new_contact->Name);

    } while (is_valid_name(new_contact->Name) == Failure);


    do
    {
        printf(BLUE"Enter Mobile Number: "RESET);
        scanf("%s", new_contact->Mobile_number);
    } while (is_valid_phone(new_contact->Mobile_number, addressbook) == Failure);

    do
    {
        printf(BLUE"Enter Email: "RESET);
        scanf("%s", new_contact->Mail_ID);
    } while (is_valid_email(new_contact->Mail_ID, addressbook) == Failure);

    addressbook->contact_count++;

    printf(GREEN"Contact added successfully!\n"RESET);
    return Success;
}



void list_contacts(AddressBook *addressbook)
{
    if (addressbook->contact_count == 0)
    {
        printf(RED"No contacts available.\n"RESET);
        return;
    }

    printf(CYAN"\n----- Contact List -----\n"RESET);

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        printf(MAGENTA"Contact %d\n"RESET, i + 1);
        printf("Name   : %s\n", addressbook->contact_details[i].Name);
        printf("Mobile : %s\n", addressbook->contact_details[i].Mobile_number);
        printf("Email  : %s\n", addressbook->contact_details[i].Mail_ID);
    }

}

Status search_contacts(AddressBook *addressbook)
{
    int choice;
    char search[50];
    Status status;

    if (addressbook->contact_count == 0)
    {
        printf(RED"No contacts available.\n"RESET);
        return Failure;
    }

    while (1)
    {
        printf(YELLOW"\nSearch Contact menu:\n"RESET);
        printf(YELLOW"1.Name\n2.Mobile number\n3.Mail ID\n4.Exit\n"RESET);
        printf("Enter the option: ");

        scanf("%d", &choice);
        while (getchar() != '\n');   

        if (choice == 4)
            return Success;

        if (choice < 1 || choice > 4)
        {
            printf(RED"Invalid choice!\n"RESET);
            continue;
        }

        // Take input ONLY for selected option
        switch (choice)
        {
            case 1:
                do {
                    printf(BLUE"Enter the name: "RESET);
                    scanf(" %[^\n]", search);
                } while (is_valid_name(search) == Failure);
                break;

            case 2:
                do {
                    printf(BLUE"Enter the phone number: "RESET);
                    scanf("%s", search);
                } while (is_valid_phone_format(search) == Failure);
                break;

            case 3:
                do {
                    printf(BLUE"Enter the email: "RESET);
                    scanf("%s", search);
                } while (is_valid_email_format(search) == Failure);
                break;
        }

        // Search logic
        int found = 0;
        int count = 0;

        for (int i = 0; i < addressbook->contact_count; i++)
        {
            int match = 0;

            switch (choice)
            {
                case 1:
                    match = (strcmp(addressbook->contact_details[i].Name, search) == 0);
                    break;

                case 2:
                    match = (strcmp(addressbook->contact_details[i].Mobile_number, search) == 0);
                    break;

                case 3:
                    match = (strcmp(addressbook->contact_details[i].Mail_ID, search) == 0);
                    break;
            }

            if (match)
{
    if (!found)
    {
        printf(CYAN "\nMatching Contacts:\n" RESET);
    }

    printf(MAGENTA "\nContact %d\n" RESET, i + 1);
    printf("Name   : %s\n", addressbook->contact_details[i].Name);
    printf("Mobile : %s\n", addressbook->contact_details[i].Mobile_number);
    printf("Email  : %s\n", addressbook->contact_details[i].Mail_ID);

    found = 1;
}
        }

        if (!found)
        {
            printf(RED"Contact not found.\n"RESET);
        }
    }
}


Status edit_contact(AddressBook *addressbook)
{
    int choice;
    char search[50];
    Status status;

    if (addressbook->contact_count == 0)
    {
        printf(RED "No contacts available.\n" RESET);
        return Failure;
    }

    while (1)
    {
        printf(CYAN "\nEdit Contact menu : \n" RESET);
        printf(CYAN "1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\n" RESET);
        printf("Enter the option : ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        if (choice == 4)
            return Success;

        if (choice < 1 || choice > 4)
        {
            printf(RED "Invalid choice!\n" RESET);
            continue;
        }

        // Step 1: Input
        if (choice == 1)
        {
            do {
                printf(BLUE "Enter the name to edit: " RESET);
                scanf(" %[^\n]", search);
            } while (is_valid_name(search) == Failure);
        }
        else if (choice == 2)
        {
            do {
                printf(BLUE "Enter the phone number to edit: " RESET);
                scanf("%s", search);
            } while (is_valid_phone_format(search) == Failure);
        }
        else
        {
            do {
                printf(BLUE "Enter the email to edit: " RESET);
                scanf("%s", search);
            } while (is_valid_email_format(search) == Failure);
        }

        //HANDLE NAME (WITH DUPLICATES)
        if (choice == 1)
        {
            int indices[100];
            int count = 0;

            // Find matches
            for (int i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Name, search) == 0)
                {
                    indices[count++] = i;
                }
            }

            if (count == 0)
            {
                printf(RED "Contact not found.\n" RESET);
                continue;
            }

            int selected_index;

            if (count == 1)
            {
                selected_index = indices[0];
            }
            else
            {
                printf(CYAN "\nMatching Contacts:\n" RESET);

                for (int i = 0; i < count; i++)
                {
                    int idx = indices[i];
                    printf(MAGENTA "\nContact %d\n" RESET, i + 1);
                    printf("Name   : %s\n", addressbook->contact_details[idx].Name);
                    printf("Mobile : %s\n", addressbook->contact_details[idx].Mobile_number);
                    printf("Email  : %s\n", addressbook->contact_details[idx].Mail_ID);
                }

                char phone[20];
                int found = 0;

                do {
                    printf(BLUE "\nEnter phone number to select contact: " RESET);
                    scanf("%s", phone);

                    for (int i = 0; i < count; i++)
                    {
                        int idx = indices[i];

                        if (strcmp(addressbook->contact_details[idx].Mobile_number, phone) == 0)
                        {
                            selected_index = idx;
                            found = 1;
                            break;
                        }
                    }

                    if (!found)
                        printf(RED "Invalid phone number. Try again.\n" RESET);

                } while (!found);
            }

            int i = selected_index;

            // EDIT MENU
            printf(GREEN "\nContact Found!\n" RESET);
            printf("Name   : %s\n", addressbook->contact_details[i].Name);
                    printf("Mobile : %s\n", addressbook->contact_details[i].Mobile_number);
                    printf("Email  : %s\n", addressbook->contact_details[i].Mail_ID);

            int edit_choice;
            printf(CYAN "What do you want to edit?\n" RESET);
            printf(YELLOW "1. Name\n2. Phone\n3. Email\n4. All\nEnter choice: " RESET);
            scanf("%d", &edit_choice);
            while (getchar() != '\n');

            // EDIT LOGIC
            switch (edit_choice)
            {
                case 1:
                    do {
                        printf(BLUE "Enter new name: " RESET);
                        scanf(" %[^\n]", addressbook->contact_details[i].Name);

                        status = is_valid_name(addressbook->contact_details[i].Name);

                        if (status == Success)
                        {
                            for (int j = 0; j < addressbook->contact_count; j++)
                            {
                                if (j == i) continue;

                                if (strcmp(addressbook->contact_details[j].Name,
                                           addressbook->contact_details[i].Name) == 0)
                                {
                                    printf(RED "Error: Name already exists.\n" RESET);
                                    status = Failure;
                                    break;
                                }
                            }
                        }
                    } while (status == Failure);
                    break;

                case 2:
                {
                    char temp_phone[11];
                    strcpy(temp_phone, addressbook->contact_details[i].Mobile_number);

                    do {
                        printf(BLUE "Enter new phone number: " RESET);
                        scanf("%s", addressbook->contact_details[i].Mobile_number);

                        char new_phone[11];
                        strcpy(new_phone, addressbook->contact_details[i].Mobile_number);

                        strcpy(addressbook->contact_details[i].Mobile_number, temp_phone);

                        status = is_valid_phone(new_phone, addressbook);

                        if (status == Success)
                        {
                            strcpy(addressbook->contact_details[i].Mobile_number, new_phone);
                        }

                    } while (status == Failure);
                    break;
                }

                case 3:
                {
                    char temp_email[35];
                    strcpy(temp_email, addressbook->contact_details[i].Mail_ID);

                    do {
                        printf(BLUE "Enter new email: " RESET);
                        scanf("%s", addressbook->contact_details[i].Mail_ID);

                        char new_email[35];
                        strcpy(new_email, addressbook->contact_details[i].Mail_ID);

                        strcpy(addressbook->contact_details[i].Mail_ID, temp_email);

                        status = is_valid_email(new_email, addressbook);

                        if (status == Success)
                        {
                            strcpy(addressbook->contact_details[i].Mail_ID, new_email);
                        }

                    } while (status == Failure);
                    break;
                }

                case 4:
                    printf(GREEN "Edit all fields (same logic reused)\n" RESET);
                    break;

                default:
                    printf(RED "Invalid edit choice!\n" RESET);
                    break;
            }

            printf(GREEN "Contact updated successfully!\n" RESET);
        }


        else
        {
            int found = 0;

            for (int i = 0; i < addressbook->contact_count; i++)
            {
                int match = 0;

                if (choice == 2)
                    match = strcmp(addressbook->contact_details[i].Mobile_number, search) == 0;
                else
                    match = strcmp(addressbook->contact_details[i].Mail_ID, search) == 0;

                if (match)
                {
                    printf(GREEN "\nContact Found!\n" RESET);
                    printf("Name   : %s\n", addressbook->contact_details[i].Name);
                    printf("Mobile : %s\n", addressbook->contact_details[i].Mobile_number);
                    printf("Email  : %s\n", addressbook->contact_details[i].Mail_ID);

                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                printf(RED "Contact not found.\n" RESET);
            }
        }
    }
}

Status delete_contact(AddressBook *addressbook)
{
    int choice;
    char search[50];

    if (addressbook->contact_count == 0)
    {
        printf(CYAN "No contacts available.\n" RESET);
        return Failure;
    }

    while (1)
    {
        printf(CYAN "\nDelete Contact menu : \n" RESET);
        printf(YELLOW "1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\n" RESET);
        printf("Enter the option : ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        if (choice == 4)
            return Success;

        if (choice < 1 || choice > 4)
        {
            printf(RED "Invalid choice!\n" RESET);
            continue;
        }

        // Input
        if (choice == 1)
        {
            do {
                printf(BLUE "Enter the name to delete: " RESET);
                scanf(" %[^\n]", search);
            } while (is_valid_name(search) == Failure);
        }
        else if (choice == 2)
        {
            do {
                printf(BLUE "Enter the phone number to delete: " RESET);
                scanf("%s", search);
            } while (is_valid_phone_format(search) == Failure);
        }
        else
        {
            do {
                printf(BLUE "Enter the email to delete: " RESET);
                scanf("%s", search);
            } while (is_valid_email_format(search) == Failure);
        }

        // HANDLE NAME (WITH DUPLICATES)
        if (choice == 1)
        {
            int indices[100];
            int count = 0;

            // Find all matches
            for (int i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Name, search) == 0)
                {
                    indices[count++] = i;
                }
            }

            if (count == 0)
            {
                printf(CYAN "Contact not found.\n" RESET);
                continue;
            }

            int selected_index;

            if (count == 1)
            {
                selected_index = indices[0];
            }
            else
            {
                printf(CYAN "\nMatching Contacts:\n" RESET);

                for (int i = 0; i < count; i++)
                {
                    int idx = indices[i];
                    printf(MAGENTA "\nContact %d\n" RESET, i + 1);
                    printf("Name   : %s\n", addressbook->contact_details[idx].Name);
                    printf("Mobile : %s\n", addressbook->contact_details[idx].Mobile_number);
                    printf("Email  : %s\n", addressbook->contact_details[idx].Mail_ID);
                }

                char phone[20];
                int found = 0;

                do {
                    printf(BLUE "\nEnter phone number to select contact: " RESET);
                    scanf("%s", phone);

                    for (int i = 0; i < count; i++)
                    {
                        int idx = indices[i];

                        if (strcmp(addressbook->contact_details[idx].Mobile_number, phone) == 0)
                        {
                            selected_index = idx;
                            found = 1;
                            break;
                        }
                    }

                    if (!found)
                        printf(RED "Invalid phone number. Try again.\n" RESET);

                } while (!found);
            }

            int i = selected_index;

            char confirm;

            printf(GREEN "\nContact Found!\n" RESET);
            printf("Name   : %s\n", addressbook->contact_details[i].Name);
            printf("Mobile : %s\n", addressbook->contact_details[i].Mobile_number);
            printf("Email  : %s\n", addressbook->contact_details[i].Mail_ID);

            printf(YELLOW "Are you sure you want to delete this contact? (y/n): " RESET);
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y')
            {
                for (int j = i; j < addressbook->contact_count - 1; j++)
                {
                    addressbook->contact_details[j] = addressbook->contact_details[j + 1];
                }

                addressbook->contact_count--;

                printf(GREEN "Contact deleted successfully!\n" RESET);
            }
            else
            {
                printf(CYAN "Deletion cancelled.\n" RESET);
            }
        }

        // PHONE / EMAIL (NORMAL DELETE)
        else
        {
            int found = 0;

            for (int i = 0; i < addressbook->contact_count; i++)
            {
                int match = 0;

                if (choice == 2)
                    match = strcmp(addressbook->contact_details[i].Mobile_number, search) == 0;
                else
                    match = strcmp(addressbook->contact_details[i].Mail_ID, search) == 0;

                if (match)
                {
                    char confirm;

                    printf(GREEN "\nContact Found!\n" RESET);
                    printf("Name   : %s\n", addressbook->contact_details[i].Name);
                    printf("Mobile : %s\n", addressbook->contact_details[i].Mobile_number);
                    printf("Email  : %s\n", addressbook->contact_details[i].Mail_ID);

                    printf(YELLOW "Are you sure you want to delete this contact? (y/n): " RESET);
                    scanf(" %c", &confirm);

                    if (confirm == 'y' || confirm == 'Y')
                    {
                        for (int j = i; j < addressbook->contact_count - 1; j++)
                        {
                            addressbook->contact_details[j] = addressbook->contact_details[j + 1];
                        }

                        addressbook->contact_count--;

                        printf(GREEN "Contact deleted successfully!\n" RESET);
                    }
                    else
                    {
                        printf(CYAN "Deletion cancelled.\n" RESET);
                    }

                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                printf(CYAN "Contact not found.\n" RESET);
            }
        }
    }
}


Status save_contacts(AddressBook *addressbook)
{
    FILE *fp = fopen("contacts.txt", "w");

    if (fp == NULL)
        return Failure;

    fprintf(fp, "#%d\n", addressbook->contact_count);

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressbook->contact_details[i].Name,
                addressbook->contact_details[i].Mobile_number,
                addressbook->contact_details[i].Mail_ID);
    }

    fclose(fp);
    return Success;
}


Status load_contacts(AddressBook *addressbook)
{
    FILE *fp = fopen("contacts.txt", "r");

    if (fp == NULL)
        return Failure;

    fscanf(fp, "#%d\n", &addressbook->contact_count);

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        fscanf(fp, "%[^,],%[^,],%s\n",
               addressbook->contact_details[i].Name,
               addressbook->contact_details[i].Mobile_number,
               addressbook->contact_details[i].Mail_ID);
    }

    fclose(fp);
    return Success;
}

Status is_valid_name(char *Name)
{
    for (int i = 0; Name[i] != '\0'; i++)
    {
        if (!(isalpha(Name[i])|| Name[i] == ' '))
        {
            printf(RED"Invalid!Name should only contain alphabets\n"RESET);
            return Failure;
        }
    
    }
    
    return Success;
}

Status is_duplicate_name(char *Name, AddressBook *addressbook)
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (strcmp(Name, addressbook->contact_details[i].Name) == 0)
        {
            printf(RED"Error: Name already exists.\n"RESET);
            return Failure;
        }
    }
    return Success;
}

Status is_valid_phone(char *phone, AddressBook *addressbook)
{
    // Check only digits first
    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (!isdigit(phone[i]))
        {
            printf(RED"Error: Phone number must contain only digits.\n"RESET);
            return Failure;
        }
    }

    // Length check
    if (strlen(phone) != 10)
    {
        printf(RED"Error: Phone number must be exactly 10 digits.\n"RESET);
        return Failure;
    }

    // First digit check
    if (phone[0] < '6' || phone[0] > '9')
    {
        printf(RED"Error: First digit must be between 6 and 9.\n"RESET);
        return Failure;
    }

    // Unique check
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (strcmp(phone, addressbook->contact_details[i].Mobile_number) == 0)
        {
            printf(RED"Error: Phone number already exists.\n"RESET);
            return Failure;
        }
    }

    return Success;
}


Status is_valid_email(char *email, AddressBook *addressbook)
{
    int i, at = -1, dot = -1;
    int at_count = 0;

    int alpha_before_at = 0;

for (i = 0; email[i] != '\0'; i++)
{
    if (!(islower(email[i]) || isdigit(email[i]) || email[i] == '@' || email[i] == '.'))
    {
        printf(RED"Error: Only lowercase letters, digits, '@' and '.' are allowed.\n"RESET);
        return Failure;
    }

    if (email[i] == '@')
    {
        at = i;
        at_count++;
    }

    if (email[i] == '.')
        dot = i;

    //Check alphabet before '@'
    if (at == -1 && islower(email[i]))
    {
        alpha_before_at = 1;
    }

    // digits after '@'
    if (at != -1 && isdigit(email[i]))
    {
        printf(RED"Error: Digits are not allowed after '@'.\n"RESET);
        return Failure;
    }
}

    // More than one '@'
    if (at_count != 1)
    {
        printf(RED"Error: Email must contain exactly one '@'.\n"RESET);
        return Failure;
    }

    // Nothing before '@'
    if (at == 0)
    {
        printf(RED"Error: There must be characters before '@'.\n"RESET);
        return Failure;
    }

    // '@' missing
    if (at == -1)
    {
        printf(RED"Error: Email must contain '@'.\n"RESET);
        return Failure;
    }

    // '.com' check
    if (dot == -1 || strcmp(&email[dot], ".com") != 0)
    {
        printf(RED"Error: Email must end with '.com'.\n"RESET);
        return Failure;
    }

    // '.' before '@'
    if (dot < at)
    {
        printf(RED"Error: '.' must come after '@'.\n"RESET);
        return Failure;
    }

    // No domain
    if (dot - at <= 1)
    {
        printf(RED"Error: Domain name missing between '@' and '.com'.\n"RESET);
        return Failure;
    }

    if (!alpha_before_at)
    {
        printf(RED"Error: Email must contain at least one alphabet before '@'.\n"RESET);
        return Failure;
    }

    // Duplicate check
    for (i = 0; i < addressbook->contact_count; i++)
    {
        if (strcmp(email, addressbook->contact_details[i].Mail_ID) == 0)
        {
            printf(RED"Error: Email already exists.\n"RESET);
            return Failure;
        }
    }

    return Success;
}

Status is_valid_phone_format(char *phone)
{
    // Check only digits first
    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (!isdigit(phone[i]))
        {
            printf(RED"Error: Phone number must contain only digits.\n"RESET);
            return Failure;
        }
    }

    // Length check
    if (strlen(phone) != 10)
    {
        printf(RED"Error: Phone number must be exactly 10 digits.\n"RESET);
        return Failure;
    }

    // First digit check
    if (phone[0] < '6' || phone[0] > '9')
    {
        printf(RED"Error: First digit must be between 6 and 9.\n"RESET);
        return Failure;
    }

    return Success;
}

Status is_valid_email_format(char *email)
{
   int i, at = -1, dot = -1;
    int at_count = 0;

    int alpha_before_at = 0;

for (i = 0; email[i] != '\0'; i++)
{
    if (!(islower(email[i]) || isdigit(email[i]) || email[i] == '@' || email[i] == '.'))
    {
        printf(RED"Error: Only lowercase letters, digits, '@' and '.' are allowed.\n"RESET);
        return Failure;
    }

    if (email[i] == '@')
    {
        at = i;
        at_count++;
    }

    if (email[i] == '.')
        dot = i;

    //Check alphabet before '@'
    if (at == -1 && islower(email[i]))
    {
        alpha_before_at = 1;
    }

    // digits after '@'
    if (at != -1 && isdigit(email[i]))
    {
        printf(RED"Error: Digits are not allowed after '@'.\n"RESET);
        return Failure;
    }
}

    // More than one '@'
    if (at_count != 1)
    {
        printf(RED"Error: Email must contain exactly one '@'.\n"RESET);
        return Failure;
    }

    // Nothing before '@'
    if (at == 0)
    {
        printf(RED"Error: There must be characters before '@'.\n"RESET);
        return Failure;
    }

    // '@' missing
    if (at == -1)
    {
        printf(RED"Error: Email must contain '@'.\n"RESET);
        return Failure;
    }

    // '.com' check
    if (dot == -1 || strcmp(&email[dot], ".com") != 0)
    {
        printf(RED"Error: Email must end with '.com'.\n"RESET);
        return Failure;
    }

    // '.' before '@'
    if (dot < at)
    {
        printf(RED"Error: '.' must come after '@'.\n"RESET);
        return Failure;
    }

    // No domain
    if (dot - at <= 1)
    {
        printf(RED"Error: Domain name missing between '@' and '.com'.\n"RESET);
        return Failure;
    }

    if (!alpha_before_at)
    {
        printf(RED"Error: Email must contain at least one alphabet before '@'.\n"RESET);
        return Failure;
    }
    return Success;
}
int get_matching_indices(AddressBook *addressbook, char *name, int indices[])
{
    int count = 0;

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (strcmp(addressbook->contact_details[i].Name, name) == 0)
        {
            indices[count++] = i;
        }
    }

    return count;
}

