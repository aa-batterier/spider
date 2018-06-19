/*
 * Information about sourcedevelopment.
 * -------------------------------------
 *  Initial creator: Andreas Johansson.
 *  Date created: 18-06-2018
 *  Last updated by: Andreas Johansson.
 *  Date for update: 19-06-2018
 */

/*
 * File: hash.cpp
 * ----------------
 *  Provides the code for the tools for the hash used in this program.
 */

/* Include files necessary for the headerfile. */
#include "hash.h"

/*
 * Function: Hash
 * Usage: The copy constructor.
 * -----------------------------
 */
Hash::Hash(const Hash& copy) : _capacity(copy._capacity),_size(copy._size),_hashTable(allocHash(_capacity))
{
	for (unsigned int i = 0; i < _capacity; i++)
		if (copy._hashTable[i]._status == BUSY || copy._hashTable[i]._status == DELETED)
			copyElement(copy._hashTable[i],_capacity);
}

/*
 * Function: Hash
 * Usage: The move constructor.
 * -----------------------------
 */
Hash::Hash(Hash&& move) : _capacity(move._capacity),_size(move._size),_hashTable(move._hashTable)
{
	move._hashTable = nullptr;
	move._capacity = move._size = 0;
}

/*
 * Function: =
 * Usage: The allocation function.
 * ---------------------------------
 */
const Hash& Hash::operator =(const Hash& allocation)
{
	_capacity = allocation._capacity;
	_size = allocation._size;
	if (_hashTable != nullptr)
		delete [] _hashTable;
	if (allocation._hashTable != nullptr)
	{
		_hashTable = allocHash(_capacity);
		for (unsigned int i = 0; i < _capacity; i++)
			if (allocation._hashTable[i]._status == BUSY || allocation._hashTable[i]._status == DELETED)
				copyElement(allocation._hashTable[i],_capacity);
	}
	else
		_hashTable = nullptr;
	return *this;
}

/*
 * Function: =
 * Usage: The allocation-move function.
 * -------------------------------------
 */
const Hash& Hash::operator =(Hash&& move)
{
	_capacity = move._capacity;
	_size = move._size;
	if (_hashTable != nullptr)
		delete [] _hashTable;
	_hashTable = move._hashTable;
	move._hashTable = nullptr;
	move._capacity = move._size = 0;
	return *this;
}

/*
 * Function: ==
 * Usage: Checks if two hashes are equal.
 * ----------------------------------------
 */
const bool Hash::operator ==(const Hash &right) const
{
	const Hash *high = nullptr,*low = nullptr;
	right._capacity > _capacity ? high = &right,low = this : high = this,low = &right;
	for (unsigned int i; i < high->_capacity; i++)
		if (!low->contains(high->_hashTable[i]._key))
			return false;
	return true;
}

/*
 * Function: +
 * Usage: Addes two hashes.
 * -------------------------
 */
const Hash Hash::operator +(const Hash *right) const
{
	Hash newHash;
	const Hash *high = nullptr,*low = nullptr;
	right->_capacity > _capacity ? high = right,low = this : high = this,low = right;
	for (unsigned int i = 0; i < high->_capacity; i++)
		if (high->_hashTable[i]._status == BUSY || high->_hashTable[i]._status == DELETED)
			newHash.add(high->_hashTable[i]._key,high->_hashTable[i]._value);
	for (unsigned int i = 0; i < low->_capacity; i++)
		if (!contains(low->_hashTable[i]._key) && (low->_hashTable[i]._status == BUSY || low->_hashTable[i]._status == DELETED))
			newHash.add(low->_hashTable[i]._key,low->_hashTable[i]._value);
	return newHash;
}

/*
 * Function: -
 * Usage: Removes the instances that are equal.
 * ----------------------------------------------
 */
const Hash Hash::operator -(const Hash &right) const
{
	Hash newHash(*this);
	for (unsigned int i = 0; i < right._capacity; i++)
		if (newHash.contains(right._hashTable[i]._key))
			newHash.remove(right._hashTable[i]._key);
	return newHash;
}

/*
 * Function: add
 * Usage: Addes a new instance.
 * ------------------------------
 */
void Hash::add(const std::string& key,const std::string& value)
{
	if (!contains(key,value))
	{
		if (_size+1 >= _capacity)
		{
			unsigned int newCapacity = generatePrime(_capacity);
			HashCell *tmp = _hashTable;
			_hashTable = allocHash(newCapacity);
			if (tmp != nullptr)
			{
				for (unsigned int i = 0; i < _capacity; i++)
					if (tmp[i]._status == BUSY || tmp[i]._status == DELETED)
						copyElement(tmp[i],newCapacity);
				delete [] tmp;
			}
			_capacity = newCapacity;
		}
		copyElement((HashCell){key,value,generateHash(key),generateHash(value),BUSY},_capacity);
		_size++;
	}
}

/*
 * Function: remove
 * Usage: Removes an instance.
 * ----------------------------
 */
void Hash::remove(const std::string& key)
{
	assert(contains(key));
	_hashTable[indexHash(key)]._status = DELETED;
}

/*
 * Function: generatePrime
 * Usage: Generates new prime numbers.
 * -------------------------------------
 */
const unsigned int Hash::generatePrime(const unsigned int oldPrime) const
{
	unsigned int newPrime;
	if (oldPrime == 0 || oldPrime == 1)
		newPrime = 2;
	else
	{
		newPrime = oldPrime*2;
		for (bool isPrime = false; isPrime == false;)
			for (unsigned int i = 2; i <= sqrt(newPrime); i++)
			{
				if (newPrime % i == 0)
				{
					isPrime = false;
					newPrime++;
					break;
				}
				else
					isPrime = true;
			}
	}
	return newPrime;
}

/*
 * Function: generateHash
 * Usage: Generate a hash number.
 * -------------------------------
 */
const unsigned int Hash::generateHash(const std::string& str) const
{
	int hashValue = 0;
	for (unsigned int i = 0; i < str.size(); i++)
		hashValue = 37*hashValue+str[i];
	return hashValue;
}

/*
 * Function: indexHash
 * Usage: Finds the index.
 * ------------------------
 */
const int Hash::indexHash(const std::string& key) const
{
	unsigned int hash = generateHash(key),row = HASH(hash);
	for (; _hashTable[row]._status != FREE; row = HASH(row+1))
		if (_hashTable[row]._hash == hash) // && _hashTable[row]._status != DELETED)
			return row;
	return -1;
}

/*
 * Function: indexHash
 * Usage: Finds the index.
 * ------------------------
 */
const int Hash::indexHash(const std::string& key,const std::string value) const
{
	unsigned int hash = generateHash(key),row = HASH(hash);
	unsigned long long int valueHash = generateHash(value);
	for (; _hashTable[row]._status != FREE; row = HASH(row+1))
		if (_hashTable[row]._hash == hash || _hashTable[row]._valueHash == valueHash) // && _hashTable[row]._status != DELETED)
			return row;
	return -1;
}

/*
 * Function: allocHash
 * Usage: Allocates a new hash.
 * ------------------------------
 */
HashCell *Hash::allocHash(const unsigned int capacity)
{
	HashCell *hashTable = new HashCell[capacity];
	for (unsigned int i = 0; i < _capacity; i++)
		hashTable[i]._status = FREE;
	return hashTable;
}

/*
 * Function: copyElement
 * Usage: Copy one element.
 * ---------------------------
 */
void Hash::copyElement(const HashCell element,const unsigned int modulus)
{
	unsigned int row = element._hash%modulus;
	for (; _hashTable[row]._status == BUSY || _hashTable[row]._status == DELETED; row = (row+1)%modulus);
	_hashTable[row] = element;
}
