/* SPDX-License-Identifier: GPL-2.0-only */
/*
 *  Author:	Nicolas Pitre
 *  Created:	Jun 15, 2001
 *  Copyright:	MontaVista Software Inc.
 */

#ifndef __SOC_PXA_CPU_H
#define __SOC_PXA_CPU_H

#ifdef CONFIG_ARM
#include <asm/cputype.h>
#endif

/*
 *   CPU     Stepping     CPU_ID         JTAG_ID
 *
 *  PXA210	B0	0x69052922	0x2926C013
 *  PXA210	B1	0x69052923	0x3926C013
 *  PXA210	B2	0x69052924	0x4926C013
 *  PXA210	C0	0x69052D25	0x5926C013
 *
 *  PXA250	A0	0x69052100	0x09264013
 *  PXA250	A1	0x69052101	0x19264013
 *  PXA250	B0	0x69052902	0x29264013
 *  PXA250	B1	0x69052903	0x39264013
 *  PXA250	B2	0x69052904	0x49264013
 *  PXA250	C0	0x69052D05	0x59264013
 *
 *  PXA255	A0	0x69052D06	0x69264013
 *
 *  PXA26x	A0	0x69052903	0x39264013
 *  PXA26x	B0	0x69052D05	0x59264013
 *
 *  PXA27x	A0	0x69054110	0x09265013
 *  PXA27x	A1	0x69054111	0x19265013
 *  PXA27x	B0	0x69054112	0x29265013
 *  PXA27x	B1	0x69054113	0x39265013
 *  PXA27x	C0	0x69054114	0x49265013
 *  PXA27x	C5	0x69054117	0x79265013
 *
 *  PXA30x	A0	0x69056880	0x0E648013
 *  PXA30x	A1	0x69056881	0x1E648013
 *  PXA31x	A0	0x69056890	0x0E649013
 *  PXA31x	A1	0x69056891	0x1E649013
 *  PXA31x	A2	0x69056892	0x2E649013
 *  PXA32x	B1	0x69056825	0x5E642013
 *  PXA32x	B2	0x69056826	0x6E642013
 *
 *  PXA930	B0	0x69056835	0x5E643013
 *  PXA930	B1	0x69056837	0x7E643013
 *  PXA930	B2	0x69056838	0x8E643013
 *
 *  PXA935	A0	0x56056931	0x1E653013
 *  PXA935	B0	0x56056936	0x6E653013
 *  PXA935	B1	0x56056938	0x8E653013
 */
#ifdef CONFIG_PXA25x
#define __cpu_is_pxa210(id)				\
	({						\
		unsigned int _id = (id) & 0xf3f0;	\
		_id == 0x2120;				\
	})

#define __cpu_is_pxa250(id)				\
	({						\
		unsigned int _id = (id) & 0xf3ff;	\
		_id <= 0x2105;				\
	})

#define __cpu_is_pxa255(id)				\
	({						\
		unsigned int _id = (id) & 0xffff;	\
		_id == 0x2d06;				\
	})

#define __cpu_is_pxa25x(id)				\
	({						\
		unsigned int _id = (id) & 0xf300;	\
		_id == 0x2100;				\
	})
#else
#define __cpu_is_pxa210(id)	(0)
#define __cpu_is_pxa250(id)	(0)
#define __cpu_is_pxa255(id)	(0)
#define __cpu_is_pxa25x(id)	(0)
#endif

#ifdef CONFIG_PXA27x
#define __cpu_is_pxa27x(id)				\
	({						\
		unsigned int _id = (id) >> 4 & 0xfff;	\
		_id == 0x411;				\
	})
#else
#define __cpu_is_pxa27x(id)	(0)
#endif

#ifdef CONFIG_CPU_PXA300
#define __cpu_is_pxa300(id)				\
	({						\
		unsigned int _id = (id) >> 4 & 0xfff;	\
		_id == 0x688;				\
	 })
#else
#define __cpu_is_pxa300(id)	(0)
#endif

#ifdef CONFIG_CPU_PXA310
#define __cpu_is_pxa310(id)				\
	({						\
		unsigned int _id = (id) >> 4 & 0xfff;	\
		_id == 0x689;				\
	 })
#else
#define __cpu_is_pxa310(id)	(0)
#endif

#ifdef CONFIG_CPU_PXA320
#define __cpu_is_pxa320(id)				\
	({						\
		unsigned int _id = (id) >> 4 & 0xfff;	\
		_id == 0x603 || _id == 0x682;		\
	 })
#else
#define __cpu_is_pxa320(id)	(0)
#endif

#ifdef CONFIG_CPU_PXA930
#define __cpu_is_pxa930(id)				\
	({						\
		unsigned int _id = (id) >> 4 & 0xfff;	\
		_id == 0x683;				\
	 })
#else
#define __cpu_is_pxa930(id)	(0)
#endif

#ifdef CONFIG_CPU_PXA935
#define __cpu_is_pxa935(id)				\
	({						\
		unsigned int _id = (id) >> 4 & 0xfff;	\
		_id == 0x693;				\
	 })
#else
#define __cpu_is_pxa935(id)	(0)
#endif

#define cpu_is_pxa210()					\
	({						\
		__cpu_is_pxa210(read_cpuid_id());	\
	})

#define cpu_is_pxa250()					\
	({						\
		__cpu_is_pxa250(read_cpuid_id());	\
	})

#define cpu_is_pxa255()                                 \
	({                                              \
		__cpu_is_pxa255(read_cpuid_id());       \
	})

#define cpu_is_pxa25x()					\
	({						\
		__cpu_is_pxa25x(read_cpuid_id());	\
	})

#define cpu_is_pxa27x()					\
	({						\
		__cpu_is_pxa27x(read_cpuid_id());	\
	})

#define cpu_is_pxa300()					\
	({						\
		__cpu_is_pxa300(read_cpuid_id());	\
	 })

#define cpu_is_pxa310()					\
	({						\
		__cpu_is_pxa310(read_cpuid_id());	\
	 })

#define cpu_is_pxa320()					\
	({						\
		__cpu_is_pxa320(read_cpuid_id());	\
	 })

#define cpu_is_pxa930()					\
	({						\
		__cpu_is_pxa930(read_cpuid_id());	\
	 })

#define cpu_is_pxa935()					\
	({						\
		__cpu_is_pxa935(read_cpuid_id());	\
	 })



/*
 * CPUID Core Generation Bit
 * <= 0x2 for pxa21x/pxa25x/pxa26x/pxa27x
 */
#if defined(CONFIG_PXA25x) || defined(CONFIG_PXA27x)
#define __cpu_is_pxa2xx(id)				\
	({						\
		unsigned int _id = (id) >> 13 & 0x7;	\
		_id <= 0x2;				\
	 })
#else
#define __cpu_is_pxa2xx(id)	(0)
#endif

#ifdef CONFIG_PXA3xx
#define __cpu_is_pxa3xx(id)				\
	({						\
		__cpu_is_pxa300(id)			\
			|| __cpu_is_pxa310(id)		\
			|| __cpu_is_pxa320(id)		\
			|| __cpu_is_pxa93x(id);		\
	 })
#else
#define __cpu_is_pxa3xx(id)	(0)
#endif

#if defined(CONFIG_CPU_PXA930) || defined(CONFIG_CPU_PXA935)
#define __cpu_is_pxa93x(id)				\
	({						\
		__cpu_is_pxa930(id)			\
			|| __cpu_is_pxa935(id);		\
	 })
#else
#define __cpu_is_pxa93x(id)	(0)
#endif

#define cpu_is_pxa2xx()					\
	({						\
		__cpu_is_pxa2xx(read_cpuid_id());	\
	 })

#define cpu_is_pxa3xx()					\
	({						\
		__cpu_is_pxa3xx(read_cpuid_id());	\
	 })

#define cpu_is_pxa93x()					\
	({						\
		__cpu_is_pxa93x(read_cpuid_id());	\
	 })

#endif
