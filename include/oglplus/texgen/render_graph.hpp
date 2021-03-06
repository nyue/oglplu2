/**
 *  @file oglplus/texgen/render_graph.hpp
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#ifndef OGLPLUS_TEXGEN_RENDER_GRAPH_1509260923_HPP
#define OGLPLUS_TEXGEN_RENDER_GRAPH_1509260923_HPP

#include "render_node.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace oglplus {
namespace texgen {

template <typename Node>
class render_graph_node : public Node {
public:
    using Node::Node;

    // TODO throw connect error
    render_graph_node<Node>& connect(
      const cstr_ref& inp_name, output_intf& out) {
	if(auto inp = this->input_by_name(inp_name)) {
	    connect_output_to_input(out, inp);
	}
	return *this;
    }

    render_graph_node<Node>& connect(
      const cstr_ref& inp_name, node_intf& out_node, span_size_t oidx) {
	if(oidx < out_node.output_count()) {
	    return connect(inp_name, out_node.output(oidx));
	}
	return *this;
    }

    render_graph_node<Node>& connect(
      const cstr_ref& inp_name, node_intf& out_node) {
	return connect(inp_name, out_node, 0);
    }

    render_graph_node<Node>& connect(span_size_t iidx, output_intf& out) {
	if(iidx < this->input_count()) {
	    connect_output_to_input(out, this->input(iidx));
	}
	return *this;
    }

    render_graph_node<Node>& connect(
      span_size_t iidx, node_intf& out_node, span_size_t oidx) {
	if(oidx < out_node.output_count()) {
	    return connect(iidx, out_node.output(oidx));
	}
	return *this;
    }

    render_graph_node<Node>& connect(span_size_t iidx, node_intf& out_node) {
	return connect(iidx, out_node, 0);
    }

    render_graph_node<Node>& connect(output_intf& out) {
	return connect(0, out);
    }

    render_graph_node<Node>& connect(node_intf& out_node) {
	return connect(0, out_node);
    }
};

class render_graph {
private:
    typedef std::unique_ptr<node_intf> _node_ptr_t;
    std::vector<_node_ptr_t> _anon_nodes;
    std::map<std::string, _node_ptr_t> _nodes;
    std::unique_ptr<render_node> _render_node;

public:
    render_graph(void);
    ~render_graph(void);

    void disconnect_all(void);

    void add_anonymous_node(std::unique_ptr<node_intf>&&);

    void add_node(std::string name, std::unique_ptr<node_intf>&&);

    template <typename NodeType, typename... P>
    render_graph_node<NodeType>& add_new_anon(P&&... p) {
	render_graph_node<NodeType>* ptr =
	  new render_graph_node<NodeType>(std::forward<P>(p)...);
	assert(ptr);
	add_anonymous_node(_node_ptr_t(ptr));
	return *ptr;
    }

    template <typename NodeType, typename... P>
    render_graph_node<NodeType>& add_new(std::string name, P&&... p) {
	render_graph_node<NodeType>* ptr =
	  new render_graph_node<NodeType>(std::forward<P>(p)...);
	assert(ptr);
	add_node(std::move(name), _node_ptr_t(ptr));
	return *ptr;
    }

    render_node& renderer(void);

    void set_dimensions(
      eagine::valid_if_positive<int> w, eagine::valid_if_positive<int> h);

    void render(void);

    // find node
    eagine::optional_reference_wrapper<node_intf> find_node(
      const std::string& node_name);

    // find input / output
    eagine::optional_reference_wrapper<input_intf> find_node_input(
      node_intf& node, span_size_t index);

    eagine::optional_reference_wrapper<output_intf> find_node_output(
      node_intf& node, span_size_t index);

    eagine::optional_reference_wrapper<input_intf> find_node_input(
      node_intf& node, const cstr_ref& iname);

    eagine::optional_reference_wrapper<output_intf> find_node_output(
      node_intf& node, const cstr_ref& oname);

    eagine::optional_reference_wrapper<input_intf> find_node_input(
      const std::string& node_name, span_size_t index);

    eagine::optional_reference_wrapper<output_intf> find_node_output(
      const std::string& node_name, span_size_t index);

    eagine::optional_reference_wrapper<input_intf> find_node_input(
      const std::string& node_name, const cstr_ref& iname);

    eagine::optional_reference_wrapper<output_intf> find_node_output(
      const std::string& node_name, const cstr_ref& oname);

    // connect to renderer
    bool connect_to_renderer(output_intf& output);

    bool connect_to_renderer(node_intf&, span_size_t index = 0);

    bool connect_to_renderer(const std::string& node_name, span_size_t index);

    bool connect_to_renderer(const std::string& node_name) {
	return connect_to_renderer(node_name, 0);
    }

    // connect
    bool connect(output_intf& out, input_intf& inp);

    bool connect(node_intf& output_node,
      span_size_t oindex,
      node_intf& input_node,
      span_size_t iindex);

    bool connect(node_intf& output_node,
      const cstr_ref& oname,
      node_intf& input_node,
      const cstr_ref& iname);

    bool connect(
      node_intf& output_node, node_intf& input_node, const cstr_ref& iname);

    bool connect(const std::string& output_node_name,
      span_size_t oindex,
      const std::string& input_node_name,
      span_size_t iindex);

    bool connect(const std::string& output_node_name,
      const std::string& input_node_name,
      span_size_t iindex);

    bool connect(const std::string& output_node_name,
      const cstr_ref& oname,
      const std::string& input_node_name,
      const cstr_ref& iname);

    bool connect(const std::string& output_node_name,
      const std::string& input_node_name,
      const cstr_ref& iname);

    bool connect(
      const std::string& output_node_name, const std::string& input_node_name);

    bool finalize(void);
};

} // namespace texgen
} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/render_graph.inl>
#endif

#endif // include guard
