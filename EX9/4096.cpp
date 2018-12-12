#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
struct Node
{
    int index;
    Node *prev = NULL;
    Node *next = NULL;
};
Node box[30];
char verb[10], prep[10];
int a, b, n;

bool check(int a, int b)
{
    Node *tmp = &box[a];
    while(tmp)
    {
        if(tmp->index == box[b].index)
            return true;
        else
            tmp = tmp->next;
    }
    tmp = &box[a];
    while(tmp)
    {
        if(tmp->index == box[b].index)
            return true;
        else
            tmp = tmp->prev;
    }
    return false;
}

void reinit(int a)
{
    Node *tmp = &box[a], *last;
    last = tmp;
    while(tmp->next)
    {
        tmp = tmp->next;
        last->next = NULL;
        tmp->prev = NULL;
        last = tmp;
    }
}

void move_over(int a, int b) //Put boxes above a back to their init pos the move a above b
{
    if(box[a].prev != NULL)
        box[a].prev->next = NULL;
    reinit(a);
    Node *tmp = &box[b];
    while(tmp->next)
        tmp = tmp->next;
    box[a].prev = tmp;
    tmp->next = &box[a];
}

void move_onto(int a, int b) //Put boxes above a & b back to their init pos and move a onto b
{
    if(box[a].prev != NULL)
        box[a].prev->next = NULL;
    reinit(a);
    reinit(b);
    box[a].prev = &box[b];
    box[b].next = &box[a];
}

void pile_over(int a, int b) //Pile box a and boxes above it over the pile that b exists
{
    if(box[a].prev != NULL)
        box[a].prev->next = NULL;
    Node *tmp = &box[b];
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = &box[a];
    box[a].prev = &box[b];
}

void pile_onto(int a, int b) //Pile the box a and boxes above it onto b (after put all boxes above b back to their init pos)
{
    if(box[a].prev != NULL)
        box[a].prev->next = NULL;
    reinit(b);
    box[a].prev = &box[b];
    box[b].next = &box[a];
}

void show()
{
    for(int i = 0; i < n; ++i)
    {
        cout << i << ':';
        if(box[i].prev == NULL) //if the box is the bottom
        {
            Node *tmp = &box[i];
            while(tmp)
            {
                cout << ' ' << tmp->index;
                tmp = tmp->next;
            }
        }
        cout << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 0; i < n; ++i)
        box[i].index = i;
    while(true)
    {
        cin >> verb;
        if(strcmp(verb, "quit") == 0) break;
        cin >> a >> prep >> b;
        if(!check(a, b))
        {
            if(strcmp(verb, "move") == 0 && strcmp(prep, "over") == 0)
                move_over(a, b);
            if(strcmp(verb, "move") == 0 && strcmp(prep, "onto") == 0)
                move_onto(a, b);
            if(strcmp(verb, "pile") == 0 && strcmp(prep, "over") == 0)
                pile_over(a, b);
            if(strcmp(verb, "pile") == 0 && strcmp(prep, "onto") == 0)
                pile_onto(a, b);
        }
    }
    show();
    cout << flush;
    return 0;
}