/*
 * Copyright © 2015 Collabora, Ltd.
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

#include "config.h"

#include <stdio.h>
#include <string.h>

#include "weston-test-client-helper.h"
#include "ivi-application-client-protocol.h"
#include "ivi-test.h"

struct runner {
	struct client *client;
	struct weston_test_runner *test_runner;
	int done;
};

static void
runner_finished_handler(void *data, struct weston_test_runner *test_runner)
{
	struct runner *runner = data;

	runner->done = 1;
}

static const struct weston_test_runner_listener test_runner_listener = {
	runner_finished_handler
};

static struct runner *
client_create_runner(struct client *client)
{
	struct runner *runner;
	struct global *g;
	struct global *global_runner = NULL;

	runner = xzalloc(sizeof(*runner));
	runner->client = client;

	wl_list_for_each(g, &client->global_list, link) {
		if (strcmp(g->interface, "weston_test_runner"))
			continue;

		if (global_runner)
			assert(0 && "multiple weston_test_runner objects");

		global_runner = g;
	}

	assert(global_runner && "no weston_test_runner found");
	assert(global_runner->version == 1);

	runner->test_runner = wl_registry_bind(client->wl_registry,
					       global_runner->name,
					       &weston_test_runner_interface,
					       1);
	assert(runner->test_runner);

	weston_test_runner_add_listener(runner->test_runner,
					&test_runner_listener, runner);

	return runner;
}

static void
runner_destroy(struct runner *runner)
{
	weston_test_runner_destroy(runner->test_runner);
	client_roundtrip(runner->client);
	free(runner);
}

static void
runner_run(struct runner *runner, const char *test_name)
{
	fprintf(stderr, "weston_test_runner.run(\"%s\")\n", test_name);

	runner->done = 0;
	weston_test_runner_run(runner->test_runner, test_name);

	while (!runner->done) {
		if (wl_display_dispatch(runner->client->wl_display) < 0)
			assert(0 && "runner wait");
	}
}

static struct ivi_application *
get_ivi_application(struct client *client)
{
	struct global *g;
	struct global *global_iviapp = NULL;
	static struct ivi_application *iviapp;

	if (iviapp)
		return iviapp;

	wl_list_for_each(g, &client->global_list, link) {
		if (strcmp(g->interface, "ivi_application"))
			continue;

		if (global_iviapp)
			assert(0 && "multiple ivi_application objects");

		global_iviapp = g;
	}

	assert(global_iviapp && "no ivi_application found");

	assert(global_iviapp->version == 1);

	iviapp = wl_registry_bind(client->wl_registry, global_iviapp->name,
				  &ivi_application_interface, 1);
	assert(iviapp);

	return iviapp;
}

struct ivi_window {
	struct wl_surface *wl_surface;
	struct ivi_surface *ivi_surface;
	uint32_t ivi_id;
};

static struct ivi_window *
client_create_ivi_window(struct client *client, uint32_t ivi_id)
{
	struct ivi_application *iviapp;
	struct ivi_window *wnd;

	iviapp = get_ivi_application(client);

	wnd = xzalloc(sizeof(*wnd));
	wnd->wl_surface = wl_compositor_create_surface(client->wl_compositor);
	wnd->ivi_surface = ivi_application_surface_create(iviapp, ivi_id,
							  wnd->wl_surface, "layout-test");
	wnd->ivi_id = ivi_id;

	return wnd;
}

static void
ivi_window_destroy(struct ivi_window *wnd)
{
	ivi_surface_destroy(wnd->ivi_surface);
	wl_surface_destroy(wnd->wl_surface);
	free(wnd);
}

/******************************** tests ********************************/

/*
 * This is a test program, launched by ivi_layout-test-plugin.c. Each TEST()
 * is forked and exec'd as usual with the weston-test-runner framework.
 *
 * These tests make use of weston_test_runner global interface exposed by
 * ivi_layout-test-plugin.c. This allows these tests to trigger compositor-side
 * checks.
 *
 * See ivi_layout-test-plugin.c for further details.
 */

/**
 * RUNNER_TEST() names are defined in ivi_layout-test-plugin.c.
 * Each RUNNER_TEST name listed here uses the same simple initial client setup.
 */
const char * const basic_test_names[] = {
	"surface_visibility",
	"surface_opacity",
};

TEST_P(ivi_layout_runner, basic_test_names)
{
	/* an element from basic_test_names */
	const char * const *test_name = data;
	struct client *client;
	struct runner *runner;
	struct ivi_window *wnd;

	client = create_client();
	runner = client_create_runner(client);

	wnd = client_create_ivi_window(client, IVI_TEST_SURFACE_ID(0));

	runner_run(runner, *test_name);

	ivi_window_destroy(wnd);
	runner_destroy(runner);
}

TEST(ivi_layout_surface_create)
{
	struct client *client;
	struct runner *runner;
	struct ivi_window *winds[2];

	client = create_client();
	runner = client_create_runner(client);

	winds[0] = client_create_ivi_window(client, IVI_TEST_SURFACE_ID(0));
	winds[1] = client_create_ivi_window(client, IVI_TEST_SURFACE_ID(1));

	runner_run(runner, "surface_create_p1");

	ivi_window_destroy(winds[0]);

	runner_run(runner, "surface_create_p2");

	ivi_window_destroy(winds[1]);
	runner_destroy(runner);
}
