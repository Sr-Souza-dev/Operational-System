#include <stdio.h>
#include <stdlib.h>

void processor()
{

}

void memory()
{

}

void disc()
{

}


int main()
{
    char cmd[5];
    gets(cmd);

    if(cmd=="proc")
    {
        processor();
    }
    else if(cmd=="memo")
    {
        memory();
    }
    else if(cmd=="disc")
    {
        disc();
    }

    return 0;
}