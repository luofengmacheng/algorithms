
namespace luofengmacheng {

template < typename T, class alloc = alloctor<T> >
class Vector {
public:
	// type definition
	typedef T value_type;
	typedef alloc allocator_type;
	typedef typename alloc::pointer pointer;
	typedef typename alloc::const_pointer const_pointer;
	typedef typename alloc::reference reference;
	typedef typename alloc::const_reference const_reference;

	// iterator
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	// access
	reference operator[](size_type n); // without check
	const_reference operator[](size_type n) const;

	reference at(size_type n); // with check
	const_reference at(size_type n);

	reference front(); // first element
	const_reference front() const;

	reference back(); // last element
	const_reference back() const;

	// constructor
	explicit Vector(const alloc& = alloc()); // constructor without parameter constructs emtpy vector
	explicit Vector(size_type n, const T& value = T(), const alloc& = alloc());
	template < typename in >
	Vector(in first, in last, const alloc& = alloc());
	Vector(const Vector&);
	Vector& operator=(const Vector&);

	~Vector();
};

}