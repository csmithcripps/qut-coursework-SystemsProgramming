/* Program:  prac6_SJF_Sched.c
 * Author:   Yuefeng Li
 * Purpose:  using linked list queues for Round-Robin Scheduling
 *=========================================================*/

#include <stdlib.h>
#include <stdio.h>

struct process
{
   char data;
   int burst;
   struct process *next;
};

typedef struct process node;

node *head = NULL; /* ready queue's head */
node *tail = NULL; /* ready queue's tail */

node *fhead = NULL; /* SJF scheduling queue's head */
node *ftail = NULL; /* SJF scheduling queue's tail */

void print_list(node *);

int sjf(node *p); /* the shortest job first scheduling algorithm */

/*insert function for the ready queue */
void r_insq(node *new)
{
   if (tail == NULL) /* empty list */
      head = new;
   else
      tail->next = new;
   tail = new;
}

void f_insq(node *new)
{
   if (ftail == NULL) /* empty list */
      fhead = new;
   else
      ftail->next = new;
   ftail = new;
}

void main()
{
   node *p;
   int i;
   int q = 20; /* the time quantum */

   /* initializing the ready queue for SJF */
   for (i = 1; i <= 6; i++)
   {
      p = (node *)malloc(sizeof(node));
      p->data = 64 + i;
      p->burst = (int)((double)(99) * rand() / (999999999 + 1.0));
      p->next = NULL;
      r_insq(p);
   }

   printf("The ready queue for the SJF scheduling is: \n\n");
   print_list(head);
   printf("\n\n");

   /* FJF scheduling */
   sjf(head);
   printf("The resulting SJF schedule is: \n\n");
   print_list(fhead);
   printf("\n\n");
}

void del_node(node *p)
{
   if (head == p)
   {
      head = head->next;
      return;
   }
   node *cursor = head;

   while (cursor->next != p)
   {
      cursor = cursor->next;
   }
   cursor->next = cursor->next->next;
   return;
}

node *findMinNode()
{
   node *pmin = head;
   node *p = head;
   while (p != NULL)
   {
      if (p->burst < pmin->burst)
      {
         pmin = p;
      }
      p = p->next;
   }
   return pmin;
}

int sjf(node *p)
{
   node *p1;

   //if list is empty return
   if (p == NULL)
   {
      return 0;
   }
   else if (p->next == NULL) //One Node in Queue
   {
      f_insq(p);
      return (1);
   }

   //Find Shortest node;
   node *pmin = findMinNode();

   f_insq(pmin);

   del_node(pmin);
   sjf(head);
}

void print_list(node *p)
{
   if (p == NULL)
      printf("^\n");
   else
   {
      while (p->next)
      {
         printf("(%c, %d) --> ", p->data, p->burst);
         p = p->next;
      }
      printf("(%c, %d) ^\n ", p->data, p->burst);
   }
}
