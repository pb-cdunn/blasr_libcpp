#ifndef _BLASR_SAMQVConversion_HPP_
#define _BLASR_SAMQVConversion_HPP_


#define MAX_PRINTED_QUALITY 93
#define MAX_STORED_QUALITY 100
#define SENTINAL 255
#define MAP_SENTINAL 93


void QualityVectorToPrintable(unsigned char *data, int length);

void QualityStringToStored(unsigned char *data, int length) ;

#endif
