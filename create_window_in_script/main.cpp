
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libtcc.h>

extern "C" void get_text(char* str)
{
	strcpy(str,"Hello tcc!");
}

int main(int argc, char **argv)
{
    TCCState *s;
    int (*script_main)(void);

	//新建一个TCCState
    s = tcc_new();
    if (!s)
	{
        fprintf(stderr, "Could not create tcc state\n");
        exit(1);
    }

	// 生成的代码放到内存中，不生成文件
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

	// 添加代码中需要用到的lib文件
	tcc_add_file(s,"./lib/user32.def");
	tcc_add_file(s,"./lib/gdi32.def");
    tcc_add_symbol(s, "get_text", get_text);

	// 添加要执行的C代码文件
    if (tcc_add_file(s,"hello_win.c") == -1)
        return 1;

	// 文档中说在执行tcc_get_symbol之前必须先调用一下这个函数，于是我就照做了
    if (tcc_relocate(s, TCC_RELOCATE_AUTO) < 0)
        return 1;
	// 获取到脚本中的script_main函数
    script_main = (int (*)(void))tcc_get_symbol(s, "script_main");
    if (!script_main)
        return 1;
	// 执行它！
    script_main();

	// 清理现场
    tcc_delete(s);

    return 0;
}
