#include <iostream>
#include <cstdlib>

using namespace std;

int cycles = 0;

/* 	

	Cache L1 is nodes a - d
	Cache L2 is nodes e - h
	Cache L3 is nodes i - l  

	Nodes in each caceh will be doubly linked but they will
	not be linked to connect caches L1 - L2 - L3 

	Example: d will nod have a connection with e, same with
	h and i 

*/
	
	
struct node{
	int age;
	int addr;
	node* next;
	node* prev;
};

//L1
node* a = new node{-1, -200, NULL, NULL};	node* b = new node{-1, -253, NULL, NULL};	node* c = new node{-1, -204, NULL, NULL};	node* d = new node{-1, -205, NULL, NULL};
//L2
node* e = new node{-1, -200, NULL, NULL};	node* f = new node{-1, -290, NULL, NULL};	node* g = new node{-1, -230, NULL, NULL};	node* h = new node{-1, -205, NULL, NULL};
//L3
node* i = new node{-1, -200, NULL, NULL};	node* j = new node{-1, -240, NULL, NULL};	node* k = new node{-1, -207, NULL, NULL};	node* l = new node{-1, -220, NULL, NULL};


//--------------------------------

//Ages the nodes in the cache, except for x
void age(int cacheNum, node* x){
	if(cacheNum == 1){
		if(a!=x)
			a->age++;
		if(c!=x)
			b->age++;
		if(c!=x)
			c->age++;
		if(d!=x)
			d->age++;
	}
	else if(cacheNum == 2){
		if(e!=x)
			e->age++;
		if(f!=x)
			f->age++;
		if(g!=x)
			g->age++;
		if(h!=x)
			h->age++;
	}
	else if(cacheNum == 3){
		if(i!=x)
			i->age++;
		if(j!=x)
			j->age++;
		if(k!=x)
			k->age++;
		if(l!=x)
			l->age++;
	}

	x->age = 0;

}

//Searhes for the LRU node and returns it
node* checkAge(int cacheNum){
	if(cacheNum == 1){
		node* x = a;
		node* y = b;
		bool z  = true;

		while(z == true){
			while(y->age > x-> age && y->next != nullptr){
				x = y;
				y = y->next;
			}

			while(x->age > y-> age && y->next != nullptr){
				y = y->next;
			}
			z = false;
		}

		return x;
	}
	else if(cacheNum == 2){
		node* x = e;
		node* y = f;
		bool z  = true;

		while(z == true){
			while(y->age > x-> age && y->next != nullptr){
				x = y;
				y = y->next;
			}

			while(x->age > y-> age && y->next != nullptr){
				y = y->next;
			}
			z = false;
		}

		return x;
	}
	else if(cacheNum == 3){
		node* x = i;
		node* y = j;
		bool z  = true;

		while(z == true){
			while(y->age > x-> age && y->next != nullptr){
				x = y;
				y = y->next;
			}

			while(x->age > y-> age && y->next != nullptr){
				y = y->next;
			}
			z = false;
		}

		return x;
	}
}

//Finds the node with the given addr, if the node does not exist then it returns a nullptr
node* find(int addr, node* start, int cacheNum){
	//Start will be a for L1, e for L2, i for L3
	while(start->next != nullptr){
		if(cacheNum == 1){
			if(addr >= start->addr && addr <= start->addr + 255)
				return start;
		}
		else if(cacheNum == 2){
			if(addr >= start->addr && addr <= start->addr + 1023)
				return start;
		}
		else if(cacheNum == 3){
			if(addr >= start->addr && addr <= start->addr + 4095)
				return start;
		}
			
	
		start = start->next;		
		
	}
	return nullptr;
}			

//Replaces the addr of the given node, find LRU node with checkAge func
void replace(int addr, node* x, int cacheNum){
	x->addr = addr;
	age(cacheNum, x);
}
		
//--------------------------------

void load(int addr, int cacheNum){
	//check L1 first, if exists age all nodes, if not, replace oldest node with new and age all nodes set new nodes age to 0
	if(cacheNum == 1){
		node* n = find(addr, a, 1);
		if(n == nullptr){
			node* x = checkAge(1);
			replace(addr, x, 1);
			load(addr, 2);
		}
		
		else if(n != nullptr){
			age(1, n);
			cycles = cycles + 1;
		}
	}

	else if(cacheNum == 2){
		node* n = find(addr, e, 2);
		if(n == nullptr){
			node* x = checkAge(2);
			replace(addr, x, 2);
			load(addr, 3);
		}
		
		else if(n != nullptr){
			age(2, n);
			cycles = cycles + 10;
		}
	}
	//make sure we include main memory option
	else if(cacheNum == 3){
		node* n = find(addr, i, 3);
		if(n == nullptr){
			node* x = checkAge(3);
			replace(addr, x, 3);
			cycles = cycles + 1000;
		}
		
		else if(n != nullptr){
			age(3, n);
			cycles = cycles + 100;
		}
	}	
		
}


int main(){

//	L1										L2										L3
	a->next = b;	b->prev = a;			e->next = f;	f->prev = e;			i->next = j;	j->prev = i;		
	b->next = c;	c->prev = b;			f->next = g;	g->prev = f;			j->next = k;	k->prev = j;		
	c->next = d;	d->prev = c;			g->next = h;	h->prev = g;			k->next = l;	l->prev = k;					


	load (4096, 1);
	load (4132, 1);
	load (5529, 1);
	load (256, 1);
	load (66117, 1);
	load (66118, 1); 
	load (4135, 1); 
	load (66119, 1); 
	load (5632, 1); 
	load (5633, 1);
	load (5886, 1);

	cout << cycles << endl;

	return 0;
}