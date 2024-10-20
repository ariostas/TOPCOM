#ifndef _POLYMAKE_TWEAKS_H
#define _POLYMAKE_TWEAKS_H "$Project: polymake $$Id: tweaks.h,v 1.1 2002/07/10 12:34:06 bzframba Exp $"

#ifdef std_ext
#  error std_ext already defined!
#endif

#if __GNUC__ == 3 && __GNUC_MINOR__ == 0
#  define std_ext std
#  define STD_EXT_HEADER(name) <name>
#else
#  define std_ext __gnu_cxx
#  define STD_EXT_HEADER(name) <ext/name>
#endif

#endif // _POLYMAKE_TWEAKS_H

// Local Variables:
// mode:C++
// End:
