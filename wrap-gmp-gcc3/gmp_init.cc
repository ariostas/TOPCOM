/* Copyright (c) 1997-2002
   Technische Universitaet Berlin, Germany
   Department of Mathematics,
   Research Group Algorithmic and Discrete Mathematics
   mailto:polymake@math.tu-berlin.de

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330 Boston, MA 02111-1307, USA.
*/

#ident "$Project: polymake $$Id: gmp_init.cc,v 1.3 2003/01/27 08:11:47 bzframba Exp $"

#pragma implementation

#include <memory>
#include "gmp_init.h"

gmp_alloc_init::gmp_alloc_init() {
#ifdef _POLYMAKE_STD_STL_ALLOC_H
   typedef pm::alloc alloc;
#else
# if __GNUC__==3
#if __GNUC_MINOR__<1
   typedef std::alloc alloc;
#else
   typedef std::__alloc alloc;
#endif
# else
   //////////////////////////////////////////////////////////////////////////////
   // some 2.95.3 versions already have the underscore removed
   // 2003/01/24 jr:
   //    typedef std::__alloc alloc;
   typedef std::alloc alloc;
   // end jr.
   //////////////////////////////////////////////////////////////////////////////
# endif
#endif

   static bool done=false;
   if (!done) {
      mp_set_memory_functions (alloc::allocate, alloc::reallocate, alloc::deallocate);
      done=true;
   }
}
