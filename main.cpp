#include "stdafx.h"

int main()
{
    FRAMEWORK.Init(1033, 370, "COOKIE RUN!");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}