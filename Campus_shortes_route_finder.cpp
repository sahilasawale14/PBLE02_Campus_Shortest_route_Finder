#include <stdio.h>

#define MAX 20
#define INF 99999

int graph[MAX][MAX];
int n;
char locations[MAX][50];

int distance[MAX];
int visited[MAX];
int parent[MAX];

int source = -1;
int calculated = 0;

int main()
{
    int choice;

    printf("========== CAMPUS SHORTEST ROUTE FINDER ==========\n");

    do
    {
        printf("\n");
        printf("1. Enter Campus Graph\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Select Source Location\n");
        printf("4. Find Shortest Distance\n");
        printf("5. Display Shortest Paths\n");
        printf("6. Display Distance from Source to All Locations\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);


        /* 1. Enter Campus Graph */
        if (choice == 1)
        {
            printf("\nEnter no of locations: ");
            scanf("%d", &n);

            for (int i = 0; i < n; i++)
            {
                printf("Enter location %d: ", i + 1);
                scanf(" %[^\n]", locations[i]);
            }

            printf("\nEnter distances between locations.\n");
            printf("Enter 0 if there is no direct connection.\n");

            for (int i = 0; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    int distance;

                    printf("\nDistance from %s to %s: ",
                           locations[i], locations[j]);

                    scanf("%d", &distance);

                    if (distance == 0)
                    {
                        graph[i][j] = INF;
                        graph[j][i] = INF;
                    }
                    else
                    {
                        graph[i][j] = distance;
                        graph[j][i] = distance;
                    }
                }
            }

            for (int i = 0; i < n; i++)
            {
                graph[i][i] = 0;
            }

            source = -1;
            calculated = 0;

            printf("\nCampus graph entered successfully!\n");
        }


        /* 2. Display Adjacency Matrix */
        else if (choice == 2)
        {
            if (n == 0)
            {
                printf("\nPlease enter campus graph first.\n");
            }
            else
            {
                printf("\n========== ADJACENCY MATRIX ==========\n\n");

                for (int i = 0; i < n; i++)
                {
                    printf("%s\t", locations[i]);
                }

                printf("\n");

                for (int i = 0; i < n; i++)
                {
                    printf("%s\t", locations[i]);

                    for (int j = 0; j < n; j++)
                    {
                        if (graph[i][j] == INF)
                        {
                            printf("INF\t");
                        }
                        else
                        {
                            printf("%d\t", graph[i][j]);
                        }
                    }

                    printf("\n");
                }
            }
        }


        /* 3. Select Source Location */
        else if (choice == 3)
        {
            if (n == 0)
            {
                printf("\nPlease enter campus graph first.\n");
            }
            else
            {
                printf("\n========== SELECT SOURCE LOCATION ==========\n");

                for (int i = 0; i < n; i++)
                {
                    printf("%d. %s\n", i + 1, locations[i]);
                }

                int choice2;

                printf("\nEnter source location number: ");
                scanf("%d", &choice2);

                if (choice2 >= 1 && choice2 <= n)
                {
                    source = choice2 - 1;
                    calculated = 0;

                    printf("\nSource selected: %s\n",
                           locations[source]);
                }
                else
                {
                    printf("\nInvalid location number.\n");
                }
            }
        }


        /* 4. Find Shortest Distance */
        else if (choice == 4)
        {
            if (source == -1)
            {
                printf("\nPlease select source location first.\n");
            }
            else
            {
                /* Initialize Dijkstra */
                for (int i = 0; i < n; i++)
                {
                    distance[i] = INF;
                    visited[i] = 0;
                    parent[i] = -1;
                }

                distance[source] = 0;


                /* Dijkstra Algorithm */
                for (int count = 0; count < n - 1; count++)
                {
                    int min = INF;
                    int u = -1;

                    /* Find nearest unvisited location */
                    for (int i = 0; i < n; i++)
                    {
                        if (visited[i] == 0 &&
                            distance[i] < min)
                        {
                            min = distance[i];
                            u = i;
                        }
                    }

                    if (u == -1)
                    {
                        break;
                    }

                    visited[u] = 1;


                    /* Update distances */
                    for (int v = 0; v < n; v++)
                    {
                        if (visited[v] == 0 &&
                            graph[u][v] != INF &&
                            distance[u] + graph[u][v] < distance[v])
                        {
                            distance[v] =
                                distance[u] + graph[u][v];

                            parent[v] = u;
                        }
                    }
                }

                calculated = 1;

                printf("\n========== SHORTEST DISTANCES ==========\n");

                for (int i = 0; i < n; i++)
                {
                    if (distance[i] == INF)
                    {
                        printf("%s : INF\n",
                               locations[i]);
                    }
                    else
                    {
                        printf("%s : %d\n",
                               locations[i],
                               distance[i]);
                    }
                }
            }
        }


        /* 5. Display Shortest Paths */
        else if (choice == 5)
        {
            if (source == -1)
            {
                printf("\nPlease select source location first.\n");
            }
            else if (calculated == 0)
            {
                printf("\nPlease select option 4 first to find shortest distances.\n");
            }
            else
            {
                printf("\n========== SHORTEST PATHS ==========\n");

                for (int i = 0; i < n; i++)
                {
                    if (i == source)
                    {
                        continue;
                    }

                    printf("\n%s: ", locations[i]);

                    if (distance[i] == INF)
                    {
                        printf("No path");
                    }
                    else
                    {
                        int path[MAX];
                        int count = 0;
                        int current = i;

                        while (current != -1)
                        {
                            path[count] = current;
                            count++;
                            current = parent[current];
                        }

                        for (int j = count - 1; j >= 0; j--)
                        {
                            printf("%s", locations[path[j]]);

                            if (j != 0)
                            {
                                printf(" -> ");
                            }
                        }

                        printf("  (Distance = %d)",
                               distance[i]);
                    }
                }

                printf("\n");
            }
        }


        /* 6. Display Distance from Source to All Locations */
        else if (choice == 6)
        {
            if (source == -1)
            {
                printf("\nPlease select source location first.\n");
            }
            else if (calculated == 0)
            {
                printf("\nPlease select option 4 first to find shortest distances.\n");
            }
            else
            {
                printf("\n========== DISTANCE FROM SOURCE ==========\n");

                printf("Source: %s\n\n",
                       locations[source]);

                for (int i = 0; i < n; i++)
                {
                    if (distance[i] == INF)
                    {
                        printf("%s : INF\n",
                               locations[i]);
                    }
                    else
                    {
                        printf("%s : %d\n",
                               locations[i],
                               distance[i]);
                    }
                }
            }
        }


        /* 7. Exit */
        else if (choice == 7)
        {
            printf("\nThank you for using Campus Shortest Route Finder!\n");
        }


        /* Invalid choice */
        else
        {
            printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 7);


    return 0;
}
