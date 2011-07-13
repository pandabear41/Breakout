#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#ifdef WIN32
    #include <SDL.h>
#else
    #include <SDL/SDL.h>
#endif

class Animation {
	public:
		Animation();
		~Animation();
		void onTick();
		void setFrameRate(int rate);
		void setCurrentFrame(int frame);
		int getCurrentFrame();

		int	maxFrames;
		bool oscillate;
	private:
		int	currentFrame;
		int frameInc;
        int frameRate; //Milliseconds
		long oldTime;

};

#endif // ANIMATION_H_INCLUDED
