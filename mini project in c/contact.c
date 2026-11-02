
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

void addContact() {
    struct Contact c;
    FILE *fp = fopen("contacts.dat", "ab");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %49[^\n]", c.name);

    printf("Enter Phone: ");
    scanf("%14s", c.phone);

    printf("Enter Email: ");
    scanf("%49s", c.email);

    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);

    printf("Contact added successfully!\n");
}

void displayContacts() {
    struct Contact c;
    FILE *fp = fopen("contacts.dat", "rb");

    if (fp == NULL) {
        printf("No contacts found!\n");
        return;
    }

    printf("\n--- Contact List ---\n");

    while (fread(&c, sizeof(c), 1, fp) == 1) {
        printf("\nName  : %s", c.name);
        printf("\nPhone : %s", c.phone);
        printf("\nEmail : %s\n", c.email);
    }

    fclose(fp);
}

void searchContact() {
    struct Contact c;
    char name[50];
    int found = 0;

    FILE *fp = fopen("contacts.dat", "rb");

    if (fp == NULL) {
        printf("No contacts found!\n");
        return;
    }

    printf("Enter name to search: ");
    scanf(" %49[^\n]", name);

    while (fread(&c, sizeof(c), 1, fp) == 1) {
        if (strcmp(c.name, name) == 0) {
            printf("\nContact Found!\n");
            printf("Name  : %s\n", c.name);
            printf("Phone : %s\n", c.phone);
            printf("Email : %s\n", c.email);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Contact not found!\n");

    fclose(fp);
}

void updateContact() {
    struct Contact c;
    char name[50];
    int found = 0;

    FILE *fp = fopen("contacts.dat", "rb+");

    if (fp == NULL) {
        printf("No contacts found!\n");
        return;
    }

    printf("Enter name to update: ");
    scanf(" %49[^\n]", name);

    while (fread(&c, sizeof(c), 1, fp) == 1) {
        if (strcmp(c.name, name) == 0) {
            printf("Enter new phone: ");
            scanf("%14s", c.phone);

            printf("Enter new email: ");
            scanf("%49s", c.email);

            fseek(fp, -(long)sizeof(c), SEEK_CUR);
            fwrite(&c, sizeof(c), 1, fp);

            found = 1;
            printf("Contact updated!\n");
            break;
        }
    }

    if (!found)
        printf("Contact not found!\n");

    fclose(fp);
}

void deleteContact() {
    struct Contact c;
    char name[50];
    int found = 0;

    FILE *fp = fopen("contacts.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        if (fp != NULL)
            fclose(fp);
        if (temp != NULL)
            fclose(temp);
        return;
    }

    printf("Enter name to delete: ");
    scanf(" %49[^\n]", name);

    while (fread(&c, sizeof(c), 1, fp) == 1) {
        if (strcmp(c.name, name) == 0 && !found) {
            found = 1;
            continue;
        }

        fwrite(&c, sizeof(c), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("contacts.dat");
    rename("temp.dat", "contacts.dat");

    if (found)
        printf("Contact deleted!\n");
    else
        printf("Contact not found!\n");
}

int main() {
    int choice;

    do {
        printf("\n===== CONTACT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Update Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addContact();
                break;

            case 2:
                displayContacts();
                break;

            case 3:
                searchContact();
                break;

            case 4:
                updateContact();
                break;

            case 5:
                deleteContact();
                break;

            case 6:
                printf("Thank you!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}
