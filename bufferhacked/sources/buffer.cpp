#include <stdio.h>
#include <stdlib.h>

int main()
    {
    FILE* fileptr = fopen("hack.txt","w+");

    fprintf( fileptr, "%c%c%c%c%c", 0x3B, 0xC0, 0xE9, 0xB3, 0xFF);

    for ( int i = 0; i < 0x0000FE78; i++ )
        {
        fprintf( fileptr, "%c", 0);    
        }
        
    fprintf( fileptr, "%c%c\r\n", 0x7F, 0x01 ); 

    fclose(fileptr);
    return 0;
    }