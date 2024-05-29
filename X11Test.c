//compile with:  gcc X11Test.c -lX11
#include	<X11/Xlib.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<stdbool.h>
#include	<string.h>

int main(void)
{
	Display	*d;
	Window	w;
	XEvent	e;
	
	const char	*msg	="Hello, World!";
	int			s;
	
	d	=XOpenDisplay(NULL);
	if(d == NULL)
	{
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}

	s	=DefaultScreen(d);
	w	=XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
			BlackPixel(d, s), WhitePixel(d, s));

	XSelectInput(d, w, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);
	XMapWindow(d, w);
	
	const unsigned int	mask	=ButtonPressMask | ButtonReleaseMask
								| PointerMotionMask | FocusChangeMask;
	
	while(true)
	{
		XNextEvent(d, &e);
		
		if(e.type == Expose)
		{
			XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
			XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
		}
		else if(e.type == KeyPress)
		{
			break;
		}
		else if(e.type == ButtonPress)
		{
			int	res	=XGrabPointer(d, w, false, mask, GrabModeAsync,
						GrabModeAsync, w, None, CurrentTime);
			printf("Grab res: %d\n", res);
		}
		else if(e.type == ButtonRelease)
		{
			int	res	=XUngrabPointer(d, CurrentTime);
			printf("UnGrab res: %d\n", res);
		}
	}
		
	XCloseDisplay(d);

	return	0;
}