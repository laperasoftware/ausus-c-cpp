//
// Created by famiglia on 16/01/21.
//

#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <ftw.h>
#include <fcntl.h>


#ifndef PROCESSES_H
#define PROCESSES_H

int writeString(char *str) {
    printf("\n%s", str);
}

FILE *stream;
int FDS[2];

void family(int x, int y) {

    if (x==3) {
        pipe(FDS);
        //read end [0] - write end [1]

        pid_t childPid = fork();


        if (childPid == 0) {
            //child process
            writeString("child is running");
            sleep(1);
            writeString("summing");

            //PIPES

            //can only write -> close read end
            close(FDS[0]);
            stream = fdopen(FDS[1], "w");
            for (int i = 0; i < 5; i++) {
                float result = sqrt(pow(x, i) + pow(y, i));
                fprintf(stream, ("order:%d\t%f\n"), i + 1, result);
                fflush(stream);
                sleep(1);
            }
            //writing is completed
            close(FDS[1]);

        } else {
            //father
            writeString("child generated");
            printf("\nchild pid = %d", childPid);
            writeString("waiting for child");
            //wait(NULL);
            //can only read -> close write end

            close(FDS[1]);
            char buffer[1024];
            /* Read until we hit the end of the stream.
           * fgets reads until either a newline or the end­of­file. */
            while (!feof(stream) && !ferror(stream)
                   && fgets(buffer, sizeof(buffer), stream) != NULL)
                fputs(buffer, stdout);
            close(FDS[0]);
        }
    }
    else if (x==4) {
        writeString("---NAMED PIPES [FIFO]--");
        char * nPipe = "/tmp/named_pipes/alepippa1";
        pid_t child = fork();

        //open pipe
        if (child == 0) {
            if(mkfifo(nPipe, S_IRUSR | S_IWUSR)!=0) {
                writeString("pipe is already existing");
            }
            int fd = open(nPipe, O_RDWR);
            if (fd == 0) {
                writeString("Cannot open fifo");
                unlink(nPipe);
                return;
            }

            struct s_point{
                int xp, yp;
            };
            struct s_point p = {20, 40};
            write(fd,  &p, sizeof (struct s_point) );
            writeString("VHBCW");
            close(fd);
            unlink(nPipe); //UNLINK SO IMPORTANT!!
        }
        else {
            wait(NULL);

        }

    }
}

int run() {
    writeString("STARTING MULTIPROCESS TESTS");
    family(4, 10);
    return 0;
}

#endif //PROCESSES_H


