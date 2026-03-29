#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

void save_file(struct person* head, char fileName[]);
void load_file(struct person** head, char fileName[]);

static void print_menu(void) {
    printf("\n===== Social Network Menu =====\n");
    printf("1) Introduce user\n");
    printf("2) Introduce new relationship\n");
    printf("3) Remove user\n");
    printf("4) Print a given person's friends\n");
    printf("5) Save to file\n");
    printf("6) Retrieve data from file\n");
    printf("7) Exit\n");
    printf("8) Print all users (debug)\n");
    printf("Choose an option: ");
}

int main() {
    struct person* head = NULL;
    int option = 0;
    char name1[MAX_NAME];
    char name2[MAX_NAME];
    char fileName[100];

    do {
        print_menu();

        if (scanf("%d", &option) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');   // clear input buffer
            continue;
        }

        switch (option) {
        case 1:
            printf("Enter user name: ");
            scanf("%49s", name1);
            insert_person(name1, &head);
            break;

        case 2:
            printf("Enter first user name: ");
            scanf("%49s", name1);
            printf("Enter second user name: ");
            scanf("%49s", name2);
            add_relationship(head, name1, name2);
            break;

        case 3:
            printf("Enter user name to remove: ");
            scanf("%49s", name1);
            remove_person(&head, name1);
            break;

        case 4:
            printf("Enter user name: ");
            scanf("%49s", name1);
            print_friend(head, name1);
            break;

        case 5:
            printf("Enter file name to save: ");
            scanf("%99s", fileName);
            save_file(head, fileName);
            break;

        case 6:
            printf("Enter the whole file path to load: ");
            scanf("%99s", fileName);
            load_file(&head, fileName);
            break;

        case 7:
            printf("Exiting program...\n");
            break;

        case 8:
            print_all_users(head);
            break;

        default:
            printf("Invalid option. Please choose 1-8.\n");
        }

    } while (option != 7);

    free_list(&head);
    return 0;

}