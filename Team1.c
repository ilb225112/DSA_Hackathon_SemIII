//==========================        HEADERS         ================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>            //for color change



//================  STRUCTURE declarations     ======================================
struct User {
    char name[50];                   
    int degree;                                        // Number of friends
    struct User* friends[12];                          // List of friends (adjacency list)
};
typedef struct User USERNODE;        


struct Network {
    USERNODE** users;                
    int total;                       // Total number of users
    int capacity;                    
};
typedef struct Network NETWORK;      


//======================        PROTOTYPES          ==================================
void changeColor(int color);
USERNODE* create_user(NETWORK*, char*);
void add_friend(USERNODE* user1, USERNODE* user2);
void print_network(NETWORK*);

USERNODE* find_user(NETWORK*, char* name);
void list_friends(NETWORK*, char* name);

void mutual_friends(NETWORK*, char* name1, char* name2);

int is_visited(USERNODE *visited[], int count, USERNODE *user);
void recommend_friends(NETWORK *network, char *name, int degree);

void most_popular(NETWORK*);
void shortest_path(NETWORK *network, char *name1, char *name2);
void free_network(NETWORK*);
//=================================================================================



int main() {
    int choice;
    NETWORK network = {0};
    char name[50];
    char user1[50], user2[50];

    network.users = (USERNODE **)malloc(sizeof(USERNODE *) * 12);  
    network.capacity = 12;    //set total no. of nodes

    //=====================================                 MAIN MENU                 ==============================================================================
    changeColor(14);
    printf("1.create_user          : Creates a user\n");
    printf("2.add_friend           : Add friend to a user\n");
    printf("3.print_network        : Display all users and their connections\n");
    printf("4.list_friends         : List all friends of the specified user\n");
    printf("5.mutual_friends       : Display mutual connection between two friends\n");
    printf("6.recommend_friends    : Suggest friends for a user by finding users connected within degree levels\n");
    printf("7.most_popular         : List users based on the number of their connections, in descending order.\n");
    printf("8.shortest_path        : Display the shortest path from <user1> to <user2> if it exists, showing the sequence of  connections.\n");
    printf("9.clear \n");
    printf("10.exit\n");
    changeColor(7);
    //===============================================================================================================================================================

    while(1){
        printf("Enter the choice : ");
        scanf("%d", &choice);

        switch(choice) 
        {
            case 1: {
                printf("Enter user name: ");
                scanf("%s", name);

                if (create_user(&network, name) != NULL) {
                    printf("User '%s' created successfully.\n", name);
                } else {
                    printf("Failed to create user '%s'.\n", name);
                }
            } break;

            case 2: {
                printf("Enter name of user 1: ");
                scanf("%s", user1);

                printf("Enter name of user 2: ");
                scanf("%s", user2);

                USERNODE* u1 = NULL;
                USERNODE* u2 = NULL;

                for (int i = 0; i < network.total; i++) {
                    if (strcmp(network.users[i]->name, user1) == 0) {
                        u1 = network.users[i];
                    }
                    if (strcmp(network.users[i]->name, user2) == 0) {
                        u2 = network.users[i];
                    }
                }

                if (u1 == NULL || u2 == NULL) {
                    printf("One or both users not found in the network.\n");
                } else {
                    add_friend(u1, u2);
                    printf("Users '%s' and '%s' are now friends!\n", user1, user2);
                }
            } break;


            case 3: {
                print_network(&network);
            } break;


            case 4:{
                printf("Enter the name of the user: ");
                scanf("%s", name);
                list_friends(&network, name);
            }break;


            case 5:{
                printf("Enter the name of the first user: ");
                scanf("%s", user1);

                printf("Enter the name of the second user: ");
                scanf("%s", user2);

                mutual_friends(&network, user1, user2);
            }break;


            case 6:{
                printf("Enter the name of the user: ");
                scanf("%s", name);

                int degree;
                printf("Enter the degree level for recommendations: ");
                scanf("%d", &degree);

                recommend_friends(&network, name, degree);
            }break;


            case 7:{
                most_popular(&network);
            }break;


            case 8:{
                printf("Enter the name of the first user: ");
                scanf("%s", user1);

                printf("Enter the name of the second user: ");
                scanf("%s", user2);

                shortest_path(&network, user1, user2);
            }break;


            case 9: {
                system("cls");
                break;
            }


            case 10:
                free_network(&network);  
                exit(0);


            default:
                printf("Invalid Choice\n");
        }
    }
    return 0;
}


//=====================================         FUNCTION DEFINITIONS        ==========================================================

void changeColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


USERNODE* create_user(NETWORK* network, char* name) {
    USERNODE* newnode = (USERNODE*)malloc(sizeof(USERNODE));
    strcpy(newnode->name, name);
    newnode->degree = 0;

    network->users[network->total++] = newnode;  
    return newnode;
}

void add_friend(USERNODE* user1, USERNODE* user2) {
    //for undirected network
    user1->friends[user1->degree++] = user2;
    user2->friends[user2->degree++] = user1;
}

void print_network(NETWORK *network) {
    for (int i = 0; i < network->total; i++) 
    {
        USERNODE *temp = network->users[i];
        printf("%s : ", temp->name);

        for (int j = 0; j < temp->degree; j++) 
        {
            printf(" %s", temp->friends[j]->name);
            if (j < temp->degree - 1) printf(",");  
        }
        printf("\n");
    }
}


USERNODE* find_user(NETWORK* network, char* name) {
    for (int i = 0; i < network->total; i++) {
        if (strcmp(network->users[i]->name, name) == 0) {
            return network->users[i];
        }
    }
    return NULL; // if not found
}

void list_friends(NETWORK* network, char* name) {
    USERNODE* temp = find_user(network, name);
    if (temp == NULL) {
        printf("User %s not found.\n", name);
        return;
    }
    
    printf("Friends of %s:\n", temp->name);
    for (int i = 0; i < temp->degree; i++) {
        printf("- %s\n", temp->friends[i]->name);
    }
}


void mutual_friends(NETWORK* network, char* name1, char* name2) {
    USERNODE* user1 = find_user(network, name1);
    USERNODE* user2 = find_user(network, name2);

    if (user1 == NULL || user2 == NULL) {
        printf("One of them ore both not founs .\n");
        return;
    }

    printf("Mutual friends between %s and %s:\n", user1->name, user2->name);
    int found = 0;
    for (int i = 0; i < user1->degree; i++) {
        for (int j = 0; j < user2->degree; j++) {
            if (user1->friends[i] == user2->friends[j]) {
                printf("- %s\n", user1->friends[i]->name);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("No mutual friends found.\n");
    }
}


int is_visited(USERNODE *visited[], int count, USERNODE *user) {
    for (int i = 0; i < count; i++) {
        if (visited[i] == user) {
            return 1;
        }
    }
    return 0;
}

void recommend_friends(NETWORK *network, char *name, int degree) {
    USERNODE *start = find_user(network, name);
    if (start == NULL) {
        printf("User %s not found in the network.\n", name);
        return;
    }
    
    USERNODE *visited[10] = {NULL};
    int visited_count = 0;
    USERNODE *queue[10];
    int level[10] = {0};  // To track the degree level of each user in the queue
    int front = 0, rear = 0;

    // Enqueue the start user
    queue[rear] = start;
    level[rear] = 0;
    rear++;
    visited[visited_count++] = start;

    printf("Friend recommendations for %s at exactly %d levels:\n", name, degree);
    int found_recommendations = 0;

    while (front < rear) {
        USERNODE *current = queue[front];
        int current_level = level[front];
        front++;

        if (current_level >= degree) {
            continue;
        }

        for (int i = 0; i < current->degree; i++) {
            USERNODE *friend = current->friends[i];

            if (!is_visited(visited, visited_count, friend)) {
                queue[rear] = friend;
                level[rear] = current_level + 1;
                rear++;
                visited[visited_count++] = friend;

                if (current_level + 1 == degree) {
                    printf("- %s\n", friend->name);
                    found_recommendations = 1;
                }
            }
        }
    }

    if (!found_recommendations) {
        printf("No recommendations found at exactly %d levels.\n", degree);
    }
}



void most_popular(NETWORK* network) {
    if (network->total == 0) {
        printf("No users in the network.\n");
        return;
    }

    int max_degree = -1;

    //find maxdegree
    for (int i = 0; i < network->total; i++) {
        if (network->users[i]->degree > max_degree) {
            max_degree = network->users[i]->degree;
        }
    }


    printf("Most popular users (with %d connections):\n", max_degree);
    for (int i = 0; i < network->total; i++) {
        if (network->users[i]->degree == max_degree) {
            printf("- %s\n", network->users[i]->name);
        }
    }
}

void shortest_path(NETWORK* network, char *user1, char *user2) {
    if (strcmp(user1, user2) == 0) {
        printf("Same user entered, no path for the same user\n");
        return;
    }

    int index1 = -1, index2 = -1;
 
    for (int i = 0; i < network->total; i++) {
        if (strcmp(network->users[i]->name, user1) == 0) {
            index1 = i;
        }
        if (strcmp(network->users[i]->name, user2) == 0) {
            index2 = i;
        }
    }


    if (index1 == -1 || index2 == -1) {
        printf("One or both users not found in the network.\n");
        return;
    }

    int visited[network->capacity];   
    int parent[network->capacity];   

    for (int i = 0; i < network->capacity; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    int queue[network->capacity];
    int front = 0, rear = 0;

    // Start BFS from index1
    queue[rear++] = index1;
    visited[index1] = 1;

    // BFS Loop
    while (front < rear) {
        int current_index = queue[front++];
        
        // Stop if we reach the target user
        if (current_index == index2) break;

        USERNODE* current_user = network->users[current_index];

        for (int j = 0; j < current_user->degree; j++) {
            USERNODE* friend = current_user->friends[j];
            int friend_index = -1;

            // Find index of the friend
            for (int k = 0; k < network->total; k++) {
                if (network->users[k] == friend) {
                    friend_index = k;
                    break;
                }
            }

            if (friend_index != -1 && !visited[friend_index]) {
                queue[rear++] = friend_index;
                visited[friend_index] = 1;
                parent[friend_index] = current_index;
            }
        }
    }

    // Check if a path was found
    if (!visited[index2]) {
        printf("No path exists between %s and %s\n", user1, user2);
        return;
    }

    // Trace the path from end to start
    int path[network->capacity];
    int path_length = 0;
    for (int at = index2; at != -1; at = parent[at]) {
        path[path_length++] = at;
    }

    printf("Shortest path from %s to %s:\n", user1, user2);
    for (int i = path_length - 1; i >= 0; i--) {
        printf("%s", network->users[path[i]]->name);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

void free_network(NETWORK* network) {
    for (int i = 0; i < network->total; i++) {
        free(network->users[i]);  // Free memory for each user
    }
    free(network->users);  // Free memory for the users array
}
