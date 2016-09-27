#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char* argv[])
{

    int N = atoi(argv[1]);
    FILE *data, *output;
    char buffer[20];
    double iterate = 0, binary =0, recursive=0;
    double tmp = 0;
    data = fopen("origin_data.txt", "r");
    while(!feof(data)) {
        fscanf(data, "%s %lf", buffer, &tmp);
        if(strcmp(buffer, "iterate") == 0) {
            iterate += tmp;
        } else if (strcmp(buffer, "recursive") ==0 ) {
            recursive += tmp;
        } else {
            binary += tmp;
        }
    }
    fclose(data);
    iterate /= N;
    recursive /= N;
    binary /= N;
    output = fopen("output.txt","w");
    fprintf(output, "recursive %lf\n", recursive);
    fprintf(output, "iterate %lf\n", iterate);
    fprintf(output, "binary %lf\n", binary);
    fclose(output);
    return 0;
}
