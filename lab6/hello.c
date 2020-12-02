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

static uint amount = 1;
static struct my_linked_list_head *head;
module_param(amount,uint,S_IRUGO);
MODULE_PARM_DESC(amount, "That`s how many times the line should be printed");


static int __init init_fuction(void)
{
  uint i = 0;

  struct my_linked_list_head *temp1, *temp2;
  head = kmalloc(sizeof(struct my_linked_list_head), GFP_KERNEL);
  temp1 = head;


  printk(KERN_INFO "times: %d\n", amount);

  if(amount == 0) {
    printk(KERN_WARNING "The parameter is 0");
  }else if(amount >=5 && amount <= 10) {
    printk(KERN_WARNING "The parameter is between 5 and 10");
  } else if(amount > 10) {
    printk(KERN_ERR "The parameter is greater than 10");
    return -EINVAL;
  }

  for(i = 0; i < amount; i++){
    temp1->next = kmalloc(sizeof(struct my_linked_list_head), GFP_KERNEL);
    temp1->start_time = ktime_get();
    printk(KERN_INFO "Hello, world!\n");
    temp1->end_time = ktime_get();
    temp2 = temp1;
    temp1 = temp1->next;   
  }
  kfree(temp2->next);
  temp2->next = NULL;


  return 0;
}

static void __exit cleanup_function(void)
{
  struct my_linked_list_head* temp;
  while(head != NULL){
    temp = head;
    pr_info("Time: %lld", temp->end_time - temp->start_time);
    head = temp->next;
    kfree(temp);
    }
}

module_init(init_fuction);
module_exit(cleanup_function);

