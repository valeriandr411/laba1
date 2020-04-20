//Продрамма- интерпритатор командной строки
//Позволяет 
//Допустим, пользователь вводит последовательность ls -a -l
//Данная программа выведет в консоль 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAXNLINE 16
#define MAXNCOLUMN 80

main ()
{
    int i, j;
    char c;
    char arg[MAXNLINE][MAXNCOLUMN];
    char*argv[MAXNLINE+1];
    i=0;
    j=0;
    
    while ((c = getchar()) != EOF){
        if (c != '\n'){ //
            
            if (c != ' '){//аргументы программы или сама программа
                arg[i][j] = c;
                ++j;
            }
            
            else {//пробел
                
                arg[i][j]='\0';//заканчиваем писать в очередную строку
                ++i;//
                j=0;
            }
        }
        else{ //конец строки => заполняем массив  для exec
            arg[i][j] = '\0';//последний символ был концом строки => добавляем в конце последнего элемента массива символ конца строки
            for (j = 0;j<=i;++j){// заполняем массив аргументов для exec
                argv[j]=arg[j];
                }
                
            argv[j]=NULL;//последний элемент ссылается на NULL 
        
        
            for(j=0;j<=i;++j){//печать того, что записали в arg
                printf("%s\n",arg[j]);
            }
            
            pid_t pid=fork();
            
            if (!pid) {
                int rv = execvp(argv[0],argv);
                
                if (rv == -1) {
                    perror("execlp");
                    return EXIT_FAILURE;
                } 
            }
            pid = wait(NULL);
            if (pid == -1){
            perror("wait");
            return EXIT_FAILURE;
            }
            
            i=0;
            j=0;
        }
    
    }

    return EXIT_SUCCESS;
     
}
