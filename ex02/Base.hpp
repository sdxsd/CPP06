#ifndef BASE_H
#define BASE_H

class Base {
	public:
		virtual ~Base(void);
};

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

#endif // BASE_H
