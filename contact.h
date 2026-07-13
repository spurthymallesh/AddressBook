#ifndef CONTACT_H
#define CONTACT_H

// Structures for the Fields
typedef struct Contact_data
{
    char Name[32];
    char Mobile_number[11];
    char Mail_ID[35];

} Contacts;

// Structures foe the Contact deatils
typedef struct AddressBook_Data
{
    // Array of structures for the Fields sturucture
    Contacts contact_details[100];
    // To keep the track no of contact count
    int contact_count;
} AddressBook;

typedef enum Status_info
{
    Failure,
    Success,
} Status;

/* Function declarations */

Status create_contact(AddressBook *);
void list_contacts(AddressBook *);
Status search_contacts(AddressBook *);
Status edit_contact(AddressBook *);
Status delete_contact(AddressBook *);
Status save_contacts(AddressBook *);
Status load_contacts(AddressBook *addressbook);


// Validation function declarations//
Status is_valid_name(char *name);
Status is_duplicate_name(char *Name, AddressBook *addressbook);
Status is_valid_phone(char *phone, AddressBook *addressbook);
Status is_valid_email(char *email, AddressBook *addressbook);
Status is_valid_email_format(char *email);
Status is_valid_phone_format(char *phone);



#endif
// CONTACT_H
// CONTACT_H