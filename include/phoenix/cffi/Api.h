// Copyright © 2023. Luis Michaelis <me@lmichaelis.de>
// SPDX-License-Identifier: MIT-Modern-Variant
#pragma once
#include <stdint.h>

#ifdef __EMSCRIPTEN__
	#include <emscripten/emscripten.h>
	#define PXC_PRELUDE EMSCRIPTEN_KEEPALIVE
#else
	#define PXC_PRELUDE
#endif

#ifdef __cplusplus
	#define PXC_EXTERN extern "C" PXC_PRELUDE
#else
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
} PxVec4;

typedef struct {
	float x, y, z, w;
} PxQuat;

typedef struct {
	/// \note Column major column order!
	float m00;
	float m01;
	float m02;
	float m10;
	float m11;
	float m12;
	float m20;
	float m21;
	float m22;
} PxMat3x3;

typedef struct {
	float m00;
	float m01;
	float m02;
	float m03;
	float m10;
	float m11;
	float m12;
	float m13;
	float m20;
	float m21;
	float m22;
	float m23;
	float m30;
	float m31;
	float m32;
	float m33;
} PxMat4x4;

typedef struct {
	uint8_t r, g, b, a;
} PxColor;

typedef struct {
	PxVec3 min, max;
} PxAABB;

typedef int PxBool;
