/**************************************************************************
 *
 * Copyright 2013-2014 RAD Game Tools and Valve Software
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/

// File: vogl_query_state.h
#ifndef VOGL_QUERY_STATE_H
#define VOGL_QUERY_STATE_H

#include "vogl_dynamic_string.h"
#include "vogl_json.h"
#include "vogl_map.h"

#include "vogl_common.h"
#include "vogl_general_context_state.h"
#include "vogl_blob_manager.h"

class vogl_query_state : public vogl_gl_object_state
{
public:
    vogl_query_state();
    virtual ~vogl_query_state();

    virtual vogl_gl_object_state_type get_type() const
    {
        return cGLSTQuery;
    }
    virtual vogl_namespace_t get_handle_namespace() const
    {
        return VOGL_NAMESPACE_QUERIES;
    }

    // Target must be supplied by the caller, we can't determine it via normal GL calls.
    virtual bool snapshot(const vogl_context_info &context_info, vogl_handle_remapper &remapper, GLuint64 handle, GLenum target);

    // restore() tries to restore the previously bound query on target, but it must begin/end it to do so.
    virtual bool restore(const vogl_context_info &context_info, vogl_handle_remapper &remapper, GLuint64 &handle) const;

    virtual bool remap_handles(vogl_handle_remapper &remapper);

    virtual void clear();

    virtual bool serialize(json_node &node, vogl_blob_manager &blob_manager) const;
    virtual bool deserialize(const json_node &node, const vogl_blob_manager &blob_manager);

    virtual GLuint64 get_snapshot_handle() const
    {
        return m_snapshot_handle;
    }

    virtual bool compare_restorable_state(const vogl_gl_object_state &rhs) const;

    GLenum get_target() const
    {
        return m_target;
    }

    int64_t get_prev_result() const
    {
        return m_prev_result;
    }

    virtual bool is_valid() const
    {
        return m_is_valid;
    }

private:
    GLuint m_snapshot_handle;

    GLuint m_target;

    int64_t m_prev_result;
    GLenum m_get_result_status;

    bool m_has_been_begun;

    bool m_is_valid;
};

namespace vogl
{
    VOGL_DEFINE_BITWISE_MOVABLE(vogl_query_state);
}

#endif // VOGL_QUERY_STATE_H
