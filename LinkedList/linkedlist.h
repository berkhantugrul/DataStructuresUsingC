struct nodeFB
{
	int id;
	int age;
	struct nodeFB *next;
};

struct nodeGS
{
	int id;
	struct nodeGS *next;
};

struct newNodeFB
{
	int id;
	int age;
	struct newNodeGS *next;
};

struct newNodeGS
{
	int id;
	struct newNodeFB *next;
};

// You must write all the function definitions to be used in this lab into this file. 
// You may also write other functions that may be called from our functions.
// Do not make any changes to the main.c file.
// Upload function.h file to the system as StudentNumber.h.

/* insertFB --- input alacak ve alır almaz artan sıralama yapacak */
void insertFB(struct nodeFB **startFB, int id, int age)
{
	struct nodeFB *ptr, *newnode, *temp; // ptr for startFB ----- temp for sorting process ----- last for controlling the last node
	
	newnode = (struct nodeFB *)malloc(sizeof(struct nodeFB));
	newnode->id = id;
	newnode->age = age;
	newnode->next = NULL;
    
	if(*startFB == NULL) // liste bossa - basa ekle 
	{
		*startFB = newnode;
	}

	else // bos degilse
	{
		ptr = *startFB;
		int i=0;
		while(1)
		{
			if(newnode->id > ptr->id) // yeni eleman once eklenenden buyukse
			{
				temp = ptr; // temp, kontrol edilmis olan node'u tutar
				if(ptr->next == NULL) // en sona gelindi ise sona ekle
				{
					ptr->next = newnode; 
					break;
				}

				else // sona ilerle
				{
					ptr = ptr->next;
				}
			}

			else if(newnode->id < ptr->id) // yeni eleman once eklenenden kucukse - bu once eklenen eleman sona dogru da olabilir
			{
				if(i == 0) // basa ekleme - i=0 en basa eklenme kontrolu yapar
				{
					*startFB = newnode;
					newnode->next = ptr;
					break;
				}

				else // basta degil de arada ise
				{ // last controlled = temp
					newnode->next = temp->next; // X-(Y)-Z yeni eleman (Y) Z ye baglanir
					temp->next = newnode; // temp = X ve yeni node'e baglanir ---------------(X-Z : X-Y + Y-Z = X-Y)
					break;
				} 
			}
			i++; // basa ekleme kontrolu
		}
		//ptr->next = newnode;
	}
};

void insertGS(struct nodeGS **startGS, int id)
{
	struct nodeGS *ptr, *newnode, *temp;  // ptr for startFB ----- temp for sorting process 
	
	newnode = (struct nodeGS *)malloc(sizeof(struct nodeGS));
	newnode->id = id;
	newnode->next = NULL;
    
	if(*startGS == NULL) // liste bossa - basa ekle
	{
		*startGS = newnode;
	}

	else // bos degilse
	{
		ptr = *startGS;
		int i=0;
		while(1)
		{
			if(newnode->id < ptr->id) // yeni eleman once eklenenden buyukse
			{
				temp = ptr; // temp, kontrol edilmis olan node'u tutar
				if(ptr->next == NULL) // en sona gelindi ise sona ekle
				{
					ptr->next = newnode; 
					break;
				}

				else // sona ilerle
				{
					ptr = ptr->next;
				}
			}

			else if(newnode->id > ptr->id) // yeni eleman once eklenenden kucukse - bu once eklenen eleman sona dogru da olabilir
			{
				if(i == 0) // basa ekleme - i=0 en basa eklenme kontrolu yapar
				{
					*startGS = newnode;
					newnode->next = ptr;
					break;
				}

				else // basta degil de arada ise
				{ // last controlled = temp
					newnode->next = temp->next; // X-(Y)-Z yeni eleman (Y) Z ye baglanir
					temp->next = newnode; // temp = X ve yeni node'e baglanir ---------------(X-Z : X-Y + Y-Z = X-Y)
					break;
				} 
			}
			i++; // basa ekleme kontrolu
		}
		//ptr->next = newnode;
	}
	/*
	else
	{
		ptr = *startGS;
		temp = *startGS;

		while(1)
		{
			if(newnode->id )
		}
		//ptr->next = newnode;
	}
	*/
};

void printFB(struct nodeFB *startFB)
{
	struct nodeFB *ptr;

	ptr = startFB;

	while(ptr != NULL)
	{
		printf("%d %d\n", ptr->id, ptr->age);
		ptr = ptr->next;
	}
	printf("\n");
};

void printGS(struct nodeGS *startGS)
{
	struct nodeGS *ptr;

	ptr = startGS;

	while(ptr != NULL)
	{
		printf("%d\n", ptr->id);
		ptr = ptr->next;
	}
	printf("\n");
};

void createFinalList(struct newNodeFB **startNewFB, struct nodeFB *startFB, struct nodeGS *startGS)
{
	int i = 0;
	struct newNodeGS * lastNode;
	while(startGS != NULL)
	{
		struct newNodeFB * newFB;
		newFB = (struct newNodeFB *)malloc(sizeof(struct newNodeFB));

		struct newNodeGS * newGS;
		newGS = (struct newNodeGS *)malloc(sizeof(struct newNodeGS));

		if (i == 0) // 0 ise basa FB ekler
		{
			*startNewFB = newFB;
		}

		newFB->age = startFB->age;
		newFB->id = startFB->id;
		newFB->next = newGS;
		newGS->id = startGS->id;
		newGS->next = NULL;

		if(i != 0) // 1 ise FB node ekler
		{
			lastNode->next = newFB;
		}

		lastNode = newGS; // sonrasinda GS ekler - i=0 alinir
		startFB = startFB->next;
		startGS = startGS->next;
		i++;
	}
};

void printAll(struct newNodeFB *startNewFB)
{
	struct newNodeGS *GS = NULL;
	int i = 0; // 0-2-4-... cift ise FB basar, tekse GS basar

	while(startNewFB != NULL)
	{
		if(i % 2 == 0) // FB basar
		{
			printf("%d %d\n", startNewFB->id, startNewFB->age);
			GS = startNewFB->next; // sonraki node
		}

		else // GS basar
		{
			printf("%d\n", GS->id);
			startNewFB = GS->next; // sonraki node
		}
		i++;
	}
};

/*
insertFB(&startFB, id, age); *
insertGS(&startGS, id); *
printFB(startFB); *
printGS(startGS); *
createFinalList(&startNewFB,startFB,startGS); 	
printAll(startNewFB); 
*/

