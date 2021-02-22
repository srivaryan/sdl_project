#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (1280)
#define WINDOW_HEIGHT (960)

// speed in pixels/second
#define SPEED1 (600)
#define SPEED2 (400)

int main(void)
{
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Galaga reloaded!",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT,0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                         "MISSION START",
                         "YOU PILOT THE EAGLE,THE BEST OF THE MEDIUM CLASS FIGHTERS, WITH EXELLENT MANUVERABILITY AND DECENT FIREPOWER.\nHOWEVER, THE ENEMY HAS A HEAVY ALIEN CRUISER, CODENAMED TIGER.\nIT IS THE WORST POSSIBLE SITUATION FOR YOU, BUT THE DEFENSE OF THE FORWARD BASE RESTS IN YOU HANDS.\n			GOOD LUCK",
                         NULL);

    // load the image into memory using SDL_image library function
    SDL_Surface* ship = IMG_Load("resources/b50d96c3-a8b8-4fe3-b135-5472da9241fb_1.png");
    if (!ship)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture* text = SDL_CreateTextureFromSurface(rend, ship);
    SDL_FreeSurface(ship);
    if (!text)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    // struct to hold the position and size of the sprite
    SDL_Rect dests;

    // get and scale the dimensions of texture
    SDL_QueryTexture(text, NULL, NULL, &dests.w, &dests.h);
    dests.w = dests.w/12;
    dests.h = dests.h/12;

    // start sprite
    float x_pos = (WINDOW_WIDTH - dests.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dests.h)*3 / 4;
    float x_vel = 0;
    float y_vel = 0;
    
    // keep track of which inputs are given
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
    
    
    // load the image into memory using SDL_image library function
    SDL_Surface* bullet = IMG_Load("resources/unknown.png");
    if (!bullet)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture* texb = SDL_CreateTextureFromSurface(rend, bullet);
    SDL_FreeSurface(bullet);
    if (!texb)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    // struct to hold the position and size of the sprite
    SDL_Rect destb;

    // get and scale the dimensions of texture
    SDL_QueryTexture(texb, NULL, NULL, &destb.w, &destb.h);
    destb.w = destb.w/8;
    destb.h = destb.h/8;

    // start sprite
    float x_posb = x_pos;
    float y_posb = y_pos;
    float x_velb = 0;
    float y_velb = -SPEED1;
    
    // load the image into memory using SDL_image library function
    SDL_Surface* surface1 = IMG_Load("resources/f079e626-1088-4128-954a-43ac65c7979d.png");
    if (!surface1)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture* tex1 = SDL_CreateTextureFromSurface(rend, surface1);
    SDL_FreeSurface(surface1);
    if (!tex1)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    // struct to hold the position and size of the sprite
    SDL_Rect dest1;
    
    // get and scale the dimensions of texture
    SDL_QueryTexture(tex1, NULL, NULL, &dest1.w, &dest1.h);
    dest1.w = dest1.w/2;
    dest1.h = dest1.h/2;
    
    // start sprite in center of screen
    float x_pos1 = (WINDOW_WIDTH - dest1.w) / 2;
    float y_pos1 = 0;
    // give sprite initial velocity
    float x_vel1 = SPEED2;
    float y_vel1 = 0;
    
    // load the image into memory using SDL_image library function
    SDL_Surface* bullet1 = IMG_Load("resources/unknown1.png");
    if (!bullet1)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture* texc = SDL_CreateTextureFromSurface(rend, bullet1);
    SDL_FreeSurface(bullet1);
    if (!texc)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    // struct to hold the position and size of the sprite
    SDL_Rect destc;

    // get and scale the dimensions of texture
    SDL_QueryTexture(texc, NULL, NULL, &destc.w, &destc.h);
    destc.w = WINDOW_WIDTH/8;
    destc.h = WINDOW_HEIGHT/8;

    // start sprite
    float x_posc = x_pos1;
    float y_posc = y_pos1;
    float x_velc = 0;
    float y_velc = SPEED1;
    
    // set to 1 when window close button is pressed
    int close_requested = 0;
    int i=0,s=0,a=0;
    // animation loop
    while (!close_requested)//close not requested loop
    {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                close_requested = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 1;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 1;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 1;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 0;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 0;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 0;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 0;
                    break;
                }
                break;
            }
        }

        // determine velocity
        x_vel = y_vel = 0;
        if (up && !down) y_vel = -SPEED1;
        if (down && !up) y_vel = SPEED1;
        if (left && !right) x_vel = -SPEED1;
        if (right && !left) x_vel = SPEED1;

        // update positions
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        // collision detection with bounds
        if (x_pos <= 0) x_pos = 0;
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= WINDOW_WIDTH - dests.w) x_pos = WINDOW_WIDTH - dests.w;
        if (y_pos >= WINDOW_HEIGHT - dests.h) y_pos = WINDOW_HEIGHT - dests.h;

        // set the positions in the struct
        dests.y = (int) y_pos;
        dests.x = (int) x_pos;
        
        x_posb += x_velb / 60;
        y_posb += y_velb / 60;
        
        destb.y = (int) y_posb;
        destb.x = (int) x_posb;
        
        if(y_posb == 0)
        {
            x_posb = x_pos + dests.w/2 - 5;
            y_posb = y_pos;
        }
        
        // collision detection with bounds
        if (x_pos1 <= 0)
        {
            x_pos1 = 0;
            x_vel1 = -x_vel1;
        }
        if (y_pos1 <= 0)
        {
            y_pos1 = 0;
            y_vel1 = -y_vel1;
        }
        if (x_pos1 >= WINDOW_WIDTH - dest1.w) 
        {
            x_pos1 = WINDOW_WIDTH - dest1.w;
            x_vel1 = -x_vel1;
        }
        if (y_pos1 >= WINDOW_HEIGHT - dest1.h)
        {
            y_pos1 = WINDOW_HEIGHT - dest1.h;
            y_vel1 = -y_vel1;
        }

        // update positions
        x_pos1 += x_vel1 / 60;
        y_pos1 += y_vel1 / 60;

        // set the positions in the struct
        dest1.y = (int) y_pos1;
        dest1.x = (int) x_pos1;

        x_posc += x_velc / 60;
        y_posc += y_velc / 60;
        
        destc.y = (int) y_posc+dest1.h-20;
        destc.x = (int) x_posc;
        	
	if(y_posc > WINDOW_HEIGHT)
	{
		x_posc = x_pos1 + dest1.w/4 - 50;
		y_posc = y_pos1;
	}
	
	if(y_posb < dest1.h && x_posb > x_pos1 && x_posb < x_pos1+dest1.w)
	{
		a++;
		x_posb = x_pos + dests.w/2 - 5;
        	y_posb = y_pos; 
	}
	
	if(i>300)
	{
		i = 0;
		if(x_pos > x_pos1)
		{
			x_vel1 = SPEED2;
		}
		if(x_pos < x_pos1)
		{
			x_vel1 = -SPEED2;
		}
	}
	
	if(y_posc > y_pos && y_posc < y_pos + dests.w && x_posc+(destc.w/2) > x_pos+10 && x_posc+(destc.w/2) < x_pos+dests.w-10)	//for ship interaction
	{
		s++;
		x_posc = x_pos1 + dest1.w/4 - 50;
		y_posc = y_pos1;
		if(s == 1)
		{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                         "CRITICAL WARNING",
                         "YOUR SHIPS SHIELDS SYSTEMS ARE OFFLINE, IT WILL NOT SURVIVE ANOTHER HEAVY HIT LIKE THAT",
                         NULL);
	}
	
	}
	
	if(a == 10)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                         "YOU WIN",
                         "YOU HAVE SINGLE-HANDEDLY SAVED THE ADVANCE POST FROM DESCTRUCTION.\nTHANKS TO YOU, THE WAR IS WON.\nYOU WILL BE FOREVER REMEMBERED AS A HERO",
                         NULL);
                SDL_Delay(1000);
                close_requested = 1;
	}
	
	if(s == 2)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                         "YOU LOSE",
                         "THE ADVANCE POST HAS BEEN DESTROYED.\nHOWEVER, HUMANITY STILL HAS A CHANCE AT THIS WAR.\nYOU WILL BE FOREVER REMEMBERED AS A MARTYR",
                         NULL);
                SDL_Delay(1000);
                close_requested = 1;
	}
	
        // draw the image to the window
        SDL_RenderCopy(rend, tex1, NULL, &dest1);
        SDL_RenderCopy(rend, text, NULL, &dests);
        SDL_RenderCopy(rend, texb, NULL, &destb);
        SDL_RenderCopy(rend, texc, NULL, &destc);
        SDL_RenderPresent(rend);
	// clear the window
        SDL_RenderClear(rend);
        
        // wait 1/60th of a second
        SDL_Delay(1000/60);
        i++;
    }
    
    // clean up resources before exiting
    SDL_DestroyTexture(tex1);
    SDL_DestroyTexture(text);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
