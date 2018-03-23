#include <stdio.h>
#define KEY_LENGTH 2
// Can be anything from 1 to 13

float abso(float a, float b)
{
    if (a>b)
        return (float)a-(float)b;
    return (float)b-(float)a;
}

int main(){  
    unsigned char ch;
    unsigned char ch2;  
    FILE *fpIn, *fpOut;  
    int i;  unsigned char key[KEY_LENGTH] = {0x00, 0x00};

    fpIn = fopen("ctext.txt", "r");  //  fpOut = fopen("ptext.txt", "w");
    i=0;  
    while (fscanf(fpIn, "%c", &ch) != EOF) 
    {
        fscanf(fpIn, "%c", &ch2);

        if (ch >= '0' && ch <= '9') ch = ch - '0';
        else if (ch >= 'A' && ch <='F') ch = ch - 'A' + 10;
        int f = (int)ch;
        f = f<<4;

        if (ch2 >= '0' && ch2 <= '9') ch2 = ch2 - '0';
        else if (ch2 >= 'A' && ch2 <='F') ch2 = ch2 - 'A' + 10;
        int c = (int)ch2;
        int final = f + c;
        i++;
    }
    i--;
    int arr[i];
    fseek(fpIn, 0L, SEEK_SET);
    i=0;
    while (fscanf(fpIn, "%c", &ch) != EOF)
    {
        fscanf(fpIn, "%c", &ch2);
        if (ch >= '0' && ch <= '9') ch = ch - '0';
        else if (ch >= 'A' && ch <='F') ch = ch - 'A' + 10;
        int f = (int)ch;
        f = f<<4;

        if (ch2 >= '0' && ch2 <= '9') ch2 = ch2 - '0';
        else if (ch2 >= 'A' && ch2 <='F') ch2 = ch2 - 'A' + 10;
        
        int c = (int)ch2;
        int final = f + c;
        
        arr[i]=final;
        i++;
    }
    i--;
    int n=i;
    float A[13];

    float req[26]={0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074};

    float S=0;
    for (int i = 0; i < 26; ++i)
    {
        S = S + req[i]*req[i];
    }

    for (int i = 0; i < 13; ++i)
    {
        A[i]=0;
        float f[256];
        for (int i = 0; i < 256; ++i)
        {
            f[i]=0;
        }
        int count =0;
        for (int j = 0; j < n; j=j+i+1)
        {
            f[arr[j]]++;
            count++;
        }
 /*     printf("count is %d\n", count);*/
        for (int i = 0; i < 256; ++i)
        {
            f[i] = f[i]/(float)count;
//          printf("F[i] are %f\n", f[i]);
        }
        for (int k = 0; k < 256; ++k)
        {
            A[i] = f[k]*f[k] + A[i];
        }//      printf("A[i] %f\n", A[i]);
    }

    int length = 0;
    float max_ = 0;

    for (int i = 0; i < 13; ++i)
    {
//      printf("%f\n", A[i]);
        if (A[i] > max_)
        {
            max_ = A[i];
            length = i;
        }
    }

    length++;
    printf("KEY_LENGTH is %d\n", length);

    float fre[256];
    int E[length];
    for (int i = 0; i < 256; ++i)
    {
        E[length]=0;
    }
    for (int i = 0; i < length; ++i)
    {
        float E_[256];
        for (int i = 0; i < 256; ++i)
        {
            E_[i]=0;
        }
        for (int j = 0; j < 256; ++j)
        {
            int count=0;
            for (int i = 0; i < 256; ++i)
            {
                fre[i]=0;
            }
            for (int k = i; k < n; k=k+length)
            {
                fre[arr[k]^j]++;
                count++;
            }
            for (int i = 0; i < 256; ++i)
            {
                fre[i]=fre[i]/(float)count;
            }
            for (int i = 0; i < 26; ++i)
            {
                E_[j] = E_[j] + req[i]*fre[i+'a'];
            }
//          printf("E is %f and S is %f\n", E_[j], S);
        }
//      float min2 = 2;
        float min = abso(E_[0], S);
        E[i] = 0;
        for (int j = 0; j < 256; ++j)
        { 
            if (abso(E_[j],S)<min)
            {
//              printf("%f\n", abso(E_[j],S));
                min = abso(E_[j], S);
                E[i] = j;
            }
        }
        printf("min is %f\n", min);
        E_[E[i]]=21;
        min = abso(E_[0], S);
//      E[i] = 0;
        for (int j = 0; j < 256; ++j)
        { 
            if (abso(E_[j],S)<min)
            {
 //             printf("%f\n", abso(E_[j],S));
                min = abso(E_[j], S);
//              E[i] = j;
            }
        }
        printf("2nd min is %f\n", min);
    }

    for (int i = 0; i < length; ++i)
    {
        printf("%d\n", E[i]);
    }

    for (int i = 0; i < n; ++i)
    {
        printf("%c", arr[i]^E[i%length]);
    }

    fclose(fpIn);  
//    fclose(fpOut);  
    return 0;
} 
