#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/types.h>
#include <linux/slab.h>


MODULE_AUTHOR("Melniichuk Bohdan IO-81");
MODULE_DESCRIPTION("First training kernel module wich repeat phrase");
MODULE_LICENSE("Dual BSD/GPL");


struct my_linked_list_head{
struct my_linked_list_head *next;
ktime_t start_time;
ktime_t end_time;
};

struct list_item {
  ktime_t time;
  struct list_head list_node;
};

static struct list_head my_list_head = LIST_HEAD_INIT(my_list_head);

static uint amount = 1;
static struct my_linked_list_head *head;
module_param(amount, uint, S_IRUGO);
MODULE_PARM_DESC(amount, "That`s how many times the line should be printed");


static int __init init_fuction(void)
{
  struct list_item *tail;

  uint i = 0;

  printk(KERN_INFO "times: %d\n", amount);

  BUG_ON(amount > 10);

  if (amount == 0) {
    printk(KERN_WARNING "The parameter is 0");
  } else if (amount > =5 && amount <= 10) {
    printk(KERN_WARNING "The parameter is between 5 and 10");
  }
 
  for (i = 0; i < amount; i++) {
    tail = kmalloc(sizeof(struct list_item), GFP_KERNEL); 
    if (i == 5)
      tail = 0; 
    //if(ZERO_OR_NULL_PTR(tail))
    // goto error;
    tail->time = ktime_get();
    list_add_tail(&(tail->list_node), &my_list_head);
    pr_info("Hello world\n");
  }

  return 0;
  error:
  {
    struct list_item *md, *tmp;
    pr_err("kmalloc out of memory");
    //clear memory
    list_for_each_entry_safe(md, tmp, &my_list_head, list_node) {
      list_del(&md->list_node);
      kfree(md);
    }
    BUG();
    return -ENOMEM;
  }

}

static void __exit cleanup_function(void)
{struct list_item *md, *tmp;

  list_for_each_entry_safe(md, tmp, &my_list_head, list_node) {
    pr_info("time: %lld\n", md->time);
    list_del(&md->list_node);
    kfree(md);
    }
  }




module_init(init_fuction);
module_exit(cleanup_function);

