#include <stdio.h>
int main()
{
	int count = 0, i, j;
	float srcX, srcY;
	for(i = 0; i < 96; i++)
	{
		for(j = 0; j <= 127; j++)
		{
			srcX = i * 0.25;  // i * 0.16 + 5;
			printf("%.1f,", srcX);
			count++;
			if(count >= 32)
			{
				printf("\n");
				count = 0;
			}
		}
	}
	
	printf("\n\n");
	
	for(i = 0; i < 96; i++)
	{
		for(j = 0; j <= 127; j++)
		{
			srcY = j * 0.25;  //j * 0.16 + 6;
			printf("%.1f,", srcY);
			count++;
			if(count >= 32)
			{
				printf("\n");
				count = 0;
			}
		}
	}
	
	return 0;
}
