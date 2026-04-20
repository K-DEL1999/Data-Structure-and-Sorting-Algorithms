#include<iostream>

using namespace std;

struct node {
	int data;
	node *next;
};

void Link_list ( int argc, char* argv[], node *&head ); // creates linked_list
void reverse ( node *&head ); // reverse linked_list
void Insert_link ( int number, int location, node *&head ); // insert into linked_list
void head_change ( int number, node *&head ); // insert to beginning of list
void clone ( node *&h, node *&other); // copy linked_list
void remove ( node *&head, int number ); // delete from list

int main( int argc, char* argv[] ){
    int temp, l;
	node *head, *Rhead;
    
    //creates list ------- //
	Link_list( argc, argv, head ); // creates list
    cout << "List: ";
    for ( node *t = head; t && (*t).data; t = (*t).next ){ // ...t&&t->data; t = t->next )
        printf("%d ", (*t).data);
    }
    cout << endl;
    // ------------------- //
    
    //clones list ----------//
    clone ( head, Rhead );
    //reverses list ----------//
    reverse( Rhead ); // reverses list
    cout << "Reversed List: ";
    for ( node *t = Rhead; t && (*t).data; t = (*t).next ){ // ...t&&t->data; t = t->next )
        printf("%d ", (*t).data);
    }
    cout << endl << endl;;
    // ---------------------- //
    
    //insert --------------------//
    cout <<"Insert: ";
    cin >> temp;
    cout <<"Where? Next to... ";
    cin >> l;
    Insert_link ( temp, l, head );//insert
    cout << "\nInserted List: ";
    for ( node *t = head; t && (*t).data; t = (*t).next ){ // ...t&&t->data; t = t->next )
        printf("%d ", (*t).data);
    }
    cout << endl;
    // ------------------------- //
    
    //new head------------------//
    head_change ( temp, head );
    for ( node *t = head; t && (*t).data; t = (*t).next ){ // ...t&&t->data; t = t->next )
        printf("%d ", (*t).data);
    }
    cout << endl;
    //------------------------------//
    
    //delete from list --------------//
    cout << "What do you want to remove?: ";
    cin >> temp;
    remove ( head, temp );
    for ( node *t = head; t && t->data; t = t->next ){
        cout << t->data << " ";
    }
    //-------------------------------//
    return 0;
}

void Link_list ( int argc, char* argv[], node *&head ){
	node *t, *n;
	for ( int i = 1; i < argc; i++ ){
		if ( i == 1 ){
			n = new node;
			(*n).data = stoi(argv[1]);
			t = n;
			head = n;
		}
		else {
			n = new node;
			(*n).data = stoi(argv[i]); // n -> data = ...
			(*t).next = n; // t -> next = n;
			t = n;
		}
	}
	n = NULL;
	t->next = n;
}

void reverse ( node *&head ){
    node *current = head;
    node *prev = NULL;
    node *Next;
    while ( current != NULL ){
        Next = current->next; // Next = (*current).next
        current->next = prev;
        prev = current;
        current = Next;
    }
    head = prev;
}

void Insert_link ( int number, int location, node *&head ){
    node *current, *Next, *N;
    for ( node* t = head; t && t->data; t = t->next){
        if ( t->data == location ){
            Next = t->next;
            N = new node;
            N->data = number;
            t->next = N;
            N->next = Next;
            return;
        }
    }
    cout << " Cant insert there. That is not in the list. Goodbye..." << endl;
}

void head_change ( int number, node *&head ){
    node *N;
    N = new node;
    N->data = number;
    N->next = head;
    head = N;
}

void clone ( node *&head, node *&other ){
    node *N, *m;
    for ( node *t = head; t && t->data; t = t->next ){
        if ( t == head ){
            N = new node;
            N->data = t->data;
            other = N;
            m = N;
        }
        else {
            N = new node;
            N->data = t->data;
            m->next = N;
            m = N;
        }
    }
    N = NULL;
    m->next = N;
    
    cout << endl;
}

void remove ( node *&head, int number ){
    node *prev;
    for ( node *t = head; t && t->data; t = t->next ){
        if ( t == head ){
            prev = t;
            if ( t->data == number ){
                head = prev->next;
                delete prev;
                return;
            }
        }
        else if ( t->data == number ){
            if ( t->next == NULL ){
                prev->next = NULL;
                delete t;
                return;
            }
            else {
                prev->next = t->next;
                delete t;
                return;
            }
        }
        else {
            prev = t;
        }
    }
    cout << "Number is not in the list." << endl;
}
