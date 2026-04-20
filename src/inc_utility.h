#include <momo/Version.h>
#include <momo/Utility.h>

#if MOMO_VERSION_MAJOR == 3 && 4 <= MOMO_VERSION_MINOR && MOMO_VERSION_MINOR < 12

#undef MOMO_FRIENDS_SIZE_BEGIN_END_CONST
#define MOMO_FRIENDS_SIZE_BEGIN_END_CONST(Class, ConstIterator) \
	friend ConstIterator begin(const Class& object) noexcept \
	{ \
		return object.GetBegin(); \
	} \
	friend ConstIterator end(const Class& object) noexcept \
	{ \
		return object.GetEnd(); \
	}

#undef MOMO_FRIENDS_BEGIN_END
#define MOMO_FRIENDS_BEGIN_END(Class, Iterator) \
	friend Iterator begin(Class& object) noexcept \
	{ \
		return object.GetBegin(); \
	} \
	friend Iterator end(Class& object) noexcept \
	{ \
		return object.GetEnd(); \
	}

#endif
