#include <iostream>

#ifndef HUGE_INT_H_INCLUDED
#define HUGE_INT_H_INCLUDED

using namespace std;

struct Node
{
    int key;
    Node *next;
};


class HUGE_INT
{
private:
    Node *head;
    int sizei;
    void printHelper(ostream &, Node*) const;
    HUGE_INT multHelper(const HUGE_INT&, int , int);
    void clearHelper(void);
public:
    HUGE_INT();
    ~HUGE_INT();
    HUGE_INT(unsigned long long int);
	void setInt(unsigned long long int);
    HUGE_INT(const HUGE_INT&);
    HUGE_INT add(const HUGE_INT&);
    HUGE_INT mult(const HUGE_INT&);
    HUGE_INT &operator=(const HUGE_INT&);
    HUGE_INT operator*(const HUGE_INT);
    HUGE_INT operator+(const HUGE_INT);
    int getsize() const;
    friend ostream&operator<<(ostream&, const HUGE_INT&);
};

#endif
