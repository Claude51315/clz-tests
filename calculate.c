#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static int N;
void calculate(char filename[]);
int main(int argc, char* argv[])
{

    N = atoi(argv[1]);
    printf("N = %d\n", N);
    calculate("binary.txt");
    calculate("recursive.txt");
    calculate("iterate.txt");
    return 0;
}
void calculate(char filename[])
{
    FILE *data, *output;
    char *pch;
    double tmp_sum = 0;
    double tmp = 0;
    data = fopen(filename, "r");
    if(data == NULL) {
        printf("%s open fail!\n", filename);
        return ;
    }
    while(!feof(data)) {
        fscanf(data, "%lf", &tmp);
        tmp_sum += tmp;
    }
    fclose(data);
    tmp_sum /= N;
    /*
    pch = strtok(filename, ".");
    if(pch==NULL){
        printf("QQQ\n");

        return;

    }
    */
    output = fopen("output.txt","a");
    fprintf(output, "%s %lf\n", filename, tmp_sum);
    fclose(output);
}
