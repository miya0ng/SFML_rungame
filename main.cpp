#include "stdafx.h"

int main()
{
    FRAMEWORK.Init(1920, 1080, "COOKIE RUN!");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}