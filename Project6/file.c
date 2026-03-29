#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

void save_file(struct person* head, char fileName[]) {
	FILE* fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Fail to open file.\n");
		return;
	}

	struct person* curr = head;
	while (curr != NULL) {
		fprintf(fp, "%s \n %d\n ", curr->name, curr->friend_count); 
		for (int i = 0; i < curr->friend_count; i++) {
			fprintf(fp, "%s\n", curr->friends[i]);
		}
		curr = curr->next;
	}

	fclose(fp);
	return;
}

void load_file(struct person** head, char fileName[]) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Fail to open file.\n");
		return;
	}

	free_list(head);

	char name[MAX_NAME];
	char friendName[MAX_NAME];
	int fc = 0;
	while (fscanf(fp, "%s %d", name, &fc) == 2) {
		struct person* p = insert_person(name,head);
		if (p == NULL) {
			fclose(fp);
			return;
		}
		p->friend_count = fc;

		for (int i = 0; i < fc; i++) {
			fscanf(fp, "%s", friendName);
			strcpy(p->friends[i], friendName);
		}
	}

	fclose(fp);
	
}

