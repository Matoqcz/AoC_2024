#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int compare_ints(const void *a, const void *b) {
        return (*(int *)a - *(int *)b);
}

int calculate_total_distance(int left[], int right[], size_t size) {
        int result = 0;
        for (size_t i = 0; i < size; i++) {
                result += abs(left[i] - right[i]);
        }
        return result;
}

void populate_similarity_array(int left[], int right[], size_t size, int similarity_array[]) {
        for(int i = 0; i < size; i++){
                int count = 0;
                for(int j = 0; j < size; j++){
                        if(right[j] == left[i]){
                                count += 1;
                        }
                        if(right[j] < left[i]){
                                continue;
                        }
                        if(right[j] > left[i]){
                                break;
                        }
                }
                similarity_array[i] = count;
        }
}

int calculate_similarity(int left[], size_t size, int similarity_array[]) {
        int result = 0;
        for(int i =0; i < size; i++){
                result += left[i] * similarity_array[i];
        }
        return result;
}

int main(){

        FILE* fp =  fopen("./input.txt", "r");
        if(fp == NULL){
                exit(EXIT_FAILURE);
        }

        // String input buffer
        char buffer[255];

        //Left buffer
        int left_buffer[1200];

        //Right buffer
        int right_buffer[1200];

        size_t curr = 0; // Current locations buffer index
        while(fgets(buffer, sizeof(buffer), fp) != NULL){


                char *token = strtok(buffer, " ");
                if(token != NULL){
                        int temp = atoi(token);
                        left_buffer[curr] = temp;

                        token = strtok(NULL, " ");
                        if(token != NULL){
                                int temp = atoi(token);
                                right_buffer[curr] = temp;
                        } else {
                                printf("Malformed string, second token not found");
                                exit(EXIT_FAILURE);
                        }
                }
                curr ++;
        }

        fclose(fp);

        qsort(left_buffer, curr, sizeof(int), compare_ints);
        qsort(right_buffer, curr, sizeof(int), compare_ints);


        for (int i = 0; i < curr; i++){
                printf("Index %d : %d | %d\n", i, left_buffer[i], right_buffer[i]);
        }

        int result = calculate_total_distance(left_buffer, right_buffer, curr);
        printf("Total distance is: %d\n", result);

        int similarity_ar[curr];

        populate_similarity_array(left_buffer, right_buffer, curr, similarity_ar);

        for(int i = 0; i < curr; i++){
                printf("Similarity for index %d = %d\n", i, similarity_ar[i]);
        }

        int similarity_result = calculate_similarity(left_buffer, curr, similarity_ar);
        printf("Similarity result: %d\n", similarity_result);

        return 0;
}