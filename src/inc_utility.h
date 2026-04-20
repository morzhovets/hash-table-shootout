#include <momo/Version.h>
#include <momo/Utility.h>

#if MOMO_VERSION_MAJOR == 3 && MOMO_VERSION_MINOR < 12

#undef MOMO_FRIENDS_SIZE_BEGIN_END_CONST
#define MOMO_FRIENDS_SIZE_BEGIN_END_CONST(Object, ConstIterator) \
	friend size_t size(const Object& object) noexcept \
	{ \
		return object.GetCount(); \
	} \
	friend ConstIterator begin(const Object& object) noexcept \
	{ \
		return object.GetBegin(); \
	} \
	friend ConstIterator end(const Object& object) noexcept \
	{ \
		return object.GetEnd(); \
	}

#undef MOMO_FRIENDS_BEGIN_END
#define MOMO_FRIENDS_BEGIN_END(Object, Iterator) \
	friend Iterator begin(Object& object) noexcept \
	{ \
		return object.GetBegin(); \
	} \
	friend Iterator end(Object& object) noexcept \
	{ \
		return object.GetEnd(); \
	}

#endif
