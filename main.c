#include <stdio.h>
#include <stdlib.h>
#include<string.h>
/*
typedef enum {Apple,Banana,Orange,Watermelon,Mango}Fruits;
typedef enum {Tomato,Peppers,Potato,Carrots,Broccoli}vegetables;
typedef enum {Milk,Yoghurt,Cheese}dairy;
typedef enum {Meat,Fish,Chicken,Egg}protein;
typedef enum {Rice,Oat,Bread,Serial,Pasta}grains;
*/
int hashing (char* name);
int hashCode(int key);
struct DataItem *search(int key);
void insert(char * name,int price,int type,char * catougery_name );
void ordering(char* name,FILE * receipt);
void receipt_print(FILE * receipt);

typedef enum {fruits,vegetables,dairy,protein,grains}producets_types;

struct product
{
    int key;
    int price;
    char name[15];
    int required;
    char product_category[15];
    int product_key;
};


struct product* products[255];
char    keys[100];
char numberoforders;
char* product_type[11];
int main()
{
    //typedef enum Fruits{Apple,Banana,Orange,Watermelon,Mango}Fruits;
    ///parsing variables init
    char * p1=NULL;
    char * p2=NULL;
    char * line;
    //printf("the first key %d\n",products[1].key);
    /// Files init
    FILE  * data_base,*order,*receipt;
    data_base=fopen("data_base.txt","r");
    order=fopen("order.txt","r");
    receipt=fopen("receipt.txt","w");
    fprintf(receipt,"\n-----------------------------------------------------------------------------------\n\r");

    fprintf(receipt,"   \t\t\t\t THE UNAVAILABLE ITMES  \n\r");
    fprintf(receipt,"-----------------------------------------------------------------------------------\n\r");

    /*fgets(line,20,data_base);
    printf("%s\n",line);
*/
    //fgets(line,20,data_base);
    //printf("%s\n\n",line);
    int temp_key;
    int temp_price;
    char temp_name[15];
    int temp_required;
    //int temp_product_key=0;
    char temp_product_category[15];
    int static temp_product_key;
    int i;
while(fgets(line,20,data_base)){
///data used temp init
     temp_key=0;
     temp_price=0;
     temp_name[15]=0;
     //temp_product_key;

///data parsing


    //p1 = strtok(line, "%");
    //strlwr(p1);
    //printf("the value after token %% is %s \n",p1);
    p1 = strtok(line, ",");
    strlwr(p1);
  //  printf("the value after token , is %s \n",p1);
    p2 = strtok(NULL, "\n");
    strlwr(p2);
    //printf("the value after token ' ' is %s \n",p2);
if (p2==0&&p1[1]!=0){

    p1 = strtok(line, "%");
    strlwr(p1);
   // printf("the value after token %% is %s \n",p1);

    //printf("the hashing value is %d\n",hashing(p1)%11);
    product_type[hashing(p1)%11]=p1;
    //printf("the hashing value is %s\n",product_type[hashing(p1)%11]);
    //printf("hamo");
    strcpy(temp_product_category,p1);
     temp_product_key=hashing(p1)%11;
//    printf("product key is %d",temp_product_key);

}
else if(p1[1]!=0) {
    p2 = strtok(line+strlen(p1)+1, "\n");
    //p2 = strtok(p2, "\n");
    //printf("the value after token ' ' is %c  \n",p2[1]);
    i=0;
    temp_key=hashing(p1);
    //while(p2[i]>'0'){
    temp_price=atoi(p2);
    //temp_price+=p2[0]-'0';
    //if (p2[1]-'0'>0)temp_price+=p2[1]-'0';
    //i++;}
    strcpy(temp_name,p1);

//printf("product key is %d",temp_product_key);
//printf("name is %s\n",temp_name);
//printf("key is %d\n",temp_key);
//printf("price is %d\n",temp_price);
//printf("product category is %s\n",temp_product_category);
//printf("product key is %d\n",temp_product_key);
insert(temp_name,temp_price,temp_product_key,temp_product_category);
//void insert(char * name,int price,int type,char * catougery_name )
}
}
//display();

///reading data in the order
 printf("\n\n");
while(fgets(line,20,order)){
p1=strtok(line,"\n");
strlwr(p1);
//printf("%s\n",p1);
ordering(p1,receipt);

}
fprintf(receipt,"\n\r");

    fprintf(receipt,"-----------------------------------------------------------------------------------\n\r");
       fprintf(receipt,"    Food\t\t Number\t\t Price\t\t Cost\t\t Category\n\r");
    fprintf(receipt,"-----------------------------------------------------------------------------------\n\r");
    receipt_print(receipt);
//display();




 //   printf("the value after token ' ' is %d \n",strcmp(p2,p1));
    //printf("Hello world!\n");
    return 0;
}





int hashing (char* name){

int key=0;
int i=0;
//printf("the name is %s\n",name);
while (name[i]!='\n'&&name[i]!=NULL){

    key +=name[i]-'a';
    //printf("the key value number %d is  with letter %c\n",key,name[i]);

    i++;
}
//key+=' ';
return key;
}


int hashCode(int key) {
   return key % 255;
}


void insert(char * name,int price,int type,char * catougery_name ){

   struct product *item = (struct product*) malloc(sizeof(struct product));
   item->price = price;
   strcpy(item->product_category,catougery_name);
   strcpy(item->name,name);
   item->product_key=type;
   item->required=0;
   int key=0;
    key=hashing(name);
   item->key = key;

   //get the hash
   int hashIndex = hashCode(key);

   //move in array until an empty or deleted cell
   while(products[hashIndex] != NULL && products[hashIndex]->key != -1) {///expected error
      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= 255;
   }

   products[hashIndex] = item;
}


struct DataItem *search(int key) {
   //get the hash
   int hashIndex = hashCode(key);

   //move in array until an empty
   while(products[hashIndex] != NULL) {

      if(products[hashIndex]->key == key)
         return products[hashIndex];

      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= 255;
   }

   return NULL;
}


void display() {
   int i = 0;

   for(i = 0; i<255; i++) {

      if(products[i] != NULL)
         printf(" (%d,%d,%s,%s,%d,required=%d)",products[i]->key,products[i]->price,products[i]->name,products[i]->product_category,products[i]->product_key,products[i]->required);
      else
         printf(" ~~ ");
   }

   printf("\n");
}


void ordering(char* name,FILE * receipt){

int key=0;
key=hashing(name);
struct product* temp;
    temp=search(key);
if (temp==NULL){
       fprintf(receipt," \t\t %s",name);
    ///print not avavilabe
}
else{
        if (temp->required==0){
                keys[numberoforders]=key;
                numberoforders++;
        }
temp->required++;
}
}

void receipt_print(FILE * receipt){
struct product *temp =NULL;
int total=0;
int i =0;
for (i=0;i<numberoforders;i++){
    temp=search(keys[i]);
    if (temp==NULL)continue;
    total +=temp->price*temp->required;

         fprintf(receipt,"    %s\t\t %d\t\t %d\t\t %d\t\t %s\n",temp->name,temp->price,temp->required,temp->required*temp->price,temp->product_category);
    //switch(temp->product_key){
        /*///prints
        case fruits: ///edit with numbers of the data
        break;
        case vegetables:
        break;
        case dairy:
        break;
        case protein:
        break;
        case grains:
        break;
*/
    //}
    //print data in recipt

}
        fprintf(receipt,"\n-----------------------------------------------------------------------------------\n\r");

        fprintf(receipt,"\n\rthe total value is %d",total);
        fprintf(receipt,"\n-----------------------------------------------------------------------------------\n\r");


}
