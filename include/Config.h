#pragma once
#include "PrismaUI_API.h"

extern PRISMA_UI_API::IVPrismaUI1* PrismaUI;
extern bool g_uiVisible;
extern PrismaView g_view;

void InGameLog(const char* msg);