#pragma once
#ifdef _WIN32 || _WIN64
#include <Windows.h>
#endif

inline float GetFrameTime()
{
	static unsigned long long lastTime = 0;
	static unsigned long long timeCurrent = 0;
#ifdef __AAPLE__
	timeval current;
	gettimeofday(&current, nullptr);
	timeCurrent = current.tv_sec * 1000 + current.yv_usec / 1000;
#elif _WIN32 || _WIN64
	timeCurrent = timeGetTime();
#endif
	unsigned long frameTime = lastTime == 0 ? 0 : timeCurrent - lastTime;
	lastTime = timeCurrent;
	return float(frameTime) / 1000;
}


inline void display_4x4(glm::mat4 m4) 
{
	std::cout << "mat[4x4]" << std::endl;
	for (int col = 0; col < 4; ++col)
	{
		std::cout << "| " << '\t';
		for (int row = 0; row < 4; ++row)
		{
			std::cout << m4[col][row] << '\t';
		}
		std::cout << "| " << '\n';
	}
}
inline void display_vec3(glm::vec3 v3) 
{
	std::cout << "vec3" << "\n| " << v3.x << '\t'
		<< v3.y << '\t' << v3.z << '\t' << std::endl;
}
inline void display_vec3(float* v3) 
{
	std::cout << "vec3" << "\n| " << v3[0] << '\t'
		<< v3[1] << '\t' << v3[2] << '\t' << std::endl;
}
inline void display_vec4(glm::vec4 v4)
{
	std::cout << "vec4" << "\n| " << v4.x << '\t'
		<< v4.y << '\t' << v4.z << '\t' << v4.w << '\t'
		<< std::endl;
}
inline void display_vec4(float* v4) 
{
	std::cout << "vec4" << "\n| " << v4[0] << '\t'
		<< v4[1] << '\t' << v4[2] << '\t' << v4[3] << '\t'
		<< std::endl;
}