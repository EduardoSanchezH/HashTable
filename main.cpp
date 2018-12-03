#include <bits/stdc++.h>
using namespace std;

int NextPrime(int a)
{
    int i, j, count, num;
    for (i = a + 1; 1; i++)
    {
        for (j = 2, count = 0; j <= i; j++)
        {
            if (i%j == 0)
            {
                count++;
            }
        }
        if (count == 1)
        {
            return i;
            break;
        }
    }
}

int doublehash(int x, int p){
	return p-(x%p);
}

template <typename HashedObj>
class HashTable
{
public:
	explicit HashTable( int size = 101 ): array( NextPrime( size ) ){
		makeEmpty( ); 
	}
	
	bool contains( const HashedObj & x ) const{ 
		return isActive( findPos( x ) ); 
	}
	
	void makeEmpty( ){
		currentSize = 0;
		for( auto & entry : array )
			entry.info = EMPTY;
	}

	bool insert( const HashedObj & x ){
		// Insert x as active
		int currentPos = findPos( x );
		if( isActive( currentPos ) )
			return false;

		array[ currentPos ].element = x;
		array[ currentPos ].info = ACTIVE;

		// Rehash; see Section 5.5
		if( ++currentSize > array.size( )/2)
			rehash( );
		return true;
	}

	//bool insert( HashedObj && x );
	bool remove( const HashedObj & x ){
		int currentPos = findPos( x );
		if( !isActive( currentPos ) )
			return false;
		array[ currentPos ].info = DELETED;
		return true;
	}

	void print(){
		cout<<currentSize<<endl;
		for (int i = 0; i < currentSize; ++i)
		{
			cout<<array[i].element<<" ";
		}
		cout<<endl;
	}

	enum EntryType { ACTIVE, EMPTY, DELETED };

private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;

		HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY ): element{ e }, info{ i}{}
		HashEntry( HashedObj && e, EntryType i = EMPTY ): element{ std::move( e ) }, info{ i}{}
	};

	vector<HashEntry> array;
	int currentSize;

	bool isActive( int currentPos ) const{
		return array[ currentPos ].info == ACTIVE;
	}

	

	/*//cuadratico
	int findPos( const HashedObj & x ) const{
		int offset = 1;
		int currentPos = myhash( x );

		while( array[ currentPos ].info != EMPTY && array[ currentPos ].element != x )
		{
			currentPos += offset; // Compute ith probe
			offset += 2;
			if( currentPos >= array.size( ) )
				currentPos -= array.size( );
		}

		return currentPos;
	}*/

	/*
	//Linear
	int findPos( const HashedObj & x ) const{
		int offset = 1;
		int currentPos = myhash( x );

		while( array[ currentPos ].info != EMPTY && array[ currentPos ].element != x )
		{
			currentPos++; // Compute ith probe
			if( currentPos >= array.size( ) )
				currentPos -= array.size( );
		}

		return currentPos;
	}
	*/

	//Doble
	int findPos( const HashedObj & x ) const{
		int currentPos = myhash( x );
		int offset = doublehash(currentPos,array.size());

		while( array[ currentPos ].info != EMPTY && array[ currentPos ].element != x )
		{
			currentPos = currentPos + offset ; // Compute ith probe
			if( currentPos >= array.size( ) )
				currentPos -= array.size( );
		}

		return currentPos;
	}


	
	void rehash( ){
		vector<HashEntry> oldArray = array;
		// Create new double-sized, empty table
		array.resize( NextPrime( 2 * oldArray.size( ) ) );
		for( auto & entry : array )
			entry.info = EMPTY;

		// Copy table over
		currentSize = 0;
		for( auto & entry : oldArray )
			if( entry.info == ACTIVE )
				insert( std::move( entry.element ) );
	}

	size_t myhash( const HashedObj & x ) const{
		static hash<HashedObj> hf;
		return hf( x ) % array.size( );
	}
};

/*template <typename Key>
class hash
{
public:
	size_t operator() ( const Key & k ) const;
};*/

template <typename k>
class hash
{
public:
	size_t operator()( const string & key )
	{
		size_t hashVal = 0;
		for( char ch : key )
			hashVal = 37 * hashVal + ch;
		return hashVal;
	}
};

class Employee
{
public:
	const string & getName( ) const
	{ return name; }

	bool operator==( const Employee & rhs ) const{ 
		return getName( ) == rhs.getName( );
	}
	
	bool operator!=( const Employee & rhs ) const{ 
		return *this != rhs;
	}
	// Additional public members not shown
private:
	string name;
	double salary;
	int seniority;
	 // Additional private members not shown
};

int main(){
	HashTable<string> a;
	//string x="casa";
	a.insert("casa");
	a.insert("ca");
	a.insert("ba");
	a.insert("da");
	a.insert("ea");
	a.insert("fa");
	//a.print();
	if(a.contains("ca")) cout<<"si"<<endl;
	else cout<<"no"<<endl;
	//cout<<NextPrime(101)<<endl;
	return 0;
}
