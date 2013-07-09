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
    static const std::size_t static_size = N;
    typedef int value_type;

private:
    std::array<int, N> vl;
    int first = END; // first non-empty element

public:
    arraylist() noexcept
    {
        vl.fill(EMPTY);
    }

    bool set(int idx) noexcept // insert element in the list
    {
        if(static_cast<unsigned int>(idx) >= N)
            return false; // out of bounds
        if(vl[idx] != EMPTY)
            return false;
        if(idx < first || first == END) // empty list or inserting in front O(1)
        {
            vl[idx] = first;
            first = idx;
            return true;
        }
        // inserting in the middle (slow)
        int prev = idx - 1;
        while(prev >= first && vl[prev] == EMPTY)
            --prev;
        assert(prev >= first);
        vl[idx] = vl[prev];
        vl[prev] = idx;
        return true;
    }

    bool unset(int idx) noexcept // remove element from the list
    {
        if(static_cast<unsigned int>(idx) >= N)
            return false; // out of bounds
        if(vl[idx] == EMPTY)
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

    bool get(int idx) const noexcept
    {
        if(static_cast<unsigned int>(idx) >= N)
            return false; // out of bounds
        return vl[idx] != EMPTY;
    }
    bool at(int idx) const noexcept { return get(idx); }

    bool operator [] (int idx) const noexcept
    {
        return vl[idx] != EMPTY;
    }
    
    bool empty() const noexcept
    {
    	return first == END;
    }
    
    int min() const noexcept
    {
        return (!empty()) ? first : -1;
    }

    const int * data() const noexcept
    {
        // pointer to the internal array
        return vl.data();
    }

    std::size_t size() const noexcept // slow
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
    int next(int idx) const noexcept
    {
        if(idx < 0 || first > idx || first == END)
            return first; //
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
    int prev(int idx) const noexcept // slow
    {
        if(idx < 0 || first > idx || first == END)
            return END; //
        if(idx > static_cast<int>(N))
            idx = N;

        int prev = idx - 1;
        while(prev >= first && vl[prev] == EMPTY)
            --prev;
        assert(prev >= first);
        return prev;
    }


	// input iterator
    class const_iterator
    {
    private:
        const int * const vl; // cref
        int index;
    public:
        const_iterator(const int * vl, int index) noexcept : vl(vl), index(index)
        {
        }
        const_iterator() noexcept : vl(NULL), index(END) {}

        typedef int value_type;
        typedef const int * pointer;
        typedef const int & reference;

        const_iterator& operator++() noexcept
        {
            // iterator should be valid
            // if index may have been unset, use arraylist::next(index)
            index = vl[index];
            return *this;
        }
        const_iterator operator++(int) noexcept
        {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator ==(const const_iterator& rhs) const noexcept
        {
            return index == rhs.index;
        }
        bool operator !=(const const_iterator& rhs) const noexcept
        {
            return index != rhs.index;
        }
        bool operator < (const const_iterator& rhs) const noexcept
        {
            return index < rhs.index;
        }

        value_type operator * () const noexcept
        {
            return index;
        }
        pointer operator -> () const noexcept
        {
            return &index;
        }

    };
    typedef const_iterator iterator;


    // iterator
    const_iterator begin() const noexcept
    {
        return const_iterator(data(), first);
    }
    const_iterator end() const noexcept
    {
        return const_iterator();
    }
};





} // util

#endif
