/* Copyright(C) 2013, OpenOSEK by Fan Wang(parai). All rights reserved.
 *
 * This file is part of OpenOSEK.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Email: parai@foxmail.com
 * Sourrce Open At: https://github.com/parai/OpenOSEK/
 */
#ifndef _PORTABLE_H_
#define _PORTABLE_H_
/* ================================ INCLUDEs  =============================== */

/* ================================ MACROs    =============================== */
/*
 * Interrupt enable/disable
 */
#define DISABLE_INTERRUPT() (void)knl_disable_int()
#define ENABLE_INTERRUPT()  knl_enable_int(TRUE)

/*
 * Start/End interrupt disable section
 */
#define BEGIN_DISABLE_INTERRUPT()	{ imask_t _primask_ = knl_disable_int()
#define END_DISABLE_INTERRUPT()	knl_enable_int(_primask_); }

/*
 * Start/End critical section
 */
#define BEGIN_CRITICAL_SECTION()	{ imask_t _primask_ = knl_disable_int()
#define END_CRITICAL_SECTION()	if ( knl_curtsk != knl_schedtsk         \
                                     && (0u == knl_taskindp)            \
                                     && (0u == knl_dispatch_disabled) ) { \
        knl_dispatch();                                                 \
    }                                                                   \
    knl_enable_int(_primask_); }

#define knl_dispatch() knl_dispatch_entry()
#define knl_isr_dispatch() knl_dispatch_entry()
/* ================================ TYPEs     =============================== */
/* interrupr mask type.determined by CPU */
typedef unsigned int imask_t;

/* ================================ DATAs     =============================== */

/* ================================ FUNCTIONs =============================== */
IMPORT imask_t knl_disable_int( void );
IMPORT void knl_enable_int( imask_t mask );
IMPORT void knl_force_dispatch(void);
IMPORT void knl_setup_context(TaskType taskid);
IMPORT void knl_dispatch_entry(void);

#endif /* _PORTABLE_H_ */
