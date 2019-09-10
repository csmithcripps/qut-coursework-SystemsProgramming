/**
 * A pthread program illustrating how to
 * create a simple thread and some of the pthread API
 * This program implements the insert data to the front of a linked list
 * the operation is run as a separate thread.
 *
 * gcc threading_wk4.c -lpthread
 *
 * @Yuefeng Li, August 2008.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* shared data structure by the thread(s) */
struct list_el
{
   int data;
   struct list_el *next;
};

typedef struct list_el item;
item *head = NULL;

/* the thread */
void insert_to_front(int);

/* function for the parent */
item *add_to_list(int, item *);

int main(int argc, char *argv[])
{
   pthread_t tid;       /* the thread identifier */
   pthread_attr_t attr; /* set of attributes for the thread */

   head = add_to_list(100, head);
   head = add_to_list(200, head);
   printf("The list created by the parent: %d --> %d\n", head->data, (head->next)->data);

   if (argc != 2)
   {
      fprintf(stderr, "usage: a.out <integer value>\n");
      /*exit(1);*/
      return -1;
   }

   if (atoi(argv[1]) < 0)
   {
      fprintf(stderr, "Argument %d must be non-negative\n", atoi(argv[1]));
      /*exit(1);*/
      return -1;
   }

   /* get the default attributes */
   pthread_attr_init(&attr);

   /* create the thread */
   pthread_create(&tid, &attr, (void *(*)(void *))insert_to_front, (void *__restrict__)(size_t)atoi(argv[1]));

   /* now wait for the thread to exit */
   pthread_join(tid, NULL);

   printf("The list updated by the child: %d --> %d --> %d\n", head->data, (head->next)->data, ((head->next)->next)->data);

   printf("The END \n");
}

/**
 * The thread will begin control in this function
 */

void insert_to_front(int it){
    item *new_node = (item*)malloc(sizeof(item));

    new_node->next = head->next;
    new_node->data = head->data;
    head->data = it;
    head->next = new_node;
}

item *add_to_list(int it, item *h)
{
   item *p = h;
   item *new_rec = NULL; /* Holds address of new rec */

   new_rec = (item *)malloc(sizeof(item)); /* Get memory location */
   if (!new_rec)                           /* Unable to get memory */
   {
      printf("\nUnable to allocate memory!\n");
      exit(1);
   }

   new_rec->data = it;   /* Store character into new location */
   new_rec->next = NULL; /* Last record always pts to NULL */

   if (p == NULL)
      return (new_rec);
   else
   {
      while (p->next)
         p = p->next;
      p->next = new_rec;
      return (h); /* return address of the new head */
   }
}
