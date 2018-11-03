#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WIDTH 1280.0
#define HEIGHT 720.0
#define ASPECT (HEIGHT / WIDTH)
#define INF 100000000

static inline float MIN(float a, float b){
	if(a < b) {
		return a;
	} else {
		return b;
	}
}

static inline float MAX(float a, float b){
	if(a > b) {
		return a;
	} else {
		return b;
	}
}

#endif
