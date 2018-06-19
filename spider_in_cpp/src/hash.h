/*
 * Information about sourcedevelopment.
 * -------------------------------------
 *  Initial creator: Andreas Johansson.
 *  Date created: 18-06-2018
 *  Last updated by: Andreas Johansson.
 *  Date for update: 19-06-2018
 */

/*
 * File: hash.h
 * ----------------
 *  Provides tools for the hash used in this program.
 */

#ifndef _spider_h
#define _spider_h

/* Include files necessary for the headerfile. */
#include <cmath>
#include <cassert>
#include <iostream>

/* Macros. */

/*
 * Macro: HASH
 * Usage: The hash function.
 * --------------------------
 *  This macro is the hash function to get the index number
 *  for the instnace in the hash.
 */
#define HASH(h) (h%_capacity)

/* Typedefinitions. */

/*
 * Typedefinition: Status
 * -----------------------
 *  Status store the state of the instance.
 */
enum Status {FREE,BUSY,DELETED};

/*
 * Typedefinition: HashCell
 * --------------------------
 *  Contains all the info one instance in the hash needs.
 */
struct HashCell
{
	std::string _key,_value;
	unsigned int _hash;
	unsigned long long int _valueHash;
	Status _status;
};

/* Classdefinitions. */

/*
 * Classdefinition: Hash 
 * -------------------------
 *  This class contains all the functions and varibles the hash
 *  needs to operate.
 */
class Hash
{
	public:
		/* Function prototypes. */

		/*
		 * Function: Hash
		 * Usage: The contructor.
		 * ------------------------
		 *  This is the constructor of the Hash class.
		 *  It sets the start values when the hash is created.
		 */
		Hash(const unsigned int capacity = 0) : _capacity(generatePrime(capacity)),_size(0),_hashTable(allocHash(_capacity)) {}

		/*
		 * Function: Hash
		 * Usage: The copy constructor.
		 * -----------------------------
		 *  This constructor is used when you want to copy the hash.
		 */
		Hash(const Hash& copy);

		/*
		 * Function: Hash
		 * Usage: The move constructor.
		 * -----------------------------
		 *  This constructor is used when you want to move the hash.
		 */
		Hash(Hash&& move);

		/*
		 * Function: =
		 * Usage: The allocation function.
		 * ---------------------------------
		 *  This function copy the hash on the right side of =
		 *  to the hash on the left side of =.
		 */
		const Hash& operator =(const Hash& allocation);

		/*
		 * Function: =
		 * Usage: The allocation-move function.
		 * -------------------------------------
		 *  Is almost the same as the one above, with the difference
		 *  that this function moves the hash.
		 */
		const Hash& operator =(Hash&& move);

		/*
		 * Function: ==
		 * Usage: Checks if two hashes are equal.
		 * ----------------------------------------
		 *  This functions checks if two hashes are equal.
		 *  If they are equal then true is returned, if they are not equal
		 *  then false is returned.
		 */
		const bool operator ==(const Hash &right) const;

		/*
		 * Function: <
		 * Usage: Checks if one hash is less.
		 * ---------------------------------------
		 *  This function checks if the left side hash is lesser then the
		 *  hash on the right side, if so the true is returned, else false
		 *  is returned.
		 */
		const bool operator <(const Hash &right) const {return _size < right._size;}

		/*
		 * Function: <=
		 * Usage: Checks if one hash is less or equal.
		 * ---------------------------------------------
		 *  Combination of the two above.
		 */ 
		const bool operator <=(const Hash &right) const {return *this < right || *this == right;}

		/*
		 * Function: >
		 * Usage: Checks if one hash is more.
		 * -----------------------------------
		 *  The same as < but opposite.
		 */
		const bool operator >(const Hash &right) const {return _size > right._size;}

		/*
		 * Function: >=
		 * Usage: Chechs if one hash is more or equal.
		 * --------------------------------------------
		 *  > and == combined.
		 */
		const bool operator >=(const Hash &right) const {return *this > right || *this == right;}

		/*
		 * Function: +
		 * Usage: Addes two hashes.
		 * -------------------------
		 *  This function addeds two hashes together, and
		 *  returns the combined hash, sorts out duplicates.
		 */
		const Hash operator +(const Hash *right) const;

		/*
		 * Function: -
		 * Usage: Removes the instances that are equal.
		 * ----------------------------------------------
		 *  This function creates a copy of the hash on the left side
		 *  and then removes all instances from it that are the same as
		 *  the instances in the hash on the right side.
		 */
		const Hash operator -(const Hash &right) const;

		/*
		 * Function: add
		 * Usage: Addes a new instance.
		 * ------------------------------
		 *  add adds a new instance to the hash.
		 */
		void add(const std::string& key,const std::string& value);

		/*
		 * Function: remove
		 * Usage: Removes an instance.
		 * ----------------------------
		 *  remove change the lable from BUSY to DELETED,
		 *  aka deletes an instnace.
		 */
		void remove(const std::string& key);

		/*
		 * Function: contains
		 * Usage: Check if the instance exist.
		 * ------------------------------------
		 *  contains check if the instance exist in the hash
		 *  only based on the instance key.
		 */
		const bool contains(const std::string& key) const {return indexHash(key) == -1 ? false : true;}

		/*
		 * Function: contains
		 * Usage: Chech if the instance exist.
		 * ------------------------------------
		 *  contains check if the instance exist in the hash
		 *  both based on the instance key and value.
		 */
		const bool contains(const std::string& key,const std::string& value) const {return indexHash(key,value) == -1 ? false : true;}

		/*
		 * Function: getValue
		 * Usage: Returns the instance value.
		 * -----------------------------------
		 *  getValue returns the instance value which is find by the key.
		 */
		const std::string getValue(const std::string key) const {return contains(key) ? _hashTable[indexHash(key)]._value : "The key doesn't exist.";}

		/*
		 * Function: getKey
		 * Usage: Returns the instance key.
		 * ---------------------------------
		 *  getKey returns the instance key which is find by the key.
		 */
		const std::string getKey(const std::string key) const {return contains(key) ? _hashTable[indexHash(key)]._key : "The key doesn't exist.";}

		/*
		 * Function: ~Hash
		 * Usage: The destructor.
		 * ------------------------
		 *  This is the destructor of this class.
		 *  It destroys the hash.
		 */
		~Hash(void) {if (_hashTable != nullptr) delete [] _hashTable;}

	private:

		/*
		 * Function: generatePrime
		 * Usage: Generates new prime numbers.
		 * -------------------------------------
		 *  generatePrime generates and returns a new prime number which
		 *  is the closest larger prime number to the original prime number times two.
		 */
		const unsigned int generatePrime(const unsigned int oldPrime) const;

		/*
		 * Function: generateHash
		 * Usage: Generate a hash number.
		 * -------------------------------
		 *  generateHash generates and returns a new hash based on the string sent in.
		 */
		const unsigned int generateHash(const std::string& str) const;

		/*
		 * Function: indexHash
		 * Usage: Finds the index.
		 * ------------------------
		 *  indexHash finds the index in the hash of the instance based on the instance key.
		 *  Returns the index or -1 if the key is not found.
		 */
		const int indexHash(const std::string& key) const;

		/*
		 * Function: indexHash
		 * Usage: Finds the index.
		 * ------------------------
		 *  indexHash finds the index in the hash of the instance based
		 *  on the instance key and value.
		 *  Returns the index or -1 if the key or value is not found.
		 */
		const int indexHash(const std::string& key,const std::string value) const;

		/*
		 * Function: allocHash
		 * Usage: Allocates a new hash.
		 * ------------------------------
		 *  allocHash allocates and returns a new hash with the specifed capacity.
		 *  Every instance in the hash is labled FREE.
		 */
		HashCell *allocHash(const unsigned int capacity);

		/*
		 * Function: copyElement
		 * Usage: Copy one element.
		 * ---------------------------
		 *  copyElement adds the element varible to the hash throw the modulus
		 *  hash algrithem.
		 */
		void copyElement(const HashCell element,const unsigned int modulus);

		/* Varibles. */

		/*
		 * Varible: _capacity
		 * -------------------
		 *  The real size of the hash.
		 *  This should always be a prime number!
		 */
		unsigned int _capacity;

		/*
		 * Varible: _size
		 * ---------------
		 *  The amount of instnaces in the hash.
		 */
		unsigned int _size;

		/*
		 * Varible: _hashTable
		 * --------------------
		 *  Pointer the the hash where all the info are stored.
		 */
		HashCell *_hashTable;
};

#endif
