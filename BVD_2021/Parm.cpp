#include "Parm.h"
#include "Error.h"
#include <wchar.h>

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM rp{};
		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE) throw ERROR_THROW(104);

			if (wcsstr(argv[i], PARM_IN) == argv[i])
				wcscpy_s(rp.in, wcsstr(argv[i], L":") + 1);

			if (wcsstr(argv[i], PARM_OUT) == argv[i])
				wcscpy_s(rp.out, wcsstr(argv[i], L":") + 1);

			if (wcsstr(argv[i], PARM_LOG) == argv[i])
				wcscpy_s(rp.log, wcsstr(argv[i], L":") + 1);
		}

		if (!wcslen(rp.in)) throw ERROR_THROW(100);
		if (!wcslen(rp.out))
		{
			wcscpy_s(rp.out, rp.in);
			if (wcslen(rp.out) + wcslen(PARM_OUT_DEFAULT_EXT) < PARM_MAX_SIZE)
				wcscpy_s(rp.out + wcslen(rp.out), wcslen(rp.out), PARM_OUT_DEFAULT_EXT);
			else throw ERROR_THROW(104);
		}
		if (!wcslen(rp.log))
		{
			wcscpy_s(rp.log, rp.in);
			if (wcslen(rp.log) + wcslen(PARM_LOG_DEFAULT_EXT) < PARM_MAX_SIZE)
				wcscpy_s(rp.log + wcslen(rp.log), wcslen(rp.log), PARM_LOG_DEFAULT_EXT);
			else throw ERROR_THROW(104);
		}
		return rp;
	}
}