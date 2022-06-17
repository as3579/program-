#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
void add_item();
void read_item();
void modify_item();
void delete_item();
int option();
void checkitem();
struct inventory
      {
            char name[30];
            float price;
            int quantity;
            int code;
      };
void main()
{
      int c;
      char con='Y';
      while(con=='Y')
      {
            c=option();
            switch(c)
            {
                  case 1:
                  add_item();
                  break;
                  case 2:
                  read_item();
                  break;
                  case 3:
                  modify_item();
                  break;
                  case 4:
                  delete_item();
                  break;
            }
            checkitem();
            printf("\nType 'Y' to continue with operations:");
            scanf("\n%c",&con);
      }
}
int option()
{
      int ch;
      printf("\nOptions available:");
      printf("\n1 to add item in inventory \n2 to read items from inventory \n3 to modify item quantity \n4 to delete an item from the inventory");
      printf("\nEnter choice: ");
      scanf("%d",&ch);
      return ch;
}
void add_item()
{
      struct inventory item;
      FILE *ft;
      char x='Y';
      ft=fopen("inventory","a+");
      do
      {
            char ch;
            printf("\nEnter item name,price,quantity to be stored: ");
            scanf("%s %d %f %d",item.name,&item.code,&item.price,&item.quantity);
            fprintf(ft,"%-6s    %d    %8.2f    %7d\n",item.name,item.code,item.price,item.quantity);
            printf("Type 'Y' to repeat the operation\n");
            scanf("\n%c",&ch);
            x=ch;
      }while(x=='Y');
      fclose(ft);
}
void read_item()
{
      struct inventory item;
      FILE *ft;
      ft=fopen("inventory","r");
      printf("NAME      CODE      PRICE     QUANTITY");
      while(feof(ft)==0)
      {
            fscanf(ft,"%s     %d     %f     %d\n",item.name,&item.code,&item.price,&item.quantity);
            printf("\n%-6s      %d    %8.2f    %7d",item.name,item.code,item.price,item.quantity);
      }
      fclose(ft);
}
void modify_item()
{
      struct inventory item;
      FILE *ft,*fp;
      ft=fopen("inventory","r");
      fp=fopen("temp","w+");
      int code;
      int quant;
      printf("\nenter the item code who's quantity is to be modified and the new quantity:\n");
      scanf("%d %d",&code,&quant);
      while(!feof(ft))
      {
            fscanf(ft,"%s     %d     %f     %d\n",item.name,&item.code,&item.price,&item.quantity);
            if(item.code!=code)
            fprintf(fp,"%-8s    %d    %8.2f    %7d\n",item.name,item.code,item.price,item.quantity);
            else
            {
                  item.quantity=quant;
                  fprintf(fp,"%-8s    %d    %8.2f    %7d\n",item.name,item.code,item.price,item.quantity);
            }
      }
      fclose(ft);
      fclose(fp);
      remove("inventory");
      rename("temp","inventory");
}
void delete_item()
{
      struct inventory item;
      FILE *ft,*fp;
      int code;
      ft=fopen("inventory","r");
      fp=fopen("temp","w+");
      printf("\nenter the code of item to be deleted:\n");
      scanf("%d",&code);
      while (!feof(ft))
      {
            fscanf(ft,"%s     %d     %f     %d\n",item.name,&item.code,&item.price,&item.quantity);
            if(code!=item.code)
            fprintf(fp,"%-8s    %d    %8.2f    %7d\n",item.name,item.code,item.price,item.quantity);
      }
      fclose(ft);
      fclose(fp);
      remove("inventory");
      rename("temp","inventory");
}
void checkitem()
{
      struct inventory item;
      FILE *ft;
      int code;
      ft=fopen("inventory","r");
      printf("\n");
      printf("ALERT");
      while (!feof(ft))
      {
            fscanf(ft,"%s     %d     %f     %d\n",item.name,&item.code,&item.price,&item.quantity);
            if(item.quantity<20)
            printf("\n%s needs to be imported",item.name);
      }
      fclose(ft);
}