## COL106 Long Assignment 2 - SocialNet Simulator

## Overview

**SocialNet Simulator** is a command-line social network backend built in **C++** as my submission for the second long assignment of the **COL106: Data Structures and Algorithms** course at IIT Delhi.

It’s a prototype simulation of a social networking platform — where you can create users, connect them as friends, and let them share posts — all implemented by custom-implementations of **Graphs** and **AVL Trees**.

Friendships are modeled as edges in an undirected graph, while each user’s posts are stored and retrieved efficiently using a self-balanced AVL Tree.

---

## Key Features

* **User and Friendship Management:** Add users and create bidirectional friendships similar to real world social networks.
* **Friend Suggestions:** Get friend recommendations ranked by the number of mutual friends, and alphabetically in case of ties.
* **Degrees of Separation (DOS):** Find how many friendship links separate two users using BFS algorithm.
* **Post Management:** Add posts and display them in reverse chronological order.
* **Case-Insensitive System:** All usernames and post contents are treated in a case-insensitive way.
* **Error-Resilient Design:** Handles invalid inputs and edge cases carefully.

---

## Purpose

This project was built to:

* Get a detailed implementation of **Graphs** and **AVL Trees** data structures from scratch.
* Learn how real-world systems work using fundamental data structures.
* Practice and get a good grasp of efficient searching, sorting, and traversal algorithms.
* Write robust, readable, and maintainable code for run-time command inputs.

---

## Setup and Compilation

### Requirements

* C++17 or newer (g++ 7.0+)
* Any terminal or command-line environment.

### Files

| File         | Description                                                  |
| ------------ | ------------------------------------------------------------ |
| `main.cpp`   | Handles input parsing and command execution.                 |
| `graph.hpp`  | Contains the user and social network (graph) implementation. |
| `avl.hpp`    | Implements the AVL Tree for storing and retrieving posts.    |
| `compile.sh` | Simple shell script to compile all files.                    |
* **Make sure all of the above files are in the same directory and then run the following commands in a terminal environment**
```sh
#Grant Execution Permission
>chmod +x compile.sh

# Compile
./compile.sh

# Run the executable
./start
```

### Example Interaction

```
ADD_USER Budhya
ADD_USER GARV
ADD_FRIEND Budhya Garv
ADD_POST Budhya Hello World!
OUTPUT_POSTS Budhya 1
DEGREES_OF_SEPARATION Budhya Garv
```

```bash
Output:
User named 'Budhya' was added.
User named 'Garv' was added.
Budhya & Garv are now friends!
Budhya added a new post!
Most Recent posts of BUdhya are listed:
Hello World!
1
```
---

## System Design

### 1. Graph Structure (`graph.hpp`)

The core network is an undirected graph:

* Each **user** is a vertex.
* Each **friendship** is an edge connecting two users.

| Component             | Data Structure                 | Description                                      |
| --------------------- | ------------------------------ | ------------------------------------------------ |
| User Storage          | `unordered_map<string, User*>` | Stores all users (case-insensitive keys).        |
| Friend List           | `vector<string>`               | Each user’s friends, kept alphabetically sorted. |
| Friend Suggestion     | Custom sorting algorithm       | Ranks by mutual friend count, then name.         |
| Degrees of Separation | Breadth-First Search           | Finds the shortest connection path.              |

---

### 2. AVL Tree for Posts (`avl.hpp`)

Each user’s posts are stored in their own AVL Tree, sorted by a global timestamp.

| Feature   | Description                                                     |
| --------- | --------------------------------------------------------------- |
| Ordering  | Each post is assigned a timestamp to ensure proper order.       |
| Balancing | Supports all rotations (LL, RR, LR, RL) for O(logN) insertion. |
| Retrieval | Reverse in-order traversal displays the newest posts first.     |

---

## Command Reference

### Network Commands

| Command                           | Example                               | Description                                  |
| --------------------------------- | ------------------------------------- | -------------------------------------------- |
| `ADD_USER <username>`             | `ADD_USER Alice`                      | Adds a new user.                             |
| `ADD_FRIEND <u1> <u2>`            | `ADD_FRIEND Alice Bob`                | Creates a friendship link between two users. |
| `LIST_FRIENDS <username>`         | `LIST_FRIENDS Alice`                  | Lists all friends alphabetically.            |
| `SUGGEST_FRIENDS <username> <N>`  | `SUGGEST_FRIENDS Alice 5`             | Suggests up to N friends based on number of mutual friends.   |
| `DEGREES_OF_SEPARATION <u1> <u2>` | `DEGREES_OF_SEPARATION Alice Charlie` | Calculates the shortest connection path by comparing friendships graph.     |
| `EXIT` |  | Stops the code(You can also use ctrl+C to exit the code)     |

### Post Commands

| Command                           | Example                          | Description                                        |
| --------------------------------- | -------------------------------- | -------------------------------------------------- |
| `ADD_POST <username> <content>` | `ADD_POST Alice Good morning!` | Adds a new post.                                   |
| `OUTPUT_POSTS <username> <N>`     | `OUTPUT_POSTS Alice 3`           | Displays the most recent N posts (`N=-1` for all). |

---
## Assumptions and Specifications
I have included all the assumptions and the specifications made by me for the assignment here
| Case                   |Specification                                   |
| ---------------------- | ------------------------------------------------ |
| Empty Post         | Not allowed, will give an error.               |
| Case Sensitivity         | My code converts all usernames and post contents to lower case letters. So after creation original case structured cannot be retrieved. |
| Friend Lists | Lists all friends by alphabetical order. As empty string names are not allowed and all names are lower case and unique there is no ambiguity in ordering.               |
| Self-Friendship        | Users cannot add themselves as friends.|
| Suggest Friends | N = 0 is allowed but outputs nothing. Orders suggestions using number of mutual friends and ties are decided by alphabetical order.  |
| Degrees of Separation | Outputs 0 for referencing self as a friend. Outputs -1 if the two users connection path.     |
| Output Posts            | For N = 0 ouputs nothing. For N = -1 outputs all posts made by the user.                |
## Error Handling

| Case                   | Output Message                                   |
| ---------------------- | ------------------------------------------------ |
| Empty Username         | `Error: Username cannot be empty.`               |
| Duplicate User         | `Error: User with a similar name already exists` |
| Missing User           | `Error: User not found: <username>`              |
| Self-Friendship        | `Error: Cannot add self as a friend`             |
| Already Friends        | `Error: <u1> and <u2> are already friends.`      |
| Invalid Friend Command | `Error: Usage: ADD FRIEND <user1> <user2>`       |
| Negative or Invalid N  | `Error: Please enter a valid number for N.`      |
| No Friends             | `Friend list of <user> is empty.`                |
| No Suggestions         | `No friend suggestions available for <user>.`    |
| Missing Post User      | `Error: User not found: <username>`              |
| Invalid Post Request   | `Error: Please enter a valid number for N.`      |

The system never crashes on bad input — every invalid operation is caught and handled carefully with an error message.

---

## Review Summary

### Strengths

* Clean and well-structured integration of **Graphs** and **AVL Trees**.
* Fast O(1) user lookup using hash maps.
* Friend lists always stay alphabetically sorted.
* Friend suggestions correctly prioritize mutuals and handle ties.
* Strong input validation and error recovery for every command.

### Possible Improvements

| Area               | Observation                               | Suggestion                                      |
| ------------------ | ----------------------------------------- | ----------------------------------------------- |
| Suggestion Sorting | Uses selection sort (O(K²)).              | Replace with `std::sort` for better efficiency. |
| Case Display       | Currently prints all lowercase usernames. | Store original case for display.                |
| Post Input         | May keep quotation marks around content.  | Strip quotes before storing.                    |

---

## Complexity Overview

| Operation             | Structure                  | Avg. Time    |
| --------------------- | -------------------------- | ------------ |
| User Lookup           | Hash Map (`unordered_map`) | O(1)         |
| Add User              | Hash Insertion             | O(1)         |
| Add Friend            | Sorted Vector Insertion    | O(log F)     |
| List Friends          | Vector Traversal           | O(F)         |
| Add Post              | AVL Insertion              | O(log P)     |
| Output Posts          | Reverse Traversal          | O(N + log P) |
| Degrees of Separation | BFS                        | O(V + E)     |
| Suggest Friends       | Traversal + Sorting        | O(F² + K²)   |

*(F = number of friends, P = posts per user, V = total users, E = friendships, K = suggestion candidates)*

---

## Author

**SocialNet Simulator**
Developed by *Budhyadeb Roy* as part of **COL106 - Data Structures and Algorithms (IIT Delhi)**
*Long Assignment 2: Building a Social Network Backend with Graphs and AVL Trees*.
