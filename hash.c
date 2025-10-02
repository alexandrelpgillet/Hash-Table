#include <stdlib.h>
#include <stdio.h>

typedef struct node{
  
    struct node *next;
    char *string;
    int string_value;

}node;


typedef struct{

    node *head;
    node *tail;
    int size;;
}list;


typedef struct {

    list *V;
    int M;
    int size;     

}hashTable;


//Função para realizar a copia de strings 

char* copyString(char *a, char*b){
    

    if(b==NULL) return NULL;
    
    int i = 0;

    while(b[i]!= '\0'){
        
        i++;
        
    };

    
    

    a = (char*)malloc(sizeof(char*)*i+1);
    
    for(int j=0 ; j< i; j++){
        a[j]=b[j];
    }

    return a;

}

//Função conversora de string para int via ASCII
int convertAscIIforInt(char *c){
    
    int num =0;

    int i =0;
    

    while(c[i]!='\0')
    {
        num+=c[i];
        i++;

    }
    

    return num;

}


//Função para fazer uma comparação profunda das Strings de nome
int deepCompareString(char *a, char *b){


    if(sizeof(a)== sizeof(b))
    {
        
        for(int i = 0 ; i<(int) sizeof (a) && a[i]!='\0' ; i++){
            
            if(a[i]!=b[i])
            {
                return -1;
            }

        }

        return 0;
        
    }

    return -1;
}



//Função para concatenar strings 
char* concatString(char*a , char *b){

    char *aux = (char*) malloc(sizeof(a) + sizeof(b)+1);
    
    int i,j,k;



    for(i =0 ; i<(int)sizeof(a) && a[i]!='\0'; i++)
    {
         
        aux[i] = a[i];

    }

    aux[i] = ' ';

    for(j =i+1, k=0 ; j < (int) sizeof(b); j++,k++){
 
        aux[j]=b[k];
    };

    if(a) free(a);
    if(b) free(b);

    return aux;
}


//Função para criar um node na lista 

node* createNode(char *s){

    node *p = (node*) malloc(sizeof(node));
    
    if(!p) return NULL;

    
    
    

  
    p->string = copyString(p->string, s);


    
    p->string_value = convertAscIIforInt(p->string);
    

    p->next = NULL;

    return p;
    
}



//Função para inserir um node na lista encadeada
void  insertList(list *l,char *s){
    
    node *p = createNode(s);

    if(l->head == NULL && l->tail == NULL){
        
        l->head = p;
        l->tail = p;
    
    }
    else {

        l->tail->next = p;
        l->tail = p;
    }

    l->size+=1;

}



//Função para remover um node da lista encadeada

int removeList(list *l,char *s){

    
    node *prev = NULL;
    node *aux = l->head;

    int stringValueSearch = convertAscIIforInt (s);


    
    
    while (aux->string_value != stringValueSearch && aux!=NULL)
    {
        
        prev = aux;

        aux = aux->next;

    }
    
    //Caso o node a ser excluido não seja encontrado retornamos -1
    if(!aux) return -1;

    

    //Caso o meu node esteja no head ou no tail

    if(aux==l->head || aux== l->tail)
    {
        
        //Caso na lista tenha apenas 1 node Head == Tail
        if(l->head == l->tail)
        {
            free(aux);
            l->head = NULL;
            l->tail = NULL;
            
        }

        //Caso minha lista tenha mais de 1 node e o node a ser excluido esteja no Head
        else if(l->head){

            l->head = aux->next;
            free(aux);
        }

        //Caso a minha lista tenha mais de 1 node e o node a ser excluido esteja no Tail
        else if(l->tail){
            

            l->tail=prev;
            
            prev->next = NULL;

        }

    
    }
    //Caso a minha lista tenha mais de 2 nodes e que o node a ser excluido não esteja nem no Tail e nem no Head 
    else{

        prev->next = aux->next;
        free(aux);
    }

    l->size -=1;

    return 0;


}


//Função busca dentro de uma lista;
char * searchList(list *l,char *s){

    node  *aux = l->head;
    
    int stringValueSearch = convertAscIIforInt(s);
    
    int quant =0;
    
    char *c;

    while(aux!=NULL){
        
        //Caso a string seja encontrada  retornamos uma cópia de char dela (não retornamos a localização do meu item por questão de segurança)
        if(aux->string_value == stringValueSearch)
        {

            int res = deepCompareString(aux->string, s);
            
            if(res==0)
            {   
                if(quant ==0) 
                {   

                    
                
            
                    c= copyString(c, aux->string);
                }

                quant+=1;

    
            }
                   
        }

        aux= aux->next;

    }
    
    //Caso exista mais de um nome em comum, printamos o número de usuário encontrados
    if(quant>1){
        
        
        int decimal_case = 0;
        int quant_aux = quant;
        
        while(quant_aux>0){

            decimal_case+=1;
            quant_aux= (int)quant_aux/10;
        }

        char *quantString = (char*)malloc(sizeof(char*)*decimal_case);

        sprintf(quantString,"%d",quant);

        char *resp = concatString (quantString, "user's found by name");

        resp = concatString(resp , c);
        

        return resp;
    }

    //Caso só tenha um usuário retornamos somente o nome dele
    else
    {
        return c;
    }

    return NULL;

}


//Função apagar lista encadeada
void clearList(list *l){

    node *aux = l->head;
    node *temp;
     
    while(aux){
        temp = aux;
        aux = aux->next;
        
        temp->string_value=0;
        free(temp->string);
        free(temp);
        
    }

    l->size =0;
}


void createHashTable(hashTable *H,int M){
        
     H->V = (list*) malloc(sizeof(list)*M);

     for(int i =0 ; i<M; i++){
     
        H->V[i].head = NULL;
        H->V[i].tail = NULL;
        H->size =0;
     }
     
     H-> M = M;
     H->size = 0;

     if(!H->V) exit(-1);

    

}


void insertHashTable(hashTable *H, char *string){
    
    
    if(string==NULL)return;

    int stringValue = convertAscIIforInt(string);

    int pos = (int) (stringValue % H->M);
    
    list *l =  H->V+pos;

    insertList(l,string);
    
    H->size+=1;
}


void removeHashTable(hashTable *H, char *string){

    int stringValue = convertAscIIforInt(string);

    int pos = (int) (stringValue % H->M);

    list *l = H->V+pos;

    removeList(l,string);

    H->size -=1;
}

char * searchHashTable(hashTable *H, char *string){

    int stringValue = convertAscIIforInt(string);

    int pos = (int) (stringValue);

    list *l = H->V+pos;

    char *response = searchList(l,string);
    
    if(!response){

        return NULL;
    }

    return response;
}




void deleteHashTable(hashTable *H){

    int M = H->M;
    
    for(int i = 0 ; i< M ; i++){

        
        clearList(H->V+i);
        
    }

    free(H->V);
    
    if(H->V) exit(-1);

}










int main(){

    hashTable hash;
    
    createHashTable(&hash,7);

    char string_test[4]="ade";
    string_test[3]='\0';


    

    insertHashTable(&hash, string_test);

    deleteHashTable(&hash);

}
