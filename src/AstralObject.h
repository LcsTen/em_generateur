#ifndef astral_object_h
#define astral_object_h

#include <stddef.h>

class AstralObject{
	private:
		size_t radius;
		
	public:
		AstralObject(size_t r);
		
		virtual bool isStar() const;
		virtual bool isWorld() const;
		size_t getRadius() const;
};

#endif // astral_object_h
