#include "common.h" 

int main(int argc, char *argv[])
{
    LOGINFO("main start ...");
	CallbackTest();
	CreateThread();

    LOGINFO("main end ...");
    return 0;
}

