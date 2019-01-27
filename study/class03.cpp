
#include <iostream.h>
#include <fstream.h>

class filemnp
{
	char *filename;
	
	void setFile()
	{
		output.open( filename );
		if( !output.is_open() ){
			cout << "\"" << filename << "\" is not opened\n";
		}
	}
	
public:
	ofstream output;
	
	filemnp()
	{
		filename = "test.txt";
		setFile();
		cout << "Opened \"" << filename << "\" with non-param\n";
	}
	
	filemnp( char *ch )
	{
		filename = ch;
		setFile();
		cout << "Opened \"" << filename << "\" with param\n";
	}
	
	~filemnp()
	{
		if( output.is_open() )
		{
			output.close();
			cout << "Closed \"" << filename << "\"\n";
		}
	}
	
	
};