#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#pragma once

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


int print_hello(uint amount);


