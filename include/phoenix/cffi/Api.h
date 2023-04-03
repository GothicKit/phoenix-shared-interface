// Copyright © 2023. Luis Michaelis <me@lmichaelis.de>
// SPDX-License-Identifier: MIT-Modern-Variant
#pragma once

#ifdef __cplusplus
	#define PXC_EXPORT extern "C"
#else
	#include <stdbool.h>
	#define PXC_EXPORT
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
	#ifdef PXC_EXPORTS
		#ifdef __GNUC__
			#define PXC_API __attribute__((dllexport)) PXC_EXPORT
		#else
			#define PXC_API __declspec(dllexport) PXC_EXPORT
		#endif
	#else
		#ifdef __GNUC__
			#define PXC_API __attribute__((dllimport)) PXC_EXPORT
		#else
			#define PXC_API __declspec(dllimport) PXC_EXPORT
		#endif
	#endif
	#define PXC_INTERNAL
#else
	#define PXC_API __attribute__((visibility("default"))) PXC_EXPORT
	#define PXC_INTERNAL __attribute__((visibility("hidden"))) PXC_EXPORT
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