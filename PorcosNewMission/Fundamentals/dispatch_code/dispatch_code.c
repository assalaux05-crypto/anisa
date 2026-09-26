#include "dispatch_code.h"


int count(const char* str)
{
    int len=0;
    while(str[len]!='\0')
    {
        len++;
    }
    return len ;
}
void embed_hidden_message(char *cover_text, int stride, const char *hidden)
{
    if (stride <=0 || cover_text==NULL || hidden==NULL)
    {
        printf("Error : Invalid Parameter\n");

    }
    else
    {
        int len=count(hidden);
        int size=count(cover_text);
        for(int i=0;i<len;i++)
        {
           if (i*stride>=size)
           {
                break;
           }
        cover_text[i*stride]=hidden[i];

        }
    }
    

}
/*
int main(void)
{
char cover_text[] = "abcdefghij";
int stride = 3;
const char *hidden = "BONJOUR";
embed_hidden_message(cover_text, stride, hidden);
printf("cover_text is now %s\n",cover_text);
return 0;
}
*/


void extract_hidden_message(const char *cover_text, int stride, char *hidden_out, size_t size) 
{
    if (stride <=0 || cover_text==NULL || hidden_out==NULL)
    {
        printf("Error : Invalid Parameter\n");

    }
    else
    {
        size_t taille=count(cover_text);
        for(size_t i=0;i<size;i++)
        {
            if (i*stride>=taille)
           {
            hidden_out[i]='\0';
            break;
           }
            hidden_out[i]=cover_text[i*stride];
        }
        hidden_out[size]='\0';
    }
}
/*
int main(void)
{
    char cover_text[] = "abcdefghijk";
int stride = 4;
char hidden_out[6];
size_t size = 5;

extract_hidden_message(cover_text, stride, hidden_out, size);
printf("cover_text is now %s\n",hidden_out);
return 0;

}
*/