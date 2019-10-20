#include<stdio.h>
typedef struct highscore highscore;
struct highscore{
    char digit[100];
};
int main()
{
    highscore H[3];
    int i;
    FILE */*fp=fopen("highscore.bin","wb");
    for(i=0;i<3;i++)
    {
        scanf("%s",H[i].digit);
    fwrite(&H[i], sizeof(H[i]), 1, fp);
    }
    fclose(fp);
    i=0;
    */fp=fopen("highscore.bin","rb");
    i=0;
    while(fread(&H[i],sizeof(H[i]),1,fp)==1)
    {
        printf("%s \n",H[i].digit);
        i++;
    }

    fclose(fp);
}
