#include <stlib.h>

typedef struct {
  
    node *next;
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



void createHashTable(hashTable *H,int M){
        
     H->V = (list*) malloc(sizeof(list)*M);

     for(int i =0 ; i<M, i++){
     
        H->V[i]->head = NULL;
        H->V[i]->tail = NULL;
        H->size =0;
     }
     
     H-> M = M
     H->size = 0;

     if(!H->V) exit(-1);

    

}


void insertHashTable(hashTable *H, char *string){
    
    int stringValue = convertAscIIforInt(string);

    int pos = (int) (stringValue % H->M);
    
    list *l =  H->(V+pos);

    insertList(l,string);
    
    H->size+=1;
}


void removeHashTable(hashTable *H, char *string){

    int stringValue = convertAscIIforInt(string);

    int pos = (int) (stringValue % H->M);

    list *l = H->(V+pos);

    removeList(l,s);

    H->size -=1;
}

char * searchHashTable(hashTable *H, char *string){

    int stringValue = convertAscIIforInt(string);

    int pos = (int) (stringValue);

    list *l = H->(V+pos);

    char *response = searchList(l,string);
    
    if(!response){

        return NULL;
    }

    return response;
}




void deleteHashTable(hashTable *H){

    int M = H->M;
    
    for(int i = 0 ; i< M ; i++){

        
        clearList(H->V[i]);
        
    }

}



//Função para realizar a copia de strings 

void copyString(char *a, char*b){
    


    for(int i=0 ; i< (int) sizeof(a), i++){
        a[i]=b;
    }
}



//Função para criar um node na lista 

node* createNode(char *s){

    node *p = (node*) malloc(sizeof(node));
    
    if(!p) return NULL;
    
    p->string = (char*) malloc(sizeof(s));
    

    copyString(p->string, s);
    
    p->string_value = convertAscIIforInt(p->string);
    
    p->next = NULL;

    return node;
    
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

    
    list *prev = NULL;
    list *aux = l->head;

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
    
    while(aux!=NULL){
        
        //Caso a string seja encontrada  retornamos uma cópia de char dela (não retornamos a localização do meu item por questão de segurança)
        if(aux->string_value == stringValueSearch)
        {
            char *c = (char *) malloc(sizeof(aux->string));
            
            copyString(c, aux->string);

            return c;
        }

        aux= aux->next;

    }

    return NULL;

}


//Função apagar lista encadeada
void clearList(list *l){

    node *aux = l->head;
    node *temp;

    while(aux){
    
        temp = aux;
        aux = aux->next.
        free(temp);
        
    }

    l->size =0;
}



//Função conversora de string para int via ASCII
int convertAscIIforInt(char *c){
    
    int num =0;

    for(int i=0 ;i<(int)sizeof(c); i++) 
    {
        num+=c[i];
    }

    return num;
}


int main(){


}
