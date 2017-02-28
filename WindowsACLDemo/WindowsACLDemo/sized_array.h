#pragma once

#ifndef _ALOGRITHM_
#include <algorithm>
#endif /* _ALGORITHM_ */


namespace std {

	template<class DatType>
	class sized_array
	{/**	A simplified scoped_array class from Boost. I felt the scoped_array from Boost was too useful to not be used.
	 *	But since I did not want the dependencies/or the bloat from Boost, I instead rolled out my own implementation of it.
	 *	This class zeroes out the array during initialisation. This means the weird _tcsncat()/_tcscat() null terminator bugs
	 *	do not affect me. This makes it act more like a C99 VLA rather than an auto_ptr.
	 **/
	private:
		size_t Size;
		DatType * OurPtr;	/* The scope of this variable is determined by the object. */
	public:
		explicit sized_array (size_t len = 1) : OurPtr(new DatType[len]), Size(len)
		{
			std::fill/*<DatType *, DatType>*/(OurPtr, OurPtr + len, 0);
		};

		sized_array(const sized_array &OldClass) : Size(OldClass.Size), OurPtr(new DatType[OldClass.Size])
		{
			std::copy<const DatType *, DatType *>(OldClass.OurPtr, OldClass.OurPtr + Size, OurPtr);
		};

		void reset(size_t len = 1)
		{/* Also called release and reallocate. */
			delete [] OurPtr;
			OurPtr = new DatType[len];
			std::fill/*<DatType *, DatType>*/(OurPtr, OurPtr + len , 0);
			Size = len;
		};


		DatType *get(void)
		{/* Accessor. Only get is currently implemented. */
			return OurPtr;
		};

		size_t get_Size(void)
		{/* For Convenience */
			return Size;
		};


		sized_array &operator=(const sized_array &OldClass)
		{/* This equality may be required by CObjSecurity. */
			if(this==&OldClass) return *this;

			Size = OldClass.Size;
			this->reset(Size);
			std::copy<const DatType *, DatType *>(OldClass.OurPtr, OldClass.OurPtr + Size, OurPtr);
			return *this;
		};

		virtual ~sized_array()
		{
			delete [] OurPtr;
			OurPtr = NULL;
		};
	};

} /* namespace std */