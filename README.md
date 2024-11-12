# DSA Hackathon Problem Statement and Solution

## Problem Statement: Social Network Friend Recommendation System

Create a program to manage a social network of users, where users can establish and query connections, find new friends based on shared contacts, and access various functionalities.

## Team Members

| SRN                | Name                             |
|--------------------|----------------------------------|
| PES1UG23CS166      | Chinmay Shivanand Muragod        |
| PES1UG23CS167      | Chirag K M                       |
| PES1UG23CS172      | Darshith M S                     |

### Functionalities:

#### 1. Display Network Structure:
   - **Input**: `print_network`
   - **Output**: Display all users and their connections.
   
#### 2. List Friends of a User:
   - **Input**: `list_friends <user>`
   - **Output**: List all friends of the specified `<user>`.


#### 3. Find Mutual Friends:
   - **Input**: `mutual_friends <user1> <user2>`
   - **Output**: Display mutual connections between `<user1>` and `<user2>`.


#### 4. Find Possible Friends (Recommendations):
   - **Input**: `recommend_friends <user> <degree>`
   - **Output**: Suggest friends for `<user>` by finding users connected within `<degree>` levels (e.g., friends of friends).
   - **Example**: 

#### 5. Identify Popular Users:
   - **Input**: `most_popular`
   - **Output**: List users based on the number of their connections, in descending order.

#### 6. Find Shortest Path Between Users:
   - **Input**: `shortest_path <user1> <user2>`
   - **Output**: Display the shortest path from `<user1>` to `<user2>` if it exists, showing the sequence of connections.


### Constraints:
- The network's structure should be provided as an initial input.
- The program should handle cases where no connection exists between users.
- The solution should manage and query connections efficiently.

---


### Main Menu:
1. `create_user`: Creates a user.
2. `add_friend`: Adds a friend to a user.
3. `print_network`: Displays all users and their connections.
4. `list_friends`: Lists all friends of a specified user.
5. `mutual_friends`: Displays mutual connections between two users.
6. `recommend_friends`: Suggests friends for a user within a specified degree.
7. `most_popular`: Lists users based on the number of their connections.
8. `shortest_path`: Displays the shortest path between two users.
9. `clear`: Clears the console.
10. `exit`: Exits the program.

---
