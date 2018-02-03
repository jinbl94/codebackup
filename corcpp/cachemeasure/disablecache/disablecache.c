#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
MODULE_LICENSE("CPL");
/*static int cache_off(void){
	printk(KERN_ALERT "Disabling caches...\n");
	asm(
			"push %eax\n\t"
			"movl %cr0,%eax\n\t"
			"orl $0x40000000,%eax\n\t"  //Set cache disable bit
			"movl %eax,%cr0\n\t"
			"wbinvd\n\t"
			"pop  %eax\n\t");
	return 0;
}

static inline void cache_on(void){
	printk(KERN_ALERT "Enabling caches...\n");
	asm(
			"push %eax\n\t"
			"movl %cr0,%eax\n\t"
			"andl $0xbfffffff,%eax\n\t"  //Set cache disable bit
			"movl %eax,%cr0\n\t"
			"wbinvd\n\t"
			"pop  %eax\n\t");
}*/

static int __init lkp_init(void){
	printk(KERN_ALERT "Starting...\n");
	return 0;
}

static void __exit lkp_cleanup(void){
	printk(KERN_ALERT "Exiting...\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);
MODULE_AUTHOR("Tang");
MODULE_DESCRIPTION("TEST");
