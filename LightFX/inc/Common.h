#pragma once

#include <memory>
#include <chrono>

#define DECLARE_SMARTPOINTER(_TYPE_)			   \
class _TYPE_;									   \
typedef std::shared_ptr<_TYPE_> _TYPE_##Ptr;	   \
typedef std::weak_ptr<_TYPE_> _TYPE_##WeakPtr;     \
typedef std::unique_ptr<_TYPE_> _TYPE_##UniquePtr;

namespace LightFx
{
    typedef std::chrono::high_resolution_clock high_res_clock;
    typedef std::chrono::high_resolution_clock::time_point time_point;
    typedef std::chrono::high_resolution_clock::duration duration;
    typedef std::chrono::milliseconds milliseconds;
}
