#include<stdio.h>
#include<stdlib.h>

#define MAX_LINES 1048576 // 2^20
#define MAX_WIDTH 1048576 // 2^20
#define MAX_FILE_PATH 255 // longest path a file can have

FILE* file;

void clear_screen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__) || defined(__APPLE__)
        clear_screen();
    #else
        printf("Cannot clear the terminal for this OS.\n");
    #endif
}

int Remove(char* path){
    int ret = remove(path);
    if (ret != 0){
        printf("ERROR: File does not exist.\n");
    }
    printf("File removed.\n");
    return ret;
}

int editFile(char* path){
    file = fopen(path, "r+");
    if (file==NULL){
        printf("ERROR: File does not exist.\n");
        return 2;
    }

    int c = fgetc(file);
    while (c!=EOF){
        putchar(c);
        c = fgetc(file);
    }

    fseek(file, -1, SEEK_END);
    char* string = (char*)malloc(MAX_WIDTH*sizeof(char));
    if (string==NULL){
        printf("ERROR: Memory allocation failure.\n");
        return 1;
    }
    for (int i=0; i<MAX_LINES; i++){
        while (1){
            if (fgets(string, MAX_WIDTH, stdin) != NULL){
                if (string[0] == '~' && string[1] == '\n'){
                    printf("Saving file...\n");
                    free(string);
                    fclose(file);
                    return 0;
                }else{
                    fprintf(file, "%s", string);
                }
            }
        }
    }
}

int writeFile(char* path){
    file = fopen(path, "w");
    if (file == NULL){
        printf("ERROR: File creation failed.\n");
        return 2;
    }
    fseek(file, 0, SEEK_END);
    char* string = (char*)malloc(MAX_WIDTH*sizeof(char));
    if (string==NULL){
        printf("ERROR: Memory allocation failure.\n");
        return 1;
    }
    for (int i=0; i<MAX_LINES; i++){
        while (1){
            if (fgets(string, MAX_WIDTH, stdin) != NULL){
                if (string[0] == '~' && string[1] == '\n'){
                    printf("Saving file...\n");
                    free(string);
                    fclose(file);
                    return 0;
                }else{
                    fprintf(file, "%s", string);
                }
            }
        }
    }
}

int readFile(char* path){
    file = fopen(path, "r");
    if (file==NULL){
        printf("ERROR: File does not exist.\n");
        return 2;
    }

    int c = fgetc(file);

    while (c != EOF){
        putchar(c);
        c = fgetc(file);
    }
    printf("\n--------------------------------------\n");
    printf("\t1- Edit file\n");
    printf("\t2- Close file\n");
    int action=0;
    while (action<=0 || action>2){
        printf("Action: ");
        scanf("%d", &action);
    }
    switch (action){
        case 1:
            clear_screen();
            editFile(path);
            break;
        case 2:
            fclose(file);
            break;
    }
    return 0;
}

int newFile(char* path){
    clear_screen();
    int ret;
    ret = writeFile(path);

    if (ret==0){
        printf("File saved succesfully.\n");
    }
    return ret;
}

int openFile(char* path){
    clear_screen();
    return readFile(path);
}

void Menu(){
    printf("\t\tEon Editor\n");
    printf("\t1- New\n");
    printf("\t2- Open\n");
    printf("\t3- Edit\n");
    printf("\t4- Delete\n");
    printf("\t5- Quit\n");
    int action=0;
    while (action<=0 || action>5){
        printf("Action: ");
        scanf("%d", &action);
    }
    char* filePath = (char*)malloc(MAX_FILE_PATH*sizeof(char));
    switch (action){
        case 1:
            filePath = (char*)malloc(MAX_FILE_PATH*sizeof(char));
            printf("\nFile name with extension: ");
            scanf("%s", filePath);
            clear_screen();
            newFile(filePath);
            free(filePath);
            break;
        case 2:
            filePath = (char*)malloc(MAX_FILE_PATH*sizeof(char));
            printf("\nFile name with extension: ");
            scanf("%s", filePath);
            clear_screen();
            openFile(filePath);
            free(filePath);
            break;
        case 3:
            filePath = (char*)malloc(MAX_FILE_PATH*sizeof(char));
            printf("\nFile path with extension: ");
            scanf("%s", filePath);
            clear_screen();
            editFile(filePath);
            free(filePath);
            break;
        case 4:
            filePath = (char*)malloc(MAX_FILE_PATH*sizeof(char));
            printf("\nFile path with extension: ");
            scanf("%s", filePath);
            clear_screen();
            Remove(filePath);
            free(filePath);
            break;
        case 5:
            printf("Quitting...\n");
            exit(0);
            break;
    }
    Menu();
}

int main(){
    while(1){
        Menu();
    }
    return 0;
}
