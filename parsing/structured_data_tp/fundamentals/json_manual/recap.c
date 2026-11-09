








int fct(const char*filename, key, out, out_size)
{
    FILE*fopen(filename,"r");
    if(!f)return -1;

    fseek(f,0,SEEK_END);
    long size=ftell(f);
    rewind(f);
    if (size<=0){fclose(f); return -1;}

    char*buff=malloc(size+1);
    if(!buff){fclose(f); return -1;}
    fread(buff,1,size,f);
    buff[size]='\0';
    fclose(f);




    const char*p=space(buff);
    if(*p && *p!='{'){free(buff); return -1;}
    p++;
    while(*p!='\0')
    {
    
        p=space(p);
        if(*p && *p=='}')break;
        if(*p && *p!='"'){free(buff); return -1;}
        p++;
       const char*start=p;
        while(*p && *p!='"')
        {
            p++;
        }
        if(*p!='"'){free(buff); return -1;}
        
        size_t len=p-start;
        p++;
        int match=0;
        if(strlen(key)==len && strncmp(start,key,len)==0)
        {
            match=1;
        }
        p=space(p);
        if(*p && *p!=':'){free(buff); return -1;}
        p++;
        p=space(p);
        if(match)
        {










            free(buff);
            return 0;

        }
        p=skip(p);
        p=space(p);
        if(*p && *p==',')
        {
            p++;
        }








    }


    free(buff);
    return -1;




}










// cas de matcch

=>string  "....."  :  "sofpsvgp"
if(*p && *p!='"')cas errruer

=>int "fedsg" : 433

if((*p<0 || *p>9) && *p!='-')cas erreur 
char* end;
const char* s=p;
long val=strtol(s,&end,10);
if(end==s)erruer 
*out=(int)val;


=>tab