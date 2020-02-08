#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int and(int x, int y);
int or (int x, int y);
int nand(int x, int y);
int nor (int x, int y);
int xor(int x, int y);
int xnor(int x, int y);
struct line
{
  char statement[1000];
  struct line * next;
};
struct node
{
  char name[20];
  int value;
  struct node * next;
};
int logarithm(int n)
{
  return (n>1) ? 1+logarithm(n/2) : 0;
}
unsigned long power(int x, int y)
{
  int i;
  unsigned long result = 1;
  for (i = 0; i < y; i++)
    {
      result *= x;
    }
  return result;
}
int grayCode(int n)
{
  return n^(n>>1);
}
int inverseGrayCode(int g)
{
  int n = 0;
  for (; g; g>>=1)
    {
      n^=g;
    }
  return n;
}
void fillGrayCode(struct node * inputs, int n)
{
  int g = grayCode(n);
  struct node * pointer = inputs;
  while (pointer != NULL)
    {
      pointer -> value = g&1;
      g -= (g&1);
      g >>= 1;
      pointer = pointer->next;
    }
}
void printGrayCode(struct node * head)
{
  if (head == NULL)
    {
      return;
    }
  printGrayCode(head->next);
  printf("%d ", head->value);
}
int isLower(char c)
{
  if (c >= 'a' && c <= 'z')
    {
      return 1;
    }
  return 0;
}
struct node * makeNode(char name[], int value)
{
  struct node * n = malloc(sizeof(struct node));
  strcpy(n->name, name);
  n->value = value;
  n->next = NULL;
  return n;
};
struct node * addNode(struct node * head, struct node * n)
{
  n->next = head;
  return n;
}
struct node * findNode(struct node * head, char name[])
{
  struct node * pointer = head;
  while (pointer != NULL)
    {
      if (strcmp(pointer->name, name) == 0)
	{
	  return pointer;
	}
      pointer = pointer->next;
    }
  return NULL;
}
void printLL(struct node * head)
{
  struct node * pointer = head;
  while (pointer != NULL)
    {
      printf("%s: %d\n", pointer->name, pointer->value);
      pointer = pointer->next;
    }
}
struct textFile
{
  struct line * head;
  struct line * tail;
  int length;
};
struct line * makeLine(char statement[])
{
  struct line * l = malloc(sizeof(struct line));
  strcpy(l->statement, statement);
  l->next = NULL;
  return l;
}
struct textFile * makeTextFile()
{
  struct textFile * t = malloc(sizeof(struct textFile));
  t -> head = NULL;
  t -> tail = NULL;
  t -> length = 0;
  return t;
}
void add(struct textFile * t, struct line * l)
{
  if (t->head == NULL)
    {
      t->head = l;
      t->tail = l;
    }
  else
    {
      t->tail->next = l;
      t->tail = l;
    }
  t->length++;
}
struct line * pop(struct textFile * t)
{
  if (t->head == NULL)
    {
      return NULL;
    }
  struct line * temp = t -> head;
  t -> length--;
  if (t->head == t->tail)
    {
      t -> head = NULL;
      t -> tail = NULL;
      return temp;
    }
  t -> head = t -> head -> next;
  
  return temp;
}
void printTextFile(struct textFile * t)
{
  struct line * pointer = t -> head;
  while (pointer != NULL)
    {
      printf("%s\n", pointer->statement);
      pointer = pointer -> next;
    }
}
void freeTextFile(struct textFile * t)
{
  struct line * pointer = t->head;
  struct line * temp = t->head;
  while (pointer != NULL)
    {
      pointer = pointer->next;
      free(temp);
      temp = pointer;
    }
}
char ** split(char str[], int rows, int cols)
{
  char ** arr = malloc(rows * sizeof(char *));
  int i;
  for (i = 0; i < rows; i++)
    {
      arr[i] = malloc(cols * sizeof(char));
    }
  int j = 0;
  int count = 0;
  for (i = 0; i <= (strlen(str)); i++)
    {
      if (str[i] == ' ' || str[i] == '\0')
	{
	  arr[count][j] = '\0';
	  count++;
	  j = 0;
	}
      else
	{
	  arr[count][j] = str[i];
	  j++;
	}
    }
  return arr;
}
void freeArr(char ** arr, int rows)
{
  int i = 0;
  for (i = 0; i < rows; i++)
    {
      free(arr[i]);
    }
  free(arr);
}
struct node * deleteTemps(struct node * head)
{
  struct node * pointer = head;
  while (isLower(pointer -> name[0]) == 1)
    {
      struct node * temp = pointer;
      pointer = pointer->next;
      free(temp);
    }
  head = pointer;
  return head;
}
void freeLL(struct node * head)
{
  struct node * current = head;
  struct node * pointer = NULL;
  while (current != NULL)
    {
      pointer = current -> next;
      free(current);
      current = pointer;
    }
}
int not(int b)
{
  return !b;
}
struct node * notGate(struct node * inputs, struct node * outputs, char inputName[], char outputName[])
{
  int result = 0;
  if (inputName[0] == '0' || inputName[0] == '1')
    {
      result = not(atoi(inputName));
    }
  else
    {
      result = not(findNode(inputs, inputName)->value);
    }
  if (isLower(outputName[0])==0)
    {
      findNode(outputs, outputName)->value = result;
    }
  else
    {
      if (findNode(inputs, outputName) == NULL)
	{
	  inputs = addNode(inputs, makeNode(outputName, result));
	}
	else
	{
	  findNode(inputs, outputName)->value = result;
	}
    }
  return inputs;
}
struct node * pairGate(struct node * inputs, struct node * outputs, char i1[], char i2[], char out[], char directive[])
{
  int bit1 = 0;
  int bit2 = 0;
  int result = 0;
  if (i1[0] == '0' || i1[0] == '1')
    {
      bit1 = atoi(i1);
    }
  else
    {
      bit1 = findNode(inputs, i1)->value;
    }
  if (i2[0] == '0' || i2[0] == '1')
    {
      bit2 = atoi(i2);
    }
  else
    {
      bit2 = findNode(inputs, i2)->value;
    }
  if (strcmp(directive, "AND") == 0)
    {
      result = and(bit1, bit2);
    }
  else if (strcmp(directive, "OR") == 0)
    {
      result = or(bit1, bit2);
    }
  else if (strcmp(directive, "NAND") == 0)
    {
      result = nand(bit1, bit2);
    }
  else if (strcmp(directive, "NOR") == 0)
    {
      result = nor(bit1, bit2);
    }
  else if (strcmp(directive, "XOR") == 0)
    {
      result = xor(bit1, bit2);
    }
  else
    {
      result = xnor(bit1, bit2);
    }
  if (isLower(out[0])==0)
    {
      findNode(outputs, out)->value = result;
    }
  else
    {
      if (findNode(inputs, out) == NULL)
	{
	  inputs = addNode(inputs, makeNode(out, result));
	}
	else
	{
	  findNode(inputs, out)->value = result;
	}
    }
  return inputs;
}
struct node * decoder(char inputNames[][20], char outputNames[][20], struct node * inputs, struct node * outputs, int numberOfInputs)
{
  int i;
  int dValue = 0;
  for (i = 0; i < numberOfInputs; i++)
    {
      int indexValue = 0;
      if (inputNames[i][0] == '0' || inputNames[i][0] == '1')
	{
	  indexValue = atoi(inputNames[i]);
	}
      else
	{
	  indexValue = findNode(inputs, inputNames[i])->value;
	}
      dValue += indexValue * power(2,numberOfInputs-i-1);
    }
  dValue = inverseGrayCode(dValue);
  char o[power(2,numberOfInputs)];
  for (i = 0; i < power(2,numberOfInputs);i++)
    {
      if (i == dValue)
	{
	  o[i]=1;
	}
      else
	{
	  o[i]=0;
	}
    }
  for (i = 0; i < power(2,numberOfInputs);i++)
    {
      if (isLower(outputNames[i][0]) == 0)
	{
	  findNode(outputs, outputNames[i])->value = o[i];
	}
      else
	{
	  if (findNode(inputs, outputNames[i]) == NULL)
	    {
	      inputs = addNode(inputs, makeNode(outputNames[i], o[i]));
	    }
	  else
	    {
	      findNode(inputs, outputNames[i])->value = o[i];
	    }
	}
    }
  return inputs;
}
struct node * mux(char inputNames[][20], char selectors[][20], char out[], struct node * inputs, struct node * outputs, int numberOfSelectors)
{
  int i;
  int dValue = 0;
  for (i = 0; i<numberOfSelectors; i++)
    {
      int indexValue = 0;
      if (selectors[i][0] == '0' || selectors[i][0] == '1')
      	{
      	  indexValue = atoi(selectors[i]);
	  
      	}
      else
      	{
      	  indexValue = findNode(inputs, selectors[i])->value;
      	}
      dValue += indexValue * power(2, numberOfSelectors - 1 -i);
    }
  dValue = inverseGrayCode(dValue);
  int result;
  if (inputNames[dValue][0] == '0' || inputNames[dValue][0] == '1')
    {
      result = atoi(inputNames[dValue]);
    }
  else
    {
      result = findNode(inputs, inputNames[dValue])->value;
    }
  if (isLower(out[0])==0)
    {
      findNode(outputs, out)->value = result;
    }
  else
    {
      if (findNode(inputs, out) == NULL)
	{
	  inputs = addNode(inputs, makeNode(out, result));
	}
	else
	{
	  findNode(inputs, out)->value = result;
	}
    }
  return inputs;
}
int and(int b, int c)
{
  return b&c;
}
int or(int b, int c)
{
  return b|c;
}
int nand(int b, int c)
{
  return not(and(b,c));
}
int nor(int b, int c)
{
  return not(or(b,c));
}
int xor(int b, int c)
{
  return b^c;
}
int xnor(int b, int c)
{
  return not(xor(b,c));
}
int main(int argc, char ** argv)
{
  struct node * inputs = NULL;
  struct node * outputs = NULL;
  FILE * f = fopen(argv[1], "r");
  char line[1000];
  int r = fscanf(f, "%[^\n]\n", line);
  struct textFile * textFile = makeTextFile(); 
  while (r == 1)
    {
      add(textFile, makeLine(line));
      r = fscanf(f, "%[^\n]\n", line);
    }
  struct textFile * correctFile = makeTextFile();
  struct line * lineFinder = textFile -> head;
  int i;
  int numberOfInputs = 0;
  //                                                         GETTING INPUTS AND OUTPUTS
  while (lineFinder != NULL)
    {
      if (lineFinder->statement[0] == 'I')
	{
	  strcpy(line, lineFinder->statement);
	  char ** breakInput = split(line, 50, 20);
	  for (i = 2; i < atoi(breakInput[1])+2; i++)
	    {
	      inputs = addNode(inputs, makeNode(breakInput[i], 0));
	      numberOfInputs++;
	    }
	  freeArr(breakInput, 50);
	}
      else if (lineFinder -> statement[0] == 'O' && lineFinder -> statement[1] == 'U')
	{
	  strcpy(line, lineFinder->statement);
	  char ** breakOutput = split(line, 50,20);
	  for (i = 2; i < atoi(breakOutput[1])+2; i++)
	    {
	      outputs = addNode(outputs, makeNode(breakOutput[i], -1));
	    }
	  freeArr(breakOutput, 50);
	}
      lineFinder = lineFinder -> next;
    }

  //                                                      PUTTING DIRECTIVES IN CORRECT ORDER     
  while (textFile->length > 0)
    {
      strcpy(line, textFile->head->statement);
      if (textFile->head->statement[0] == 'N' && textFile->head->statement[2] == 'T')
  	{
  	  char ** breakNot = split(line, 3, 20);
  	  if (findNode(inputs, breakNot[1]) != NULL || breakNot[1][0] == '0' || breakNot[1][0] == '1')
	    {
	      if (isLower(breakNot[2][0]) == 1)
		{
		  inputs = addNode(inputs, makeNode(breakNot[2], 0));
		}
	      add(correctFile, makeLine(textFile->head->statement));
	      pop(textFile);
	    }
	  else
	    {
	      struct line * popped = pop(textFile);
	      popped->next = NULL;
	      add(textFile, popped); 
	    }
	  freeArr(breakNot, 3);
  	}
      else if (textFile->head->statement[0] == 'A' || textFile->head->statement[0]  == 'N' || textFile->head->statement[0] == 'X' || (textFile->head->statement[0] == 'O' && textFile->head->statement[1] == 'R') )
	{
	  char ** breakPair = split(line, 4, 20);
	  int w;
	  int check = 0;
	  for (w = 0; w < 2; w++)
	    {
	      if (findNode(inputs, breakPair[w+1]) != NULL || breakPair[w+1][0] == '0' || breakPair[w+1][0] == '1')
		{
		  check++;
		}
	    }
	  if (check == 2)
	    {
	      if (isLower(breakPair[3][0]) == 1)
		{
		  inputs = addNode(inputs, makeNode(breakPair[3],0));
		}
	      add(correctFile, makeLine(textFile->head->statement));
	      pop(textFile);
	    }
	  else
	    {
	      struct line * popped = pop(textFile);
	      popped->next = NULL;
	      add(textFile, popped);
	    }
	    freeArr(breakPair, 4);
	}
      else if (textFile->head->statement[0] == 'M')
      	{
      	  char ** breakMux = split(line, 100, 20);
      	  int selection = atoi(breakMux[1]);
      	  int w;
      	  int check1 = 0;
	  int check2 = 0;
      	  for (w = 0; w < selection; w++)
      	    {
      	      if (findNode(inputs, breakMux[w+2]) != NULL || breakMux[w+2][0] == '0' || breakMux[w+2][0] == '1')
      		{
		  check1++;
      		}
      	    }
	  for (w = 0; w < logarithm(selection); w++)
	    {
	      if (findNode(inputs, breakMux[w+2+selection]) != NULL || breakMux[w+2+selection][0] == '0' || breakMux[w+2+selection][0] == '1')
      		{
		  check2++;
      		}
	    }
	  if (check1 == selection && check2 == logarithm(selection))
	    {
	      if (isLower(breakMux[2+selection+logarithm(selection)][0]) == 1)
		{
		  inputs = addNode(inputs, makeNode(breakMux[2+selection+logarithm(selection)],0));
		}
	      add(correctFile, makeLine(textFile->head->statement));
	      pop(textFile);
	    }
	  else
	    {
	      struct line * popped = pop(textFile);
	      popped->next = NULL;
	      add(textFile, popped);
	    }
	  freeArr(breakMux, 100);
      	}
      else if (textFile->head->statement[0] == 'D')
      	{
	  char ** breakDecoder = split(line, 100, 20);
      	  int ins = atoi(breakDecoder[1]);
      	  int w;
      	  int check1 = 0;
      	  for (w = 0; w < ins; w++)
      	    {
      	      if (findNode(inputs, breakDecoder[w+2]) != NULL || breakDecoder[w+2][0] == '0' || breakDecoder[w+2][0] == '1')
      		{
		  check1++;
      		}
      	    }
	  if (check1 == ins)
	    {
	      for (w = 0; w < power(2, ins); w++)
		{
		   if (isLower(breakDecoder[2+ins+w][0]) == 1)
		     {
		       inputs = addNode(inputs, makeNode(breakDecoder[2+ins+w],0));
		     }
		}
	      add(correctFile, makeLine(textFile->head->statement));
	      pop(textFile);
	    }
	  else
	    {
	      struct line * popped = pop(textFile);
	      popped->next = NULL;
	      add(textFile, popped);
	    }
	  freeArr(breakDecoder, 100);
      	}
      else if (textFile->head->statement[0] == 'I')
	{
	  pop(textFile);
	}
      else if (textFile->head->statement[0] == 'O')
	{
	  pop(textFile);
	}
    }
  inputs = deleteTemps(inputs);
  //                                       CIRCUIT
  unsigned long counter = power(2, numberOfInputs);
  
  for (i = 0; i < counter; i++)
    {
      lineFinder = correctFile->head;
      fillGrayCode(inputs, i);
      printGrayCode(inputs);
      while (lineFinder != NULL)
	{
	  if (lineFinder->statement[0] == 'N' && lineFinder->statement[2] == 'T')
	    {
	      char ** dir = split(lineFinder->statement, 3, 20);
	       
	      inputs = notGate(inputs, outputs, dir[1], dir[2]);
		
	      freeArr(dir, 3);
	    }
	  else if (lineFinder->statement[0] == 'A' || lineFinder->statement[0] == 'X' || lineFinder->statement[0] == 'O' || lineFinder->statement[0] == 'N')
	    {
	      char ** dir = split(lineFinder->statement, 4, 20);
	      inputs = pairGate(inputs, outputs, dir[1], dir[2], dir[3], dir[0]);	
	      freeArr(dir, 4);
	    }
	  else if (lineFinder->statement[0] == 'D')
	    {
	      char ** dir = split(lineFinder->statement, 100, 20);
	      int decodeInput = atoi(dir[1]);
	      char inputNames[decodeInput][20];
	      char outputNames[power(2, decodeInput)][20];
	      int v;
	      for (v = 0; v < decodeInput; v++)
		{
		  strcpy(inputNames[v], dir[2+v]);
		}
	      for (v = 0; v < power(2, decodeInput); v++)
		{
		  strcpy(outputNames[v], dir[2+v+decodeInput]);
		}
	      inputs = decoder(inputNames, outputNames, inputs, outputs, decodeInput);
	      freeArr(dir, 100);
	    }
	  else if (lineFinder->statement[0] == 'M')
	    {
	      char ** dir = split(lineFinder->statement, 100, 20);
	      int ins = atoi(dir[1]);
	      char inputNames[ins][20];
	      char selectors[logarithm(ins)][20];
	      int v;
	      for (v = 0; v < ins; v++)
		{
		  strcpy(inputNames[v], dir[2+v]);
		}
	      for (v = 0; v < logarithm(ins); v++)
		{
		  strcpy(selectors[v], dir[2+v+ins]);
		}
	      inputs = mux(inputNames, selectors, dir[2+ins+logarithm(ins)], inputs, outputs, logarithm(ins));
	      freeArr(dir, 100);
	    }
	  lineFinder = lineFinder->next;
	}
      printGrayCode(outputs);
      printf("\n");
      inputs = deleteTemps(inputs);
      
    }
  freeTextFile(textFile);
  freeTextFile(correctFile);
  freeLL(inputs);
  freeLL(outputs);
  return 0;
}
