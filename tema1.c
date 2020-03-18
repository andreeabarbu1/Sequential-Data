//312CC_BARBU_ANDREEA
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

typedef struct node {
	double data; //retine valoarea numarului
	int timestamp;//retine timestamp ul 
	int s; //variabila auxilara pentru taskul 1
	struct node * next; //nodul urmator
	struct node * prev;	//nodul anterior
} *Node;

typedef struct list {
	Node head; //capatul listei
	Node tail; //coada listei
	int n;  //numarul elementelor din lista
} *List;

Node head, tail;

//initializeaza lista
List init_list (Node head, Node tail, int n) {
	List lista = (struct list *) malloc (sizeof (struct list));
	lista -> head = head;
	lista -> tail = tail;
	lista -> n = n;
	return lista;
}

//initializeaza nodul listei cu o valoare data
Node init_node ( double x, int s, int tms) {
	Node nod = (struct node *) malloc (sizeof (struct node));
	nod -> s = 0;
	nod -> timestamp = tms;
	nod -> data = x;
	nod -> prev = NULL;
	nod -> next = NULL;
	return nod;
}

//elibereaza memoria listei
void free_list (List l, Node *head) {
	
	Node nod = *head;
	while (nod != NULL) {
		Node p = nod;
		nod = nod -> next;
		free (p);
	}
	free (l);
	free (nod);
}

//printeaza continutul listei- timestampul si valoarea 
void print_list (List l) {
	Node nod = l -> head;
	if (l -> head != NULL) {
		while (nod != NULL && nod != l -> tail) {
			//printeaza valoarea cu o precizie de doua zecimale
			printf ("%d %.2lf\n", nod -> timestamp, nod -> data);
			nod = nod -> next;
		}
		printf("%d %.2lf\n", l->tail->timestamp, l -> tail -> data);
	}
}

//insereaza un nod cu valorile date la capatul listei
void InsertAtTail (Node *head, Node *tail, double x, int s, int tms) {
	Node aux = (*head);
	Node nod = init_node ( x, s, tms );
	//verifica daca lista e goala 
	if ( (*head) == NULL ) {
		(*head) = nod;
		return;
	}
	//parcurge pana la finalul listei
	while ( aux -> next != NULL )
		aux = aux -> next;
	//ultimul nod devine anterior nodului nou
	aux -> next = nod;
	nod -> prev = aux;
	*tail = nod;
}

//insereaza un nod dupa un nod dat
void InsertAfter (Node *prev_node, int timestamp, double data) {
	if ( *prev_node == NULL ) {
		return;
	}
	Node nod = malloc ( sizeof  (struct node) ); //alocare nod
	nod -> data = data;
	nod -> timestamp = timestamp;
	nod -> s = 0;
	nod -> next = (*prev_node) -> next;
	(*prev_node) -> next = nod;
	nod -> prev = (*prev_node);
	if (nod -> next != NULL) 
		nod -> next -> prev = nod;
}

//copiaza lista data intr-o alta lista, pe care o returneaza
List copyList (List l) {
	List lista;
	Node aux, h1= NULL, t1 = NULL, nod;
	aux = l -> head;
	//initializeaza head ul listei
	nod = init_node (aux -> data, aux -> s, aux -> timestamp);
	InsertAtTail (&h1, &t1, nod -> data, nod -> s, nod -> timestamp);
	free (nod);
	aux = l -> head;
	aux = aux -> next;
	//copiaza nodurile in lista
	while (aux -> next != NULL) {
		nod = init_node (aux -> data, aux -> s, aux -> timestamp);
		InsertAtTail (&h1, &t1, nod -> data, nod -> s, nod -> timestamp);
		free (nod);
		aux = aux -> next;	
	}
	//insereaza ultimul nod
	nod = init_node (aux -> data, aux -> s, aux -> timestamp);
	InsertAtTail (&h1, &t1, nod -> data, nod -> s, nod -> timestamp);
	free(nod);
	//initializeaza si returneaza lista
	lista = init_list (h1, t1, 5);
	return lista;
}

//sterge primul nod din lista
void deleteFirstNode (Node *head) {
	Node aux = *head;
	(*head) -> next -> prev = NULL;
	(*head) = (*head) -> next;
	free (aux);
}

//sterge nodul primit ca parametru din lista
void deleteNode (Node * node) {
	Node aux = (*node);
	aux -> next -> prev = aux -> prev;
	aux -> prev -> next = aux -> next;
	free (aux);
}

//interschimba doua noduri
void swap (Node a, Node b) {
	int aux = a -> timestamp;
	double auxx = a -> data;
	a -> timestamp = b -> timestamp;
	a -> data = b -> data;
	b -> timestamp = aux;
	b -> data = auxx;
}

//sorteaza o lista in functie de valorile nodurilor
void bubbleSort (Node head) {
	int aux;
	Node nod1, nod2 = NULL;
	//verifica daca lista e goala
	if ( head  == NULL )
		return;
	do {
		aux = 0;
		nod1 = head;
		while (nod1 -> next != nod2) { 
			if (nod1 -> data > (nod1 -> next -> data)) {
				swap ( nod1, nod1 -> next );
				aux = 1; //auxiliar pentru a verifica daca mai sunt elemente de sortat
			}
			nod1 = nod1 -> next; //trece la nodul urmator
		}
		nod2 = nod1;
	}
	while (aux); 
}

//returneaza numarul de noduri dintr-o lista
int getCount (Node head) {
	int nr = 0;
	Node aux = head;
	while ( aux != NULL ) {
		nr++;
		aux = aux -> next;
	}
	return nr;
}

//inverseaza o lista
void reverse (Node *head, Node *tail) {
	Node aux = NULL;
	Node curr = (*head);
	//interschimba nodurile intre ele
	while (curr != NULL) {
		aux = curr -> next;
		curr -> next = curr -> prev;
		curr -> prev = aux;
		curr = aux;
	}
	aux = (*head);
	(*head) = (*tail);
	(*tail ) = aux;
}

//returneaza media ferestrei, nodul central al ferestrei este dat
double average (Node * node) {
	double sum = 0;
	int n = 5;//fereastra contine 5 elemente
	Node aux, current;
	aux = *node;
	current = *node;
	sum = sum + (aux -> data);
	current = current -> prev;//elementul anterior nodului
	sum = sum + (current -> data); 
	current = current -> prev;//elementul postanterior nodului
	sum = sum + (current -> data); 
	current = aux;
	current = current -> next;
	sum = sum + (current -> data); //elementul urmator nodului
	current = current -> next;
	sum = sum + (current -> data); //cel de al doilea element dupa nod
	return (sum / n);
}

//returneaza deviatia standard a ferestrei
double deviation (double med, Node * node) {
	double sum = 0;
	int n = 5;//fereastra contine 5 elemente
	Node aux, current;
	aux = *node;
	current = *node;
	sum = sum + (current -> data - med) * (current -> data - med);
	current = current -> prev;//elementul anterior nodului
	sum = sum + (current -> data - med) * (current -> data - med);
	current = current -> prev;//elementul postanterior nodului
	sum = sum + (current -> data - med) * (current -> data - med);
	current = aux;
	current = current -> next; //elementul urmator nodului
	sum = sum + (current -> data - med) * (current -> data - med);
	current = current -> next;//cel de al doilea element dupa nod
	sum = sum + (current -> data - med) * (current -> data - med);
	return sqrt (sum / n);
}

//returneaza valoarea din mijloc a sublistei ordonate
double MiddleValue (List l) {
	Node hhead = l -> head;
	bubbleSort (hhead);
	return (hhead) -> next -> next -> data;
}

//returneaza media aritmetica a sublistei 
double MediaAritmetica (List l, int *retineTimestamp) {
	Node aux = l -> head;
	//retineTimestamp o sa retina timestamp-ul nodului central
	(*retineTimestamp) = aux -> next -> next -> timestamp;
	double Sum = 0;
	//calculeaza suma
	while (aux != NULL) {
		Sum = Sum + aux -> data;
		aux = aux -> next;
	}
	return (Sum / 5);
}

void task1 (List *l) {
	Node temp;
	double med = 0, dev = 0, left = 0, right = 0;
	//retinem in temp al treilea nod
	temp = (*l) -> head -> next;
	temp = temp -> next;
	//parcurgem pana la ultimul element
	while ((temp -> next) != (*l) -> tail) {
		med = average (&temp);//media nodului curent
		dev = deviation(med, &temp);//deviatia nodului curent
		left = med - dev;//capatul din stanga al intervalului
		right = med + dev;//capatul din dreapta al intervalului
		//verificam daca nodul curent nu apartine intervalului
		//in acest caz retinem in variabila s a nodului valoarea 1
		if (temp -> data < left || temp -> data > right)
			temp -> s = 1;
		//trecem la nodul urmator
		temp = temp -> next;
	}
	//parcurgem lista si stergem nodurile cu s = 1
	temp = (*l) -> head;
	while (temp != (*l) -> tail) {
		if (temp -> s == 1) {
			deleteNode (&temp);
			(*l) -> n = (*l) -> n - 1;
		}
		temp = temp -> next;
	}
}

void task2A (List *l, Node * HeadMediana, Node * TailMediana) {
	Node curr = (*l) -> head;
	Node headSublista = NULL, tailSublista = NULL;
	List Sublista, retineLista;
	int i, ok = 0, timestampReturnat;
	double valMid;
	int s = 0;
	int k = 5;
	//parcurgem lista
	while (curr != NULL)  {
		//in cazul in care ne aflam la primele valori din lista (ok == 0), le retinem pe primele k intr-o sublista
		if (ok == 0) { 
			for (i = 0; i < k; i++) {
				//inseram nodul curent in sublista si trecem la urmatorul
				InsertAtTail (&headSublista, &tailSublista, curr -> data, s, curr -> timestamp);
				curr = curr -> next;
			}
			ok = 1;//marcam crearea sublistei
		}
		else {
			//stergem primul nod din sublista si il inseream pe urmatorul din lista
			deleteFirstNode (&headSublista);
			InsertAtTail ( &headSublista, &tailSublista, curr -> data, s, curr -> timestamp);
			curr = curr -> next;
		}
		Sublista = init_list (headSublista, tailSublista, k);
		retineLista = copyList (Sublista);//copiem sublista in retineLista
		valMid = MiddleValue (retineLista );//valMid o sa retina valoarea din mijloc a sublistei
		timestampReturnat = headSublista -> next -> next ->timestamp;
		//inseram in lista mediana valorile corespunzatoare
		InsertAtTail (HeadMediana, TailMediana, valMid, s, timestampReturnat);
	}
		free_list (retineLista, &(retineLista -> head));
		free_list (Sublista, &headSublista);//elibereaza memoria sublistei
}

void task2B (List *l , Node *HeadMedie, Node *TailMedie, int *nrValori) {
	Node curr = (*l) -> head;
	Node headSublista = NULL, tailSublista = NULL;
	List Sublista, retineLista;
	int i, ok = 0, retineTimestamp;
	double Media;
	int s = 0;
	int k = 5;
	while (curr != NULL)  {
		if (ok == 0) { 
			//cream sublista din primele k valori ale listei l
			for (i = 0; i < 5; i++) {
				InsertAtTail (&headSublista, &tailSublista, curr -> data, s, curr -> timestamp);
				curr = curr -> next;
			}
			ok = 1;
		}
		else {
			//stergem primul nod si il adaugam pe urmatorul din lista
			deleteFirstNode (&headSublista);
			InsertAtTail (&headSublista, &tailSublista, curr -> data, s, curr -> timestamp);
			curr = curr -> next;
		}
		Sublista = init_list (headSublista, tailSublista, 5);
		retineLista = copyList (Sublista);
		//media aritmetica a sublistei, modificarea timestampului
		Media = MediaAritmetica (Sublista, &retineTimestamp);
		nrValori++;
		//inseram in lista medie, head si tail sunt primiti ca parametrii
		InsertAtTail (HeadMedie, TailMedie, Media, s, retineTimestamp);	
	}
		free_list (retineLista, &(retineLista -> head));
		free_list (Sublista, &headSublista);//elibereaza memoria
}

void task3 (List l) {
	Node aux = (l) -> head -> next;//aux retine al doilea nod din lista
	double diferenta = 0;
	while (aux != NULL) {
		//diferenta dintre nodul curent si cel anterior
		diferenta = (aux -> timestamp) - (aux -> prev -> timestamp);
		//daca diferenta se afla in interval inlocuim valorie nodului curent 
		//cu media dintre nodul curent si cel anterior
		if (diferenta  >= 100 && diferenta <= 1000) {
			aux  -> timestamp = ((aux -> timestamp) + (aux -> prev -> timestamp)) / 2;
			aux  -> data = ((aux -> data) + (aux -> prev -> data)) / 2;
			aux = aux -> next;
		}
		else { 
			aux = aux -> next;
		}
	}
}

//creeaza sublista din stanga a nodului currLeft
List create_left (Node currLeft) {
	int k = 3, i, s = 0;
	List left;
	Node leftHead = NULL, leftTail = NULL;
	//insereaza primele k - 1 elemente la coada sublistei
	for (i = 0; i < k - 1 ; i++) {
		InsertAtTail (&leftHead, &leftTail, currLeft -> data, s, currLeft -> timestamp);
		currLeft = currLeft -> prev;
	}
	//insereaza ultimul element
	InsertAtTail (&leftHead, &leftTail, currLeft -> data, s, currLeft -> timestamp);
	left = init_list (leftHead, leftTail, k); //initializeaza sublista left
	reverse (&leftHead, &leftTail);//inverseaza sublista
	left = init_list (leftHead, leftTail, k);//reintializeaza sublista
	return left;
}

//creeaza sublista din dreapta a nodului currRight
List create_right (Node currRight) {
	int k = 3, i, s = 0;
	List right;
	Node rightHead = NULL, rightTail = NULL;
	//introduce elementele in sublista
	for (i = 0; i < k - 1 ; i++) {
		InsertAtTail (&rightHead, &rightTail, currRight -> data, s, currRight -> timestamp);	
		currRight = currRight -> next;	
	}
	InsertAtTail (&rightHead, &rightTail, currRight -> data, s, currRight -> timestamp);
	right = init_list (rightHead, rightTail, k);//initializeaza sublista right
	return right;
}

//returneaza valoarea C, calculata dupa formula data
double C (int tms, int left, int right) {
	double c = ((double) ( tms - left)) / ((double)( right - left ));
	return c;
}

//returneaza valoarea W, calculata in functie de i si k
double W (double i, double k) {
	double  sum = 0, w = 0;
	double j;
	for (j = 0; j < k; j++) {
		sum = sum + (j / (k - 1)) * (j / (k - 1)) * 0.9 + 0.1;
	}
	w = ((i / (k - 1)) * (i / (k - 1)) * 0.9 + 0.1 ) / sum;
	return w;
}

//calculeaza noua valoare ce trebuie adaugata ulterior in nod
double value (List left, List right, int tms) {
	//retinem in leftTms si rightTms timestamp-urile celor mai apropiate noduri
	int leftTms = (left -> head) -> next -> next -> timestamp;
	int rightTms = right -> head -> timestamp;
	double c = C (tms,  leftTms, rightTms);//factorul de scalare C
	double f = 0;
	double i, k = 3, w = 0;
	double sum1 = 0, sum2 = 0;
	Node current = left -> head;//retine capatul sublistei left
	//calculeaza sum1 a sublistei left dupa formula
	for (i = 0; i < k; i++) {
		w = W (i, k);
		sum1 = sum1 + (current -> data * w);
		current = current -> next;
	}
	current = right -> head;
	//calculeaza sum2 a sublistei right dupa formula
	for (i = k - 1; i >= 0; i--) {
		w = W (i, k);
		sum2 = sum2 + (current -> data * w);
		current = current -> next;
	}
	f = (1 - c) * sum1 + c * sum2;
	return f;
}

void task4 (List l) {
	Node aux = l -> head;
	List left, right;
	Node limLeft, limRight;
	double val = 0;
	//parcurgem pana la ultimul element al listei l
	while (aux -> next != NULL) {
		//daca diferenta e dintre nodul curent si cel urmator e mai mare de 1000
		//retinem in limLeft nodul curent si in limRight nodul urmator
		if ((aux -> next -> timestamp) - (aux -> timestamp) >= 1000) {
			limLeft = aux;
			limRight = aux -> next;
			//creare liste left si right
			right = create_right (limRight);
			left = create_left (limLeft);
			//atat timp cat diferenta dintre timestampul limRight-ului si timestamp-ul 
			//curent e mai mare de 200 introducem un nou nod cu valorile corespunzatoare
			while ((limRight -> timestamp) - (limLeft -> timestamp) > 200) {
				val = value (left, right, (limLeft -> timestamp) + 200);//calculeaza valoarea
				InsertAfter (&limLeft,(limLeft -> timestamp) + 200, val);//inseram dupa nodul curent
				limLeft = limLeft -> next;//trecem la urmatorul nod
			}
		}
		aux = aux -> next;
	}
}

//converteste valoarea unui sir intr-un numar double
double Convert (char *s) {
	double number = atof (s);
	return number;
}

void bonus (Node *head, Node *tail, double interval, int nr) {
	double margineInferioaraa = (*head) -> data;//retine cea mai mica valoare din lista
	//aproximeaza margineInferioara
	double margineInferioara = round (margineInferioaraa);
	if (margineInferioaraa < margineInferioara && margineInferioaraa < 0) 
			margineInferioara --;
	double margineSuperioara = margineInferioara + interval;//marginea superioara a intervalului
	Node retinemHead = (*head);
	Node aux = (*head);
	int nrElem = 0;//retinem nr de elemente din intervalul curent
	double val = 0;
	int ok = 0;
	//parcurgem lista pana la final
	while ((*head) != NULL && ok == 0) {
		//daca valoarea curenta apartine intervalului
		if (((*head) -> data) >= margineInferioara && ((*head) -> data) <= margineSuperioara) {
			nrElem++;
			if ((*head) != (*tail))
				deleteFirstNode (head);//stergem primul nod 
			else {
				//marcam in ok ca am ajuns la capatul listei si verificam carui interval ii apartine
				ok = 1;
				goto loop;
			}
		}
		else {	
			loop:
			//afisam intervalul si nr de elemente din el daca e diferit de 0
			if ( nrElem != 0) {
				printf("[%.0lf, %.0lf] ", margineInferioara, margineSuperioara);
				printf("%d\n", nrElem);
			}				
			nrElem = 0;//reinitializam nr de elemente
			//schimbam marginile intervalului
			margineInferioara = margineSuperioara;
			margineSuperioara = margineSuperioara + interval;			
		}
		
	}
}

int main (int argc, char *argv [ ]) {
	int s = 0, n = 0, i, tms = 0, j, nrValori = 0;
	double nr = 0;
	Node HeadMediana = NULL, TailMediana = NULL, HeadMedie = NULL, TailMedie = NULL;
	List lista = NULL, ListaMedie = NULL, ListaMediana = NULL;
	head = NULL;
	tail = NULL;
	scanf ("%d", &n);
	//inseram cele n noduri in lista
	for (i = 0; i < n; i++) {
		scanf ("%d", &tms);
		scanf ("%lf", &nr);
		InsertAtTail (&head, &tail, nr, s, tms);
	}
	lista  = init_list (head, tail, n);//initializam lista
	List listaBonus = copyList(lista);//copiem in listaBonus lista
	//pentru fiecare argument modificam lista dupa cerinte
	for (j = 0; j < argc ; j++) {
		//task 1 - Eliminare de exceptii folosind metode statistice
		if (strcmp (argv [j], "--e1") == 0 ) {
			task1 (&lista);
			n = getCount (lista -> head);//retinem nr de elemente din lista
		}
		//task 2.1 - Filtrarea mediana
		else if (strcmp (argv [j], "--e2") == 0) {
			task2A (&lista, &HeadMediana, &TailMediana);
			n = getCount (HeadMediana );
			//initializam lista mediana
			ListaMediana = init_list (HeadMediana, TailMediana, n);
			free_list (lista, &(lista -> head));
			lista = ListaMediana;//lista va fi lista mediana, anterior initializata
			//free_list (ListaMediana, &(ListaMediana -> head));
		}
		//task 2.2 - Filtrarea folosind media aritmetica
		else if (strcmp (argv [j], "--e3") == 0) {
			task2B (&lista, &HeadMedie, &TailMedie, &nrValori);
			n = getCount (HeadMedie);
			ListaMedie = init_list (HeadMedie, TailMedie, n);
			free_list (lista, &(lista -> head));
			lista = ListaMedie;//lista va fi lista mediana, anterior initializata
			//free_list (ListaMedie, &(ListaMedie -> head));
		}
		//task 3 - Uniformizarea frecventei in timp a datelor
		else if (strcmp (argv [j], "--u") == 0) { 	
			task3 (lista);
		}
		//task 4 - Completarea datelor
		else if (strcmp (argv [j], "--c") == 0) {
			task4 (lista);
		}
		//bonus
		else if (argv [j][2] == 's')
		{
			char *delta = malloc (50 * sizeof (char));
			strcpy (delta, argv[j] + 4);
			double interval = 0;
			interval = Convert (delta);
			int nrValoriBonus = 0;
			nrValoriBonus =  getCount (listaBonus-> head);
			bubbleSort (listaBonus -> head);//sorteaza listaBonus
			bonus (&(listaBonus -> head), &(listaBonus -> tail), interval, nrValoriBonus);
			free(delta);
			return 0;
		}
	}
	n = getCount (lista -> head);//numarul de elemente din lista
	printf("%d\n", n);
	print_list (lista);//afiseaza lista
	free_list(lista, &(lista -> head));//elibereaza memoria listei
	return 0;
}
