#pragma once

#define GEOMETRY_SCRIPT_VER "v1.0.0"
#ifdef _PROD
#define GEOMETRY_SCRIPT_ID "prod"
#elif _BETA
#define GEOMETRY_SCRIPT_ID "beta"
#elif _DEV
#define GEOMETRY_SCRIPT_ID "dev"
#else
#define GEOMETRY_SCRIPT_ID "local"
#endif