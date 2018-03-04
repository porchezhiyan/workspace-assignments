#include"stdio.h"

int negateinteger(int bin)
{
        for(int i = 0 ; i < 32 ; i++)
        {
                bin = bin ^ (1<<i);
        }
        return bin;     //
}
void main()
{
	int n;
	scanf("%d",&n);
	printf("%d",negateinteger(n));
}
