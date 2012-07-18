#ifndef _MEM__SS__HPP_
#define _MEM__SS__HPP_


#define GETTER(name, type) public: type name() const
#define SETTER(name, type) public: void set ## name(type val)

#ifdef NDEBUG
#define IF_DEBUG if(0)
#endif
#ifndef NDEBUG
#define IF_DEBUG if(1)
#endif

#endif
