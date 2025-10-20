#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>



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



typedef struct{
    
    char *string;

}data;

typedef struct{

    data *V; 
    int size;

}dictionary;

//Função para realizar a copia de strings 

char* copyString(char *a, char*b){
    


    if(b==NULL) return NULL;
    
    int i = 0;



    while(b[i]!= '\0'){
        
        i++;
        
    };

    
    

    a = (char*)malloc(sizeof(char)*i+1);
    
    if(!a) return NULL;

    for(int j=0 ; j<=i; j++){
        a[j]=b[j];
    }

    return a;

}

//Função conversora de string para int via ASCII
int convertAscIIforInt(char *c){
    
    int num =0;

    int i =0;
    
    if(c==NULL) return -1;

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
char* concatString(char*a , char *b, int isDynamicAllocationMemoryA, int isDynamicAllocationMemoryB){

    
    int i =0;
    int j= 0;
    int k;
    int l;
    int m;

    if(a)
    {
      while(a[i]!='\0') i++;
    }


    if(b)
    {
      while(b[j]!='\0') j++;

    }
 
    char *aux = (char*) malloc((sizeof(char))*(i+j)+3);


    for(k =0 ; k<i ; k++)
    {
         
        aux[k] = a[k];

    }

    aux[k] = ' ';
    

    for(l =k+1, m=0 ; m < j  ; m++,l++){
 
        aux[l]=b[m];
    };

    aux[l] = '\0';



    if(a && isDynamicAllocationMemoryA) free(a);
    if(b && isDynamicAllocationMemoryB) free(b);



    return aux;
}


dictionary* createDictionary(dictionary *d, int size){
     
    d->V = (data*) malloc(sizeof(data)*size);
    
    d->size =0;


    if(!d) exit (-1);

    return d;

}

void insertDicitonary(dictionary *d, char *s){

    int i =0;
    int pos = d->size;
    
     
    if(s) 
    {

        
        
        d->V[pos].string = NULL;


        d->V[pos].string= copyString(d->V[pos].string,s);


        d->size+=1;
       
    }
}

void deleteDictionary(dictionary *d){
 
    int size = d->size;

    for(int i =0 ; i<size ; i++){
        

        free(d->V[i].string);

    }

    free(d->V);

    d->size =0;
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
            aux->string_value = 0;
            free(aux->string);
            free(aux);
            l->head = NULL;
            l->tail = NULL;
             
        }

        //Caso minha lista tenha mais de 1 node e o node a ser excluido esteja no Head
        else if(l->head){
            
            aux->string_value =0;
            free(aux->string);
            l->head = aux->next;
            free(aux);
        }

        //Caso a minha lista tenha mais de 1 node e o node a ser excluido esteja no Tail
        else if(l->tail){
            
   
            l->tail=prev;
            
            prev->next = NULL;
            aux->string_value=0;          
            free(aux->string);
            free(aux);

        }

    
    }
    //Caso a minha lista tenha mais de 2 nodes e que o node a ser excluido não esteja nem no Tail e nem no Head 
    else{

        prev->next = aux->next;
        aux->string_value=0;
        free(aux->string);
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

        char *quantString = (char*)malloc(sizeof(char)*decimal_case + 1);
        
        
        sprintf(quantString,"%d",quant);

        

        char *resp = concatString (quantString, "user's found by name \0",1,0);


        resp = concatString(resp , c,1,1);
        

        return resp;
    }

    //Caso só tenha um usuário retornamos somente o nome dele
    else if(quant ==1)
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
        H->V[i].size =0;
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

    int pos = (int) (stringValue) % H->M;

    list *l = H->V+pos;

    char *response = searchList(l,string);
    
    
    
    if(!response){
        
        response = concatString("ERROR - User not found by name",string,0,0);

        
        return response;
    }

    

    return response;
}




void deleteHashTable(hashTable *H){

    int M = H->M;
    
    for(int i = 0 ; i< M ; i++){

        
        clearList(H->V+i);
        
    }

    if(H->V) free(H->V);

    
   

}




int getSizeHashTable(hashTable *H){
    return H->size;
}

long double  getStandartDeviationHashTable(hashTable *H){

    int i =0;

     
    list *l = NULL;

    long double media = 0.0;
    
    long double sum=0.0;
    
    long double standartDeviation=0.0;
 

    for(i =0 ; i< H->M; i++){
        
        l = H->V+i;

        printf("List %d size nodes = %d\n", i+1 ,l->size );
        media+= (long double) l->size;

    }

    media/=(long double) H->M;
    

    for(i = 0 ; i< H->M; i++){
        
        l = H->V+i;
        

        sum += (long double) (l->size - media) * (l->size - media);
        
        
    
    

    }
    
    sum/=H->M;

    standartDeviation = sqrt(sum);

    return standartDeviation;



}

char *genRandomString(int maxSize){
    
    int i;

    int size = (1+rand() % maxSize); 
    
    char *string = (char*) malloc(sizeof(char)*size+1);
   
    for(i =0 ; i< size ; i++){
    
        //Carateres de 32 a 126

        char c = (33+rand()%94);
        
        string[i] = c;


    }

    string[i]='\0';

    return string;

}




float getAverageColission(hashTable *H){

    float average = 0;

    int N = H->M;

    for(int i =0 ; i<N ; i++){

        if(H->V[i].size>1)
        {

           average = average + H->V[i].size;
        }    
    }

    average = average / (float) N;
    
    return average;
}




double beanchMarkSearch(hashTable *H, char *string){
     
    clock_t start_time;
    clock_t end_time;
    clock_t time;
    double time_in_miseconds; 
    
    start_time = clock();

    char *c = searchHashTable(H,string);
    
    
    end_time = clock();
    
    time = end_time - start_time;

    time_in_miseconds = (((double)time)/ CLOCKS_PER_SEC)*1000;
    
    free(c);
    return time_in_miseconds;


}


double getSearchTimeAverage(double *T, int N){

    double average =0.0;
    
    for(int i =0 ; i<N; i++){

        average = average+ T[i];
    
    }

    average = average/(double)N;
    
    return average;
}


void initTest(hashTable *H, dictionary *D,int *M , int quantHashKey,int quantTest){

    double *times_Search;
    double timeSearchRandom;
   
    FILE *ftpr;

    ftpr = fopen("Teste/result.txt", "w");
    
    

    srand(time(NULL));            

    for(int i =100 ;  i<=100000; i= i*10)
    {
        
        

        for(int j =0 ; j<quantHashKey ; j++)
        {
            
            double endAverageSearch =0;
        
            double endColissionAverage = 0;
            
            for(int k=0 ; k < quantTest ; k++)
            {   


                times_Search = (double*) malloc(sizeof(double)*quantTest*quantTest);

                createHashTable(H,M[j]);
                
                createDictionary(D,i);

              


                for(int l = 0 ; l<i ; l++){

                  char *string_random = genRandomString( 1+rand()%1000);
                    
                   insertDicitonary(D,string_random);
                    
                   insertHashTable(H,string_random);
                     
                   free(string_random);
                
                }

                for(int m = 0 ; m<quantTest; m++)
                {
                  char *stringSearchRandom = D->V[rand()%i].string;

                  timeSearchRandom =  beanchMarkSearch(H,stringSearchRandom);
                    
                  times_Search[m] = timeSearchRandom; 
                }
                
                
                
                double searchTimeAverage = getSearchTimeAverage(times_Search, quantTest);
                double averageColission = getAverageColission(H);
                
                /*
                printf("Quantidade de String = %d | M = %d\n", i, M[j]);
                printf("Tempo médio de busca = %lf seg(s) em 10 buscas aleatorias\n", searchTimeAverage);;
                printf("Colisão média por hash = %lf colisões \n", averageColission);
                */
                endAverageSearch+= searchTimeAverage;
                endColissionAverage+= averageColission;
                
                if(times_Search) free(times_Search);

                deleteDictionary(D);

                deleteHashTable(H);


                

            }

            endAverageSearch =endAverageSearch/10.0;
            
            endColissionAverage = endColissionAverage/10.0;

            
            printf("Quantidade de String = %d | M = %d\n", i, M[j]);
            printf("Tempo médio de busca = %lf milisegundo(s)\n", endAverageSearch);
            printf("Colisão média por lista da hash table = %lf colisões\n", endColissionAverage);
            printf("-------------------------------------------------------------\n");
            
            fprintf(ftpr, "%d;%d;%lf;%lf\n",i,M[j],endAverageSearch,endColissionAverage);
        }






    }

    fclose(ftpr);
            

        

    

}

int main(){

    hashTable hash;
    
    dictionary dict ;

    int M[3]={31,79,151};

    initTest(&hash, &dict, M, (int)sizeof(M)/4 , 10);

    //createHashTable(&hash,3);
    
    //createDictionary(&dict,10000);

    //char string_test1[]="A"; // A == 65 % 3 = 2  
    //char string_test2[]="B"; // B == 66 % 3 = 0
    //char string_test3[]="C"; // C == 67 % 3 = 1

    



    /*
    
    
    
    for(int i =0 ; i<10000 ; i++)
    {
        
        char *string_random = genRandomString(50);
        


        
        insertDicitonary(&dict, string_random);

        insertHashTable(&hash, string_random);

        free(string_random);

      
    }

    */
    
    /*
    for(int i =0 ; i<10000; i++)
    {   
        char *c = i+1;
        removeHashTable(&hash,c);
        
    }
    */
    

     
    //removeHashTable(&hash, string_test1);
    
    //char *c1 = searchHashTable(&hash, "Alexandre");
    

    //printf("%s\n", c1);
    
    //printf("Standart Deviation in Hash Table = %0.4Lf\n", getStandartDeviationHashTable(&hash));
    
    //free(c1);
        

    //deleteDictionary(&dict);

    //deleteHashTable(&hash);

    
}
