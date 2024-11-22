#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int entradas[] = {10, 25, 50, 100, 150, 200, 300, 500, 750, 1000, 1500, 2000, 2500, 5000, 7500, 10000, 15000, 20000, 30000, 50000, 75000, 100000, 150000, 250000, 350000, 500000, 750000, 1000000};
    char mode = 't';
    char chamada[100];
    int status;

    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (j >= 6)
                mode = 'f';

            sprintf(chamada, "./main.x data/Aula%d.txt %c", entradas[i], mode);
            
            system(chamada);
            wait(&status);
        }
        mode = 't';
    }

    return 0;
}