#pragma once

#define MAX_NAME 50
#define MAX_FRIENDS 20

struct person {
	char name[MAX_NAME];
	char friends[MAX_FRIENDS][MAX_NAME];
	int friend_count;
	struct person* next;
};

struct person* create_person(char name[]);
struct person* find_person(struct person* head, char name[]);
struct person* insert_person(char name[], struct person** head);
int is_friend(struct person* p, char name[]);
void add_relationship(struct person* head, char name1[], char name2[]);
void print_friend(struct person* head, char name[]);
void remove_friend(struct person* p, char name[]);
void remove_person(struct person** head, char name[]);
void free_list(struct person** head);
void print_all_users(struct person* head);

void save_file(struct person* head, char fileName[]);
void load_file(struct person** head, char fileName[]);