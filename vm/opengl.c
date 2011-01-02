/* Copyright (C) 2009, Chris Double.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License, version 2.1
 * as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "waspvm.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <GL/gl.h>
#include <GL/glx.h>

void wasp_init_opengl_subsystem( );

WASP_BEGIN_TYPE( display )
    Display* display;
WASP_END_TYPE( display )
#define REQ_DISPLAY_ARG( vn ) REQ_TYPED_ARG( vn, display )
#define DISPLAY_RESULT( vn ) TYPED_RESULT( vn, display )
#define OPT_DISPLAY_ARG( vn ) OPT_TYPED_ARG( vn, display )

wasp_display wasp_make_display( );

WASP_BEGIN_SUBTYPE( input, display_service )
    struct event event;
    wasp_display display;
WASP_END_SUBTYPE( display_service )
#define REQ_DISPLAY_SERVICE_ARG( x ) REQ_TYPED_ARG( x, display_service )
#define OPT_DISPLAY_SERVICE_ARG( x ) OPT_TYPED_ARG( x, display_service )
#define DISPLAY_SERVICE_RESULT( x )  TYPED_RESULT( display_service, x )

wasp_display_service wasp_make_display_service( wasp_display display );

WASP_BEGIN_TYPE( window )
  wasp_display display;
  Window window;
  XVisualInfo* visual_info;
  GLXContext context;
  Colormap color_map;
  Atom protocols;
  int mapped;
  int configured;
  int width;
  int height;
  int x;
  int y;
WASP_END_TYPE( window )
#define REQ_WINDOW_ARG( vn ) REQ_TYPED_ARG( vn, window )
#define WINDOW_RESULT( vn ) TYPED_RESULT( vn, window )
#define OPT_WINDOW_ARG( vn ) OPT_TYPED_ARG( vn, window )

wasp_window wasp_make_window( wasp_display display, wasp_string title,
                              wasp_integer x, wasp_integer y,
                              wasp_integer width, wasp_integer height );

void wasp_display_cb( int handle, short event, void* service ){
    printf("wasp_display_cb\n");
    wasp_unroot_obj( (wasp_object) service );
    wasp_disable_os_loop( );

    // Pass event?
    wasp_wake_monitor( (wasp_input)service, wasp_vf_integer( 1 ) );
}

int wasp_display_recv_mt( wasp_display_service svc, wasp_value* data ){
    printf("wasp_display_recv_mt\n");
    wasp_root_obj( (wasp_object) svc );
    printf("a\n");
    wasp_enable_os_loop( );
    printf("b\n");
    event_add( &( svc->event ), NULL );
    printf("c\n");
    return 0;
}

wasp_display_service wasp_make_display_service( wasp_display display ){
    wasp_display_service svc = WASP_OBJALLOC( display_service );

    svc->display = display;
    ((wasp_input)svc)->recv = (wasp_input_mt)wasp_display_recv_mt;
    event_set( &( svc->event ), ConnectionNumber( display->display ), EV_READ, wasp_display_cb, (void*)svc );
    return svc;
}

void wasp_trace_display_service ( wasp_display_service svc ){
    printf("tracing display_service\n");
    wasp_grey_obj( (wasp_object) svc->display );
    wasp_trace_input( (wasp_input)svc );
}

void wasp_free_display_service( wasp_display_service svc ){
    printf("freeing display_service\n");
    event_del( &(svc->event) );
    wasp_objfree( (wasp_object)svc );
}

WASP_GENERIC_COMPARE( display_service );
WASP_GENERIC_FORMAT( display_service );
//WASP_C_TYPE( display_service );
WASP_C_SUBTYPE2( display_service, "display-service", input );

wasp_display wasp_make_display( ){
    wasp_display display = WASP_OBJALLOC( display );

    display->display = XOpenDisplay( NULL );
    return display;
}

wasp_window wasp_create_window( wasp_display display, wasp_string title,
                                wasp_integer x, wasp_integer y,
                                wasp_integer width, wasp_integer height ){
    wasp_window w = WASP_OBJALLOC( window );
    w->display = display;
    w->window = 0;
    w->visual_info = 0;
    w->mapped = 0;
    w->configured = 0;
    w->width = width;
    w->height = height;
    w->x = x;
    w->y = y;
    return w;
}

void wasp_free_display( wasp_display display ){
    printf("free display\n");
#if 0
    if ( wasp_input_monitored( (wasp_input) display->service ) ){
        wasp_unroot_obj( (wasp_object) display->service );
        wasp_disable_os_loop( );
        wasp_wake_monitor( (wasp_input)display->service, wasp_vf_symbol( wasp_ss_close ) );
    }
#endif
    XCloseDisplay( display->display );
    wasp_objfree( display );
}

void wasp_trace_display ( wasp_display display ){
    printf("tracing display\n");
}

WASP_GENERIC_COMPARE( display );
WASP_GENERIC_FORMAT( display );
WASP_C_TYPE( display );

WASP_BEGIN_PRIM( "open-display", open_display )
    NO_REST_ARGS( );

    RESULT( wasp_vf_display( wasp_make_display( ) ) );
WASP_END_PRIM( open_display )

WASP_BEGIN_PRIM( "display-service", display_service )
    REQ_DISPLAY_ARG( d );
    NO_REST_ARGS( );

    DISPLAY_SERVICE_RESULT( wasp_make_display_service( d ) );
WASP_END_PRIM( display_service )

WASP_BEGIN_PRIM( "display-events-pending", display_events_pending )
    REQ_DISPLAY_ARG( d );
    NO_REST_ARGS( );

    RESULT( wasp_vf_integer( XPending ( d->display ) ) );
WASP_END_PRIM( display_events_pending )

void wasp_trace_window ( wasp_window w ){
    wasp_grey_obj( (wasp_object) w->display );
}

WASP_GENERIC_FREE( window );
WASP_GENERIC_COMPARE( window );
WASP_GENERIC_FORMAT( window );
WASP_C_TYPE( window );

WASP_BEGIN_PRIM( "create-window", create_window )
    REQ_DISPLAY_ARG( d );
    REQ_STRING_ARG( title );
    REQ_INTEGER_ARG( x );
    REQ_INTEGER_ARG( y );
    REQ_INTEGER_ARG( width );
    REQ_INTEGER_ARG( height );
    NO_REST_ARGS( );

    Display* display = d->display;
    XSizeHints hints;
    XSetWindowAttributes swa;
    int attributes[] = {
        GLX_DOUBLEBUFFER,
        GLX_RGBA,
        0
    };
    wasp_window w = wasp_create_window( d, title, x, y, width, height );
    w->visual_info = glXChooseVisual(display, DefaultScreen(display), attributes);
    if(!w->visual_info)
    {
        wasp_errf(wasp_es_vm, "s", "Could not get GLX visual");
    }

    w->context = glXCreateContext(display, w->visual_info, NULL, GL_TRUE);
    if(!w->context)
    {
        wasp_errf(wasp_es_vm, "s", "Could not create GLX context");
    }

    w->color_map =
        XCreateColormap(display,
                        RootWindow(display, w->visual_info->screen),
                        w->visual_info->visual,
                        AllocNone);

    hints.x = x;
    hints.y = y;
    hints.width = width;
    hints.height = height;
    hints.flags = PPosition | PSize;

    swa.colormap = w->color_map;
    swa.border_pixel = 0;
    swa.event_mask =
        KeyPressMask |
        KeyReleaseMask |
        ExposureMask |
        ButtonPressMask |
        ButtonReleaseMask |
        StructureNotifyMask |
        FocusChangeMask |
        PointerMotionMask;

    w->window =
        XCreateWindow(display,
                      RootWindow(display, w->visual_info->screen),
                      hints.x, hints.y, hints.width, hints.height,
                      0, w->visual_info->depth, InputOutput, w->visual_info->visual,
                      CWBorderPixel | CWColormap | CWEventMask, &swa);
    XSetStandardProperties(display,
                           w->window,
                           wasp_sf_string( title ),
                           wasp_sf_string( title ),
                           None,
                           NULL,
                           0,
                           &hints);
    w->protocols = XInternAtom(display, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(display, w->window, &w->protocols, 1);
    XMapWindow(display, w->window);

    RESULT( wasp_vf_window( w ) );
WASP_END_PRIM( create_window )

WASP_BEGIN_PRIM( "close-window", close_window )
    REQ_WINDOW_ARG( w );
    NO_REST_ARGS( );

    XUnmapWindow( w->display->display, w->window );
    RESULT( wasp_vf_window( w ) );
WASP_END_PRIM( close_window )

WASP_BEGIN_PRIM( "window-handle", window_handle )
    REQ_WINDOW_ARG( w );
    NO_REST_ARGS( );

    wasp_quad q = (wasp_quad)w->window;
    RESULT( wasp_vf_integer( q ) );
WASP_END_PRIM( window_handle )

WASP_BEGIN_TYPE( event )
  wasp_integer type;
  Window window;
WASP_END_TYPE( event )
#define REQ_EVENT_ARG( vn ) REQ_TYPED_ARG( vn, event )
#define EVENT_RESULT( vn ) TYPED_RESULT( vn, event )
#define OPT_EVENT_ARG( vn ) OPT_TYPED_ARG( vn, event )

WASP_GENERIC_TRACE( event );
WASP_GENERIC_FREE( event );
WASP_GENERIC_COMPARE( event );
WASP_GENERIC_FORMAT( event );
WASP_C_TYPE( event );

WASP_BEGIN_PRIM( "event-type", event_type )
    REQ_EVENT_ARG( e );
    NO_REST_ARGS( );

    wasp_quad q = (wasp_quad)e->type;
    RESULT( wasp_vf_integer( q ) );
WASP_END_PRIM( event_type )

WASP_BEGIN_PRIM( "event-window-handle", event_window_handle )
    REQ_EVENT_ARG( e );
    NO_REST_ARGS( );

    wasp_quad q = (wasp_quad)e->window;
    RESULT( wasp_vf_integer( q ) );
WASP_END_PRIM( event_window_handle )

WASP_BEGIN_PRIM( "display-next-event", display_next_event )
    REQ_DISPLAY_ARG( d );
    NO_REST_ARGS( );

    XEvent event;
    wasp_event e = WASP_OBJALLOC( event );
    XNextEvent( d->display, &event );
    e->type = event.xany.type;
    e->window = event.xany.window;
    RESULT( wasp_vf_event( e ) );
WASP_END_PRIM( display_next_event )

void wasp_init_opengl_subsystem( ){
    WASP_I_TYPE( display );
    WASP_I_SUBTYPE( display_service, input );
    WASP_I_TYPE( window );
    WASP_I_TYPE( event );

    WASP_BIND_PRIM( open_display );
    WASP_BIND_PRIM( display_service );
    WASP_BIND_PRIM( display_events_pending );
    WASP_BIND_PRIM( display_next_event );
    WASP_BIND_PRIM( create_window );
    WASP_BIND_PRIM( window_handle );
    WASP_BIND_PRIM( close_window );
    WASP_BIND_PRIM( event_type );
    WASP_BIND_PRIM( event_window_handle );
}
