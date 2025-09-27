#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Global variables for storing matched results
int matchedIndices[100];
int matchedCount = 0;

// **Validation Functions**

// Validate Name -> Only alphabets & spaces allowed
int is_valid_name(const char new_name[]) {
    for (int i = 0; new_name[i] != '\0'; i++) {
        if (!isalpha(new_name[i]) && new_name[i] != ' ')
            return 0;  // invalid
    }
    return 1; // valid
}

// Validate Phone Number -> 10 digits, starts with 6-9, unique
int is_valid_phno(AddressBook *addressBook, const char new_phno[]) {
    int len = strlen(new_phno);

    // Must be 10 digits
    if (len != 10) 
        return 0;
    // Must start 6-9
    if (new_phno[0] < '6' || new_phno[0] > '9') 
        return 0;
    // Must be digits
    for (int i = 0; i < len; i++) {
        if (!isdigit(new_phno[i])) 
            return 0;
    }
    // Check uniqueness
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, new_phno) == 0)
            return 0;
    }

    return 1; //valid
}

// Validate Email -> @ and . check, in correct position, unique
int is_valid_email(AddressBook *addressBook, const char new_email[]) {
    int len = strlen(new_email);
    int count = 0;

    char *at = strchr(new_email, '@');
    // must contain @
    if (at == NULL) 
        return 0;

    //must coniatin only one @
    for(int i = 0;i < len;i++){
        if(new_email[i] == '@')
            count++;
    }
    if (count != 1)
        return 0;

    // must be present in the middle
    if (at == new_email || at == new_email + len - 1) 
        return 0;  

    char *dot = strrchr(at, '.');
    // must contain .
    if (dot == NULL || dot == at + 1) 
        return 0; 
    // must not have . at end
    if (dot == new_email + len - 1) 
        return 0; 
    
    for (int i = 0; i < len; i++) {
        // should not contain spaces
        if (isspace(new_email[i])) 
            return 0;
        // should not contain anything except numbers, lowercase alphabet, '.' and '@'  
        if (!(isdigit(new_email[i]) || islower(new_email[i]) || new_email[i] == '.' || new_email[i] == '@'))
            return 0;
    }
    // Check uniqueness
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, new_email) == 0)
            return 0;
    }

    return 1; // valid
}


// **Search Functions**

// Search by Name
void searchByName(AddressBook *addressBook, const char *search) {
    if (!is_valid_name(search)) {
        printf("\n❌ Invalid name format! Please enter alphabets only.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, search) == 0) { 
            printf("\n✅ Contact Found!\n");
            printf("---------------------------------\n");
            printf("👤 Name : %s\n", addressBook->contacts[i].name);
            printf("📞 Phone: %s\n", addressBook->contacts[i].phone);
            printf("📧 Email: %s\n", addressBook->contacts[i].email);
            printf("---------------------------------\n");
            found = 1;
        }
    }
    if (!found) 
        printf("\n⚠️ No contact found with that name.\n");
}

// Search by Phone number
void searchByPhone(AddressBook *addressBook, const char *search) {
    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, search) == 0) {
            printf("\n✅ Contact Found!\n");
            printf("---------------------------------\n");
            printf("👤 Name : %s\n", addressBook->contacts[i].name);
            printf("📞 Phone: %s\n", addressBook->contacts[i].phone);
            printf("📧 Email: %s\n", addressBook->contacts[i].email);
            printf("---------------------------------\n");
            found = 1;
        }
    }
    if (!found) 
        printf("\n⚠️ No contact found with that phone number.\n");
}

// Search by Email
void searchByEmail(AddressBook *addressBook, const char *search) {
    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, search) == 0) {
            printf("\n✅ Contact Found!\n");
            printf("---------------------------------\n");
            printf("👤 Name : %s\n", addressBook->contacts[i].name);
            printf("📞 Phone: %s\n", addressBook->contacts[i].phone);
            printf("📧 Email: %s\n", addressBook->contacts[i].email);
            printf("---------------------------------\n");
            found = 1;
        }
    }
    if (!found) 
        printf("\n⚠️ No contact found with that email.\n");
}

//Edit Functions

void editMenu(AddressBook *addressBook, int index) {
    int choice;
    char buffer[50];

    printf("\n=====================================\n");
    printf("            ✏️ Edit Menu\n");
    printf("=====================================\n");
    printf(" 1) 👤 Edit Name\n");
    printf(" 2) 📞 Edit Phone Number\n");
    printf(" 3) 📧 Edit Email\n");
    printf("=====================================\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            while (1) {
                printf("Enter new name (or 'q' to cancel): ");
                scanf(" %[^\n]", buffer);
                if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0) {
                    printf("❌ Edit cancelled.\n");
                    break;
                }
                if (is_valid_name(buffer)) {
                    strcpy(addressBook->contacts[index].name, buffer);
                    printf("✅ Name updated successfully!\n");
                    break;
                } 
                else 
                    printf("⚠️ Invalid name format! Try again.\n");
            }
            break;

        case 2:
            while (1) {
                printf("Enter new phone number (or 'q' to cancel): ");
                scanf(" %[^\n]", buffer);
                if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0) {
                    printf("❌ Edit cancelled.\n");
                    break;
                }
                if (is_valid_phno(addressBook, buffer)) {
                    strcpy(addressBook->contacts[index].phone, buffer);
                    printf("✅ Phone updated successfully!\n");
                    break;
                } 
                else 
                    printf("⚠️ Invalid phone number! Try again.\n");
            }
            break;

        case 3:
            while (1) {
                printf("Enter new email (or 'q' to cancel): ");
                scanf(" %[^\n]", buffer);
                if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0) {
                    printf("❌ Edit cancelled.\n");
                    break;
                }
                if (is_valid_email(addressBook, buffer)) {
                    strcpy(addressBook->contacts[index].email, buffer);
                    printf("✅ Email updated successfully!\n");
                    break;
                } 
                else 
                    printf("⚠️ Invalid email format! Try again.\n");
            }
            break;

        default:
            printf("⚠️ Invalid choice!\n");
    }
}

// Compare by Name

int compareByName(const void *a, const void *b) {
    Contact *c1 = (Contact *)a;
    Contact *c2 = (Contact *)b;
    return strcmp(c1->name, c2->name); // A to Z
}

// **List Contact**

void listContacts(AddressBook *addressBook, int sortCriteria) {
    if (addressBook->contactCount == 0) {
        printf("\n⚠️ No contacts to display!\n");
        return;
    }

    // If sorting by name, create a copy and sort it
    if (sortCriteria == 1) {
        AddressBook temp = *addressBook; // copy all contacts
        qsort(temp.contacts, temp.contactCount, sizeof(Contact), compareByName);

        printf("\n📖 Contacts (Sorted by Name A-Z):\n");
        for (int i = 0; i < temp.contactCount; i++) {
            printf("%d) %s | %s | %s\n", i + 1,
                   temp.contacts[i].name,
                   temp.contacts[i].phone,
                   temp.contacts[i].email);
        }
    }
    // If recently added (default order)
    else if (sortCriteria == 2) {
        printf("\n📖 Contacts (Recently Added):\n");
        for (int i = 0; i < addressBook->contactCount; i++) {
            printf("%d) %s | %s | %s\n", i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
        }
    }
    else
        printf("❌ Invalid choice.\n");
}

// **Initaial Load Contact**

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

// **Save and Exit Contact**

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

// **Create Contact**

void createContact(AddressBook *addressBook) {
    if (addressBook->contactCount >= MAX_CONTACTS) {
        printf("\n🚫 Address book is full! Cannot add more contacts.\n");
        return;
    }

    Contact newContact;
    int valid;

    printf("\n=====================================\n");
    printf("       📒 Add a New Contact\n");
    printf("=====================================\n");

    // Name
    do {
        printf("👤 Enter Name: ");
        scanf(" %[^\n]", newContact.name);
        valid = is_valid_name(newContact.name);
        if (!valid) 
            printf("❌ Invalid name! Use only letters & spaces.\n");
    } while (!valid);

    // Phone
    do {
        printf("📞 Enter Phone (10 digits): ");
        scanf(" %[^\n]", newContact.phone);
        valid = is_valid_phno(addressBook, newContact.phone);
        if (!valid) 
            printf("❌ Invalid phone number! Try again.\n");
    } while (!valid);

    // Email
    do {
        printf("📧 Enter Email: ");
        scanf(" %[^\n]", newContact.email);
        valid = is_valid_email(addressBook, newContact.email);
        if (!valid) 
            printf("❌ Invalid email! Try again.\n");
    } while (!valid);

    addressBook->contacts[addressBook->contactCount++] = newContact;
    printf("Name: '%s' saved successfully!\n", newContact.name);
    printf("Phone: '%s' saved successfully!\n", newContact.phone);
    printf("Email: '%s' saved successfully!\n", newContact.email);
    printf("\n✅ Contact saved successfully!\n");
}

// **Search Contact**

void searchContact(AddressBook *addressBook) {
    int choice;
    char search[50];

    while (1) {
        printf("\n=====================================\n");
        printf("           🔍 Search Menu\n");
        printf("=====================================\n");
        printf(" 1) 👤 Search by Name\n");
        printf(" 2) 📞 Search by Phone Number\n");
        printf(" 3) 📧 Search by Email ID\n");
        printf(" 4) 🔙 Back to Main Menu\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter Name to search: ");
                scanf(" %[^\n]", search);
                searchByName(addressBook, search);
                break;
            case 2:
                printf("\nEnter Phone Number to search: ");
                scanf(" %[^\n]", search);
                searchByPhone(addressBook, search);
                break;
            case 3:
                printf("\nEnter Email ID to search: ");
                scanf(" %[^\n]", search);
                searchByEmail(addressBook, search);
                break;
            case 4:
                printf("\n🔙 Returning to Main Menu...\n");
                return;
            default:
                printf("\n❌ Invalid choice! Try again.\n");
        }
    }
}

// **Edit Contact**

void editContact(AddressBook *addressBook) {
    int searchChoice;
    char query[50];

    printf("\n=====================================\n");
    printf("            ✏️ Edit Contact\n");
    printf("=====================================\n");
    printf(" 1) 👤 Search by Name\n");
    printf(" 2) 📞 Search by Phone\n");
    printf(" 3) 📧 Search by Email\n");
    printf("=====================================\n");
    printf("Enter choice: ");
    scanf("%d", &searchChoice);

    if (searchChoice == 1) {
        printf("Enter name to search: ");
        scanf(" %[^\n]", query);
        if (!is_valid_name(query)) {
            printf("❌ Invalid name format!\n");
            return;
        }

        matchedCount = 0;
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].name, query) == 0) {
                matchedIndices[matchedCount++] = i;
                printf("[%d] %s | %s | %s\n", matchedCount,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
            }
        }
        if (matchedCount == 0) {
            printf("⚠️ No contacts found with that name.\n");
            return;
        }
        int choice;
        printf("Enter index of contact to edit (1-%d): ", matchedCount);
        scanf("%d", &choice);
        if (choice < 1 || choice > matchedCount) {
            printf("⚠️ Invalid choice!\n");
            return;
        }
        editMenu(addressBook, matchedIndices[choice - 1]);
    }
    else if (searchChoice == 2) {
        printf("Enter phone number: ");
        scanf(" %[^\n]", query);
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].phone, query) == 0) {
                editMenu(addressBook, i);
                return;
            }
        }
        printf("⚠️ No contact found with that phone number.\n");
    }
    else if (searchChoice == 3) {
        printf("Enter email: ");
        scanf(" %[^\n]", query);
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].email, query) == 0) {
                editMenu(addressBook, i);
                return;
            }
        }
        printf("⚠️ No contact found with that email.\n");
    }
    else {
        printf("⚠️ Invalid search choice!\n");
    }
}

// **Delete Contact**

void deleteContact(AddressBook *addressBook) {
    int choice;
    char query[50];
    int deleteIndexes[10];
    int deleteCount = 0;

    printf("\n=====================================\n");
    printf("            🗑️ Delete Contact\n");
    printf("=====================================\n");
    printf(" 1) 👤 Delete by Name\n");
    printf(" 2) 📞 Delete by Phone Number\n");
    printf(" 3) 📧 Delete by Email ID\n");
    printf("=====================================\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("Enter search query: ");
    scanf(" %[^\n]", query);

    if (choice == 1) {
        int matches[100], matchCount = 0;
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].name, query) == 0) {
                matches[matchCount++] = i;
            }
        }
        if (matchCount == 0) {
            printf("❌ No contacts found with that name.\n");
            return;
        }
        printf("\nFound %d contact(s):\n", matchCount);
        for (int i = 0; i < matchCount; i++) {
            int idx = matches[i];
            printf("[%d] %s | %s | %s\n", idx, addressBook->contacts[idx].name, addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
        }
        printf("\nEnter indexes to delete (space separated, -1 to stop): ");
        while (1) {
            int idx;
            scanf("%d", &idx);
            if (idx == -1) 
                break;
            deleteIndexes[deleteCount++] = idx;
        }
    }
    else if (choice == 2 || choice == 3) {
        int found = -1;
        for (int i = 0; i < addressBook->contactCount; i++) {
            if ((choice == 2 && strcmp(addressBook->contacts[i].phone, query) == 0) || (choice == 3 && strcmp(addressBook->contacts[i].email, query) == 0)) {
                found = i;
                break;
            }
        }
        if (found == -1) {
            printf("❌ Contact not found.\n");
            return;
        }
        deleteIndexes[deleteCount++] = found;
    }
    else {
        printf("❌ Invalid choice.\n");
        return;
    }

    printf("\nAre you sure you want to delete %d contact(s)? (y/n): ", deleteCount);
    char confirm;
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("❌ Deletion cancelled.\n");
        return;
    }

    for (int i = 0; i < deleteCount; i++) {
        int idx = deleteIndexes[i];
        for (int j = idx; j < addressBook->contactCount - 1; j++) {
            addressBook->contacts[j] = addressBook->contacts[j + 1];
        }
        addressBook->contactCount--;
        for (int k = i + 1; k < deleteCount; k++) {
            if (deleteIndexes[k] > idx) deleteIndexes[k]--;
        }
    }
    printf("✅ %d contact(s) deleted successfully!\n", deleteCount);
}
