#include <stdio.h>
#include <stdlib.h>

int main()
    {
    FILE* fileptr = fopen("PATCHTEST.COM","r+");

    fseek( fileptr, 67, SEEK_SET );
    fprintf( fileptr, "%c%c%c", 0x3B, 0xC9, 90); //cmp cx, cx nop

    fseek( fileptr, 12, SEEK_CUR);    
    fprintf( fileptr,"%c%c%c", 0x83, 0xC3, 0x00); //add bx, 0 

    fclose(fileptr);
    return 0;
    }