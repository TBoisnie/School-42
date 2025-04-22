#include <cstring>

class N
{
public:
	int ( N::*fn )( N & );
	char annotation[100];
	int n;

public:
	N( int n ) : n(n), fn(&N::operator+) {}

	int operator+( N & other ) { return this->n + other.n; }
	int operator-( N & other ) { return this->n - other.n; }

	int setAnnotation( char const * str )
		{ return std::memcpy(this->annotation, str, std::strlen(str)); }
};

int main(int argc, const char **argv, const char **envp)
{
	N *a; // ebx
	N *b; // ebx
	N *c; // [esp+1Ch] [ebp-8h]

	if ( argc <= 1 )
	exit(1);

	a = new N(5);
	b = new N(6);
	c = a;
	c->setAnnotation(argv[1]);

	return (b->*(b->fn))(*c);
}
