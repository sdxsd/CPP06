#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <cstdint>

typedef struct s_data {
	int	num;
} Data;

uintptr_t	serialize(Data *ptr);
Data*		deserialize(uintptr_t raw);

#endif // SERIALIZATION_H
