
#include <iostream.h>

class two_d
{
	int x, y;
public:
	two_d( int a, int b )
	{
		x = a;
		y = b;
	}
	friend ostream &operator<<( ostream &stream, two_d obj );
	friend istream &operator>>( istream &stream, two_d &obj );
};


ostream &operator<<( ostream &stream, two_d obj )
{
	stream << obj.x << " ,";
	stream << obj.y << "\n";
	
	return stream;
}


istream &operator>>( istream &stream, two_d &obj )
{
	cout << "Enter x, y values  ";
	cout << obj.x + obj.y << '\n';
	stream >> obj.x >> obj.y;
	cout << obj.x + obj.y << '\n';
	
	return stream;
}

