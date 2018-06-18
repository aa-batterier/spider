#include <cmath>
#include <cassert>

#define HASH(h) (h%_capacity)

class Hash
{
	public:
		Hash(const unsigned int capacity = 0) : _capacity(generatePrime(capacity)),_size(0),_hashTable(allocHash(_capacity)) {}
		Hash(const Hash& copy) : _capacity(copy._capacity),_size(copy._size),_hashTable(allocHash(_capacity));
		Hash(Hash&& move) : _capacity(move._capacity),_size(move._size),_hashTable(move._hashTable);
		const Hash& operator =(const Hash& allocation);
		const Hash& operator =(Hash&& move);
		const bool operator ==(const Hash &right) const;
		const bool operator <(const Hash &right) const {return _size < right._size;}
		const bool operator <=(const Hash &right) const {return *this < right || *this == right;}
		const bool operator >(const Hash &right) const {return _size > right._size;}
		const bool operator >=(const Hash &right) const {return *this > right || *this == right;}
		const Hash operator +(const Hash *right) const;
		const Hash operator -(const Hash &right) const;
		void add(const std::string& key,const std::string& value);
		void remove(const std::string& key);
		const std::string getValue(const std::string key) const {return contains(key) ? _hashTable[indexHash(key)]._value : "The key doesn't exist.";}
		const std::string getKey(const std::string key) const {return contains(key) ? _hashTable[indexHash(key)]._key : "The key doesn't exist.";}
		~Hash(void) {if (_hashTable != nullptr) delete [] _hashTable;}
	private:
		enum Status {FREE,BUSY,DELETED};
		struct HashCell
		{
			std::string _key;
			std::string _value;
			unsigned int _hash;
			Status _status;
		};
		unsigned int _capacity,_size;
		HashCell *_hashTable;
		const unsigned int generatePrime(const unsigned int oldPrime) const;
		const unsigned int generateHash(const std::string& str) const;
		const int indexHash(const std::string& key) const;
		HashCell *allocHash(const unsigned int capacity);
		void copyElement(const HashCell element,const unsigned int modulus);
};
