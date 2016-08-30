#include "Utility.h"




void strConcatenate(char * r, char *a, char *b) {
    sprintf(r,"%s%s",a,b);//doesn't need explanation
}


int splitOnChar(char *a, char c, char result[][maxStringLength]) {


    int end = strlen(a);
    int t = 0;//number of items that will be splited
    int i,j;
    i = 0;
    while(i < end && a[i] == c)// find the first char not equale to c
        i++;

    while( i < end ) {
        j = i;
        while(j < end && a[j] != c)//find the first char not equale to c
            j++;

        //copy splited string from i to j-1
        memcpy(result[t], a+i, (j-i)*sizeof(char));
        result[t][j-i] = '\0';

        t++;

        //find the next char to start form next
        while(j < end && a[j] == c)
            j++;

        i = j;
    }


    return t;
}


void trim(char *a) {

    int i = 0;
    int end = strlen(a);

    //find the first char not a spcace or a tab
    while(i < end && (a[i] == ' ' || a[i] == '\t'))
        i++;

    int j = end-1;
    //find the last char not a spcace or a tab
    while(j >= 0 &&  (a[j] == ' ' || a[j] == '\t'))
        j--;

   // printf("%d %d\n",i,j);
    if(i > j) {
        a[0] = '\0';
        return;
    }

   int k = i;
   char temp[j-i+2];
   while (k <= j) {
       // printf("%d %c\n",k,a[k]);
        temp[k-i] = a[k];
        k++;
   }
    temp[k-i] = '\0';
   // printf("ggg |%s|\n",temp);

    for(k = 0; k <= strlen(temp); k++) {
        a[k] = temp[k];
    }


}


















