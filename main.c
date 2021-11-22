#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
const char* getOpcodeHex(const char*);

//char* outputFilename = strcat(strtok(argv[1],"."),".obj");
struct Symbol {
int address;
int sourceLineNumber;
struct Symbol* next;
char name[7];
char opcode[7];

};

struct Symbol* isInHashes(struct Symbol* Hashes[],const char*);



int main(int argc, char *argv[]) {
  int sourceLineCounter=0; 
int startingLine=0;
int locationCounter=0;
if (argc != 2)
{
printf("USAGE: %s <filename>\r\n", argv[0]); 
return 1;
}

 FILE *inputFile;
 inputFile = fopen(argv[1], "r");

if (!inputFile){
printf("ERROR: %s could not be opened for reading.\r\n", argv[1]);
return 1; 

}
char delimit[]=" \t\r\n\v\f";
FILE *outputFile;
bool end=false;
int operand=0;
outputFile = fopen("OUT.txt", "w");
char line[1024]; 
bool tf=true;
struct Symbol *Hashes[26];
char * token;
int i;
for (i=0; i<26;i++)
{
	Hashes[i]=NULL;
}
bool firstLine=true;



while (fgets(line,1024,inputFile))
{
	tf=true;

int length;
length = strlen(line);




//the 1 is to include the new line char
if (length==1)
{
    printf("LINE %d ERROR: Program contains empty line.\r\n",sourceLineCounter);
    return 1;
}
i=0;









if (length>0)
{
if (line[0] == 32)
{

tf=false;
sourceLineCounter++;
locationCounter+=3;
}
if (line[0] == 35){
	
	tf=false;
  sourceLineCounter++;
  
}
if (line[0] == 9){
	
	tf=false;
  sourceLineCounter++;
  locationCounter+=3;

}
if (tf==true){
	sourceLineCounter++;
  
  char name[7];
  char opcode[7];
   
memset(name, 0, sizeof name);


  


i=0;
unsigned int *q=malloc(sizeof(unsigned int));  
char * c=malloc(sizeof(char));

   token = strtok(line, delimit);
   // loop through the string to extract all other tokens
   while( token != NULL ) {
     if (i==0)
     {
       
       


       if (end)
       {
         printf("LINE %d ERROR: intsructions after END.\r\n",sourceLineCounter);
         return 1; 
       }
       strcpy(name, token);




        if (0==strcmp(name, "START"))
        {
          printf("LINE %d ERROR: Directive as symbol.\r\n",sourceLineCounter);
          return 1;
        }
          if (0==strcmp(name, "END"))
        {
          printf("LINE %d ERROR: Directive as symbol.\r\n",sourceLineCounter);
          return 1;
        }
          if (0==strcmp(name, "BYTE"))
        {
          printf("LINE %d ERROR: Directive as symbol.\r\n",sourceLineCounter);
          return 1;
        }
          if (0==strcmp(name, "WORD"))
        {
          printf("LINE %d ERROR: Directive as symbol.\r\n",sourceLineCounter);
          return 1;
        }
          if (0==strcmp(name, "RESB"))
        {
          printf("LINE %d ERROR: Directive as symbol.\r\n",sourceLineCounter);
          return 1;
        }
          if (0==strcmp(name, "RESW"))
        {
          printf("LINE %d ERROR: Directive as symbol.\r\n",sourceLineCounter);
          return 1;
        }
          if (0==strcmp(name, "RESR"))  
        {
          printf("LINE %d ERROR: Directive as symbol.\r\n",sourceLineCounter);
          return 1;
        }
          if (0==strcmp(name, "EXPORTS"))  
        {
          printf("LINE %d ERROR: Directive as symbol.\r\n",sourceLineCounter);
          return 1;
        }


















     }
     if (i==1)
     {
       strcpy(opcode, token);

     }if (i==2)
     {
       if (firstLine)
       {
          i=0;
          if (strcmp(opcode,"START"))
        {
          printf("LINE %d ERROR: no START directive.\r\n",sourceLineCounter);
         return 1; 
        }

          while (i<strlen(token)){
         if (!isxdigit(token[i]))
                    {
                      printf("LINE %d ERROR: Invalid start hex.\r\n",sourceLineCounter);
                      return 1;
                    }
                    i++;
          }

       }




       if (!strcmp(opcode, "RESB"))
         {
           operand=atoi(token);
          
         break;
         }

if (!strcmp(opcode, "BYTE"))
{

  if (token[0]=='C')
  {
            i=1;
                operand=0;
                while (i<strlen(token)){
                if (token[i]!=39)
                 {
                  operand+=sizeof(token[i]);
                 }
              i++;
              }
   
    i=0;
  }

int counter=0;
              if (token[0]=='X')
              {
                i=1;
                  operand=1;
                  while (i<strlen(token)){
                    
                    if (!isxdigit(token[i]) && token[i]!=39)
                    {
                      printf("LINE %d ERROR: Invalid hex.\r\n",sourceLineCounter);
                      return 1;
                    }


                if (token[i]!=39)
                 {
                  counter++;
                 }
                 
              i++;
              }
              if (counter%2==1)
              {
                counter++;
              }
operand=(counter/2);

              

      }
      break;

}

       if(!strcmp(token,"C'EOF'"))
       {
         operand= 3;
        //operand=sizeof('EOF');
        break;
       }
      

         if (token[0]=='C' && 0!=strcmp(token,"C'EOF'")){
          sscanf(token, "%c" , c);
          operand=sizeof((int)*c);
         break;
          }
          else
      sscanf(token, "%X" , q);
   
      sprintf(token, "%u", *q); 
      
      operand=atoi(token);

    
     }
       //printing each token
      token = strtok(NULL, delimit);
      i++;
   }
  



 
 

if (firstLine==true)
{


        
       



  startingLine=operand;



//if null starting address set to 0000
if (token==NULL && i==2)
{
startingLine=0;
}


  locationCounter=operand;
  if (operand<=0 && operand>=32768)
  {
printf("LINE %d ERROR: Invlaid Starting Location.\r\n",sourceLineCounter);
return 1;
}
}
	
struct	Symbol *Temp = ((struct Symbol*)malloc(sizeof(struct Symbol)));
Temp->sourceLineNumber=sourceLineCounter;
Temp->address=locationCounter;
//Temp.sourceLineNumber=27;
//Temp.address=x1000;
struct Symbol *last; 

strcpy(Temp->name, name);




struct	Symbol *Current;
tf=false;
//*Current->address;
Current=Hashes[name[0]-65];
//symbol table
if (name[0]>64 && name[0]<91)
  {
    if(Hashes[name[0]-65]==NULL)
      {
	    Hashes[name[0]-65]=Temp;
      }
    else
      {
        while (Current!=NULL)
        {
           
           
             if (!strcmp(Current->name, name))
            {
              printf("LINE %d ERROR: Duplicate symbol.\r\n",sourceLineCounter);
              return 1;
            }

            


            last=Current;
            Current=Current->next;
            

            


            
          
         
        } 
        last->next=Temp;
    
      }
  }
else 
{
  printf("LINE %d ERROR: invalid symbol.\r\n",sourceLineCounter);
  return 1; 
}

//optable


int i;


struct	Symbol *OTemp = malloc(sizeof(struct Symbol));
OTemp->sourceLineNumber=sourceLineCounter;
OTemp->address=locationCounter;
struct Symbol *Olast; 

strcpy(OTemp->opcode, opcode);



if (locationCounter<0 && locationCounter>8388608)
{
 
  printf("LINE %d ERROR: SIC ran out of memory.\r\n",sourceLineCounter);
  return 1;
}



//print to seperate file.

if (strcmp(opcode,"END"))
{
 fprintf(outputFile, "%-7s %-7X\n",name,locationCounter);
}
else
{
  fprintf(outputFile, "%-7s %-7X",name,locationCounter);

  break;
}




if (!strcmp(opcode, "WORD"))
{


        if(operand > 137922055 || operand < -137922056){
        
        
        printf("LINE %d ERROR: Contains a word that exceeds a 2^23 bit size.\r\n",sourceLineCounter);
          return 1;


        }

locationCounter+=3;

}
else
if (!strcmp(opcode, "RESW"))
{
 
locationCounter+=3*operand;
}
else
if (!strcmp(opcode, "RESB"))
{
locationCounter+=operand;
}
else
if (!strcmp(opcode, "BYTE"))
{
locationCounter+=operand;
}
else
{
  if (firstLine==false)
  locationCounter+=3;
}
firstLine=false;



if (!strcmp(opcode, "END"))
{
end=true;
}
}
}
}

fclose(inputFile);
fclose(outputFile);



int size=3;
struct	Symbol *inTable=malloc(sizeof(struct Symbol));
struct	Symbol *operandSymbol=malloc(sizeof(struct Symbol));
FILE *passTwoReader=fopen("OUT.txt", "rb"); 



//pass 2

char longLine[1024];
int byte=0;
char *concat;
char concatContinued [1024];
char byteC[sizeof(concat)];
char byteX[sizeof(concat)];
firstLine=true;
bool copyOffset=true;
int programLength=locationCounter-startingLine;
unsigned int *q=malloc(sizeof(unsigned int));
int x=0;


bool indexedAddressing=false;


char proName[7];

locationCounter=startingLine;
while (fgets(line,1024,passTwoReader))
{
token=strtok(line,delimit);
char nameOfProgram[sizeof(token)];
strcpy(nameOfProgram,token);
token = strtok(NULL, delimit);

int num = (int)strtol(token, NULL, 16);

if (firstLine==true)
{
strcpy(proName,nameOfProgram);
firstLine=false;
}
inputFile = fopen(argv[1], "r");
}


char opcode[7];
firstLine=true;


sourceLineCounter=0;
char *operandHex;
bool rSub;
bool nonSymbol;

 
char* outputFilename = strcat(argv[1],".obj");
FILE *passTwoWriter=fopen(outputFilename, "w+");

bool secondline=true;
firstLine=true;
while (fgets(line,1024,inputFile))
{
  bool longBYTE=false;
  if(copyOffset)
  {


    fprintf(passTwoWriter,"H%-6s%6.6X%6.6X\n",proName,startingLine,programLength);

    copyOffset=false;
    continue; 
  }
strcpy(longLine, line);
memset(byteC,0,strlen(byteC));
tf=true;
bool indexedAddressing=false;
int length;
length = strlen(line);
rSub=false;
nonSymbol=false;

if (length>0)
{
if (line[0] == 32)
{

tf=true;
sourceLineCounter++;

}
if (line[0] == 35){
	
	tf=false;
  sourceLineCounter++;
  continue;
}
if (line[0] == 9){
	
	tf=true;
  sourceLineCounter++;
 

}
if (tf==true){
	sourceLineCounter++;
  
  char name[7];
  
   
memset(name, 0, sizeof name);


i=0;
unsigned int *q=malloc(sizeof(unsigned int));  
char * c=malloc(sizeof(char));

  token = strtok(line, delimit);


i=0;
if (line[0] == 9)
{

i=1;
nonSymbol=true;
}
if (line[0] == 32)
{
nonSymbol=true;
i=1;
}
   // loop through the string to extract all other tokens
   while( token != NULL  ) {
     

     
     if (i==0)
     {
       
       strcpy(name, token);

      

      inTable=isInHashes(Hashes, token);


      if(NULL==inTable)
      {
       printf("ERROR: Line %d contains invalid, undeclared symbol '%s'.\n\r",sourceLineCounter, token);
        remove(outputFilename);
        return 1;
        
      }
   

     }

     if (i==1)
     {

       strcpy(opcode, token);
       
 if (nonSymbol && !strcmp(opcode, "RSUB"))
        {

          rSub=true;
          
        }
     

     }


     if (i==2)
     {
      

bool operandIsSymbol=true;
 if(0==strcmp(opcode, "START"))
        {
          
         operandIsSymbol=false;
        }
          if (0==strcmp(opcode, "END"))
        {
          operandIsSymbol=false;
        }
          if (0==strcmp(opcode, "BYTE"))
        {
          operandIsSymbol=false;
        }
          if (0==strcmp(opcode, "WORD"))
        {
          operandIsSymbol=false;
        }
          if (0==strcmp(opcode, "RESB"))
        {
          operandIsSymbol=false;
        }
          if (0==strcmp(opcode, "RESW"))
        {
          operandIsSymbol=false;
        }
          if (0==strcmp(opcode, "RESR"))  
        {
          operandIsSymbol=false;
        }
          if (0==strcmp(opcode, "EXPORTS"))  
        {
          operandIsSymbol=false;
        }
        if (0==strcmp(opcode, "RSUB"))  
        {
          operandIsSymbol=false;
        }
if (operandIsSymbol)
{
char g=token[strlen(token)-2];
char o=token[strlen(token)-1];


 if (g==',' && o=='X')
      {
       
         
        
      indexedAddressing=true;
      
      }

 

  char *indexed=token;
  char* indexedTemp;
  
   if (indexedAddressing)
   {
     indexedTemp=strtok(indexed,",");
   }
   else
   {
     indexedTemp=token;
   }
    operandSymbol=isInHashes(Hashes, indexedTemp);


if(NULL==operandSymbol)
      {
       printf("ERROR: Line %d contains invalid, undeclared symbol '%s'.\n\r",sourceLineCounter, indexedTemp);
        remove(outputFilename);
        return 1;
      }
   


}

       if (!strcmp(opcode, "RESB"))
         {
           operand=atoi(token);
         break;
         }

if (!strcmp(opcode, "BYTE"))
{

  if (token[0]=='C')
  {
    byte=1;
          int z=0;
            x=1;
                operand=0;
                while (x<strlen(token)){
                if (token[x]!=39)
                 {
                   byteC[z]=token[x];
                  operand+=sizeof(token[x]);
                 
                  z++;
                 

                 }

              x++;
              }
              
char output[2*strlen(byteC)];

              for(int z = 0; z < strlen(byteC); z++)
    {
        sprintf(output,"%s%X", output,byteC[z]);
    }   
 
char outputTemp[2*strlen(byteC)];




      for(int z = 0; z < strlen(output); z++)
    {
        outputTemp[z]=output[z+3];
    }   
   int temp = strlen(byteC);

          
   fprintf(passTwoWriter,"T%6.6X%2.2X%s\n",locationCounter,temp,outputTemp);


    x=0;
  }

int counter=0;
              if (token[0]=='X')
              {
                      byte=2;
                x=1;
                  operand=1;
                   int z=0;



                  while (x<strlen(token)){
               
                if (token[x]!=39)
                 {
                  byteX[z]=token[x];
                  z++;
                  counter++;
                 }
                 
              x++;
              }


              if (counter%2==1)
              {
                counter++;
              }
operand=(counter/2);

           
                         
   fprintf(passTwoWriter,"T%6.6X%2.2d%s\n",inTable->address,operand,byteX);
   

      }
      break;

}
         if (token[0]=='C'){
          sscanf(token, "%c" , c);
          operand=sizeof((int)*c);
         break;
          }
          else
      sscanf(token, "%X" , q);
   
      sprintf(token, "%u", *q); 
      
      operand=atoi(token);

    break;
     }
    
     
      i++;       
       //printing each token

      char * s = "'";
      token = strtok(NULL, delimit);
      if(token==NULL)
      break;
       int r=0;



  if (i>=2 && token!=NULL){

  concat = strtok(longLine, s);
      
 
         concat = strtok(NULL, "'");
           
           //longBYTE
           if (concat!=NULL)
           {
           
            longBYTE=true;

for (int z = 0; z < strlen(concat); z++) {
    sprintf(concatContinued, "%s%x", concatContinued, concat[z]);
  }
  
if (strlen(concatContinued)>60){
int counter=0;
char temp [strlen(concatContinued)];
for (int z=0; z<60; z++)
{
  temp[z]= concatContinued[z];
 
}


int sizeForTemp=strlen(temp);
int sizeForCont=strlen(concatContinued);

fprintf(passTwoWriter,"T%6.6X%d%s\n",locationCounter,sizeForTemp,temp);
strcpy( concatContinued, &concatContinued[59]);
locationCounter+=30;

sizeForTemp=strlen(concatContinued);

fprintf(passTwoWriter,"T%6.6X%d%s\n",locationCounter,sizeForTemp,concatContinued);
locationCounter+=strlen(concatContinued)/2;
if (strlen(concatContinued)%2==1)
locationCounter++;

continue;
}
 }
  } 
   }

if (!firstLine)
{




int firstInstruction;
if (secondline && !firstLine)
{
firstInstruction=locationCounter;
}

if (!strcmp(opcode, "END"))
{
  fprintf(passTwoWriter,"E%6.6X\n",firstInstruction);
end=true;
continue;
}




if (rSub)
{

  fprintf(passTwoWriter,"T%6.6X%2.2X4C0000\n",locationCounter,size);
  
}

if (strcmp(opcode,"BYTE")&& strcmp(opcode,"WORD") &&strcmp(opcode,"RSUB") && strcmp(opcode,"RESB")&&strcmp(opcode,"RESW"))
{
  
if (indexedAddressing)
{
  

 fprintf(passTwoWriter,"T%6.6X%2.2X%s%4.4X\n",locationCounter,size,getOpcodeHex(opcode),operandSymbol->address+32768);
  
}
else
{
  
  fprintf(passTwoWriter,"T%6.6X%2.2X%s%4.4X\n",locationCounter,size,getOpcodeHex(opcode),operandSymbol->address);
  
}
}
}

if (!strcmp(opcode, "WORD"))
{

  char buffer[60]; 
   
    sprintf(buffer, "%X", operand); 
 
fprintf(passTwoWriter,"T%6.6X%2.2X%6.6X\n",locationCounter,size,atoi(buffer));
locationCounter+=3;

}
else
if (!strcmp(opcode, "RESW"))
{
 locationCounter+=3*operand;

continue;
}
else
if (!strcmp(opcode, "RESB"))
{
  locationCounter+=operand;

continue;
}
else
if (!strcmp(opcode, "BYTE"))
{
  if (!longBYTE)
  {
  locationCounter+=operand;
 size=operand;
  }
}
else
{
   if (!longBYTE)
  {
  
  if (!firstLine)
  {
  locationCounter+=3;
  size=3;
  }

  }
}
}
}
if (firstLine==false)
secondline=false;
firstLine=false;
}

  return 0;

}


const char* getOpcodeHex(const char* String)
{
if (strcmp(String, "ADD")==0)
{
  return "18";
}
if (strcmp(String, "ADDF")==0)
{
  return "58";
}
if (strcmp(String, "ADDR")==0)
{
  return "90";
}
if (strcmp(String, "AND")==0)
{
  return "40";
}
if (strcmp(String, "CLEAR")==0)
{
  return "B4";
}
if (strcmp(String, "COMP")==0)
{
  return "28";
}
if (strcmp(String, "COMPF")==0)
{
  return "88";
}
if (strcmp(String, "COMPR")==0)
{
  return "A0";
}
if (strcmp(String, "DIV")==0)
{
  return "24";
}
if (strcmp(String, "DIVF")==0)
{
  return "64";
}
if (strcmp(String, "DIVR")==0)
{
  return "9C";
}
if (strcmp(String, "FIX")==0)
{
  return "C4";
}
if (strcmp(String, "FLOAT")==0)
{
  return "C0";
}
if (strcmp(String, "HIO")==0)
{
  return "F4";
}
if (strcmp(String, "J")==0)
{
  return "3C";
}
if (strcmp(String, "JEQ")==0)
{
  return "30";
}
if (strcmp(String, "JGT")==0)
{
  return "34";
}
if (strcmp(String, "JLT")==0)
{
  return "38";
}
if (strcmp(String, "JSUB")==0)
{
  return "48";
}
if (strcmp(String, "LDA")==0)
{
  return "00";
}
if (strcmp(String, "LDB")==0)
{
  return "68";
}
if (strcmp(String, "LDCH")==0)
{
  return "50";
}
if (strcmp(String, "LDF")==0)
{
  return "70";
}
if (strcmp(String, "LDL")==0)
{
  return "08";
}
if (strcmp(String, "LDS")==0)
{
  return "6C";
}
if (strcmp(String, "LDT")==0)
{
  return "74";
}
if (strcmp(String, "LDX")==0)
{
  return "04";
}
if (strcmp(String, "LPS")==0)
{
  return "D0";
}
if (strcmp(String, "MUL")==0)
{
  return "20";
}
if (strcmp(String, "MULF")==0)
{
  return "60";
}
if (strcmp(String, "MULR")==0)
{
  return "98";
}
if (strcmp(String, "NORM")==0)
{
  return "C8";
}
if (strcmp(String, "OR")==0)
{
  return "44";
}
if (strcmp(String, "RD")==0)
{
  return "D8";
}
if (strcmp(String, "RMO")==0)
{
  return "AC";
}
if (strcmp(String, "RSUB")==0)
{
  return "4C";
}
if (strcmp(String, "SHIFTL")==0)
{
  return "A4";
}
if (strcmp(String, "SHIFTR")==0)
{
  return "A8";
}
if (strcmp(String, "SIO")==0)
{
  return "F0";
}
if (strcmp(String, "SSK")==0)
{
  return "EC";
}
if (strcmp(String, "STA")==0)
{
  return "0C";
}
if (strcmp(String, "STB")==0)
{
  return "78";
}
if (strcmp(String, "STCH")==0)
{
  return "54";
}
if (strcmp(String, "STF")==0)
{
  return "80";
}
if (strcmp(String, "STL")==0)
{
  return "14";
}
if (strcmp(String, "STS")==0)
{
  return "7C";
}
if (strcmp(String, "STSW")==0)
{
  return "E8";
}
if (strcmp(String, "STT")==0)
{
  return "84";
}
if (strcmp(String, "STX")==0)
{
  return "10";
}
if (strcmp(String, "SUB")==0)
{
  return "1C";
}
if (strcmp(String, "SUBF")==0)
{
  return "5C";
}
if (strcmp(String, "SUBR")==0)
{
  return "94";
}
if (strcmp(String, "SVC")==0)
{
  return "B0";
}
if (strcmp(String, "TD")==0)
{
  return "E0";
}
if (strcmp(String, "TIO")==0)
{
  return "F8";
}
if (strcmp(String, "TIX")==0)
{
  return "2C";
}
if (strcmp(String, "TIXR")==0)
{
  return "B8";
}
if (strcmp(String, "WD")==0)
{
  return "DC";
}
if (0==strcmp(String, "START"))
        {
        
          return "00";
        }
          if (0==strcmp(String, "END"))
        {
         
          return "00";
        }
          if (0==strcmp(String, "BYTE"))
        {
         
          return "00";
        }
          if (0==strcmp(String, "WORD"))
        {
          
          return "00";
        }
          if (0==strcmp(String, "RESB"))
        {
          
          return "00";
        }
          if (0==strcmp(String, "RESW"))
        {
         ;
          return "00";
        }
          if (0==strcmp(String, "RESR"))  
        {
       
          return "00";
        }
          if (0==strcmp(String, "EXPORTS"))  
        {
        
          return "00";
        }
//Directives
else
{
  return NULL;
}


 

}

struct Symbol* isInHashes(struct Symbol* Hashes[],const char* name)
{

struct	Symbol *fCurrent;


fCurrent=Hashes[name[0]-65];


      {
        while (fCurrent!=NULL)
        {
         
             if (!strcmp(fCurrent->name, name))
            {
             break;
            }

            fCurrent=fCurrent->next;
           
        } 
        
      }
  

return fCurrent;




}







