#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void chat_clear(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
typedef struct{
    char name[20];
    long long int ip;
}devinfo;
void screen(){
    long long int tm;
    time_t t = time(NULL);
    tm = t;
    printf("----------------------------------\n");
    printf("Photon Pulse Shell\n");
    printf("%d\n", tm);
    printf("----------------------------------\n");
}
void info(int a){
    static devinfo device = {"user", 182133124025};
    if(a == 1){
        printf("New device name: ");
        if(fgets(device.name, sizeof(device.name), stdin)!=NULL){
            device.name[strcspn(device.name, "\r\n")] = 0;
        }

        printf("Sucsessful!\n");
    }else if(a == 2){
    printf("Device name:%s\nDevice IP:%lld", device.name, device.ip);
    }
}
void savehistory(const char* cmd){
    if(strlen(cmd)==0) return;
    FILE* fptr;
    fptr= fopen("C:\\Users\\HP\\Desktop\\database\\history.txt","a");
    if(fptr !=NULL){
        fprintf(fptr,"%s\n",cmd);
        fclose(fptr);
    }
}
void filesearch(){
    char path[200];
    char command[250];
    printf("Path: ");
    if(fgets(path, sizeof(path), stdin) !=NULL){
        path[strcspn(path, "\n")] = 0;
    }
   #ifdef _WIN32
   snprintf(command, sizeof(command), "dir \"%s\"", path);
   #else
   snprintf(command, sizeof(command), "ls -la \"%s\"", path);
   #endif // search
   system(command);
}
void fileread(){
    char path[100];
    char line[1024];
    printf("Path: ");
    if(fgets(path, sizeof(path), stdin) !=NULL){
        path[strcspn(path, "\n")] = 0;
}
    FILE* fptr;
    fptr = fopen(path,"r");
    if(fptr == NULL){
        printf("WRONG\n");
        return;
    }
    while(fgets(line, sizeof(line), fptr) !=NULL){
        printf("%s",line);
    }
    printf("\n\n\n>>Reading finish\n");
    fclose(fptr);
}
void filecreate(){
    char path[100];
    printf("Your crate file is Path: ");
    if(fgets(path, sizeof(path), stdin) !=NULL){
        path[strcspn(path, "\n")] = 0;
}
    FILE* fptr;
    fptr = fopen(path,"w");
    if(fptr == NULL){
        printf("WRONG\n");
        return;
    }
    printf("\n\n\n>>%s is sucsessful create.\n", path);
    fclose(fptr);
}
void filedelete(){
    char path[100];
    printf("Delete files Path: ");
    if(fgets(path, sizeof(path), stdin) !=NULL){
        path[strcspn(path, "\n")] = 0;
}
    if(remove(path)==0){
        printf("%s delete is sucsessful.\n",path);
    }else{
        printf("WRONG\n");
    }
}
void readhistory(){
    char line[512];
    int count = 1;
    FILE* fptr= fopen("C:\\Users\\HP\\Desktop\\database\\history.txt","r");
    if(fptr == NULL){
        printf("Wrong not have file\n");
        return;
    }
    printf("\t\tCOMMAND HISTORY\t\t\n");
    while(fgets(line,sizeof(line),fptr) !=NULL){
        printf("%d. %s",count++,line);
    }
    printf("\t\tFINISH\t\t\n");
    fclose(fptr);
}
void sysinfo(){
    printf("\t YOUR SYSTEM INFO\t\n");
    #ifdef _WIN32
        system("systeminfo | findstr /B /C:\"OS Name\" /C:\"OS Version\" /C:\"System Model\" /C:\"Total Physical Memory\"");
        system("powershell -Command \"Get-CimInstance Win32_Processor | Select-Object -ExpandProperty Name\"");
        system("powershell -Command \"Get-CimInstance Win32_VideoController | Select-Object -ExpandProperty Name\"");
    #else
        system("uname -srm && lscpu | grep 'Model name' && free -h | grep 'Mem:' && lspci | grep -i vga");
    #endif
    printf("\t---FINISH---\t\n");
}
int main(){
    char input[100];
    screen();
    while (1){
        printf("\nPP Shell >> ");
        if(fgets(input, sizeof(input), stdin)!= NULL){
            input[strcspn(input, "\r\n")] = 0;
            savehistory(input);
        }
        if(strcmp(input,"exit")==0 || strcmp(input,"close")==0){
            printf("Your make shell exit or close!\n");
            break;
        }else if(strcmp(input,"help")==0){
            printf("You enter the commands:\n *exit or close\n *help\n *search\n *clear\n *setinfo\n *info\n *read\n *create\n *delete(file)\n *history\n *sysinfo\n");
        }else if(strcmp(input,"clear")==0){
            chat_clear();
            screen();
        }else if(strcmp(input, "setinfo")==0){
            info(1);
        }else if(strcmp(input, "info")==0){
            info(2);
        }else if(strcmp(input, "search")==0){
            filesearch();
        }else if(strcmp(input, "read")==0){
                 fileread();
                 }
        else if(strcmp(input, "create")==0){
                 filecreate();
                 }
        else if(strcmp(input, "delete")==0){
                 filedelete();
                 }
        else if(strcmp(input, "history")==0){
                 readhistory();
                 }
        else if(strcmp(input, "sysinfo")==0 || strcmp(input, "systeminfo")==0){
                 sysinfo();
                 }
    }
}

