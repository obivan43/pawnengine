#pragma once

#define UNUSED(x) ((void)(x));

#define FROM_VOIDP(type, data) (*(static_cast<type*>(data)))