# Social Network

## Overview
This project is a simple social network application written in C.

It allows the user to:
- introduce new users
- create relationships between users
- remove users
- print a person's friends
- save the network data to a file
- retrieve the network data from a file

The project uses:
- a **linked list** to store all users in **alphabetical order**
- **arrays** to store each user's friends
- **dynamic memory allocation** for adding and removing users
- **file handling** for saving and loading data

---

## Features

### 1. Introduce user
Adds a new user into the social network.  
Users are inserted into the linked list in alphabetical order.

### 2. Introduce new relationship
Creates a friendship relationship between two existing users.  
The friendship is stored in both users' friend lists.

### 3. Remove user
Removes a user from the linked list and frees the allocated memory.  
The removed user is also deleted from other users' friend lists.

### 4. Print a given person's friends
Prints all friends of the selected user.

### 5. Save to file
Saves the current social network data into a text file.

### 6. Retrieve data from file
Loads social network data from a text file and rebuilds the linked list.

### 7. Exit
Ends the program.

### 8. Print all users (debug)
Prints all users in alphabetical order.  
This option is mainly used for testing and debugging.

---

## Data Structure

Each user is stored in the following structure:

```c
struct person {
    char name[MAX_NAME];
    char friends[MAX_FRIENDS][MAX_NAME];
    int friend_count;
    struct person* next;
};
