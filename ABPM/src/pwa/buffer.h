/*
 * buffer.h
 *
 * Add sample to adc_buffer
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * Created: 9/10/2012 1:47:21 PM
 *  Author: yoonl
 */ 


#ifndef BUFFER_H_
#define BUFFER_H_

#include "conf_abpm.h"

#ifdef _DEBUG
// The wave_table(128 sample rate, 12bits, 5seconds) is for testing purpose only to check converted to C methods, will be removed after done porting to C.
static const uint16_t wave_table[640] =
{
	2940,
	2988,
	3016,
	3008,
	2968,
	2932,
	2892,
	2852,
	2816,
	2768,
	2732,
	2696,
	2656,
	2612,
	2568,
	2520,
	2472,
	2432,
	2372,
	2328,
	2284,
	2240,
	2172,
	2112,
	2052,
	1968,
	1916,
	1888,
	1872,
	1852,
	1844,
	1828,
	1824,
	1824,
	1816,
	1812,
	1824,
	1836,
	1844,
	1844,
	1836,
	1836,
	1824,
	1812,
	1788,
	1780,
	1760,
	1740,
	1732,
	1720,
	1684,
	1668,
	1636,
	1624,
	1604,
	1592,
	1576,
	1548,
	1528,
	1504,
	1472,
	1468,
	1448,
	1416,
	1392,
	1376,
	1360,
	1328,
	1320,
	1320,
	1320,
	1312,
	1324,
	1316,
	1320,
	1320,
	1312,
	1316,
	1328,
	1324,
	1324,
	1332,
	1340,
	1360,
	1372,
	1384,
	1400,
	1412,
	1404,
	1400,
	1392,
	1360,
	1308,
	1332,
	1368,
	1424,
	1540,
	1760,
	2104,
	2396,
	2660,
	2784,
	2896,
	2940,
	2988,
	3016,
	3008,
	2968,
	2932,
	2892,
	2852,
	2816,
	2768,
	2732,
	2696,
	2656,
	2612,
	2568,
	2520,
	2472,
	2432,
	2372,
	2328,
	2284,
	2240,
	2172,
	2112,
	2052,
	1968,
	1916,
	1888,
	1872,
	1852,
	1844,
	1828,
	1824,
	1824,
	1816,
	1812,
	1824,
	1836,
	1844,
	1844,
	1836,
	1836,
	1824,
	1812,
	1788,
	1780,
	1760,
	1740,
	1732,
	1720,
	1684,
	1668,
	1636,
	1624,
	1604,
	1592,
	1576,
	1548,
	1528,
	1504,
	1472,
	1468,
	1448,
	1416,
	1392,
	1376,
	1360,
	1328,
	1320,
	1320,
	1320,
	1312,
	1324,
	1316,
	1320,
	1320,
	1312,
	1316,
	1328,
	1324,
	1324,
	1332,
	1340,
	1360,
	1372,
	1384,
	1400,
	1412,
	1404,
	1400,
	1392,
	1360,
	1308,
	1332,
	1368,
	1424,
	1540,
	1760,
	2104,
	2396,
	2660,
	2784,
	2896,
	2940,
	2988,
	3016,
	3008,
	2968,
	2932,
	2892,
	2852,
	2816,
	2768,
	2732,
	2696,
	2656,
	2612,
	2568,
	2520,
	2472,
	2432,
	2372,
	2328,
	2284,
	2240,
	2172,
	2112,
	2052,
	1968,
	1916,
	1888,
	1872,
	1852,
	1844,
	1828,
	1824,
	1824,
	1816,
	1812,
	1824,
	1836,
	1844,
	1844,
	1836,
	1836,
	1824,
	1812,
	1788,
	1780,
	1760,
	1740,
	1732,
	1720,
	1684,
	1668,
	1636,
	1624,
	1604,
	1592,
	1576,
	1548,
	1528,
	1504,
	1472,
	1468,
	1448,
	1416,
	1392,
	1376,
	1360,
	1328,
	1320,
	1320,
	1320,
	1312,
	1324,
	1316,
	1320,
	1320,
	1312,
	1316,
	1328,
	1324,
	1324,
	1332,
	1340,
	1360,
	1372,
	1384,
	1400,
	1412,
	1404,
	1400,
	1392,
	1360,
	1308,
	1332,
	1368,
	1424,
	1540,
	1760,
	2104,
	2396,
	2660,
	2784,
	2896,
	2940,
	2988,
	3016,
	3008,
	2968,
	2932,
	2892,
	2852,
	2816,
	2768,
	2732,
	2696,
	2656,
	2612,
	2568,
	2520,
	2472,
	2432,
	2372,
	2328,
	2284,
	2240,
	2172,
	2112,
	2052,
	1968,
	1916,
	1888,
	1872,
	1852,
	1844,
	1828,
	1824,
	1824,
	1816,
	1812,
	1824,
	1836,
	1844,
	1844,
	1836,
	1836,
	1824,
	1812,
	1788,
	1780,
	1760,
	1740,
	1732,
	1720,
	1684,
	1668,
	1636,
	1624,
	1604,
	1592,
	1576,
	1548,
	1528,
	1504,
	1472,
	1468,
	1448,
	1416,
	1392,
	1376,
	1360,
	1328,
	1320,
	1320,
	1320,
	1312,
	1324,
	1316,
	1320,
	1320,
	1312,
	1316,
	1328,
	1324,
	1324,
	1332,
	1340,
	1360,
	1372,
	1384,
	1400,
	1412,
	1404,
	1400,
	1392,
	1360,
	1308,
	1332,
	1368,
	1424,
	1540,
	1760,
	2104,
	2396,
	2660,
	2784,
	2896,
	2940,
	2988,
	3016,
	3008,
	2968,
	2932,
	2892,
	2852,
	2816,
	2768,
	2732,
	2696,
	2656,
	2612,
	2568,
	2520,
	2472,
	2432,
	2372,
	2328,
	2284,
	2240,
	2172,
	2112,
	2052,
	1968,
	1916,
	1888,
	1872,
	1852,
	1844,
	1828,
	1824,
	1824,
	1816,
	1812,
	1824,
	1836,
	1844,
	1844,
	1836,
	1836,
	1824,
	1812,
	1788,
	1780,
	1760,
	1740,
	1732,
	1720,
	1684,
	1668,
	1636,
	1624,
	1604,
	1592,
	1576,
	1548,
	1528,
	1504,
	1472,
	1468,
	1448,
	1416,
	1392,
	1376,
	1360,
	1328,
	1320,
	1320,
	1320,
	1312,
	1324,
	1316,
	1320,
	1320,
	1312,
	1316,
	1328,
	1324,
	1324,
	1332,
	1340,
	1360,
	1372,
	1384,
	1400,
	1412,
	1404,
	1400,
	1392,
	1360,
	1308,
	1332,
	1368,
	1424,
	1540,
	1760,
	2104,
	2396,
	2660,
	2784,
	2896,
	2940,
	2988,
	3016,
	3008,
	2968,
	2932,
	2892,
	2852,
	2816,
	2768,
	2732,
	2696,
	2656,
	2612,
	2568,
	2520,
	2472,
	2432,
	2372,
	2328,
	2284,
	2240,
	2172,
	2112,
	2052,
	1968,
	1916,
	1888,
	1872,
	1852,
	1844,
	1828,
	1824,
	1824,
	1816,
	1812,
	1824,
	1836,
	1844,
	1844,
	1836,
	1836,
	1824,
	1812,
	1788,
	1780,
	1760,
	1740,
	1732,
	1720,
	1684,
	1668,
	1636,
	1624,
	1604,
	1592,
	1576,
	1548,
	1528,
	1504,
	1472,
	1468,
	1448,
	1416,
	1392,
	1376,
	1360,
	1328,
	1320,
	1320,
	1320,
	1312,
	1324,
	1316,
	1320,
	1320,
	1312,
	1316,
	1328,
	1324,
	1324,
	1332,
	1340,
	1360,
	1372,
	1384,
	1400,
	1412,
	1404,
	1400,
	1392,
	1360,
	1308,
	1332,
	1368,
	1424,
	1540,
	1760,
	2104,
	2396,
	2660,
	2784,
	2896,
	2940,
	2988,
	3016,
	3008,
	2968,
	2932,
	2892,
	2852,
	2816,
	2768,
	2732,
	2696,
	2656,
	2612,
	2568,
	2520,
	2472,
	2432,
	2372,
	2328,
	2284,
	2240
};
#endif

volatile uint16_t *adc_buffer; // 128 sample rate, 12bits, 5seconds.

bool ADCBuffer_init(void);
void AddSignal(uint16_t signal); // Add each collected sample into adc_buffer.
bool IsADCBufferFull(void); // Check adc_buffer is full or not.
void ADCBuffer_final(void);

#endif /* BUFFER_H_ */