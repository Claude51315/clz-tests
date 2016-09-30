#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static unsigned int min;
static unsigned int max;
static unsigned int N;
void calculate(char filename[]);
int main(int argc, char* argv[])
{

    min = atoi(argv[1]);
    max = atoi(argv[2]);
    N = max - min + 1;
    calculate("binary.txt");
    calculate("recursive.txt");
    calculate("iterate.txt");
    calculate("harley.txt");
    calculate("byteshift.txt");
    return 0;
}
void calculate(char filename[])
{
    FILE *data, *output;
    char buffer[20];
    double tmp_sum = 0;
    double tmp = 0;
    unsigned int foo;
    data = fopen(filename, "r");
    if(data == NULL) {
        printf("%s open fail!\n", filename);
        return ;
    }
    while(!feof(data)) {
        fscanf(data, "%u %lf", &foo, &tmp);
        tmp_sum += tmp;
    }
    fclose(data);
    tmp_sum /= N;
    strncpy(buffer, filename, strlen(filename) -4);
    output = fopen("output.txt","a");
    fprintf(output, "%s %lf\n", buffer, tmp_sum);
    fclose(output);
}
