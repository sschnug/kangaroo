/*!
	@file cbls/hlm.hpp
	@brief The header file for high level macros.
	@details This the header file for high level macros.
	@author M.A.Hakim Newton hakim.newton@nicta.com.au
	@author Duc Nghia Pham duc-nghia.pham@nicta.com.au
	@date 01.12.2011 QRL NICTA www.nicta.com.au
*/



#ifndef HlmHppIncluded
#define HlmHppIncluded


/*!
	@def Refc(Assignable, Class, System, Handle)
	@brief Assign the reference of a constant object to the assignable.
	@details Assign the reference of a constant object to the assignable.
*/
#define Refc(Assignable, Class, System, Handle) \
		Class const & Assignable = Class::refc(System, Handle)


/*!
	@def Refm(Assignable, Class, System, Handle)
	@brief Assign the reference of a mutable object to the assignable.
	@details Assign the reference of a mutable object to the assignable.
*/
#define Refm(Assignable, Class, System, Handle) \
		Class & Assignable = Class::refm(System, Handle)



/*!
	@def NewPtrc(Assignable, Class, System, Handle)
	@brief Assign the pointer of a constant object to the new assignable.
	@details Assign the pointer of a constant object to the new assignable.
*/
#define NewPtrc(Assignable, Class, System, Handle) \
		Class const * Assignable = Class::ptrc(System, Handle)



/*!
	@def NewPtrm(Assignable, Class, System, Handle)
	@brief Assign the pointer of a mutable object to the new assignable.
	@details Assign the pointer of a mutable object to the new assignable.
*/
#define NewPtrm(Assignable, Class, System, Handle) \
		Class const * Assignable = Class::ptrm(System, Handle)



/*!
	@def OldPtrc(Assignable, Class, System, Handle)
	@brief Assign the pointer of a constant object to the old assignable.
	@details Assign the pointer of a constant object to the old assignable.
*/
#define OldPtrc(Assignable, Class, System, Handle) \
		Assignable = Class::ptrc(System, Handle)


/*!
	@def OldPtrm(Assignable, Class, System, Handle)
	@brief Assign the pointer of a mutable object to the old assignable.
	@details Assign the pointer of a mutable object to the old assignable.
*/
#define OldPtrm(Assignable, Class, System, Handle) \
		Assignable = Class::ptrm(System, Handle)



#endif // HlmHppIncluded
