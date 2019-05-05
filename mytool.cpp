#include <stdio.h>
#include <string.h>

#include <vector>

std::vector <int> MakePref(char * arg);


int main(int argc, char * argv[])
{
    if(argc <= 1)
    {
        printf("ERROR: there is no string for replacing\n");
        return 0;
    }
    
    std::vector <int> pf = MakePref(argv[1]);
    
    
    int c = getchar();
    int i = 0;
    
    
    while(c != EOF)
    {
        putchar(c);
        
        while ((i > 0) && (argv[1][i] != c))
            i = pf[i - 1];
        
        if (argv[1][i] == c)
            i ++;
        
        if (i == strlen(argv[1]))   {
            putchar('*');
            i = 0;
        }
        
        c = getchar();
    }
    
	return 0;
	
}


std::vector <int> MakePref(char * arg)
{
    std::vector <int> pf (strlen(arg));
    
    pf[0] = 0;
    
    for (int j = 0, i = 1; i < strlen(arg); ++ i)
    {
        while ((j > 0) && (arg[i] != arg[j]))
            j = pf[j - 1];
        
        if (arg[i] == arg[j])
            j ++;
        
        pf[i] = j;
    }
    
    return pf;
}
