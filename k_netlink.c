#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <net/sock.h>
#include <linux/netlink.h>

#define NETLINK_USER  22
#define USER_MSG    (NETLINK_USER + 1)
#define USER_PORT   50

MODULE_LICENSE("GPL");  
MODULE_AUTHOR("arvik");  
MODULE_DESCRIPTION("netlink_demo");

static struct sock *netlinkfd = NULL;

int send_msg(int8_t *pbuf, uint16_t len)
{
    struct sk_buff *nl_skb;
    struct nlmsghdr *nlh;

    int ret;

    printk("Entering %s,line=%d, len=%d\n", __FUNCTION__, __LINE__, len);
    nl_skb = nlmsg_new(len, GFP_KERNEL);
    if(!nl_skb)
    {
        printk("netlink_alloc_skb error\n");
        return -1;
    }

    printk("skb_tailroom(nl_skb)=%u, nlmsg_total_size(USER_MSG)=%u\n", skb_tailroom(nl_skb), nlmsg_total_size(USER_MSG));
	nlh = __nlmsg_put(nl_skb, 0, 0, USER_MSG, len, 0);
	//nlh = nlmsg_put(nl_skb, 0, 0, 0, len, 0);
	if(nlh == NULL)
    {
        printk("nlmsg_put() error\n");
        nlmsg_free(nl_skb);
        return -1;
    }
    memcpy(nlmsg_data(nlh), pbuf, len);

    ret = netlink_unicast(netlinkfd, nl_skb, USER_PORT, MSG_DONTWAIT);

    return ret;
}


static void recv_cb(struct sk_buff *skb)
{
    struct nlmsghdr *nlh = NULL;
    void *data = NULL;
    printk("Entering %s,line=%d\n", __FUNCTION__, __LINE__);
    printk("skb->len:%u\n", skb->len);
	if(skb)
	{
		char *buf = skb->data;
		int len = skb->len;
		int i;
		printk("[%s:%d]Packet length = %#4x\n", __FUNCTION__, __LINE__, len);
		for(i = 0; i < len; i++)
		{
			if (i % 16 == 0) printk("%#4.4x", i);
			if (i % 2 == 0) printk(" ");
			printk("%2.2x", ((unsigned char *)buf)[i]);
			if (i % 16 == 15) printk("\n");
		}
		printk("\n\n");
	}

    if(skb->len >= nlmsg_total_size(0))
    {
        nlh = nlmsg_hdr(skb);
        data = NLMSG_DATA(nlh);
        if(data)
        {
            printk("kernel receive data: %s\n", (int8_t *)data);
            printk("nlmsg_len(nlh)= %d\n", nlmsg_len(nlh));

            send_msg(data, nlmsg_len(nlh));
        }
    }
} 


struct netlink_kernel_cfg cfg = 
{
    .input = recv_cb,
};

static int __init test_netlink_init(void)
{
    printk("init netlink_demo!\n");

    printk("Entering %s,line=%d\n", __FUNCTION__, __LINE__);
    netlinkfd = netlink_kernel_create(&init_net, USER_MSG, &cfg);
    if(!netlinkfd)
    {
        printk(KERN_ERR "can not create a netlink socket!\n");
        return -1;
    }

    printk("netlink demo init ok!\n");
    return 0;
}

static void __exit test_netlink_exit(void)
{
    printk("Entering %s,line=%d\n", __FUNCTION__, __LINE__);
    sock_release(netlinkfd->sk_socket);
    printk(KERN_DEBUG "netlink exit\n!");
}

module_init(test_netlink_init);
module_exit(test_netlink_exit);
