#include <momo/Version.h>

#if MOMO_VERSION_MAJOR == 3 && MOMO_VERSION_MINOR < 10

#include <momo/Utility.h>
#undef MOMO_FRIENDS_SIZE_BEGIN_END_CONST
#define MOMO_FRIENDS_SIZE_BEGIN_END_CONST(Object, ConstIterator) \
	friend ConstIterator begin(const Object& object) noexcept(noexcept(object.GetBegin())) \
	{ \
		return object.GetBegin(); \
	} \
	friend ConstIterator end(const Object& object) noexcept(noexcept(object.GetEnd())) \
	{ \
		return object.GetEnd(); \
	}

#endif

#include <momo/DataTable.h>
