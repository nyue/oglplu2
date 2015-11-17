/**
 *  @file oglplus/operations.hpp
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#ifndef OGLPLUS_OPERATIONS_1509260923_HPP
#define OGLPLUS_OPERATIONS_1509260923_HPP

#include "oper/capabilities.hpp"
#include "oper/viewport.hpp"
#include "oper/buffer_masking.hpp"
#include "oper/buffer_clearing.hpp"
#include "oper/prog_var_location.hpp"
#include "oper/stencil_test.hpp"
#include "oper/drawing.hpp"
#include "oper/synchronization.hpp"

#include "oper/object_lifetime.hpp"
#include "vertex_array.hpp"
#include "buffer.hpp"
#include "texture.hpp"
#include "sampler.hpp"
#include "renderbuffer.hpp"
#include "framebuffer.hpp"
#include "shader.hpp"
#include "program.hpp"
#include "program_pipeline.hpp"
#include "transform_feedback.hpp"

#ifdef GL_NV_path_rendering
#include "path_nv.hpp"
#include "path_nv_array.hpp"
#endif

#include "oper/vertex_attrib.hpp"
#include "oper/uniform.hpp"

#ifdef GL_ARB_compatibility
#include "oper/compatibility.hpp"
#endif

namespace oglplus {

class operations
 : public oper::capability_state
 , public oper::viewport_state
 , public oper::buffer_masking_state
 , public oper::buffer_clearing_state
 , public oper::buffer_clearing_ops
 , public oper::stencil_test_state
 , public oper::drawing_ops
 , public oper::synchronization

 , public oper::object_lifetime_ops
 , public oper::vertex_array_ops
 , public oper::buffer_ops
 , public oper::texture_ops
 , public oper::sampler_ops
 , public oper::renderbuffer_ops
 , public oper::framebuffer_ops
 , public oper::shader_ops
 , public oper::program_ops
 , public oper::program_pipeline_ops
 , public oper::transform_feedback_ops

 , public oper::prog_var_location_ops
 , public oper::vertex_attrib_ops
 , public oper::uniform_ops

#ifdef GL_ARB_compatibility
 , public oper::compatibility
#endif
#ifdef GL_NV_path_rendering
 , public oper::path_nv_ops
 , public oper::path_nv_array_ops
#endif
{
public:
	static
	auto bind(vertex_array_name vao)
	noexcept
	{
		return bind_vertex_array(vao);
	}

	static
	auto bind(buffer_target tgt, buffer_name buf)
	noexcept
	{
		return bind_buffer(tgt, buf);
	}

	static
	auto binding(buffer_target tgt)
	noexcept
	{
		return buffer_binding(tgt);
	}

	static
	auto bind(texture_unit unit, sampler_name sam)
	noexcept
	{
		return bind_sampler(unit, sam);
	}

	static
	auto bind(texture_target tgt, texture_name tex)
	noexcept
	{
		return bind_texture(tgt, tex);
	}

	static
	auto binding(texture_target tgt)
	noexcept
	{
		return texture_binding(tgt);
	}

	static
	auto bind(framebuffer_target tgt, framebuffer_name fbo)
	noexcept
	{
		return bind_framebuffer(tgt, fbo);
	}

	static
	auto binding(framebuffer_target tgt)
	noexcept
	{
		return framebuffer_binding(tgt);
	}

	static
	auto bind(renderbuffer_target tgt, renderbuffer_name rbo)
	noexcept
	{
		return bind_renderbuffer(tgt, rbo);
	}

	static
	auto binding(renderbuffer_target tgt)
	noexcept
	{
		return renderbuffer_binding(tgt);
	}

	static
	auto bind(program_pipeline_name ppo)
	noexcept
	{
		return bind_program_pipeline(ppo);
	}

	static
	auto bind(transform_feedback_target tgt, transform_feedback_name xfb)
	noexcept
	{
		return bind_transform_feedback(tgt, xfb);
	}

	static
	auto binding(transform_feedback_target tgt)
	noexcept
	{
		return transform_feedback_binding(tgt);
	}

	static
	auto use(program_name prg)
	noexcept
	{
		return use_program(prg);
	}
};

} // namespace oglplus

#endif // include guard
