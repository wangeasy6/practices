#include <stdio.h>
#include <string.h>

#define TXT_SIZE 1024
#define TMP_SIZE 512

int split(char *Text, char split_char)
{
	int i,j,n = 0;
	char temp[TMP_SIZE];
	if ( Text == NULL)
		return -1;

	for ( i = 0,j = 0; Text[i] != '\0'; i++,j++)
	{
		temp[j] = Text[i];
		if( Text[i] == split_char)
		{
			temp[j+1] = '\0';
			printf("[%d] %s\n", n, temp);
			memset(temp, 0, 128);
			j = -1;
			n++;
		}
	}
	temp[j] = '\0';
	printf("[%d] %s\n", n++, temp);

	return 0;
}

int main()
{
	char text[TXT_SIZE] = "麦克\n杰克\n!@#$\n999";
	split(text, '\n');
	return 0;
}
