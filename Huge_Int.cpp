#include "HUGE_INT.h"

HUGE_INT::HUGE_INT(void)
{
    head = NULL;
    sizei = 0;
}

void HUGE_INT::clearHelper(void)
{
    Node*p = head,*q = NULL;
    while( p != NULL )
    {
        q = p;
        p = p->next;
        delete q;
    }
    delete head;
    head = NULL;
    sizei = 0;
}

HUGE_INT::~HUGE_INT(void)
{
    clearHelper();
}

void HUGE_INT::printHelper(ostream & out, Node*p) const
{
    if(p)
    {
        printHelper(out,p->next);
        out << p->key;
    }
}

ostream&operator<<(ostream&out, const HUGE_INT&number)
{
    number.printHelper(out, number.head);
    return out;
}

void HUGE_INT::setInt(unsigned long long int num)
{
    Node *p = NULL, *q = NULL, *d = new Node;
    if( head )
    {
        clearHelper();
    }
    do
    {
        if(!head)
        {
            d->key = num%10;
            d->next = head;
            head = d;
            p = head;
        }
        else
        {
            p->next = new Node;
            p = p->next;
            p->key = num%10;
            p->next = NULL;
        }
        num /= 10;
        sizei++;
    }while(num>0);
}

HUGE_INT::HUGE_INT(unsigned long long int number)
{
	setInt(number);
}

HUGE_INT HUGE_INT::add(const HUGE_INT&num2)
{
    HUGE_INT result;
    result.clearHelper();
    Node *n1 = head, *n2 = num2.head, *p = NULL;
    int t1 = 0, t2 = 0, c = 0,t = 0;
    while( n1 || n2 || c != 0)
    {
        if( c!=0 && !n1 && !n2)
        {
            t1 = t2 = 0;
        }
        else if( !n1 )
        {
            t1 = 0;
            t2 = n2->key;
            n2 = n2->next;
        }
        else if ( !n2 )
        {
            t2 = 0;
            t1 = n1->key;
            n1 = n1->next;
        }
        else
        {
            t1 = n1->key;
            t2 = n2->key;
            n1 = n1->next;
            n2 = n2->next;
        }
        t = (t1 + t2 + c) % 10;
        c = (t1 + t2 + c) / 10;
        if(!result.head)
        {
            result.head = new Node;
            result.head->key = t;
            result.head->next = NULL;
            p = result.head;
        }
        else
        {
            p->next = new Node;
            p = p->next;
            p->key = t;
            p->next = NULL;
        }
        sizei++;
    }
    return result;
}

HUGE_INT HUGE_INT::multHelper(const HUGE_INT&number, int pl, int m)
{
    int c = 0, t = 0;
    Node *n = number.head, *p;
    HUGE_INT result;
    result.clearHelper();
    while(pl>0)
    {
        if(!result.head)
        {
            result.head = new Node;
            result.head->key = 0;
            result.head->next = NULL;
            p = result.head;
        }
        else
        {
            p->next = new Node;
            p = p->next;
            p->key = 0;
            p->next = NULL;
        }
        pl--;
        sizei++;
    }
    while(n)
    {
        t = (n->key*m+c)%10;
        c = (n->key*m+c)/10;
        if(!result.head)
        {
            result.head = new Node;
            result.head->key = t;
            result.head->next = NULL;
            p = result.head;
        }
        else
        {
            p->next = new Node;
            p = p->next;
            p->key = t;
            p->next = NULL;
        }
        n = n->next;
        sizei++;
    }
    if(c!=0)
    {
        p->next = new Node;
        p = p->next;
        p->key = c;
        p->next = NULL;
        sizei++;
    }
    return result;
}

HUGE_INT HUGE_INT::mult(const HUGE_INT&num)
{
    Node *n1 = head, *n2 = num.head;
    HUGE_INT result, t;
    result.setInt(0);
    t.setInt(0);
    int p = 0;
    while(n2)
    {
        t = multHelper(*this,p,n2->key);
        result = result.add(t);
        n2 = n2->next;
        p++;
    }
    return result;
}

int HUGE_INT::getsize() const
{
    return sizei;
}

HUGE_INT&HUGE_INT::operator =(const HUGE_INT&num)
{
    Node *p = NULL, *n = num.head;
	if(n == head)
	{
		return *this;
	}
	clearHelper();
	while(n)
    {
        if(!head)
        {
            head = new Node;
            head->key = n->key;
            head->next = NULL;
            p = head;
        }
        else
        {
            p->next = new Node;
            p = p->next;
            p->key = n->key;
            p->next = NULL;
        }
        n = n->next;
        sizei++;
    }
    return *this;
}

HUGE_INT::HUGE_INT(const HUGE_INT&num)
{
    Node *p = NULL, *n = num.head;
	sizei = 0;
	head = NULL;
	while(n)
    {
        if(!head)
        {
            head = new Node;
            head->key = n->key;
            head->next = NULL;
            p = head;
        }
        else
        {
            p->next = new Node;
            p = p->next;
            p->key = n->key;
            p->next = NULL;
        }
        n = n->next;
        sizei++;
    }
}

HUGE_INT HUGE_INT::operator*(HUGE_INT rhs)
{
    return this->mult(rhs);
}

HUGE_INT HUGE_INT::operator+(HUGE_INT rhs)
{
    return this->add(rhs);
}
