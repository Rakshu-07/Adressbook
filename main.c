#include <stdio.h>
#include "contact.h"

int main() {
    int choice,sortChoice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\n=====================================\n");
        printf("     📖 Welcome to Address Book 📖    \n");
        printf("=====================================\n");
        printf(" 1️⃣  Create Contact\n");
        printf(" 2️⃣  Search Contact\n");
        printf(" 3️⃣  Edit Contact\n");
        printf(" 4️⃣  Delete Contact\n");
        printf(" 5️⃣  List All Contacts\n");
        printf(" 6️⃣  Save Contacts\n");
        printf(" 7️⃣  Exit\n");
        printf("=====================================\n");
        printf("👉 Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                printf("\n📖 List Contacts - Choose sorting option:\n");
                printf("1) By Name (A-Z)\n");
                printf("2) By Recently Added\n");
                printf("Enter your choice: ");
                scanf("%d", &sortChoice);    
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Exiting the Address Book\n");
        }
    }while (choice != 7);
    
    return 0;
}
