#include<stdio.h>
#include<stdlib.h>
#include <linux/init.h>
#include <linux/module.h>
#include <sys/socket.h> //It contains the data structures required for socket
#include <netinet/in.h>// It has the constants and structures required for Internet domain address.
#include <sys/types.h> //It has definitions of number of data types used for system calls.
#include <unistd.h>


struct file_operations aes_256_fops = {
	.owner =     THIS_MODULE,
	//.read =     aes_256_read,
	.open =	     aes_256_open,
	.write=      aes_256_write,
	};

static int    majorNumber;                  ///< Stores the device number -- determined automatically
static struct class*  AES_256_charClass  = NULL; ///< The device-driver class struct pointer
static struct device* AES_256_charClass = NULL; ///< The device-driver device struct pointer


	struct sockaddr{
		unsigned short sa_family; //addres family AF_INET
		char sa_sata[14]; //Family specific address information
	}
	struct in_addr{
		unsigned long s_addr; //internet address 32 bits
	}
	struct sockaddr_in{
		unsigned short sin_family; //address family AF_INET
		unsigned short sin_port; //assign the port
		struct in_addr sin_addr; //assign the ip address
		char sin_ero[8];
	}

static int  aes_256_open(struct inode *, struct file *){
	
	int sockfd, clientfd;
	struct sockaddr_in serverAddress, cliAddr;
	int sockfd, clientfd;
	socklen_t addr_size;
	int len= sizeof(cliAddr);
	char exampleMessage[256]= "Hello from server\n";
	
	//create a socket file descriptor
	sockfd= socket(AF_INET, SOCK_STREAM, 0);
	
	//server address
	serverAddress.sin_family=AF_INET; // AF_UNIX is good for processes in the same file system, AF_INET is good for processes running between 2 hosts in the internet
	serverAddress.sin_port=htons(5022);
	serverAddress.sin_addr.s_addr= INADDR_ANY;
		
	//bind the address
	bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));    
	
	//listen 
	if(listen(sockfd,5)==0); 
	
	//accept the connection
	clientfd= accept(sockfd, (struct sockaddr *) &cliAddr, &len);
	
	//send the data
	send(clienfd, exampleMessage, sizeof(exampleMessage),0)
	
	
	
	
	//int count = recv(sockid, recvBuf, bufLen, flags) //Receive the data using “recv()”
	
	status = close(sock);
	if(sock== -1) return -1;
	
	return 0;
}



static int __init test_init(void)
{ 
   printk(KERN_INFO "LM: Initializing the LMODULE LKM\n");
 
   // Try to dynamically allocate a major number for the device -- more difficult but worth it
   majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
   if (majorNumber<0){
      printk(KERN_ALERT "LM failed to register a major number\n");
      return majorNumber;
   }
   printk(KERN_INFO "LM: registered correctly with major number %d\n", majorNumber);
 
   // Register the device class
   AES_256_charClass = class_create(THIS_MODULE, CLASS_NAME);
   if (IS_ERR(AES_256_charClass)){                // Check for error and clean up if there is
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to register device class\n");
      return PTR_ERR(AES_256_charClass);          // Correct way to return an error on a pointer
   }
   printk(KERN_INFO "LM: device class registered correctly\n");
 
   // Register the device driver
   AES_256_charClass = device_create(AES_256_charClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
   if (IS_ERR(AES_256_charClass)){               // Clean up if there is an error
      class_destroy(AES_256_charClass);           // Repeated code but the alternative is goto statements
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to create the device\n");
      return PTR_ERR(AES_256_charClass);
   }
   printk(KERN_INFO "LM: device class created correctly\n"); // Made it! device was initialized
   
    return 0;
}
static ssize_t aes_256_write(struct file *, const char *, size_t, loff_t *){
	printk(KERN_INFO "Writing stuff\n")
	return 0;
}



static void __exit test_exit(void)
{

   device_destroy(AES_256_charClass, MKDEV(majorNumber, 0));     // remove the device
   class_unregister(AES_256_charClass);                          // unregister the device class
   class_destroy(AES_256_charClass);                             // remove the device class
   unregister_chrdev(majorNumber, DEVICE_NAME);             // unregister the major number
   printk(KERN_INFO "LM: Goodbye from the LKM!\n");
   
}














MODULE_AUTHOR("OS_PRJ");
MODULE_DESCRIPTION("Linux device driver for AES_256 cryptocore");
MODULE_LICENSE("GPL");

module_init(test_init);
module_exit(test_exit);
