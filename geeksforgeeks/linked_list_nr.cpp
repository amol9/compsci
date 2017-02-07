// problem url: http://www.geeksforgeeks.org/clone-linked-list-next-random-pointer-o1-space/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

struct Item;
Item* make_original_list(int);
Item* clone_list(Item*);
void print_list(Item*);
void add_random_links(Item*, vector<Item*>);

int run_simple(int);
int run_tests(int, int);
bool test(int);

/* args:
    1. no. of elements in the linked list (max no. of elements if running in test mode, a random number will be selected for each run)
    2. test mode (provide any value to run in test mode)
    3. no. of test cases

    e.g.
    > prog 10
    > prog 100 t 10
*/

int main(int argc, char* argv[]) {
    int n = 5;
    bool test = false;
    int nt = 10;

    if (argc > 1) {
        n = atoi(argv[1]);
    }
    if (argc > 2) {
        test = true;
    }
    if (argc > 3) {
        nt = atoi(argv[3]);
    }

    if (test) {
        return run_tests(nt, n);
    } else {
        return run_simple(n);
    }   
}

int run_simple(int n) {
    Item* head = make_original_list(n);
    cout << "original list:" << endl;
    print_list(head);

    Item* clone_head = clone_list(head);
    cout << "cloned list:" << endl;
    print_list(clone_head);

    return 0;
}

int run_tests(int nt, int n) {
    while (nt-- > 0) {
        bool r = test(n);
        if (!r) {
            cout << "test failed" << endl;
            return 1;
        } else {
            cout << "passed" << endl;
        }
    }
    return 0;
}

struct Item {
    int     value;
    Item*   next;
    Item*   random;
};

bool test(int max_n) {
    srand(time(NULL));
    int n = max_n > 0 ? rand() % max_n + 1 : 0;

    Item* head = make_original_list(n);
    Item* clone_head = clone_list(head);

    if (head == NULL) {
        if (clone_head == NULL)
            return true;
        else
            return false;
    }

    Item* ptr = head;
    Item* ptr2 = clone_head;

    while (ptr != NULL) {
        if ((ptr->value != ptr2->value) || (ptr->random->value != ptr2->random->value)) {

            cout << "orig (value, random): " << ptr->value << ", " << ptr->random->value << endl;
            cout << "clone (value, random): " << ptr2->value << ", " << ptr2->random->value << endl;
            return false;
        }
        ptr = ptr->next;
        ptr2 = ptr2->next;
    }
    return true;
}

Item* make_original_list(int n) {
    Item* head = NULL;
    Item* last = NULL;

    vector<Item*> addrs(0);

    for(int i = 0; i < n; i++) {
        Item* ni = new Item();
        ni->value = i;
        ni->next = NULL;
        ni->random = NULL;

        if (head == NULL) {
            head = ni;
        }

        if (last == NULL) {
            last = ni;
        } else {
            last->next = ni;
            last = ni;
        }
        addrs.push_back(ni);
    }

    add_random_links(head, addrs);

    return head;
}

void add_random_links(Item* head, vector<Item*> addrs) {
    Item* ptr = head;
    int n = addrs.size();
    srand(time(NULL));

    while (ptr != NULL) {
        int ridx = rand() % addrs.size();
        vector<Item*>::iterator itr = addrs.begin() + ridx;
        Item* ra = *itr;
        addrs.erase(itr);

        ptr->random = ra;
        ptr = ptr->next;
    }
}

Item* clone_list(Item* head) {
    if (head == NULL) {
        return NULL;
    }

    // add copies next to the original nodes

    Item* ptr = head;

    while (ptr != NULL) {
        Item* ni = new Item();
        ni->value = ptr->value;
        ni->next = ptr->next;
        ni->random = NULL;
        ptr->next = ni;

        ptr = ni->next;
    }

    // add random pointers for copies

    ptr = head;

    while (ptr != NULL) {
        ptr->next->random = ptr->random->next;
        ptr = ptr->next->next;
    }

    // unzip lists

    Item* clone_head = head->next;
    ptr = head;
    Item* ptr2 = clone_head;

    while (ptr != NULL) {
        ptr->next = ptr->next->next;
        ptr = ptr->next;

        if (ptr2->next != NULL) {
            ptr2->next = ptr2->next->next;
            ptr2 = ptr2->next;
        }
    }

    return clone_head;
}

void print_list(Item* head) {
    Item* ptr = head;

    while (ptr != NULL) {
        cout << ptr->value << " [" << ptr->random->value << "] ";
        ptr = ptr->next;
    }
    cout << endl;
}
