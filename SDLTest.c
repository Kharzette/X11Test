#include	<SDL3/SDL.h>
#include	<SDL3/SDL_vulkan.h>
#include	<stdio.h>
#include	<stdbool.h>

void main(void)
{
	int	res	=SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);
	if(res < 0)
	{
		printf("SDL init failed: %s\n", SDL_GetError());
		return;
	}

	SDL_Vulkan_LoadLibrary(NULL);

	SDL_PropertiesID	props	=SDL_CreateProperties();

	SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "test grabbery");
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 222);
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 222);
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN, false);
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_VULKAN_BOOLEAN, true);
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_UNDEFINED);
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_UNDEFINED);
	
	SDL_Window	*pWnd	=SDL_CreateWindowWithProperties(props);

	if(pWnd == NULL)
	{
		printf("Window creation didn't work: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}

	bool	bRunning	=true;
	while(bRunning)
	{
		SDL_Event	evt;
		while(SDL_PollEvent(&evt))
		{
			if(evt.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
			{
				SDL_SetRelativeMouseMode(SDL_TRUE);
			}
			else if(evt.type == SDL_EVENT_MOUSE_BUTTON_UP)
			{
				SDL_SetRelativeMouseMode(SDL_FALSE);
			}
			else if(evt.type == SDL_EVENT_KEY_UP)
			{
				if(evt.key.keysym.sym == SDLK_ESCAPE)
				{
					bRunning	=false;
				}
			}
		}
	}

	SDL_Vulkan_UnloadLibrary();

	SDL_DestroyWindow(pWnd);

	SDL_Quit();
}