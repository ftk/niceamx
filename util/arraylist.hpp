#ifndef UTIL_ARRAYLIST_HPP
#define UTIL_ARRAYLIST_HPP

#include <array>
#include <cassert>

namespace util {

// forward iterable set with fast search
template <std::size_t N>
class arraylist
{
public:
    enum
    {
        END = -2,
        EMPTY = -1
    };

private:
    std::array<int, N> vl;
    int first = END; // first non-empty element

public:
    arraylist()
    {
        vl.fill(EMPTY);
    }

    bool set(int idx) // insert element to the list
    {
        if(vl.at(idx) != EMPTY)
            return false;
        if(idx < first || first == END) // empty list or inserting to the front O(1)
        {
            vl[idx] = first;
            first = idx;
            return true;
        }
        // inserting to the middle or the back (slow)
        int prev = idx - 1;
        while(prev >= first && vl[prev] == EMPTY)
            --prev;
        assert(prev >= first);
        vl[idx] = vl[prev];
        vl[prev] = idx;
        return true;
    }

    bool unset(int idx) // remove element from the list
    {
        if(vl.at(idx) == EMPTY)
            return false;
        if(idx == first)
        {
        	// pop front O(1)
            first = vl[idx];
        }
        else
        {
        	// slow
            int prev = idx - 1;
            while(prev >= first && vl[prev] == EMPTY)
                --prev;
            assert(prev >= first);
            vl[prev] = vl[idx];
        }
        vl[idx] = EMPTY; // any iterators pointing to this element will be invalidated
        return true;
    }

    bool get(int idx) const
    {
        return vl.at(idx) != EMPTY;
    }

    bool operator [] (int idx) const
    {
        return vl[idx] != EMPTY;
    }
    
    bool empty() const
    {
    	return first == END;
    }
    
    std::size_t size() const // slow
    {
    	std::size_t result = 0;
    	int idx = first;
    	while(idx != END)
    	{
    		++result;
    		idx = vl[idx];
    	}
    	return result;
    }

	// safe version
    int next(int idx) const
    {
        if(idx < 0 || first > idx || first == END)
            return first;
        if(idx >= static_cast<int>(N))
            return END;
    	// next integer or END if idx was the last element
        if(vl[idx] != EMPTY)
            return vl[idx];
        // idx was deleted ...

        //if(first > idx || first == END)
        //	return first; // return first element or END if list is empty
		
        int prev = idx - 1;
        while(prev >= first && vl[prev] == EMPTY)
            --prev;
        assert(prev >= first);
        // prev - element before idx; vl[prev] - element after idx
        return vl[prev];
    }


	// input iterator
    class const_iterator
    {
    private:
        const std::array<int, N>& vl; // cref
        int index;
    public:
        const_iterator(const std::array<int, N>& vl, int index) : vl(vl), index(index)
        {
        }

        typedef int value_type;
        typedef const int * pointer;
        typedef const int & reference;

        const_iterator& operator++()
        {
            // iterator should be valid
            // if index may have been unset, use arraylist::next(index)
            index = vl[index];
            return *this;
        }
        bool operator ==(const const_iterator& rhs) const
        {
            return index == rhs.index;
        }
        bool operator !=(const const_iterator& rhs) const
        {
            return index != rhs.index;
        }
        bool operator < (const const_iterator& rhs) const
        {
            return index < rhs.index;
        }

        value_type operator * () const
        {
            return index;
        }

    };
    typedef const_iterator iterator;


    // iterator
    const_iterator begin() const
    {
        return const_iterator(vl, first);
    }
    const_iterator end() const
    {
        return const_iterator(vl, END);
    }
};





} // util

#endif
