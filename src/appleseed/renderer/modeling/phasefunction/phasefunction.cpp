
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2017 Artem Bishev, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// Interface header.
#include "phasefunction.h"

// appleseed.renderer headers.
#include "renderer/kernel/shading/shadingcontext.h"
#include "renderer/kernel/shading/shadingray.h"
#include "renderer/modeling/input/inputarray.h"

// appleseed.foundation headers.
#include "foundation/utility/arena.h"

using namespace foundation;

namespace renderer
{

//
// PhaseFunction class implementation.
//

namespace
{
    const UniqueID g_class_uid = new_guid();
}

UniqueID PhaseFunction::get_class_uid()
{
    return g_class_uid;
}

PhaseFunction::PhaseFunction(
    const char*             name,
    const ParamArray&       params)
      : ConnectableEntity(g_class_uid, params)
{
    set_name(name);
}

size_t PhaseFunction::compute_input_data_size() const
{
    return get_inputs().compute_data_size();
}

void* PhaseFunction::evaluate_inputs(
    const ShadingContext&   shading_context,
    const ShadingRay&       volume_ray) const
{
    void* data = shading_context.get_arena().allocate(compute_input_data_size());

    get_inputs().evaluate_uniforms(data);

    return data;
}

void PhaseFunction::prepare_inputs(
    foundation::Arena&          arena,
    const ShadingRay&           volume_ray,
    void*                       data) const
{
}

}   // namespace renderer
