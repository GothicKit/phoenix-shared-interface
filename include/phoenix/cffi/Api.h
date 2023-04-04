// Copyright © 2023. Luis Michaelis <me@lmichaelis.de>
// SPDX-License-Identifier: MIT-Modern-Variant
#pragma once

#ifdef __cplusplus
	#define PXC_EXTERN extern "C"
#else
	#include <stdbool.h>
	#define PXC_EXTERN
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
	#ifdef PXC_EXPORTS
		#ifdef __GNUC__
			#define PXC_API PXC_EXTERN __attribute__((dllexport))
		#else
			#define PXC_API PXC_EXTERN __declspec(dllexport)
		#endif
	#else
		#ifdef __GNUC__
			#define PXC_API PXC_EXTERN __attribute__((dllimport))
		#else
			#define PXC_API PXC_EXTERN __declspec(dllimport)
		#endif
	#endif
	#define PXC_INTERNAL
#else
	#define PXC_API PXC_EXTERN __attribute__((visibility("default")))
	#define PXC_INTERNAL PXC_EXTERN __attribute__((visibility("hidden")))
#endif

typedef struct {
	float x, y;
} PxVec2;

typedef struct {
	float x, y, z;
} PxVec3;

typedef struct {
	float x, y, z, w;
} PxQuat;

typedef struct {
	PxVec3 min, max;
} PxAABB;

typedef bool PxBool;