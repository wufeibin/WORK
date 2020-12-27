#include "common.h"
#include "cpp_class.h"
#include "cpp_stl.h"

int main(int argc, char *argv[])
{
    LOGINFO("main start ...");
	CallbackTest();
	CreateThread();

UseStringStream();
    LOGINFO("main end ...");
    return 0;
}

