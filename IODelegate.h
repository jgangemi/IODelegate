#ifndef IODelegate_H
#define IODelegate_H

#include <stdarg.h>

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_ERROR 2

#define DEFAULT_LEVEL LOG_LEVEL_ERROR 

class IODelegate 
{
	private:
    	
		int level;   

	public:

    	IODelegate(){};
	
		void debug(char* format, ...);
		void debug(const __FlashStringHelper *msg);

		void error(char* format, ...);
		void error(const __FlashStringHelper *msg);
	
		void init(long baud, int level);		
		
		void print(char* format, ...);
		void print(const __FlashStringHelper *msg);
		
		void println(char* format, ...);
		void println(const __FlashStringHelper *msg);
    
	private:
		
		void log(int level, const char* format, va_list args);
		void write(const char *format, va_list args);
		void writeBool(va_list args, const __FlashStringHelper *t, const __FlashStringHelper *f);
		void writeDecimal(double val, unsigned int precision);
};

extern IODelegate ioDelegate;

#endif
