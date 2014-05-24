#include "IODelegate.h"

#define CR "\r\n"

void IODelegate::debug(char* msg, ...)
{
    va_list args;    
    va_start(args, msg);

    IODelegate::log(LOG_LEVEL_DEBUG, msg, args);
}

void IODelegate::debug(const __FlashStringHelper *msg)
{
    Serial.print(F("[DEBUG] " ));
    Serial.println(msg);
}

void IODelegate::error(char* msg, ...)
{
    va_list args;    
    va_start(args, msg);

    IODelegate::log(LOG_LEVEL_ERROR, msg, args);    
}

void IODelegate::error(const __FlashStringHelper *msg)
{
    Serial.print(F("[ERROR] " ));
    Serial.println(msg);
}

void IODelegate::init(long baud, int level)
{
    this->level = constrain(level, LOG_LEVEL_DEBUG, LOG_LEVEL_ERROR);
    Serial.begin(baud);
}

void IODelegate::print(char* format, ...) 
{
    va_list args;    
    va_start(args, format);

    write(format, args);
 }

 void IODelegate::print(const __FlashStringHelper *msg)
 {     
     Serial.println(msg);
 }

void IODelegate::println(char* format, ...)
{
    va_list args;    
    va_start(args, format);
    
    write(format, args);
    write(CR, 0);
}

void IODelegate::println(const __FlashStringHelper *msg)
{     
    Serial.println(msg);
}

// private

void IODelegate::log(int level, const char *format, va_list args)
{
    if (this->level <= level)
    {
        // we only support two log levels 
        Serial.print((level == LOG_LEVEL_DEBUG) ? F("[DEBUG] " ) : F("[ERROR] " ));

        write(format, args);
        write(CR, 0);
    }
}
void IODelegate::write(const char *format, va_list args)
{
    for (; *format != 0; format++)
    {
        if (*format == '%')
        {
            format++;
            if (*format == '\0') 
            {
                break;
            }
            
            if (*format == '%')
            {
                Serial.print(*format);
            }
            else if ( *format == 's' )
            {
                Serial.print((char *)va_arg(args, int));
            }
            else if ( *format == 'd' || *format == 'i')
            {
                Serial.print(va_arg(args, int), DEC);
            }
            else if (*format == 'f')
            {
                writeDecimal((double) va_arg(args, double), 100);
            }            
            else if ( *format == 'x' )
            {
                Serial.print(va_arg(args, int), HEX);
            }
            else if (*format == 'X')
            {
                Serial.print("0x");
                Serial.print(va_arg(args, int), HEX);
            }            
            else if (*format == 'b')
            {
                Serial.print(va_arg(args, int), BIN);
            }
            else if (*format == 'B')
            {
                Serial.print("0b");
                Serial.print(va_arg(args, int), BIN);
            }
            else if (*format == 'l')
            {
                Serial.print(va_arg(args, long), DEC);
            }
            else if (*format == 'c')
            {
                Serial.print((char) va_arg(args, int));
            }
            else if (*format == 't')
            {
                writeBool(args, F("T"), F("F"));
            }
            else if (*format == 'T')
            {
                writeBool(args, F("TRUE"), F("FALSE"));
            }
            else            
            {
                Serial.print(*format);
            }
            
            continue;
        }
        
        Serial.print(*format);
    }
}

void IODelegate::writeBool(va_list args, const __FlashStringHelper *t, const __FlashStringHelper *f)
{
    if (va_arg(args, int) == 1) 
    {
        Serial.print(t);
    }
    else 
    {
        Serial.print(f);                
    } 
}

void IODelegate::writeDecimal(double val, unsigned int precision)
{
    Serial.print(int(val));
    Serial.print(F("."));
    
    unsigned int frac;
    
    if(val >= 0)
    {
        frac = (val - int(val)) * precision;
    }
    else
    {
        frac = (int(val)- val ) * precision;
    }
    
    Serial.print(frac, DEC);
} 
 
IODelegate ioDelegate = IODelegate();
