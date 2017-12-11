#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*
 * gcc -g brk_sbrk.c
 *
 * 内存以页为单位管理
 */

/*
brk_original 未进行减 1 操在的输出结果:
$./a.out
         bss_end addr[0x561204dfb004]
brk original address:[0x56120618d000]
brk start address:[0x56120618d001]
  brk end address:[0x56120618d002], after add 2 Byte
brk return code:0
brk current address:[0x56120618d001], after del 2 Byte
brk current address:[0x56120618d3ea][0x56120618d3e9], after add 1000 Byte
brk return code:0
brk current address:[0x56120618e000][0x56120618dfff], after add 4096 Byte
brk return code:0
brk current address:[0x56120618e001][0x56120618e000], after add 4096 Byte
brk return code:0
Segmentation fault (core dumped)

如果修改 brk_start_addr = sbrk(0); 为 brk_start_addr = sbrk(0) - 1;则在第 3 步会出现 coredump，可以观察内存页变化
*/

int bss_end; // 用全局变量来标明 bss 段的开始地址

int main()
{
    char *byte1, *byte2;
    char *brk_original,*brk_start_addr, *brk_addr2;

    // 1. 可以看到差 4 个字节与内存页对齐，操作系统应该使用这 4 个字节
    printf( "         bss_end addr[%p]\n", &bss_end - sizeof(int) );
    brk_original = sbrk(0);
    printf( "brk original address:[%p]\n", brk_original );

    // 2. 获取 heap 的起始地址。因为 bss 与 heap 之间有 random_brk，在申请内存前调用 sbrk(0) 获得的地址是 bss 的起始地址，因此增加 1 个字节的空间后再减 1 即可获得 heap 段实际的结束地址。
    // 堆上增加 1 个字节，sbrk 返回可用字节的首地址
    sbrk(1);

    // brk_start_addr 现在指向堆的结束地址
    brk_start_addr = sbrk(0) ;
    printf( "brk start address:[%p]\n", brk_start_addr );

    // 3. 堆上增加 1 个字节
    byte1 = sbrk(1);
    brk_addr2 = sbrk(0);
    printf( "  brk end address:[%p], after add 2 Byte\n", brk_addr2 );

    // 内存操作
    *byte1 = 'h';

    // 重置堆结束地址，释放内存给系统，接下来操作 byte1 应该会 coredump
    printf( "brk return code:%d\n", brk(brk_start_addr) );

    brk_addr2 = sbrk(0);
    printf( "brk current address:[%p], after del 2 Byte\n", brk_addr2 );
    *byte1 = 'e'; // core dump,this memory is not belong to this program

    // 4. 如果未出错，尝试分配 1000 Byte
    sbrk( 1000 );
    byte1 = sbrk(1);
    brk_addr2 = sbrk(0);
    printf( "brk current address:[%p][%p], after add 1000 Byte\n",
            brk_addr2, byte1 );
    printf( "brk return code:%d\n", brk(brk_start_addr) );
    *byte1 = 'a'; // core dump,this memory is not belong to this program

    // 5. 如果未出错，尝试分配 4096 Byte
    // 测试后发现达到 4096 后会出现内存错误，猜测内存的权限是根据页来划分的
    sbrk( 4094 );
    byte1 = sbrk(1);
    brk_addr2 = sbrk(0);
    printf( "brk current address:[%p][%p], after add 4096 Byte\n",
            brk_addr2, byte1 );
    printf( "brk return code:%d\n", brk(brk_start_addr) );
    *byte1 = 'p';

    sbrk( 4095 );
    byte1 = sbrk(1);
    brk_addr2 = sbrk(0);
    printf( "brk current address:[%p][%p], after add 4096 Byte\n",
            brk_addr2, byte1 );
    printf( "brk return code:%d\n", brk(brk_start_addr) );
    *byte1 = 'p';

}
