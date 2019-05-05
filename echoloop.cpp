#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <unistd.h>
#include <list>
#include <string.h>

#include <errno.h>

#define MSGMAX 4096

struct msgbuf {
    long mtype;
    char mtext[MSGMAX];
};


int main(int argc, char * argv[])
{
    
    if(argc <= 1)
    {
        printf("ERROR: there is no string for replacing\n");
        return 0;
    }
    
    key_t key_n = ftok(argv[0], 0);
	int n = msgget(key_n, IPC_CREAT | IPC_EXCL | 0666);
    
    struct msgbuf my_msg;
    my_msg.mtype = 1;
    
    memset(my_msg.mtext, 0, sizeof(my_msg.mtext));
	
	if(n < 0 && errno == EEXIST)
    {
        if(strlen(argv[1]) > MSGMAX)    {
            printf("Can't send a msg\n");
            printf("ERROR: max lenth of msg exceeded!\n");
            return 0;
        }
        
        n = msgget(key_n, IPC_CREAT | 0666);
        strcpy(my_msg.mtext, argv[1]);
        msgsnd(n, &my_msg, strlen(argv[1]), 0);
        printf("bye\n");
        
        return 0;
    }
    
	else
    {
        char * str;
        std::list <char *> strings;
        
        strings.push_back(argv[1]);
        
        bool exit = false;
        
        while(1)
        {
            if(msgrcv(n, &my_msg, MSGMAX, my_msg.mtype, IPC_NOWAIT) >= 0)
            {
                if(!strcmp("exit", my_msg.mtext)) exit = true;
                
                str = strdup(my_msg.mtext);
                strings.push_back(str);
                memset(my_msg.mtext, 0, sizeof(my_msg.mtext));
            }
            
            for(auto s : strings)
            {
                printf("%s\n", s);
            }
            
            if(exit)    break;
            
            sleep(1);
        }
    }
	
	
	msgctl(n, IPC_RMID, NULL);
    
    return 0;
}
