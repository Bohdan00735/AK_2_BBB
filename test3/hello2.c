#include "hello1.h"

static uint amount = 1;
module_param(amount,uint,S_IRUGO);
MODULE_PARM_DESC(amount, "That`s how many times the line should be printed");

static int __init init_fuction(void)
{
 
  print_hello(amount);
  return 0;
}

static void __exit cleanup_function(void)
{
  /* Do nothing here right now */
}

module_init(init_fuction);
module_exit(cleanup_function);
