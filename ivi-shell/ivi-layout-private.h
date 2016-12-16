/*
 * Copyright (C) 2014 DENSO CORPORATION
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of the copyright holders not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.  The copyright holders make
 * no representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
 * CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _ivi_layout_PRIVATE_H_
#define _ivi_layout_PRIVATE_H_

#include "compositor.h"
#include "ivi-layout-export.h"

struct ivi_layout_surface {
	struct wl_list link;
	struct wl_signal property_changed;
	struct wl_list layer_list;
	int32_t update_count;
	uint32_t id_surface;
	const char *window_title;
	uint32_t zorder;

	struct ivi_layout *layout;
	struct weston_surface *surface;

	struct wl_listener surface_destroy_listener;
	struct weston_transform surface_rotation;
	struct weston_transform layer_rotation;
	struct weston_transform surface_pos;
	struct weston_transform layer_pos;
	struct weston_transform scaling;

	struct ivi_layout_surface_properties prop;
	uint32_t event_mask;

	struct {
		struct ivi_layout_surface_properties prop;
		struct wl_list link;
	} pending;

	struct {
		struct wl_list link;
		struct wl_list layer_list;
	} order;

	struct {
		ivi_controller_surface_content_callback callback;
		void *userdata;
	} content_observer;

	struct wl_signal configured;
};

struct ivi_layout_layer {
	struct wl_list link;
	struct wl_signal property_changed;
	struct wl_list screen_list;
	struct wl_list link_to_surface;
	uint32_t id_layer;

	struct ivi_layout *layout;

	struct ivi_layout_layer_properties prop;
	uint32_t event_mask;

	struct {
		struct ivi_layout_layer_properties prop;
		struct wl_list surface_list;
		struct wl_list link;
	} pending;

	struct {
		struct wl_list surface_list;
		struct wl_list link;
	} order;
};

struct ivi_layout {
	struct weston_compositor *compositor;

	struct wl_list surface_list;
	struct wl_list layer_list;
	struct wl_list screen_list;

	struct {
		struct wl_signal created;
		struct wl_signal removed;
	} layer_notification;

	struct {
		struct wl_signal created;
		struct wl_signal removed;
		struct wl_signal configure_changed;
	} surface_notification;

	struct weston_layer layout_layer;
	struct wl_signal warning_signal;

	struct ivi_layout_transition_set *transitions;
	struct wl_list pending_transition_list;
};

struct ivi_layout *get_instance(void);

struct ivi_layout_transition;

struct ivi_layout_transition_set {
	struct wl_event_source  *event_source;
	struct wl_list          transition_list;
};

typedef void (*ivi_layout_transition_destroy_user_func)(void *user_data);

struct ivi_layout_transition_set *
ivi_layout_transition_set_create(struct weston_compositor *ec);

void
ivi_layout_transition_move_resize_view(struct ivi_layout_surface *surface,
				       int32_t dest_x, int32_t dest_y,
				       int32_t dest_width, int32_t dest_height,
				       uint32_t duration);

void
ivi_layout_transition_visibility_on(struct ivi_layout_surface *surface,
				    uint32_t duration);

void
ivi_layout_transition_visibility_off(struct ivi_layout_surface *surface,
				     uint32_t duration);


void
ivi_layout_transition_move_layer(struct ivi_layout_layer *layer,
				 int32_t dest_x, int32_t dest_y,
				 uint32_t duration);

void
ivi_layout_transition_fade_layer(struct ivi_layout_layer *layer,
				 uint32_t is_fade_in,
				 double start_alpha, double end_alpha,
				 void *user_data,
				 ivi_layout_transition_destroy_user_func destroy_func,
				 uint32_t duration);

int32_t
is_surface_transition(struct ivi_layout_surface *surface);

/**
 * methods of interaction between ivi-shell with ivi-layout
 */
struct weston_view *
ivi_layout_get_weston_view(struct ivi_layout_surface *surface);
void
ivi_layout_surface_configure(struct ivi_layout_surface *ivisurf,
			     int32_t width, int32_t height);
struct ivi_layout_surface*
ivi_layout_surface_create(struct weston_surface *wl_surface,
			  uint32_t id_surface, const char *window_title, uint32_t zorder);
void
ivi_layout_init_with_compositor(struct weston_compositor *ec);
int32_t
ivi_layout_surface_get_dimension(struct ivi_layout_surface *ivisurf,
				 int32_t *dest_width, int32_t *dest_height);
void
ivi_layout_surface_add_configured_listener(struct ivi_layout_surface* ivisurf,
					   struct wl_listener* listener);
/**
 * methods of interaction between transition animation with ivi-layout
 */
int32_t
ivi_layout_commit_changes(void);
uint32_t
ivi_layout_get_id_of_surface(struct ivi_layout_surface *ivisurf);
int32_t
ivi_layout_surface_set_destination_rectangle(struct ivi_layout_surface *ivisurf,
					     int32_t x, int32_t y,
					     int32_t width, int32_t height);
int32_t
ivi_layout_surface_set_opacity(struct ivi_layout_surface *ivisurf,
			       wl_fixed_t opacity);
wl_fixed_t
ivi_layout_surface_get_opacity(struct ivi_layout_surface *ivisurf);
int32_t
ivi_layout_surface_set_visibility(struct ivi_layout_surface *ivisurf,
				  bool newVisibility);
bool
ivi_layout_surface_get_visibility(struct ivi_layout_surface *ivisurf);
struct ivi_layout_surface *
ivi_layout_get_surface_from_id(uint32_t id_surface);
int32_t
ivi_layout_layer_set_opacity(struct ivi_layout_layer *ivilayer,
			     wl_fixed_t opacity);
wl_fixed_t
ivi_layout_layer_get_opacity(struct ivi_layout_layer *ivilayer);
int32_t
ivi_layout_layer_set_visibility(struct ivi_layout_layer *ivilayer,
				bool newVisibility);
int32_t
ivi_layout_layer_set_position(struct ivi_layout_layer *ivilayer,
			      int32_t dest_x, int32_t dest_y);
int32_t
ivi_layout_layer_get_position(struct ivi_layout_layer *ivilayer,
			      int32_t *dest_x, int32_t *dest_y);
int32_t
ivi_layout_layer_set_render_order(struct ivi_layout_layer *ivilayer,
				  struct ivi_layout_surface **pSurface,
				  int32_t number);
void
ivi_layout_transition_move_layer_cancel(struct ivi_layout_layer *layer);
int
load_controller_modules(struct weston_compositor *compositor, const char *modules,
			int *argc, char *argv[]);
#endif
