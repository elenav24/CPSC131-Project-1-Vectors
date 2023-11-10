// Name: Elena Marquez
// CWID: 885318089
// Email: elena-marquez@csu.fullerton.edu

/**
 * TODO: Complete this class!
 */

/// Your welcome
#include <assert.h>
#include <iostream>
#include <string>


//
template <typename T>
class MyVector
{
	public:
		
		/*******************
		 * Static constants
		 ******************/
		
		/// Default capacity
		static constexpr size_t DEFAULT_CAPACITY = 64;
		
		/// Minimum capacity
		static constexpr size_t MINIMUM_CAPACITY = 8;
		
		/*****************************
		 * Constructors / Destructors
		 ****************************/
		
		/// Normal constructor
		MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY) {
			
			this->capacity_ = capacity;
			T* elements_array = new T[capacity_];
			this->elements_ = elements_array;
		}
		
		/// Copy constructor
		MyVector(const MyVector& other) {
			
			T* elements_array = new T[capacity_];
			this->elements_ = elements_array;
			copyOther(other);
		}
		
		/**
		 * Destructor
		 * Should call clear() so each element gets its destructor called.
		 * Then, de-allocate the internal array and make it a nullptr, if its not already a nullptr.
		 */
		~MyVector() {
			
			clear();
			delete [] elements_;
			elements_ = nullptr;
		}
		
		/************
		 * Operators
		 ************/
		
		///	Assignment operator
		MyVector& operator=(const MyVector& rhs) {
			
			if (this == &rhs) {
				return *this;
			}

			copyOther(rhs);
			return *this;
		}
		
		/// Operator overload to at()
		T& operator[](size_t index) const {
			
			if ((index >= this->size_) || (index < 0)) {
				throw std::out_of_range("Index out of range");
			}
			return this->elements_[index];
			// TODO: Your code here
		}
		
		/************
		 * Accessors
		 ************/
		
		/// Return the number of valid elements in our data
		size_t size() const {
			
			return this->size_;
		}
		
		/// Return the capacity of our internal array
		size_t capacity() const {
			
			return this->capacity_;
		}
		
		/**
		 * Check whether our vector is empty
		 * Return true if we have zero elements in our array (regardless of capacity)
		 * Otherwise, return false
		 */
		bool empty() const {
			
			return (size_ == 0);
			// TODO: Your code here
		}
		
		/// Return a reference to the element at an index
		T& at(size_t index) const {
			
			if ((index >= this->size_) || (index < 0)) {
				throw std::out_of_range("Index out of range");
			}
			return this->elements_[index];
			// TODO: Your code here
		}
		
		/***********
		 * Mutators
		 ***********/
		
		/**
		 * Reserve capacity in advance, if our capacity isn't currently large enough.
		 * Useful if we know we're about to add a large number of elements, and we'd like to avoid the overhead of many internal changes to capacity.
		 */
		void reserve(size_t capacity) {
			
			if (capacity > this->capacity_) {
				this->capacity_ = capacity;
			}
		}
		
		/**
		 * Set an element at an index.
		 * Throws range error if outside the size boundary.
		 * Returns a reference to the newly set element (not the original)
		 */
		T& set(size_t index, const T& element) {
			
			if ((index >= this->size_) || (index < 0)) {
				throw std::out_of_range("Index out of range");
			}
			this->elements_[index].~T();
			this->elements_[index] = element;
			return this->elements_[index];
		}
		
		/**
		 * Add an element onto the end of our vector, increasing the size by 1
		 * Should rely on the insert() function to avoid repeating code.
		 * Returns a reference to the newly inserted element
		 */
		T& push_back(const T& element) {

			grow();
			elements_[size_] = element;
			size_++;
			return this->elements_[size_-1];
		}
		
		/**
		 * Remove the last element in our vector, decreasing the size by 1
		 * Should rely on the erase() function to avoid repeating code.
		 * Returns the new size.
		 */
		size_t pop_back() {

			shrink();
			return erase(this->size_-1);
		}
		
		/**
		 * Insert an element at some index in our vector, increasing the size by 1
		 * 
		 * Scoot all elements at index and beyond, one to the right. This
		 * makes a "hole" available at the index, where you can then place
		 * the new element.
		 * 
		 * Returns a reference to the newly added element (not the original).
		 */
		T& insert(size_t index, const T& element) {
			
			if ((index >= this->size_) || (index < 0)) {
				throw std::out_of_range("Index out of range");
			}
			grow();
			for (size_t spot = this->size_; spot > index; spot--) {
				this->elements_[spot] = this->elements_[spot-1];
			}
			this->elements_[index] = element;
			++size_;
			return this->elements_[index];
		}
		
		/**
		 * Erase one element in our vector at the specified index, decreasing the size by 1.
		 * 
		 * This means you'd then have to scoot elements to the left to fill the "hole"
		 * 	left by the erased element.
		 * 
		 * Throws std::range_error if the index is out of bounds.
		 * 
		 * Calls the erased element's destructor.
		 * 
		 * Returns the new size.
		 */
		size_t erase(size_t index) {
			
			if ((index >= this->size_) || (index < 0)) {
				throw std::out_of_range("Index out of range");
			}
			for (size_t spot = index; spot < size_; spot++) {
				this->elements_[spot].~T();
				this->elements_[spot] = this->elements_[spot+1];
			}
			shrink();
			--size_;
			return this->size_;
		}
		
		/**
		 * Calls each element's destructor, then clears our internal
		 * data by setting size to zero and resetting the capacity.
		*/
		void clear() {
			
			for (size_t i = 0; i < this->size_; i++) {
				this->elements_[i].~T();
			}
			size_ = 0;
			capacity_ = DEFAULT_CAPACITY;
			delete [] elements_;
			T* elements_array = new T[capacity_];
			elements_ = elements_array;
		}

		void grow() {

			if (this->size_ == this->capacity_) {
				changeCapacity(this->capacity_ * 2);
			}
		}

		void shrink() {

			if ((this->size_ * 3) < this->capacity_) {
				changeCapacity(this->capacity_ / 2);
			}
		}

	/**
	 * Begin private members and methods.
	 * Private methods can often contain useful helper functions,
	 * or functions to reduce repeated code.
	*/
	private:
		
		/// Number of valid elements currently in our vector
		size_t size_ = 0;
		
		/// Capacity of our vector; The actual size of our internal array
		size_t capacity_ = 0;
		
		/**
		 * Our internal array of elements of type T.
		 * Starts off as a null pointer.
		 */
		T* elements_ = nullptr;
		
		/**
		 * Helper function that is called whenever we need to change the capacity of our vector
		 * Should throw std::range_error when asked to change to a capacity that cannot hold our existing elements.
		 * It's probably a good idea to make an additional helper function that decides
		 * 	whether to change capacity at all (and to what new capacity), that your public functions can rely upon.
		 */
		void changeCapacity(size_t c) {
			
			if (c <= this->size_) {
				throw std::range_error("Range error");
			}
			T* elements_array = new T[c];
			for (size_t index = 0; index < this->size_; index++) {
				elements_array[index] = this->elements_[index];
			}
			this->capacity_ = c;
			delete [] this->elements_;
			this->elements_ = elements_array;
		}
		
		/**
		 * Copy another vector's elements into our own, by value.
		 * Does not simply copy the other vector's array's pointer
		 * Does not care about matching the capacity exactly.
		 * This is a helper function relied upon by the copy constructor and the assignment operator,
		 * 	to avoid repeated code.
		 * 
		 * You will probably want to make additional helper functions to make this one easier.
		 * Here is a suggested strategy for copying the internal array:
		 * 1. Deallocate the current array for 'this' (if it is already allocated)
		 * 2. Allocate a new array for 'this' of the appropriate size
		 * 3. Use a loop to copy elements one-by-one (by value)
		 * 4. Copy other relevant properties from the 'other' to 'this'
		 */
		void copyOther(const MyVector& other) {
			
			delete [] elements_;
			this->size_ = other.size();
			this->capacity_ = other.capacity();
			T* elements_array = new T[capacity_];
			this->elements_ = elements_array;
			for (size_t index = 0; index < this->size_; index++) {
				this->elements_[index] = other.elements_[index];
			}
		}
};

