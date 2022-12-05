#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*defines*/
#define MAX_NAME_LENGTH 30

/*structures*/
typedef struct list_laps {
    float lap;
    struct list_laps *next;
} list_laps;
typedef struct list_t {
    char name[MAX_NAME_LENGTH];
    int id, numberOfLaps;
    float average_of_laps;
    list_laps *laps;
} athlete;

/*function declaration*/
athlete *readFile(char*, int*);
list_laps *creat_node(float value);
void printList(list_laps*);
float calculate_average_of_laps(list_laps *, int);

int main() {
    athlete *athletes;
    list_laps  *head;
    int choice_num, number_of_athletes;
    float average;
    char file_name[] = "C:\\Users\\asus\\CLionProjects\\lab01_03\\input.txt";
    athletes = readFile(file_name, &number_of_athletes);
    /*for(int i=0; i < number_of_athletes; i++){
        printf("%s %d %d\n", (athletes)[i].name, (athletes)[i].id, (athletes)[i].numberOfLaps);
        printList((athletes)[i].laps);
    }*/

    while(1) {
        printf("Enter your choice number:\n1: list\n2: detail name\n3: best\n4: stop\n");
        scanf("%d", &choice_num);
        switch (choice_num) {
            case 1:
                printf("number of athletes: %d\n", number_of_athletes);
                for (int i = 0; i < number_of_athletes; i++) {
                    printf("name: %s\tidentifier: %d\tnumber of laps: %d\n", (athletes)[i].name, (athletes)[i].id,
                           (athletes)[i].numberOfLaps);
                }
                break;
            case 2:
                printf("Enter the name of the athlete:\n");
                char athlete_name[MAX_NAME_LENGTH];
                scanf("%s", &athlete_name);
                for (int i = 0; i < number_of_athletes; i++) {
                    if (!strcmp((athletes)[i].name, athlete_name)) {
                        printf("%d\n", (athletes)[i].id);
                        printList((athletes)[i].laps);
                    }
                }
                break;
            case 3:
                for(int i = 0; i<number_of_athletes; i++) {
                    head = athletes[i].laps;
                    average = calculate_average_of_laps(head, athletes[i].numberOfLaps);
                    athletes[i].average_of_laps = average;
                }
                float min = athletes[0].average_of_laps;
                int best_athlete_pos;
                for (int i = 0; i < number_of_athletes; i++) {
                    if (athletes[i].average_of_laps < min) {
                        min = athletes[i].average_of_laps;
                        best_athlete_pos = i;
                    }
                }
                printf("best player\nname:%s id:%d\nlaps:\n", (athletes)[best_athlete_pos].name, (athletes)[best_athlete_pos].id);
                printList((athletes)[best_athlete_pos].laps);
                printf("avarage lap: %f\n", athletes[best_athlete_pos].average_of_laps);
                break;
            case 4:
                printf("end of the program!");
                goto out_of_loop;
            default:
                printf("you didn't enter a right number.");
                break;
        }
    }
    out_of_loop:
    free (athletes);

    return (EXIT_SUCCESS);
}

athlete *readFile(char* file_name, int *number_of_athletes){
    FILE *fin = fopen(file_name, "r");
    if (fin == NULL) {
        printf ( "Error opening file.\n");
        exit (0);
    }
    fscanf(fin, "%d", number_of_athletes);
    athlete *array_of_athletes = malloc(*number_of_athletes*sizeof(athlete));
    float lap = 0;
    for(int i=0; i < *number_of_athletes; i++){
        fscanf(fin, "%s %d %d\n", &(array_of_athletes)[i].name, &(array_of_athletes)[i].id, &(array_of_athletes)[i].numberOfLaps);
        list_laps *head = NULL;
        for(int j= 0; j <(array_of_athletes)[i].numberOfLaps; j++){
            fscanf(fin, "%f", &lap);
            (array_of_athletes)[i].laps = creat_node(lap);
            (array_of_athletes)[i].laps->next = head;
            head = (array_of_athletes)[i].laps;
        }
    }
    fclose(fin);
    return array_of_athletes;
}
list_laps *creat_node(float value){
    list_laps *result = malloc(sizeof(list_laps));
    if(result == NULL) {
        printf("error allocating");
        exit(1);
    }
    result->lap = value;
    result->next = NULL;
    return result;
}
void printList(list_laps *head){
    list_laps *temp = head;
    while(temp != NULL){
        printf("%.2f -", temp->lap);
        temp = temp ->next;
    }
    printf("\n");
}
float calculate_average_of_laps(list_laps *head, int number_of_laps){
    float sum = 0;
    list_laps *ptr = head;
    for(int j = 0; j< number_of_laps; j++){
        sum += ptr->lap;
        ptr = ptr->next;
    }
    return (sum/(float)number_of_laps);
}