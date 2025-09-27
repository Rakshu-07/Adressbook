#include <stdio.h>
#include <string.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.csv", "w");  // Open file in write mode
    if (fptr == NULL) {
        printf("❌ Error: Could not open file for saving contacts.\n");
        return;
    }

    // Write contact count
    fprintf(fptr, "%d\n", addressBook->contactCount);

    // Write each contact in file
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);  // Close file
    printf("✅ Contacts saved successfully to contacts.csv\n");
}


void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.csv", "r");   // Open file in read mode
    if (fptr == NULL) {
        printf("⚠️ No saved contacts found. Starting fresh.\n");
        return;
    }

    // Read contact count
    if (fscanf(fptr, "%d\n", &addressBook->contactCount) != 1) {
        printf("❌ Error: Could not read contact count from file.\n");
        fclose(fptr);
        return;
    }

    // Read each contact
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (fscanf(fptr, "%49[^,],%19[^,],%49[^\n]\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email) != 3) 
        {
            printf("❌ Error: Malformed contact data at line %d.\n", i + 2);
            addressBook->contactCount = i;
            break;
        }
    }

    fclose(fptr);
    printf("✅ %d contacts loaded successfully from contacts.csv\n", addressBook->contactCount);
}
