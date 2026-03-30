#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

void print_all_users(struct person* head) {
	struct person* curr = head;

	if (curr == NULL) {
		printf("No users in the network.\n");
		return;
	}

	printf("All users in order:\n");
	while (curr != NULL) {
		printf("%s\n", curr->name);
		curr = curr->next;
	}
}

struct person* create_person(char name[]) {
	struct person* p = malloc(sizeof(struct person));
	if (p != NULL) {
		strcpy(p->name, name);
		p->friend_count = 0;
		p->next = NULL;
	}
	return p;
}

//

struct person* find_person(struct person *head, char name[]) {
	struct person* i = head;
	while (i != NULL) {
		if (strcmp(i->name, name) == 0) {
			return i;
		}
		i = i->next;
	}
	return NULL;
}

struct person* insert_person(char name[], struct person **head) {   // 调用的时候传&head
	if (find_person(*head, name) != NULL) {
		printf("This user was already exist.\n");
		return NULL;
	}

	struct person* newNode = create_person(name);

	if (newNode == NULL) {
		printf("memory allocation failed.\n");
		return NULL;
	}

	if (*head == NULL){
		*head = newNode;
		return newNode;
		}

	if (strcmp(name, (*head)->name) < 0) {  //compare input with head
		newNode->next = *head;
		*head = newNode;
		return newNode;
	}

	struct person* prev = *head;
	struct person* curr = (*head)->next;

	while (curr != NULL && strcmp(name, curr->name) > 0) {
		prev = curr;
		curr = curr->next;
	}

	prev->next = newNode;
	newNode->next = curr;
	return newNode;
}

int is_friend(struct person* p, char name[]) {
	for (int i = 0; i < (p->friend_count); i++ ) {
		if (strcmp(p->friends[i], name) == 0) {
			return i;
		}
	}
	return -1;
}

void add_relationship(struct person* head, char name1[], char name2[]) {
	struct person* p1 = find_person(head, name1);
	struct person* p2 = find_person(head, name2);

	if (p1 == NULL || p2 == NULL) {
		printf("User do not exist.\n");
		return;
	}

	if (strcmp(name1, name2) == 0) {
		printf("Cannot add yourself as friend.\n");
		return;
	}

	if (is_friend(p1, name2) != -1) {
		printf("Person 2 have been added as Person 1 's friend.\n");
		return;
	}

	if (is_friend(p2, name1) != -1) {
		printf("Person 1 have been added as Person 2 's friend.\n");
		return;
	}

	if (p1->friend_count == 20) {
		printf("Friend list of person 1 is full.\n");
		return;
	}

	if (p2->friend_count == 20) {
		printf("Friend list of person 2 is full.\n");
		return;
	}

	strcpy(p1->friends[p1->friend_count], name2);
	p1->friend_count++;

	strcpy(p2->friends[p2->friend_count], name1);
	p2->friend_count++;

	printf("Friends successfully added!\n");
	return;
}

void print_friend(struct person* head, char name[]) {
	struct person* p = find_person(head, name);

	if (p == NULL) {
		printf("User is not found.\n");
		return;
	}

	if (p->friend_count == 0) {
		printf("You have no friends!\n");
		return;
	}

	for (int i = 0; i < p->friend_count; i++) {
		printf("%s\n", p->friends[i]);
	}
	return;
}

void remove_friend(struct person* p, char name[]) {
	//朋友数组不是链表，所以删一个元素后要把后面的元素整体左移。
	int i = is_friend(p, name);
	if (i == -1) {  
		return;
	}
	
	for (int j = i; j < (p->friend_count)-1; j++) {
		strcpy(p->friends[j], p->friends[j + 1]);
	}
	p->friend_count = (p->friend_count) - 1;
	return;
}

void remove_person(struct person** head, char name[]) {

	if (*head == NULL) {
		printf("Empty list.\n");
		return;
	}

	struct person* t = find_person(*head, name);
	if (t == NULL) {
		printf("Person do not exit.\n");
		return;
	}

	struct person* temp = *head;
	while (temp != NULL) {
		remove_friend(temp, name);
		temp = temp->next;
	}

	if (strcmp((*head)->name, name) == 0) {
		struct person* temp = *head;
		*head = (*head)->next;
		free(temp);
		return;
	}

	struct person* prev = *head;
	struct person* curr = (*head)->next;

	while (curr != NULL && strcmp(name, curr->name) != 0) {
		prev = curr;
		curr = curr->next;
	}

	if (curr != NULL) {
		prev->next = curr->next;
		free(curr);
	}
	return;
}

void free_list(struct person** head) {
	struct person* curr = *head;
	while (curr != NULL) {
		struct person* temp = curr->next;
		free(curr);
		curr = temp;
	}
	*head = NULL;
	return;
}