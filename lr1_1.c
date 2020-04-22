/*
 * Простой интерпретатор командной строки
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXNLINE 16
#define MAXNCOLUMN 80



int main ()
{
    
    size_t i = 0, j = 0;
    int c = 0;
    char arg[MAXNLINE][MAXNCOLUMN] = {0}, *argv[MAXNLINE + 1] = {0};

    while ((i < MAXNLINE) && (j < MAXNCOLUMN) && ((c = getchar()) != EOF)) {
        if (c != '\n') {

            if (c != ' ') {
                arg[i][j] = c;
                ++j;

            } else {
                arg[i][j] = '\0';
                ++i;
                j = 0;
            }
        } else {
            arg[i][j] = '\0';

            for (j = 0; j <= i; ++j) {
                argv[j] = arg[j];
            }
            argv[j] = 0;

            //печать того, что записали в arg
# if !NDEBUG
            for (j = 0; j <= i; ++j) {
                puts(arg[j]);
            }
# endif

            pid_t pid = fork();

            if (!pid) {
                int rv = execvp(argv[0], argv);

                if (rv == -1) {
                    perror("execlp");
                    return EXIT_FAILURE;
                }
            }

            pid = wait(NULL);
            if (pid == -1) {
                perror("wait");
                return EXIT_FAILURE;
            }

            i = 0;
            j = 0;
        }

    }

    return EXIT_SUCCESS;

}
