#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"
#include "weather_utils.h"

int menor_temperatura(WeatherTable array)
{
    int min = array[0][0][0]._min_temp;

    for (unsigned int anho = 0u; anho < YEARS; anho++)
    {
        for (unsigned int mes = 0u; mes < MONTHS; mes++)
        {
            for (unsigned int dia = 0u; dia < DAYS; dia++)
            {
                if (array[anho][mes][dia]._min_temp < min)
                {
                    min = array[anho][mes][dia]._min_temp;
                }
            }
        }
    }
    return min;
}

void mayor_temp_anho(WeatherTable array, int a[YEARS])
{

    for (unsigned int anho = 0u; anho < YEARS; anho++)
    {
        int max = array[anho][0][0]._max_temp;

        for (unsigned int mes = 0u; mes < MONTHS; mes++)
        {
            for (unsigned int dia = 0u; dia < DAYS; dia++)
            {
                if (array[anho][mes][dia]._max_temp > max)
                {
                    max = array[anho][mes][dia]._max_temp;
                }
            }
        }

        a[anho] = max;
    }
}

void procedimiento(WeatherTable a, int output[])
{
    unsigned int prec, precMes;
    unsigned int mayorMes = 0; 
    
    
    for (unsigned int year = 0; year < YEARS; year++)
    { precMes = 0;
        for (unsigned int mes = 0; mes < MONTHS; mes++)
        {
            prec = 0;
            for (unsigned int dia = 0; dia < DAYS; dia++)
            {
                prec  = a[year][mes][dia]._rainfall + prec;
            }
            
            if (prec >= precMes)
            {
                precMes = prec;
                mayorMes = (mes+1);
            }
            
            
        }
        
        output[year] = mayorMes;
    }
}   